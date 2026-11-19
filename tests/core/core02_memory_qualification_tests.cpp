#include "stormline/core/memory/leak_tracker.hpp"
#include "stormline/core/memory/memory_block.hpp"
#include "stormline/core/memory/memory_budget.hpp"
#include "stormline/core/memory/memory_telemetry.hpp"
#include "stormline/core/memory/monotonic_arena.hpp"
#include "stormline/core/memory/system_memory_resource.hpp"

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <string_view>
#include <vector>

namespace {

using stormline::core::memory::ArenaError;
using stormline::core::memory::ArenaSlice;
using stormline::core::memory::BudgetError;
using stormline::core::memory::BudgetStatus;
using stormline::core::memory::LeakError;
using stormline::core::memory::LeakToken;
using stormline::core::memory::LeakTracker;
using stormline::core::memory::MemoryBlock;
using stormline::core::memory::MemoryBudget;
using stormline::core::memory::MemoryDomain;
using stormline::core::memory::MemoryError;
using stormline::core::memory::MemoryTelemetry;
using stormline::core::memory::MemoryTelemetrySnapshot;
using stormline::core::memory::MonotonicArena;
using stormline::core::memory::SystemMemoryResource;
using stormline::core::memory::TelemetryError;

int failures = 0;

void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}

void begin_case() {
    failures = 0;
}

bool finish_case() {
    return failures == 0;
}

std::size_t domain_index(MemoryDomain domain) {
    return static_cast<std::size_t>(domain);
}

bool telemetry_balanced(const MemoryTelemetrySnapshot& snapshot) {
    return snapshot.allocations == snapshot.releases + snapshot.live_allocations &&
           snapshot.total_allocated_bytes ==
               snapshot.total_released_bytes + snapshot.live_bytes;
}

bool run_integrated() {
    begin_case();
    SystemMemoryResource resource;
    MemoryTelemetry telemetry;
    MemoryTelemetrySnapshot snapshot{};

    {
        MonotonicArena arena(64 * 1024, 64, &resource, &telemetry);
        MemoryBudget budget(4096, 16384, &telemetry);
        LeakTracker leaks(&telemetry);

        MemoryBlock persistent;
        MemoryBlock job;
        MemoryBlock streaming;
        expect(MemoryBlock::allocate(&resource, 256, 64, MemoryDomain::Persistent,
                                     persistent, &telemetry) == MemoryError::None,
               "integrated persistent block");
        expect(MemoryBlock::allocate(&resource, 128, 16, MemoryDomain::Job, job,
                                     &telemetry) == MemoryError::None,
               "integrated job block");
        expect(MemoryBlock::allocate(&resource, 64, 8, MemoryDomain::Streaming, streaming,
                                     &telemetry) == MemoryError::None,
               "integrated streaming block");

        ArenaSlice slice{};
        expect(arena.allocate(128, 16, slice) == ArenaError::None, "integrated arena slice");
        expect(arena.allocate(256, 64, slice) == ArenaError::None, "integrated arena slice 2");

        BudgetStatus status = BudgetStatus::Within;
        expect(budget.try_reserve(4096, status) == BudgetError::None, "integrated budget soft");
        expect(status == BudgetStatus::SoftPressure, "integrated soft pressure");
        expect(budget.try_reserve(8192, status) == BudgetError::None, "integrated budget more");
        expect(budget.try_reserve(8192, status) == BudgetError::ExceededHardLimit,
               "integrated hard rejection");

        LeakToken first{};
        LeakToken second{};
        expect(leaks.track(64, first) == LeakError::None, "integrated leak first");
        expect(leaks.track(32, second) == LeakError::None, "integrated leak second");
        expect(leaks.release(first) == LeakError::None, "integrated leak release first");

        telemetry.snapshot(snapshot);
        expect(snapshot.domains[domain_index(MemoryDomain::Persistent)].live_bytes == 256,
               "integrated persistent bytes");
        expect(snapshot.domains[domain_index(MemoryDomain::Job)].live_bytes == 128,
               "integrated job bytes");
        expect(snapshot.domains[domain_index(MemoryDomain::Streaming)].live_bytes == 64,
               "integrated streaming bytes");
        expect(snapshot.domains[domain_index(MemoryDomain::Frame)].live_bytes == 64 * 1024,
               "integrated arena backing bytes");
        expect(snapshot.budget.reservations == 2, "integrated budget reservations");
        expect(snapshot.budget.hard_rejections == 1, "integrated budget rejection");
        expect(snapshot.leak.tracked == 2, "integrated leak tracked");
        expect(snapshot.leak.released == 1, "integrated leak released");
        expect(snapshot.arena.slices == 2, "integrated arena slices");
        expect(snapshot.arena.high_water_bytes == 384, "integrated arena high water");
        expect(telemetry_balanced(snapshot), "integrated telemetry balanced");
        expect(leaks.release(second) == LeakError::None, "integrated leak release second");
        expect(leaks.empty(), "integrated leak empty");
        expect(budget.release(12288) == BudgetError::None, "integrated budget release");
        expect(budget.used() == 0, "integrated budget drained");
        expect(persistent.release() == MemoryError::None, "integrated persistent release");
        expect(job.release() == MemoryError::None, "integrated job release");
        expect(streaming.release() == MemoryError::None, "integrated streaming release");
        expect(arena.reset() == ArenaError::None, "integrated arena reset");
        expect(arena.used() == 0, "integrated arena drained");
    }

    telemetry.snapshot(snapshot);
    expect(telemetry.empty(), "integrated telemetry empty after scope");
    expect(telemetry_balanced(snapshot), "integrated final counters balanced");
    expect(snapshot.domains[domain_index(MemoryDomain::Frame)].live_bytes == 0,
           "integrated arena backing released");
    return finish_case();
}

bool run_stress() {
    begin_case();
    SystemMemoryResource resource;
    MemoryTelemetry telemetry;
    constexpr int iterations = 10000;
    {
        MonotonicArena arena(64 * 1024, 64, &resource, &telemetry);
        MemoryBudget budget(4096, 16384, &telemetry);
        LeakTracker leaks(&telemetry);
        bool ok = true;
        for (int iteration = 0; iteration < iterations && ok; ++iteration) {
            const std::size_t size = 32 + static_cast<std::size_t>(iteration % 16) * 64;
            const std::size_t alignment = (iteration % 2) == 0 ? 8 : 64;
            MemoryBlock block;
            ok = MemoryBlock::allocate(&resource, size, alignment, MemoryDomain::Job, block,
                                       &telemetry) == MemoryError::None;
            ok = ok && block.release() == MemoryError::None;

            ArenaSlice slice{};
            ok = ok && arena.allocate(64, 16, slice) == ArenaError::None;
            if (iteration % 32 == 31) {
                ok = ok && arena.reset() == ArenaError::None;
            }

            BudgetStatus status = BudgetStatus::Within;
            ok = ok && budget.try_reserve(256, status) == BudgetError::None;
            ok = ok && budget.release(256) == BudgetError::None;

            LeakToken token{};
            ok = ok && leaks.track(32, token) == LeakError::None;
            ok = ok && leaks.release(token) == LeakError::None;

            ok = ok && telemetry.record_allocate(MemoryDomain::Streaming, 16) ==
                           TelemetryError::None;
            ok = ok && telemetry.record_release(MemoryDomain::Streaming, 16) ==
                           TelemetryError::None;
        }
        expect(ok, "stress iterations complete");
        expect(leaks.empty(), "stress leaks empty");
        expect(budget.used() == 0, "stress budget drained");
        expect(arena.reset() == ArenaError::None, "stress arena reset");
        expect(arena.used() == 0, "stress arena drained");
    }
    MemoryTelemetrySnapshot snapshot{};
    telemetry.snapshot(snapshot);
    expect(telemetry.empty(), "stress telemetry empty");
    expect(telemetry_balanced(snapshot), "stress telemetry balanced");
    expect(snapshot.allocations >= static_cast<std::uint64_t>(iterations),
           "stress allocation count");
    return finish_case();
}

bool run_recovery() {
    begin_case();
    SystemMemoryResource resource;
    MemoryTelemetry telemetry;

    {
        MonotonicArena arena(1024, 64, &resource, &telemetry);
        ArenaSlice slice{};
        bool exhausted = false;
        for (int index = 0; index < 100 && !exhausted; ++index) {
            const ArenaError error = arena.allocate(64, 64, slice);
            if (error == ArenaError::OutOfMemory) {
                exhausted = true;
            }
        }
        expect(exhausted, "arena exhausted");
        const std::size_t used = arena.used();
        const std::size_t high_water = arena.high_water();
        expect(arena.allocate(64, 64, slice) == ArenaError::OutOfMemory,
               "arena overflow rejected");
        expect(arena.used() == used && arena.high_water() == high_water,
               "arena overflow non-mutating");
        expect(arena.reset() == ArenaError::None, "arena recovery reset");
        expect(arena.allocate(512, 64, slice) == ArenaError::None, "arena recovery allocate");
    }

    MemoryBudget budget(100, 200, &telemetry);
    BudgetStatus status = BudgetStatus::Within;
    expect(budget.try_reserve(200, status) == BudgetError::None, "budget recovery reserve hard");
    expect(budget.try_reserve(1, status) == BudgetError::ExceededHardLimit,
           "budget recovery rejects excess");
    expect(budget.used() == 200, "budget rejection non-mutating");
    expect(budget.release(200) == BudgetError::None, "budget recovery release");
    expect(budget.try_reserve(50, status) == BudgetError::None, "budget recovery reserve");

    LeakTracker leaks(&telemetry);
    std::array<LeakToken, LeakTracker::capacity> tokens{};
    bool filled = true;
    for (std::size_t index = 0; index < tokens.size(); ++index) {
        filled = leaks.track(1, tokens[index]) == LeakError::None && filled;
    }
    expect(filled, "leak tracker filled");
    LeakToken rejected{};
    expect(leaks.track(1, rejected) == LeakError::CapacityExceeded,
           "leak capacity rejected");
    expect(leaks.release(tokens[0]) == LeakError::None, "leak slot released");
    LeakToken reused{};
    expect(leaks.track(1, reused) == LeakError::None, "leak slot reused");
    expect(reused.generation > tokens[0].generation, "leak generation advanced");
    expect(leaks.release(tokens[0]) == LeakError::InvalidToken, "leak stale token rejected");
    for (std::size_t index = 1; index < tokens.size(); ++index) {
        expect(leaks.release(tokens[index]) == LeakError::None, "leak recovery release");
    }
    expect(leaks.release(reused) == LeakError::None, "leak reused release");
    expect(leaks.empty(), "leak recovery empty");

    expect(telemetry.record_release(MemoryDomain::Job, 1) == TelemetryError::ReleaseUnderflow,
           "telemetry recovery underflow");
    expect(telemetry.record_allocate(MemoryDomain::Job, 8) == TelemetryError::None,
           "telemetry recovery allocate");
    expect(telemetry.record_release(MemoryDomain::Job, 9) == TelemetryError::ReleaseUnderflow,
           "telemetry recovery over-release");
    expect(telemetry.record_release(MemoryDomain::Job, 8) == TelemetryError::None,
           "telemetry recovery release");
    expect(telemetry.empty(), "telemetry recovery empty");
    return finish_case();
}

bool run_size_churn() {
    begin_case();
    SystemMemoryResource resource;
    MemoryTelemetry telemetry;
    constexpr int iterations = 2000;
    std::array<MemoryBlock, 64> live{};
    bool ok = true;
    for (int iteration = 0; iteration < iterations && ok; ++iteration) {
        MemoryBlock& slot = live[static_cast<std::size_t>(iteration) % live.size()];
        if (slot.valid()) {
            ok = slot.release() == MemoryError::None;
        }
        const std::size_t size = 1 + static_cast<std::size_t>(iteration * 37 % 4096);
        const std::size_t alignment = (iteration % 3) == 0 ? 64 : ((iteration % 3) == 1 ? 16 : 8);
        const MemoryDomain domain = static_cast<MemoryDomain>(
            static_cast<std::uint8_t>(MemoryDomain::Persistent) +
            static_cast<std::uint8_t>(iteration % 4));
        ok = ok && MemoryBlock::allocate(&resource, size, alignment, domain, slot,
                                         &telemetry) == MemoryError::None;
    }
    for (MemoryBlock& slot : live) {
        if (slot.valid()) {
            ok = ok && slot.release() == MemoryError::None;
        }
    }
    expect(ok, "size churn allocations and releases succeed");
    MemoryTelemetrySnapshot snapshot{};
    telemetry.snapshot(snapshot);
    expect(telemetry.empty(), "size churn telemetry empty");
    expect(telemetry_balanced(snapshot), "size churn counters balanced");
    expect(snapshot.allocations >= static_cast<std::uint64_t>(iterations),
           "size churn allocation count");
    return finish_case();
}

bool run_benchmark() {
    begin_case();
    SystemMemoryResource resource;
    MemoryTelemetry telemetry;
    MemoryBudget budget(4096, 16384, &telemetry);
    constexpr int iterations = 50000;
    const auto start = std::chrono::steady_clock::now();
    bool ok = true;
    for (int iteration = 0; iteration < iterations && ok; ++iteration) {
        MemoryBlock block;
        ok = MemoryBlock::allocate(&resource, 128, 16, MemoryDomain::Job, block,
                                   &telemetry) == MemoryError::None;
        ok = ok && telemetry.record_allocate(MemoryDomain::Frame, 8) == TelemetryError::None;
        ok = ok && telemetry.record_release(MemoryDomain::Frame, 8) == TelemetryError::None;
        ok = ok && block.release() == MemoryError::None;
        BudgetStatus status = BudgetStatus::Within;
        ok = ok && budget.try_reserve(64, status) == BudgetError::None;
        ok = ok && budget.release(64) == BudgetError::None;
    }
    const auto elapsed = std::chrono::steady_clock::now() - start;
    const double ns = std::chrono::duration<double, std::nano>(elapsed).count();
    expect(ok, "qualification benchmark iterations succeed");
    expect(telemetry.empty(), "qualification benchmark telemetry empty");
    MemoryTelemetrySnapshot snapshot{};
    telemetry.snapshot(snapshot);
    expect(telemetry_balanced(snapshot), "qualification benchmark balanced");
    std::printf("CORE02_QUAL_BENCH_NS_PER_ITER=%.3f iterations=%d\n",
                ns / static_cast<double>(iterations), iterations);
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: %s <integrated|stress|recovery|size_churn|benchmark>\n",
                     argv[0]);
        return 2;
    }

    const std::string_view mode(argv[1]);
    if (mode == "integrated") {
        return run_integrated() ? 0 : 1;
    }
    if (mode == "stress") {
        return run_stress() ? 0 : 1;
    }
    if (mode == "recovery") {
        return run_recovery() ? 0 : 1;
    }
    if (mode == "size_churn") {
        return run_size_churn() ? 0 : 1;
    }
    if (mode == "benchmark") {
        return run_benchmark() ? 0 : 1;
    }

    std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return 2;
}
