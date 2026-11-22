#include "stormline/core/time/timeline.hpp"

#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <string_view>
#include <thread>
#include <vector>

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

TimelineConfig base_config() {
    TimelineConfig config;
    config.tick_rate_numerator = 60;
    config.tick_rate_denominator = 1;
    config.max_catch_up_ticks = 64;
    config.max_frame_delta_ns = 1'000'000'000;
    config.max_debt_ns = 1'000'000'000;
    config.time_scale = Rational{1, 1};
    config.debt_policy = DebtPolicy::DropExcess;
    return config;
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

bool pump_partition(Timeline& timeline, std::uint32_t fps, std::uint64_t total_ns,
                    std::uint64_t& ticks, bool& alpha_ok) {
    const std::uint64_t frames = static_cast<std::uint64_t>(fps) * (total_ns / 1'000'000'000U);
    if (frames == 0) {
        return false;
    }
    const std::uint64_t base = total_ns / frames;
    const std::uint64_t remainder = total_ns % frames;
    for (std::uint64_t frame = 0; frame < frames; ++frame) {
        const std::int64_t elapsed = static_cast<std::int64_t>(base + (frame < remainder ? 1U : 0U));
        TickPlan plan;
        if (timeline.pump_elapsed(elapsed, plan) != TimeError::None) {
            return false;
        }
        ticks += plan.tick_count;
        if (!(plan.interpolation_alpha >= 0.0 && plan.interpolation_alpha < 1.0)) {
            alpha_ok = false;
        }
    }
    return true;
}

bool run_fps() {
    begin_case();
    for (const std::uint32_t fps : {30U, 60U, 144U}) {
        SteadyClockSource source;
        Timeline timeline;
        expect(timeline.start(&source, base_config()) == TimeError::None, "fps start");
        std::uint64_t ticks = 0;
        bool alpha_ok = true;
        expect(pump_partition(timeline, fps, 60'000'000'000ULL, ticks, alpha_ok),
               "fps pump");
        expect(ticks == 3600U, "fps exactly 3600 ticks");
        expect(alpha_ok, "fps alpha in range");
        expect(timeline.current_tick().value == 3600U, "fps current tick");
        expect(timeline.stop() == TimeError::None, "fps stop");
    }
    return finish_case();
}

bool run_long_run() {
    begin_case();
    SteadyClockSource source;
    Timeline timeline;
    TimelineConfig config = base_config();
    config.max_catch_up_ticks = 64;
    expect(timeline.start(&source, config) == TimeError::None, "long start");
    std::uint64_t ticks = 0;
    bool alpha_ok = true;
    expect(pump_partition(timeline, 60U, 86'400'000'000'000ULL, ticks, alpha_ok),
           "long pump");
    expect(ticks == 5'184'000U, "24h exactly 5184000 ticks");
    expect(alpha_ok, "24h alpha in range");
    expect(timeline.stop() == TimeError::None, "long stop");
    return finish_case();
}

bool run_pause() {
    begin_case();
    SteadyClockSource source;
    Timeline timeline;
    expect(timeline.start(&source, base_config()) == TimeError::None, "pause start");
    TickPlan plan;
    expect(timeline.pump_elapsed(100'000'000, plan) == TimeError::None, "pause first pump");
    expect(plan.tick_count == 6U, "pause six ticks");
    expect(timeline.pause() == TimeError::None, "pause request");
    expect(timeline.state() == TimelineState::Paused, "paused state");
    expect(timeline.pump_elapsed(1'000'000'000, plan) == TimeError::None, "paused pump");
    expect(plan.tick_count == 0U, "paused no ticks");
    expect(timeline.current_tick().value == 6U, "paused tick unchanged");
    expect(timeline.resume() == TimeError::None, "resume");
    expect(timeline.pump_elapsed(100'000'000, plan) == TimeError::None, "resume pump");
    expect(plan.tick_count == 6U, "resume no burst");
    expect(timeline.current_tick().value == 12U, "resume tick count");

    FakeClockSource fake;
    Timeline sampled;
    expect(sampled.start(&fake, base_config()) == TimeError::None, "sampled start");
    fake.set(0);
    expect(sampled.pump(plan) == TimeError::None, "sampled baseline");
    expect(plan.tick_count == 0U, "sampled baseline zero");
    fake.set(100'000'000);
    expect(sampled.pump(plan) == TimeError::None, "sampled pump");
    expect(plan.tick_count == 6U, "sampled six");
    expect(sampled.pause() == TimeError::None, "sampled pause");
    fake.set(1'000'000'000);
    expect(sampled.pump(plan) == TimeError::None, "sampled paused pump");
    expect(plan.tick_count == 0U, "sampled paused zero");
    expect(sampled.resume() == TimeError::None, "sampled resume");
    fake.set(1'100'000'000);
    expect(sampled.pump(plan) == TimeError::None, "sampled discard pause");
    expect(plan.tick_count == 0U, "sampled no pause burst");
    fake.set(1'200'000'000);
    expect(sampled.pump(plan) == TimeError::None, "sampled after resume");
    expect(plan.tick_count == 6U, "sampled resume six");
    expect(timeline.stop() == TimeError::None, "pause stop");
    expect(sampled.stop() == TimeError::None, "sampled stop");
    return finish_case();
}

bool run_step() {
    begin_case();
    SteadyClockSource source;
    Timeline timeline;
    expect(timeline.start(&source, base_config()) == TimeError::None, "step start");
    expect(timeline.pause() == TimeError::None, "step pause");
    TickPlan plan;
    expect(timeline.step_once(plan) == TimeError::None, "step first");
    expect(plan.tick_count == 1U, "step one tick");
    expect(plan.first_tick.value == 0U, "step first id");
    expect(timeline.state() == TimelineState::Paused, "step stays paused");
    expect(timeline.step_once(plan) == TimeError::None, "step second");
    expect(plan.first_tick.value == 1U, "step second id");
    expect(timeline.current_tick().value == 2U, "step tick count");
    expect(timeline.resume() == TimeError::None, "step resume");
    expect(timeline.pump_elapsed(100'000'000, plan) == TimeError::None, "step pump");
    expect(plan.tick_count == 6U, "step pump ticks");
    expect(timeline.current_tick().value == 8U, "step final tick");
    expect(timeline.stop() == TimeError::None, "step stop");
    return finish_case();
}

bool run_drop() {
    begin_case();
    SteadyClockSource source;
    TimelineConfig config = base_config();
    config.max_catch_up_ticks = 4;
    config.max_frame_delta_ns = 1'000'000'000;
    Timeline timeline;
    expect(timeline.start(&source, config) == TimeError::None, "drop start");
    TickPlan plan;
    expect(timeline.pump_elapsed(250'000'000, plan) == TimeError::None, "drop pump");
    expect(plan.tick_count == 4U, "drop capped at four");
    expect(plan.dropped_ns > 0U, "drop recorded");
    expect(timeline.current_tick().value == 4U, "drop current");
    const auto stats = timeline.stats();
    expect(stats.dropped_ns == plan.dropped_ns, "drop stats");
    expect(timeline.stop() == TimeError::None, "drop stop");
    return finish_case();
}

bool run_carry() {
    begin_case();
    SteadyClockSource source;
    TimelineConfig config = base_config();
    config.max_catch_up_ticks = 2;
    config.max_frame_delta_ns = 1'000'000'000;
    config.max_debt_ns = 100'000'000;
    config.debt_policy = DebtPolicy::Carry;
    Timeline timeline;
    expect(timeline.start(&source, config) == TimeError::None, "carry start");
    TickPlan plan;
    expect(timeline.pump_elapsed(100'000'000, plan) == TimeError::None, "carry pump one");
    expect(plan.tick_count == 2U, "carry emits two");
    expect(timeline.stats().debt_ns > 0U, "carry debt recorded");
    expect(timeline.pump_elapsed(0, plan) == TimeError::None, "carry pump two");
    expect(plan.tick_count == 2U, "carry emits two more");
    expect(timeline.pump_elapsed(0, plan) == TimeError::None, "carry pump three");
    expect(plan.tick_count == 2U, "carry drains debt");
    expect(timeline.pump_elapsed(500'000'000, plan) == TimeError::DebtLimitExceeded,
           "carry limit");
    expect(plan.tick_count == 0U, "carry limit zero plan");
    expect(timeline.state() == TimelineState::Running, "carry remains running");
    expect(timeline.stop() == TimeError::None, "carry stop");
    return finish_case();
}

bool run_scale() {
    begin_case();
    SteadyClockSource source;
    TimelineConfig config = base_config();
    config.max_catch_up_ticks = 64;
    config.max_frame_delta_ns = 1'000'000'000;
    config.time_scale = Rational{2, 1};
    Timeline doubled;
    expect(doubled.start(&source, config) == TimeError::None, "scale double start");
    TickPlan plan;
    expect(doubled.pump_elapsed(500'000'000, plan) == TimeError::None, "scale double pump 1");
    expect(plan.tick_count == 60U, "scale double sixty");
    expect(doubled.pump_elapsed(500'000'000, plan) == TimeError::None, "scale double pump 2");
    expect(plan.tick_count == 60U, "scale double second sixty");
    expect(doubled.stop() == TimeError::None, "scale double stop");

    TimelineConfig half = base_config();
    half.max_frame_delta_ns = 1'000'000'000;
    half.time_scale = Rational{1, 2};
    Timeline halved;
    expect(halved.start(&source, half) == TimeError::None, "scale half start");
    expect(halved.pump_elapsed(1'000'000'000, plan) == TimeError::None, "scale half pump");
    expect(plan.tick_count == 30U, "scale half thirty");
    expect(halved.stop() == TimeError::None, "scale half stop");
    return finish_case();
}

bool run_overflow() {
    begin_case();
    SteadyClockSource source;
    Timeline timeline;
    TimelineConfig invalid = base_config();
    invalid.max_frame_delta_ns = 0;
    expect(timeline.start(&source, invalid) == TimeError::InvalidConfig, "overflow zero frame");
    invalid = base_config();
    invalid.max_catch_up_ticks = 0;
    expect(timeline.start(&source, invalid) == TimeError::InvalidConfig, "overflow zero catchup");
    invalid = base_config();
    invalid.max_catch_up_ticks = 65;
    expect(timeline.start(&source, invalid) == TimeError::InvalidConfig, "overflow big catchup");
    invalid = base_config();
    invalid.time_scale = Rational{0, 1};
    expect(timeline.start(&source, invalid) == TimeError::InvalidConfig, "overflow zero scale");
    expect(timeline.start(nullptr, base_config()) == TimeError::InvalidConfig, "overflow null");
    expect(timeline.start(&source, base_config()) == TimeError::None, "overflow start");
    expect(timeline.start(&source, base_config()) == TimeError::AlreadyInitialized,
           "overflow second start");
    TickPlan plan;
    expect(timeline.pump_elapsed(-1, plan) == TimeError::NonMonotonicSample,
           "overflow negative delta");
    expect(timeline.state() == TimelineState::Running, "overflow state");
    expect(timeline.stop() == TimeError::None, "overflow stop");
    return finish_case();
}

bool run_lifecycle() {
    begin_case();
    SteadyClockSource source;
    {
        Timeline timeline;
        expect(timeline.state() == TimelineState::Uninitialized, "lifecycle initial");
        expect(timeline.stop() == TimeError::None, "lifecycle stop uninitialized");
        expect(timeline.state() == TimelineState::Stopped, "lifecycle stopped");
        expect(timeline.start(&source, base_config()) == TimeError::AlreadyInitialized,
               "lifecycle restart rejected");
    }
    Timeline timeline;
    expect(timeline.start(&source, base_config()) == TimeError::None, "lifecycle start");
    TimeError wrong = TimeError::None;
    std::thread outsider([&]() {
        TickPlan remote;
        wrong = timeline.pump_elapsed(0, remote);
    });
    outsider.join();
    expect(wrong == TimeError::WrongThread, "lifecycle wrong thread pump");
    expect(timeline.stop() == TimeError::None, "lifecycle stop");
    expect(timeline.stop() == TimeError::None, "lifecycle stop idempotent");
    TickPlan plan;
    expect(timeline.pump_elapsed(0, plan) == TimeError::InvalidTransition,
           "lifecycle pump after stop");
    wrong = TimeError::None;
    std::thread pause_thread([&]() { wrong = timeline.pause(); });
    pause_thread.join();
    expect(wrong == TimeError::WrongThread, "lifecycle wrong thread pause");
    return finish_case();
}

bool run_determinism() {
    begin_case();
    SteadyClockSource source_a;
    SteadyClockSource source_b;
    Timeline a;
    Timeline b;
    expect(a.start(&source_a, base_config()) == TimeError::None, "determinism start a");
    expect(b.start(&source_b, base_config()) == TimeError::None, "determinism start b");
    std::uint64_t ticks_a = 0;
    std::uint64_t ticks_b = 0;
    bool alpha_a = true;
    bool alpha_b = true;
    expect(pump_partition(a, 30U, 10'000'000'000ULL, ticks_a, alpha_a), "determinism a");
    expect(pump_partition(b, 144U, 10'000'000'000ULL, ticks_b, alpha_b), "determinism b");
    expect(ticks_a == ticks_b, "determinism tick count");
    expect(ticks_a == 600U, "determinism 600 ticks");
    expect(alpha_a && alpha_b, "determinism alpha");
    const ReplayScheduleHeader header{1, 60, 1, 0, 0};
    expect(header.schema_version == 1 && header.tick_rate_numerator == 60, "replay header");
    expect(a.stop() == TimeError::None, "determinism stop a");
    expect(b.stop() == TimeError::None, "determinism stop b");
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core04_timeline_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "fps") {
        success = run_fps();
    } else if (mode == "long_run") {
        success = run_long_run();
    } else if (mode == "pause") {
        success = run_pause();
    } else if (mode == "step") {
        success = run_step();
    } else if (mode == "drop") {
        success = run_drop();
    } else if (mode == "carry") {
        success = run_carry();
    } else if (mode == "scale") {
        success = run_scale();
    } else if (mode == "overflow") {
        success = run_overflow();
    } else if (mode == "lifecycle") {
        success = run_lifecycle();
    } else if (mode == "determinism") {
        success = run_determinism();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
