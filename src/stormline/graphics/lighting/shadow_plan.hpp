#ifndef STORMLINE_GRAPHICS_LIGHTING_SHADOW_PLAN_HPP
#define STORMLINE_GRAPHICS_LIGHTING_SHADOW_PLAN_HPP

#include "stormline/graphics/lighting/light.hpp"

#include <algorithm>
#include <cmath>

namespace stormline::graphics::lighting {

struct CascadeRequest {
    f32 near_distance{0.0f};
    f32 far_distance{0.0f};
    u32 cascade_count{0};
    f32 lambda{0.5f};
};

struct CascadeSplit {
    f32 near_distance{0.0f};
    f32 far_distance{0.0f};
    f32 blend{0.0f};
};

struct CascadePlan {
    u32 count{0};
    std::array<CascadeSplit, kMaxCascades> cascades{};
};

namespace detail {

inline LightingError set_shadow_error(
    LightingDiagnostic& diagnostic, LightingError code, u32 light_id = 0,
    u32 page_id = 0, u32 index = 0) noexcept {
    diagnostic = LightingDiagnostic{code, light_id, page_id, index};
    return code;
}

struct ShadowOrderKey {
    f32 distance{0.0f};
    u32 id{0};
};

}  // namespace detail

[[nodiscard]] inline LightingError build_cascade_plan(
    const CascadeRequest& request, CascadePlan& plan,
    LightingDiagnostic& diagnostic) noexcept {
    plan = CascadePlan{};
    diagnostic = LightingDiagnostic{};
    if (!detail::finite(request.near_distance)
        || !detail::finite(request.far_distance)
        || !detail::finite(request.lambda)
        || !(request.near_distance > 0.0f)
        || !(request.far_distance > request.near_distance)
        || request.cascade_count == 0
        || request.cascade_count > kMaxCascades
        || request.lambda < 0.0f || request.lambda > 1.0f) {
        return detail::set_shadow_error(
            diagnostic, LightingError::InvalidCascade);
    }
    CascadePlan result{};
    result.count = request.cascade_count;
    f32 previous_far = request.near_distance;
    for (u32 index = 0; index < request.cascade_count; ++index) {
        const u32 cascade = index + 1;
        const f32 p = static_cast<f32>(cascade)
            / static_cast<f32>(request.cascade_count);
        const f32 logarithmic = request.near_distance
            * std::pow(request.far_distance / request.near_distance, p);
        const f32 uniform = request.near_distance
            + (request.far_distance - request.near_distance) * p;
        f32 split = request.lambda * logarithmic
            + (1.0f - request.lambda) * uniform;
        if (cascade == request.cascade_count) {
            split = request.far_distance;
        }
        if (!detail::finite(split) || !(split > previous_far)) {
            return detail::set_shadow_error(
                diagnostic, LightingError::InvalidCascade, 0, 0, index);
        }
        const f32 near_distance = previous_far;
        const f32 far_distance = split;
        const f32 span = far_distance - near_distance;
        const f32 blend = std::min(0.1f, span * 0.1f);
        result.cascades[index] = CascadeSplit{
            near_distance, far_distance, blend};
        previous_far = far_distance;
    }
    plan = result;
    return LightingError::None;
}

struct ShadowPage {
    u32 id{0};
    u32 light_id{0};
    f32 distance{0.0f};
    bool resident{false};
};

struct ShadowPageSet {
    u32 count{0};
    std::array<ShadowPage, kMaxShadowPages> pages{};
};

struct ShadowPagePlan {
    u32 count{0};
    std::array<u32, kMaxShadowPages> page_ids{};
    u32 resident_count{0};
    u32 missing_count{0};
    bool coarse_fallback{false};
};

[[nodiscard]] inline LightingError plan_shadow_pages(
    const LightSet& lights, const ShadowPageSet& pages, u32 budget_pages,
    ShadowPagePlan& plan, LightingDiagnostic& diagnostic) noexcept {
    plan = ShadowPagePlan{};
    diagnostic = LightingDiagnostic{};
    if (pages.count > kMaxShadowPages || budget_pages > kMaxShadowPages) {
        return detail::set_shadow_error(
            diagnostic, LightingError::InvalidArgument);
    }
    std::array<detail::ShadowOrderKey, kMaxShadowPages> keys{};
    u32 missing = 0;
    u32 resident = 0;
    for (u32 index = 0; index < pages.count; ++index) {
        const ShadowPage& page = pages.pages[index];
        if (page.id == 0 || !detail::finite(page.distance)
            || page.distance < 0.0f) {
            return detail::set_shadow_error(
                diagnostic, LightingError::InvalidArgument, 0, page.id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (pages.pages[previous].id == page.id) {
                return detail::set_shadow_error(
                    diagnostic, LightingError::DuplicateId, 0, page.id, index);
            }
        }
        const u32 light_index = detail::find_light(lights, page.light_id);
        if (light_index == kMaxLights) {
            return detail::set_shadow_error(
                diagnostic, LightingError::NotFound, page.light_id, page.id,
                index);
        }
        if (lights.lights[light_index].shadow == ShadowMode::Disabled) {
            return detail::set_shadow_error(
                diagnostic, LightingError::InvalidArgument, page.light_id,
                page.id, index);
        }
        if (page.resident) {
            ++resident;
        } else {
            keys[missing] = detail::ShadowOrderKey{page.distance, page.id};
            ++missing;
        }
    }
    std::sort(keys.begin(), keys.begin() + missing,
              [](const detail::ShadowOrderKey& left,
                 const detail::ShadowOrderKey& right) {
                  if (left.distance != right.distance) {
                      return left.distance < right.distance;
                  }
                  return left.id < right.id;
              });
    const u32 admitted = std::min(missing, budget_pages);
    plan.count = admitted;
    plan.resident_count = resident;
    plan.missing_count = missing;
    plan.coarse_fallback = admitted < missing;
    for (u32 index = 0; index < admitted; ++index) {
        plan.page_ids[index] = keys[index].id;
    }
    return LightingError::None;
}

}  // namespace stormline::graphics::lighting

#endif  // STORMLINE_GRAPHICS_LIGHTING_SHADOW_PLAN_HPP
