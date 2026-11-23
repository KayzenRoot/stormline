#ifndef STORMLINE_GRAPHICS_POST_OUTPUT_PLAN_HPP
#define STORMLINE_GRAPHICS_POST_OUTPUT_PLAN_HPP

#include "stormline/graphics/post/tone_color.hpp"

namespace stormline::graphics::post {

struct HdrCapability {
    bool display_hdr{false};
    bool swapchain_hdr{false};
    bool os_hdr{false};
    bool pq_supported{false};
};

struct OutputRequest {
    bool prefer_hdr{false};
};

struct OutputPlan {
    OutputMode mode{OutputMode::SdrSrgb};
    bool degraded{false};
};

[[nodiscard]] inline PostError plan_output(
    const HdrCapability& capability, const OutputRequest& request,
    OutputPlan& plan, PostDiagnostic& diagnostic) noexcept {
    plan = OutputPlan{};
    diagnostic = PostDiagnostic{};
    const bool hdr_available = capability.display_hdr
        && capability.swapchain_hdr && capability.os_hdr
        && capability.pq_supported;
    if (request.prefer_hdr && hdr_available) {
        plan.mode = OutputMode::Hdr10Pq;
        plan.degraded = false;
    } else {
        plan.mode = OutputMode::SdrSrgb;
        plan.degraded = request.prefer_hdr && !hdr_available;
    }
    return PostError::None;
}

}  // namespace stormline::graphics::post

#endif  // STORMLINE_GRAPHICS_POST_OUTPUT_PLAN_HPP
