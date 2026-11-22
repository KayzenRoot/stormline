#ifndef STORMLINE_CORE_DIAG_TRACE_HPP
#define STORMLINE_CORE_DIAG_TRACE_HPP

#include "stormline/core/diag/diagnostics_types.hpp"

#include <array>
#include <string_view>

namespace stormline::core::diag {

struct SpanRecord {
    u32 schema_version{kDiagnosticsSchemaVersion};
    BuildId build{};
    TraceId trace{};
    SpanId span{};
    SpanId parent{};
    u64 producer_sequence{0};
    DiagnosticTime start{};
    DiagnosticTime end{};
    u32 subsystem{0};
    DiagnosticReason outcome{DiagnosticReason::None};
    BoundedText<kMaxNameBytes> name{};
    bool completed{false};
};

[[nodiscard]] inline DiagnosticError make_span(
    BuildId build, TraceId trace, SpanId span, SpanId parent,
    u64 producer_sequence, DiagnosticTime start, u32 subsystem,
    std::string_view name, SpanRecord& out) noexcept {
    if (!valid(build) || !valid(trace) || !valid(span)
        || start.monotonic_ns < 0) {
        return DiagnosticError::InvalidArgument;
    }
    if (parent.value != 0 && parent.value == span.value) {
        return DiagnosticError::InvalidArgument;
    }
    SpanRecord record{};
    record.build = build;
    record.trace = trace;
    record.span = span;
    record.parent = parent;
    record.producer_sequence = producer_sequence;
    record.start = start;
    record.subsystem = subsystem;
    const DiagnosticError error = assign_text(record.name, name);
    if (error != DiagnosticError::None) {
        return error;
    }
    out = record;
    return DiagnosticError::None;
}

[[nodiscard]] inline DiagnosticError complete_span(
    SpanRecord& span, DiagnosticTime end, DiagnosticReason outcome) noexcept {
    if (span.completed || end.monotonic_ns < span.start.monotonic_ns) {
        return DiagnosticError::InvalidArgument;
    }
    span.end = end;
    span.outcome = outcome;
    span.completed = true;
    return DiagnosticError::None;
}

class TraceBuffer final {
public:
    TraceBuffer() noexcept = default;

    [[nodiscard]] DiagnosticError accept(const SpanRecord& span) noexcept {
        if (!span.completed) {
            return DiagnosticError::InvalidArgument;
        }
        if (size_ >= kTraceBufferCapacity) {
            ++dropped_;
            return DiagnosticError::BufferFull;
        }
        spans_[size_] = span;
        ++size_;
        return DiagnosticError::None;
    }

    [[nodiscard]] u32 size() const noexcept {
        return size_;
    }

    [[nodiscard]] u64 dropped() const noexcept {
        return dropped_;
    }

    [[nodiscard]] bool at(u32 index, SpanRecord& out) const noexcept {
        if (index >= size_) {
            return false;
        }
        out = spans_[index];
        return true;
    }

private:
    std::array<SpanRecord, kTraceBufferCapacity> spans_{};
    u32 size_{0};
    u64 dropped_{0};
};

}  // namespace stormline::core::diag

#endif  // STORMLINE_CORE_DIAG_TRACE_HPP
