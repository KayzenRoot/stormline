#ifndef STORMLINE_GRAPHICS_LIGHTING_REFLECTION_PLAN_HPP
#define STORMLINE_GRAPHICS_LIGHTING_REFLECTION_PLAN_HPP

#include "stormline/graphics/lighting/light.hpp"

namespace stormline::graphics::lighting {

struct ReflectionRequest {
    ReflectionMode preferred{ReflectionMode::ScreenSpace};
    u32 roughness_band{0};
    bool environment_available{false};
    bool probe_available{false};
    bool ssr_available{false};
};

struct ReflectionPlan {
    ReflectionMode mode{ReflectionMode::Unsupported};
    ReflectionMode fallback{ReflectionMode::Unsupported};
    bool offscreen_fallback{false};
    bool degraded{false};
};

[[nodiscard]] inline LightingError plan_reflections(
    const ReflectionRequest& request, ReflectionPlan& plan,
    LightingDiagnostic& diagnostic) noexcept {
    plan = ReflectionPlan{};
    diagnostic = LightingDiagnostic{};
    if (request.roughness_band > 3) {
        return detail::set_light_error(
            diagnostic, LightingError::InvalidArgument, 0, 0);
    }
    if (request.preferred != ReflectionMode::ScreenSpace
        && request.preferred != ReflectionMode::Probe
        && request.preferred != ReflectionMode::Environment
        && request.preferred != ReflectionMode::Unsupported) {
        return detail::set_light_error(
            diagnostic, LightingError::InvalidArgument, 0, 0);
    }
    switch (request.preferred) {
        case ReflectionMode::ScreenSpace:
            if (request.ssr_available) {
                plan.mode = ReflectionMode::ScreenSpace;
            } else if (request.probe_available) {
                plan.mode = ReflectionMode::Probe;
            } else if (request.environment_available) {
                plan.mode = ReflectionMode::Environment;
            }
            break;
        case ReflectionMode::Probe:
            if (request.probe_available) {
                plan.mode = ReflectionMode::Probe;
            } else if (request.environment_available) {
                plan.mode = ReflectionMode::Environment;
            }
            break;
        case ReflectionMode::Environment:
            if (request.environment_available) {
                plan.mode = ReflectionMode::Environment;
            }
            break;
        case ReflectionMode::Unsupported:
            return detail::set_light_error(
                diagnostic, LightingError::Unsupported, 0, 0);
    }
    if (plan.mode == ReflectionMode::Unsupported) {
        return detail::set_light_error(
            diagnostic, LightingError::ReflectionOffscreen, 0, 0);
    }
    if (plan.mode == ReflectionMode::ScreenSpace) {
        if (request.probe_available) {
            plan.fallback = ReflectionMode::Probe;
        } else if (request.environment_available) {
            plan.fallback = ReflectionMode::Environment;
        }
        plan.offscreen_fallback = plan.fallback != ReflectionMode::Unsupported;
    } else if (plan.mode == ReflectionMode::Probe
               && request.environment_available) {
        plan.fallback = ReflectionMode::Environment;
    }
    plan.degraded = plan.mode != request.preferred;
    return LightingError::None;
}

}  // namespace stormline::graphics::lighting

#endif  // STORMLINE_GRAPHICS_LIGHTING_REFLECTION_PLAN_HPP
