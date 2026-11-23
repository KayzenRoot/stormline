#ifndef STORMLINE_GRAPHICS_POST_MOTION_BLUR_HPP
#define STORMLINE_GRAPHICS_POST_MOTION_BLUR_HPP

#include "stormline/graphics/post/reconstruction_plan.hpp"

namespace stormline::graphics::post {

struct MotionBlurDesc {
    bool enabled{false};
    bool reduced_motion{false};
    f32 shutter_angle_degrees{180.0f};
    f32 max_velocity_pixels{0.0f};
};

struct MotionBlurPlan {
    bool enabled{false};
};

[[nodiscard]] inline PostError plan_motion_blur(
    const MotionBlurDesc& description, MotionBlurPlan& plan,
    PostDiagnostic& diagnostic) noexcept {
    plan = MotionBlurPlan{};
    diagnostic = PostDiagnostic{};
    if (!detail::finite(description.shutter_angle_degrees)
        || !detail::finite(description.max_velocity_pixels)) {
        return detail::set_post_error(
            diagnostic, PostError::NonFiniteValue, 0, 0);
    }
    if (description.shutter_angle_degrees < 0.0f
        || description.shutter_angle_degrees > 360.0f
        || description.max_velocity_pixels < 0.0f) {
        return detail::set_post_error(
            diagnostic, PostError::OutOfRange, 0, 0);
    }
    if (!description.enabled || description.reduced_motion) {
        plan.enabled = false;
        return PostError::None;
    }
    if (!(description.max_velocity_pixels > 0.0f)) {
        plan.enabled = false;
        return detail::set_post_error(
            diagnostic, PostError::Unsupported, 0, 0);
    }
    plan.enabled = true;
    return PostError::None;
}

}  // namespace stormline::graphics::post

#endif  // STORMLINE_GRAPHICS_POST_MOTION_BLUR_HPP
