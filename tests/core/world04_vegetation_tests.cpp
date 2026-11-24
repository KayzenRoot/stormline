#include "stormline/terrain/vegetation_plan.hpp"

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

VegetationGroupDesc group(
    u64 key, u32 prototype, u32 instances, u32 density, bool collider) {
    VegetationGroupDesc desc{};
    desc.group_key = key;
    desc.prototype_asset_id = prototype;
    desc.revision = 1;
    desc.instance_count = instances;
    desc.density_limit = density;
    desc.collider_required = collider;
    desc.min_x = -4.0f;
    desc.min_z = -2.0f;
    desc.max_x = 4.0f;
    desc.max_z = 2.0f;
    return desc;
}

VegetationSetDesc vegetation_set() {
    VegetationSetDesc desc{};
    desc.asset_id = 10;
    desc.revision = 2;
    desc.group_count = 3;
    desc.groups[0] = group(1, 100, 64, 128, true);
    desc.groups[1] = group(2, 101, 32, 64, false);
    desc.groups[2] = group(3, 102, 16, 32, true);
    return desc;
}

bool run_veg01() {
    begin();
    VegetationSetDesc vegetation = vegetation_set();
    VegetationPlan plan{};
    TerrainDiagnostic diagnostic{};
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::None,
           "valid vegetation");
    expect(plan.group_count == 3 && plan.total_instances == 112
               && plan.collider_group_count == 2,
           "valid plan");
    expect(diagnostic.code == TerrainError::None, "success diagnostic");
    VegetationPlan repeat{};
    expect(plan_vegetation(vegetation, repeat, diagnostic)
               == TerrainError::None,
           "repeat vegetation");
    expect(repeat.total_instances == plan.total_instances
               && repeat.collider_group_count == plan.collider_group_count,
           "deterministic plan");

    vegetation.group_count = 0;
    expect(plan_vegetation(vegetation, plan, diagnostic) == TerrainError::None,
           "empty vegetation");
    expect(plan.group_count == 0 && plan.total_instances == 0,
           "empty plan");

    vegetation = vegetation_set();
    vegetation.asset_id = 0;
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::InvalidArgument,
           "zero asset");
    expect(plan.group_count == 0 && plan.total_instances == 0,
           "reset on zero asset");
    vegetation = vegetation_set();
    vegetation.revision = 0;
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::InvalidArgument,
           "zero revision");
    vegetation = vegetation_set();
    vegetation.group_count = kMaxVegetationGroups + 1;
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::CapacityFull,
           "group overflow");

    vegetation = vegetation_set();
    vegetation.groups[1].group_key = 0;
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::VegetationInvalid,
           "zero group key");
    expect(diagnostic.index == 1, "zero key diagnostic");
    vegetation = vegetation_set();
    vegetation.groups[1].prototype_asset_id = 0;
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::VegetationInvalid,
           "zero prototype");
    vegetation = vegetation_set();
    vegetation.groups[1].revision = 0;
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::VegetationInvalid,
           "zero group revision");
    vegetation = vegetation_set();
    vegetation.groups[0].instance_count = 0;
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::VegetationInvalid,
           "zero instances");
    vegetation = vegetation_set();
    vegetation.groups[0].instance_count = 129;
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::VegetationInvalid,
           "instances above density");
    vegetation = vegetation_set();
    vegetation.groups[0].density_limit = kMaxVegetationInstances + 1;
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::VegetationInvalid,
           "density overflow");
    vegetation = vegetation_set();
    vegetation.groups[2].group_key = 1;
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::DuplicateId,
           "duplicate group key");
    expect(diagnostic.index == 2, "duplicate group diagnostic");

    vegetation = vegetation_set();
    vegetation.groups[0].min_x = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::NonFiniteValue,
           "nan bounds");
    vegetation = vegetation_set();
    vegetation.groups[0].max_z = std::numeric_limits<f32>::infinity();
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::NonFiniteValue,
           "infinite bounds");
    vegetation = vegetation_set();
    vegetation.groups[0].min_x = 4.0f;
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::OutOfRange,
           "reversed bounds");
    expect(diagnostic.index == 0, "reversed bounds diagnostic");

    vegetation = vegetation_set();
    vegetation.group_count = 2;
    vegetation.groups[0] = group(1, 100, 3000, 4096, false);
    vegetation.groups[1] = group(2, 101, 3000, 4096, false);
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::OutOfRange,
           "total instance overflow");
    expect(plan.total_instances == 0, "reset on total overflow");

    vegetation = vegetation_set();
    vegetation.group_count = kMaxVegetationGroups;
    for (u32 index = 0; index < kMaxVegetationGroups; ++index) {
        vegetation.groups[index] =
            group(static_cast<u64>(index) + 1, index + 1, 128, 128,
                  index % 2 == 0);
    }
    expect(plan_vegetation(vegetation, plan, diagnostic)
               == TerrainError::None,
           "capacity vegetation");
    expect(plan.group_count == kMaxVegetationGroups
               && plan.total_instances == kMaxVegetationInstances
               && plan.collider_group_count == 16,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world04_vegetation_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "veg01") { success = run_veg01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
