#ifndef STORMLINE_ANIMATION_BLEND_PLAN_HPP
#define STORMLINE_ANIMATION_BLEND_PLAN_HPP

#include "stormline/animation/animation_types.hpp"

namespace stormline::animation {

struct BlendClipDesc {
    u32 clip_id{0};
    u32 revision{0};
    f32 weight{0.0f};
};

struct BlendDesc {
    u32 blend_id{0};
    u32 revision{0};
    bool additive{false};
    bool discrete_targets{false};
    u32 clip_count{0};
    std::array<BlendClipDesc, kMaxBlendClips> clips{};
};

struct BlendPlan {
    u32 clip_count{0};
    std::array<f32, kMaxBlendClips> normalized_weights{};
};

[[nodiscard]] inline AnimationError plan_blend(
    const BlendDesc& blend, BlendPlan& plan,
    AnimationDiagnostic& diagnostic) noexcept {
    plan = BlendPlan{};
    diagnostic = AnimationDiagnostic{};
    if (blend.blend_id == 0 || blend.revision == 0) {
        return detail::set_animation_error(
            diagnostic, AnimationError::InvalidArgument, blend.blend_id, 0);
    }
    if (blend.clip_count == 0 || blend.clip_count > kMaxBlendClips) {
        return detail::set_animation_error(
            diagnostic, AnimationError::BlendInvalid, blend.blend_id, 0);
    }
    if (blend.additive && !blend.discrete_targets) {
        return detail::set_animation_error(
            diagnostic, AnimationError::BlendInvalid, blend.blend_id, 0);
    }
    for (u32 index = 0; index < blend.clip_count; ++index) {
        const BlendClipDesc& clip = blend.clips[index];
        if (clip.clip_id == 0 || clip.revision == 0) {
            return detail::set_animation_error(
                diagnostic, AnimationError::BlendInvalid, blend.blend_id,
                index);
        }
        if (!detail::finite(clip.weight)) {
            return detail::set_animation_error(
                diagnostic, AnimationError::NonFiniteValue, blend.blend_id,
                index);
        }
        if (clip.weight < 0.0f) {
            return detail::set_animation_error(
                diagnostic, AnimationError::BlendInvalid, blend.blend_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (blend.clips[previous].clip_id == clip.clip_id) {
                return detail::set_animation_error(
                    diagnostic, AnimationError::DuplicateId, blend.blend_id,
                    index);
            }
        }
    }
    std::array<f32, kMaxBlendClips> normalized{};
    double total = 0.0;
    for (u32 index = 0; index < blend.clip_count; ++index) {
        total += static_cast<double>(blend.clips[index].weight);
    }
    if (!(total > 0.0) || total - total != 0.0) {
        return detail::set_animation_error(
            diagnostic, AnimationError::BlendInvalid, blend.blend_id, 0);
    }
    for (u32 index = 0; index < blend.clip_count; ++index) {
        normalized[index] = static_cast<f32>(
            static_cast<double>(blend.clips[index].weight) / total);
    }
    plan.clip_count = blend.clip_count;
    plan.normalized_weights = normalized;
    return AnimationError::None;
}

}  // namespace stormline::animation

#endif  // STORMLINE_ANIMATION_BLEND_PLAN_HPP
