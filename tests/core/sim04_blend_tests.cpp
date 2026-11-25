#include "stormline/animation/skeletal/blend_tree_plan.hpp"

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

BlendNodeDesc node(u32 id, BlendKind kind, bool enabled) {
    BlendNodeDesc desc{};
    desc.node_id = id;
    desc.revision = 1;
    desc.kind = kind;
    desc.weight = 0.5f;
    desc.threshold = 0.25f;
    desc.enabled = enabled;
    return desc;
}

BlendSetDesc blend_set() {
    BlendSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.node_count = 3;
    desc.nodes[0] = node(1, BlendKind::Lerp, true);
    desc.nodes[1] = node(2, BlendKind::Additive, false);
    desc.nodes[2] = node(3, BlendKind::Blend1D, true);
    return desc;
}

bool run_blend01() {
    begin();
    BlendSetDesc blends = blend_set();
    BlendPlan plan{};
    SkeletalDiagnostic diagnostic{};
    expect(plan_blends(blends, plan, diagnostic) == SkeletalError::None,
           "valid blends");
    expect(plan.node_count == 3 && plan.lerp_count == 1
               && plan.additive_count == 1 && plan.blend_1d_count == 1
               && plan.enabled_count == 2,
           "valid plan");
    expect(diagnostic.code == SkeletalError::None, "success diagnostic");

    BlendPlan repeat{};
    expect(plan_blends(blends, repeat, diagnostic) == SkeletalError::None,
           "repeat blends");
    expect(repeat.enabled_count == plan.enabled_count, "deterministic plan");

    blends.owner_id = 0;
    expect(plan_blends(blends, plan, diagnostic)
               == SkeletalError::InvalidArgument,
           "zero owner");
    expect(plan.node_count == 0, "reset on zero owner");
    blends = blend_set();
    blends.revision = 0;
    expect(plan_blends(blends, plan, diagnostic)
               == SkeletalError::InvalidArgument,
           "zero revision");
    blends = blend_set();
    blends.node_count = kMaxBlendNodes + 1;
    expect(plan_blends(blends, plan, diagnostic)
               == SkeletalError::CapacityFull,
           "node overflow");

    blends = blend_set();
    blends.nodes[1].node_id = 0;
    expect(plan_blends(blends, plan, diagnostic)
               == SkeletalError::BlendInvalid,
           "zero node id");
    expect(diagnostic.index == 1, "zero node diagnostic");
    blends = blend_set();
    blends.nodes[1].revision = 0;
    expect(plan_blends(blends, plan, diagnostic)
               == SkeletalError::BlendInvalid,
           "zero revision");
    blends = blend_set();
    blends.nodes[1].kind = static_cast<BlendKind>(9);
    expect(plan_blends(blends, plan, diagnostic)
               == SkeletalError::BlendInvalid,
           "invalid kind");

    blends = blend_set();
    blends.nodes[1].weight = 1.5f;
    expect(plan_blends(blends, plan, diagnostic)
               == SkeletalError::OutOfRange,
           "weight above one");
    blends = blend_set();
    blends.nodes[1].threshold = -0.5f;
    expect(plan_blends(blends, plan, diagnostic)
               == SkeletalError::OutOfRange,
           "negative threshold");
    blends = blend_set();
    blends.nodes[1].weight = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_blends(blends, plan, diagnostic)
               == SkeletalError::OutOfRange,
           "non-finite weight");
    blends = blend_set();
    blends.nodes[2].node_id = 1;
    expect(plan_blends(blends, plan, diagnostic)
               == SkeletalError::DuplicateId,
           "duplicate node");
    expect(diagnostic.index == 2, "duplicate node diagnostic");

    blends = blend_set();
    blends.node_count = kMaxBlendNodes;
    for (u32 index = 0; index < kMaxBlendNodes; ++index) {
        blends.nodes[index] = node(index + 1,
                                   static_cast<BlendKind>(index % 5),
                                   index % 2 == 0);
    }
    expect(plan_blends(blends, plan, diagnostic) == SkeletalError::None,
           "capacity blends");
    expect(plan.node_count == kMaxBlendNodes
               && plan.enabled_count == kMaxBlendNodes / 2,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim04_blend_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "blend01") { success = run_blend01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
