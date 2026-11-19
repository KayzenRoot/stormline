#include "stormline/core/memory/memory_telemetry.hpp"

#include "stormline/core/memory/leak_tracker.hpp"
#include "stormline/core/memory/memory_block.hpp"
#include "stormline/core/memory/memory_budget.hpp"
#include "stormline/core/memory/monotonic_arena.hpp"
#include "stormline/core/memory/system_memory_resource.hpp"

#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <string_view>
#include <thread>
#include <vector>

namespace {

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

bool run_basic() {
    begin_case();
    MemoryTelemetry telemetry;
    MemoryTelemetrySnapshot snapshot{};
    telemetry.snapshot(snapshot);
    expect(snapshot.allocations == 0 && snapshot.live_bytes == 0, "fresh telemetry empty");
    expect(telemetry.empty(), "fresh telemetry reports empty");

    expect(telemetry.record_allocate(MemoryDomain::Persistent, 64) == TelemetryError::None,
           "allocate persistent succeeds");
    expect(telemetry.record_allocate(MemoryDomain::Job, 32) == TelemetryError::None,
           "allocate job succeeds");
    telemetry.snapshot(snapshot);
    expect(snapshot.allocations == 2, "two allocations counted");
    expect(snapshot.live_allocations == 2, "two live allocations");
    expect(snapshot.live_bytes == 96, "96 live bytes");
    expect(snapshot.peak_live_bytes == 96, "peak live bytes 96");
    expect(snapshot.total_allocated_bytes == 96, "total allocated 96");
    const auto& persistent = snapshot.domains[domain_index(MemoryDomain::Persistent)];
    const auto& job = snapshot.domains[domain_index(MemoryDomain::Job)];
    expect(persistent.allocations == 1 && persistent.live_bytes == 64,
           "persistent domain isolated");
    expect(job.allocations == 1 && job.live_bytes == 32, "job domain isolated");

    expect(telemetry.record_release(MemoryDomain::Persistent, 64) == TelemetryError::None,
           "release persistent succeeds");
    telemetry.snapshot(snapshot);
    expect(snapshot.releases == 1, "one release counted");
    expect(snapshot.live_allocations == 1, "one live allocation remains");
    expect(snapshot.live_bytes == 32, "32 live bytes remain");
    expect(snapshot.total_released_bytes == 64, "total released 64");
    expect(snapshot.domains[domain_index(MemoryDomain::Persistent)].releases == 1,
           "persistent release isolated");
    expect(snapshot.peak_live_bytes == 96, "peak retained after release");

    expect(telemetry.record_release(MemoryDomain::Job, 32) == TelemetryError::None,
           "release job succeeds");
    telemetry.snapshot(snapshot);
    expect(snapshot.allocations == 2 && snapshot.releases == 2, "counts balanced");
    expect(snapshot.live_allocations == 0 && snapshot.live_bytes == 0, "telemetry drained");
    expect(telemetry.empty(), "telemetry empty after drain");
    expect(snapshot.total_allocated_bytes == snapshot.total_released_bytes,
           "cumulative counters balanced");
    return finish_case();
}

bool run_invalid() {
    begin_case();
    MemoryTelemetry telemetry;
    MemoryTelemetrySnapshot snapshot{};
    const MemoryDomain invalid = static_cast<MemoryDomain>(255);
    expect(telemetry.record_allocate(MemoryDomain::Persistent, 0) == TelemetryError::InvalidBytes,
           "zero-byte allocate rejected");
    expect(telemetry.record_release(MemoryDomain::Persistent, 0) == TelemetryError::InvalidBytes,
           "zero-byte release rejected");
    expect(telemetry.record_allocate(invalid, 8) == TelemetryError::InvalidDomain,
           "invalid allocate domain rejected");
    expect(telemetry.record_release(invalid, 8) == TelemetryError::InvalidDomain,
           "invalid release domain rejected");
    telemetry.snapshot(snapshot);
    expect(snapshot.allocations == 0 && snapshot.releases == 0, "invalid input not counted");
    expect(snapshot.live_bytes == 0, "invalid input leaves no live bytes");
    return finish_case();
}

bool run_underflow() {
    begin_case();
    MemoryTelemetry telemetry;
    MemoryTelemetrySnapshot snapshot{};
    expect(telemetry.record_release(MemoryDomain::Job, 8) == TelemetryError::ReleaseUnderflow,
           "release without allocation rejected");
    expect(telemetry.record_allocate(MemoryDomain::Job, 64) == TelemetryError::None,
           "allocate 64 succeeds");
    expect(telemetry.record_release(MemoryDomain::Job, 65) == TelemetryError::ReleaseUnderflow,
           "release above live bytes rejected");
    telemetry.snapshot(snapshot);
    expect(snapshot.allocations == 1 && snapshot.releases == 0, "underflow not counted");
    expect(snapshot.live_allocations == 1 && snapshot.live_bytes == 64,
           "underflow leaves live state unchanged");
    expect(telemetry.record_release(MemoryDomain::Job, 64) == TelemetryError::None,
           "exact release succeeds");
    expect(telemetry.record_release(MemoryDomain::Job, 64) == TelemetryError::ReleaseUnderflow,
           "double release rejected");
    telemetry.snapshot(snapshot);
    expect(snapshot.live_allocations == 0 && snapshot.live_bytes == 0,
           "telemetry drained after exact release");
    return finish_case();
}

bool run_integration() {
    begin_case();
    SystemMemoryResource resource;
    MemoryTelemetry telemetry;
    MemoryTelemetrySnapshot snapshot{};

    {
        MemoryBlock block;
        expect(MemoryBlock::allocate(&resource, 64, 8, MemoryDomain::Job, block,
                                     &telemetry) == MemoryError::None,
               "block allocation with telemetry succeeds");
        telemetry.snapshot(snapshot);
        expect(snapshot.domains[domain_index(MemoryDomain::Job)].live_bytes == 64,
               "block allocation recorded");
        expect(block.release() == MemoryError::None, "block release succeeds");
        telemetry.snapshot(snapshot);
        expect(snapshot.domains[domain_index(MemoryDomain::Job)].releases == 1,
               "block release recorded");
        expect(snapshot.domains[domain_index(MemoryDomain::Job)].live_bytes == 0,
               "block release clears live bytes");
    }

    {
        MemoryBudget budget(100, 200, &telemetry);
        BudgetStatus status = BudgetStatus::Within;
        expect(budget.try_reserve(50, status) == BudgetError::None, "budget reserve 50");
        expect(budget.try_reserve(100, status) == BudgetError::None, "budget reserve 100");
        expect(status == BudgetStatus::SoftPressure, "budget soft pressure reached");
        expect(budget.try_reserve(60, status) == BudgetError::ExceededHardLimit,
               "budget hard rejection");
        telemetry.snapshot(snapshot);
        expect(snapshot.budget.reservations == 2, "two budget reservations recorded");
        expect(snapshot.budget.reserved_bytes == 150, "budget reserved bytes recorded");
        expect(snapshot.budget.peak_reserved_bytes == 150, "budget peak recorded");
        expect(snapshot.budget.soft_pressure_events == 1, "soft pressure event recorded");
        expect(snapshot.budget.hard_rejections == 1, "hard rejection recorded");
        expect(budget.release(150) == BudgetError::None, "budget release succeeds");
        telemetry.snapshot(snapshot);
        expect(snapshot.budget.releases == 1, "budget release recorded");
        expect(snapshot.budget.released_bytes == 150, "budget released bytes recorded");
    }

    {
        LeakTracker tracker(&telemetry);
        LeakToken token{};
        expect(tracker.track(32, token) == LeakError::None, "leak token tracked");
        telemetry.snapshot(snapshot);
        expect(snapshot.leak.tracked == 1, "leak track recorded");
        expect(snapshot.leak.tracked_bytes == 32, "leak tracked bytes recorded");
        expect(snapshot.leak.peak_tracked_bytes == 32, "leak peak recorded");
        expect(tracker.release(token) == LeakError::None, "leak token released");
        telemetry.snapshot(snapshot);
        expect(snapshot.leak.released == 1, "leak release recorded");
        expect(snapshot.leak.released_bytes == 32, "leak released bytes recorded");
    }

    {
        MonotonicArena arena(1024, 64, &resource, &telemetry);
        ArenaSlice slice{};
        expect(arena.allocate(128, 16, slice) == stormline::core::memory::ArenaError::None,
               "arena slice 128 succeeds");
        telemetry.snapshot(snapshot);
        expect(snapshot.arena.slices == 1, "arena slice counted");
        expect(snapshot.arena.slice_bytes == 128, "arena slice bytes counted");
        expect(snapshot.arena.high_water_bytes == 128, "arena high-water counted");
        expect(snapshot.domains[domain_index(MemoryDomain::Frame)].live_bytes == 1024,
               "arena backing allocation recorded");
        expect(arena.reset() == stormline::core::memory::ArenaError::None,
               "arena reset succeeds");
        expect(arena.allocate(256, 64, slice) == stormline::core::memory::ArenaError::None,
               "arena slice 256 succeeds");
        telemetry.snapshot(snapshot);
        expect(snapshot.arena.slices == 2, "second arena slice counted");
        expect(snapshot.arena.slice_bytes == 384, "arena slice bytes accumulate");
        expect(snapshot.arena.high_water_bytes == 256, "arena high-water updates");
    }
    telemetry.snapshot(snapshot);
    expect(snapshot.domains[domain_index(MemoryDomain::Frame)].live_bytes == 0,
           "arena backing release recorded");
    expect(telemetry.empty(), "telemetry empty after integration scopes");

    MemoryBlock plain;
    expect(MemoryBlock::allocate(&resource, 16, 8, MemoryDomain::Persistent, plain) ==
               MemoryError::None,
           "telemetry-null block allocation unchanged");
    expect(plain.release() == MemoryError::None, "telemetry-null block release unchanged");
    return finish_case();
}

bool run_concurrent() {
    begin_case();
    MemoryTelemetry telemetry;
    std::atomic<int> worker_failures{0};
    constexpr int thread_count = 4;
    constexpr int iterations = 10000;
    std::vector<std::thread> workers;
    workers.reserve(thread_count);
    for (int worker = 0; worker < thread_count; ++worker) {
        workers.emplace_back([&telemetry, &worker_failures] {
            for (int iteration = 0; iteration < iterations; ++iteration) {
                if (telemetry.record_allocate(MemoryDomain::Job, 8) != TelemetryError::None ||
                    telemetry.record_release(MemoryDomain::Job, 8) != TelemetryError::None) {
                    worker_failures.fetch_add(1);
                }
            }
        });
    }
    for (std::thread& worker : workers) {
        worker.join();
    }
    expect(worker_failures.load() == 0, "concurrent record operations succeed");
    MemoryTelemetrySnapshot snapshot{};
    telemetry.snapshot(snapshot);
    expect(snapshot.allocations == thread_count * iterations, "concurrent allocations counted");
    expect(snapshot.releases == thread_count * iterations, "concurrent releases counted");
    expect(snapshot.live_allocations == 0, "concurrent live allocations zero");
    expect(snapshot.live_bytes == 0, "concurrent live bytes zero");
    expect(snapshot.total_allocated_bytes == snapshot.total_released_bytes,
           "concurrent cumulative counters balanced");
    expect(telemetry.empty(), "telemetry empty after concurrency");
    return finish_case();
}

bool run_benchmark() {
    begin_case();
    MemoryTelemetry telemetry;
    constexpr int iterations = 500000;
    const auto start = std::chrono::steady_clock::now();
    for (int iteration = 0; iteration < iterations; ++iteration) {
        if (telemetry.record_allocate(MemoryDomain::Frame, 8) != TelemetryError::None ||
            telemetry.record_release(MemoryDomain::Frame, 8) != TelemetryError::None) {
            ++failures;
        }
    }
    const auto elapsed = std::chrono::steady_clock::now() - start;
    const double ns = std::chrono::duration<double, std::nano>(elapsed).count();
    MemoryTelemetrySnapshot snapshot{};
    telemetry.snapshot(snapshot);
    expect(failures == 0, "benchmark record operations succeed");
    expect(snapshot.allocations == iterations && snapshot.releases == iterations,
           "benchmark counters balanced");
    expect(telemetry.empty(), "benchmark telemetry empty");
    std::printf("TELEMETRY_BENCH_NS_PER_PAIR=%.3f iterations=%d\n",
                ns / static_cast<double>(iterations), iterations);
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: %s <basic|invalid|underflow|integration|concurrent|benchmark>\n",
                     argv[0]);
        return 2;
    }

    const std::string_view mode(argv[1]);
    if (mode == "basic") {
        return run_basic() ? 0 : 1;
    }
    if (mode == "invalid") {
        return run_invalid() ? 0 : 1;
    }
    if (mode == "underflow") {
        return run_underflow() ? 0 : 1;
    }
    if (mode == "integration") {
        return run_integration() ? 0 : 1;
    }
    if (mode == "concurrent") {
        return run_concurrent() ? 0 : 1;
    }
    if (mode == "benchmark") {
        return run_benchmark() ? 0 : 1;
    }

    std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return 2;
}
