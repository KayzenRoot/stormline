#ifndef STORMLINE_GRAPHICS_CANVAS2D_LIGHT_PLAN_HPP
#define STORMLINE_GRAPHICS_CANVAS2D_LIGHT_PLAN_HPP

#include "stormline/graphics/canvas2d/canvas_types.hpp"

namespace stormline::graphics::canvas2d {

struct CanvasLightDesc {
    u32 light_id{0};
    u32 revision{0};
    f32 intensity{1.0f};
    f32 radius{1.0f};
    f32 color_r{1.0f};
    f32 color_g{1.0f};
    f32 color_b{1.0f};
    u32 layer_id{0};
    FalloffKind falloff{FalloffKind::Radial};
};

struct CanvasLightBudget {
    u32 max_lights{0};
    f32 max_intensity{0.0f};
};

struct LightPlan {
    u32 light_id{0};
    f32 intensity{0.0f};
    f32 radius{0.0f};
    bool clamped{false};
};

[[nodiscard]] inline CanvasError plan_light(
    const CanvasLightDesc& light, const CanvasLightBudget& budget,
    LightPlan& plan, CanvasDiagnostic& diagnostic) noexcept {
    plan = LightPlan{};
    diagnostic = CanvasDiagnostic{};
    if (light.light_id == 0 || light.revision == 0 || light.layer_id == 0) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::InvalidArgument, light.light_id, 0);
    }
    if (!detail::valid_falloff(light.falloff)) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::InvalidArgument, light.light_id, 0);
    }
    if (!detail::finite(light.intensity) || !detail::finite(light.radius)
        || !detail::finite(light.color_r) || !detail::finite(light.color_g)
        || !detail::finite(light.color_b)
        || !detail::finite(budget.max_intensity)) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::NonFiniteValue, light.light_id, 0);
    }
    if (light.intensity < 0.0f || !(light.radius > 0.0f)
        || light.color_r < 0.0f || light.color_r > 1.0f
        || light.color_g < 0.0f || light.color_g > 1.0f
        || light.color_b < 0.0f || light.color_b > 1.0f
        || budget.max_intensity < 0.0f) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::OutOfRange, light.light_id, 0);
    }
    if (budget.max_lights == 0) {
        return detail::set_canvas_error(
            diagnostic, CanvasError::LightBudgetExceeded, light.light_id, 0);
    }
    plan.light_id = light.light_id;
    plan.intensity = light.intensity;
    plan.radius = light.radius;
    if (plan.intensity > budget.max_intensity) {
        plan.intensity = budget.max_intensity;
        plan.clamped = true;
    }
    return CanvasError::None;
}

}  // namespace stormline::graphics::canvas2d

#endif  // STORMLINE_GRAPHICS_CANVAS2D_LIGHT_PLAN_HPP
