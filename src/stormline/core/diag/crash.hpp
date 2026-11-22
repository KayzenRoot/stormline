#ifndef STORMLINE_CORE_DIAG_CRASH_HPP
#define STORMLINE_CORE_DIAG_CRASH_HPP

#include "stormline/core/diag/log.hpp"

#include <array>

namespace stormline::core::diag {

struct CrashEnvelope {
    u32 schema_version{kDiagnosticsSchemaVersion};
    BuildId build{};
    SessionId session{};
    u32 platform_tag{0};
    DiagnosticTime time{};
    DiagnosticReason reason{DiagnosticReason::CrashUnhandled};
    u32 preceding_count{0};
    std::array<LogRecord, kCrashPrecedingRecords> preceding{};
};

[[nodiscard]] inline DiagnosticError make_crash_envelope(
    BuildId build, SessionId session, u32 platform_tag, DiagnosticTime time,
    DiagnosticReason reason, const LogRecord* preceding, u32 count,
    CrashEnvelope& out) noexcept {
    if (!valid(build) || !valid(session) || time.monotonic_ns < 0
        || count > kCrashPrecedingRecords
        || (count != 0 && preceding == nullptr)) {
        return DiagnosticError::InvalidArgument;
    }
    CrashEnvelope envelope{};
    envelope.build = build;
    envelope.session = session;
    envelope.platform_tag = platform_tag;
    envelope.time = time;
    envelope.reason = reason;
    for (u32 index = 0; index < count; ++index) {
        envelope.preceding[index] = preceding[index];
    }
    envelope.preceding_count = count;
    out = envelope;
    return DiagnosticError::None;
}

}  // namespace stormline::core::diag

#endif  // STORMLINE_CORE_DIAG_CRASH_HPP
