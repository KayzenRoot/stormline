#include "stormline/core/diag/telemetry.hpp"

#include <cstdio>
#include <limits>
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

bool run_tel01() {
    begin_case();

    const BuildId build{1, 2};
    TelemetryEvent event{};
    expect(make_telemetry_event(build, DiagnosticTime{10}, 1, 2.5, "frame", event)
               == DiagnosticError::None,
           "valid telemetry event");
    expect(event.event_id == 1 && event.value == 2.5, "event fields");
    expect(view(event.name) == "frame", "event name");
    const double nan = std::numeric_limits<double>::quiet_NaN();
    expect(make_telemetry_event(build, DiagnosticTime{0}, 1, nan, "x", event)
               == DiagnosticError::InvalidArgument,
           "nan rejected");
    expect(make_telemetry_event(BuildId{}, DiagnosticTime{0}, 1, 1.0, "x", event)
               == DiagnosticError::InvalidArgument,
           "invalid build rejected");
    expect(make_telemetry_event(build, DiagnosticTime{0}, 0, 1.0, "x", event)
               == DiagnosticError::InvalidArgument,
           "zero event id rejected");

    TelemetryBuffer buffer;
    expect(!buffer.enabled(), "default disabled");
    expect(buffer.record(event) == DiagnosticError::NotEnabled, "record disabled");
    expect(buffer.set_enabled(true) == DiagnosticError::None, "enable local");
    expect(buffer.enabled(), "enabled");
    expect(make_telemetry_event(build, DiagnosticTime{1}, 1, 1.0, "a", event)
               == DiagnosticError::None,
           "record fixture");
    expect(buffer.record(event) == DiagnosticError::None, "record enabled");
    expect(buffer.size() == 1, "size one");
    expect(buffer.record(TelemetryEvent{}) == DiagnosticError::InvalidArgument,
           "invalid event rejected");
    expect(buffer.set_enabled(false) == DiagnosticError::None, "disable local");
    expect(!buffer.enabled(), "disabled again");
    expect(buffer.record(event) == DiagnosticError::NotEnabled, "record after disable");

    TelemetryPolicy non_local{};
    non_local.local_only = false;
    TelemetryBuffer non_local_buffer(non_local);
    expect(non_local_buffer.set_enabled(true) == DiagnosticError::Unsupported,
           "non-local rejected");

    TelemetryBuffer full_buffer;
    expect(full_buffer.set_enabled(true) == DiagnosticError::None, "full enable");
    for (u32 index = 0; index < kTelemetryCapacity; ++index) {
        expect(full_buffer.record(event) == DiagnosticError::None, "fill telemetry");
    }
    expect(full_buffer.record(event) == DiagnosticError::BufferFull, "telemetry full");
    expect(full_buffer.dropped() == 1, "telemetry dropped");

    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core06_telemetry_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "tel01") {
        success = run_tel01();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
