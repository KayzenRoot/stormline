#ifndef STORMLINE_CORE_DIAG_COUNTER_HPP
#define STORMLINE_CORE_DIAG_COUNTER_HPP

#include "stormline/core/diag/diagnostics_types.hpp"

#include <array>
#include <cmath>

namespace stormline::core::diag {

enum class CounterUnit : u8 {
    Count,
    Nanoseconds,
    Bytes,
    Percent,
    Custom
};

struct CounterSample {
    u32 schema_version{kDiagnosticsSchemaVersion};
    BuildId build{};
    DiagnosticTime time{};
    u32 counter_id{0};
    CounterUnit unit{CounterUnit::Count};
    f64 value{0.0};
};

[[nodiscard]] inline DiagnosticError make_counter_sample(
    BuildId build, DiagnosticTime time, u32 counter_id, CounterUnit unit,
    f64 value, CounterSample& out) noexcept {
    if (!valid(build) || time.monotonic_ns < 0 || counter_id == 0
        || !std::isfinite(value)) {
        return DiagnosticError::InvalidArgument;
    }
    CounterSample sample{};
    sample.build = build;
    sample.time = time;
    sample.counter_id = counter_id;
    sample.unit = unit;
    sample.value = value;
    out = sample;
    return DiagnosticError::None;
}

class CounterSet final {
public:
    CounterSet() noexcept = default;

    [[nodiscard]] DiagnosticError record(const CounterSample& sample) noexcept {
        if (!valid(sample.build) || sample.time.monotonic_ns < 0
            || sample.counter_id == 0 || !std::isfinite(sample.value)) {
            return DiagnosticError::InvalidArgument;
        }
        for (u32 index = 0; index < size_; ++index) {
            if (samples_[index].counter_id == sample.counter_id) {
                samples_[index] = sample;
                return DiagnosticError::None;
            }
        }
        if (size_ >= kCounterCapacity) {
            ++dropped_;
            return DiagnosticError::BufferFull;
        }
        samples_[size_] = sample;
        ++size_;
        return DiagnosticError::None;
    }

    [[nodiscard]] bool find(u32 counter_id, CounterSample& out) const noexcept {
        for (u32 index = 0; index < size_; ++index) {
            if (samples_[index].counter_id == counter_id) {
                out = samples_[index];
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] u32 size() const noexcept {
        return size_;
    }

    [[nodiscard]] u64 dropped() const noexcept {
        return dropped_;
    }

private:
    std::array<CounterSample, kCounterCapacity> samples_{};
    u32 size_{0};
    u64 dropped_{0};
};

}  // namespace stormline::core::diag

#endif  // STORMLINE_CORE_DIAG_COUNTER_HPP
