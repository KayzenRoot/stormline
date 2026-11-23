#ifndef STORMLINE_GRAPHICS_POST_RECONSTRUCTION_PLAN_HPP
#define STORMLINE_GRAPHICS_POST_RECONSTRUCTION_PLAN_HPP

#include "stormline/graphics/post/output_plan.hpp"

namespace stormline::graphics::post {

struct ReconstructionRequest {
    ReconstructionStrategy preferred{ReconstructionStrategy::Native};
    bool depth_available{false};
    bool velocity_available{false};
    bool history_available{false};
    bool reactive_mask_available{false};
    bool vendor_available{false};
};

struct ReconstructionPlan {
    ReconstructionStrategy strategy{ReconstructionStrategy::Native};
    bool degraded{false};
};

[[nodiscard]] inline PostError plan_reconstruction(
    const ReconstructionRequest& request, ReconstructionPlan& plan,
    PostDiagnostic& diagnostic) noexcept {
    plan = ReconstructionPlan{};
    diagnostic = PostDiagnostic{};
    switch (request.preferred) {
        case ReconstructionStrategy::Native:
            plan.strategy = ReconstructionStrategy::Native;
            return PostError::None;
        case ReconstructionStrategy::Spatial:
            plan.strategy = ReconstructionStrategy::Spatial;
            return PostError::None;
        case ReconstructionStrategy::Taa:
            if (request.depth_available && request.velocity_available
                && request.history_available) {
                plan.strategy = ReconstructionStrategy::Taa;
                return PostError::None;
            }
            plan.strategy = ReconstructionStrategy::Spatial;
            plan.degraded = true;
            return PostError::None;
        case ReconstructionStrategy::VendorUpscale:
            if (request.depth_available && request.velocity_available
                && request.history_available
                && request.reactive_mask_available
                && request.vendor_available) {
                plan.strategy = ReconstructionStrategy::VendorUpscale;
                return PostError::None;
            }
            plan.strategy = ReconstructionStrategy::Spatial;
            plan.degraded = true;
            return PostError::None;
    }
    return detail::set_post_error(
        diagnostic, PostError::InvalidArgument, 0, 0);
}

}  // namespace stormline::graphics::post

#endif  // STORMLINE_GRAPHICS_POST_RECONSTRUCTION_PLAN_HPP
