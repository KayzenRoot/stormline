#ifndef STORMLINE_GRAPHICS_LIGHTING_GI_PLAN_HPP
#define STORMLINE_GRAPHICS_LIGHTING_GI_PLAN_HPP

#include "stormline/graphics/lighting/light.hpp"

namespace stormline::graphics::lighting {

struct GiRequest {
    GiMode requested{GiMode::Baked};
    bool baked_available{false};
    bool environment_available{false};
    bool probe_available{false};
};

struct GiPlan {
    GiMode mode{GiMode::Unsupported};
    bool degraded{false};
};

[[nodiscard]] inline LightingError plan_gi(
    const GiRequest& request, GiPlan& plan,
    LightingDiagnostic& diagnostic) noexcept {
    plan = GiPlan{};
    diagnostic = LightingDiagnostic{};
    switch (request.requested) {
        case GiMode::Baked:
            if (request.baked_available) {
                plan.mode = GiMode::Baked;
                return LightingError::None;
            }
            if (request.probe_available) {
                plan.mode = GiMode::ProbeFallback;
                plan.degraded = true;
                return LightingError::None;
            }
            if (request.environment_available) {
                plan.mode = GiMode::Environment;
                plan.degraded = true;
                return LightingError::None;
            }
            break;
        case GiMode::ProbeFallback:
            if (request.probe_available) {
                plan.mode = GiMode::ProbeFallback;
                return LightingError::None;
            }
            break;
        case GiMode::Environment:
            if (request.environment_available) {
                plan.mode = GiMode::Environment;
                return LightingError::None;
            }
            break;
        case GiMode::Unsupported:
            return detail::set_light_error(
                diagnostic, LightingError::Unsupported, 0, 0);
    }
    if (request.requested != GiMode::Baked
        && request.requested != GiMode::ProbeFallback
        && request.requested != GiMode::Environment
        && request.requested != GiMode::Unsupported) {
        return detail::set_light_error(
            diagnostic, LightingError::InvalidArgument, 0, 0);
    }
    return detail::set_light_error(
        diagnostic, LightingError::GiUnavailable, 0, 0);
}

}  // namespace stormline::graphics::lighting

#endif  // STORMLINE_GRAPHICS_LIGHTING_GI_PLAN_HPP
