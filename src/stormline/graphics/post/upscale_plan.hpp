#ifndef STORMLINE_GRAPHICS_POST_UPSCALE_PLAN_HPP
#define STORMLINE_GRAPHICS_POST_UPSCALE_PLAN_HPP

#include <numeric>

#include "stormline/graphics/post/reconstruction_plan.hpp"

namespace stormline::graphics::post {

struct UpscaleRequest {
    u32 render_width{0};
    u32 render_height{0};
    u32 output_width{0};
    u32 output_height{0};
    ReconstructionStrategy strategy{ReconstructionStrategy::Native};
};

struct UpscalePlan {
    u32 scale_numerator{1};
    u32 scale_denominator{1};
    bool reconstructed{false};
};

[[nodiscard]] inline PostError plan_upscale(
    const UpscaleRequest& request, UpscalePlan& plan,
    PostDiagnostic& diagnostic) noexcept {
    plan = UpscalePlan{};
    diagnostic = PostDiagnostic{};
    switch (request.strategy) {
        case ReconstructionStrategy::Native:
        case ReconstructionStrategy::Spatial:
        case ReconstructionStrategy::Taa:
        case ReconstructionStrategy::VendorUpscale:
            break;
        default:
            return detail::set_post_error(
                diagnostic, PostError::InvalidArgument, 0, 0);
    }
    if (request.render_width == 0 || request.render_height == 0
        || request.output_width == 0 || request.output_height == 0) {
        return detail::set_post_error(
            diagnostic, PostError::InvalidArgument, 0, 0);
    }
    if (request.output_width < request.render_width
        || request.output_height < request.render_height) {
        return detail::set_post_error(
            diagnostic, PostError::OutOfRange, 0, 0);
    }
    const bool mismatch = request.render_width != request.output_width
        || request.render_height != request.output_height;
    if (mismatch && request.strategy == ReconstructionStrategy::Native) {
        return detail::set_post_error(
            diagnostic, PostError::Unsupported, 0, 0);
    }
    plan.reconstructed = mismatch;
    if (!plan.reconstructed) {
        return PostError::None;
    }
    const u32 divisor =
        std::gcd(request.render_width, request.output_width);
    plan.scale_numerator = request.render_width / divisor;
    plan.scale_denominator = request.output_width / divisor;
    return PostError::None;
}

}  // namespace stormline::graphics::post

#endif  // STORMLINE_GRAPHICS_POST_UPSCALE_PLAN_HPP
