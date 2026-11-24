#include "stormline/scene/instance_plan.hpp"

#include <cstdio>
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

PrefabInstanceDesc instance(
    u32 id, u32 prefab, u32 expansion, u32 depth) {
    PrefabInstanceDesc desc{};
    desc.instance_id = id;
    desc.revision = 1;
    desc.prefab_id = prefab;
    desc.prefab_revision = 1;
    desc.expansion_count = expansion;
    desc.expansion_depth = depth;
    return desc;
}

PrefabInstanceSetDesc scene() {
    PrefabInstanceSetDesc desc{};
    desc.scene_id = 50;
    desc.revision = 1;
    desc.instance_count = 2;
    desc.instances[0] = instance(1, 30, 10, 1);
    desc.instances[1] = instance(2, 31, 20, 2);
    return desc;
}

bool run_ins01() {
    begin();
    PrefabInstanceSetDesc value = scene();
    PrefabInstancePlan plan{};
    SceneDiagnostic diagnostic{};

    expect(plan_prefab_instances(value, plan, diagnostic) == SceneError::None,
           "valid instances");
    expect(plan.instance_count == 2 && plan.total_expansion == 30
               && plan.max_depth == 2,
           "valid plan");
    PrefabInstancePlan repeat{};
    expect(plan_prefab_instances(value, repeat, diagnostic) == SceneError::None,
           "repeat instances");
    expect(plan.total_expansion == repeat.total_expansion
               && plan.max_depth == repeat.max_depth,
           "deterministic plan");

    value.scene_id = 0;
    expect(plan_prefab_instances(value, plan, diagnostic)
               == SceneError::InvalidArgument,
           "zero scene");
    expect(plan.instance_count == 0 && plan.total_expansion == 0,
           "reset on zero scene");
    value = scene();
    value.revision = 0;
    expect(plan_prefab_instances(value, plan, diagnostic)
               == SceneError::InvalidArgument,
           "zero revision");
    value = scene();
    value.instance_count = kMaxSceneInstances + 1;
    expect(plan_prefab_instances(value, plan, diagnostic)
               == SceneError::InstanceInvalid,
           "instance overflow");

    value = scene();
    value.instances[0].instance_id = 0;
    expect(plan_prefab_instances(value, plan, diagnostic)
               == SceneError::InstanceInvalid,
           "zero instance");
    value = scene();
    value.instances[0].revision = 0;
    expect(plan_prefab_instances(value, plan, diagnostic)
               == SceneError::InstanceInvalid,
           "zero instance revision");
    value = scene();
    value.instances[0].prefab_id = 0;
    expect(plan_prefab_instances(value, plan, diagnostic)
               == SceneError::InstanceInvalid,
           "zero prefab");
    value = scene();
    value.instances[0].prefab_revision = 0;
    expect(plan_prefab_instances(value, plan, diagnostic)
               == SceneError::InstanceInvalid,
           "zero prefab revision");
    value = scene();
    value.instances[1].instance_id = 1;
    expect(plan_prefab_instances(value, plan, diagnostic)
               == SceneError::DuplicateId,
           "duplicate instance");
    value = scene();
    value.instances[0].expansion_count = 0;
    expect(plan_prefab_instances(value, plan, diagnostic)
               == SceneError::InstanceInvalid,
           "zero expansion");
    value = scene();
    value.instances[0].expansion_count = kMaxInstanceExpansion + 1;
    expect(plan_prefab_instances(value, plan, diagnostic)
               == SceneError::InstanceInvalid,
           "expansion overflow");
    value = scene();
    value.instances[0].expansion_depth = kMaxPrefabDepth + 1;
    expect(plan_prefab_instances(value, plan, diagnostic)
               == SceneError::DepthExceeded,
           "depth overflow");

    value = scene();
    value.instance_count = 0;
    expect(plan_prefab_instances(value, plan, diagnostic) == SceneError::None,
           "empty instances");
    expect(plan.instance_count == 0 && plan.total_expansion == 0,
           "empty plan");

    value = scene();
    value.instance_count = kMaxSceneInstances;
    for (u32 index = 0; index < kMaxSceneInstances; ++index) {
        value.instances[index]
            = instance(index + 1, 30 + index, kMaxInstanceExpansion, 4);
    }
    expect(plan_prefab_instances(value, plan, diagnostic) == SceneError::None,
           "capacity instances");
    expect(plan.instance_count == kMaxSceneInstances
               && plan.total_expansion
                   == kMaxSceneInstances * kMaxInstanceExpansion
               && plan.max_depth == 4,
           "capacity counts");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world02_instance_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "ins01") { success = run_ins01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
