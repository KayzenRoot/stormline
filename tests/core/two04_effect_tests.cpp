#include "stormline/hybrid/effect_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::hybrid;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

HybridEffectDesc effect(u32 id, u32 layer) {
    HybridEffectDesc desc{};
    desc.effect_id = id;
    desc.revision = 1;
    desc.layer_id = layer;
    return desc;
}

HybridEffectSetDesc scene() {
    HybridEffectSetDesc desc{};
    desc.scene_id = 60;
    desc.revision = 1;
    desc.effect_count = 3;
    desc.effects[0] = effect(1, 10);
    desc.effects[0].lit = true;
    desc.effects[1] = effect(2, 11);
    desc.effects[1].shadow_proxy = true;
    desc.effects[1].subview_width = 512;
    desc.effects[1].subview_height = 256;
    desc.effects[1].subview_depth = 2;
    desc.effects[2] = effect(3, 12);
    desc.effects[2].lit = true;
    desc.effects[2].shadow_proxy = true;
    desc.effects[2].subview_width = 64;
    desc.effects[2].subview_height = 64;
    desc.effects[2].subview_depth = 1;
    desc.effects[2].fallback = FallbackReason::BudgetExceeded;
    return desc;
}

bool run_efe01() {
    begin();
    HybridEffectSetDesc effects = scene();
    HybridEffectPlan plan{};
    HybridDiagnostic diagnostic{};

    expect(plan_effects(effects, plan, diagnostic) == HybridError::None,
           "valid effects");
    expect(plan.effect_count == 3 && plan.lit_count == 2
               && plan.shadow_count == 2 && plan.subview_count == 2
               && plan.max_subview_depth == 2,
           "valid plan");
    HybridEffectPlan repeat{};
    expect(plan_effects(effects, repeat, diagnostic) == HybridError::None,
           "repeat effects");
    expect(plan.effect_count == repeat.effect_count
               && plan.lit_count == repeat.lit_count
               && plan.shadow_count == repeat.shadow_count
               && plan.subview_count == repeat.subview_count
               && plan.max_subview_depth == repeat.max_subview_depth,
           "deterministic plan");

    effects.effect_count = 0;
    expect(plan_effects(effects, plan, diagnostic) == HybridError::None,
           "empty effects");
    expect(plan.effect_count == 0 && plan.lit_count == 0
               && plan.shadow_count == 0 && plan.subview_count == 0
               && plan.max_subview_depth == 0,
           "empty plan");
    effects.effect_count = kMaxHybridEffects + 1;
    expect(plan_effects(effects, plan, diagnostic)
               == HybridError::EffectInvalid,
           "effect overflow");

    effects = scene();
    effects.scene_id = 0;
    expect(plan_effects(effects, plan, diagnostic)
               == HybridError::InvalidArgument,
           "zero scene");
    effects = scene();
    effects.revision = 0;
    expect(plan_effects(effects, plan, diagnostic)
               == HybridError::InvalidArgument,
           "zero scene revision");

    effects = scene();
    effects.effects[0].effect_id = 0;
    expect(plan_effects(effects, plan, diagnostic)
               == HybridError::EffectInvalid,
           "zero effect id");
    effects = scene();
    effects.effects[0].revision = 0;
    expect(plan_effects(effects, plan, diagnostic)
               == HybridError::EffectInvalid,
           "zero effect revision");
    effects = scene();
    effects.effects[0].layer_id = 0;
    expect(plan_effects(effects, plan, diagnostic)
               == HybridError::EffectInvalid,
           "zero layer id");
    effects = scene();
    effects.effects[0].fallback = static_cast<FallbackReason>(200);
    expect(plan_effects(effects, plan, diagnostic)
               == HybridError::EffectInvalid,
           "invalid fallback");
    effects = scene();
    effects.effects[1].effect_id = 1;
    expect(plan_effects(effects, plan, diagnostic)
               == HybridError::DuplicateId,
           "duplicate effect id");

    effects = scene();
    effects.effects[1].subview_height = 0;
    expect(plan_effects(effects, plan, diagnostic)
               == HybridError::EffectInvalid,
           "width without height");
    effects = scene();
    effects.effects[1].subview_width = 0;
    expect(plan_effects(effects, plan, diagnostic)
               == HybridError::EffectInvalid,
           "height without width");
    effects = scene();
    effects.effects[1].subview_width = kMaxSubviewExtent + 1;
    expect(plan_effects(effects, plan, diagnostic)
               == HybridError::OutOfRange,
           "width overflow");
    effects = scene();
    effects.effects[1].subview_height = kMaxSubviewExtent + 1;
    expect(plan_effects(effects, plan, diagnostic)
               == HybridError::OutOfRange,
           "height overflow");
    effects = scene();
    effects.effects[1].subview_depth = kMaxSubviewDepth + 1;
    expect(plan_effects(effects, plan, diagnostic)
               == HybridError::DepthExceeded,
           "depth overflow");
    effects = scene();
    effects.effects[2].subview_width = 0;
    effects.effects[2].subview_height = 0;
    expect(plan_effects(effects, plan, diagnostic)
               == HybridError::EffectInvalid,
           "depth without extent");
    expect(plan.effect_count == 0 && plan.lit_count == 0,
           "reset on failure");

    effects = scene();
    effects.effects[1].subview_width = kMaxSubviewExtent;
    effects.effects[1].subview_height = kMaxSubviewExtent;
    effects.effects[1].subview_depth = kMaxSubviewDepth;
    expect(plan_effects(effects, plan, diagnostic) == HybridError::None,
           "max subview");
    expect(plan.max_subview_depth == kMaxSubviewDepth, "max subview depth");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two04_effect_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "efe01") { success = run_efe01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
