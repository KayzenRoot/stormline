#ifndef STORMLINE_GRAPHICS_POST_TONE_COLOR_HPP
#define STORMLINE_GRAPHICS_POST_TONE_COLOR_HPP

#include "stormline/graphics/post/camera_exposure.hpp"

namespace stormline::graphics::post {

struct ColorPlanDesc {
    ColorTransfer input_transfer{ColorTransfer::Linear};
    ColorTransfer output_transfer{ColorTransfer::Srgb};
    ToneCurve tone_curve{ToneCurve::Neutral};
    f32 exposure_stops{0.0f};
    f32 white_point_nits{203.0f};
    bool tone_already_applied{false};
    bool gamma_already_applied{false};
};

struct ColorPlan {
    ColorTransfer output_transfer{ColorTransfer::Srgb};
    ToneCurve tone_curve{ToneCurve::Neutral};
    f32 exposure_stops{0.0f};
};

[[nodiscard]] inline PostError plan_color(
    const ColorPlanDesc& description, ColorPlan& plan,
    PostDiagnostic& diagnostic) noexcept {
    plan = ColorPlan{};
    diagnostic = PostDiagnostic{};
    if (!detail::finite(description.exposure_stops)
        || !detail::finite(description.white_point_nits)) {
        return detail::set_post_error(
            diagnostic, PostError::NonFiniteValue, 0, 0);
    }
    if (description.tone_already_applied
        || description.gamma_already_applied) {
        return detail::set_post_error(
            diagnostic, PostError::DoubleTransferGuard, 0, 0);
    }
    if (description.input_transfer != ColorTransfer::Linear
        && description.input_transfer != ColorTransfer::Srgb) {
        return detail::set_post_error(
            diagnostic, PostError::ColorSpaceMismatch, 0, 0);
    }
    if (description.output_transfer != ColorTransfer::Linear
        && description.output_transfer != ColorTransfer::Srgb) {
        return detail::set_post_error(
            diagnostic, PostError::ColorSpaceMismatch, 0, 0);
    }
    if (description.tone_curve != ToneCurve::None
        && description.tone_curve != ToneCurve::Neutral
        && description.tone_curve != ToneCurve::Filmic) {
        return detail::set_post_error(
            diagnostic, PostError::InvalidArgument, 0, 0);
    }
    if (description.exposure_stops < -16.0f
        || description.exposure_stops > 16.0f
        || !(description.white_point_nits > 0.0f)) {
        return detail::set_post_error(
            diagnostic, PostError::OutOfRange, 0, 0);
    }
    if (description.output_transfer != ColorTransfer::Srgb) {
        return detail::set_post_error(
            diagnostic, PostError::Unsupported, 0, 0);
    }
    plan.output_transfer = description.output_transfer;
    plan.tone_curve = description.tone_curve;
    plan.exposure_stops = description.exposure_stops;
    return PostError::None;
}

}  // namespace stormline::graphics::post

#endif  // STORMLINE_GRAPHICS_POST_TONE_COLOR_HPP
