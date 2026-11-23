#ifndef STORMLINE_GRAPHICS_VFX_BLEND_PLAN_HPP
#define STORMLINE_GRAPHICS_VFX_BLEND_PLAN_HPP

#include "stormline/graphics/vfx/graph_plan.hpp"

namespace stormline::graphics::vfx {

struct VfxBlendDesc {
    u32 material_id{0};
    u32 material_revision{0};
    BlendMode blend{BlendMode::Opaque};
    DepthPolicy depth{DepthPolicy::TestAndWrite};
    bool premultiplied_alpha{false};
    bool sort_required{false};
    bool oit_approximation_allowed{false};
};

struct VfxBlendPlan {
    BlendMode blend{BlendMode::Opaque};
    DepthPolicy depth{DepthPolicy::TestAndWrite};
    bool needs_sort{false};
    bool oit_approx{false};
};

namespace detail {

inline bool valid_blend_mode(BlendMode mode) noexcept {
    switch (mode) {
        case BlendMode::Opaque:
        case BlendMode::Mask:
        case BlendMode::Blend:
        case BlendMode::Additive:
            return true;
    }
    return false;
}

inline bool valid_depth_policy(DepthPolicy policy) noexcept {
    switch (policy) {
        case DepthPolicy::TestAndWrite:
        case DepthPolicy::TestOnly:
        case DepthPolicy::Disabled:
            return true;
    }
    return false;
}

}  // namespace detail

[[nodiscard]] inline VfxError plan_blend(
    const VfxBlendDesc& description, VfxBlendPlan& plan,
    VfxDiagnostic& diagnostic) noexcept {
    plan = VfxBlendPlan{};
    diagnostic = VfxDiagnostic{};
    if (description.material_id == 0 || description.material_revision == 0) {
        return detail::set_vfx_error(
            diagnostic, VfxError::InvalidArgument, description.material_id, 0,
            0);
    }
    if (!detail::valid_blend_mode(description.blend)
        || !detail::valid_depth_policy(description.depth)) {
        return detail::set_vfx_error(
            diagnostic, VfxError::InvalidArgument, description.material_id, 0,
            0);
    }
    const bool depth_write = description.depth == DepthPolicy::TestAndWrite;
    if (description.blend == BlendMode::Opaque
        || description.blend == BlendMode::Mask) {
        if (!depth_write || description.premultiplied_alpha
            || description.sort_required
            || description.oit_approximation_allowed) {
            return detail::set_vfx_error(
                diagnostic, VfxError::MaterialMismatch,
                description.material_id, 0, 0);
        }
    } else if (description.blend == BlendMode::Blend) {
        if (depth_write) {
            return detail::set_vfx_error(
                diagnostic, VfxError::MaterialMismatch,
                description.material_id, 0, 0);
        }
    } else {
        if (depth_write || description.sort_required) {
            return detail::set_vfx_error(
                diagnostic, VfxError::MaterialMismatch,
                description.material_id, 0, 0);
        }
        if (description.oit_approximation_allowed) {
            return detail::set_vfx_error(
                diagnostic, VfxError::Unsupported, description.material_id, 0,
                0);
        }
    }
    plan.blend = description.blend;
    plan.depth = description.depth;
    plan.needs_sort = description.sort_required
        && description.blend == BlendMode::Blend;
    plan.oit_approx = description.oit_approximation_allowed
        && description.blend == BlendMode::Blend;
    return VfxError::None;
}

}  // namespace stormline::graphics::vfx

#endif  // STORMLINE_GRAPHICS_VFX_BLEND_PLAN_HPP
