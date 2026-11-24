#ifndef STORMLINE_TERRAIN_SPLAT_PLAN_HPP
#define STORMLINE_TERRAIN_SPLAT_PLAN_HPP

#include <array>

#include "stormline/terrain/terrain_types.hpp"

namespace stormline::terrain {

struct SplatLayerDesc {
    u32 layer_id{0};
    u32 material_asset_id{0};
    u32 revision{0};
    f32 weight{0.0f};
    u8 channel{0};
    u32 precedence{0};
};

struct SplatSetDesc {
    u32 asset_id{0};
    u32 revision{0};
    u32 layer_count{0};
    std::array<SplatLayerDesc, kMaxSplatLayers> layers{};
};

struct SplatPlan {
    u32 layer_count{0};
    u32 material_count{0};
    f32 total_weight{0.0f};
};

[[nodiscard]] inline TerrainError plan_splat_layers(
    const SplatSetDesc& splat, SplatPlan& plan,
    TerrainDiagnostic& diagnostic) noexcept {
    plan = SplatPlan{};
    diagnostic = TerrainDiagnostic{};
    if (splat.asset_id == 0 || splat.revision == 0) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::InvalidArgument, splat.asset_id, 0);
    }
    if (splat.layer_count == 0) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::SplatInvalid, splat.asset_id, 0);
    }
    if (splat.layer_count > kMaxSplatLayers) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::CapacityFull, splat.asset_id, 0);
    }
    f32 total = 0.0f;
    for (u32 index = 0; index < splat.layer_count; ++index) {
        const SplatLayerDesc& layer = splat.layers[index];
        if (layer.layer_id == 0 || layer.material_asset_id == 0
            || layer.revision == 0 || layer.channel > 3) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::SplatInvalid, splat.asset_id,
                index);
        }
        if (!detail::finite(layer.weight) || !(layer.weight >= 0.0f)
            || !(layer.weight <= 1.0f)) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::NonFiniteValue, splat.asset_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (splat.layers[previous].layer_id == layer.layer_id) {
                return detail::set_terrain_error(
                    diagnostic, TerrainError::DuplicateId, splat.asset_id,
                    index);
            }
        }
        total += layer.weight;
        if (!(total <= 1.0f + 1e-6f)) {
            return detail::set_terrain_error(
                diagnostic, TerrainError::OutOfRange, splat.asset_id, index);
        }
    }
    if (total > 1.0f + 1e-6f) {
        return detail::set_terrain_error(
            diagnostic, TerrainError::OutOfRange, splat.asset_id, 0);
    }
    plan.layer_count = splat.layer_count;
    plan.total_weight = total;
    for (u32 index = 0; index < splat.layer_count; ++index) {
        bool seen = false;
        for (u32 previous = 0; previous < index; ++previous) {
            if (splat.layers[previous].material_asset_id
                == splat.layers[index].material_asset_id) {
                seen = true;
                break;
            }
        }
        if (!seen) {
            ++plan.material_count;
        }
    }
    return TerrainError::None;
}

}  // namespace stormline::terrain

#endif  // STORMLINE_TERRAIN_SPLAT_PLAN_HPP
