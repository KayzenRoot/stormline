#ifndef STORMLINE_GRAPHICS_CANVAS2D_CAMERA_PLAN_HPP
#define STORMLINE_GRAPHICS_CANVAS2D_CAMERA_PLAN_HPP

#include "stormline/graphics/canvas2d/canvas_types.hpp"

namespace stormline::graphics::canvas2d {

struct CanvasCameraDesc {
    u32 viewport_width{0};
    u32 viewport_height{0};
    f32 position_x{0.0f};
    f32 position_y{0.0f};
    f32 zoom{1.0f};
    f32 dpi_scale{1.0f};
    bool letterbox{false};
};

struct CameraPlan {
    f32 effective_zoom{1.0f};
    f32 dpi_scale{1.0f};
    bool letterbox{false};
};

[[nodiscard]] inline CanvasError plan_camera(
    const CanvasCameraDesc& camera, CameraPlan& plan,
    CanvasDiagnostic& diagnostic) noexcept {
    plan = CameraPlan{};
    diagnostic = CanvasDiagnostic{};
    if (camera.viewport_width == 0 || camera.viewport_height == 0) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::CameraInvalid, 0, 0);
    }
    if (!detail::finite(camera.position_x) || !detail::finite(camera.position_y)
        || !detail::finite(camera.zoom) || !detail::finite(camera.dpi_scale)) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::NonFiniteValue, 0, 0);
    }
    if (!(camera.zoom > 0.0f) || !(camera.dpi_scale > 0.0f)) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::CameraInvalid, 0, 0);
    }
    const f32 effective_zoom = camera.zoom * camera.dpi_scale;
    if (!detail::finite(effective_zoom)) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::OutOfRange, 0, 0);
    }
    plan.effective_zoom = effective_zoom;
    plan.dpi_scale = camera.dpi_scale;
    plan.letterbox = camera.letterbox;
    return CanvasError::None;
}

}  // namespace stormline::graphics::canvas2d

#endif  // STORMLINE_GRAPHICS_CANVAS2D_CAMERA_PLAN_HPP
