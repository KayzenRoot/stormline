#include "stormline/hybrid/layer_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::hybrid;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

HybridObjectRef object(u32 id, ObjectKind kind, f32 depth) {
    HybridObjectRef ref{};
    ref.object_id = id;
    ref.revision = 1;
    ref.kind = kind;
    ref.depth_key = depth;
    return ref;
}

HybridLayerDesc layer(u32 id, CompositionMode mode, u32 order) {
    HybridLayerDesc desc{};
    desc.layer_id = id;
    desc.revision = 1;
    desc.mode = mode;
    desc.author_order = order;
    return desc;
}

HybridLayerSetDesc scene() {
    HybridLayerSetDesc desc{};
    desc.scene_id = 10;
    desc.revision = 1;
    desc.layer_count = 3;
    desc.layers[0] = layer(1, CompositionMode::SharedDepthWorld, 0);
    desc.layers[0].depth_test = true;
    desc.layers[0].depth_write = true;
    desc.layers[0].alpha = AlphaPolicy::Opaque;
    desc.layers[0].object_count = 2;
    desc.layers[0].objects[0] = object(1, ObjectKind::Sprite, 0.5f);
    desc.layers[0].objects[1] = object(2, ObjectKind::Mesh, 2.0f);
    desc.layers[1] = layer(2, CompositionMode::OrderedCanvasOverlay, 1);
    desc.layers[1].alpha = AlphaPolicy::Masked;
    desc.layers[1].object_count = 1;
    desc.layers[1].objects[0] = object(3, ObjectKind::Ui, 0.0f);
    desc.layers[2] = layer(3, CompositionMode::IsolatedSubview, 2);
    desc.layers[2].alpha = AlphaPolicy::Blended;
    return desc;
}

bool run_lay01() {
    begin();
    HybridLayerSetDesc layers = scene();
    HybridLayerPlan plan{};
    HybridDiagnostic diagnostic{};

    expect(plan_layers(layers, plan, diagnostic) == HybridError::None,
           "valid layers");
    expect(plan.layer_count == 3 && plan.object_count == 3
               && plan.depth_write_count == 1 && plan.canvas_count == 1,
           "valid plan");
    HybridLayerPlan repeat{};
    expect(plan_layers(layers, repeat, diagnostic) == HybridError::None,
           "repeat layers");
    expect(plan.layer_count == repeat.layer_count
               && plan.object_count == repeat.object_count
               && plan.depth_write_count == repeat.depth_write_count
               && plan.canvas_count == repeat.canvas_count,
           "deterministic plan");

    layers.layer_count = 0;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "empty layers");
    expect(plan.layer_count == 0 && plan.object_count == 0,
           "reset on empty");
    layers.layer_count = kMaxHybridLayers + 1;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "layer overflow");

    layers = scene();
    layers.scene_id = 0;
    expect(plan_layers(layers, plan, diagnostic)
               == HybridError::InvalidArgument,
           "zero scene");
    layers = scene();
    layers.revision = 0;
    expect(plan_layers(layers, plan, diagnostic)
               == HybridError::InvalidArgument,
           "zero scene revision");

    layers = scene();
    layers.layers[0].layer_id = 0;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "zero layer id");
    layers = scene();
    layers.layers[0].revision = 0;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "zero layer revision");
    layers = scene();
    layers.layers[0].mode = static_cast<CompositionMode>(200);
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "invalid mode");
    layers = scene();
    layers.layers[0].alpha = static_cast<AlphaPolicy>(200);
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "invalid alpha");

    layers = scene();
    layers.layers[1].author_order = 0;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::DuplicateId,
           "duplicate order");

    layers = scene();
    layers.layers[0].object_count = kMaxHybridObjects + 1;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "object overflow");

    layers = scene();
    layers.layers[0].objects[0].object_id = 0;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "zero object id");
    layers = scene();
    layers.layers[0].objects[0].revision = 0;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "zero object revision");
    layers = scene();
    layers.layers[0].objects[0].kind = static_cast<ObjectKind>(200);
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "invalid object kind");
    layers = scene();
    layers.layers[0].objects[0].depth_key
        = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_layers(layers, plan, diagnostic)
               == HybridError::NonFiniteValue,
           "nan depth");

    layers = scene();
    layers.layers[1].objects[0].object_id = 1;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::DuplicateId,
           "duplicate object across layers");

    layers = scene();
    layers.layers[1].depth_test = true;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "canvas depth test");
    layers = scene();
    layers.layers[1].depth_write = true;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "canvas depth write");
    layers = scene();
    layers.layers[2].depth_test = true;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "subview depth test");
    layers = scene();
    layers.layers[0].depth_test = false;
    layers.layers[0].depth_write = true;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "depth write without test");
    layers = scene();
    layers.layers[0].alpha = AlphaPolicy::Blended;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::LayerInvalid,
           "blended depth write");
    layers = scene();
    layers.layers[0].alpha = AlphaPolicy::Blended;
    layers.layers[0].depth_write = false;
    expect(plan_layers(layers, plan, diagnostic) == HybridError::None,
           "blended depth test only");

    layers = scene();
    layers.layer_count = kMaxHybridLayers;
    for (u32 index = 0; index < kMaxHybridLayers; ++index) {
        layers.layers[index]
            = layer(index + 1, CompositionMode::SharedDepthWorld, index);
        layers.layers[index].object_count = 1;
        layers.layers[index].objects[0]
            = object(index + 1, ObjectKind::Sprite, 0.0f);
    }
    expect(plan_layers(layers, plan, diagnostic) == HybridError::None,
           "capacity layers");
    expect(plan.layer_count == kMaxHybridLayers
               && plan.object_count == kMaxHybridLayers,
           "capacity counts");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two04_layer_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "lay01") { success = run_lay01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
