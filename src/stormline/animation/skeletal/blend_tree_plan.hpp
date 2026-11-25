#ifndef STORMLINE_ANIMATION_SKELETAL_BLEND_TREE_PLAN_HPP
#define STORMLINE_ANIMATION_SKELETAL_BLEND_TREE_PLAN_HPP

#include <array>

#include "stormline/animation/skeletal/skeletal_types.hpp"

namespace stormline::animation::skeletal {

struct BlendNodeDesc {
    u32 node_id{0};
    u32 revision{0};
    BlendKind kind{BlendKind::Lerp};
    f32 weight{1.0f};
    f32 threshold{0.0f};
    bool enabled{false};
};

struct BlendSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 node_count{0};
    std::array<BlendNodeDesc, kMaxBlendNodes> nodes{};
};

struct BlendPlan {
    u32 node_count{0};
    u32 lerp_count{0};
    u32 additive_count{0};
    u32 mask_count{0};
    u32 blend_1d_count{0};
    u32 blend_2d_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] inline SkeletalError plan_blends(
    const BlendSetDesc& blends, BlendPlan& plan,
    SkeletalDiagnostic& diagnostic) noexcept {
    plan = BlendPlan{};
    diagnostic = SkeletalDiagnostic{};
    if (blends.owner_id == 0 || blends.revision == 0) {
        return detail::set_skeletal_error(
            diagnostic, SkeletalError::InvalidArgument, blends.owner_id, 0);
    }
    if (blends.node_count > kMaxBlendNodes) {
        return detail::set_skeletal_error(
            diagnostic, SkeletalError::CapacityFull, blends.owner_id, 0);
    }
    for (u32 index = 0; index < blends.node_count; ++index) {
        const BlendNodeDesc& node = blends.nodes[index];
        if (node.node_id == 0 || node.revision == 0
            || !detail::valid_blend_kind(node.kind)) {
            return detail::set_skeletal_error(
                diagnostic, SkeletalError::BlendInvalid, blends.owner_id,
                index);
        }
        if (!detail::unit_scalar_in(node.weight, 0.0f, 1.0f)
            || !detail::unit_scalar_in(node.threshold, 0.0f, 1.0f)) {
            return detail::set_skeletal_error(
                diagnostic, SkeletalError::OutOfRange, blends.owner_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (blends.nodes[previous].node_id == node.node_id) {
                return detail::set_skeletal_error(
                    diagnostic, SkeletalError::DuplicateId, blends.owner_id,
                    index);
            }
        }
    }
    plan.node_count = blends.node_count;
    for (u32 index = 0; index < blends.node_count; ++index) {
        const BlendNodeDesc& node = blends.nodes[index];
        switch (node.kind) {
            case BlendKind::Lerp:
                ++plan.lerp_count;
                break;
            case BlendKind::Additive:
                ++plan.additive_count;
                break;
            case BlendKind::Mask:
                ++plan.mask_count;
                break;
            case BlendKind::Blend1D:
                ++plan.blend_1d_count;
                break;
            case BlendKind::Blend2D:
                ++plan.blend_2d_count;
                break;
        }
        if (node.enabled) {
            ++plan.enabled_count;
        }
    }
    return SkeletalError::None;
}

}  // namespace stormline::animation::skeletal

#endif  // STORMLINE_ANIMATION_SKELETAL_BLEND_TREE_PLAN_HPP
