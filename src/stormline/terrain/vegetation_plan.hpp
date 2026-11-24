#ifndef STORMLINE_TERRAIN_VEGETATION_PLAN_HPP
#define STORMLINE_TERRAIN_VEGETATION_PLAN_HPP

#include <array>

#include "stormline/terrain/terrain_types.hpp"

namespace stormline::terrain {

struct VegetationGroupDesc {
    u64 group_key{0};
    u32 prototype_asset_id{0};
    u32 revision{0};
    u32 instance_count{0};
    u32 density_limit{0};
    bool collider_required{false};
    f32 min_x{0.0f};
    f32 min_z{0.0f};
    f32 max_x{0.0f};
    f32 max_z{0.0f};
};

struct VegetationSetDesc {
    u32 asset_id{0};
    u32 revision{0};
    u32 group_count{0};
    std::array<VegetationGroupDesc, kMaxVegetationGroups> groups{};
};

struct VegetationPlan {
    u32 group_count{0};
    u32 total_instances{0};
    u32 collider_group_count{0};
};

[[nodiscard]] inline TerrainError plan_vegetation(
    const VegetationSetDesc& vegetation, VegetationPlan& plan,
    TerrainDiagnostic& diagnostic) noexcept {
    plan = VegetationPlan{};
    diagnostic = TerrainDiagnostic{};
    if (vegetation.asset_id == 0 || vegetation.revision == 0) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::InvalidArgument, vegetation.asset_id,
            0);
    }
    if (vegetation.group_count > kMaxVegetationGroups) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::CapacityFull, vegetation.asset_id, 0);
    }
    for (u32 index = 0; index < vegetation.group_count; ++index) {
        const VegetationGroupDesc& group = vegetation.groups[index];
        if (group.group_key == 0 || group.prototype_asset_id == 0
            || group.revision == 0) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::VegetationInvalid,
                vegetation.asset_id, index);
        }
        if (group.instance_count == 0 || group.density_limit == 0
            || group.instance_count > group.density_limit
            || group.density_limit > kMaxVegetationInstances) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::VegetationInvalid,
                vegetation.asset_id, index);
        }
        if (!detail::finite(group.min_x) || !detail::finite(group.min_z)
            || !detail::finite(group.max_x)
            || !detail::finite(group.max_z)) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::NonFiniteValue, vegetation.asset_id,
                index);
        }
        if (!(group.min_x < group.max_x) || !(group.min_z < group.max_z)) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::OutOfRange, vegetation.asset_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (vegetation.groups[previous].group_key == group.group_key) {
                return detail::set_terrain_error(
                    diagnostic, TerrainError::DuplicateId, vegetation.asset_id,
                    index);
            }
        }
    }
    plan.group_count = vegetation.group_count;
    for (u32 index = 0; index < vegetation.group_count; ++index) {
        const VegetationGroupDesc& group = vegetation.groups[index];
        if (!detail::checked_add_u32(plan.total_instances,
                                     group.instance_count)
            || plan.total_instances > kMaxVegetationInstances) {
            plan = VegetationPlan{};
            return detail::set_terrain_error(
                diagnostic, TerrainError::OutOfRange, vegetation.asset_id,
                index);
        }
        if (group.collider_required) {
            ++plan.collider_group_count;
        }
    }
    return TerrainError::None;
}

}  // namespace stormline::terrain

#endif  // STORMLINE_TERRAIN_VEGETATION_PLAN_HPP
