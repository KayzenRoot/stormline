#ifndef STORMLINE_GRAPHICS_VFX_RIBBON_PLAN_HPP
#define STORMLINE_GRAPHICS_VFX_RIBBON_PLAN_HPP

#include <cmath>

#include "stormline/graphics/vfx/graph_plan.hpp"

namespace stormline::graphics::vfx {

struct VfxRibbonDesc {
    u32 source_id{0};
    u32 revision{0};
    u32 sample_count{0};
    f32 width{0.0f};
    f32 min_sample_distance{0.0f};
    u32 max_segments{0};
    u32 max_vertices{0};
};

struct VfxRibbonPlan {
    u32 segments{0};
    u32 vertices{0};
};

[[nodiscard]] inline VfxError plan_ribbon(
    const VfxRibbonDesc& ribbon, VfxRibbonPlan& plan,
    VfxDiagnostic& diagnostic) noexcept {
    plan = VfxRibbonPlan{};
    diagnostic = VfxDiagnostic{};
    if (ribbon.source_id == 0 || ribbon.revision == 0) {
        return detail::set_vfx_error(
            diagnostic, VfxError::InvalidArgument, ribbon.source_id, 0, 0);
    }
    if (!std::isfinite(ribbon.width)
        || !std::isfinite(ribbon.min_sample_distance)) {
        return detail::set_vfx_error(
            diagnostic, VfxError::NonFiniteValue, ribbon.source_id, 0, 0);
    }
    if (ribbon.sample_count < 2
        || ribbon.sample_count > kMaxRibbonSamples
        || !(ribbon.width > 0.0f)
        || !(ribbon.min_sample_distance > 0.0f)) {
        return detail::set_vfx_error(
            diagnostic, VfxError::GeometryInvalid, ribbon.source_id, 0, 0);
    }
    if (ribbon.max_segments == 0 || ribbon.max_vertices == 0) {
        return detail::set_vfx_error(
            diagnostic, VfxError::InvalidArgument, ribbon.source_id, 0, 0);
    }
    const u32 segments = ribbon.sample_count - 1;
    const u32 vertices = ribbon.sample_count * 2;
    if (segments > ribbon.max_segments || vertices > ribbon.max_vertices) {
        return detail::set_vfx_error(
            diagnostic, VfxError::BudgetExceeded, ribbon.source_id, 0, 0);
    }
    plan.segments = segments;
    plan.vertices = vertices;
    return VfxError::None;
}

}  // namespace stormline::graphics::vfx

#endif  // STORMLINE_GRAPHICS_VFX_RIBBON_PLAN_HPP
