#include "stormline/physics3d/layer_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::physics3d;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

LayerDesc layer(u32 id, u32 bits, u32 mask, u32 group = 0) {
    LayerDesc desc{};
    desc.layer_id = id;
    desc.revision = 1;
    desc.layer_bits = bits;
    desc.mask_bits = mask;
    desc.group_index = group;
    return desc;
}

LayerSetDesc layer_set() {
    LayerSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.layer_count = 3;
    desc.layers[0] = layer(1, 0x1, 0x2);
    desc.layers[1] = layer(2, 0x2, 0x1);
    desc.layers[2] = layer(3, 0x4, 0x8);
    return desc;
}

bool run_broad301() {
    begin();
    LayerSetDesc layers = layer_set();
    LayerPlan plan{};
    Physics3DDiagnostic diagnostic{};
    expect(plan_layers(layers, plan, diagnostic) == Physics3DError::None,
           "valid layers");
    expect(plan.layer_count == 3 && plan.group_count == 0
               && plan.compatible_pair_count == 1,
           "valid plan");
    expect(diagnostic.code == Physics3DError::None, "success diagnostic");
    expect(layers_compatible(layers.layers[0], layers.layers[1]),
           "bits match");
    expect(!layers_compatible(layers.layers[0], layers.layers[2]),
           "bits differ");

    LayerDesc group_a = layer(4, 0x1, 0x1, 7);
    LayerDesc group_b = layer(5, 0x2, 0x2, 7);
    LayerDesc group_c = layer(6, 0x1, 0x1, 8);
    expect(layers_compatible(group_a, group_b), "same group overrides bits");
    expect(!layers_compatible(group_a, group_c), "different group blocks");
    expect(!layers_compatible(group_a, layers.layers[0]),
           "group vs no group");
    expect(layers_compatible(group_a, group_b)
               == layers_compatible(group_b, group_a),
           "compatibility symmetric");

    LayerPlan repeat{};
    expect(plan_layers(layers, repeat, diagnostic) == Physics3DError::None,
           "repeat layers");
    expect(repeat.compatible_pair_count == plan.compatible_pair_count,
           "deterministic plan");

    layers.world_id = 0;
    expect(plan_layers(layers, plan, diagnostic)
               == Physics3DError::InvalidArgument,
           "zero world");
    expect(plan.layer_count == 0, "reset on zero world");
    layers = layer_set();
    layers.revision = 0;
    expect(plan_layers(layers, plan, diagnostic)
               == Physics3DError::InvalidArgument,
           "zero revision");
    layers = layer_set();
    layers.layer_count = kMaxLayers + 1;
    expect(plan_layers(layers, plan, diagnostic)
               == Physics3DError::CapacityFull,
           "layer overflow");

    layers = layer_set();
    layers.layers[1].layer_id = 0;
    expect(plan_layers(layers, plan, diagnostic)
               == Physics3DError::LayerInvalid,
           "zero layer id");
    expect(diagnostic.index == 1, "zero layer diagnostic");
    layers = layer_set();
    layers.layers[1].revision = 0;
    expect(plan_layers(layers, plan, diagnostic)
               == Physics3DError::LayerInvalid,
           "zero layer revision");
    layers = layer_set();
    layers.layers[1].layer_bits = 0;
    expect(plan_layers(layers, plan, diagnostic)
               == Physics3DError::LayerInvalid,
           "zero layer bits");
    layers = layer_set();
    layers.layers[1].mask_bits = 0;
    expect(plan_layers(layers, plan, diagnostic)
               == Physics3DError::LayerInvalid,
           "zero mask bits");
    layers = layer_set();
    layers.layers[2].layer_id = 1;
    expect(plan_layers(layers, plan, diagnostic)
               == Physics3DError::DuplicateId,
           "duplicate layer");
    expect(diagnostic.index == 2, "duplicate layer diagnostic");

    layers = layer_set();
    layers.layer_count = kMaxLayers;
    for (u32 index = 0; index < kMaxLayers; ++index) {
        layers.layers[index] =
            layer(index + 1, 0x1, 0x1, index < 16 ? 1u : 0u);
    }
    expect(plan_layers(layers, plan, diagnostic) == Physics3DError::None,
           "capacity layers");
    expect(plan.layer_count == kMaxLayers && plan.group_count == 1
               && plan.compatible_pair_count == 240,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim02_layer_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "broad301") { success = run_broad301(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
