#include "stormline/scene/transform_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::scene;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

SceneTransformDesc transform(u32 id, ReparentMode mode) {
    SceneTransformDesc desc{};
    desc.node_id = id;
    desc.revision = 1;
    desc.x = 1.0f;
    desc.y = 2.0f;
    desc.z = 3.0f;
    desc.rotation_x = 0.1f;
    desc.rotation_y = 0.2f;
    desc.rotation_z = 0.3f;
    desc.scale_x = 1.0f;
    desc.scale_y = 1.0f;
    desc.scale_z = 1.0f;
    desc.mode = mode;
    return desc;
}

SceneTransformSetDesc scene() {
    SceneTransformSetDesc desc{};
    desc.scene_id = 60;
    desc.revision = 1;
    desc.node_count = 2;
    desc.nodes[0] = transform(1, ReparentMode::KeepLocal);
    desc.nodes[1] = transform(2, ReparentMode::KeepWorld);
    return desc;
}

bool run_trs01() {
    begin();
    SceneTransformSetDesc value = scene();
    SceneTransformPlan plan{};
    SceneDiagnostic diagnostic{};

    expect(plan_scene_transforms(value, plan, diagnostic) == SceneError::None,
           "valid transforms");
    expect(plan.node_count == 2 && plan.keep_local_count == 1
               && plan.keep_world_count == 1,
           "valid plan");
    SceneTransformPlan repeat{};
    expect(plan_scene_transforms(value, repeat, diagnostic) == SceneError::None,
           "repeat transforms");
    expect(plan.keep_local_count == repeat.keep_local_count
               && plan.keep_world_count == repeat.keep_world_count,
           "deterministic plan");

    value.scene_id = 0;
    expect(plan_scene_transforms(value, plan, diagnostic)
               == SceneError::InvalidArgument,
           "zero scene");
    expect(plan.node_count == 0 && plan.keep_local_count == 0,
           "reset on zero scene");
    value = scene();
    value.revision = 0;
    expect(plan_scene_transforms(value, plan, diagnostic)
               == SceneError::InvalidArgument,
           "zero revision");
    value = scene();
    value.node_count = 0;
    expect(plan_scene_transforms(value, plan, diagnostic)
               == SceneError::TransformInvalid,
           "zero nodes");
    value.node_count = kMaxSceneNodes + 1;
    expect(plan_scene_transforms(value, plan, diagnostic)
               == SceneError::TransformInvalid,
           "node overflow");

    value = scene();
    value.nodes[0].node_id = 0;
    expect(plan_scene_transforms(value, plan, diagnostic)
               == SceneError::TransformInvalid,
           "zero node");
    value = scene();
    value.nodes[0].revision = 0;
    expect(plan_scene_transforms(value, plan, diagnostic)
               == SceneError::TransformInvalid,
           "zero revision");
    value = scene();
    value.nodes[1].node_id = 1;
    expect(plan_scene_transforms(value, plan, diagnostic)
               == SceneError::DuplicateId,
           "duplicate node");
    value = scene();
    value.nodes[0].mode = static_cast<ReparentMode>(200);
    expect(plan_scene_transforms(value, plan, diagnostic)
               == SceneError::TransformInvalid,
           "invalid mode");

    value = scene();
    value.nodes[0].x = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_scene_transforms(value, plan, diagnostic)
               == SceneError::NonFiniteValue,
           "nan translation");
    value = scene();
    value.nodes[0].rotation_y = std::numeric_limits<f32>::infinity();
    expect(plan_scene_transforms(value, plan, diagnostic)
               == SceneError::NonFiniteValue,
           "infinite rotation");
    value = scene();
    value.nodes[0].scale_z = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_scene_transforms(value, plan, diagnostic)
               == SceneError::NonFiniteValue,
           "nan scale");
    value = scene();
    value.nodes[0].scale_x = 0.0f;
    expect(plan_scene_transforms(value, plan, diagnostic)
               == SceneError::TransformInvalid,
           "zero scale x");
    value = scene();
    value.nodes[0].scale_y = 0.0f;
    expect(plan_scene_transforms(value, plan, diagnostic)
               == SceneError::TransformInvalid,
           "zero scale y");
    value = scene();
    value.nodes[0].scale_z = 0.0f;
    expect(plan_scene_transforms(value, plan, diagnostic)
               == SceneError::TransformInvalid,
           "zero scale z");

    value = scene();
    value.node_count = kMaxSceneNodes;
    for (u32 index = 0; index < kMaxSceneNodes; ++index) {
        value.nodes[index] = transform(
            index + 1, index % 2 == 0 ? ReparentMode::KeepLocal
                                     : ReparentMode::KeepWorld);
    }
    expect(plan_scene_transforms(value, plan, diagnostic) == SceneError::None,
           "capacity transforms");
    expect(plan.node_count == kMaxSceneNodes
               && plan.keep_local_count == kMaxSceneNodes / 2
               && plan.keep_world_count == kMaxSceneNodes / 2,
           "capacity counts");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world02_transform_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "trs01") { success = run_trs01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
