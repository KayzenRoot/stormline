#ifndef STORMLINE_CORE_DIAG_TELEMETRY_HPP
#define STORMLINE_CORE_DIAG_TELEMETRY_HPP

#include "stormline/core/diag/diagnostics_types.hpp"

#include <array>
#include <cmath>
#include <string_view>

namespace stormline::core::diag {

struct TelemetryPolicy {
    bool enabled{false};
    bool local_only{true};
};

struct TelemetryEvent {
    u32 schema_version{kDiagnosticsSchemaVersion};
    BuildId build{};
    DiagnosticTime time{};
    u32 event_id{0};
    f64 value{0.0};
    BoundedText<kMaxNameBytes> name{};
};

[[nodiscard]] inline DiagnosticError make_telemetry_event(
    BuildId build, DiagnosticTime time, u32 event_id, f64 value,
    std::string_view name, TelemetryEvent& out) noexcept {
    if (!valid(build) || time.monotonic_ns < 0 || event_id == 0
        || !std::isfinite(value)) {
        return DiagnosticError::InvalidArgument;
    }
    TelemetryEvent event{};
    event.build = build;
    event.time = time;
    event.event_id = event_id;
    event.value = value;
    const DiagnosticError error = assign_text(event.name, name);
    if (error != DiagnosticError::None) {
        return error;
    }
    out = event;
    return DiagnosticError::None;
}

class TelemetryBuffer final {
public:
    explicit TelemetryBuffer(TelemetryPolicy policy = {}) noexcept
        : policy_(policy) {}

    [[nodiscard]] DiagnosticError set_enabled(bool enabled) noexcept {
        if (enabled && !policy_.local_only) {
            return DiagnosticError::Unsupported;
        }
        policy_.enabled = enabled;
        return DiagnosticError::None;
    }

    [[nodiscard]] bool enabled() const noexcept {
        return policy_.enabled;
    }

    [[nodiscard]] DiagnosticError record(const TelemetryEvent& event) noexcept {
        if (!policy_.enabled) {
            return DiagnosticError::NotEnabled;
        }
        if (!valid(event.build) || event.time.monotonic_ns < 0
            || event.event_id == 0 || !std::isfinite(event.value)
            || event.name.length > kMaxNameBytes) {
            return DiagnosticError::InvalidArgument;
        }
        if (size_ >= kTelemetryCapacity) {
            ++dropped_;
            return DiagnosticError::BufferFull;
        }
        events_[size_] = event;
        ++size_;
        return DiagnosticError::None;
    }

    [[nodiscard]] u32 size() const noexcept {
        return size_;
    }

    [[nodiscard]] u64 dropped() const noexcept {
        return dropped_;
    }

private:
    std::array<TelemetryEvent, kTelemetryCapacity> events_{};
    TelemetryPolicy policy_{};
    u32 size_{0};
    u64 dropped_{0};
};

}  // namespace stormline::core::diag

#endif  // STORMLINE_CORE_DIAG_TELEMETRY_HPP
