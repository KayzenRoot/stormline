#ifndef STORMLINE_SCENE_INSTANCE_PLAN_HPP
#define STORMLINE_SCENE_INSTANCE_PLAN_HPP

#include <limits>
#include <array>

#include "stormline/scene/scene_types.hpp"

namespace stormline::scene {

struct PrefabInstanceDesc {
    u32 instance_id{0};
    u32 revision{0};
    u32 prefab_id{0};
    u32 prefab_revision{0};
    u32 expansion_count{0};
    u32 expansion_depth{0};
};

struct PrefabInstanceSetDesc {
    u32 scene_id{0};
    u32 revision{0};
    u32 instance_count{0};
    std::array<PrefabInstanceDesc, kMaxSceneInstances> instances{};
};

struct PrefabInstancePlan {
    u32 instance_count{0};
    u32 total_expansion{0};
    u32 max_depth{0};
};

[[nodiscard]] inline SceneError plan_prefab_instances(
    const PrefabInstanceSetDesc& instances, PrefabInstancePlan& plan,
    SceneDiagnostic& diagnostic) noexcept {
    plan = PrefabInstancePlan{};
    diagnostic = SceneDiagnostic{};
    if (instances.scene_id == 0 || instances.revision == 0) {
        return detail::set_scene_error(
            diagnostic, SceneError::InvalidArgument, instances.scene_id, 0);
    }
    if (instances.instance_count > kMaxSceneInstances) {
        return detail::set_scene_error(
            diagnostic, SceneError::InstanceInvalid, instances.scene_id, 0);
    }
    u32 total = 0;
    u32 max_depth = 0;
    for (u32 index = 0; index < instances.instance_count; ++index) {
        const PrefabInstanceDesc& instance = instances.instances[index];
        if (instance.instance_id == 0 || instance.revision == 0
            || instance.prefab_id == 0 || instance.prefab_revision == 0) {
            return detail::set_scene_error(
                diagnostic, SceneError::InstanceInvalid, instances.scene_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (instances.instances[previous].instance_id
                == instance.instance_id) {
                return detail::set_scene_error(
                    diagnostic, SceneError::DuplicateId, instances.scene_id,
                    index);
            }
        }
        if (instance.expansion_count == 0
            || instance.expansion_count > kMaxInstanceExpansion) {
            return detail::set_scene_error(
                diagnostic, SceneError::InstanceInvalid, instances.scene_id,
                index);
        }
        if (instance.expansion_depth > kMaxPrefabDepth) {
            return detail::set_scene_error(
                diagnostic, SceneError::DepthExceeded, instances.scene_id,
                index);
        }
        if (total > std::numeric_limits<u32>::max()
                - instance.expansion_count) {
            return detail::set_scene_error(
                diagnostic, SceneError::OutOfRange, instances.scene_id,
                index);
        }
        total += instance.expansion_count;
        if (instance.expansion_depth > max_depth) {
            max_depth = instance.expansion_depth;
        }
    }
    plan.instance_count = instances.instance_count;
    plan.total_expansion = total;
    plan.max_depth = max_depth;
    return SceneError::None;
}

}  // namespace stormline::scene

#endif  // STORMLINE_SCENE_INSTANCE_PLAN_HPP
