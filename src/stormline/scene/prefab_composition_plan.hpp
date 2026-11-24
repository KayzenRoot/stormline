#ifndef STORMLINE_SCENE_PREFAB_COMPOSITION_PLAN_HPP
#define STORMLINE_SCENE_PREFAB_COMPOSITION_PLAN_HPP

#include <array>

#include "stormline/scene/scene_types.hpp"

namespace stormline::scene {

struct PrefabRefDesc {
    u32 prefab_id{0};
    u32 revision{0};
};

struct PrefabSourceDesc {
    u32 prefab_id{0};
    u32 revision{0};
    u32 depth{0};
    u32 nested_count{0};
    std::array<PrefabRefDesc, kMaxPrefabRefs> nested{};
};

struct PrefabCompositionPlan {
    u32 nested_count{0};
    u32 depth{0};
};

[[nodiscard]] inline SceneError plan_prefab_composition(
    const PrefabSourceDesc& prefab, PrefabCompositionPlan& plan,
    SceneDiagnostic& diagnostic) noexcept {
    plan = PrefabCompositionPlan{};
    diagnostic = SceneDiagnostic{};
    if (prefab.prefab_id == 0 || prefab.revision == 0) {
        return detail::set_scene_error(
            diagnostic, SceneError::InvalidArgument, prefab.prefab_id, 0);
    }
    if (prefab.depth > kMaxPrefabDepth) {
        return detail::set_scene_error(
            diagnostic, SceneError::DepthExceeded, prefab.prefab_id, 0);
    }
    if (prefab.nested_count > kMaxPrefabRefs) {
        return detail::set_scene_error(
            diagnostic, SceneError::PrefabInvalid, prefab.prefab_id, 0);
    }
    for (u32 index = 0; index < prefab.nested_count; ++index) {
        const PrefabRefDesc& ref = prefab.nested[index];
        if (ref.prefab_id == 0 || ref.revision == 0
            || ref.prefab_id == prefab.prefab_id) {
            return detail::set_scene_error(
                diagnostic, SceneError::PrefabInvalid, prefab.prefab_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (prefab.nested[previous].prefab_id == ref.prefab_id) {
                return detail::set_scene_error(
                    diagnostic, SceneError::DuplicateId, prefab.prefab_id,
                    index);
            }
        }
    }
    plan.nested_count = prefab.nested_count;
    plan.depth = prefab.depth;
    return SceneError::None;
}

}  // namespace stormline::scene

#endif  // STORMLINE_SCENE_PREFAB_COMPOSITION_PLAN_HPP
