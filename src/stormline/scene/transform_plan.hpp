#ifndef STORMLINE_SCENE_TRANSFORM_PLAN_HPP
#define STORMLINE_SCENE_TRANSFORM_PLAN_HPP

#include <array>

#include "stormline/scene/scene_types.hpp"

namespace stormline::scene {

struct SceneTransformDesc {
    u32 node_id{0};
    u32 revision{0};
    f32 x{0.0f};
    f32 y{0.0f};
    f32 z{0.0f};
    f32 rotation_x{0.0f};
    f32 rotation_y{0.0f};
    f32 rotation_z{0.0f};
    f32 scale_x{1.0f};
    f32 scale_y{1.0f};
    f32 scale_z{1.0f};
    ReparentMode mode{ReparentMode::KeepLocal};
};

struct SceneTransformSetDesc {
    u32 scene_id{0};
    u32 revision{0};
    u32 node_count{0};
    std::array<SceneTransformDesc, kMaxSceneNodes> nodes{};
};

struct SceneTransformPlan {
    u32 node_count{0};
    u32 keep_local_count{0};
    u32 keep_world_count{0};
};

[[nodiscard]] inline SceneError plan_scene_transforms(
    const SceneTransformSetDesc& transforms, SceneTransformPlan& plan,
    SceneDiagnostic& diagnostic) noexcept {
    plan = SceneTransformPlan{};
    diagnostic = SceneDiagnostic{};
    if (transforms.scene_id == 0 || transforms.revision == 0) {
        return detail::set_scene_error(
            diagnostic, SceneError::InvalidArgument, transforms.scene_id, 0);
    }
    if (transforms.node_count == 0
        || transforms.node_count > kMaxSceneNodes) {
        return detail::set_scene_error(
            diagnostic, SceneError::TransformInvalid, transforms.scene_id, 0);
    }
    SceneTransformPlan computed{};
    computed.node_count = transforms.node_count;
    for (u32 index = 0; index < transforms.node_count; ++index) {
        const SceneTransformDesc& transform = transforms.nodes[index];
        if (transform.node_id == 0 || transform.revision == 0
            || !detail::valid_reparent_mode(transform.mode)) {
            return detail::set_scene_error(
                diagnostic, SceneError::TransformInvalid, transforms.scene_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (transforms.nodes[previous].node_id == transform.node_id) {
                return detail::set_scene_error(
                    diagnostic, SceneError::DuplicateId, transforms.scene_id,
                    index);
            }
        }
        if (!detail::finite(transform.x) || !detail::finite(transform.y)
            || !detail::finite(transform.z)
            || !detail::finite(transform.rotation_x)
            || !detail::finite(transform.rotation_y)
            || !detail::finite(transform.rotation_z)
            || !detail::finite(transform.scale_x)
            || !detail::finite(transform.scale_y)
            || !detail::finite(transform.scale_z)) {
            return detail::set_scene_error(
                diagnostic, SceneError::NonFiniteValue, transforms.scene_id,
                index);
        }
        if (transform.scale_x == 0.0f || transform.scale_y == 0.0f
            || transform.scale_z == 0.0f) {
            return detail::set_scene_error(
                diagnostic, SceneError::TransformInvalid, transforms.scene_id,
                index);
        }
        if (transform.mode == ReparentMode::KeepLocal) {
            ++computed.keep_local_count;
        } else {
            ++computed.keep_world_count;
        }
    }
    plan = computed;
    return SceneError::None;
}

}  // namespace stormline::scene

#endif  // STORMLINE_SCENE_TRANSFORM_PLAN_HPP
