#ifndef STORMLINE_GRAPHICS_VFX_DENSITY_PLAN_HPP
#define STORMLINE_GRAPHICS_VFX_DENSITY_PLAN_HPP

#include <cmath>

#include "stormline/graphics/vfx/graph_plan.hpp"

namespace stormline::graphics::vfx {

struct VfxDensityStampDesc {
    u32 stamp_id{0};
    u32 revision{0};
    f32 density{0.0f};
    f32 extinction{0.0f};
    f32 extent_x{0.0f};
    f32 extent_y{0.0f};
    f32 extent_z{0.0f};
    f32 lifetime_seconds{0.0f};
    f32 max_density{0.0f};
};

struct VfxDensityPlan {
    f32 density{0.0f};
    f32 extinction{0.0f};
    bool clamped{false};
};

[[nodiscard]] inline VfxError plan_density_stamp(
    const VfxDensityStampDesc& stamp, VfxDensityPlan& plan,
    VfxDiagnostic& diagnostic) noexcept {
    plan = VfxDensityPlan{};
    diagnostic = VfxDiagnostic{};
    if (stamp.stamp_id == 0 || stamp.revision == 0) {
        return detail::set_vfx_error(
            diagnostic, VfxError::InvalidArgument, stamp.stamp_id, 0, 0);
    }
    if (!std::isfinite(stamp.density) || !std::isfinite(stamp.extinction)
        || !std::isfinite(stamp.extent_x) || !std::isfinite(stamp.extent_y)
        || !std::isfinite(stamp.extent_z)
        || !std::isfinite(stamp.lifetime_seconds)
        || !std::isfinite(stamp.max_density)) {
        return detail::set_vfx_error(
            diagnostic, VfxError::NonFiniteValue, stamp.stamp_id, 0, 0);
    }
    if (stamp.density < 0.0f || stamp.extinction < 0.0f
        || !(stamp.extent_x > 0.0f) || !(stamp.extent_y > 0.0f)
        || !(stamp.extent_z > 0.0f) || !(stamp.lifetime_seconds > 0.0f)
        || !(stamp.max_density > 0.0f)) {
        return detail::set_vfx_error(
            diagnostic, VfxError::DensityInvalid, stamp.stamp_id, 0, 0);
    }
    plan.density = stamp.density;
    plan.extinction = stamp.extinction;
    if (plan.density > stamp.max_density) {
        plan.density = stamp.max_density;
        plan.clamped = true;
    }
    return VfxError::None;
}

}  // namespace stormline::graphics::vfx

#endif  // STORMLINE_GRAPHICS_VFX_DENSITY_PLAN_HPP
