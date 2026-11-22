#include "stormline/core/time/clock_source.hpp"

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <string_view>
#include <thread>

namespace {

using stormline::core::time::ClockSample;
using stormline::core::time::ClockSource;
using stormline::core::time::DebtPolicy;
using stormline::core::time::Rational;
using stormline::core::time::ReplayScheduleHeader;
using stormline::core::time::SteadyClockSource;
using stormline::core::time::TickId;
using stormline::core::time::TickPlan;
using stormline::core::time::TimeError;
using stormline::core::time::TimelineConfig;
using stormline::core::time::TimelineState;
using stormline::core::time::TimelineStats;

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

class FakeClockSource final : public ClockSource {
public:
    explicit FakeClockSource(ClockSample value) noexcept : value_(value) {}

    ClockSample sample() noexcept override {
        return value_;
    }

private:
    ClockSample value_{};
};

bool run_basic() {
    begin_case();
    SteadyClockSource source;
    const ClockSample first = source.sample();
    expect(first.error == TimeError::None, "basic first sample no error");
    expect(first.elapsed_ns >= 0, "basic first sample non-negative");
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    const ClockSample second = source.sample();
    expect(second.error == TimeError::None, "basic second sample no error");
    expect(second.elapsed_ns >= first.elapsed_ns, "basic monotonic elapsed");
    return finish_case();
}

bool run_injected() {
    begin_case();
    FakeClockSource fake(ClockSample{123456789, TimeError::None});
    const ClockSample sample = fake.sample();
    expect(sample.elapsed_ns == 123456789, "injected exact elapsed");
    expect(sample.error == TimeError::None, "injected no error");
    return finish_case();
}

bool run_errors() {
    begin_case();
    FakeClockSource unavailable(ClockSample{0, TimeError::ClockUnavailable});
    FakeClockSource backward(ClockSample{0, TimeError::NonMonotonicSample});
    FakeClockSource overflow(ClockSample{0, TimeError::DurationOverflow});
    expect(unavailable.sample().error == TimeError::ClockUnavailable, "unavailable error");
    expect(backward.sample().error == TimeError::NonMonotonicSample, "backward error");
    expect(overflow.sample().error == TimeError::DurationOverflow, "overflow error");
    return finish_case();
}

bool run_monotonic() {
    begin_case();
    SteadyClockSource source;
    ClockSample previous = source.sample();
    expect(previous.error == TimeError::None, "monotonic initial sample");
    for (int index = 0; index < 100; ++index) {
        const ClockSample current = source.sample();
        expect(current.error == TimeError::None, "monotonic repeated sample");
        expect(current.elapsed_ns >= previous.elapsed_ns, "monotonic non-decreasing");
        previous = current;
    }
    return finish_case();
}

bool run_defaults() {
    begin_case();
    const TimelineConfig config{};
    expect(config.tick_rate_numerator == 60, "default tick numerator");
    expect(config.tick_rate_denominator == 1, "default tick denominator");
    expect(config.max_catch_up_ticks == 4, "default catch-up");
    expect(config.max_frame_delta_ns == 250'000'000, "default frame clamp");
    expect(config.max_debt_ns == 1'000'000'000, "default debt cap");
    expect(config.time_scale.numerator == 1 && config.time_scale.denominator == 1,
           "default time scale");
    expect(config.debt_policy == DebtPolicy::DropExcess, "default debt policy");
    expect(TickId{}.value == 0, "default tick id");
    expect(Rational{}.numerator == 0 && Rational{}.denominator == 1, "default rational");
    expect(TickPlan{}.fixed_step.numerator == 1 && TickPlan{}.fixed_step.denominator == 60,
           "default fixed step");
    expect(TimelineStats{}.pumps == 0, "default stats");
    expect(ReplayScheduleHeader{}.schema_version == 1, "default replay schema");
    expect(ReplayScheduleHeader{}.initial_tick == 0, "default replay tick");
    expect(TimelineState::Uninitialized != TimelineState::Running, "state enum distinct");
    return finish_case();
}

bool run_lifetime() {
    begin_case();
    {
        SteadyClockSource source;
        expect(source.sample().error == TimeError::None, "lifetime sample");
    }
    {
        FakeClockSource fake(ClockSample{1, TimeError::None});
        expect(fake.sample().elapsed_ns == 1, "lifetime fake");
    }
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core04_clock_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "basic") {
        success = run_basic();
    } else if (mode == "injected") {
        success = run_injected();
    } else if (mode == "errors") {
        success = run_errors();
    } else if (mode == "monotonic") {
        success = run_monotonic();
    } else if (mode == "defaults") {
        success = run_defaults();
    } else if (mode == "lifetime") {
        success = run_lifetime();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
