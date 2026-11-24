#include "stormline/scene/hierarchy_plan.hpp"

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

SceneHierarchyDesc scene() {
    SceneHierarchyDesc desc{};
    desc.scene_id = 20;
    desc.revision = 1;
    desc.node_count = 4;
    desc.nodes[0] = node(1, 0, 0);
    desc.nodes[1] = node(2, 1, 0);
    desc.nodes[2] = node(3, 1, 1);
    desc.nodes[3] = node(4, 0, 1);
    return desc;
}

bool run_hir01() {
    begin();
    SceneHierarchyDesc hierarchy = scene();
    SceneHierarchyPlan plan{};
    SceneDiagnostic diagnostic{};

    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic) == SceneError::None,
           "valid hierarchy");
    expect(plan.node_count == 4 && plan.root_count == 2
               && plan.max_depth == 2,
           "valid plan");
    SceneHierarchyPlan repeat{};
    expect(plan_scene_hierarchy(hierarchy, repeat, diagnostic)
               == SceneError::None,
           "repeat hierarchy");
    expect(plan.root_count == repeat.root_count
               && plan.max_depth == repeat.max_depth,
           "deterministic plan");

    hierarchy.scene_id = 0;
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic)
               == SceneError::InvalidArgument,
           "zero scene");
    expect(plan.node_count == 0 && plan.root_count == 0,
           "reset on zero scene");
    hierarchy = scene();
    hierarchy.revision = 0;
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic)
               == SceneError::InvalidArgument,
           "zero revision");
    hierarchy = scene();
    hierarchy.node_count = 0;
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic)
               == SceneError::HierarchyInvalid,
           "zero nodes");
    hierarchy.node_count = kMaxSceneNodes + 1;
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic)
               == SceneError::HierarchyInvalid,
           "node overflow");

    hierarchy = scene();
    hierarchy.nodes[0].node_id = 0;
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic)
               == SceneError::HierarchyInvalid,
           "zero node id");
    hierarchy = scene();
    hierarchy.nodes[0].revision = 0;
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic)
               == SceneError::HierarchyInvalid,
           "zero revision");
    hierarchy = scene();
    hierarchy.nodes[1].node_id = 1;
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic)
               == SceneError::DuplicateId,
           "duplicate node");
    hierarchy = scene();
    hierarchy.nodes[1].parent_id = 99;
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic)
               == SceneError::HierarchyInvalid,
           "missing parent");
    hierarchy = scene();
    hierarchy.nodes[0].parent_id = 1;
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic)
               == SceneError::HierarchyInvalid,
           "self parent");
    hierarchy = scene();
    hierarchy.nodes[0].parent_id = 2;
    hierarchy.nodes[1].parent_id = 1;
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic)
               == SceneError::HierarchyInvalid,
           "two-node cycle");

    hierarchy = scene();
    hierarchy.nodes[2].sibling_order = 0;
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic)
               == SceneError::DuplicateId,
           "duplicate sibling order");
    hierarchy = scene();
    hierarchy.nodes[2].parent_id = 2;
    hierarchy.nodes[2].sibling_order = 0;
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic)
               == SceneError::None,
           "same order different parent");

    hierarchy = scene();
    hierarchy.node_count = kMaxSceneDepth;
    for (u32 index = 0; index < kMaxSceneDepth; ++index) {
        hierarchy.nodes[index] = node(index + 1, index, 0);
    }
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic) == SceneError::None,
           "depth sixteen");
    expect(plan.max_depth == kMaxSceneDepth && plan.root_count == 1,
           "depth sixteen plan");
    hierarchy.node_count = kMaxSceneDepth + 1;
    for (u32 index = 0; index < kMaxSceneDepth + 1; ++index) {
        hierarchy.nodes[index] = node(index + 1, index, 0);
    }
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic)
               == SceneError::DepthExceeded,
           "depth seventeen");

    hierarchy = scene();
    hierarchy.node_count = kMaxSceneNodes;
    for (u32 index = 0; index < kMaxSceneNodes; ++index) {
        hierarchy.nodes[index] = node(index + 1, 0, index);
    }
    expect(plan_scene_hierarchy(hierarchy, plan, diagnostic) == SceneError::None,
           "capacity hierarchy");
    expect(plan.root_count == kMaxSceneNodes && plan.max_depth == 1,
           "capacity counts");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world02_hierarchy_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "hir01") { success = run_hir01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
