#include "stormline/procedural/biome_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::procedural;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

BiomeZoneDesc zone(
    u32 id, u32 palette, f32 weight, u32 priority, bool enabled) {
    BiomeZoneDesc desc{};
    desc.zone_id = id;
    desc.revision = 1;
    desc.palette_asset_id = palette;
    desc.weight = weight;
    desc.priority = priority;
    desc.enabled = enabled;
    return desc;
}

BiomeSetDesc biome_set() {
    BiomeSetDesc desc{};
    desc.graph_id = 20;
    desc.revision = 1;
    desc.zone_count = 3;
    desc.zones[0] = zone(1, 100, 0.5f, 1, true);
    desc.zones[1] = zone(2, 101, 0.25f, 4, true);
    desc.zones[2] = zone(3, 102, 0.75f, 2, false);
    return desc;
}

bool run_biome01() {
    begin();
    BiomeSetDesc biomes = biome_set();
    BiomePlan plan{};
    ProcDiagnostic diagnostic{};
    expect(plan_biomes(biomes, plan, diagnostic) == ProcError::None,
           "valid biomes");
    expect(plan.zone_count == 3 && plan.enabled_count == 2
               && plan.total_weight == 1.5f && plan.max_priority == 4,
           "valid plan");
    expect(diagnostic.code == ProcError::None, "success diagnostic");
    BiomePlan repeat{};
    expect(plan_biomes(biomes, repeat, diagnostic) == ProcError::None,
           "repeat biomes");
    expect(repeat.enabled_count == plan.enabled_count
               && repeat.max_priority == plan.max_priority,
           "deterministic plan");

    biomes.graph_id = 0;
    expect(plan_biomes(biomes, plan, diagnostic)
               == ProcError::InvalidArgument,
           "zero graph");
    expect(plan.zone_count == 0 && plan.total_weight == 0.0f,
           "reset on zero graph");
    biomes = biome_set();
    biomes.revision = 0;
    expect(plan_biomes(biomes, plan, diagnostic)
               == ProcError::InvalidArgument,
           "zero revision");
    biomes = biome_set();
    biomes.zone_count = 0;
    expect(plan_biomes(biomes, plan, diagnostic) == ProcError::BiomeInvalid,
           "zero zones");
    biomes.zone_count = kMaxBiomeZones + 1;
    expect(plan_biomes(biomes, plan, diagnostic) == ProcError::CapacityFull,
           "zone overflow");

    biomes = biome_set();
    biomes.zones[1].zone_id = 0;
    expect(plan_biomes(biomes, plan, diagnostic) == ProcError::BiomeInvalid,
           "zero zone id");
    expect(diagnostic.index == 1, "zero zone diagnostic");
    biomes = biome_set();
    biomes.zones[1].revision = 0;
    expect(plan_biomes(biomes, plan, diagnostic) == ProcError::BiomeInvalid,
           "zero zone revision");
    biomes = biome_set();
    biomes.zones[1].palette_asset_id = 0;
    expect(plan_biomes(biomes, plan, diagnostic) == ProcError::BiomeInvalid,
           "zero palette");
    biomes = biome_set();
    biomes.zones[2].zone_id = 1;
    expect(plan_biomes(biomes, plan, diagnostic) == ProcError::DuplicateId,
           "duplicate zone");
    expect(diagnostic.index == 2, "duplicate zone diagnostic");

    biomes = biome_set();
    biomes.zones[0].weight = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_biomes(biomes, plan, diagnostic) == ProcError::OutOfRange,
           "nan weight");
    biomes = biome_set();
    biomes.zones[0].weight = -0.1f;
    expect(plan_biomes(biomes, plan, diagnostic) == ProcError::OutOfRange,
           "negative weight");
    biomes = biome_set();
    biomes.zones[0].weight = 1.1f;
    expect(plan_biomes(biomes, plan, diagnostic) == ProcError::OutOfRange,
           "weight above one");

    biomes = biome_set();
    biomes.zone_count = kMaxBiomeZones;
    for (u32 index = 0; index < kMaxBiomeZones; ++index) {
        biomes.zones[index] = zone(index + 1, index + 1, 1.0f, index,
                                   index % 2 == 0);
    }
    expect(plan_biomes(biomes, plan, diagnostic) == ProcError::None,
           "capacity biomes");
    expect(plan.zone_count == kMaxBiomeZones && plan.enabled_count == 8
               && plan.total_weight == 16.0f && plan.max_priority == 15,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world05_biome_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "biome01") { success = run_biome01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
