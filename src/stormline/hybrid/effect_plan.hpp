#ifndef STORMLINE_HYBRID_EFFECT_PLAN_HPP
#define STORMLINE_HYBRID_EFFECT_PLAN_HPP

#include <array>

#include "stormline/hybrid/hybrid_types.hpp"

namespace stormline::hybrid {

struct HybridEffectDesc {
    u32 effect_id{0};
    u32 revision{0};
    u32 layer_id{0};
    bool lit{false};
    bool shadow_proxy{false};
    u32 subview_width{0};
    u32 subview_height{0};
    u32 subview_depth{0};
    FallbackReason fallback{FallbackReason::None};
};

struct HybridEffectSetDesc {
    u32 scene_id{0};
    u32 revision{0};
    u32 effect_count{0};
    std::array<HybridEffectDesc, kMaxHybridEffects> effects{};
};

struct HybridEffectPlan {
    u32 effect_count{0};
    u32 lit_count{0};
    u32 shadow_count{0};
    u32 subview_count{0};
    u32 max_subview_depth{0};
};

[[nodiscard]] inline HybridError plan_effects(
    const HybridEffectSetDesc& effects, HybridEffectPlan& plan,
    HybridDiagnostic& diagnostic) noexcept {
    plan = HybridEffectPlan{};
    diagnostic = HybridDiagnostic{};
    if (effects.scene_id == 0 || effects.revision == 0) {
        return detail::set_hybrid_error(
            diagnostic, HybridError::InvalidArgument, effects.scene_id, 0);
    }
    if (effects.effect_count > kMaxHybridEffects) {
        return detail::set_hybrid_error(
            diagnostic, HybridError::EffectInvalid, effects.scene_id, 0);
    }
    HybridEffectPlan computed{};
    computed.effect_count = effects.effect_count;
    for (u32 index = 0; index < effects.effect_count; ++index) {
        const HybridEffectDesc& effect = effects.effects[index];
        if (effect.effect_id == 0 || effect.revision == 0
            || effect.layer_id == 0
            || !detail::valid_fallback(effect.fallback)) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::EffectInvalid, effects.scene_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (effects.effects[previous].effect_id == effect.effect_id) {
                return detail::set_hybrid_error(
                    diagnostic, HybridError::DuplicateId, effects.scene_id,
                    index);
            }
        }
        if ((effect.subview_width == 0) != (effect.subview_height == 0)) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::EffectInvalid, effects.scene_id,
                index);
        }
        if (effect.subview_width > kMaxSubviewExtent
            || effect.subview_height > kMaxSubviewExtent) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::OutOfRange, effects.scene_id, index);
        }
        if (effect.subview_depth > kMaxSubviewDepth) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::DepthExceeded, effects.scene_id,
                index);
        }
        if (effect.subview_depth > 0 && effect.subview_width == 0) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::EffectInvalid, effects.scene_id,
                index);
        }
        if (effect.lit) {
            ++computed.lit_count;
        }
        if (effect.shadow_proxy) {
            ++computed.shadow_count;
        }
        if (effect.subview_width != 0) {
            ++computed.subview_count;
            if (effect.subview_depth > computed.max_subview_depth) {
                computed.max_subview_depth = effect.subview_depth;
            }
        }
    }
    plan = computed;
    return HybridError::None;
}

}  // namespace stormline::hybrid

#endif  // STORMLINE_HYBRID_EFFECT_PLAN_HPP
