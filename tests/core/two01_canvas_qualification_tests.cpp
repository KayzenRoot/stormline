#include "stormline/graphics/canvas2d/atlas_plan.hpp"
#include "stormline/graphics/canvas2d/camera_plan.hpp"
#include "stormline/graphics/canvas2d/layer_plan.hpp"
#include "stormline/graphics/canvas2d/light_plan.hpp"
#include "stormline/graphics/canvas2d/snap_plan.hpp"
#include "stormline/graphics/canvas2d/sprite_plan.hpp"

#include <cstdio>
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

struct Pipeline {
    SpritePlan sprite{};
    AtlasPlan atlas{};
    LayerPlan layers{};
    CameraPlan camera{};
    SnapPlan snap{};
    LightPlan light{};
    CanvasDiagnostic diagnostic{};
};

SpriteDrawDesc sprite_desc() {
    SpriteDrawDesc sprite{};
    sprite.sprite_id = 7;
    sprite.revision = 1;
    sprite.asset_id = 21;
    sprite.asset_revision = 1;
    sprite.atlas_id = 4;
    sprite.layer_id = 1;
    sprite.region_width = 32;
    sprite.region_height = 48;
    sprite.pivot_x = 0.5f;
    sprite.pivot_y = 0.5f;
    return sprite;
}

AtlasDesc atlas_desc() {
    AtlasDesc atlas{};
    atlas.atlas_id = 4;
    atlas.revision = 1;
    atlas.width = 512;
    atlas.height = 512;
    atlas.gutter = 2;
    atlas.mip_count = 3;
    atlas.region_count = 1;
    atlas.regions[0] = AtlasRegion{10, 1, 0, 0, 32, 48};
    return atlas;
}

CanvasLayerSet layer_set() {
    CanvasLayerSet set{};
    set.count = 3;
    set.layers[0] = CanvasLayerDesc{5, 1, 2, 1.0f, BlendMode::Blend, true, 0};
    set.layers[1] = CanvasLayerDesc{6, 1, 0, 0.5f, BlendMode::Opaque, true, 1};
    set.layers[2] = CanvasLayerDesc{7, 1, 1, 0.75f, BlendMode::Additive, true, 2};
    return set;
}

bool run_pipeline(Pipeline& pipeline) {
    pipeline = Pipeline{};
    if (plan_sprite(sprite_desc(), pipeline.sprite, pipeline.diagnostic)
        != CanvasError::None) {
        return false;
    }
    if (plan_atlas(atlas_desc(), pipeline.atlas, pipeline.diagnostic)
        != CanvasError::None) {
        return false;
    }
    if (plan_layers(layer_set(), pipeline.layers, pipeline.diagnostic)
        != CanvasError::None) {
        return false;
    }
    CanvasCameraDesc camera{};
    camera.viewport_width = 1280;
    camera.viewport_height = 720;
    camera.zoom = 2.0f;
    camera.dpi_scale = 1.0f;
    if (plan_camera(camera, pipeline.camera, pipeline.diagnostic)
        != CanvasError::None) {
        return false;
    }
    CanvasSnapDesc snap{};
    snap.mode = SnapMode::Integer;
    snap.filter = FilterMode::Nearest;
    snap.scale_x = 2.0f;
    snap.scale_y = 2.0f;
    snap.offset_x = 0.4f;
    snap.offset_y = -1.6f;
    if (plan_snap(snap, pipeline.snap, pipeline.diagnostic)
        != CanvasError::None) {
        return false;
    }
    CanvasLightDesc light{};
    light.light_id = 9;
    light.revision = 1;
    light.intensity = 2.0f;
    light.radius = 3.0f;
    light.layer_id = 1;
    return plan_light(light, CanvasLightBudget{2, 4.0f}, pipeline.light,
                      pipeline.diagnostic) == CanvasError::None;
}

bool same_pipeline(const Pipeline& left, const Pipeline& right) {
    return left.sprite.sprite_id == right.sprite.sprite_id
        && left.sprite.visible == right.sprite.visible
        && left.atlas.region_count == right.atlas.region_count
        && left.layers.count == right.layers.count
        && left.layers.order[0] == right.layers.order[0]
        && left.layers.order[1] == right.layers.order[1]
        && left.layers.order[2] == right.layers.order[2]
        && left.camera.effective_zoom == right.camera.effective_zoom
        && left.snap.snapped_offset_x == right.snap.snapped_offset_x
        && left.snap.snapped_offset_y == right.snap.snapped_offset_y
        && left.light.intensity == right.light.intensity
        && left.light.clamped == right.light.clamped
        && left.diagnostic.code == right.diagnostic.code;
}

bool run_qlft101() {
    begin();
    Pipeline pipeline{};
    expect(run_pipeline(pipeline), "integrated pipeline");
    expect(pipeline.sprite.visible && pipeline.sprite.atlas_id == 4,
           "sprite plan");
    expect(pipeline.atlas.region_count == 1 && pipeline.atlas.mip_count == 3,
           "atlas plan");
    expect(pipeline.layers.count == 3 && pipeline.layers.order[0] == 6,
           "layer plan");
    expect(pipeline.camera.effective_zoom == 2.0f, "camera plan");
    expect(pipeline.snap.snapped_offset_x == 0.0f
               && pipeline.snap.snapped_offset_y == -2.0f,
           "snap plan");
    expect(pipeline.light.intensity == 2.0f && !pipeline.light.clamped,
           "light plan");
    return finish();
}

bool run_qlft102() {
    begin();
    Pipeline first{};
    Pipeline second{};
    expect(run_pipeline(first), "first run");
    expect(run_pipeline(second), "second run");
    expect(same_pipeline(first, second), "deterministic plans");
    for (u32 attempt = 0; attempt < 100; ++attempt) {
        Pipeline repeated{};
        expect(run_pipeline(repeated), "repeat succeeds");
        expect(same_pipeline(first, repeated), "repeat identical");
        if (failures != 0) {
            break;
        }
    }
    return finish();
}

bool run_qlft103() {
    begin();
    Pipeline pipeline{};
    expect(run_pipeline(pipeline), "baseline pipeline");
    CanvasDiagnostic diagnostic{};

    SpriteDrawDesc sprite = sprite_desc();
    sprite.asset_id = 0;
    expect(plan_sprite(sprite, pipeline.sprite, diagnostic)
               == CanvasError::InvalidArgument,
           "sprite failure");
    sprite = sprite_desc();
    expect(plan_sprite(sprite, pipeline.sprite, diagnostic) == CanvasError::None,
           "sprite recovery");

    AtlasDesc atlas = atlas_desc();
    atlas.region_count = 2;
    atlas.regions[1] = atlas.regions[0];
    expect(plan_atlas(atlas, pipeline.atlas, diagnostic)
               == CanvasError::DuplicateId,
           "atlas failure");
    atlas = atlas_desc();
    expect(plan_atlas(atlas, pipeline.atlas, diagnostic) == CanvasError::None,
           "atlas recovery");

    CanvasLayerSet layers = layer_set();
    layers.layers[1].order = 2;
    expect(plan_layers(layers, pipeline.layers, diagnostic)
               == CanvasError::LayerOrderInvalid,
           "layer failure");
    layers = layer_set();
    expect(plan_layers(layers, pipeline.layers, diagnostic) == CanvasError::None,
           "layer recovery");

    CanvasCameraDesc camera{};
    camera.viewport_width = 1280;
    camera.viewport_height = 720;
    camera.zoom = 0.0f;
    expect(plan_camera(camera, pipeline.camera, diagnostic)
               == CanvasError::CameraInvalid,
           "camera failure");
    camera.zoom = 1.0f;
    expect(plan_camera(camera, pipeline.camera, diagnostic) == CanvasError::None,
           "camera recovery");

    CanvasSnapDesc snap{};
    snap.scale_x = 0.0f;
    expect(plan_snap(snap, pipeline.snap, diagnostic)
               == CanvasError::SnapInvalid,
           "snap failure");
    snap.scale_x = 1.0f;
    expect(plan_snap(snap, pipeline.snap, diagnostic) == CanvasError::None,
           "snap recovery");

    CanvasLightDesc light{};
    light.light_id = 9;
    light.revision = 1;
    light.layer_id = 1;
    expect(plan_light(light, CanvasLightBudget{0, 4.0f}, pipeline.light,
                      diagnostic) == CanvasError::LightBudgetExceeded,
           "light failure");
    expect(plan_light(light, CanvasLightBudget{2, 4.0f}, pipeline.light,
                      diagnostic) == CanvasError::None,
           "light recovery");
    return finish();
}

bool run_qlft104() {
    begin();
    CanvasDiagnostic diagnostic{};
    CanvasLayerSet too_large{};
    too_large.count = kMaxLayers + 1;
    LayerPlan layers{};
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        expect(plan_layers(too_large, layers, diagnostic)
                   == CanvasError::CapacityFull,
               "layer cap bounded");
        if (failures != 0) {
            break;
        }
    }
    expect(layers.count == 0, "layer cap reset");
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        Pipeline pipeline{};
        expect(run_pipeline(pipeline), "bounded pipeline succeeds");
        if (failures != 0) {
            break;
        }
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two01_canvas_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlft101") { success = run_qlft101(); }
    else if (mode == "qlft102") { success = run_qlft102(); }
    else if (mode == "qlft103") { success = run_qlft103(); }
    else if (mode == "qlft104") { success = run_qlft104(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
