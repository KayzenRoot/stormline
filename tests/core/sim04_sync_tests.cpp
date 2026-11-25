#include "stormline/animation/skeletal/sync_plan.hpp"

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

SyncGroupDesc group(u32 id, f32 phase, bool enabled) {
    SyncGroupDesc desc{};
    desc.group_id = id;
    desc.revision = 1;
    desc.leader_id = 100 + id;
    desc.member_count = 2;
    desc.phase = phase;
    desc.enabled = enabled;
    return desc;
}

SyncSetDesc sync_set() {
    SyncSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.group_count = 3;
    desc.groups[0] = group(1, 0.0f, true);
    desc.groups[1] = group(2, 0.25f, false);
    desc.groups[2] = group(3, 0.5f, true);
    return desc;
}

bool run_sync01() {
    begin();
    SyncSetDesc sync = sync_set();
    SyncPlan plan{};
    SkeletalDiagnostic diagnostic{};
    expect(plan_sync(sync, plan, diagnostic) == SkeletalError::None,
           "valid sync");
    expect(plan.group_count == 3 && plan.phased_count == 2
               && plan.enabled_count == 2,
           "valid plan");
    expect(diagnostic.code == SkeletalError::None, "success diagnostic");

    SyncPlan repeat{};
    expect(plan_sync(sync, repeat, diagnostic) == SkeletalError::None,
           "repeat sync");
    expect(repeat.phased_count == plan.phased_count, "deterministic plan");

    sync.owner_id = 0;
    expect(plan_sync(sync, plan, diagnostic) == SkeletalError::InvalidArgument,
           "zero owner");
    expect(plan.group_count == 0, "reset on zero owner");
    sync = sync_set();
    sync.revision = 0;
    expect(plan_sync(sync, plan, diagnostic) == SkeletalError::InvalidArgument,
           "zero revision");
    sync = sync_set();
    sync.group_count = kMaxSyncGroups + 1;
    expect(plan_sync(sync, plan, diagnostic) == SkeletalError::CapacityFull,
           "group overflow");

    sync = sync_set();
    sync.groups[1].group_id = 0;
    expect(plan_sync(sync, plan, diagnostic) == SkeletalError::SyncInvalid,
           "zero group id");
    expect(diagnostic.index == 1, "zero group diagnostic");
    sync = sync_set();
    sync.groups[1].revision = 0;
    expect(plan_sync(sync, plan, diagnostic) == SkeletalError::SyncInvalid,
           "zero revision");
    sync = sync_set();
    sync.groups[1].leader_id = 0;
    expect(plan_sync(sync, plan, diagnostic) == SkeletalError::SyncInvalid,
           "zero leader");
    sync = sync_set();
    sync.groups[1].member_count = 0;
    expect(plan_sync(sync, plan, diagnostic) == SkeletalError::OutOfRange,
           "zero members");
    sync = sync_set();
    sync.groups[1].member_count = 33;
    expect(plan_sync(sync, plan, diagnostic) == SkeletalError::OutOfRange,
           "member overflow");
    sync = sync_set();
    sync.groups[1].phase = 1.5f;
    expect(plan_sync(sync, plan, diagnostic) == SkeletalError::OutOfRange,
           "phase above one");
    sync = sync_set();
    sync.groups[1].phase = -0.1f;
    expect(plan_sync(sync, plan, diagnostic) == SkeletalError::OutOfRange,
           "negative phase");
    sync = sync_set();
    sync.groups[1].phase = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_sync(sync, plan, diagnostic) == SkeletalError::OutOfRange,
           "non-finite phase");
    sync = sync_set();
    sync.groups[2].group_id = 1;
    expect(plan_sync(sync, plan, diagnostic) == SkeletalError::DuplicateId,
           "duplicate group");
    expect(diagnostic.index == 2, "duplicate group diagnostic");

    sync = sync_set();
    sync.group_count = kMaxSyncGroups;
    for (u32 index = 0; index < kMaxSyncGroups; ++index) {
        sync.groups[index] =
            group(index + 1, (index % 4) * 0.25f, index % 2 == 0);
    }
    expect(plan_sync(sync, plan, diagnostic) == SkeletalError::None,
           "capacity sync");
    expect(plan.group_count == kMaxSyncGroups
               && plan.phased_count == kMaxSyncGroups - kMaxSyncGroups / 4
               && plan.enabled_count == kMaxSyncGroups / 2,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim04_sync_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "sync01") { success = run_sync01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
