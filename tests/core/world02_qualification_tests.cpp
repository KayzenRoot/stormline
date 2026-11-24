#include "stormline/scene/hierarchy_plan.hpp"
#include "stormline/scene/instance_plan.hpp"
#include "stormline/scene/prefab_composition_plan.hpp"
#include "stormline/scene/prefab_variant_plan.hpp"
#include "stormline/scene/transform_plan.hpp"

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

SceneNodeDesc node(u32 id, u32 parent, u32 order) {
    SceneNodeDesc desc{};
    desc.node_id = id;
    desc.revision = 1;
    desc.parent_id = parent;
    desc.sibling_order = order;
    return desc;
}

SceneHierarchyDesc make_hierarchy() {
    SceneHierarchyDesc desc{};
    desc.scene_id = 70;
    desc.revision = 1;
    desc.node_count = 3;
    desc.nodes[0] = node(1, 0, 0);
    desc.nodes[1] = node(2, 1, 0);
    desc.nodes[2] = node(3, 1, 1);
    return desc;
}

PrefabSourceDesc make_composition() {
    PrefabSourceDesc desc{};
    desc.prefab_id = 80;
    desc.revision = 1;
    desc.depth = 1;
    desc.nested_count = 2;
    desc.nested[0].prefab_id = 81;
    desc.nested[0].revision = 1;
    desc.nested[1].prefab_id = 82;
    desc.nested[1].revision = 1;
    return desc;
}

PrefabVariantDesc make_variant() {
    PrefabVariantDesc desc{};
    desc.variant_id = 90;
    desc.revision = 1;
    desc.base_prefab_id = 80;
    desc.base_revision = 1;
    desc.override_count = 2;
    desc.overrides[0] = VariantOverrideDesc{1, 10, 1, false, true};
    desc.overrides[1] = VariantOverrideDesc{2, 11, 1, true, false};
    return desc;
}

PrefabInstanceSetDesc make_instances() {
    PrefabInstanceSetDesc desc{};
    desc.scene_id = 70;
    desc.revision = 1;
    desc.instance_count = 2;
    desc.instances[0] = PrefabInstanceDesc{1, 1, 80, 1, 4, 1};
    desc.instances[1] = PrefabInstanceDesc{2, 1, 81, 1, 8, 2};
    return desc;
}

SceneTransformSetDesc make_transforms() {
    SceneTransformSetDesc desc{};
    desc.scene_id = 70;
    desc.revision = 1;
    desc.node_count = 3;
    desc.nodes[0] = SceneTransformDesc{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1,
                                       ReparentMode::KeepLocal};
    desc.nodes[1] = SceneTransformDesc{2, 1, 1, 2, 3, 0, 0, 0, 1, 1, 1,
                                       ReparentMode::KeepWorld};
    desc.nodes[2] = SceneTransformDesc{3, 1, -1, 0, 0, 0, 0, 0, 2, 2, 2,
                                       ReparentMode::KeepLocal};
    return desc;
}

struct IntegratedPlans {
    SceneHierarchyPlan hierarchy{};
    PrefabCompositionPlan composition{};
    PrefabVariantPlan variant{};
    PrefabInstancePlan instances{};
    SceneTransformPlan transforms{};
    SceneDiagnostic diagnostic{};
};

bool plan_all(const SceneHierarchyDesc& hierarchy,
              const PrefabSourceDesc& composition,
              const PrefabVariantDesc& variant,
              const PrefabInstanceSetDesc& instances,
              const SceneTransformSetDesc& transforms,
              IntegratedPlans& plans) {
    return plan_scene_hierarchy(hierarchy, plans.hierarchy, plans.diagnostic)
               == SceneError::None
        && plan_prefab_composition(composition, plans.composition,
                                   plans.diagnostic)
               == SceneError::None
        && plan_prefab_variant(variant, plans.variant, plans.diagnostic)
               == SceneError::None
        && plan_prefab_instances(instances, plans.instances, plans.diagnostic)
               == SceneError::None
        && plan_scene_transforms(transforms, plans.transforms,
                                 plans.diagnostic)
               == SceneError::None;
}

bool run_qlfs201() {
    begin();
    const SceneHierarchyDesc hierarchy = make_hierarchy();
    const PrefabSourceDesc composition = make_composition();
    const PrefabVariantDesc variant = make_variant();
    const PrefabInstanceSetDesc instances = make_instances();
    const SceneTransformSetDesc transforms = make_transforms();
    IntegratedPlans plans{};

    expect(plan_all(hierarchy, composition, variant, instances, transforms,
                    plans),
           "integrated plans");
    expect(plans.hierarchy.node_count == 3 && plans.hierarchy.root_count == 1
               && plans.hierarchy.max_depth == 2,
           "integrated hierarchy");
    expect(plans.composition.nested_count == 2 && plans.composition.depth == 1,
           "integrated composition");
    expect(plans.variant.override_count == 2, "integrated variant");
    expect(plans.instances.instance_count == 2
               && plans.instances.total_expansion == 12
               && plans.instances.max_depth == 2,
           "integrated instances");
    expect(plans.transforms.node_count == 3
               && plans.transforms.keep_local_count == 2
               && plans.transforms.keep_world_count == 1,
           "integrated transforms");
    expect(plans.diagnostic.code == SceneError::None,
           "integrated diagnostic");
    return finish();
}

bool run_qlfs202() {
    begin();
    const SceneHierarchyDesc hierarchy = make_hierarchy();
    const PrefabSourceDesc composition = make_composition();
    const PrefabVariantDesc variant = make_variant();
    const PrefabInstanceSetDesc instances = make_instances();
    const SceneTransformSetDesc transforms = make_transforms();
    IntegratedPlans first{};
    IntegratedPlans second{};

    expect(plan_all(hierarchy, composition, variant, instances, transforms,
                    first),
           "first integrated");
    expect(plan_all(hierarchy, composition, variant, instances, transforms,
                    second),
           "second integrated");
    expect(first.hierarchy.root_count == second.hierarchy.root_count
               && first.hierarchy.max_depth == second.hierarchy.max_depth,
           "repeat hierarchy");
    expect(first.composition.nested_count == second.composition.nested_count
               && first.composition.depth == second.composition.depth,
           "repeat composition");
    expect(first.variant.override_count == second.variant.override_count,
           "repeat variant");
    expect(first.instances.total_expansion
               == second.instances.total_expansion
               && first.instances.max_depth == second.instances.max_depth,
           "repeat instances");
    expect(first.transforms.keep_local_count
               == second.transforms.keep_local_count
               && first.transforms.keep_world_count
                   == second.transforms.keep_world_count,
           "repeat transforms");
    return finish();
}

bool run_qlfs203() {
    begin();
    SceneHierarchyDesc hierarchy = make_hierarchy();
    PrefabSourceDesc composition = make_composition();
    PrefabVariantDesc variant = make_variant();
    PrefabInstanceSetDesc instances = make_instances();
    SceneTransformSetDesc transforms = make_transforms();
    IntegratedPlans plans{};

    hierarchy.scene_id = 0;
    expect(plan_scene_hierarchy(hierarchy, plans.hierarchy, plans.diagnostic)
               == SceneError::InvalidArgument,
           "hierarchy failure");
    hierarchy = make_hierarchy();
    expect(plan_scene_hierarchy(hierarchy, plans.hierarchy, plans.diagnostic)
               == SceneError::None,
           "hierarchy recovery");

    composition.nested[0].prefab_id = 80;
    expect(plan_prefab_composition(composition, plans.composition,
                                   plans.diagnostic)
               == SceneError::PrefabInvalid,
           "composition failure");
    composition = make_composition();
    expect(plan_prefab_composition(composition, plans.composition,
                                   plans.diagnostic)
               == SceneError::None,
           "composition recovery");

    variant.overrides[0].base_changed = true;
    expect(plan_prefab_variant(variant, plans.variant, plans.diagnostic)
               == SceneError::VariantInvalid,
           "variant failure");
    variant = make_variant();
    expect(plan_prefab_variant(variant, plans.variant, plans.diagnostic)
               == SceneError::None,
           "variant recovery");

    instances.instances[0].expansion_count = 0;
    expect(plan_prefab_instances(instances, plans.instances, plans.diagnostic)
               == SceneError::InstanceInvalid,
           "instance failure");
    instances = make_instances();
    expect(plan_prefab_instances(instances, plans.instances, plans.diagnostic)
               == SceneError::None,
           "instance recovery");

    transforms.nodes[0].scale_x = 0.0f;
    expect(plan_scene_transforms(transforms, plans.transforms,
                                 plans.diagnostic)
               == SceneError::TransformInvalid,
           "transform failure");
    transforms = make_transforms();
    expect(plan_scene_transforms(transforms, plans.transforms,
                                 plans.diagnostic)
               == SceneError::None,
           "transform recovery");
    return finish();
}

bool run_qlfs204() {
    begin();
    constexpr u32 kAttempts = 10000;
    for (u32 attempt = 0; attempt < kAttempts; ++attempt) {
        SceneHierarchyDesc hierarchy = make_hierarchy();
        PrefabSourceDesc composition = make_composition();
        PrefabVariantDesc variant = make_variant();
        PrefabInstanceSetDesc instances = make_instances();
        SceneTransformSetDesc transforms = make_transforms();
        IntegratedPlans plans{};
        if (attempt % 97 == 0) {
            hierarchy.scene_id = 0;
            expect(plan_scene_hierarchy(hierarchy, plans.hierarchy,
                                        plans.diagnostic)
                       == SceneError::InvalidArgument,
                   "overload hierarchy failure");
            hierarchy = make_hierarchy();
        }
        if (attempt % 89 == 0) {
            composition.nested[1].prefab_id = 81;
            expect(plan_prefab_composition(composition, plans.composition,
                                           plans.diagnostic)
                       == SceneError::DuplicateId,
                   "overload composition failure");
            composition = make_composition();
        }
        if (attempt % 83 == 0) {
            variant.overrides[0].base_changed = true;
            variant.overrides[0].variant_changed = true;
            expect(plan_prefab_variant(variant, plans.variant, plans.diagnostic)
                       == SceneError::VariantInvalid,
                   "overload variant failure");
            variant = make_variant();
        }
        if (attempt % 79 == 0) {
            instances.instances[0].expansion_depth = kMaxPrefabDepth + 1;
            expect(plan_prefab_instances(instances, plans.instances,
                                         plans.diagnostic)
                       == SceneError::DepthExceeded,
                   "overload instance failure");
            instances = make_instances();
        }
        if (attempt % 73 == 0) {
            transforms.nodes[1].scale_y = 0.0f;
            expect(plan_scene_transforms(transforms, plans.transforms,
                                         plans.diagnostic)
                       == SceneError::TransformInvalid,
                   "overload transform failure");
            transforms = make_transforms();
        }
        expect(plan_all(hierarchy, composition, variant, instances, transforms,
                        plans),
               "overload plans");
        expect(plans.hierarchy.node_count <= kMaxSceneNodes, "hierarchy cap");
        expect(plans.hierarchy.max_depth <= kMaxSceneDepth, "depth cap");
        expect(plans.composition.nested_count <= kMaxPrefabRefs,
               "composition cap");
        expect(plans.variant.override_count <= kMaxVariantOverrides,
               "variant cap");
        expect(plans.instances.instance_count <= kMaxSceneInstances,
               "instance cap");
        expect(plans.instances.total_expansion
                   <= kMaxSceneInstances * kMaxInstanceExpansion,
               "expansion cap");
        expect(plans.transforms.node_count <= kMaxSceneNodes, "transform cap");
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world02_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlfs201") { success = run_qlfs201(); }
    else if (mode == "qlfs202") { success = run_qlfs202(); }
    else if (mode == "qlfs203") { success = run_qlfs203(); }
    else if (mode == "qlfs204") { success = run_qlfs204(); }
    else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
