#include "stormline/core/diag/profile.hpp"

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

bool run_prof01() {
    begin_case();

    const BuildId build{1, 2};
    ProfileSample sample{};
    expect(make_profile_sample(build, 1, 0, 3, sample) == DiagnosticError::None,
           "zero elapsed allowed");
    expect(sample.build.high == 1 && sample.scope_id == 1, "metadata");
    expect(make_profile_sample(BuildId{}, 1, 1, 0, sample)
               == DiagnosticError::InvalidArgument,
           "invalid build rejected");
    expect(make_profile_sample(build, 0, 1, 0, sample)
               == DiagnosticError::InvalidArgument,
           "zero scope rejected");

    ProfileAccumulator accumulator;
    const ProfileSample invalid_sample{};
    expect(accumulator.add(invalid_sample) == DiagnosticError::InvalidArgument,
           "invalid sample rejected");
    expect(make_profile_sample(build, 1, 5, 0, sample) == DiagnosticError::None,
           "sample five");
    expect(accumulator.add(sample) == DiagnosticError::None, "add five");
    expect(make_profile_sample(build, 1, 10, 0, sample) == DiagnosticError::None,
           "sample ten");
    expect(accumulator.add(sample) == DiagnosticError::None, "add ten");
    expect(make_profile_sample(build, 1, 20, 0, sample) == DiagnosticError::None,
           "sample twenty");
    expect(accumulator.add(sample) == DiagnosticError::None, "add twenty");
    expect(accumulator.count() == 3, "count");
    expect(accumulator.total_ns() == 35, "total");
    expect(accumulator.min_ns() == 5, "min");
    expect(accumulator.max_ns() == 20, "max");

    accumulator.reset();
    expect(accumulator.count() == 0 && accumulator.total_ns() == 0
               && accumulator.min_ns() == 0 && accumulator.max_ns() == 0,
           "reset");
    expect(accumulator.dropped() == 0, "reset dropped");

    for (u64 index = 0; index < kProfileCapacity; ++index) {
        expect(make_profile_sample(build, 1, index + 1, 0, sample)
                   == DiagnosticError::None,
               "fill sample");
        expect(accumulator.add(sample) == DiagnosticError::None, "fill add");
    }
    expect(accumulator.count() == kProfileCapacity, "capacity");
    expect(make_profile_sample(build, 1, 1, 0, sample) == DiagnosticError::None,
           "overflow sample");
    expect(accumulator.add(sample) == DiagnosticError::BufferFull, "full error");
    expect(accumulator.dropped() == 1, "dropped");

    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core06_profile_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "prof01") {
        success = run_prof01();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
