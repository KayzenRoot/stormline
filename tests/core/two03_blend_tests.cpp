#include "stormline/animation/blend_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::animation;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool near(f32 left, f32 right) {
    const f32 difference = left > right ? left - right : right - left;
    return difference <= 0.000001f;
}

BlendClipDesc clip(u32 id, f32 weight) {
    BlendClipDesc desc{};
    desc.clip_id = id;
    desc.revision = 1;
    desc.weight = weight;
    return desc;
}

bool run_bld01() {
    begin();
    BlendDesc blend{};
    blend.blend_id = 11;
    blend.revision = 2;
    blend.clip_count = 3;
    blend.clips[0] = clip(1, 1.0f);
    blend.clips[1] = clip(2, 1.0f);
    blend.clips[2] = clip(3, 2.0f);
    BlendPlan plan{};
    AnimationDiagnostic diagnostic{};

    expect(plan_blend(blend, plan, diagnostic) == AnimationError::None,
           "valid blend");
    expect(plan.clip_count == 3 && near(plan.normalized_weights[0], 0.25f)
               && near(plan.normalized_weights[1], 0.25f)
               && near(plan.normalized_weights[2], 0.5f),
           "valid normalized weights");
    BlendPlan repeat{};
    expect(plan_blend(blend, repeat, diagnostic) == AnimationError::None,
           "repeat blend");
    expect(plan.normalized_weights == repeat.normalized_weights,
           "deterministic weights");

    blend.clip_count = 0;
    expect(plan_blend(blend, plan, diagnostic)
               == AnimationError::BlendInvalid,
           "empty blend");
    expect(plan.clip_count == 0 && near(plan.normalized_weights[0], 0.0f),
           "reset on empty");

    blend.clip_count = kMaxBlendClips + 1;
    expect(plan_blend(blend, plan, diagnostic)
               == AnimationError::BlendInvalid,
           "over capacity");

    blend.clip_count = 2;
    blend.blend_id = 0;
    expect(plan_blend(blend, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero blend");
    blend.blend_id = 11;
    blend.revision = 0;
    expect(plan_blend(blend, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero revision");
    blend.revision = 1;

    blend.clips[0] = clip(0, 1.0f);
    expect(plan_blend(blend, plan, diagnostic)
               == AnimationError::BlendInvalid,
           "zero clip id");
    expect(diagnostic.index == 0 && diagnostic.source_id == 11,
           "clip diagnostic");
    blend.clips[0] = clip(1, 1.0f);
    blend.clips[0].revision = 0;
    expect(plan_blend(blend, plan, diagnostic)
               == AnimationError::BlendInvalid,
           "zero clip revision");
    blend.clips[0].revision = 1;

    blend.clips[0].weight = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_blend(blend, plan, diagnostic)
               == AnimationError::NonFiniteValue,
           "nan weight");
    blend.clips[0].weight = std::numeric_limits<f32>::infinity();
    expect(plan_blend(blend, plan, diagnostic)
               == AnimationError::NonFiniteValue,
           "infinite weight");
    blend.clips[0].weight = -1.0f;
    expect(plan_blend(blend, plan, diagnostic)
               == AnimationError::BlendInvalid,
           "negative weight");

    blend.clips[0] = clip(1, 0.0f);
    blend.clips[1] = clip(2, 0.0f);
    expect(plan_blend(blend, plan, diagnostic)
               == AnimationError::BlendInvalid,
           "zero total");
    blend.clips[0] = clip(1, 1.0f);
    blend.clips[1] = clip(1, 1.0f);
    expect(plan_blend(blend, plan, diagnostic)
               == AnimationError::DuplicateId,
           "duplicate clip id");
    expect(diagnostic.index == 1, "duplicate index");

    blend.clips[1] = clip(2, 1.0f);
    blend.additive = true;
    blend.discrete_targets = false;
    expect(plan_blend(blend, plan, diagnostic)
               == AnimationError::BlendInvalid,
           "additive continuous");
    blend.discrete_targets = true;
    expect(plan_blend(blend, plan, diagnostic) == AnimationError::None,
           "additive discrete");

    blend.additive = false;
    blend.discrete_targets = false;
    blend.clip_count = kMaxBlendClips;
    for (u32 index = 0; index < kMaxBlendClips; ++index) {
        blend.clips[index] = clip(index + 1, 1.0f);
    }
    expect(plan_blend(blend, plan, diagnostic) == AnimationError::None,
           "capacity blend");
    expect(plan.clip_count == kMaxBlendClips
               && near(plan.normalized_weights[0], 0.25f)
               && near(plan.normalized_weights[3], 0.25f),
           "capacity weights");

    const f32 maximum = std::numeric_limits<f32>::max();
    for (u32 index = 0; index < kMaxBlendClips; ++index) {
        blend.clips[index] = clip(index + 1, maximum);
    }
    expect(plan_blend(blend, plan, diagnostic) == AnimationError::None,
           "large weights");
    expect(near(plan.normalized_weights[0], 0.25f)
               && near(plan.normalized_weights[3], 0.25f),
           "large normalized weights");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two03_blend_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "bld01") { success = run_bld01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
