#include "stormline/graphics/shader/shader_incremental.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::graphics::shader;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_inc01() {
    begin();
    DependencySet first{};
    first.count = 2;
    first.dependencies[0] = DependencyRef{1, 10};
    first.dependencies[1] = DependencyRef{2, 20};
    u64 fingerprint = 0;
    expect(dependency_fingerprint(first, fingerprint) == ShaderError::None,
           "fingerprint");
    expect(fingerprint != 0, "fingerprint nonzero");

    u64 repeat = 0;
    expect(dependency_fingerprint(first, repeat) == ShaderError::None
               && repeat == fingerprint, "fingerprint repeat");
    const u64 expected_fingerprint = fingerprint;

    DependencySet reversed{};
    reversed.count = 2;
    reversed.dependencies[0] = DependencyRef{2, 20};
    reversed.dependencies[1] = DependencyRef{1, 10};
    u64 reversed_fingerprint = 0;
    expect(dependency_fingerprint(reversed, reversed_fingerprint) == ShaderError::None
               && reversed_fingerprint == fingerprint,
           "order insensitive");

    DependencySet changed = first;
    changed.dependencies[0].revision = 11;
    u64 changed_fingerprint = 0;
    expect(dependency_fingerprint(changed, changed_fingerprint) == ShaderError::None
               && changed_fingerprint != fingerprint,
           "revision changes fingerprint");

    DependencySet invalid = first;
    invalid.dependencies[1].id = 1;
    expect(dependency_fingerprint(invalid, fingerprint) == ShaderError::InvalidArgument,
           "duplicate id");
    invalid = first;
    invalid.dependencies[0].id = 0;
    expect(dependency_fingerprint(invalid, fingerprint) == ShaderError::InvalidArgument,
           "zero id");
    invalid = first;
    invalid.dependencies[0].revision = 0;
    expect(dependency_fingerprint(invalid, fingerprint) == ShaderError::InvalidArgument,
           "zero revision");
    invalid = first;
    invalid.count = 0;
    expect(dependency_fingerprint(invalid, fingerprint) == ShaderError::InvalidArgument,
           "zero count");
    invalid = first;
    invalid.count = kMaxDependencies + 1;
    expect(dependency_fingerprint(invalid, fingerprint) == ShaderError::InvalidArgument,
           "count range");

    bool rebuild = false;
    u64 plan_fingerprint = 0;
    expect(plan_incremental(first, IncrementalState{}, rebuild, plan_fingerprint)
               == ShaderError::None,
           "initial plan");
    expect(rebuild && plan_fingerprint == expected_fingerprint, "initial rebuild");

    expect(plan_incremental(first, IncrementalState{plan_fingerprint, 99},
                            rebuild, plan_fingerprint) == ShaderError::None,
           "stable plan");
    expect(!rebuild, "stable no rebuild");

    expect(plan_incremental(first, IncrementalState{plan_fingerprint, 0},
                            rebuild, plan_fingerprint) == ShaderError::None,
           "zero cache key plan");
    expect(rebuild, "zero cache key rebuild");

    expect(plan_incremental(changed, IncrementalState{expected_fingerprint, 99},
                            rebuild, plan_fingerprint) == ShaderError::None,
           "changed plan");
    expect(rebuild && plan_fingerprint == changed_fingerprint, "changed rebuild");

    expect(plan_incremental(invalid, IncrementalState{}, rebuild, plan_fingerprint)
               == ShaderError::InvalidArgument,
           "invalid plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx02_incremental_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "inc01") { success = run_inc01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
