#ifndef STORMLINE_SCENE_HIERARCHY_PLAN_HPP
#define STORMLINE_SCENE_HIERARCHY_PLAN_HPP

#include <array>

#include "stormline/scene/scene_types.hpp"

namespace stormline::scene {

struct SceneNodeDesc {
    u32 node_id{0};
    u32 revision{0};
    u32 parent_id{0};
    u32 sibling_order{0};
};

struct SceneHierarchyDesc {
    u32 scene_id{0};
    u32 revision{0};
    u32 node_count{0};
    std::array<SceneNodeDesc, kMaxSceneNodes> nodes{};
};

struct SceneHierarchyPlan {
    u32 node_count{0};
    u32 root_count{0};
    u32 max_depth{0};
};

[[nodiscard]] inline SceneError plan_scene_hierarchy(
    const SceneHierarchyDesc& hierarchy, SceneHierarchyPlan& plan,
    SceneDiagnostic& diagnostic) noexcept {
    plan = SceneHierarchyPlan{};
    diagnostic = SceneDiagnostic{};
    if (hierarchy.scene_id == 0 || hierarchy.revision == 0) {
        return detail::set_scene_error(
            diagnostic, SceneError::InvalidArgument, hierarchy.scene_id, 0);
    }
    if (hierarchy.node_count == 0 || hierarchy.node_count > kMaxSceneNodes) {
        return detail::set_scene_error(
            diagnostic, SceneError::HierarchyInvalid, hierarchy.scene_id, 0);
    }
    for (u32 index = 0; index < hierarchy.node_count; ++index) {
        const SceneNodeDesc& node = hierarchy.nodes[index];
        if (node.node_id == 0 || node.revision == 0) {
            return detail::set_scene_error(
                diagnostic, SceneError::HierarchyInvalid, hierarchy.scene_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (hierarchy.nodes[previous].node_id == node.node_id) {
                return detail::set_scene_error(
                    diagnostic, SceneError::DuplicateId, hierarchy.scene_id,
                    index);
            }
            if (hierarchy.nodes[previous].parent_id == node.parent_id
                && hierarchy.nodes[previous].sibling_order
                    == node.sibling_order) {
                return detail::set_scene_error(
                    diagnostic, SceneError::DuplicateId, hierarchy.scene_id,
                    index);
            }
        }
        if (node.parent_id == node.node_id) {
            return detail::set_scene_error(
                diagnostic, SceneError::HierarchyInvalid, hierarchy.scene_id,
                index);
        }
    }
    SceneHierarchyPlan computed{};
    computed.node_count = hierarchy.node_count;
    for (u32 index = 0; index < hierarchy.node_count; ++index) {
        const SceneNodeDesc& node = hierarchy.nodes[index];
        u32 parent_index = kMaxSceneNodes;
        if (node.parent_id != 0) {
            for (u32 candidate = 0; candidate < hierarchy.node_count;
                 ++candidate) {
                if (hierarchy.nodes[candidate].node_id == node.parent_id) {
                    parent_index = candidate;
                    break;
                }
            }
            if (parent_index == kMaxSceneNodes) {
                return detail::set_scene_error(
                    diagnostic, SceneError::HierarchyInvalid,
                    hierarchy.scene_id, index);
            }
        } else {
            ++computed.root_count;
        }
        std::array<bool, kMaxSceneNodes> seen{};
        u32 depth = 1;
        u32 cursor = index;
        seen[cursor] = true;
        while (hierarchy.nodes[cursor].parent_id != 0) {
            if (depth >= kMaxSceneDepth) {
                return detail::set_scene_error(
                    diagnostic, SceneError::DepthExceeded, hierarchy.scene_id,
                    index);
            }
            cursor = parent_index;
            if (seen[cursor]) {
                return detail::set_scene_error(
                    diagnostic, SceneError::HierarchyInvalid,
                    hierarchy.scene_id, index);
            }
            seen[cursor] = true;
            ++depth;
            parent_index = kMaxSceneNodes;
            if (hierarchy.nodes[cursor].parent_id != 0) {
                for (u32 candidate = 0; candidate < hierarchy.node_count;
                     ++candidate) {
                    if (hierarchy.nodes[candidate].node_id
                        == hierarchy.nodes[cursor].parent_id) {
                        parent_index = candidate;
                        break;
                    }
                }
                if (parent_index == kMaxSceneNodes) {
                    return detail::set_scene_error(
                        diagnostic, SceneError::HierarchyInvalid,
                        hierarchy.scene_id, index);
                }
            }
        }
        if (depth > computed.max_depth) {
            computed.max_depth = depth;
        }
    }
    plan = computed;
    return SceneError::None;
}

}  // namespace stormline::scene

#endif  // STORMLINE_SCENE_HIERARCHY_PLAN_HPP
