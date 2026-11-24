#ifndef STORMLINE_TERRAIN_TERRAIN_PATCH_PLAN_HPP
#define STORMLINE_TERRAIN_TERRAIN_PATCH_PLAN_HPP

#include <array>

#include "stormline/terrain/terrain_types.hpp"

namespace stormline::terrain {

struct TerrainPatchDesc {
    u64 patch_key{0};
    u32 revision{0};
    i64 tile_x{0};
    i64 tile_z{0};
    u32 lod{0};
    PatchTopology topology{PatchTopology::Heightfield};
    u32 neighbor_count{0};
    std::array<u64, kMaxPatchNeighbors> neighbors{};
};

struct TerrainPatchSetDesc {
    u32 asset_id{0};
    u32 revision{0};
    u32 patch_count{0};
    std::array<TerrainPatchDesc, kMaxTerrainPatches> patches{};
};

struct TerrainPatchPlan {
    u32 patch_count{0};
    u32 max_lod{0};
    u32 mesh_surface_count{0};
    i64 min_tile_x{0};
    i64 max_tile_x{0};
    i64 min_tile_z{0};
    i64 max_tile_z{0};
};

[[nodiscard]] inline TerrainError plan_terrain_patches(
    const TerrainPatchSetDesc& patches, TerrainPatchPlan& plan,
    TerrainDiagnostic& diagnostic) noexcept {
    plan = TerrainPatchPlan{};
    diagnostic = TerrainDiagnostic{};
    if (patches.asset_id == 0 || patches.revision == 0) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::InvalidArgument, patches.asset_id, 0);
    }
    if (patches.patch_count == 0) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::PatchInvalid, patches.asset_id, 0);
    }
    if (patches.patch_count > kMaxTerrainPatches) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::CapacityFull, patches.asset_id, 0);
    }
    for (u32 index = 0; index < patches.patch_count; ++index) {
        const TerrainPatchDesc& patch = patches.patches[index];
        if (patch.patch_key == 0 || patch.revision == 0
            || !detail::valid_patch_topology(patch.topology)) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::PatchInvalid, patches.asset_id,
                index);
        }
        if (patch.lod > kMaxTerrainLod) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::OutOfRange, patches.asset_id,
                index);
        }
        if (patch.neighbor_count > kMaxPatchNeighbors) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::CapacityFull, patches.asset_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (patches.patches[previous].patch_key == patch.patch_key) {
                return detail::set_terrain_error(
                    diagnostic, TerrainError::DuplicateId, patches.asset_id,
                    index);
            }
            if (patches.patches[previous].tile_x == patch.tile_x
                && patches.patches[previous].tile_z == patch.tile_z) {
                return detail::set_terrain_error(
                    diagnostic, TerrainError::DuplicateId, patches.asset_id,
                    index);
            }
        }
    }
    for (u32 index = 0; index < patches.patch_count; ++index) {
        const TerrainPatchDesc& patch = patches.patches[index];
        for (u32 neighbor = 0; neighbor < patch.neighbor_count; ++neighbor) {
            const u64 key = patch.neighbors[neighbor];
            if (key == 0 || key == patch.patch_key) {
                return detail::set_terrain_error(
                    diagnostic, TerrainError::PatchInvalid, patches.asset_id,
                    index);
            }
            for (u32 previous = 0; previous < neighbor; ++previous) {
                if (patch.neighbors[previous] == key) {
                    return detail::set_terrain_error(
                        diagnostic, TerrainError::DuplicateId,
                        patches.asset_id, index);
                }
            }
            bool found = false;
            for (u32 candidate = 0; candidate < patches.patch_count;
                 ++candidate) {
                if (patches.patches[candidate].patch_key == key) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return detail::set_terrain_error(
                    diagnostic, TerrainError::NotFound, patches.asset_id,
                    index);
            }
        }
    }
    plan.patch_count = patches.patch_count;
    plan.min_tile_x = patches.patches[0].tile_x;
    plan.max_tile_x = patches.patches[0].tile_x;
    plan.min_tile_z = patches.patches[0].tile_z;
    plan.max_tile_z = patches.patches[0].tile_z;
    for (u32 index = 0; index < patches.patch_count; ++index) {
        const TerrainPatchDesc& patch = patches.patches[index];
        if (patch.lod > plan.max_lod) {
            plan.max_lod = patch.lod;
        }
        if (patch.topology == PatchTopology::MeshSurface) {
            ++plan.mesh_surface_count;
        }
        if (patch.tile_x < plan.min_tile_x) {
            plan.min_tile_x = patch.tile_x;
        }
        if (patch.tile_x > plan.max_tile_x) {
            plan.max_tile_x = patch.tile_x;
        }
        if (patch.tile_z < plan.min_tile_z) {
            plan.min_tile_z = patch.tile_z;
        }
        if (patch.tile_z > plan.max_tile_z) {
            plan.max_tile_z = patch.tile_z;
        }
    }
    return TerrainError::None;
}

}  // namespace stormline::terrain

#endif  // STORMLINE_TERRAIN_TERRAIN_PATCH_PLAN_HPP
