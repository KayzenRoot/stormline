#include "stormline/core/time/timeline.hpp"

#include <array>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <limits>
#include <string_view>
#include <vector>

namespace {

using stormline::core::time::ClockSample;
using stormline::core::time::ClockSource;
using stormline::core::time::DebtPolicy;
using stormline::core::time::Rational;
using stormline::core::time::ReplayScheduleHeader;
using stormline::core::time::replay_schedule_compatible;
using stormline::core::time::TickId;
using stormline::core::time::TickPlan;
using stormline::core::time::TimeError;
using stormline::core::time::Timeline;
using stormline::core::time::TimelineConfig;
using stormline::core::time::TimelineState;

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
    ClockSample sample() noexcept override {
        return sample_;
    }

    void set(std::int64_t elapsed_ns) noexcept {
        sample_ = ClockSample{elapsed_ns, TimeError::None};
    }

    void set_error(TimeError error) noexcept {
        sample_ = ClockSample{0, error};
    }

private:
    ClockSample sample_{};
};

TimelineConfig config(std::uint32_t rate, std::uint32_t catchup = 64) {
    TimelineConfig value;
    value.tick_rate_numerator = rate;
    value.tick_rate_denominator = 1;
    value.max_catch_up_ticks = catchup;
    value.max_frame_delta_ns = 1'000'000'000;
    value.max_debt_ns = 1'000'000'000;
    value.time_scale = Rational{1, 1};
    value.debt_policy = DebtPolicy::DropExcess;
    return value;
}

bool pump_partition(Timeline& timeline, std::uint32_t fps, std::uint64_t total_ns,
                    std::uint64_t& ticks) {
    const std::uint64_t frames = static_cast<std::uint64_t>(fps) * (total_ns / 1'000'000'000U);
    if (frames == 0) {
        return false;
    }
    const std::uint64_t base = total_ns / frames;
    const std::uint64_t remainder = total_ns % frames;
    for (std::uint64_t frame = 0; frame < frames; ++frame) {
        TickPlan plan;
        const auto elapsed = static_cast<std::int64_t>(base + (frame < remainder ? 1U : 0U));
        if (timeline.pump_elapsed(elapsed, plan) != TimeError::None) {
            return false;
        }
        ticks += plan.tick_count;
    }
    return true;
}

bool run_integrated() {
    begin_case();
    FakeClockSource fake_a;
    Timeline a;
    expect(a.start(&fake_a, config(60)) == TimeError::None, "qlf01 start a");
    std::uint64_t ticks = 0;
    expect(pump_partition(a, 30, 10'000'000'000ULL, ticks), "qlf01 pump a");
    expect(ticks == 600U, "qlf01 600 ticks");
    expect(a.pause() == TimeError::None, "qlf01 pause a");
    TickPlan plan;
    expect(a.step_once(plan) == TimeError::None, "qlf01 step a");
    expect(plan.tick_count == 1U, "qlf01 step one");
    expect(a.resume() == TimeError::None, "qlf01 resume a");
    expect(a.pump_elapsed(100'000'000, plan) == TimeError::None, "qlf01 resume pump");
    expect(plan.tick_count == 6U, "qlf01 resume six");
    expect(a.current_tick().value == 607U, "qlf01 total a");

    FakeClockSource fake_b;
    Timeline b;
    TimelineConfig scaled = config(120);
    scaled.time_scale = Rational{2, 1};
    expect(b.start(&fake_b, scaled) == TimeError::None, "qlf01 start b");
    ticks = 0;
    expect(pump_partition(b, 144, 10'000'000'000ULL, ticks), "qlf01 pump b");
    expect(ticks == 2400U, "qlf01 scaled 2400 ticks");

    const ReplayScheduleHeader header{1, 60, 1, 0, 99};
    expect(replay_schedule_compatible(header, config(60), TickId{0}, 99) == TimeError::None,
           "qlf01 replay exact");
    expect(replay_schedule_compatible(header, config(120), TickId{0}, 99)
               == TimeError::ReplayIncompatible,
           "qlf01 replay rate mismatch");
    expect(a.stop() == TimeError::None, "qlf01 stop a");
    expect(b.stop() == TimeError::None, "qlf01 stop b");
    return finish_case();
}

bool run_stress() {
    begin_case();
    constexpr std::uint32_t runs = 5;
    for (std::uint32_t run = 0; run < runs; ++run) {
        FakeClockSource fake;
        Timeline timeline;
        expect(timeline.start(&fake, config(60)) == TimeError::None, "qlf02 start");
        std::uint64_t ticks = 0;
        bool ok = true;
        for (std::uint32_t second = 0; second < 86'400; ++second) {
            TickPlan plan;
            if (timeline.pump_elapsed(1'000'000'000, plan) != TimeError::None) {
                ok = false;
                break;
            }
            ticks += plan.tick_count;
        }
        expect(ok, "qlf02 pump");
        expect(ticks == 5'184'000U, "qlf02 24h ticks");
        expect(timeline.stop() == TimeError::None, "qlf02 stop");
    }
    return finish_case();
}

bool run_recovery() {
    begin_case();
    FakeClockSource clock;
    Timeline timeline;
    expect(timeline.start(&clock, config(60)) == TimeError::None, "qlf03 start");
    clock.set_error(TimeError::ClockUnavailable);
    TickPlan plan;
    expect(timeline.pump(plan) == TimeError::ClockUnavailable, "qlf03 clock error");
    expect(timeline.state() == TimelineState::Failed, "qlf03 failed state");
    expect(timeline.stop() == TimeError::None, "qlf03 stop failed");

    Timeline fresh;
    expect(fresh.start(&clock, config(60)) == TimeError::None, "qlf03 fresh start");
    expect(fresh.stop() == TimeError::None, "qlf03 fresh stop");

    TimelineConfig invalid = config(60);
    invalid.max_catch_up_ticks = 0;
    Timeline invalid_timeline;
    expect(invalid_timeline.start(&clock, invalid) == TimeError::InvalidConfig,
           "qlf03 invalid config");

    TimelineConfig carry = config(60, 2);
    carry.max_debt_ns = 50'000'000;
    carry.debt_policy = DebtPolicy::Carry;
    Timeline debt;
    expect(debt.start(&clock, carry) == TimeError::None, "qlf03 debt start");
    expect(debt.pump_elapsed(500'000'000, plan) == TimeError::DebtLimitExceeded,
           "qlf03 debt limit");
    expect(debt.state() == TimelineState::Running, "qlf03 debt running");
    expect(debt.stop() == TimeError::None, "qlf03 debt stop");

    Timeline overflow;
    expect(overflow.start_at(&clock, config(60),
                             TickId{std::numeric_limits<std::uint64_t>::max() - 1U})
               == TimeError::None,
           "qlf03 overflow start");
    expect(overflow.pause() == TimeError::None, "qlf03 overflow pause");
    expect(overflow.step_once(plan) == TimeError::None, "qlf03 overflow step");
    expect(overflow.step_once(plan) == TimeError::TickOverflow, "qlf03 overflow guard");
    expect(overflow.stop() == TimeError::None, "qlf03 overflow stop");

    const ReplayScheduleHeader header{1, 60, 1, 0, 1};
    expect(replay_schedule_compatible(header, config(60), TickId{0}, 2)
               == TimeError::ReplayIncompatible,
           "qlf03 replay mismatch");
    return finish_case();
}

bool run_overload() {
    begin_case();
    FakeClockSource clock;
    Timeline drop;
    TimelineConfig drop_config = config(60, 4);
    expect(drop.start(&clock, drop_config) == TimeError::None, "qlf04 drop start");
    TickPlan plan;
    expect(drop.pump_elapsed(250'000'000, plan) == TimeError::None, "qlf04 drop pump");
    expect(plan.tick_count == 4U, "qlf04 drop cap");
    expect(plan.dropped_ns > 0U, "qlf04 drop recorded");
    expect(drop.stop() == TimeError::None, "qlf04 drop stop");

    Timeline carry;
    TimelineConfig carry_config = config(60, 2);
    carry_config.debt_policy = DebtPolicy::Carry;
    carry_config.max_debt_ns = 100'000'000;
    expect(carry.start(&clock, carry_config) == TimeError::None, "qlf04 carry start");
    expect(carry.pump_elapsed(100'000'000, plan) == TimeError::None, "qlf04 carry pump");
    expect(plan.tick_count == 2U, "qlf04 carry cap");
    expect(carry.stats().debt_ns > 0U, "qlf04 carry debt");
    expect(carry.stop() == TimeError::None, "qlf04 carry stop");

    Timeline clamp;
    TimelineConfig clamp_config = config(60);
    clamp_config.max_frame_delta_ns = 100'000'000;
    expect(clamp.start(&clock, clamp_config) == TimeError::None, "qlf04 clamp start");
    expect(clamp.pump_elapsed(250'000'000, plan) == TimeError::None, "qlf04 clamp pump");
    expect(plan.clamped, "qlf04 clamped");
    expect(plan.tick_count == 6U, "qlf04 clamp six");
    expect(clamp.stop() == TimeError::None, "qlf04 clamp stop");
    return finish_case();
}

bool run_benchmark() {
    begin_case();
    FakeClockSource clock;
    Timeline timeline;
    expect(timeline.start(&clock, config(60)) == TimeError::None, "qlf05 start");
    constexpr std::uint64_t target_ticks = 1'000'000;
    constexpr std::uint64_t chunk_ns = 1'000'000'000;
    const auto start = std::chrono::steady_clock::now();
    std::uint64_t ticks = 0;
    TickPlan plan;
    while (ticks < target_ticks) {
        expect(timeline.pump_elapsed(static_cast<std::int64_t>(chunk_ns), plan)
                   == TimeError::None,
               "qlf05 pump");
        ticks += plan.tick_count;
    }
    const auto end = std::chrono::steady_clock::now();
    const auto elapsed_ns = static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    const double seconds = static_cast<double>(elapsed_ns) / 1000000000.0;
    const double ticks_per_second = seconds > 0.0 ? static_cast<double>(ticks) / seconds : 0.0;
    std::printf("QLF05_BENCH ticks=%llu elapsed_ns=%llu ticks_per_second=%.2f\n",
                static_cast<unsigned long long>(ticks),
                static_cast<unsigned long long>(elapsed_ns), ticks_per_second);
    expect(ticks >= target_ticks, "qlf05 target reached");
    expect(timeline.stop() == TimeError::None, "qlf05 stop");
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core04_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlf01") {
        success = run_integrated();
    } else if (mode == "qlf02") {
        success = run_stress();
    } else if (mode == "qlf03") {
        success = run_recovery();
    } else if (mode == "qlf04") {
        success = run_overload();
    } else if (mode == "qlf05") {
        success = run_benchmark();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
