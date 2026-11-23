#ifndef STORMLINE_GRAPHICS_CANVAS2D_SNAP_PLAN_HPP
#define STORMLINE_GRAPHICS_CANVAS2D_SNAP_PLAN_HPP

#include <cmath>

#include "stormline/graphics/canvas2d/canvas_types.hpp"

namespace stormline::graphics::canvas2d {

struct CanvasSnapDesc {
    SnapMode mode{SnapMode::None};
    FilterMode filter{FilterMode::Linear};
    f32 scale_x{1.0f};
    f32 scale_y{1.0f};
    f32 offset_x{0.0f};
    f32 offset_y{0.0f};
};

struct SnapPlan {
    SnapMode mode{SnapMode::None};
    FilterMode filter{FilterMode::Linear};
    f32 snapped_offset_x{0.0f};
    f32 snapped_offset_y{0.0f};
    bool degraded{false};
};

[[nodiscard]] inline CanvasError plan_snap(
    const CanvasSnapDesc& snap, SnapPlan& plan,
    CanvasDiagnostic& diagnostic) noexcept {
    plan = SnapPlan{};
    diagnostic = CanvasDiagnostic{};
    if (!detail::valid_snap_mode(snap.mode) || !detail::valid_filter(snap.filter)) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::InvalidArgument, 0, 0);
    }
    if (!detail::finite(snap.scale_x) || !detail::finite(snap.scale_y)
        || !detail::finite(snap.offset_x) || !detail::finite(snap.offset_y)) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::NonFiniteValue, 0, 0);
    }
    if (!(snap.scale_x > 0.0f) || !(snap.scale_y > 0.0f)) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::SnapInvalid, 0, 0);
    }
    plan.mode = snap.mode;
    plan.filter = snap.filter;
    plan.snapped_offset_x = snap.offset_x;
    plan.snapped_offset_y = snap.offset_y;
    if (snap.mode == SnapMode::Integer) {
        const bool integer_scale = snap.scale_x == std::floor(snap.scale_x)
            && snap.scale_y == std::floor(snap.scale_y);
        plan.snapped_offset_x = std::round(snap.offset_x);
        plan.snapped_offset_y = std::round(snap.offset_y);
        plan.degraded = !integer_scale;
    }
    return CanvasError::None;
}

}  // namespace stormline::graphics::canvas2d

#endif  // STORMLINE_GRAPHICS_CANVAS2D_SNAP_PLAN_HPP
