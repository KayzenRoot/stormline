#ifndef STORMLINE_TERRAIN_WEATHER_PLAN_HPP
#define STORMLINE_TERRAIN_WEATHER_PLAN_HPP

#include <array>

#include "stormline/terrain/terrain_types.hpp"

namespace stormline::terrain {

struct WeatherZoneDesc {
    u32 zone_id{0};
    u32 revision{0};
    u32 source_tick{0};
    u32 source_revision{0};
    f32 rain_intensity{0.0f};
    f32 snow_intensity{0.0f};
    f32 wind_speed{0.0f};
    f32 fog_density{0.0f};
    bool authoritative_ack{false};
};

struct WeatherSetDesc {
    u32 asset_id{0};
    u32 revision{0};
    u32 zone_count{0};
    std::array<WeatherZoneDesc, kMaxWeatherZones> zones{};
};

struct WeatherPlan {
    u32 zone_count{0};
    u32 acknowledged_count{0};
    u32 pending_count{0};
    f32 max_rain{0.0f};
    f32 max_snow{0.0f};
    f32 max_wind{0.0f};
};

[[nodiscard]] inline TerrainError plan_weather(
    const WeatherSetDesc& weather, WeatherPlan& plan,
    TerrainDiagnostic& diagnostic) noexcept {
    plan = WeatherPlan{};
    diagnostic = TerrainDiagnostic{};
    if (weather.asset_id == 0 || weather.revision == 0) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::InvalidArgument, weather.asset_id, 0);
    }
    if (weather.zone_count > kMaxWeatherZones) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::CapacityFull, weather.asset_id, 0);
    }
    for (u32 index = 0; index < weather.zone_count; ++index) {
        const WeatherZoneDesc& zone = weather.zones[index];
        if (zone.zone_id == 0 || zone.revision == 0 || zone.source_tick == 0
            || zone.source_revision == 0) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::WeatherInvalid, weather.asset_id,
                index);
        }
        if (!detail::finite(zone.rain_intensity)
            || !detail::finite(zone.snow_intensity)
            || !detail::finite(zone.wind_speed)
            || !detail::finite(zone.fog_density)) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::NonFiniteValue, weather.asset_id,
                index);
        }
        if (!(zone.rain_intensity >= 0.0f)
            || !(zone.rain_intensity <= 1.0f)
            || !(zone.snow_intensity >= 0.0f)
            || !(zone.snow_intensity <= 1.0f)
            || !(zone.wind_speed >= 0.0f)
            || !(zone.fog_density >= 0.0f)) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::OutOfRange, weather.asset_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (weather.zones[previous].zone_id == zone.zone_id) {
                return detail::set_terrain_error(
                    diagnostic, TerrainError::DuplicateId, weather.asset_id,
                    index);
            }
        }
    }
    plan.zone_count = weather.zone_count;
    for (u32 index = 0; index < weather.zone_count; ++index) {
        const WeatherZoneDesc& zone = weather.zones[index];
        if (zone.authoritative_ack) {
            ++plan.acknowledged_count;
        } else {
            ++plan.pending_count;
        }
        if (zone.rain_intensity > plan.max_rain) {
            plan.max_rain = zone.rain_intensity;
        }
        if (zone.snow_intensity > plan.max_snow) {
            plan.max_snow = zone.snow_intensity;
        }
        if (zone.wind_speed > plan.max_wind) {
            plan.max_wind = zone.wind_speed;
        }
    }
    return TerrainError::None;
}

}  // namespace stormline::terrain

#endif  // STORMLINE_TERRAIN_WEATHER_PLAN_HPP
