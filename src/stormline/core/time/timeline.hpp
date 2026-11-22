#pragma once

#include "stormline/core/time/clock_source.hpp"

#include <memory>

namespace stormline::core::time {

class Timeline final {
public:
    Timeline() noexcept;
    ~Timeline() noexcept;

    Timeline(const Timeline&) = delete;
    Timeline& operator=(const Timeline&) = delete;
    Timeline(Timeline&&) = delete;
    Timeline& operator=(Timeline&&) = delete;

    [[nodiscard]] TimeError start(ClockSource* source, TimelineConfig config) noexcept;
    [[nodiscard]] TimeError pump(TickPlan& plan) noexcept;
    [[nodiscard]] TimeError pump_elapsed(std::int64_t elapsed_ns, TickPlan& plan) noexcept;
    [[nodiscard]] TimeError pause() noexcept;
    [[nodiscard]] TimeError resume() noexcept;
    [[nodiscard]] TimeError step_once(TickPlan& plan) noexcept;
    [[nodiscard]] TimeError stop() noexcept;
    [[nodiscard]] TimelineState state() const noexcept;
    [[nodiscard]] TimelineStats stats() const noexcept;
    [[nodiscard]] TickId current_tick() const noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}  // namespace stormline::core::time
