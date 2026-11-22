#include "stormline/core/time/clock_source.hpp"

#include <chrono>
#include <cstdint>
#include <limits>

namespace stormline::core::time {

SteadyClockSource::SteadyClockSource() noexcept
    : epoch_(std::chrono::steady_clock::now()) {}

ClockSample SteadyClockSource::sample() noexcept {
    const auto now = std::chrono::steady_clock::now();
    if (now < epoch_) {
        return ClockSample{0, TimeError::NonMonotonicSample};
    }
    const auto elapsed = now - epoch_;
    const auto elapsed_seconds =
        std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
    constexpr std::int64_t max_nanoseconds = std::numeric_limits<std::int64_t>::max();
    if (elapsed_seconds > (max_nanoseconds - 999'999'999) / 1'000'000'000) {
        return ClockSample{0, TimeError::DurationOverflow};
    }
    const auto nanoseconds =
        std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    if (nanoseconds < 0) {
        return ClockSample{0, TimeError::NonMonotonicSample};
    }
    const std::int64_t value = static_cast<std::int64_t>(nanoseconds);
    if (has_sample_ && value < last_elapsed_ns_) {
        return ClockSample{0, TimeError::NonMonotonicSample};
    }
    last_elapsed_ns_ = value;
    has_sample_ = true;
    return ClockSample{value, TimeError::None};
}

}  // namespace stormline::core::time
