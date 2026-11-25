#include "stormline/animation/skeletal/retarget_plan.hpp"

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

RetargetProfileDesc profile(u32 id, u32 pairs, bool enabled) {
    RetargetProfileDesc desc{};
    desc.retarget_id = id;
    desc.revision = 1;
    desc.bind_scale = 1.0f;
    desc.pair_count = pairs;
    for (u32 index = 0; index < pairs; ++index) {
        desc.pairs[index] =
            RetargetJointPair{index + 1, index + 101};
    }
    desc.enabled = enabled;
    return desc;
}

RetargetSetDesc retarget_set() {
    RetargetSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.profile_count = 2;
    desc.profiles[0] = profile(1, 3, true);
    desc.profiles[1] = profile(2, 2, false);
    return desc;
}

bool run_ret01() {
    begin();
    RetargetSetDesc retargets = retarget_set();
    RetargetPlan plan{};
    SkeletalDiagnostic diagnostic{};
    expect(plan_retargets(retargets, plan, diagnostic) == SkeletalError::None,
           "valid retargets");
    expect(plan.profile_count == 2 && plan.total_pair_count == 5
               && plan.enabled_count == 1,
           "valid plan");
    expect(diagnostic.code == SkeletalError::None, "success diagnostic");

    RetargetPlan repeat{};
    expect(plan_retargets(retargets, repeat, diagnostic)
               == SkeletalError::None,
           "repeat retargets");
    expect(repeat.total_pair_count == plan.total_pair_count,
           "deterministic plan");

    retargets.owner_id = 0;
    expect(plan_retargets(retargets, plan, diagnostic)
               == SkeletalError::InvalidArgument,
           "zero owner");
    expect(plan.profile_count == 0, "reset on zero owner");
    retargets = retarget_set();
    retargets.revision = 0;
    expect(plan_retargets(retargets, plan, diagnostic)
               == SkeletalError::InvalidArgument,
           "zero revision");
    retargets = retarget_set();
    retargets.profile_count = kMaxRetargetProfiles + 1;
    expect(plan_retargets(retargets, plan, diagnostic)
               == SkeletalError::CapacityFull,
           "profile overflow");

    retargets = retarget_set();
    retargets.profiles[1].retarget_id = 0;
    expect(plan_retargets(retargets, plan, diagnostic)
               == SkeletalError::RetargetInvalid,
           "zero profile id");
    expect(diagnostic.index == 1, "zero profile diagnostic");
    retargets = retarget_set();
    retargets.profiles[1].revision = 0;
    expect(plan_retargets(retargets, plan, diagnostic)
               == SkeletalError::RetargetInvalid,
           "zero profile revision");
    retargets = retarget_set();
    retargets.profiles[0].bind_scale = 0.0f;
    expect(plan_retargets(retargets, plan, diagnostic)
               == SkeletalError::OutOfRange,
           "zero bind scale");
    retargets = retarget_set();
    retargets.profiles[0].bind_scale =
        std::numeric_limits<f32>::quiet_NaN();
    expect(plan_retargets(retargets, plan, diagnostic)
               == SkeletalError::OutOfRange,
           "non-finite bind scale");
    retargets = retarget_set();
    retargets.profiles[0].pair_count = kMaxRetargetPairs + 1;
    expect(plan_retargets(retargets, plan, diagnostic)
               == SkeletalError::CapacityFull,
           "pair overflow");
    retargets = retarget_set();
    retargets.profiles[0].pairs[1].source_joint = 0;
    expect(plan_retargets(retargets, plan, diagnostic)
               == SkeletalError::RetargetInvalid,
           "zero source joint");
    retargets = retarget_set();
    retargets.profiles[0].pairs[1].target_joint = 0;
    expect(plan_retargets(retargets, plan, diagnostic)
               == SkeletalError::RetargetInvalid,
           "zero target joint");
    retargets = retarget_set();
    retargets.profiles[0].pairs[2].source_joint = 1;
    expect(plan_retargets(retargets, plan, diagnostic)
               == SkeletalError::DuplicateId,
           "duplicate source joint");
    retargets = retarget_set();
    retargets.profiles[0].pairs[2].target_joint = 101;
    expect(plan_retargets(retargets, plan, diagnostic)
               == SkeletalError::DuplicateId,
           "duplicate target joint");
    retargets = retarget_set();
    retargets.profiles[1].retarget_id = 1;
    expect(plan_retargets(retargets, plan, diagnostic)
               == SkeletalError::DuplicateId,
           "duplicate profile");
    expect(diagnostic.index == 1, "duplicate profile diagnostic");

    retargets = retarget_set();
    retargets.profile_count = kMaxRetargetProfiles;
    for (u32 index = 0; index < kMaxRetargetProfiles; ++index) {
        retargets.profiles[index] =
            profile(index + 1, index < 8 ? 4 : 0, index % 2 == 0);
    }
    expect(plan_retargets(retargets, plan, diagnostic) == SkeletalError::None,
           "capacity retargets");
    expect(plan.profile_count == kMaxRetargetProfiles
               && plan.total_pair_count == 32
               && plan.enabled_count == kMaxRetargetProfiles / 2,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim04_retarget_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "ret01") { success = run_ret01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
