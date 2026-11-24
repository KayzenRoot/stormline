#ifndef STORMLINE_TERRAIN_SKY_PLAN_HPP
#define STORMLINE_TERRAIN_SKY_PLAN_HPP

#include <array>

#include "stormline/terrain/terrain_types.hpp"

namespace stormline::terrain {

struct SkyProfileDesc {
    u32 profile_id{0};
    u32 revision{0};
    f32 time_of_day{0.0f};
    f32 sun_dir_x{0.0f};
    f32 sun_dir_y{0.0f};
    f32 sun_dir_z{0.0f};
    f32 moon_dir_x{0.0f};
    f32 moon_dir_y{0.0f};
    f32 moon_dir_z{0.0f};
    f32 cloud_coverage{0.0f};
    f32 fog_density{0.0f};
    QualityTier tier{QualityTier::Low};
};

struct SkySetDesc {
    u32 asset_id{0};
    u32 revision{0};
    u32 profile_count{0};
    std::array<SkyProfileDesc, kMaxSkyProfiles> profiles{};
};

struct SkyPlan {
    u32 profile_count{0};
    u32 low_count{0};
    u32 medium_count{0};
    u32 high_count{0};
    u32 ultra_count{0};
    f32 max_cloud_coverage{0.0f};
};

[[nodiscard]] inline TerrainError plan_sky(
    const SkySetDesc& sky, SkyPlan& plan,
    TerrainDiagnostic& diagnostic) noexcept {
    plan = SkyPlan{};
    diagnostic = TerrainDiagnostic{};
    if (sky.asset_id == 0 || sky.revision == 0) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::InvalidArgument, sky.asset_id, 0);
    }
    if (sky.profile_count == 0) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::SkyInvalid, sky.asset_id, 0);
    }
    if (sky.profile_count > kMaxSkyProfiles) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::CapacityFull, sky.asset_id, 0);
    }
    for (u32 index = 0; index < sky.profile_count; ++index) {
        const SkyProfileDesc& profile = sky.profiles[index];
        if (profile.profile_id == 0 || profile.revision == 0
            || !detail::valid_quality_tier(profile.tier)) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::SkyInvalid, sky.asset_id, index);
        }
        if (!detail::finite(profile.time_of_day)
            || !detail::finite(profile.sun_dir_x)
            || !detail::finite(profile.sun_dir_y)
            || !detail::finite(profile.sun_dir_z)
            || !detail::finite(profile.moon_dir_x)
            || !detail::finite(profile.moon_dir_y)
            || !detail::finite(profile.moon_dir_z)
            || !detail::finite(profile.cloud_coverage)
            || !detail::finite(profile.fog_density)) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::NonFiniteValue, sky.asset_id,
                index);
        }
        if (!(profile.time_of_day >= 0.0f)
            || !(profile.time_of_day < 24.0f)
            || !(profile.cloud_coverage >= 0.0f)
            || !(profile.cloud_coverage <= 1.0f)
            || !(profile.fog_density >= 0.0f)) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::OutOfRange, sky.asset_id, index);
        }
        if ((profile.sun_dir_x == 0.0f && profile.sun_dir_y == 0.0f
             && profile.sun_dir_z == 0.0f)
            || (profile.moon_dir_x == 0.0f && profile.moon_dir_y == 0.0f
                && profile.moon_dir_z == 0.0f)) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::SkyInvalid, sky.asset_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (sky.profiles[previous].profile_id == profile.profile_id) {
                return detail::set_terrain_error(
                    diagnostic, TerrainError::DuplicateId, sky.asset_id,
                    index);
            }
        }
    }
    plan.profile_count = sky.profile_count;
    for (u32 index = 0; index < sky.profile_count; ++index) {
        const SkyProfileDesc& profile = sky.profiles[index];
        switch (profile.tier) {
            case QualityTier::Low:
                ++plan.low_count;
                break;
            case QualityTier::Medium:
                ++plan.medium_count;
                break;
            case QualityTier::High:
                ++plan.high_count;
                break;
            case QualityTier::Ultra:
                ++plan.ultra_count;
                break;
        }
        if (profile.cloud_coverage > plan.max_cloud_coverage) {
            plan.max_cloud_coverage = profile.cloud_coverage;
        }
    }
    return TerrainError::None;
}

}  // namespace stormline::terrain

#endif  // STORMLINE_TERRAIN_SKY_PLAN_HPP
