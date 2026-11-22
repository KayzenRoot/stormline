#include "stormline/core/diag/counter.hpp"
#include "stormline/core/diag/crash.hpp"
#include "stormline/core/diag/log.hpp"
#include "stormline/core/diag/profile.hpp"
#include "stormline/core/diag/telemetry.hpp"
#include "stormline/core/diag/trace.hpp"

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

bool run_qlf_d01() {
    begin_case();

    const BuildId build{1, 2};
    const DiagnosticTime time{10};
    LogBuffer logs;
    Logger logger(build, &logs);
    expect(logger.log(time, DiagnosticSeverity::Info, DiagnosticReason::None,
                      1, "integrated", nullptr, 0) == DiagnosticError::None,
           "log integrated");

    SpanRecord span{};
    expect(make_span(build, TraceId{3, 4}, SpanId{5}, SpanId{}, 0,
                     time, 1, "span", span) == DiagnosticError::None,
           "span create");
    expect(complete_span(span, DiagnosticTime{20}, DiagnosticReason::None)
               == DiagnosticError::None,
           "span complete");
    TraceBuffer traces;
    expect(traces.accept(span) == DiagnosticError::None, "trace accept");

    CounterSample counter{};
    expect(make_counter_sample(build, time, 7, CounterUnit::Count, 8.0, counter)
               == DiagnosticError::None,
           "counter create");
    CounterSet counters;
    expect(counters.record(counter) == DiagnosticError::None, "counter record");

    ProfileSample profile{};
    expect(make_profile_sample(build, 9, 100, 1, profile) == DiagnosticError::None,
           "profile create");
    ProfileAccumulator profiles;
    expect(profiles.add(profile) == DiagnosticError::None, "profile add");

    LogRecord preceding{};
    expect(make_log_record(build, 0, time, DiagnosticSeverity::Warn,
                           DiagnosticReason::FrameBudgetOverrun, 1,
                           "before crash", nullptr, 0, preceding)
               == DiagnosticError::None,
           "preceding log");
    CrashEnvelope crash{};
    expect(make_crash_envelope(build, SessionId{11}, 2, DiagnosticTime{30},
                               DiagnosticReason::CrashUnhandled, &preceding, 1, crash)
               == DiagnosticError::None,
           "crash envelope");

    TelemetryBuffer telemetry;
    expect(telemetry.set_enabled(true) == DiagnosticError::None, "telemetry enable");
    TelemetryEvent event{};
    expect(make_telemetry_event(build, time, 12, 13.0, "local", event)
               == DiagnosticError::None,
           "telemetry event");
    expect(telemetry.record(event) == DiagnosticError::None, "telemetry record");

    expect(logs.size() == 1 && traces.size() == 1 && counters.size() == 1
               && profiles.count() == 1 && crash.preceding_count == 1
               && telemetry.size() == 1,
           "integrated sizes");
    expect(logs.at(0, preceding) && view(preceding.message) == "integrated",
           "integrated log value");

    return finish_case();
}

bool run_qlf_d02() {
    begin_case();

    const BuildId build{1, 2};
    LogBuffer logs;
    Logger logger(build, &logs);
    const DiagnosticError first =
        logger.log(DiagnosticTime{1}, DiagnosticSeverity::Info,
                   DiagnosticReason::None, 0, "repeat", nullptr, 0);
    const DiagnosticError second =
        logger.log(DiagnosticTime{2}, DiagnosticSeverity::Info,
                   DiagnosticReason::None, 0, "repeat", nullptr, 0);
    expect(first == DiagnosticError::None && second == DiagnosticError::None,
           "repeat logs");
    LogRecord a{};
    LogRecord b{};
    expect(logs.at(0, a) && logs.at(1, b), "repeat read");
    expect(a.producer_sequence == 0 && b.producer_sequence == 1,
           "repeat sequence");
    expect(view(a.message) == view(b.message), "repeat message");

    CounterSet counters;
    CounterSample sample{};
    expect(make_counter_sample(build, DiagnosticTime{1}, 1, CounterUnit::Count,
                               1.0, sample) == DiagnosticError::None,
           "repeat counter");
    expect(counters.record(sample) == DiagnosticError::None, "repeat record");
    expect(counters.find(1, sample) && sample.value == 1.0, "repeat find");

    return finish_case();
}

bool run_qlf_d03() {
    begin_case();

    LogRecord invalid{};
    expect(make_log_record(BuildId{}, 0, DiagnosticTime{0},
                           DiagnosticSeverity::Info, DiagnosticReason::None,
                           0, "x", nullptr, 0, invalid)
               == DiagnosticError::InvalidArgument,
           "log error");
    LogBuffer logs;
    LogRecord valid{};
    expect(make_log_record(BuildId{1, 0}, 0, DiagnosticTime{0},
                           DiagnosticSeverity::Info, DiagnosticReason::None,
                           0, "valid", nullptr, 0, valid)
               == DiagnosticError::None,
           "log recovery fixture");
    expect(logs.accept(valid) == DiagnosticError::None, "log recovery");

    SpanRecord span{};
    expect(make_span(BuildId{1, 0}, TraceId{1, 0}, SpanId{1}, SpanId{}, 0,
                     DiagnosticTime{0}, 0, "x", span) == DiagnosticError::None,
           "span fixture");
    expect(complete_span(span, DiagnosticTime{1}, DiagnosticReason::None)
               == DiagnosticError::None,
           "span complete");
    expect(complete_span(span, DiagnosticTime{2}, DiagnosticReason::None)
               == DiagnosticError::InvalidArgument,
           "span error");
    TraceBuffer traces;
    expect(traces.accept(span) == DiagnosticError::None, "span recovery");

    TelemetryBuffer telemetry;
    expect(telemetry.record(TelemetryEvent{}) == DiagnosticError::NotEnabled,
           "telemetry error");
    expect(telemetry.set_enabled(true) == DiagnosticError::None, "telemetry recovery");

    CounterSet counters;
    expect(counters.record(CounterSample{}) == DiagnosticError::InvalidArgument,
           "counter error");
    CounterSample sample{};
    expect(make_counter_sample(BuildId{1, 0}, DiagnosticTime{0}, 1,
                               CounterUnit::Count, 1.0, sample)
               == DiagnosticError::None,
           "counter recovery fixture");
    expect(counters.record(sample) == DiagnosticError::None, "counter recovery");

    return finish_case();
}

bool run_qlf_d04() {
    begin_case();

    const BuildId build{1, 2};
    LogRecord log{};
    expect(make_log_record(build, 0, DiagnosticTime{0}, DiagnosticSeverity::Info,
                           DiagnosticReason::None, 0, "spam", nullptr, 0, log)
               == DiagnosticError::None,
           "spam log fixture");
    LogBuffer logs;
    for (int index = 0; index < 10'000; ++index) {
        const DiagnosticError error = logs.accept(log);
        if (index < static_cast<int>(kLogBufferCapacity)) {
            expect(error == DiagnosticError::None, "log capacity phase");
        } else {
            expect(error == DiagnosticError::BufferFull, "log full phase");
        }
    }
    expect(logs.size() == kLogBufferCapacity, "log fixed size");
    expect(logs.dropped() == 10'000 - kLogBufferCapacity, "log drops");

    TelemetryBuffer telemetry;
    expect(telemetry.set_enabled(true) == DiagnosticError::None, "spam telemetry enable");
    TelemetryEvent event{};
    expect(make_telemetry_event(build, DiagnosticTime{0}, 1, 1.0, "spam", event)
               == DiagnosticError::None,
           "spam event fixture");
    for (int index = 0; index < 10'000; ++index) {
        const DiagnosticError error = telemetry.record(event);
        if (index < static_cast<int>(kTelemetryCapacity)) {
            expect(error == DiagnosticError::None, "telemetry capacity phase");
        } else {
            expect(error == DiagnosticError::BufferFull, "telemetry full phase");
        }
    }
    expect(telemetry.size() == kTelemetryCapacity, "telemetry fixed size");
    expect(telemetry.dropped() == 10'000 - kTelemetryCapacity, "telemetry drops");

    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core06_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlfd01") {
        success = run_qlf_d01();
    } else if (mode == "qlfd02") {
        success = run_qlf_d02();
    } else if (mode == "qlfd03") {
        success = run_qlf_d03();
    } else if (mode == "qlfd04") {
        success = run_qlf_d04();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
