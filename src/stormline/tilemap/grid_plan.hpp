#ifndef STORMLINE_TILEMAP_GRID_PLAN_HPP
#define STORMLINE_TILEMAP_GRID_PLAN_HPP

#include "stormline/tilemap/tilemap_types.hpp"

namespace stormline::tilemap {

struct GridDesc {
    u32 map_id{0};
    u32 revision{0};
    u32 tile_width{0};
    u32 tile_height{0};
    u32 chunk_width{0};
    u32 chunk_height{0};
    i64 min_cell_x{0};
    i64 min_cell_y{0};
    i64 max_cell_x{0};
    i64 max_cell_y{0};
};

struct GridCellPlan {
    i64 chunk_x{0};
    i64 chunk_y{0};
    u32 local_x{0};
    u32 local_y{0};
};

namespace detail {

inline i64 floor_div(i64 value, u32 divisor) noexcept {
    const i64 d = static_cast<i64>(divisor);
    i64 quotient = value / d;
    i64 remainder = value % d;
    if (remainder < 0) {
        --quotient;
        remainder += d;
    }
    return quotient;
}

inline u32 floor_local(i64 value, u32 divisor) noexcept {
    i64 remainder = value % static_cast<i64>(divisor);
    if (remainder < 0) {
        remainder += static_cast<i64>(divisor);
    }
    return static_cast<u32>(remainder);
}

}  // namespace detail

[[nodiscard]] inline TilemapError plan_grid_cell(
    const GridDesc& grid, i64 cell_x, i64 cell_y, GridCellPlan& plan,
    TilemapDiagnostic& diagnostic) noexcept {
    plan = GridCellPlan{};
    diagnostic = TilemapDiagnostic{};
    if (grid.map_id == 0 || grid.revision == 0) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::InvalidArgument, grid.map_id, 0);
    }
    if (grid.tile_width == 0 || grid.tile_height == 0
        || grid.chunk_width == 0 || grid.chunk_height == 0) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::GridInvalid, grid.map_id, 0);
    }
    if (grid.min_cell_x > grid.max_cell_x
        || grid.min_cell_y > grid.max_cell_y) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::GridInvalid, grid.map_id, 0);
    }
    if (cell_x < grid.min_cell_x || cell_x > grid.max_cell_x
        || cell_y < grid.min_cell_y || cell_y > grid.max_cell_y) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::CoordinateOutOfBounds, grid.map_id, 0);
    }
    plan.chunk_x = detail::floor_div(cell_x, grid.chunk_width);
    plan.chunk_y = detail::floor_div(cell_y, grid.chunk_height);
    plan.local_x = detail::floor_local(cell_x, grid.chunk_width);
    plan.local_y = detail::floor_local(cell_y, grid.chunk_height);
    return TilemapError::None;
}

}  // namespace stormline::tilemap

#endif  // STORMLINE_TILEMAP_GRID_PLAN_HPP
