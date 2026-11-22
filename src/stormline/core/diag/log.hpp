#ifndef STORMLINE_CORE_DIAG_LOG_HPP
#define STORMLINE_CORE_DIAG_LOG_HPP

#include "stormline/core/diag/diagnostics_types.hpp"

#include <array>
#include <string_view>

namespace stormline::core::diag {

struct Attribute {
    BoundedText<kMaxAttributeKeyBytes> key{};
    BoundedText<kMaxAttributeValueBytes> value{};
};

struct LogRecord {
    u32 schema_version{kDiagnosticsSchemaVersion};
    BuildId build{};
    u64 producer_sequence{0};
    DiagnosticTime time{};
    DiagnosticSeverity severity{DiagnosticSeverity::Info};
    DiagnosticReason reason{DiagnosticReason::None};
    u32 subsystem{0};
    BoundedText<kMaxMessageBytes> message{};
    std::array<Attribute, kMaxAttributes> attributes{};
    u32 attribute_count{0};
};

[[nodiscard]] inline DiagnosticError make_log_record(
    BuildId build, u64 producer_sequence, DiagnosticTime time,
    DiagnosticSeverity severity, DiagnosticReason reason, u32 subsystem,
    std::string_view message, const Attribute* attributes, u32 attribute_count,
    LogRecord& out) noexcept {
    if (!valid(build) || time.monotonic_ns < 0
        || attribute_count > kMaxAttributes
        || (attribute_count != 0 && attributes == nullptr)) {
        return DiagnosticError::InvalidArgument;
    }

    LogRecord record{};
    record.build = build;
    record.producer_sequence = producer_sequence;
    record.time = time;
    record.severity = severity;
    record.reason = reason;
    record.subsystem = subsystem;
    DiagnosticError error = assign_text(record.message, message);
    if (error != DiagnosticError::None) {
        return error;
    }
    for (u32 index = 0; index < attribute_count; ++index) {
        const Attribute& source = attributes[index];
        if (source.key.length == 0
            || source.key.length > kMaxAttributeKeyBytes
            || source.value.length > kMaxAttributeValueBytes) {
            return DiagnosticError::InvalidArgument;
        }
        error = assign_text(record.attributes[index].key, view(source.key));
        if (error != DiagnosticError::None) {
            return error;
        }
        error = assign_text(record.attributes[index].value, view(source.value));
        if (error != DiagnosticError::None) {
            return error;
        }
    }
    record.attribute_count = attribute_count;
    out = record;
    return DiagnosticError::None;
}

class DiagnosticSink {
public:
    virtual ~DiagnosticSink() = default;
    virtual DiagnosticError accept(const LogRecord& record) noexcept = 0;
    virtual DiagnosticError flush() noexcept = 0;
    virtual void shutdown() noexcept = 0;
};

class LogBuffer final : public DiagnosticSink {
public:
    LogBuffer() noexcept = default;
    ~LogBuffer() override = default;
    LogBuffer(const LogBuffer&) = delete;
    LogBuffer& operator=(const LogBuffer&) = delete;
    LogBuffer(LogBuffer&&) = delete;
    LogBuffer& operator=(LogBuffer&&) = delete;

    DiagnosticError accept(const LogRecord& record) noexcept override {
        if (shutdown_) {
            return DiagnosticError::Shutdown;
        }
        if (size_ >= kLogBufferCapacity) {
            ++dropped_;
            return DiagnosticError::BufferFull;
        }
        records_[size_] = record;
        ++size_;
        return DiagnosticError::None;
    }

    DiagnosticError flush() noexcept override {
        return shutdown_ ? DiagnosticError::Shutdown : DiagnosticError::None;
    }

    void shutdown() noexcept override {
        shutdown_ = true;
    }

    [[nodiscard]] u32 size() const noexcept {
        return size_;
    }

    [[nodiscard]] u64 dropped() const noexcept {
        return dropped_;
    }

    [[nodiscard]] bool at(u32 index, LogRecord& out) const noexcept {
        if (index >= size_) {
            return false;
        }
        out = records_[index];
        return true;
    }

private:
    std::array<LogRecord, kLogBufferCapacity> records_{};
    u32 size_{0};
    u64 dropped_{0};
    bool shutdown_{false};
};

class Logger final {
public:
    Logger(BuildId build, DiagnosticSink* sink) noexcept
        : build_(build), sink_(sink) {}

    [[nodiscard]] DiagnosticError log(
        DiagnosticTime time, DiagnosticSeverity severity, DiagnosticReason reason,
        u32 subsystem, std::string_view message,
        const Attribute* attributes = nullptr, u32 attribute_count = 0) noexcept {
        const u64 sequence = sequence_;
        ++sequence_;
        LogRecord record{};
        DiagnosticError error = make_log_record(
            build_, sequence, time, severity, reason, subsystem, message,
            attributes, attribute_count, record);
        if (error != DiagnosticError::None) {
            return error;
        }
        if (sink_ == nullptr) {
            return DiagnosticError::InvalidArgument;
        }
        return sink_->accept(record);
    }

    [[nodiscard]] u64 next_sequence() const noexcept {
        return sequence_;
    }

private:
    BuildId build_{};
    DiagnosticSink* sink_{nullptr};
    u64 sequence_{0};
};

}  // namespace stormline::core::diag

#endif  // STORMLINE_CORE_DIAG_LOG_HPP
