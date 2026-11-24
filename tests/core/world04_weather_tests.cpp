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

WeatherZoneDesc zone(
    u32 id, u32 tick, f32 rain, f32 snow, f32 wind, f32 fog, bool ack) {
    WeatherZoneDesc desc{};
    desc.zone_id = id;
    desc.revision = 1;
    desc.source_tick = tick;
    desc.source_revision = 1;
    desc.rain_intensity = rain;
    desc.snow_intensity = snow;
    desc.wind_speed = wind;
    desc.fog_density = fog;
    desc.authoritative_ack = ack;
    return desc;
}

WeatherSetDesc weather_set() {
    WeatherSetDesc desc{};
    desc.asset_id = 10;
    desc.revision = 2;
    desc.zone_count = 4;
    desc.zones[0] = zone(1, 100, 0.5f, 0.0f, 12.0f, 0.1f, true);
    desc.zones[1] = zone(2, 100, 0.0f, 0.75f, 8.0f, 0.2f, true);
    desc.zones[2] = zone(3, 101, 0.25f, 0.0f, 20.0f, 0.05f, false);
    desc.zones[3] = zone(4, 101, 0.0f, 0.0f, 2.0f, 0.0f, false);
    return desc;
}

bool run_cli01() {
    begin();
    WeatherSetDesc weather = weather_set();
    WeatherPlan plan{};
    TerrainDiagnostic diagnostic{};
    expect(plan_weather(weather, plan, diagnostic) == TerrainError::None,
           "valid weather");
    expect(plan.zone_count == 4 && plan.acknowledged_count == 2
               && plan.pending_count == 2,
           "valid ack counts");
    expect(plan.max_rain == 0.5f && plan.max_snow == 0.75f
               && plan.max_wind == 20.0f,
           "valid maxima");
    expect(diagnostic.code == TerrainError::None, "success diagnostic");
    WeatherPlan repeat{};
    expect(plan_weather(weather, repeat, diagnostic) == TerrainError::None,
           "repeat weather");
    expect(repeat.acknowledged_count == plan.acknowledged_count
               && repeat.max_wind == plan.max_wind,
           "deterministic plan");

    weather.zone_count = 0;
    expect(plan_weather(weather, plan, diagnostic) == TerrainError::None,
           "empty weather");
    expect(plan.zone_count == 0 && plan.acknowledged_count == 0,
           "empty plan");

    weather = weather_set();
    weather.asset_id = 0;
    expect(plan_weather(weather, plan, diagnostic)
               == TerrainError::InvalidArgument,
           "zero asset");
    expect(plan.zone_count == 0 && plan.max_rain == 0.0f,
           "reset on zero asset");
    weather = weather_set();
    weather.revision = 0;
    expect(plan_weather(weather, plan, diagnostic)
               == TerrainError::InvalidArgument,
           "zero revision");
    weather = weather_set();
    weather.zone_count = kMaxWeatherZones + 1;
    expect(plan_weather(weather, plan, diagnostic)
               == TerrainError::CapacityFull,
           "zone overflow");

    weather = weather_set();
    weather.zones[1].zone_id = 0;
    expect(plan_weather(weather, plan, diagnostic)
               == TerrainError::WeatherInvalid,
           "zero zone id");
    expect(diagnostic.index == 1, "zero zone diagnostic");
    weather = weather_set();
    weather.zones[1].revision = 0;
    expect(plan_weather(weather, plan, diagnostic)
               == TerrainError::WeatherInvalid,
           "zero zone revision");
    weather = weather_set();
    weather.zones[1].source_tick = 0;
    expect(plan_weather(weather, plan, diagnostic)
               == TerrainError::WeatherInvalid,
           "zero source tick");
    weather = weather_set();
    weather.zones[1].source_revision = 0;
    expect(plan_weather(weather, plan, diagnostic)
               == TerrainError::WeatherInvalid,
           "zero source revision");
    weather = weather_set();
    weather.zones[3].zone_id = 1;
    expect(plan_weather(weather, plan, diagnostic)
               == TerrainError::DuplicateId,
           "duplicate zone id");
    expect(diagnostic.index == 3, "duplicate zone diagnostic");

    weather = weather_set();
    weather.zones[0].rain_intensity =
        std::numeric_limits<f32>::quiet_NaN();
    expect(plan_weather(weather, plan, diagnostic)
               == TerrainError::NonFiniteValue,
           "nan rain");
    weather = weather_set();
    weather.zones[1].wind_speed = std::numeric_limits<f32>::infinity();
    expect(plan_weather(weather, plan, diagnostic)
               == TerrainError::NonFiniteValue,
           "infinite wind");
    weather = weather_set();
    weather.zones[0].rain_intensity = 1.5f;
    expect(plan_weather(weather, plan, diagnostic)
               == TerrainError::OutOfRange,
           "rain overflow");
    weather = weather_set();
    weather.zones[1].snow_intensity = -0.1f;
    expect(plan_weather(weather, plan, diagnostic)
               == TerrainError::OutOfRange,
           "negative snow");
    weather = weather_set();
    weather.zones[2].wind_speed = -1.0f;
    expect(plan_weather(weather, plan, diagnostic)
               == TerrainError::OutOfRange,
           "negative wind");

    weather = weather_set();
    weather.zone_count = kMaxWeatherZones;
    for (u32 index = 0; index < kMaxWeatherZones; ++index) {
        weather.zones[index] =
            zone(index + 1, index + 1, 0.5f, 0.25f,
                 static_cast<f32>(index), 0.01f, index % 2 == 0);
    }
    expect(plan_weather(weather, plan, diagnostic) == TerrainError::None,
           "capacity weather");
    expect(plan.zone_count == kMaxWeatherZones
               && plan.acknowledged_count == 16
               && plan.pending_count == 16,
           "capacity ack counts");
    expect(plan.max_rain == 0.5f && plan.max_snow == 0.25f
               && plan.max_wind == 31.0f,
           "capacity maxima");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world04_weather_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "cli01") { success = run_cli01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
