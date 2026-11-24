#include "stormline/terrain/terrain_patch_plan.hpp"
#include "stormline/terrain/splat_plan.hpp"
#include "stormline/terrain/vegetation_plan.hpp"
#include "stormline/terrain/water_plan.hpp"
#include "stormline/terrain/sky_plan.hpp"
#include "stormline/terrain/weather_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::terrain;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

struct Plans {
    TerrainPatchPlan terrain{};
    SplatPlan splat{};
    VegetationPlan vegetation{};
    WaterPlan water{};
    SkyPlan sky{};
    WeatherPlan weather{};
    TerrainDiagnostic diagnostic{};
};

TerrainPatchSetDesc make_terrain() {
    TerrainPatchSetDesc desc{};
    desc.asset_id = 10;
    desc.revision = 1;
    desc.patch_count = 4;
    for (u32 index = 0; index < 4; ++index) {
        TerrainPatchDesc& patch = desc.patches[index];
        patch.patch_key = index + 1;
        patch.revision = 1;
        patch.tile_x = static_cast<i64>(index) - 1;
        patch.tile_z = static_cast<i64>(index);
        patch.lod = index;
        patch.topology = index % 2 == 0 ? PatchTopology::Heightfield
                                        : PatchTopology::MeshSurface;
        patch.neighbor_count = 1;
        patch.neighbors[0] = index == 3 ? 1 : index + 2;
    }
    return desc;
}

SplatSetDesc make_splat() {
    SplatSetDesc desc{};
    desc.asset_id = 11;
    desc.revision = 1;
    desc.layer_count = 4;
    for (u32 index = 0; index < 4; ++index) {
        SplatLayerDesc& layer = desc.layers[index];
        layer.layer_id = index + 1;
        layer.material_asset_id = 100 + index;
        layer.revision = 1;
        layer.weight = 0.25f;
        layer.channel = static_cast<u8>(index);
        layer.precedence = index;
    }
    return desc;
}

VegetationSetDesc make_vegetation() {
    VegetationSetDesc desc{};
    desc.asset_id = 12;
    desc.revision = 1;
    desc.group_count = 3;
    for (u32 index = 0; index < 3; ++index) {
        VegetationGroupDesc& group = desc.groups[index];
        group.group_key = index + 1;
        group.prototype_asset_id = 200 + index;
        group.revision = 1;
        group.instance_count = 32;
        group.density_limit = 64;
        group.collider_required = index == 0;
        group.min_x = -4.0f;
        group.min_z = -4.0f;
        group.max_x = 4.0f;
        group.max_z = 4.0f;
    }
    return desc;
}

WaterSetDesc make_water() {
    WaterSetDesc desc{};
    desc.asset_id = 13;
    desc.revision = 1;
    desc.body_count = 4;
    for (u32 index = 0; index < 4; ++index) {
        WaterBodyDesc& body = desc.bodies[index];
        body.body_key = index + 1;
        body.revision = 1;
        body.water_class = static_cast<WaterClass>(index % 4);
        body.min_x = -4.0f;
        body.min_z = -4.0f;
        body.max_x = 4.0f;
        body.max_z = 4.0f;
        body.surface_height = static_cast<f32>(index) - 1.0f;
        body.wave_amplitude = 0.25f;
        body.wave_frequency = 0.5f;
        body.shore_complete = index % 2 == 0;
    }
    return desc;
}

SkySetDesc make_sky() {
    SkySetDesc desc{};
    desc.asset_id = 14;
    desc.revision = 1;
    desc.profile_count = 4;
    for (u32 index = 0; index < 4; ++index) {
        SkyProfileDesc& profile = desc.profiles[index];
        profile.profile_id = index + 1;
        profile.revision = 1;
        profile.time_of_day = static_cast<f32>(index) * 6.0f;
        profile.sun_dir_x = 1.0f;
        profile.sun_dir_y = 0.5f;
        profile.sun_dir_z = 0.25f;
        profile.moon_dir_x = -1.0f;
        profile.moon_dir_y = 0.25f;
        profile.moon_dir_z = 0.5f;
        profile.cloud_coverage = 0.25f * static_cast<f32>(index);
        profile.fog_density = 0.01f;
        profile.tier = static_cast<QualityTier>(index % 4);
    }
    return desc;
}

WeatherSetDesc make_weather() {
    WeatherSetDesc desc{};
    desc.asset_id = 15;
    desc.revision = 1;
    desc.zone_count = 4;
    for (u32 index = 0; index < 4; ++index) {
        WeatherZoneDesc& zone = desc.zones[index];
        zone.zone_id = index + 1;
        zone.revision = 1;
        zone.source_tick = 100 + index;
        zone.source_revision = 1;
        zone.rain_intensity = 0.25f * static_cast<f32>(index);
        zone.snow_intensity = 0.0f;
        zone.wind_speed = 4.0f * static_cast<f32>(index);
        zone.fog_density = 0.02f;
        zone.authoritative_ack = index % 2 == 0;
    }
    return desc;
}

bool plan_all(const TerrainPatchSetDesc& terrain, const SplatSetDesc& splat,
              const VegetationSetDesc& vegetation, const WaterSetDesc& water,
              const SkySetDesc& sky, const WeatherSetDesc& weather,
              Plans& plans) {
    return plan_terrain_patches(terrain, plans.terrain, plans.diagnostic)
               == TerrainError::None
           && plan_splat_layers(splat, plans.splat, plans.diagnostic)
               == TerrainError::None
           && plan_vegetation(vegetation, plans.vegetation, plans.diagnostic)
               == TerrainError::None
           && plan_water(water, plans.water, plans.diagnostic)
               == TerrainError::None
           && plan_sky(sky, plans.sky, plans.diagnostic) == TerrainError::None
           && plan_weather(weather, plans.weather, plans.diagnostic)
               == TerrainError::None;
}

bool run_qlfw401() {
    begin();
    Plans plans{};
    expect(plan_all(make_terrain(), make_splat(), make_vegetation(),
                    make_water(), make_sky(), make_weather(), plans),
           "integrated plans");
    expect(plans.terrain.patch_count == 4 && plans.terrain.max_lod == 3
               && plans.terrain.mesh_surface_count == 2,
           "terrain plan");
    expect(plans.splat.layer_count == 4 && plans.splat.material_count == 4
               && plans.splat.total_weight == 1.0f,
           "splat plan");
    expect(plans.vegetation.group_count == 3
               && plans.vegetation.total_instances == 96
               && plans.vegetation.collider_group_count == 1,
           "vegetation plan");
    expect(plans.water.body_count == 4 && plans.water.ocean_count == 1
               && plans.water.incomplete_shore_count == 2,
           "water plan");
    expect(plans.sky.profile_count == 4 && plans.sky.low_count == 1
               && plans.sky.ultra_count == 1,
           "sky plan");
    expect(plans.weather.zone_count == 4
               && plans.weather.acknowledged_count == 2
               && plans.weather.pending_count == 2,
           "weather plan");
    expect(plans.diagnostic.code == TerrainError::None,
           "integrated diagnostic");
    return finish();
}

bool run_qlfw402() {
    begin();
    const TerrainPatchSetDesc terrain = make_terrain();
    const SplatSetDesc splat = make_splat();
    const VegetationSetDesc vegetation = make_vegetation();
    const WaterSetDesc water = make_water();
    const SkySetDesc sky = make_sky();
    const WeatherSetDesc weather = make_weather();
    Plans first{};
    expect(plan_all(terrain, splat, vegetation, water, sky, weather, first),
           "deterministic first");
    for (u32 attempt = 0; attempt < 100; ++attempt) {
        Plans repeat{};
        expect(plan_all(terrain, splat, vegetation, water, sky, weather,
                        repeat),
               "deterministic repeat success");
        expect(repeat.terrain.max_lod == first.terrain.max_lod
                   && repeat.terrain.min_tile_x == first.terrain.min_tile_x,
               "terrain identical");
        expect(repeat.splat.material_count == first.splat.material_count
                   && repeat.splat.total_weight == first.splat.total_weight,
               "splat identical");
        expect(repeat.vegetation.total_instances
                   == first.vegetation.total_instances,
               "vegetation identical");
        expect(repeat.water.min_surface == first.water.min_surface
                   && repeat.water.max_surface == first.water.max_surface,
               "water identical");
        expect(repeat.sky.max_cloud_coverage == first.sky.max_cloud_coverage,
               "sky identical");
        expect(repeat.weather.max_wind == first.weather.max_wind
                   && repeat.weather.acknowledged_count
                       == first.weather.acknowledged_count,
               "weather identical");
    }
    return finish();
}

bool run_qlfw403() {
    begin();
    Plans plans{};
    TerrainPatchSetDesc terrain = make_terrain();
    terrain.patches[2].patch_key = 1;
    expect(plan_terrain_patches(terrain, plans.terrain, plans.diagnostic)
               == TerrainError::DuplicateId,
           "terrain failure");
    expect(plans.terrain.patch_count == 0, "terrain reset");
    terrain = make_terrain();
    expect(plan_terrain_patches(terrain, plans.terrain, plans.diagnostic)
               == TerrainError::None,
           "terrain recovery");

    SplatSetDesc splat = make_splat();
    splat.layers[2].layer_id = 1;
    expect(plan_splat_layers(splat, plans.splat, plans.diagnostic)
               == TerrainError::DuplicateId,
           "splat failure");
    expect(plans.splat.layer_count == 0, "splat reset");
    splat = make_splat();
    expect(plan_splat_layers(splat, plans.splat, plans.diagnostic)
               == TerrainError::None,
           "splat recovery");

    VegetationSetDesc vegetation = make_vegetation();
    vegetation.groups[2].group_key = 1;
    expect(plan_vegetation(vegetation, plans.vegetation, plans.diagnostic)
               == TerrainError::DuplicateId,
           "vegetation failure");
    expect(plans.vegetation.group_count == 0, "vegetation reset");
    vegetation = make_vegetation();
    expect(plan_vegetation(vegetation, plans.vegetation, plans.diagnostic)
               == TerrainError::None,
           "vegetation recovery");

    WaterSetDesc water = make_water();
    water.bodies[2].body_key = 1;
    expect(plan_water(water, plans.water, plans.diagnostic)
               == TerrainError::DuplicateId,
           "water failure");
    expect(plans.water.body_count == 0, "water reset");
    water = make_water();
    expect(plan_water(water, plans.water, plans.diagnostic)
               == TerrainError::None,
           "water recovery");

    SkySetDesc sky = make_sky();
    sky.profiles[2].profile_id = 1;
    expect(plan_sky(sky, plans.sky, plans.diagnostic)
               == TerrainError::DuplicateId,
           "sky failure");
    expect(plans.sky.profile_count == 0, "sky reset");
    sky = make_sky();
    expect(plan_sky(sky, plans.sky, plans.diagnostic) == TerrainError::None,
           "sky recovery");

    WeatherSetDesc weather = make_weather();
    weather.zones[2].zone_id = 1;
    expect(plan_weather(weather, plans.weather, plans.diagnostic)
               == TerrainError::DuplicateId,
           "weather failure");
    expect(plans.weather.zone_count == 0, "weather reset");
    weather = make_weather();
    expect(plan_weather(weather, plans.weather, plans.diagnostic)
               == TerrainError::None,
           "weather recovery");
    expect(plans.diagnostic.code == TerrainError::None,
           "recovery diagnostic");
    return finish();
}

bool run_qlfw404() {
    begin();
    Plans plans{};
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        TerrainPatchSetDesc terrain = make_terrain();
        terrain.patch_count = kMaxTerrainPatches;
        for (u32 index = 0; index < kMaxTerrainPatches; ++index) {
            TerrainPatchDesc& patch = terrain.patches[index];
            patch.patch_key = static_cast<u64>(attempt) * 64ull + index + 1;
            patch.revision = 1;
            patch.tile_x = static_cast<i64>(index);
            patch.tile_z = -static_cast<i64>(index);
            patch.lod = index % (kMaxTerrainLod + 1);
            patch.topology = index % 2 == 0 ? PatchTopology::Heightfield
                                            : PatchTopology::MeshSurface;
            patch.neighbor_count = 1;
            patch.neighbors[0] =
                static_cast<u64>(attempt) * 64ull + (index + 1) % 64 + 1;
        }
        expect(plan_terrain_patches(terrain, plans.terrain, plans.diagnostic)
                   == TerrainError::None,
               "overload terrain");
        expect(plans.terrain.patch_count <= kMaxTerrainPatches,
               "terrain cap");

        SplatSetDesc splat = make_splat();
        splat.layer_count = kMaxSplatLayers;
        for (u32 index = 0; index < kMaxSplatLayers; ++index) {
            SplatLayerDesc& layer = splat.layers[index];
            layer.layer_id = index + 1;
            layer.material_asset_id = index + 1;
            layer.revision = 1;
            layer.weight = 1.0f / 16.0f;
            layer.channel = static_cast<u8>(index % 4);
            layer.precedence = index;
        }
        expect(plan_splat_layers(splat, plans.splat, plans.diagnostic)
                   == TerrainError::None,
               "overload splat");
        expect(plans.splat.layer_count <= kMaxSplatLayers, "splat cap");

        VegetationSetDesc vegetation = make_vegetation();
        vegetation.group_count = kMaxVegetationGroups;
        for (u32 index = 0; index < kMaxVegetationGroups; ++index) {
            VegetationGroupDesc& group = vegetation.groups[index];
            group.group_key = index + 1;
            group.prototype_asset_id = index + 1;
            group.revision = 1;
            group.instance_count = 128;
            group.density_limit = 128;
            group.collider_required = index % 2 == 0;
            group.min_x = -4.0f;
            group.min_z = -4.0f;
            group.max_x = 4.0f;
            group.max_z = 4.0f;
        }
        expect(plan_vegetation(vegetation, plans.vegetation, plans.diagnostic)
                   == TerrainError::None,
               "overload vegetation");
        expect(plans.vegetation.total_instances
                   <= kMaxVegetationInstances,
               "vegetation cap");

        WaterSetDesc water = make_water();
        water.body_count = kMaxWaterBodies;
        for (u32 index = 0; index < kMaxWaterBodies; ++index) {
            WaterBodyDesc& body = water.bodies[index];
            body.body_key = index + 1;
            body.revision = 1;
            body.water_class = static_cast<WaterClass>(index % 4);
            body.min_x = -4.0f;
            body.min_z = -4.0f;
            body.max_x = 4.0f;
            body.max_z = 4.0f;
            body.surface_height = static_cast<f32>(index);
            body.wave_amplitude = 0.25f;
            body.wave_frequency = 0.5f;
            body.shore_complete = true;
        }
        expect(plan_water(water, plans.water, plans.diagnostic)
                   == TerrainError::None,
               "overload water");
        expect(plans.water.body_count <= kMaxWaterBodies, "water cap");

        SkySetDesc sky = make_sky();
        sky.profile_count = kMaxSkyProfiles;
        for (u32 index = 0; index < kMaxSkyProfiles; ++index) {
            SkyProfileDesc& profile = sky.profiles[index];
            profile.profile_id = index + 1;
            profile.revision = 1;
            profile.time_of_day = static_cast<f32>(index);
            profile.sun_dir_x = 1.0f;
            profile.sun_dir_y = 0.0f;
            profile.sun_dir_z = 0.0f;
            profile.moon_dir_x = 0.0f;
            profile.moon_dir_y = 1.0f;
            profile.moon_dir_z = 0.0f;
            profile.cloud_coverage = 0.5f;
            profile.fog_density = 0.01f;
            profile.tier = static_cast<QualityTier>(index % 4);
        }
        expect(plan_sky(sky, plans.sky, plans.diagnostic)
                   == TerrainError::None,
               "overload sky");
        expect(plans.sky.profile_count <= kMaxSkyProfiles, "sky cap");

        WeatherSetDesc weather = make_weather();
        weather.zone_count = kMaxWeatherZones;
        for (u32 index = 0; index < kMaxWeatherZones; ++index) {
            WeatherZoneDesc& zone = weather.zones[index];
            zone.zone_id = index + 1;
            zone.revision = 1;
            zone.source_tick = index + 1;
            zone.source_revision = 1;
            zone.rain_intensity = 0.5f;
            zone.snow_intensity = 0.25f;
            zone.wind_speed = static_cast<f32>(index);
            zone.fog_density = 0.01f;
            zone.authoritative_ack = index % 2 == 0;
        }
        expect(plan_weather(weather, plans.weather, plans.diagnostic)
                   == TerrainError::None,
               "overload weather");
        expect(plans.weather.zone_count <= kMaxWeatherZones, "weather cap");

        if (attempt % 100 == 0) {
            terrain.patch_count = kMaxTerrainPatches + 1;
            expect(plan_terrain_patches(terrain, plans.terrain,
                                        plans.diagnostic)
                       == TerrainError::CapacityFull,
                   "overload terrain rejection");
            expect(plans.terrain.patch_count == 0, "overload terrain reset");
        }
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world04_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlfw401") { success = run_qlfw401(); }
    else if (mode == "qlfw402") { success = run_qlfw402(); }
    else if (mode == "qlfw403") { success = run_qlfw403(); }
    else if (mode == "qlfw404") { success = run_qlfw404(); }
    else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
