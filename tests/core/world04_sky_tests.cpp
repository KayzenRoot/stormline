#include "stormline/terrain/sky_plan.hpp"

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

SkyProfileDesc profile(
    u32 id, f32 time_of_day, f32 cloud, f32 fog, QualityTier tier) {
    SkyProfileDesc desc{};
    desc.profile_id = id;
    desc.revision = 1;
    desc.time_of_day = time_of_day;
    desc.sun_dir_x = 1.0f;
    desc.sun_dir_y = 0.5f;
    desc.sun_dir_z = 0.25f;
    desc.moon_dir_x = -1.0f;
    desc.moon_dir_y = 0.25f;
    desc.moon_dir_z = 0.5f;
    desc.cloud_coverage = cloud;
    desc.fog_density = fog;
    desc.tier = tier;
    return desc;
}

SkySetDesc sky_set() {
    SkySetDesc desc{};
    desc.asset_id = 10;
    desc.revision = 2;
    desc.profile_count = 4;
    desc.profiles[0] = profile(1, 6.0f, 0.25f, 0.01f, QualityTier::Low);
    desc.profiles[1] = profile(2, 12.0f, 0.5f, 0.02f, QualityTier::Medium);
    desc.profiles[2] = profile(3, 18.0f, 0.75f, 0.03f, QualityTier::High);
    desc.profiles[3] = profile(4, 23.5f, 1.0f, 0.04f, QualityTier::Ultra);
    return desc;
}

bool run_sky01() {
    begin();
    SkySetDesc sky = sky_set();
    SkyPlan plan{};
    TerrainDiagnostic diagnostic{};
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::None,
           "valid sky");
    expect(plan.profile_count == 4 && plan.low_count == 1
               && plan.medium_count == 1 && plan.high_count == 1
               && plan.ultra_count == 1,
           "valid tier counts");
    expect(plan.max_cloud_coverage == 1.0f, "valid max cloud");
    expect(diagnostic.code == TerrainError::None, "success diagnostic");
    SkyPlan repeat{};
    expect(plan_sky(sky, repeat, diagnostic) == TerrainError::None,
           "repeat sky");
    expect(repeat.max_cloud_coverage == plan.max_cloud_coverage
               && repeat.ultra_count == plan.ultra_count,
           "deterministic plan");

    sky.asset_id = 0;
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::InvalidArgument,
           "zero asset");
    expect(plan.profile_count == 0 && plan.low_count == 0,
           "reset on zero asset");
    sky = sky_set();
    sky.revision = 0;
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::InvalidArgument,
           "zero revision");
    sky = sky_set();
    sky.profile_count = 0;
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::SkyInvalid,
           "zero count");
    sky.profile_count = kMaxSkyProfiles + 1;
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::CapacityFull,
           "count overflow");

    sky = sky_set();
    sky.profiles[1].profile_id = 0;
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::SkyInvalid,
           "zero profile id");
    expect(diagnostic.index == 1, "zero profile diagnostic");
    sky = sky_set();
    sky.profiles[1].revision = 0;
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::SkyInvalid,
           "zero profile revision");
    sky = sky_set();
    sky.profiles[2].tier =
        static_cast<QualityTier>(static_cast<u8>(99));
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::SkyInvalid,
           "unknown tier");
    sky = sky_set();
    sky.profiles[3].profile_id = 1;
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::DuplicateId,
           "duplicate profile id");
    expect(diagnostic.index == 3, "duplicate profile diagnostic");

    sky = sky_set();
    sky.profiles[0].time_of_day = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::NonFiniteValue,
           "nan time");
    sky = sky_set();
    sky.profiles[1].sun_dir_x = std::numeric_limits<f32>::infinity();
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::NonFiniteValue,
           "infinite direction");
    sky = sky_set();
    sky.profiles[0].time_of_day = 24.0f;
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::OutOfRange,
           "time overflow");
    sky = sky_set();
    sky.profiles[1].cloud_coverage = 1.5f;
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::OutOfRange,
           "cloud overflow");
    sky = sky_set();
    sky.profiles[2].fog_density = -0.1f;
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::OutOfRange,
           "negative fog");
    sky = sky_set();
    sky.profiles[0].sun_dir_x = 0.0f;
    sky.profiles[0].sun_dir_y = 0.0f;
    sky.profiles[0].sun_dir_z = 0.0f;
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::SkyInvalid,
           "zero sun direction");
    sky = sky_set();
    sky.profiles[1].moon_dir_x = 0.0f;
    sky.profiles[1].moon_dir_y = 0.0f;
    sky.profiles[1].moon_dir_z = 0.0f;
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::SkyInvalid,
           "zero moon direction");

    sky = sky_set();
    sky.profile_count = kMaxSkyProfiles;
    for (u32 index = 0; index < kMaxSkyProfiles; ++index) {
        sky.profiles[index] =
            profile(index + 1, static_cast<f32>(index) * 1.5f,
                    static_cast<f32>(index) / 16.0f, 0.01f,
                    static_cast<QualityTier>(index % 4));
    }
    expect(plan_sky(sky, plan, diagnostic) == TerrainError::None,
           "capacity sky");
    expect(plan.profile_count == kMaxSkyProfiles && plan.low_count == 4
               && plan.medium_count == 4 && plan.high_count == 4
               && plan.ultra_count == 4,
           "capacity tier counts");
    expect(plan.max_cloud_coverage == 15.0f / 16.0f,
           "capacity max cloud");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world04_sky_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "sky01") { success = run_sky01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
