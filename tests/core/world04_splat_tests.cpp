#include "stormline/terrain/splat_plan.hpp"

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

SplatLayerDesc layer(
    u32 layer_id, u32 material_id, f32 weight, u8 channel,
    u32 precedence = 0) {
    SplatLayerDesc desc{};
    desc.layer_id = layer_id;
    desc.material_asset_id = material_id;
    desc.revision = 1;
    desc.weight = weight;
    desc.channel = channel;
    desc.precedence = precedence;
    return desc;
}

SplatSetDesc splat_set() {
    SplatSetDesc desc{};
    desc.asset_id = 10;
    desc.revision = 2;
    desc.layer_count = 4;
    desc.layers[0] = layer(1, 100, 0.25f, 0, 0);
    desc.layers[1] = layer(2, 101, 0.25f, 1, 1);
    desc.layers[2] = layer(3, 102, 0.25f, 2, 2);
    desc.layers[3] = layer(4, 103, 0.25f, 3, 3);
    return desc;
}

bool run_spl01() {
    begin();
    SplatSetDesc splat = splat_set();
    SplatPlan plan{};
    TerrainDiagnostic diagnostic{};
    expect(plan_splat_layers(splat, plan, diagnostic) == TerrainError::None,
           "valid splat");
    expect(plan.layer_count == 4 && plan.material_count == 4
               && plan.total_weight == 1.0f,
           "valid plan");
    expect(diagnostic.code == TerrainError::None, "success diagnostic");
    SplatPlan repeat{};
    expect(plan_splat_layers(splat, repeat, diagnostic) == TerrainError::None,
           "repeat splat");
    expect(repeat.material_count == plan.material_count
               && repeat.total_weight == plan.total_weight,
           "deterministic plan");

    splat.layers[3].material_asset_id = 100;
    expect(plan_splat_layers(splat, plan, diagnostic) == TerrainError::None,
           "shared material");
    expect(plan.material_count == 3, "distinct material count");
    splat = splat_set();
    splat.asset_id = 0;
    expect(plan_splat_layers(splat, plan, diagnostic)
               == TerrainError::InvalidArgument,
           "zero asset");
    expect(plan.layer_count == 0 && plan.material_count == 0,
           "reset on zero asset");
    splat = splat_set();
    splat.revision = 0;
    expect(plan_splat_layers(splat, plan, diagnostic)
               == TerrainError::InvalidArgument,
           "zero revision");
    splat = splat_set();
    splat.layer_count = 0;
    expect(plan_splat_layers(splat, plan, diagnostic)
               == TerrainError::SplatInvalid,
           "zero count");
    splat.layer_count = kMaxSplatLayers + 1;
    expect(plan_splat_layers(splat, plan, diagnostic)
               == TerrainError::CapacityFull,
           "count overflow");

    splat = splat_set();
    splat.layers[1].layer_id = 0;
    expect(plan_splat_layers(splat, plan, diagnostic)
               == TerrainError::SplatInvalid,
           "zero layer id");
    expect(diagnostic.index == 1, "zero layer diagnostic");
    splat = splat_set();
    splat.layers[1].material_asset_id = 0;
    expect(plan_splat_layers(splat, plan, diagnostic)
               == TerrainError::SplatInvalid,
           "zero material");
    splat = splat_set();
    splat.layers[2].revision = 0;
    expect(plan_splat_layers(splat, plan, diagnostic)
               == TerrainError::SplatInvalid,
           "zero layer revision");
    splat = splat_set();
    splat.layers[0].channel = 4;
    expect(plan_splat_layers(splat, plan, diagnostic)
               == TerrainError::SplatInvalid,
           "channel overflow");
    splat = splat_set();
    splat.layers[3].layer_id = 1;
    expect(plan_splat_layers(splat, plan, diagnostic)
               == TerrainError::DuplicateId,
           "duplicate layer id");
    expect(diagnostic.index == 3, "duplicate layer diagnostic");

    splat = splat_set();
    splat.layers[0].weight =
        std::numeric_limits<f32>::quiet_NaN();
    expect(plan_splat_layers(splat, plan, diagnostic)
               == TerrainError::NonFiniteValue,
           "nan weight");
    splat = splat_set();
    splat.layers[0].weight = -0.1f;
    expect(plan_splat_layers(splat, plan, diagnostic)
               == TerrainError::NonFiniteValue,
           "negative weight");
    splat = splat_set();
    splat.layers[0].weight = 1.1f;
    expect(plan_splat_layers(splat, plan, diagnostic)
               == TerrainError::NonFiniteValue,
           "weight above one");
    splat = splat_set();
    splat.layers[0].weight = 0.6f;
    splat.layers[1].weight = 0.6f;
    expect(plan_splat_layers(splat, plan, diagnostic)
               == TerrainError::OutOfRange,
           "total weight overflow");
    expect(diagnostic.index == 1, "total weight diagnostic");

    splat = splat_set();
    splat.layer_count = kMaxSplatLayers;
    for (u32 index = 0; index < kMaxSplatLayers; ++index) {
        splat.layers[index] =
            layer(index + 1, index + 1, 1.0f / 16.0f,
                  static_cast<u8>(index % 4), index);
    }
    expect(plan_splat_layers(splat, plan, diagnostic) == TerrainError::None,
           "capacity splat");
    expect(plan.layer_count == kMaxSplatLayers
               && plan.material_count == kMaxSplatLayers
               && plan.total_weight == 1.0f,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world04_splat_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "spl01") { success = run_spl01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
