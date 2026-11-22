#pragma once

#include <cstdint>

namespace stormline::core::time {

enum class TimeError : std::uint8_t {
    None,
    InvalidConfig,
    InvalidTransition,
    WrongThread,
    NotInitialized,
    AlreadyInitialized,
    ClockUnavailable,
    NonMonotonicSample,
    DurationOverflow,
    TickOverflow,
    DebtLimitExceeded,
    ReplayIncompatible,
    InternalFailure
};

enum class TimelineState : std::uint8_t {
    Uninitialized,
    Running,
    Paused,
    Stopped,
    Failed
};

enum class DebtPolicy : std::uint8_t {
    DropExcess,
    Carry
};

struct TickId {
    std::uint64_t value{0};
};

struct Rational {
    std::int64_t numerator{0};
    std::int64_t denominator{1};
};

struct ClockSample {
    std::int64_t elapsed_ns{0};
    TimeError error{TimeError::None};
};

struct TimelineConfig {
    std::uint32_t tick_rate_numerator{60};
    std::uint32_t tick_rate_denominator{1};
    std::uint32_t max_catch_up_ticks{4};
    std::uint64_t max_frame_delta_ns{250'000'000};
    std::uint64_t max_debt_ns{1'000'000'000};
    Rational time_scale{1, 1};
    DebtPolicy debt_policy{DebtPolicy::DropExcess};
};

struct TickPlan {
    std::uint32_t tick_count{0};
    TickId first_tick{};
    Rational fixed_step{1, 60};
    double interpolation_alpha{0.0};
    std::uint64_t dropped_ns{0};
    bool clamped{false};
};

struct TimelineStats {
    std::uint64_t pumps{0};
    std::uint64_t ticks_emitted{0};
    std::uint64_t dropped_ns{0};
    std::uint64_t debt_ns{0};
    std::uint64_t clock_errors{0};
    std::uint64_t rejected_pumps{0};
    double last_alpha{0.0};
};

struct ReplayScheduleHeader {
    std::uint32_t schema_version{1};
    std::uint32_t tick_rate_numerator{60};
    std::uint32_t tick_rate_denominator{1};
    std::uint64_t initial_tick{0};
    std::uint64_t build_fingerprint{0};
};

}  // namespace stormline::core::time
