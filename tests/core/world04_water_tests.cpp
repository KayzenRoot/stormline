#include "stormline/terrain/water_plan.hpp"

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

WaterBodyDesc body(
    u64 key, WaterClass water_class, f32 surface, bool shore_complete) {
    WaterBodyDesc desc{};
    desc.body_key = key;
    desc.revision = 1;
    desc.water_class = water_class;
    desc.min_x = -4.0f;
    desc.min_z = -2.0f;
    desc.max_x = 4.0f;
    desc.max_z = 2.0f;
    desc.surface_height = surface;
    desc.wave_amplitude = 0.5f;
    desc.wave_frequency = 0.25f;
    desc.shore_complete = shore_complete;
    return desc;
}

WaterSetDesc water_set() {
    WaterSetDesc desc{};
    desc.asset_id = 10;
    desc.revision = 2;
    desc.body_count = 4;
    desc.bodies[0] = body(1, WaterClass::Ocean, -1.0f, true);
    desc.bodies[1] = body(2, WaterClass::Lake, 2.5f, true);
    desc.bodies[2] = body(3, WaterClass::River, 0.0f, false);
    desc.bodies[3] = body(4, WaterClass::Local, 1.0f, false);
    return desc;
}

bool run_wat01() {
    begin();
    WaterSetDesc water = water_set();
    WaterPlan plan{};
    TerrainDiagnostic diagnostic{};
    expect(plan_water(water, plan, diagnostic) == TerrainError::None,
           "valid water");
    expect(plan.body_count == 4 && plan.ocean_count == 1
               && plan.lake_count == 1 && plan.river_count == 1
               && plan.local_count == 1,
           "valid class counts");
    expect(plan.incomplete_shore_count == 2, "shore completeness");
    expect(plan.min_surface == -1.0f && plan.max_surface == 2.5f,
           "surface bounds");
    expect(diagnostic.code == TerrainError::None, "success diagnostic");
    WaterPlan repeat{};
    expect(plan_water(water, repeat, diagnostic) == TerrainError::None,
           "repeat water");
    expect(repeat.min_surface == plan.min_surface
               && repeat.max_surface == plan.max_surface
               && repeat.ocean_count == plan.ocean_count,
           "deterministic plan");

    water.body_count = 0;
    expect(plan_water(water, plan, diagnostic) == TerrainError::None,
           "empty water");
    expect(plan.body_count == 0 && plan.min_surface == 0.0f,
           "empty plan");

    water = water_set();
    water.asset_id = 0;
    expect(plan_water(water, plan, diagnostic)
               == TerrainError::InvalidArgument,
           "zero asset");
    expect(plan.body_count == 0 && plan.ocean_count == 0,
           "reset on zero asset");
    water = water_set();
    water.revision = 0;
    expect(plan_water(water, plan, diagnostic)
               == TerrainError::InvalidArgument,
           "zero revision");
    water = water_set();
    water.body_count = kMaxWaterBodies + 1;
    expect(plan_water(water, plan, diagnostic)
               == TerrainError::CapacityFull,
           "body overflow");

    water = water_set();
    water.bodies[1].body_key = 0;
    expect(plan_water(water, plan, diagnostic)
               == TerrainError::WaterInvalid,
           "zero body key");
    expect(diagnostic.index == 1, "zero key diagnostic");
    water = water_set();
    water.bodies[1].revision = 0;
    expect(plan_water(water, plan, diagnostic)
               == TerrainError::WaterInvalid,
           "zero body revision");
    water = water_set();
    water.bodies[2].water_class =
        static_cast<WaterClass>(static_cast<u8>(99));
    expect(plan_water(water, plan, diagnostic)
               == TerrainError::WaterInvalid,
           "unknown class");
    water = water_set();
    water.bodies[3].body_key = 1;
    expect(plan_water(water, plan, diagnostic)
               == TerrainError::DuplicateId,
           "duplicate body key");
    expect(diagnostic.index == 3, "duplicate key diagnostic");

    water = water_set();
    water.bodies[0].min_x = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_water(water, plan, diagnostic)
               == TerrainError::NonFiniteValue,
           "nan bounds");
    water = water_set();
    water.bodies[1].surface_height =
        std::numeric_limits<f32>::infinity();
    expect(plan_water(water, plan, diagnostic)
               == TerrainError::NonFiniteValue,
           "infinite surface");
    water = water_set();
    water.bodies[2].max_z = -3.0f;
    expect(plan_water(water, plan, diagnostic)
               == TerrainError::WaterInvalid,
           "reversed bounds");
    water = water_set();
    water.bodies[0].wave_amplitude = -0.5f;
    expect(plan_water(water, plan, diagnostic)
               == TerrainError::WaterInvalid,
           "negative amplitude");
    water = water_set();
    water.bodies[0].wave_frequency = 0.0f;
    expect(plan_water(water, plan, diagnostic)
               == TerrainError::WaterInvalid,
           "zero frequency");

    water = water_set();
    water.body_count = kMaxWaterBodies;
    for (u32 index = 0; index < kMaxWaterBodies; ++index) {
        water.bodies[index] =
            body(static_cast<u64>(index) + 1,
                 static_cast<WaterClass>(index % 4),
                 static_cast<f32>(index) - 16.0f, index % 2 == 0);
    }
    expect(plan_water(water, plan, diagnostic) == TerrainError::None,
           "capacity water");
    expect(plan.body_count == kMaxWaterBodies
               && plan.ocean_count == 8 && plan.lake_count == 8
               && plan.river_count == 8 && plan.local_count == 8,
           "capacity class counts");
    expect(plan.incomplete_shore_count == 16, "capacity shore count");
    expect(plan.min_surface == -16.0f && plan.max_surface == 15.0f,
           "capacity surface bounds");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world04_water_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "wat01") { success = run_wat01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
