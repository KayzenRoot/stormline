#include "stormline/animation/skeletal/ragdoll_plan.hpp"

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

RagdollProfileDesc profile(u32 id, bool auto_activate, bool enabled) {
    RagdollProfileDesc desc{};
    desc.ragdoll_id = id;
    desc.revision = 1;
    desc.body_mapping_id = 100 + id;
    desc.constraint_mapping_id = 200 + id;
    desc.activation_weight = 0.75f;
    desc.auto_activate = auto_activate;
    desc.enabled = enabled;
    return desc;
}

RagdollSetDesc ragdoll_set() {
    RagdollSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.profile_count = 3;
    desc.profiles[0] = profile(1, true, true);
    desc.profiles[1] = profile(2, false, false);
    desc.profiles[2] = profile(3, true, true);
    return desc;
}

bool run_rag01() {
    begin();
    RagdollSetDesc ragdolls = ragdoll_set();
    RagdollPlan plan{};
    SkeletalDiagnostic diagnostic{};
    expect(plan_ragdolls(ragdolls, plan, diagnostic) == SkeletalError::None,
           "valid ragdolls");
    expect(plan.profile_count == 3 && plan.auto_count == 2
               && plan.enabled_count == 2,
           "valid plan");
    expect(diagnostic.code == SkeletalError::None, "success diagnostic");

    RagdollPlan repeat{};
    expect(plan_ragdolls(ragdolls, repeat, diagnostic) == SkeletalError::None,
           "repeat ragdolls");
    expect(repeat.auto_count == plan.auto_count, "deterministic plan");

    ragdolls.owner_id = 0;
    expect(plan_ragdolls(ragdolls, plan, diagnostic)
               == SkeletalError::InvalidArgument,
           "zero owner");
    expect(plan.profile_count == 0, "reset on zero owner");
    ragdolls = ragdoll_set();
    ragdolls.revision = 0;
    expect(plan_ragdolls(ragdolls, plan, diagnostic)
               == SkeletalError::InvalidArgument,
           "zero revision");
    ragdolls = ragdoll_set();
    ragdolls.profile_count = kMaxRagdollProfiles + 1;
    expect(plan_ragdolls(ragdolls, plan, diagnostic)
               == SkeletalError::CapacityFull,
           "profile overflow");

    ragdolls = ragdoll_set();
    ragdolls.profiles[1].ragdoll_id = 0;
    expect(plan_ragdolls(ragdolls, plan, diagnostic)
               == SkeletalError::RagdollInvalid,
           "zero ragdoll id");
    expect(diagnostic.index == 1, "zero ragdoll diagnostic");
    ragdolls = ragdoll_set();
    ragdolls.profiles[1].revision = 0;
    expect(plan_ragdolls(ragdolls, plan, diagnostic)
               == SkeletalError::RagdollInvalid,
           "zero revision");
    ragdolls = ragdoll_set();
    ragdolls.profiles[1].body_mapping_id = 0;
    expect(plan_ragdolls(ragdolls, plan, diagnostic)
               == SkeletalError::RagdollInvalid,
           "zero body mapping");
    ragdolls = ragdoll_set();
    ragdolls.profiles[1].constraint_mapping_id = 0;
    expect(plan_ragdolls(ragdolls, plan, diagnostic)
               == SkeletalError::RagdollInvalid,
           "zero constraint mapping");
    ragdolls = ragdoll_set();
    ragdolls.profiles[1].activation_weight = 1.5f;
    expect(plan_ragdolls(ragdolls, plan, diagnostic)
               == SkeletalError::OutOfRange,
           "weight above one");
    ragdolls = ragdoll_set();
    ragdolls.profiles[1].activation_weight =
        std::numeric_limits<f32>::quiet_NaN();
    expect(plan_ragdolls(ragdolls, plan, diagnostic)
               == SkeletalError::OutOfRange,
           "non-finite weight");
    ragdolls = ragdoll_set();
    ragdolls.profiles[2].ragdoll_id = 1;
    expect(plan_ragdolls(ragdolls, plan, diagnostic)
               == SkeletalError::DuplicateId,
           "duplicate ragdoll");
    expect(diagnostic.index == 2, "duplicate ragdoll diagnostic");

    ragdolls = ragdoll_set();
    ragdolls.profile_count = kMaxRagdollProfiles;
    for (u32 index = 0; index < kMaxRagdollProfiles; ++index) {
        ragdolls.profiles[index] =
            profile(index + 1, index % 2 == 0, index % 3 != 0);
    }
    expect(plan_ragdolls(ragdolls, plan, diagnostic) == SkeletalError::None,
           "capacity ragdolls");
    expect(plan.profile_count == kMaxRagdollProfiles
               && plan.auto_count == kMaxRagdollProfiles / 2,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim04_ragdoll_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "rag01") { success = run_rag01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
