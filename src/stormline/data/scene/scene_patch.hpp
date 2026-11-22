#ifndef STORMLINE_DATA_SCENE_SCENE_PATCH_HPP
#define STORMLINE_DATA_SCENE_SCENE_PATCH_HPP

#include "stormline/data/scene/scene_document.hpp"

#include <span>

namespace stormline::data::scene {

enum class PatchOp : std::uint8_t {
    AddEntity,
    RemoveEntity,
    SetEnabled
};

struct PatchOperation {
    PatchOp kind{PatchOp::AddEntity};
    EntityRecord entity{};
    EntityId target{};
    bool enabled{true};
};

struct ScenePatch {
    u64 operation_id{0};
    u64 base_revision{0};
    SceneId scene{};
};

[[nodiscard]] inline SceneError apply_patch(
    SceneDocument& document, const ScenePatch& patch,
    std::span<const PatchOperation> operations) noexcept {
    if (patch.operation_id == 0) {
        return SceneError::InvalidArgument;
    }
    if (patch.scene.value != document.scene().value) {
        return SceneError::InvalidPatch;
    }
    if (patch.base_revision != document.revision()) {
        return SceneError::StaleRevision;
    }
    if (operations.size() > kMaxPatchOps) {
        return SceneError::InvalidPatch;
    }
    SceneDocument candidate = document;
    for (const PatchOperation& operation : operations) {
        SceneError status = SceneError::None;
        switch (operation.kind) {
            case PatchOp::AddEntity:
                status = candidate.add_entity(operation.entity);
                break;
            case PatchOp::RemoveEntity:
                status = candidate.remove_entity(operation.target);
                break;
            case PatchOp::SetEnabled:
                status = candidate.set_enabled(operation.target, operation.enabled);
                break;
            default:
                return SceneError::InvalidPatch;
        }
        if (status != SceneError::None) {
            return status;
        }
    }
    candidate.advance_revision();
    document = candidate;
    return SceneError::None;
}

}  // namespace stormline::data::scene

#endif  // STORMLINE_DATA_SCENE_SCENE_PATCH_HPP
