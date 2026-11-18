#include "stormline/core/memory/leak_tracker.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string_view>
#include <thread>

namespace {

using stormline::core::memory::LeakError;
using stormline::core::memory::LeakToken;
using stormline::core::memory::LeakTracker;

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

bool run_basic() {
    begin_case();
    LeakTracker tracker;
    expect(tracker.empty(), "fresh tracker empty");
    expect(tracker.live_allocations() == 0, "fresh live allocations zero");
    expect(tracker.live_bytes() == 0, "fresh live bytes zero");
    expect(tracker.peak_allocations() == 0, "fresh peak allocations zero");
    expect(tracker.peak_bytes() == 0, "fresh peak bytes zero");

    LeakToken first{};
    LeakToken second{};
    expect(tracker.track(64, first) == LeakError::None, "track 64 succeeds");
    expect(tracker.track(128, second) == LeakError::None, "track 128 succeeds");
    expect(!(first == second), "tokens are distinct");
    expect(tracker.live_allocations() == 2, "two live allocations");
    expect(tracker.live_bytes() == 192, "192 live bytes");
    expect(tracker.peak_allocations() == 2, "peak allocations two");
    expect(tracker.peak_bytes() == 192, "peak bytes 192");
    expect(!tracker.empty(), "tracker not empty");

    expect(tracker.release(first) == LeakError::None, "release first succeeds");
    expect(tracker.live_allocations() == 1, "one live allocation");
    expect(tracker.live_bytes() == 128, "128 live bytes");
    expect(tracker.release(second) == LeakError::None, "release second succeeds");
    expect(tracker.empty(), "tracker empty after releases");
    expect(tracker.live_bytes() == 0, "live bytes zero after releases");
    expect(tracker.peak_allocations() == 2, "peak allocations retained");
    expect(tracker.peak_bytes() == 192, "peak bytes retained");
    return finish_case();
}

bool run_invalid() {
    begin_case();
    LeakTracker tracker;
    LeakToken unchanged{7, 9};
    expect(tracker.track(0, unchanged) == LeakError::InvalidBytes,
           "zero-byte track rejected");
    expect(unchanged.index == 7 && unchanged.generation == 9,
           "invalid bytes leaves token unchanged");
    expect(tracker.empty(), "invalid bytes leaves tracker empty");
    expect(tracker.live_bytes() == 0, "invalid bytes leaves live bytes zero");
    expect(tracker.peak_allocations() == 0, "invalid bytes leaves peak zero");
    return finish_case();
}

bool run_capacity() {
    begin_case();
    LeakTracker tracker;
    std::array<LeakToken, LeakTracker::capacity> tokens{};
    bool filled = true;
    for (std::size_t index = 0; index < tokens.size(); ++index) {
        filled = tracker.track(index + 1, tokens[index]) == LeakError::None && filled;
    }
    expect(filled, "all capacity slots tracked");
    expect(tracker.live_allocations() == LeakTracker::capacity, "tracker full");
    expect(tracker.live_bytes() == 8256, "capacity live bytes correct");
    expect(tracker.peak_allocations() == LeakTracker::capacity, "peak reaches capacity");
    expect(tracker.peak_bytes() == 8256, "peak bytes reach capacity");

    LeakToken rejected{11, 13};
    expect(tracker.track(1, rejected) == LeakError::CapacityExceeded,
           "capacity overflow rejected");
    expect(rejected.index == 11 && rejected.generation == 13,
           "capacity overflow leaves token unchanged");
    expect(tracker.live_allocations() == LeakTracker::capacity,
           "capacity overflow leaves live count unchanged");
    expect(tracker.live_bytes() == 8256, "capacity overflow leaves live bytes unchanged");

    const LeakToken released = tokens[0];
    expect(tracker.release(released) == LeakError::None, "release one slot succeeds");
    LeakToken reused{};
    expect(tracker.track(1, reused) == LeakError::None, "released slot reusable");
    expect(reused.index == released.index, "reused slot index matches");
    expect(reused.generation == released.generation + 1, "reuse advances generation");
    expect(tracker.release(released) == LeakError::InvalidToken,
           "stale token rejected after reuse");
    expect(tracker.release(reused) == LeakError::None, "reused token releases");

    bool released_all = true;
    for (std::size_t index = 1; index < tokens.size(); ++index) {
        released_all = tracker.release(tokens[index]) == LeakError::None && released_all;
    }
    expect(released_all, "remaining tokens released");
    expect(tracker.empty(), "tracker empty after capacity drain");
    expect(tracker.live_bytes() == 0, "live bytes zero after capacity drain");
    expect(tracker.peak_allocations() == LeakTracker::capacity, "peak retained after drain");
    expect(tracker.peak_bytes() == 8256, "peak bytes retained after drain");
    return finish_case();
}

bool run_token() {
    begin_case();
    LeakTracker tracker;
    LeakToken token{};
    expect(tracker.track(8, token) == LeakError::None, "track 8 succeeds");

    LeakToken forged = token;
    ++forged.generation;
    expect(tracker.release(forged) == LeakError::InvalidToken,
           "forged generation rejected");
    LeakToken out_of_range{static_cast<std::uint32_t>(LeakTracker::capacity), 1};
    expect(tracker.release(out_of_range) == LeakError::InvalidToken,
           "out-of-range token rejected");
    expect(tracker.release(LeakToken{}) == LeakError::InvalidToken,
           "default token rejected");
    expect(tracker.live_allocations() == 1, "invalid tokens leave live count unchanged");
    expect(tracker.live_bytes() == 8, "invalid tokens leave live bytes unchanged");

    expect(tracker.release(token) == LeakError::None, "original token releases");
    expect(tracker.release(token) == LeakError::InvalidToken, "double release rejected");
    expect(tracker.empty(), "tracker empty after release");
    expect(tracker.live_bytes() == 0, "live bytes zero after release");
    return finish_case();
}

bool run_lifetime() {
    begin_case();
    LeakTracker tracker;
    bool ok = true;
    for (int cycle = 0; cycle < 1000 && ok; ++cycle) {
        LeakToken token{};
        ok = tracker.track(8, token) == LeakError::None;
        ok = ok && tracker.release(token) == LeakError::None;
        ok = ok && tracker.empty();
    }
    expect(ok, "1000 track/release cycles succeed");
    expect(tracker.live_bytes() == 0, "lifetime leaves live bytes zero");
    expect(tracker.peak_allocations() == 1, "lifetime peak allocations one");
    expect(tracker.peak_bytes() == 8, "lifetime peak bytes eight");
    return finish_case();
}

bool run_wrong_thread() {
    begin_case();
    LeakTracker tracker;
    LeakError worker_track = LeakError::None;
    LeakError worker_release = LeakError::None;
    std::thread worker([&tracker, &worker_track, &worker_release] {
        LeakToken token{};
        worker_track = tracker.track(8, token);
        worker_release = tracker.release(token);
    });
    worker.join();
    expect(worker_track == LeakError::WrongThread, "worker track rejected");
    expect(worker_release == LeakError::WrongThread, "worker release rejected");
    expect(tracker.empty(), "worker calls leave tracker empty");
    expect(tracker.peak_allocations() == 0, "worker calls leave peak zero");
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: %s <basic|invalid|capacity|token|lifetime|wrong_thread>\n",
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
    if (mode == "capacity") {
        return run_capacity() ? 0 : 1;
    }
    if (mode == "token") {
        return run_token() ? 0 : 1;
    }
    if (mode == "lifetime") {
        return run_lifetime() ? 0 : 1;
    }
    if (mode == "wrong_thread") {
        return run_wrong_thread() ? 0 : 1;
    }

    std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return 2;
}
