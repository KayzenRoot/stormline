#include "stormline/animation/skeletal/ik_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::animation::skeletal;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

IkChainDesc chain(u32 id, u32 bones, u32 iterations, bool enabled) {
    IkChainDesc desc{};
    desc.chain_id = id;
    desc.revision = 1;
    desc.bone_count = bones;
    desc.iterations = iterations;
    desc.tolerance = 0.01f;
    desc.target_weight = 0.5f;
    desc.enabled = enabled;
    return desc;
}

IkSetDesc ik_set() {
    IkSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.chain_count = 3;
    desc.chains[0] = chain(1, 3, 16, true);
    desc.chains[1] = chain(2, 2, 8, false);
    desc.chains[2] = chain(3, 4, 32, true);
    return desc;
}

bool run_ik01() {
    begin();
    IkSetDesc ik = ik_set();
    IkPlan plan{};
    SkeletalDiagnostic diagnostic{};
    expect(plan_ik(ik, plan, diagnostic) == SkeletalError::None,
           "valid ik");
    expect(plan.chain_count == 3 && plan.total_bone_count == 9
               && plan.max_iterations == 32 && plan.enabled_count == 2,
           "valid plan");
    expect(diagnostic.code == SkeletalError::None, "success diagnostic");

    IkPlan repeat{};
    expect(plan_ik(ik, repeat, diagnostic) == SkeletalError::None,
           "repeat ik");
    expect(repeat.max_iterations == plan.max_iterations,
           "deterministic plan");

    ik.owner_id = 0;
    expect(plan_ik(ik, plan, diagnostic) == SkeletalError::InvalidArgument,
           "zero owner");
    expect(plan.chain_count == 0, "reset on zero owner");
    ik = ik_set();
    ik.revision = 0;
    expect(plan_ik(ik, plan, diagnostic) == SkeletalError::InvalidArgument,
           "zero revision");
    ik = ik_set();
    ik.chain_count = kMaxIkChains + 1;
    expect(plan_ik(ik, plan, diagnostic) == SkeletalError::CapacityFull,
           "chain overflow");

    ik = ik_set();
    ik.chains[1].chain_id = 0;
    expect(plan_ik(ik, plan, diagnostic) == SkeletalError::IkInvalid,
           "zero chain id");
    expect(diagnostic.index == 1, "zero chain diagnostic");
    ik = ik_set();
    ik.chains[1].revision = 0;
    expect(plan_ik(ik, plan, diagnostic) == SkeletalError::IkInvalid,
           "zero revision");
    ik = ik_set();
    ik.chains[1].bone_count = 0;
    expect(plan_ik(ik, plan, diagnostic) == SkeletalError::OutOfRange,
           "zero bones");
    ik = ik_set();
    ik.chains[1].bone_count = 17;
    expect(plan_ik(ik, plan, diagnostic) == SkeletalError::OutOfRange,
           "bone overflow");
    ik = ik_set();
    ik.chains[1].iterations = kMaxIkIterations + 1;
    expect(plan_ik(ik, plan, diagnostic) == SkeletalError::OutOfRange,
           "iteration overflow");
    ik = ik_set();
    ik.chains[1].tolerance = -0.1f;
    expect(plan_ik(ik, plan, diagnostic) == SkeletalError::OutOfRange,
           "negative tolerance");
    ik = ik_set();
    ik.chains[1].target_weight = 1.5f;
    expect(plan_ik(ik, plan, diagnostic) == SkeletalError::OutOfRange,
           "weight above one");
    ik = ik_set();
    ik.chains[1].tolerance = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_ik(ik, plan, diagnostic) == SkeletalError::OutOfRange,
           "non-finite tolerance");
    ik = ik_set();
    ik.chains[2].chain_id = 1;
    expect(plan_ik(ik, plan, diagnostic) == SkeletalError::DuplicateId,
           "duplicate chain");
    expect(diagnostic.index == 2, "duplicate chain diagnostic");

    ik = ik_set();
    ik.chain_count = kMaxIkChains;
    for (u32 index = 0; index < kMaxIkChains; ++index) {
        ik.chains[index] =
            chain(index + 1, 1 + index % 16, index % 65, index % 2 == 0);
    }
    expect(plan_ik(ik, plan, diagnostic) == SkeletalError::None,
           "capacity ik");
    expect(plan.chain_count == kMaxIkChains
               && plan.enabled_count == kMaxIkChains / 2,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim04_ik_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "ik01") { success = run_ik01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
