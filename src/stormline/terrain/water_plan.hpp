#ifndef STORMLINE_TERRAIN_WATER_PLAN_HPP
#define STORMLINE_TERRAIN_WATER_PLAN_HPP

#include <array>

#include "stormline/terrain/terrain_types.hpp"

namespace stormline::terrain {

struct WaterBodyDesc {
    u64 body_key{0};
    u32 revision{0};
    WaterClass water_class{WaterClass::Local};
    f32 min_x{0.0f};
    f32 min_z{0.0f};
    f32 max_x{0.0f};
    f32 max_z{0.0f};
    f32 surface_height{0.0f};
    f32 wave_amplitude{0.0f};
    f32 wave_frequency{0.0f};
    bool shore_complete{false};
};

struct WaterSetDesc {
    u32 asset_id{0};
    u32 revision{0};
    u32 body_count{0};
    std::array<WaterBodyDesc, kMaxWaterBodies> bodies{};
};

struct WaterPlan {
    u32 body_count{0};
    u32 ocean_count{0};
    u32 lake_count{0};
    u32 river_count{0};
    u32 local_count{0};
    u32 incomplete_shore_count{0};
    f32 min_surface{0.0f};
    f32 max_surface{0.0f};
};

[[nodiscard]] inline TerrainError plan_water(
    const WaterSetDesc& water, WaterPlan& plan,
    TerrainDiagnostic& diagnostic) noexcept {
    plan = WaterPlan{};
    diagnostic = TerrainDiagnostic{};
    if (water.asset_id == 0 || water.revision == 0) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::InvalidArgument, water.asset_id, 0);
    }
    if (water.body_count > kMaxWaterBodies) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::CapacityFull, water.asset_id, 0);
    }
    for (u32 index = 0; index < water.body_count; ++index) {
        const WaterBodyDesc& body = water.bodies[index];
        if (body.body_key == 0 || body.revision == 0
            || !detail::valid_water_class(body.water_class)) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::WaterInvalid, water.asset_id,
                index);
        }
        if (!detail::finite(body.min_x) || !detail::finite(body.min_z)
            || !detail::finite(body.max_x)
            || !detail::finite(body.max_z)
            || !detail::finite(body.surface_height)
            || !detail::finite(body.wave_amplitude)
            || !detail::finite(body.wave_frequency)) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::NonFiniteValue, water.asset_id,
                index);
        }
        if (!(body.min_x < body.max_x) || !(body.min_z < body.max_z)
            || !(body.wave_amplitude >= 0.0f)
            || !(body.wave_frequency > 0.0f)) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::WaterInvalid, water.asset_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (water.bodies[previous].body_key == body.body_key) {
                return detail::set_terrain_error(
                    diagnostic, TerrainError::DuplicateId, water.asset_id,
                    index);
            }
        }
    }
    plan.body_count = water.body_count;
    if (water.body_count == 0) {
        return TerrainError::None;
    }
    plan.min_surface = water.bodies[0].surface_height;
    plan.max_surface = water.bodies[0].surface_height;
    for (u32 index = 0; index < water.body_count; ++index) {
        const WaterBodyDesc& body = water.bodies[index];
        switch (body.water_class) {
            case WaterClass::Ocean:
                ++plan.ocean_count;
                break;
            case WaterClass::Lake:
                ++plan.lake_count;
                break;
            case WaterClass::River:
                ++plan.river_count;
                break;
            case WaterClass::Local:
                ++plan.local_count;
                break;
        }
        if (!body.shore_complete) {
            ++plan.incomplete_shore_count;
        }
        if (body.surface_height < plan.min_surface) {
            plan.min_surface = body.surface_height;
        }
        if (body.surface_height > plan.max_surface) {
            plan.max_surface = body.surface_height;
        }
    }
    return TerrainError::None;
}

}  // namespace stormline::terrain

#endif  // STORMLINE_TERRAIN_WATER_PLAN_HPP
