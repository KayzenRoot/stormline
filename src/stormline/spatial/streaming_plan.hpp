#ifndef STORMLINE_SPATIAL_STREAMING_PLAN_HPP
#define STORMLINE_SPATIAL_STREAMING_PLAN_HPP

#include <array>

#include "stormline/spatial/spatial_types.hpp"

namespace stormline::spatial {

struct StreamingCellDesc {
    u64 cell_key{0};
    u32 revision{0};
    CellPriority priority{CellPriority::Optional};
    u32 request_generation{0};
    u32 cancel_generation{0};
    u64 byte_budget{0};
};

struct StreamingPlanDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 cell_count{0};
    std::array<StreamingCellDesc, kMaxStreamingCells> cells{};
};

struct StreamingPlan {
    u32 cell_count{0};
    u32 pinned_count{0};
    u32 prefetch_count{0};
    u64 total_bytes{0};
};

[[nodiscard]] inline SpatialError plan_streaming(
    const StreamingPlanDesc& streaming, StreamingPlan& plan,
    SpatialDiagnostic& diagnostic) noexcept {
    plan = StreamingPlan{};
    diagnostic = SpatialDiagnostic{};
    if (streaming.world_id == 0 || streaming.revision == 0) {
        return detail::set_spatial_error(
            diagnostic, SpatialError::InvalidArgument, streaming.world_id, 0);
    }
    if (streaming.cell_count > kMaxStreamingCells) {
        return detail::set_spatial_error(
            diagnostic, SpatialError::CapacityFull, streaming.world_id, 0);
    }
    for (u32 index = 0; index < streaming.cell_count; ++index) {
        const StreamingCellDesc& cell = streaming.cells[index];
        if (cell.cell_key == 0 || !detail::valid_cell_priority(cell.priority)
            || cell.request_generation == 0
            || cell.cancel_generation > cell.request_generation) {
            return detail::set_spatial_error(
                diagnostic, SpatialError::StreamInvalid, streaming.world_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (streaming.cells[previous].cell_key == cell.cell_key) {
                return detail::set_spatial_error(
                    diagnostic, SpatialError::DuplicateId, streaming.world_id,
                    index);
            }
        }
        if (cell.byte_budget > kMaxCellBytes) {
            return detail::set_spatial_error(
                diagnostic, SpatialError::OutOfRange, streaming.world_id,
                index);
        }
    }
    plan.cell_count = streaming.cell_count;
    for (u32 index = 0; index < streaming.cell_count; ++index) {
        const StreamingCellDesc& cell = streaming.cells[index];
        if (!detail::checked_add_u64(plan.total_bytes, cell.byte_budget)) {
            plan = StreamingPlan{};
            return detail::set_spatial_error(
                diagnostic, SpatialError::OutOfRange, streaming.world_id,
                index);
        }
        if (cell.priority == CellPriority::Pinned) {
            ++plan.pinned_count;
        } else if (cell.priority == CellPriority::Prefetch) {
            ++plan.prefetch_count;
        }
    }
    return SpatialError::None;
}

}  // namespace stormline::spatial

#endif  // STORMLINE_SPATIAL_STREAMING_PLAN_HPP
