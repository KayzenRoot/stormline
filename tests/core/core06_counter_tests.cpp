#include "stormline/core/diag/counter.hpp"

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

bool run_counter01() {
    begin_case();

    const BuildId build{1, 2};
    CounterSample sample{};
    expect(make_counter_sample(build, DiagnosticTime{10}, 1,
                               CounterUnit::Bytes, 42.5, sample)
               == DiagnosticError::None,
           "valid counter");
    expect(sample.schema_version == kDiagnosticsSchemaVersion, "schema");
    expect(sample.build.high == 1 && sample.time.monotonic_ns == 10, "metadata");
    expect(sample.counter_id == 1 && sample.unit == CounterUnit::Bytes,
           "counter fields");
    expect(sample.value == 42.5, "counter value");

    const double nan = std::numeric_limits<double>::quiet_NaN();
    const double infinity = std::numeric_limits<double>::infinity();
    expect(make_counter_sample(build, DiagnosticTime{0}, 1, CounterUnit::Count,
                               nan, sample)
               == DiagnosticError::InvalidArgument,
           "nan rejected");
    expect(make_counter_sample(build, DiagnosticTime{0}, 1, CounterUnit::Count,
                               infinity, sample)
               == DiagnosticError::InvalidArgument,
           "infinity rejected");
    expect(make_counter_sample(BuildId{}, DiagnosticTime{0}, 1,
                               CounterUnit::Count, 1.0, sample)
               == DiagnosticError::InvalidArgument,
           "invalid build rejected");
    expect(make_counter_sample(build, DiagnosticTime{-1}, 1,
                               CounterUnit::Count, 1.0, sample)
               == DiagnosticError::InvalidArgument,
           "negative time rejected");
    expect(make_counter_sample(build, DiagnosticTime{0}, 0,
                               CounterUnit::Count, 1.0, sample)
               == DiagnosticError::InvalidArgument,
           "zero counter id rejected");

    CounterSet counters;
    expect(make_counter_sample(build, DiagnosticTime{1}, 1, CounterUnit::Count,
                               10.0, sample)
               == DiagnosticError::None,
           "counter fixture");
    expect(counters.record(sample) == DiagnosticError::None, "record first");
    expect(counters.size() == 1, "size one");
    CounterSample found{};
    expect(counters.find(1, found) && found.value == 10.0, "find first");
    expect(!counters.find(2, found), "find missing");

    expect(make_counter_sample(build, DiagnosticTime{2}, 1, CounterUnit::Count,
                               20.0, sample)
               == DiagnosticError::None,
           "update fixture");
    expect(counters.record(sample) == DiagnosticError::None, "update duplicate");
    expect(counters.size() == 1, "duplicate does not grow");
    expect(counters.find(1, found) && found.value == 20.0, "duplicate updated");

    for (u32 id = 2; id <= kCounterCapacity; ++id) {
        expect(make_counter_sample(build, DiagnosticTime{3}, id,
                                   CounterUnit::Count, static_cast<double>(id), sample)
                   == DiagnosticError::None,
               "fill fixture");
        expect(counters.record(sample) == DiagnosticError::None, "fill record");
    }
    expect(counters.size() == kCounterCapacity, "counter capacity");
    expect(make_counter_sample(build, DiagnosticTime{4}, kCounterCapacity + 1,
                               CounterUnit::Count, 1.0, sample)
               == DiagnosticError::None,
           "overflow fixture");
    expect(counters.record(sample) == DiagnosticError::BufferFull, "counter full");
    expect(counters.dropped() == 1, "counter dropped");

    CounterSample invalid{};
    invalid.build = build;
    invalid.counter_id = 1;
    invalid.value = nan;
    expect(counters.record(invalid) == DiagnosticError::InvalidArgument,
           "record validates nan");

    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core06_counter_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "counter01") {
        success = run_counter01();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
