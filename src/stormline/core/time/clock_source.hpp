#pragma once

#include "stormline/core/time/time_types.hpp"

#include <chrono>
#include <cstdint>

namespace stormline::core::time {

class ClockSource {
public:
    virtual ~ClockSource() = default;
    virtual ClockSample sample() noexcept = 0;
};

class SteadyClockSource final : public ClockSource {
public:
    SteadyClockSource() noexcept;

    ClockSample sample() noexcept override;

private:
    std::chrono::steady_clock::time_point epoch_{};
    std::int64_t last_elapsed_ns_{0};
    bool has_sample_{false};
};

}  // namespace stormline::core::time
