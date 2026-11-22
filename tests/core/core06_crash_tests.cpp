#include "stormline/core/diag/crash.hpp"

#include <cstdio>
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

bool run_crash01() {
    begin_case();

    const BuildId build{1, 2};
    const SessionId session{3};
    LogRecord logs[2]{};
    expect(make_log_record(build, 0, DiagnosticTime{10}, DiagnosticSeverity::Info,
                           DiagnosticReason::None, 1, "first", nullptr, 0, logs[0])
               == DiagnosticError::None,
           "first log");
    expect(make_log_record(build, 1, DiagnosticTime{11}, DiagnosticSeverity::Error,
                           DiagnosticReason::InternalFailure, 2, "second", nullptr, 0, logs[1])
               == DiagnosticError::None,
           "second log");

    CrashEnvelope envelope{};
    expect(make_crash_envelope(build, session, 7, DiagnosticTime{12},
                               DiagnosticReason::CrashUnhandled, logs, 2, envelope)
               == DiagnosticError::None,
           "crash envelope");
    expect(envelope.schema_version == kDiagnosticsSchemaVersion, "schema");
    expect(envelope.build.high == 1 && envelope.session.value == 3, "IDs");
    expect(envelope.platform_tag == 7 && envelope.time.monotonic_ns == 12, "metadata");
    expect(envelope.reason == DiagnosticReason::CrashUnhandled, "reason");
    expect(envelope.preceding_count == 2, "preceding count");
    expect(view(envelope.preceding[0].message) == "first", "first preceding");
    expect(view(envelope.preceding[1].message) == "second", "second preceding");

    expect(make_crash_envelope(build, session, 0, DiagnosticTime{0},
                               DiagnosticReason::CrashUnhandled, nullptr, 1, envelope)
               == DiagnosticError::InvalidArgument,
           "null preceding rejected");
    LogRecord overflow[kCrashPrecedingRecords + 1]{};
    expect(make_crash_envelope(build, session, 0, DiagnosticTime{0},
                               DiagnosticReason::CrashUnhandled, overflow,
                               kCrashPrecedingRecords + 1, envelope)
               == DiagnosticError::InvalidArgument,
           "too many preceding rejected");
    expect(make_crash_envelope(BuildId{}, session, 0, DiagnosticTime{0},
                               DiagnosticReason::CrashUnhandled, nullptr, 0, envelope)
               == DiagnosticError::InvalidArgument,
           "invalid build rejected");
    expect(make_crash_envelope(build, SessionId{}, 0, DiagnosticTime{0},
                               DiagnosticReason::CrashUnhandled, nullptr, 0, envelope)
               == DiagnosticError::InvalidArgument,
           "invalid session rejected");
    expect(make_crash_envelope(build, session, 0, DiagnosticTime{-1},
                               DiagnosticReason::CrashUnhandled, nullptr, 0, envelope)
               == DiagnosticError::InvalidArgument,
           "negative time rejected");

    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core06_crash_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "crash01") {
        success = run_crash01();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
