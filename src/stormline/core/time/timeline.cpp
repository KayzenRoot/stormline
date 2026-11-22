#include "stormline/core/time/timeline.hpp"

#include <chrono>
#include <cstdint>
#include <limits>
#include <memory>
#include <mutex>
#include <new>
#include <thread>

namespace stormline::core::time {
namespace {

constexpr std::int64_t nanoseconds_per_second = 1'000'000'000;
constexpr std::uint32_t max_catch_up_limit = 64;
constexpr std::uint32_t max_rate_component = 1'000'000;

bool checked_mul(std::int64_t left, std::int64_t right, std::int64_t& result) noexcept {
    if (left == 0 || right == 0) {
        result = 0;
        return true;
    }
    constexpr std::int64_t maximum = std::numeric_limits<std::int64_t>::max();
    if (left > 0 && right > 0 && left > maximum / right) {
        return false;
    }
    if (left < 0 || right < 0) {
        return false;
    }
    result = left * right;
    return true;
}

bool validate_config(const TimelineConfig& config) noexcept {
    if (config.tick_rate_numerator == 0 || config.tick_rate_denominator == 0
        || config.tick_rate_numerator > max_rate_component
        || config.tick_rate_denominator > max_rate_component
        || config.max_catch_up_ticks == 0 || config.max_catch_up_ticks > max_catch_up_limit
        || config.max_frame_delta_ns == 0 || config.max_debt_ns == 0
        || config.max_frame_delta_ns > static_cast<std::uint64_t>(
               std::numeric_limits<std::int64_t>::max())
        || config.time_scale.numerator <= 0 || config.time_scale.denominator <= 0
        || config.time_scale.numerator > max_rate_component
        || config.time_scale.denominator > max_rate_component) {
        return false;
    }
    if (config.tick_rate_denominator > static_cast<std::uint32_t>(
            std::numeric_limits<std::int64_t>::max() / nanoseconds_per_second)) {
        return false;
    }
    const std::int64_t tick_denominator =
        static_cast<std::int64_t>(config.tick_rate_denominator) * nanoseconds_per_second;
    const std::int64_t max_frame = static_cast<std::int64_t>(config.max_frame_delta_ns);
    std::int64_t scaled_max = 0;
    if (!checked_mul(max_frame, config.time_scale.numerator, scaled_max)) {
        return false;
    }
    const std::int64_t remaining =
        std::numeric_limits<std::int64_t>::max() - tick_denominator;
    if (scaled_max > remaining / static_cast<std::int64_t>(config.tick_rate_numerator)) {
        return false;
    }
    return true;
}

bool tick_duration_ns(std::int64_t ticks, std::int64_t tick_denominator,
                      std::uint32_t tick_numerator, std::uint64_t& result) noexcept {
    std::int64_t product = 0;
    if (!checked_mul(ticks, tick_denominator, product)) {
        return false;
    }
    const std::int64_t duration = product / static_cast<std::int64_t>(tick_numerator);
    if (duration < 0) {
        return false;
    }
    result = static_cast<std::uint64_t>(duration);
    return true;
}

}  // namespace

struct Timeline::Impl {
    mutable std::mutex mutex;
    ClockSource* source{nullptr};
    TimelineConfig config{};
    TimelineState state{TimelineState::Uninitialized};
    std::thread::id owner{};
    TickId next_tick{};
    std::int64_t tick_denominator{nanoseconds_per_second};
    std::int64_t tick_remainder{0};
    std::int64_t scale_remainder{0};
    std::int64_t last_sample_ns{0};
    bool has_sample{false};
    bool discard_next_sample{false};
    TimelineStats stats{};

    TimeError pump_delta_locked(std::int64_t elapsed_ns, TickPlan& plan) noexcept;
    void reset_counters() noexcept;
};

void Timeline::Impl::reset_counters() noexcept {
    next_tick = TickId{};
    tick_remainder = 0;
    scale_remainder = 0;
    last_sample_ns = 0;
    has_sample = false;
    discard_next_sample = false;
    stats = TimelineStats{};
}

TimeError Timeline::Impl::pump_delta_locked(std::int64_t elapsed_ns, TickPlan& plan) noexcept {
    plan = TickPlan{};
    plan.first_tick = next_tick;
    plan.fixed_step = Rational{static_cast<std::int64_t>(config.tick_rate_denominator),
                               static_cast<std::int64_t>(config.tick_rate_numerator)};

    if (elapsed_ns < 0) {
        ++stats.rejected_pumps;
        return TimeError::NonMonotonicSample;
    }
    if (state == TimelineState::Paused) {
        ++stats.pumps;
        plan.interpolation_alpha =
            static_cast<double>(tick_remainder) / static_cast<double>(tick_denominator);
        stats.last_alpha = plan.interpolation_alpha;
        return TimeError::None;
    }
    if (state != TimelineState::Running) {
        ++stats.rejected_pumps;
        return state == TimelineState::Uninitialized ? TimeError::NotInitialized
                                                     : TimeError::InvalidTransition;
    }

    ++stats.pumps;
    const std::int64_t frame_limit = static_cast<std::int64_t>(config.max_frame_delta_ns);
    if (elapsed_ns > frame_limit) {
        elapsed_ns = frame_limit;
        plan.clamped = true;
    }

    std::int64_t scale_product = 0;
    if (!checked_mul(elapsed_ns, config.time_scale.numerator, scale_product)
        || scale_product > std::numeric_limits<std::int64_t>::max() - scale_remainder) {
        ++stats.rejected_pumps;
        return TimeError::DurationOverflow;
    }
    const std::int64_t scaled_total = scale_product + scale_remainder;
    const std::int64_t scaled_ns = scaled_total / config.time_scale.denominator;
    const std::int64_t next_scale_remainder = scaled_total % config.time_scale.denominator;

    std::int64_t tick_product = 0;
    if (!checked_mul(scaled_ns, static_cast<std::int64_t>(config.tick_rate_numerator),
                     tick_product)
        || tick_product > std::numeric_limits<std::int64_t>::max() - tick_remainder) {
        ++stats.rejected_pumps;
        return TimeError::DurationOverflow;
    }
    const std::int64_t tick_total = tick_product + tick_remainder;
    const std::int64_t total_ticks = tick_total / tick_denominator;
    const std::int64_t fractional = tick_total % tick_denominator;

    std::int64_t emitted = total_ticks;
    std::int64_t next_tick_remainder = fractional;
    std::uint64_t dropped_ns = 0;
    std::uint64_t debt_ns = 0;
    if (total_ticks > static_cast<std::int64_t>(config.max_catch_up_ticks)) {
        emitted = static_cast<std::int64_t>(config.max_catch_up_ticks);
        const std::int64_t excess = total_ticks - emitted;
        if (config.debt_policy == DebtPolicy::DropExcess) {
            if (!tick_duration_ns(excess, tick_denominator, config.tick_rate_numerator,
                                  dropped_ns)) {
                ++stats.rejected_pumps;
                return TimeError::DurationOverflow;
            }
            next_tick_remainder = fractional;
        } else {
            if (!tick_duration_ns(excess, tick_denominator, config.tick_rate_numerator,
                                  debt_ns)
                || debt_ns > config.max_debt_ns) {
                ++stats.rejected_pumps;
                return TimeError::DebtLimitExceeded;
            }
            next_tick_remainder = tick_total - emitted * tick_denominator;
        }
    }

    if (emitted < 0
        || next_tick.value > std::numeric_limits<std::uint64_t>::max()
                                 - static_cast<std::uint64_t>(emitted)) {
        ++stats.rejected_pumps;
        return TimeError::TickOverflow;
    }

    tick_remainder = next_tick_remainder;
    scale_remainder = next_scale_remainder;
    plan.first_tick = next_tick;
    plan.tick_count = static_cast<std::uint32_t>(emitted);
    plan.dropped_ns = dropped_ns;
    plan.interpolation_alpha =
        static_cast<double>(fractional) / static_cast<double>(tick_denominator);
    next_tick.value += static_cast<std::uint64_t>(emitted);
    stats.ticks_emitted += static_cast<std::uint64_t>(emitted);
    stats.dropped_ns += dropped_ns;
    stats.debt_ns = debt_ns;
    stats.last_alpha = plan.interpolation_alpha;
    return TimeError::None;
}

Timeline::Timeline() noexcept
    : impl_(new (std::nothrow) Impl()) {}

Timeline::~Timeline() noexcept = default;

TimeError Timeline::start(ClockSource* source, TimelineConfig config) noexcept {
    return start_at(source, config, TickId{0});
}

TimeError Timeline::start_at(ClockSource* source, TimelineConfig config,
                             TickId initial_tick) noexcept {
    if (!impl_) {
        return TimeError::InternalFailure;
    }
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (impl_->state != TimelineState::Uninitialized) {
        return TimeError::AlreadyInitialized;
    }
    if (source == nullptr || !validate_config(config)) {
        return TimeError::InvalidConfig;
    }
    impl_->source = source;
    impl_->config = config;
    impl_->owner = std::this_thread::get_id();
    impl_->tick_denominator =
        static_cast<std::int64_t>(config.tick_rate_denominator) * nanoseconds_per_second;
    impl_->reset_counters();
    impl_->next_tick = initial_tick;
    impl_->state = TimelineState::Running;
    return TimeError::None;
}

TimeError Timeline::pump(TickPlan& plan) noexcept {
    plan = TickPlan{};
    if (!impl_) {
        return TimeError::InternalFailure;
    }
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (impl_->state != TimelineState::Running && impl_->state != TimelineState::Paused) {
        return impl_->state == TimelineState::Uninitialized ? TimeError::NotInitialized
                                                           : TimeError::InvalidTransition;
    }
    if (std::this_thread::get_id() != impl_->owner) {
        return TimeError::WrongThread;
    }
    if (impl_->state == TimelineState::Paused) {
        return impl_->pump_delta_locked(0, plan);
    }

    const ClockSample sample = impl_->source->sample();
    if (sample.error != TimeError::None) {
        ++impl_->stats.clock_errors;
        impl_->state = TimelineState::Failed;
        return sample.error;
    }
    std::int64_t delta = 0;
    if (!impl_->has_sample) {
        impl_->has_sample = true;
        impl_->last_sample_ns = sample.elapsed_ns;
    } else if (impl_->discard_next_sample) {
        impl_->discard_next_sample = false;
        impl_->last_sample_ns = sample.elapsed_ns;
    } else {
        if (sample.elapsed_ns < impl_->last_sample_ns) {
            ++impl_->stats.clock_errors;
            impl_->state = TimelineState::Failed;
            return TimeError::NonMonotonicSample;
        }
        delta = sample.elapsed_ns - impl_->last_sample_ns;
        impl_->last_sample_ns = sample.elapsed_ns;
    }
    return impl_->pump_delta_locked(delta, plan);
}

TimeError Timeline::pump_elapsed(std::int64_t elapsed_ns, TickPlan& plan) noexcept {
    plan = TickPlan{};
    if (!impl_) {
        return TimeError::InternalFailure;
    }
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (impl_->state != TimelineState::Running && impl_->state != TimelineState::Paused) {
        return impl_->state == TimelineState::Uninitialized ? TimeError::NotInitialized
                                                           : TimeError::InvalidTransition;
    }
    if (std::this_thread::get_id() != impl_->owner) {
        return TimeError::WrongThread;
    }
    return impl_->pump_delta_locked(elapsed_ns, plan);
}

TimeError Timeline::pause() noexcept {
    if (!impl_) {
        return TimeError::InternalFailure;
    }
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (std::this_thread::get_id() != impl_->owner) {
        return TimeError::WrongThread;
    }
    if (impl_->state == TimelineState::Paused) {
        return TimeError::None;
    }
    if (impl_->state != TimelineState::Running) {
        return TimeError::InvalidTransition;
    }
    impl_->state = TimelineState::Paused;
    return TimeError::None;
}

TimeError Timeline::resume() noexcept {
    if (!impl_) {
        return TimeError::InternalFailure;
    }
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (std::this_thread::get_id() != impl_->owner) {
        return TimeError::WrongThread;
    }
    if (impl_->state == TimelineState::Running) {
        return TimeError::None;
    }
    if (impl_->state != TimelineState::Paused) {
        return TimeError::InvalidTransition;
    }
    impl_->state = TimelineState::Running;
    impl_->discard_next_sample = true;
    return TimeError::None;
}

TimeError Timeline::step_once(TickPlan& plan) noexcept {
    plan = TickPlan{};
    if (!impl_) {
        return TimeError::InternalFailure;
    }
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (std::this_thread::get_id() != impl_->owner) {
        return TimeError::WrongThread;
    }
    if (impl_->state != TimelineState::Paused) {
        return TimeError::InvalidTransition;
    }
    if (impl_->next_tick.value == std::numeric_limits<std::uint64_t>::max()) {
        return TimeError::TickOverflow;
    }
    plan.tick_count = 1;
    plan.first_tick = impl_->next_tick;
    plan.fixed_step = Rational{static_cast<std::int64_t>(impl_->config.tick_rate_denominator),
                               static_cast<std::int64_t>(impl_->config.tick_rate_numerator)};
    plan.interpolation_alpha =
        static_cast<double>(impl_->tick_remainder) / static_cast<double>(impl_->tick_denominator);
    ++impl_->next_tick.value;
    ++impl_->stats.ticks_emitted;
    impl_->stats.last_alpha = plan.interpolation_alpha;
    return TimeError::None;
}

TimeError Timeline::stop() noexcept {
    if (!impl_) {
        return TimeError::InternalFailure;
    }
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (impl_->state != TimelineState::Uninitialized
        && std::this_thread::get_id() != impl_->owner) {
        return TimeError::WrongThread;
    }
    if (impl_->state == TimelineState::Stopped) {
        return TimeError::None;
    }
    impl_->state = TimelineState::Stopped;
    return TimeError::None;
}

TimelineState Timeline::state() const noexcept {
    if (!impl_) {
        return TimelineState::Failed;
    }
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return impl_->state;
}

TimelineStats Timeline::stats() const noexcept {
    if (!impl_) {
        return TimelineStats{};
    }
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return impl_->stats;
}

TickId Timeline::current_tick() const noexcept {
    if (!impl_) {
        return TickId{};
    }
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return impl_->next_tick;
}

TimeError replay_schedule_compatible(const ReplayScheduleHeader& header,
                                     const TimelineConfig& config,
                                     TickId initial_tick,
                                     std::uint64_t current_build_fingerprint) noexcept {
    if (!validate_config(config)) {
        return TimeError::InvalidConfig;
    }
    if (header.schema_version != 1U
        || header.tick_rate_numerator != config.tick_rate_numerator
        || header.tick_rate_denominator != config.tick_rate_denominator
        || header.initial_tick != initial_tick.value) {
        return TimeError::ReplayIncompatible;
    }
    if (header.build_fingerprint != 0U
        && header.build_fingerprint != current_build_fingerprint) {
        return TimeError::ReplayIncompatible;
    }
    return TimeError::None;
}

}  // namespace stormline::core::time
