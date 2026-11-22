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

bool run_trace01() {
    begin_case();

    const BuildId build{1, 2};
    const TraceId trace{3, 4};
    SpanRecord root{};
    expect(make_span(build, trace, SpanId{10}, SpanId{}, 1,
                     DiagnosticTime{100}, 7, "frame", root)
               == DiagnosticError::None,
           "root span created");
    expect(root.schema_version == kDiagnosticsSchemaVersion, "schema");
    expect(root.build.high == 1 && root.trace.high == 3, "IDs");
    expect(root.parent.value == 0 && !root.completed, "root state");
    expect(view(root.name) == "frame", "name");

    SpanRecord child{};
    expect(make_span(build, trace, SpanId{11}, SpanId{10}, 2,
                     DiagnosticTime{110}, 7, "draw", child)
               == DiagnosticError::None,
           "child span created");

    expect(complete_span(root, DiagnosticTime{150}, DiagnosticReason::FrameBudgetOverrun)
               == DiagnosticError::None,
           "root completed");
    expect(root.completed && root.end.monotonic_ns == 150, "root end");
    expect(root.outcome == DiagnosticReason::FrameBudgetOverrun, "root outcome");
    expect(complete_span(root, DiagnosticTime{160}, DiagnosticReason::None)
               == DiagnosticError::InvalidArgument,
           "double completion rejected");

    SpanRecord bad_end{};
    expect(make_span(build, trace, SpanId{12}, SpanId{}, 3,
                     DiagnosticTime{200}, 0, "bad", bad_end)
               == DiagnosticError::None,
           "bad-end fixture");
    expect(complete_span(bad_end, DiagnosticTime{199}, DiagnosticReason::None)
               == DiagnosticError::InvalidArgument,
           "end before start rejected");

    SpanRecord invalid{};
    expect(make_span(BuildId{}, trace, SpanId{1}, SpanId{}, 0,
                     DiagnosticTime{0}, 0, "x", invalid)
               == DiagnosticError::InvalidArgument,
           "invalid build rejected");
    expect(make_span(build, TraceId{}, SpanId{1}, SpanId{}, 0,
                     DiagnosticTime{0}, 0, "x", invalid)
               == DiagnosticError::InvalidArgument,
           "invalid trace rejected");
    expect(make_span(build, trace, SpanId{}, SpanId{}, 0,
                     DiagnosticTime{0}, 0, "x", invalid)
               == DiagnosticError::InvalidArgument,
           "invalid span rejected");
    expect(make_span(build, trace, SpanId{1}, SpanId{}, 0,
                     DiagnosticTime{-1}, 0, "x", invalid)
               == DiagnosticError::InvalidArgument,
           "negative start rejected");
    expect(make_span(build, trace, SpanId{1}, SpanId{1}, 0,
                     DiagnosticTime{0}, 0, "x", invalid)
               == DiagnosticError::InvalidArgument,
           "self parent rejected");

    TraceBuffer buffer;
    expect(buffer.accept(child) == DiagnosticError::InvalidArgument,
           "incomplete span rejected");
    expect(complete_span(child, DiagnosticTime{120}, DiagnosticReason::None)
               == DiagnosticError::None,
           "child completed");
    expect(buffer.accept(child) == DiagnosticError::None, "completed child accepted");
    for (u32 index = 1; index < kTraceBufferCapacity; ++index) {
        expect(buffer.accept(child) == DiagnosticError::None, "trace buffer fill");
    }
    expect(buffer.accept(child) == DiagnosticError::BufferFull, "trace buffer full");
    expect(buffer.dropped() == 1, "trace dropped");
    SpanRecord out{};
    expect(buffer.at(0, out) && out.span.value == 11, "trace at");
    expect(!buffer.at(kTraceBufferCapacity, out), "trace out of range");

    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core06_trace_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "trace01") {
        success = run_trace01();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
