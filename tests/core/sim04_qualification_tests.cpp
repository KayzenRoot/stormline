#include "stormline/animation/skeletal/retarget_plan.hpp"
#include "stormline/animation/skeletal/blend_tree_plan.hpp"
#include "stormline/animation/skeletal/ik_plan.hpp"
#include "stormline/animation/skeletal/ragdoll_plan.hpp"
#include "stormline/animation/skeletal/compression_plan.hpp"
#include "stormline/animation/skeletal/sync_plan.hpp"

#include <cstdio>
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

struct Plans {
    RetargetPlan retargets{};
    BlendPlan blends{};
    IkPlan ik{};
    RagdollPlan ragdolls{};
    CompressionPlan compression{};
    SyncPlan sync{};
    SkeletalDiagnostic diagnostic{};
};

RetargetProfileDesc make_retarget(u32 id, u32 pairs, bool enabled) {
    RetargetProfileDesc desc{};
    desc.retarget_id = id;
    desc.revision = 1;
    desc.bind_scale = 1.0f;
    desc.pair_count = pairs;
    for (u32 index = 0; index < pairs; ++index) {
        desc.pairs[index] = RetargetJointPair{index + 1, index + 101};
    }
    desc.enabled = enabled;
    return desc;
}

RetargetSetDesc make_retargets() {
    RetargetSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.profile_count = 2;
    desc.profiles[0] = make_retarget(1, 3, true);
    desc.profiles[1] = make_retarget(2, 2, false);
    return desc;
}

BlendNodeDesc make_blend(u32 id, BlendKind kind, bool enabled) {
    BlendNodeDesc desc{};
    desc.node_id = id;
    desc.revision = 1;
    desc.kind = kind;
    desc.weight = 0.5f;
    desc.threshold = 0.25f;
    desc.enabled = enabled;
    return desc;
}

BlendSetDesc make_blends() {
    BlendSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.node_count = 3;
    desc.nodes[0] = make_blend(1, BlendKind::Lerp, true);
    desc.nodes[1] = make_blend(2, BlendKind::Additive, false);
    desc.nodes[2] = make_blend(3, BlendKind::Blend1D, true);
    return desc;
}

IkChainDesc make_ik(u32 id, u32 bones, u32 iterations, bool enabled) {
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

IkSetDesc make_ik_set() {
    IkSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.chain_count = 3;
    desc.chains[0] = make_ik(1, 3, 16, true);
    desc.chains[1] = make_ik(2, 2, 8, false);
    desc.chains[2] = make_ik(3, 4, 32, true);
    return desc;
}

RagdollProfileDesc make_ragdoll(u32 id, bool auto_activate, bool enabled) {
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

RagdollSetDesc make_ragdolls() {
    RagdollSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.profile_count = 3;
    desc.profiles[0] = make_ragdoll(1, true, true);
    desc.profiles[1] = make_ragdoll(2, false, false);
    desc.profiles[2] = make_ragdoll(3, true, true);
    return desc;
}

CompressionProfileDesc make_compression(u32 id, bool lossless,
                                        bool enabled) {
    CompressionProfileDesc desc{};
    desc.profile_id = id;
    desc.revision = 1;
    desc.translation_bits = 16;
    desc.rotation_bits = 16;
    desc.scale_bits = 8;
    desc.keyframe_interval = 8;
    desc.lossless = lossless;
    desc.enabled = enabled;
    return desc;
}

CompressionSetDesc make_compressions() {
    CompressionSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.profile_count = 3;
    desc.profiles[0] = make_compression(1, true, true);
    desc.profiles[1] = make_compression(2, false, false);
    desc.profiles[2] = make_compression(3, false, true);
    return desc;
}

SyncGroupDesc make_sync(u32 id, f32 phase, bool enabled) {
    SyncGroupDesc desc{};
    desc.group_id = id;
    desc.revision = 1;
    desc.leader_id = 100 + id;
    desc.member_count = 2;
    desc.phase = phase;
    desc.enabled = enabled;
    return desc;
}

SyncSetDesc make_syncs() {
    SyncSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.group_count = 3;
    desc.groups[0] = make_sync(1, 0.0f, true);
    desc.groups[1] = make_sync(2, 0.25f, false);
    desc.groups[2] = make_sync(3, 0.5f, true);
    return desc;
}

bool plan_all(const RetargetSetDesc& retargets, const BlendSetDesc& blends,
              const IkSetDesc& ik, const RagdollSetDesc& ragdolls,
              const CompressionSetDesc& compression, const SyncSetDesc& sync,
              Plans& plans) {
    return plan_retargets(retargets, plans.retargets, plans.diagnostic)
               == SkeletalError::None
           && plan_blends(blends, plans.blends, plans.diagnostic)
               == SkeletalError::None
           && plan_ik(ik, plans.ik, plans.diagnostic)
               == SkeletalError::None
           && plan_ragdolls(ragdolls, plans.ragdolls, plans.diagnostic)
               == SkeletalError::None
           && plan_compression(compression, plans.compression,
                               plans.diagnostic)
               == SkeletalError::None
           && plan_sync(sync, plans.sync, plans.diagnostic)
               == SkeletalError::None;
}

bool plan_default(Plans& plans) {
    return plan_all(make_retargets(), make_blends(), make_ik_set(),
                    make_ragdolls(), make_compressions(), make_syncs(),
                    plans);
}

bool run_qlfs401() {
    begin();
    Plans plans{};
    expect(plan_default(plans), "integrated plans");
    expect(plans.retargets.profile_count == 2
               && plans.retargets.total_pair_count == 5
               && plans.retargets.enabled_count == 1,
           "retarget plan");
    expect(plans.blends.node_count == 3 && plans.blends.lerp_count == 1
               && plans.blends.additive_count == 1
               && plans.blends.blend_1d_count == 1
               && plans.blends.enabled_count == 2,
           "blend plan");
    expect(plans.ik.chain_count == 3 && plans.ik.total_bone_count == 9
               && plans.ik.max_iterations == 32
               && plans.ik.enabled_count == 2,
           "ik plan");
    expect(plans.ragdolls.profile_count == 3
               && plans.ragdolls.auto_count == 2
               && plans.ragdolls.enabled_count == 2,
           "ragdoll plan");
    expect(plans.compression.profile_count == 3
               && plans.compression.lossless_count == 1
               && plans.compression.enabled_count == 2,
           "compression plan");
    expect(plans.sync.group_count == 3 && plans.sync.phased_count == 2
               && plans.sync.enabled_count == 2,
           "sync plan");
    expect(plans.diagnostic.code == SkeletalError::None,
           "integrated diagnostic");
    return finish();
}

bool run_qlfs402() {
    begin();
    Plans first{};
    expect(plan_default(first), "deterministic first");
    for (u32 attempt = 0; attempt < 100; ++attempt) {
        Plans repeat{};
        expect(plan_default(repeat), "deterministic repeat success");
        expect(repeat.retargets.total_pair_count
                   == first.retargets.total_pair_count,
               "retargets identical");
        expect(repeat.blends.enabled_count == first.blends.enabled_count,
               "blends identical");
        expect(repeat.ik.max_iterations == first.ik.max_iterations,
               "ik identical");
        expect(repeat.ragdolls.auto_count == first.ragdolls.auto_count,
               "ragdolls identical");
        expect(repeat.compression.lossless_count
                   == first.compression.lossless_count,
               "compression identical");
        expect(repeat.sync.phased_count == first.sync.phased_count,
               "sync identical");
    }
    return finish();
}

bool run_qlfs403() {
    begin();
    Plans plans{};

    RetargetSetDesc retargets = make_retargets();
    retargets.profiles[1].retarget_id = 1;
    expect(plan_retargets(retargets, plans.retargets, plans.diagnostic)
               == SkeletalError::DuplicateId,
           "retarget failure");
    expect(plans.retargets.profile_count == 0, "retarget reset");
    expect(plan_retargets(make_retargets(), plans.retargets, plans.diagnostic)
               == SkeletalError::None,
           "retarget recovery");

    BlendSetDesc blends = make_blends();
    blends.nodes[2].node_id = 1;
    expect(plan_blends(blends, plans.blends, plans.diagnostic)
               == SkeletalError::DuplicateId,
           "blend failure");
    expect(plans.blends.node_count == 0, "blend reset");
    expect(plan_blends(make_blends(), plans.blends, plans.diagnostic)
               == SkeletalError::None,
           "blend recovery");

    IkSetDesc ik = make_ik_set();
    ik.chains[2].chain_id = 1;
    expect(plan_ik(ik, plans.ik, plans.diagnostic)
               == SkeletalError::DuplicateId,
           "ik failure");
    expect(plans.ik.chain_count == 0, "ik reset");
    expect(plan_ik(make_ik_set(), plans.ik, plans.diagnostic)
               == SkeletalError::None,
           "ik recovery");

    RagdollSetDesc ragdolls = make_ragdolls();
    ragdolls.profiles[2].ragdoll_id = 1;
    expect(plan_ragdolls(ragdolls, plans.ragdolls, plans.diagnostic)
               == SkeletalError::DuplicateId,
           "ragdoll failure");
    expect(plans.ragdolls.profile_count == 0, "ragdoll reset");
    expect(plan_ragdolls(make_ragdolls(), plans.ragdolls, plans.diagnostic)
               == SkeletalError::None,
           "ragdoll recovery");

    CompressionSetDesc compression = make_compressions();
    compression.profiles[2].profile_id = 1;
    expect(plan_compression(compression, plans.compression,
                            plans.diagnostic)
               == SkeletalError::DuplicateId,
           "compression failure");
    expect(plans.compression.profile_count == 0, "compression reset");
    expect(plan_compression(make_compressions(), plans.compression,
                            plans.diagnostic)
               == SkeletalError::None,
           "compression recovery");

    SyncSetDesc sync = make_syncs();
    sync.groups[2].group_id = 1;
    expect(plan_sync(sync, plans.sync, plans.diagnostic)
               == SkeletalError::DuplicateId,
           "sync failure");
    expect(plans.sync.group_count == 0, "sync reset");
    expect(plan_sync(make_syncs(), plans.sync, plans.diagnostic)
               == SkeletalError::None,
           "sync recovery");
    return finish();
}

bool run_qlfs404() {
    begin();
    Plans plans{};
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        RetargetSetDesc retargets = make_retargets();
        retargets.profile_count = kMaxRetargetProfiles;
        for (u32 index = 0; index < kMaxRetargetProfiles; ++index) {
            retargets.profiles[index] =
                make_retarget(index + 1, index < 8 ? 4 : 0, index % 2 == 0);
        }
        expect(plan_retargets(retargets, plans.retargets, plans.diagnostic)
                   == SkeletalError::None,
               "overload retargets");
        expect(plans.retargets.total_pair_count <= 32, "retarget pair cap");

        BlendSetDesc blends = make_blends();
        blends.node_count = kMaxBlendNodes;
        for (u32 index = 0; index < kMaxBlendNodes; ++index) {
            blends.nodes[index] =
                make_blend(index + 1, static_cast<BlendKind>(index % 5),
                           index % 2 == 0);
        }
        expect(plan_blends(blends, plans.blends, plans.diagnostic)
                   == SkeletalError::None,
               "overload blends");
        expect(plans.blends.node_count <= kMaxBlendNodes, "blend cap");

        IkSetDesc ik = make_ik_set();
        ik.chain_count = kMaxIkChains;
        for (u32 index = 0; index < kMaxIkChains; ++index) {
            ik.chains[index] =
                make_ik(index + 1, 1 + index % 16, index % 65,
                        index % 2 == 0);
        }
        expect(plan_ik(ik, plans.ik, plans.diagnostic)
                   == SkeletalError::None,
               "overload ik");
        expect(plans.ik.chain_count <= kMaxIkChains, "ik cap");

        RagdollSetDesc ragdolls = make_ragdolls();
        ragdolls.profile_count = kMaxRagdollProfiles;
        for (u32 index = 0; index < kMaxRagdollProfiles; ++index) {
            ragdolls.profiles[index] =
                make_ragdoll(index + 1, index % 2 == 0, index % 3 != 0);
        }
        expect(plan_ragdolls(ragdolls, plans.ragdolls, plans.diagnostic)
                   == SkeletalError::None,
               "overload ragdolls");
        expect(plans.ragdolls.profile_count <= kMaxRagdollProfiles,
               "ragdoll cap");

        CompressionSetDesc compression = make_compressions();
        compression.profile_count = kMaxCompressionProfiles;
        for (u32 index = 0; index < kMaxCompressionProfiles; ++index) {
            compression.profiles[index] = make_compression(
                index + 1, index % 3 == 0, index % 2 == 0);
        }
        expect(plan_compression(compression, plans.compression,
                                plans.diagnostic)
                   == SkeletalError::None,
               "overload compression");
        expect(plans.compression.profile_count <= kMaxCompressionProfiles,
               "compression cap");

        SyncSetDesc sync = make_syncs();
        sync.group_count = kMaxSyncGroups;
        for (u32 index = 0; index < kMaxSyncGroups; ++index) {
            sync.groups[index] =
                make_sync(index + 1, static_cast<f32>(index % 4) * 0.25f,
                          index % 2 == 0);
        }
        expect(plan_sync(sync, plans.sync, plans.diagnostic)
                   == SkeletalError::None,
               "overload sync");
        expect(plans.sync.group_count <= kMaxSyncGroups, "sync cap");
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_sim04_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlfs401") { success = run_qlfs401(); }
    else if (mode == "qlfs402") { success = run_qlfs402(); }
    else if (mode == "qlfs403") { success = run_qlfs403(); }
    else if (mode == "qlfs404") { success = run_qlfs404(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
