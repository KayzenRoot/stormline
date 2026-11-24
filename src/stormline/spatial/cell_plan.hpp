#ifndef STORMLINE_SPATIAL_CELL_PLAN_HPP
#define STORMLINE_SPATIAL_CELL_PLAN_HPP

#include <array>
#include <climits>

#include "stormline/spatial/spatial_types.hpp"

namespace stormline::spatial {

struct CellDesc {
    u64 cell_key{0};
    i64 x{0};
    i64 z{0};
    u32 revision{0};
};

struct CellSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 cell_count{0};
    std::array<CellDesc, kMaxSpatialCells> cells{};
};

struct CellPlan {
    u32 cell_count{0};
    i64 min_x{0};
    i64 max_x{0};
    i64 min_z{0};
    i64 max_z{0};
};

[[nodiscard]] inline bool cell_floor_div(
    i64 value, i64 cell_size, i64& result) noexcept {
    if (value == INT64_MIN && cell_size == -1) {
        return false;
    }
    if (cell_size <= 0) {
        return false;
    }
    i64 quotient = value / cell_size;
    if (value % cell_size != 0 && value < 0) {
        --quotient;
    }
    result = quotient;
    return true;
}

[[nodiscard]] inline SpatialError plan_cells(
    const CellSetDesc& cells, CellPlan& plan,
    SpatialDiagnostic& diagnostic) noexcept {
    plan = CellPlan{};
    diagnostic = SpatialDiagnostic{};
    if (cells.world_id == 0 || cells.revision == 0) {
        return detail::set_spatial_error(
            diagnostic, SpatialError::InvalidArgument, cells.world_id, 0);
    }
    if (cells.cell_count == 0) {
        return detail::set_spatial_error(
            diagnostic, SpatialError::CellInvalid, cells.world_id, 0);
    }
    if (cells.cell_count > kMaxSpatialCells) {
        return detail::set_spatial_error(
            diagnostic, SpatialError::CapacityFull, cells.world_id, 0);
    }
    for (u32 index = 0; index < cells.cell_count; ++index) {
        const CellDesc& cell = cells.cells[index];
        if (cell.cell_key == 0 || cell.revision == 0) {
            return detail::set_spatial_error(
                diagnostic, SpatialError::CellInvalid, cells.world_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            const CellDesc& prior = cells.cells[previous];
            if (prior.cell_key == cell.cell_key
                || (prior.x == cell.x && prior.z == cell.z)) {
                return detail::set_spatial_error(
                    diagnostic, SpatialError::DuplicateId, cells.world_id,
                    index);
            }
        }
    }
    plan.cell_count = cells.cell_count;
    plan.min_x = cells.cells[0].x;
    plan.max_x = cells.cells[0].x;
    plan.min_z = cells.cells[0].z;
    plan.max_z = cells.cells[0].z;
    for (u32 index = 1; index < cells.cell_count; ++index) {
        const CellDesc& cell = cells.cells[index];
        if (cell.x < plan.min_x) {
            plan.min_x = cell.x;
        }
        if (cell.x > plan.max_x) {
            plan.max_x = cell.x;
        }
        if (cell.z < plan.min_z) {
            plan.min_z = cell.z;
        }
        if (cell.z > plan.max_z) {
            plan.max_z = cell.z;
        }
    }
    return SpatialError::None;
}

}  // namespace stormline::spatial

#endif  // STORMLINE_SPATIAL_CELL_PLAN_HPP
