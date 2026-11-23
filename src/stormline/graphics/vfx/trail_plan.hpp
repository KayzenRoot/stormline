#ifndef STORMLINE_GRAPHICS_VFX_TRAIL_PLAN_HPP
#define STORMLINE_GRAPHICS_VFX_TRAIL_PLAN_HPP

#include <cmath>

#include "stormline/graphics/vfx/graph_plan.hpp"

namespace stormline::graphics::vfx {

struct VfxTrailSample {
    f32 age_seconds{0.0f};
    f32 width{0.0f};
};

struct VfxTrailDesc {
    u32 source_id{0};
    u32 revision{0};
    u32 sample_count{0};
    std::array<VfxTrailSample, kMaxTrailSamples> samples{};
    u32 max_segments{0};
    u32 max_vertices{0};
    f32 max_age_seconds{0.0f};
};

struct VfxTrailPlan {
    u32 segments{0};
    u32 vertices{0};
    f32 lifetime_seconds{0.0f};
};

[[nodiscard]] inline VfxError plan_trail(
    const VfxTrailDesc& trail, VfxTrailPlan& plan,
    VfxDiagnostic& diagnostic) noexcept {
    plan = VfxTrailPlan{};
    diagnostic = VfxDiagnostic{};
    if (trail.source_id == 0 || trail.revision == 0) {
        return detail::set_vfx_error(
            diagnostic, VfxError::InvalidArgument, trail.source_id, 0, 0);
    }
    if (!std::isfinite(trail.max_age_seconds)) {
        return detail::set_vfx_error(
            diagnostic, VfxError::NonFiniteValue, trail.source_id, 0, 0);
    }
    if (!(trail.max_age_seconds > 0.0f)) {
        return detail::set_vfx_error(
            diagnostic, VfxError::OutOfRange, trail.source_id, 0, 0);
    }
    if (trail.sample_count < 2 || trail.sample_count > kMaxTrailSamples) {
        return detail::set_vfx_error(
            diagnostic, VfxError::GeometryInvalid, trail.source_id, 0, 0);
    }
    if (trail.max_segments == 0 || trail.max_vertices == 0) {
        return detail::set_vfx_error(
            diagnostic, VfxError::InvalidArgument, trail.source_id, 0, 0);
    }
    for (u32 index = 0; index < trail.sample_count; ++index) {
        const VfxTrailSample& sample = trail.samples[index];
        if (!std::isfinite(sample.age_seconds)
            || !std::isfinite(sample.width)) {
            return detail::set_vfx_error(
                diagnostic, VfxError::NonFiniteValue, trail.source_id, 0,
                index);
        }
        if (sample.age_seconds < 0.0f || !(sample.width > 0.0f)) {
            return detail::set_vfx_error(
                diagnostic, VfxError::GeometryInvalid, trail.source_id, 0,
                index);
        }
        if (index > 0
            && !(sample.age_seconds > trail.samples[index - 1].age_seconds)) {
            return detail::set_vfx_error(
                diagnostic, VfxError::GeometryInvalid, trail.source_id, 0,
                index);
        }
    }
    const f32 lifetime = trail.samples[trail.sample_count - 1].age_seconds;
    if (lifetime > trail.max_age_seconds) {
        return detail::set_vfx_error(
            diagnostic, VfxError::OutOfRange, trail.source_id, 0,
            trail.sample_count - 1);
    }
    const u32 segments = trail.sample_count - 1;
    const u32 vertices = trail.sample_count * 2;
    if (segments > trail.max_segments || vertices > trail.max_vertices) {
        return detail::set_vfx_error(
            diagnostic, VfxError::BudgetExceeded, trail.source_id, 0, 0);
    }
    plan.segments = segments;
    plan.vertices = vertices;
    plan.lifetime_seconds = lifetime;
    return VfxError::None;
}

}  // namespace stormline::graphics::vfx

#endif  // STORMLINE_GRAPHICS_VFX_TRAIL_PLAN_HPP
