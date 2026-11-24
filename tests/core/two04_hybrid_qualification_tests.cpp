#include "stormline/hybrid/camera_plan.hpp"
#include "stormline/hybrid/effect_plan.hpp"
#include "stormline/hybrid/layer_plan.hpp"
#include "stormline/hybrid/sort_plan.hpp"

#include <cstdio>
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

CameraDesc make_camera() {
    CameraDesc desc{};
    desc.camera_id = 71;
    desc.revision = 1;
    desc.projection = ProjectionKind::Orthographic;
    desc.near_plane = 0.1f;
    desc.far_plane = 500.0f;
    desc.ortho_half_height = 8.0f;
    desc.ortho_aspect = 1.5f;
    return desc;
}

HybridObjectRef make_object(u32 id, ObjectKind kind) {
    HybridObjectRef ref{};
    ref.object_id = id;
    ref.revision = 1;
    ref.kind = kind;
    ref.depth_key = static_cast<f32>(id);
    return ref;
}

HybridLayerSetDesc make_layers() {
    HybridLayerSetDesc desc{};
    desc.scene_id = 72;
    desc.revision = 1;
    desc.layer_count = 2;
    desc.layers[0].layer_id = 1;
    desc.layers[0].revision = 1;
    desc.layers[0].mode = CompositionMode::SharedDepthWorld;
    desc.layers[0].author_order = 0;
    desc.layers[0].depth_test = true;
    desc.layers[0].depth_write = true;
    desc.layers[0].alpha = AlphaPolicy::Opaque;
    desc.layers[0].object_count = 2;
    desc.layers[0].objects[0] = make_object(101, ObjectKind::Sprite);
    desc.layers[0].objects[1] = make_object(102, ObjectKind::Mesh);
    desc.layers[1].layer_id = 2;
    desc.layers[1].revision = 1;
    desc.layers[1].mode = CompositionMode::OrderedCanvasOverlay;
    desc.layers[1].author_order = 1;
    desc.layers[1].alpha = AlphaPolicy::Masked;
    desc.layers[1].object_count = 1;
    desc.layers[1].objects[0] = make_object(103, ObjectKind::Ui);
    return desc;
}

HybridSortDesc make_sort() {
    HybridSortDesc desc{};
    desc.scene_id = 72;
    desc.revision = 1;
    desc.object_count = 3;
    desc.objects[0].object_id = 103;
    desc.objects[0].revision = 1;
    desc.objects[0].layer_order = 1;
    desc.objects[0].depth_key = 3.0f;
    desc.objects[0].tie_breaker = 0;
    desc.objects[1].object_id = 102;
    desc.objects[1].revision = 1;
    desc.objects[1].layer_order = 0;
    desc.objects[1].depth_key = 2.0f;
    desc.objects[1].tie_breaker = 1;
    desc.objects[2].object_id = 101;
    desc.objects[2].revision = 1;
    desc.objects[2].layer_order = 0;
    desc.objects[2].depth_key = 2.0f;
    desc.objects[2].tie_breaker = 0;
    return desc;
}

HybridEffectSetDesc make_effects() {
    HybridEffectSetDesc desc{};
    desc.scene_id = 72;
    desc.revision = 1;
    desc.effect_count = 2;
    desc.effects[0].effect_id = 1;
    desc.effects[0].revision = 1;
    desc.effects[0].layer_id = 1;
    desc.effects[0].lit = true;
    desc.effects[1].effect_id = 2;
    desc.effects[1].revision = 1;
    desc.effects[1].layer_id = 2;
    desc.effects[1].shadow_proxy = true;
    desc.effects[1].subview_width = 256;
    desc.effects[1].subview_height = 128;
    desc.effects[1].subview_depth = 1;
    return desc;
}

struct IntegratedPlans {
    CameraPlan camera{};
    HybridLayerPlan layers{};
    HybridSortPlan sort{};
    HybridEffectPlan effects{};
    HybridDiagnostic diagnostic{};
};

bool plan_all(const CameraDesc& camera, const HybridLayerSetDesc& layers,
              const HybridSortDesc& sort, const HybridEffectSetDesc& effects,
              IntegratedPlans& plans) {
    return plan_camera(camera, plans.camera, plans.diagnostic)
               == HybridError::None
        && plan_layers(layers, plans.layers, plans.diagnostic)
               == HybridError::None
        && plan_sort(sort, plans.sort, plans.diagnostic)
               == HybridError::None
        && plan_effects(effects, plans.effects, plans.diagnostic)
               == HybridError::None;
}

bool run_qlft401() {
    begin();
    const CameraDesc camera = make_camera();
    const HybridLayerSetDesc layers = make_layers();
    const HybridSortDesc sort = make_sort();
    const HybridEffectSetDesc effects = make_effects();
    IntegratedPlans plans{};

    expect(plan_all(camera, layers, sort, effects, plans), "integrated plans");
    expect(plans.camera.projection == ProjectionKind::Orthographic
               && plans.camera.primary_extent == 8.0f,
           "integrated camera");
    expect(plans.layers.layer_count == 2 && plans.layers.object_count == 3
               && plans.layers.depth_write_count == 1
               && plans.layers.canvas_count == 1,
           "integrated layers");
    expect(plans.sort.object_count == 3 && plans.sort.order[0] == 101
               && plans.sort.order[1] == 102 && plans.sort.order[2] == 103,
           "integrated sort");
    expect(plans.effects.effect_count == 2 && plans.effects.lit_count == 1
               && plans.effects.shadow_count == 1
               && plans.effects.subview_count == 1,
           "integrated effects");
    expect(plans.diagnostic.code == HybridError::None,
           "integrated diagnostic");
    return finish();
}

bool run_qlft402() {
    begin();
    const CameraDesc camera = make_camera();
    const HybridLayerSetDesc layers = make_layers();
    const HybridSortDesc sort = make_sort();
    const HybridEffectSetDesc effects = make_effects();
    IntegratedPlans first{};
    IntegratedPlans second{};

    expect(plan_all(camera, layers, sort, effects, first), "first integrated");
    expect(plan_all(camera, layers, sort, effects, second), "second integrated");
    expect(first.camera.primary_extent == second.camera.primary_extent
               && first.camera.aspect == second.camera.aspect,
           "repeat camera");
    expect(first.layers.layer_count == second.layers.layer_count
               && first.layers.object_count == second.layers.object_count
               && first.layers.depth_write_count
                   == second.layers.depth_write_count,
           "repeat layers");
    expect(first.sort.order == second.sort.order, "repeat sort");
    expect(first.effects.effect_count == second.effects.effect_count
               && first.effects.lit_count == second.effects.lit_count
               && first.effects.max_subview_depth
                   == second.effects.max_subview_depth,
           "repeat effects");
    return finish();
}

bool run_qlft403() {
    begin();
    CameraDesc camera = make_camera();
    HybridLayerSetDesc layers = make_layers();
    HybridSortDesc sort = make_sort();
    HybridEffectSetDesc effects = make_effects();
    IntegratedPlans plans{};

    camera.perspective_fov_degrees = 0.0f;
    camera.projection = ProjectionKind::Perspective;
    expect(plan_camera(camera, plans.camera, plans.diagnostic)
               == HybridError::CameraInvalid,
           "camera failure");
    camera = make_camera();
    expect(plan_camera(camera, plans.camera, plans.diagnostic)
               == HybridError::None,
           "camera recovery");

    layers.layers[1].depth_test = true;
    expect(plan_layers(layers, plans.layers, plans.diagnostic)
               == HybridError::LayerInvalid,
           "layer failure");
    layers = make_layers();
    expect(plan_layers(layers, plans.layers, plans.diagnostic)
               == HybridError::None,
           "layer recovery");

    sort.objects[1].object_id = 101;
    expect(plan_sort(sort, plans.sort, plans.diagnostic)
               == HybridError::DuplicateId,
           "sort failure");
    sort = make_sort();
    expect(plan_sort(sort, plans.sort, plans.diagnostic) == HybridError::None,
           "sort recovery");

    effects.effects[1].subview_height = 0;
    expect(plan_effects(effects, plans.effects, plans.diagnostic)
               == HybridError::EffectInvalid,
           "effect failure");
    effects = make_effects();
    expect(plan_effects(effects, plans.effects, plans.diagnostic)
               == HybridError::None,
           "effect recovery");
    return finish();
}

bool run_qlft404() {
    begin();
    constexpr u32 kAttempts = 10000;
    for (u32 attempt = 0; attempt < kAttempts; ++attempt) {
        CameraDesc camera = make_camera();
        HybridLayerSetDesc layers = make_layers();
        HybridSortDesc sort = make_sort();
        HybridEffectSetDesc effects = make_effects();
        IntegratedPlans plans{};
        if (attempt % 97 == 0) {
            camera.near_plane = 0.0f;
            expect(plan_camera(camera, plans.camera, plans.diagnostic)
                       == HybridError::CameraInvalid,
                   "overload camera failure");
            camera = make_camera();
        }
        if (attempt % 89 == 0) {
            layers.layers[0].depth_write = false;
            layers.layers[0].depth_test = false;
            expect(plan_layers(layers, plans.layers, plans.diagnostic)
                       == HybridError::None,
                   "overload layer valid");
            layers = make_layers();
        }
        if (attempt % 83 == 0) {
            sort.object_count = 0;
            expect(plan_sort(sort, plans.sort, plans.diagnostic)
                       == HybridError::SortInvalid,
                   "overload sort failure");
            sort = make_sort();
        }
        if (attempt % 79 == 0) {
            effects.effect_count = kMaxHybridEffects + 1;
            expect(plan_effects(effects, plans.effects, plans.diagnostic)
                       == HybridError::EffectInvalid,
                   "overload effect failure");
            effects = make_effects();
        }
        expect(plan_all(camera, layers, sort, effects, plans),
               "overload plans");
        expect(plans.layers.layer_count <= kMaxHybridLayers,
               "layer cap");
        expect(plans.sort.object_count <= kMaxHybridObjects, "sort cap");
        expect(plans.effects.effect_count <= kMaxHybridEffects,
               "effect cap");
        expect(plans.effects.max_subview_depth <= kMaxSubviewDepth,
               "subview cap");
        expect(plans.sort.order[0] == 101 && plans.sort.order[2] == 103,
               "stable overload order");
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_two04_hybrid_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlft401") { success = run_qlft401(); }
    else if (mode == "qlft402") { success = run_qlft402(); }
    else if (mode == "qlft403") { success = run_qlft403(); }
    else if (mode == "qlft404") { success = run_qlft404(); }
    else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
