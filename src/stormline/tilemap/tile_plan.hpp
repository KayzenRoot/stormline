#ifndef STORMLINE_TILEMAP_TILE_PLAN_HPP
#define STORMLINE_TILEMAP_TILE_PLAN_HPP

#include "stormline/tilemap/tilemap_types.hpp"

namespace stormline::tilemap {

struct TileCellDesc {
    u32 map_id{0};
    u32 layer_id{0};
    u32 revision{0};
    i64 cell_x{0};
    i64 cell_y{0};
    u32 tile_id{0};
    u32 tile_revision{0};
    bool empty{false};
    TileOrientation orientation{TileOrientation::Orthogonal};
    TileTransform transform{TileTransform::None};
};

struct TileCellPlan {
    u32 tile_id{0};
    bool empty{false};
    TileTransform transform{TileTransform::None};
};

[[nodiscard]] inline TilemapError plan_tile_cell(
    const TileCellDesc& cell, TileCellPlan& plan,
    TilemapDiagnostic& diagnostic) noexcept {
    plan = TileCellPlan{};
    diagnostic = TilemapDiagnostic{};
    if (cell.map_id == 0 || cell.layer_id == 0 || cell.revision == 0) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::InvalidArgument, cell.map_id, 0);
    }
    if (!detail::valid_orientation(cell.orientation)
        || !detail::valid_transform(cell.transform)) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::InvalidArgument, cell.map_id, 0);
    }
    if (cell.empty) {
        if (cell.tile_id != 0 || cell.tile_revision != 0
            || cell.transform != TileTransform::None) {
            return detail::set_tilemap_error(
                diagnostic, TilemapError::TileInvalid, cell.map_id, 0);
        }
        plan.empty = true;
        return TilemapError::None;
    }
    if (cell.tile_id == 0 || cell.tile_revision == 0) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::TileInvalid, cell.map_id, 0);
    }
    if (cell.orientation != TileOrientation::Orthogonal
        && cell.transform != TileTransform::None) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::Unsupported, cell.map_id, 0);
    }
    plan.tile_id = cell.tile_id;
    plan.empty = false;
    plan.transform = cell.transform;
    return TilemapError::None;
}

}  // namespace stormline::tilemap

#endif  // STORMLINE_TILEMAP_TILE_PLAN_HPP
