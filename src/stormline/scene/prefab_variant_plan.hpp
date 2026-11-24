#ifndef STORMLINE_SCENE_PREFAB_VARIANT_PLAN_HPP
#define STORMLINE_SCENE_PREFAB_VARIANT_PLAN_HPP

#include <array>

#include "stormline/scene/scene_types.hpp"

namespace stormline::scene {

struct VariantOverrideDesc {
    u32 node_id{0};
    u32 component_type_id{0};
    u32 field_id{0};
    bool base_changed{false};
    bool variant_changed{false};
};

struct PrefabVariantDesc {
    u32 variant_id{0};
    u32 revision{0};
    u32 base_prefab_id{0};
    u32 base_revision{0};
    u32 override_count{0};
    std::array<VariantOverrideDesc, kMaxVariantOverrides> overrides{};
};

struct PrefabVariantPlan {
    u32 override_count{0};
};

[[nodiscard]] inline SceneError plan_prefab_variant(
    const PrefabVariantDesc& variant, PrefabVariantPlan& plan,
    SceneDiagnostic& diagnostic) noexcept {
    plan = PrefabVariantPlan{};
    diagnostic = SceneDiagnostic{};
    if (variant.variant_id == 0 || variant.revision == 0
        || variant.base_prefab_id == 0 || variant.base_revision == 0) {
        return detail::set_scene_error(
            diagnostic, SceneError::InvalidArgument, variant.variant_id, 0);
    }
    if (variant.override_count == 0
        || variant.override_count > kMaxVariantOverrides) {
        return detail::set_scene_error(
            diagnostic, SceneError::VariantInvalid, variant.variant_id, 0);
    }
    for (u32 index = 0; index < variant.override_count; ++index) {
        const VariantOverrideDesc& override_desc = variant.overrides[index];
        if (override_desc.node_id == 0 || override_desc.component_type_id == 0
            || override_desc.field_id == 0
            || (override_desc.base_changed && override_desc.variant_changed)) {
            return detail::set_scene_error(
                diagnostic, SceneError::VariantInvalid, variant.variant_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            const VariantOverrideDesc& prior = variant.overrides[previous];
            if (prior.node_id == override_desc.node_id
                && prior.component_type_id == override_desc.component_type_id
                && prior.field_id == override_desc.field_id) {
                return detail::set_scene_error(
                    diagnostic, SceneError::DuplicateId, variant.variant_id,
                    index);
            }
        }
    }
    plan.override_count = variant.override_count;
    return SceneError::None;
}

}  // namespace stormline::scene

#endif  // STORMLINE_SCENE_PREFAB_VARIANT_PLAN_HPP
