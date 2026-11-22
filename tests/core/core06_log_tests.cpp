#include "stormline/core/diag/log.hpp"

#include <cstdio>
#include <string>
#include <string_view>

namespace {

using namespace stormline::core::diag;

int failures = 0;

void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}

void begin_case() {
    failures = 0;
}

bool finish_case() {
    return failures == 0;
}

bool run_log01() {
    begin_case();

    BoundedText<8> text{};
    expect(assign_text(text, "12345678") == DiagnosticError::None, "max text accepted");
    expect(view(text) == "12345678", "max text view");
    expect(assign_text(text, "123456789") == DiagnosticError::InvalidArgument,
           "overlong text rejected");
    expect(assign_text(text, std::string_view("bad\0text", 8)) == DiagnosticError::InvalidArgument,
           "embedded NUL rejected");

    Attribute attributes[2]{};
    expect(assign_text(attributes[0].key, "asset") == DiagnosticError::None, "key assign");
    expect(assign_text(attributes[0].value, "hero") == DiagnosticError::None, "value assign");
    expect(assign_text(attributes[1].key, "frame") == DiagnosticError::None, "key2 assign");
    expect(assign_text(attributes[1].value, "42") == DiagnosticError::None, "value2 assign");

    LogRecord record{};
    const BuildId build{1, 2};
    const DiagnosticTime time{123};
    expect(make_log_record(build, 7, time, DiagnosticSeverity::Warn,
                           DiagnosticReason::FrameBudgetOverrun, 3,
                           "frame over budget", attributes, 2, record)
               == DiagnosticError::None,
           "valid log record");
    expect(record.schema_version == kDiagnosticsSchemaVersion, "schema version");
    expect(record.build.high == 1 && record.build.low == 2, "build round-trip");
    expect(record.producer_sequence == 7, "sequence round-trip");
    expect(record.time.monotonic_ns == 123, "time round-trip");
    expect(record.severity == DiagnosticSeverity::Warn, "severity round-trip");
    expect(record.reason == DiagnosticReason::FrameBudgetOverrun, "reason round-trip");
    expect(record.subsystem == 3, "subsystem round-trip");
    expect(view(record.message) == "frame over budget", "message view");
    expect(record.attribute_count == 2, "attribute count");
    expect(view(record.attributes[0].key) == "asset", "attribute key view");
    expect(view(record.attributes[0].value) == "hero", "attribute value view");

    LogRecord invalid{};
    expect(make_log_record(BuildId{}, 0, time, DiagnosticSeverity::Info,
                           DiagnosticReason::None, 0, "x", nullptr, 0, invalid)
               == DiagnosticError::InvalidArgument,
           "zero build rejected");
    expect(make_log_record(build, 0, DiagnosticTime{-1}, DiagnosticSeverity::Info,
                           DiagnosticReason::None, 0, "x", nullptr, 0, invalid)
               == DiagnosticError::InvalidArgument,
           "negative time rejected");
    expect(make_log_record(build, 0, time, DiagnosticSeverity::Info,
                           DiagnosticReason::None, 0, "x", nullptr, 1, invalid)
               == DiagnosticError::InvalidArgument,
           "null attributes rejected");
    expect(make_log_record(build, 0, time, DiagnosticSeverity::Info,
                           DiagnosticReason::None, 0, "x", nullptr,
                           kMaxAttributes + 1, invalid)
               == DiagnosticError::InvalidArgument,
           "too many attributes rejected");

    Attribute bad_key{};
    expect(make_log_record(build, 0, time, DiagnosticSeverity::Info,
                           DiagnosticReason::None, 0, "x", &bad_key, 1, invalid)
               == DiagnosticError::InvalidArgument,
           "empty attribute key rejected");

    return finish_case();
}

bool run_log02() {
    begin_case();

    LogBuffer buffer;
    LogRecord record{};
    expect(make_log_record(BuildId{1, 0}, 0, DiagnosticTime{1},
                           DiagnosticSeverity::Info, DiagnosticReason::None,
                           0, "capacity", nullptr, 0, record)
               == DiagnosticError::None,
           "buffer fixture record");
    for (u32 index = 0; index < kLogBufferCapacity; ++index) {
        expect(buffer.accept(record) == DiagnosticError::None, "buffer accept");
    }
    expect(buffer.size() == kLogBufferCapacity, "buffer size capacity");
    expect(buffer.accept(record) == DiagnosticError::BufferFull, "buffer full error");
    expect(buffer.dropped() == 1, "buffer dropped count");
    LogRecord out{};
    expect(buffer.at(0, out) && out.producer_sequence == 0, "buffer first record");
    expect(!buffer.at(kLogBufferCapacity, out), "buffer out of range");

    buffer.shutdown();
    expect(buffer.accept(record) == DiagnosticError::Shutdown, "accept after shutdown");
    expect(buffer.flush() == DiagnosticError::Shutdown, "flush after shutdown");
    buffer.shutdown();
    expect(buffer.flush() == DiagnosticError::Shutdown, "shutdown idempotent");

    LogBuffer other;
    expect(other.flush() == DiagnosticError::None, "fresh flush");
    return finish_case();
}

bool run_log03() {
    begin_case();

    const BuildId build{0x1234, 0x5678};
    LogBuffer buffer;
    Logger logger(build, &buffer);
    expect(logger.log(DiagnosticTime{10}, DiagnosticSeverity::Info,
                      DiagnosticReason::None, 1, "first", nullptr, 0)
               == DiagnosticError::None,
           "logger first");
    expect(logger.log(DiagnosticTime{11}, DiagnosticSeverity::Error,
                      DiagnosticReason::InvalidInput, 2, "second", nullptr, 0)
               == DiagnosticError::None,
           "logger second");
    expect(logger.next_sequence() == 2, "logger next sequence");
    LogRecord first{};
    LogRecord second{};
    expect(buffer.at(0, first) && first.producer_sequence == 0, "first sequence");
    expect(buffer.at(1, second) && second.producer_sequence == 1, "second sequence");
    expect(first.time.monotonic_ns == 10 && second.time.monotonic_ns == 11,
           "logger time order");
    expect(second.severity == DiagnosticSeverity::Error, "logger severity");
    expect(second.reason == DiagnosticReason::InvalidInput, "logger reason");

    Logger null_logger(build, nullptr);
    expect(null_logger.log(DiagnosticTime{1}, DiagnosticSeverity::Info,
                           DiagnosticReason::None, 0, "x", nullptr, 0)
               == DiagnosticError::InvalidArgument,
           "null sink rejected");
    expect(null_logger.next_sequence() == 1, "null sink sequence increments");

    Logger invalid_logger(BuildId{}, &buffer);
    expect(invalid_logger.log(DiagnosticTime{1}, DiagnosticSeverity::Info,
                              DiagnosticReason::None, 0, "x", nullptr, 0)
               == DiagnosticError::InvalidArgument,
           "invalid build rejected");
    expect(invalid_logger.next_sequence() == 1, "invalid build sequence increments");

    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core06_log_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "log01") {
        success = run_log01();
    } else if (mode == "log02") {
        success = run_log02();
    } else if (mode == "log03") {
        success = run_log03();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
