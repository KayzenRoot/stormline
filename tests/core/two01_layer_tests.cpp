#include "stormline/graphics/canvas2d/layer_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::graphics::canvas2d;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

CanvasLayerSet valid_layers() {
    CanvasLayerSet set{};
    set.count = 3;
    set.layers[0] = CanvasLayerDesc{5, 1, 2, 1.0f, BlendMode::Blend, true, 0};
    set.layers[1] = CanvasLayerDesc{6, 1, 0, 0.5f, BlendMode::Opaque, true, 1};
    set.layers[2] = CanvasLayerDesc{7, 1, 1, 0.75f, BlendMode::Additive, true, 2};
    return set;
}

bool run_lay01() {
    begin();
    CanvasLayerSet layers = valid_layers();
    LayerPlan plan{};
    CanvasDiagnostic diagnostic{};

    expect(plan_layers(layers, plan, diagnostic) == CanvasError::None,
           "valid layers");
    expect(plan.count == 3 && plan.order[0] == 6 && plan.order[1] == 7
               && plan.order[2] == 5,
           "painter order");

    layers.layers[1].layer_id = 5;
    expect(plan_layers(layers, plan, diagnostic) == CanvasError::DuplicateId,
           "duplicate id");
    expect(plan.count == 0, "reset");

    layers = valid_layers();
    layers.layers[1].order = 2;
    expect(plan_layers(layers, plan, diagnostic)
               == CanvasError::LayerOrderInvalid,
           "duplicate order");
    layers = valid_layers();
    layers.layers[1].order = 5;
    expect(plan_layers(layers, plan, diagnostic) == CanvasError::None,
           "noncontiguous order");
    expect(plan.order[0] == 7 && plan.order[1] == 5 && plan.order[2] == 6,
           "noncontiguous sorted");
    layers = valid_layers();
    layers.layers[0].opacity = 1.5f;
    expect(plan_layers(layers, plan, diagnostic) == CanvasError::OutOfRange,
           "opacity range");
    layers = valid_layers();
    layers.layers[0].opacity = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_layers(layers, plan, diagnostic)
               == CanvasError::NonFiniteValue,
           "nonfinite opacity");
    layers = valid_layers();
    layers.layers[0].clip_depth = 9;
    expect(plan_layers(layers, plan, diagnostic) == CanvasError::OutOfRange,
           "clip depth");
    layers = valid_layers();
    layers.layers[0].blend = static_cast<BlendMode>(200);
    expect(plan_layers(layers, plan, diagnostic)
               == CanvasError::InvalidArgument,
           "invalid blend");
    layers = valid_layers();
    layers.count = kMaxLayers + 1;
    expect(plan_layers(layers, plan, diagnostic) == CanvasError::CapacityFull,
           "layer cap");
    layers = valid_layers();
    layers.layers[0].revision = 0;
    expect(plan_layers(layers, plan, diagnostic)
               == CanvasError::InvalidArgument,
           "zero revision");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two01_layer_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "lay01") { success = run_lay01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
