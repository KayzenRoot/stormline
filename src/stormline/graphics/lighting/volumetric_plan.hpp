#ifndef STORMLINE_GRAPHICS_LIGHTING_VOLUMETRIC_PLAN_HPP
#define STORMLINE_GRAPHICS_LIGHTING_VOLUMETRIC_PLAN_HPP

#include "stormline/graphics/lighting/light.hpp"

#include <algorithm>

namespace stormline::graphics::lighting {

struct VolumetricDesc {
    u32 id{0};
    u32 revision{0};
    f32 density{0.0f};
    f32 extinction{0.0f};
    f32 scattering{0.0f};
    f32 anisotropy{0.0f};
    VolumetricTier tier{VolumetricTier::Analytic};
    u32 step_count{0};
};

struct VolumetricSet {
    u32 count{0};
    std::array<VolumetricDesc, kMaxVolumetrics> volumes{};
};

struct VolumetricPlan {
    u32 count{0};
    std::array<u32, kMaxVolumetrics> volume_ids{};
    u32 total_steps{0};
};

namespace detail {

inline bool valid_volumetric_tier(VolumetricTier tier) noexcept {
    switch (tier) {
        case VolumetricTier::Analytic:
        case VolumetricTier::Froxel:
            return true;
    }
    return false;
}

}  // namespace detail

[[nodiscard]] inline LightingError plan_volumetrics(
    const VolumetricSet& volumes, u32 max_steps,
    VolumetricPlan& plan, LightingDiagnostic& diagnostic) noexcept {
    plan = VolumetricPlan{};
    diagnostic = LightingDiagnostic{};
    if (volumes.count > kMaxVolumetrics || max_steps == 0) {
        return detail::set_light_error(
            diagnostic, LightingError::InvalidArgument, 0, 0);
    }
    std::array<u32, kMaxVolumetrics> ids{};
    u64 total_steps = 0;
    for (u32 index = 0; index < volumes.count; ++index) {
        const VolumetricDesc& volume = volumes.volumes[index];
        if (volume.id == 0 || volume.revision == 0) {
            return detail::set_light_error(
                diagnostic, LightingError::InvalidArgument, volume.id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (volumes.volumes[previous].id == volume.id) {
                return detail::set_light_error(
                    diagnostic, LightingError::DuplicateId, volume.id, index);
            }
        }
        if (!detail::finite(volume.density)
            || !detail::finite(volume.extinction)
            || !detail::finite(volume.scattering)
            || !detail::finite(volume.anisotropy)) {
            return detail::set_light_error(
                diagnostic, LightingError::NonFiniteValue, volume.id, index);
        }
        if (volume.density < 0.0f || volume.extinction < 0.0f
            || volume.scattering < 0.0f) {
            return detail::set_light_error(
                diagnostic, LightingError::OutOfRange, volume.id, index);
        }
        if (volume.anisotropy < -1.0f || volume.anisotropy > 1.0f) {
            return detail::set_light_error(
                diagnostic, LightingError::OutOfRange, volume.id, index);
        }
        if (!detail::valid_volumetric_tier(volume.tier)
            || volume.step_count == 0) {
            return detail::set_light_error(
                diagnostic, LightingError::InvalidArgument, volume.id, index);
        }
        total_steps += volume.step_count;
        ids[index] = volume.id;
    }
    if (total_steps > max_steps || total_steps > 0xFFFFFFFFull) {
        return detail::set_light_error(
            diagnostic, LightingError::VolumetricBudgetExceeded, 0, 0);
    }
    std::sort(ids.begin(), ids.begin() + volumes.count);
    plan.count = volumes.count;
    plan.total_steps = static_cast<u32>(total_steps);
    for (u32 index = 0; index < volumes.count; ++index) {
        plan.volume_ids[index] = ids[index];
    }
    return LightingError::None;
}

}  // namespace stormline::graphics::lighting

#endif  // STORMLINE_GRAPHICS_LIGHTING_VOLUMETRIC_PLAN_HPP
