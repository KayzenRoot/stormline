#ifndef STORMLINE_TILEMAP_STREAMING_PLAN_HPP
#define STORMLINE_TILEMAP_STREAMING_PLAN_HPP

#include "stormline/tilemap/tilemap_types.hpp"

namespace stormline::tilemap {

struct StreamingBudget {
    u32 max_visible_chunks{0};
    u32 max_prefetch_chunks{0};
    u32 max_requests{0};
    u64 max_bytes{0};
};

struct StreamingRequest {
    u32 map_id{0};
    u32 revision{0};
    u32 visible_chunks{0};
    u32 prefetch_chunks{0};
    u32 request_count{0};
    u64 requested_bytes{0};
    u32 failed_chunks{0};
};

struct StreamingPlan {
    u32 visible_chunks{0};
    u32 prefetch_chunks{0};
    u32 request_count{0};
    u64 bytes{0};
    bool degraded{false};
};

namespace detail {

inline u32 clamp_u32(u32 value, u32 cap) noexcept {
    return value > cap ? cap : value;
}

inline u64 clamp_u64(u64 value, u64 cap) noexcept {
    return value > cap ? cap : value;
}

}  // namespace detail

[[nodiscard]] inline TilemapError plan_streaming(
    const StreamingRequest& request, const StreamingBudget& budget,
    StreamingPlan& plan, TilemapDiagnostic& diagnostic) noexcept {
    plan = StreamingPlan{};
    diagnostic = TilemapDiagnostic{};
    if (request.map_id == 0 || request.revision == 0) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::InvalidArgument, request.map_id, 0);
    }
    if (budget.max_visible_chunks == 0 || budget.max_prefetch_chunks == 0
        || budget.max_requests == 0 || budget.max_bytes == 0) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::StreamingInvalid, request.map_id, 0);
    }
    if (request.failed_chunks > request.request_count) {
        return detail::set_tilemap_error(
            diagnostic, TilemapError::StreamingInvalid, request.map_id, 0);
    }
    plan.visible_chunks =
        detail::clamp_u32(request.visible_chunks, budget.max_visible_chunks);
    plan.prefetch_chunks =
        detail::clamp_u32(request.prefetch_chunks, budget.max_prefetch_chunks);
    plan.request_count =
        detail::clamp_u32(request.request_count, budget.max_requests);
    plan.bytes = detail::clamp_u64(request.requested_bytes, budget.max_bytes);
    plan.degraded = plan.visible_chunks != request.visible_chunks
        || plan.prefetch_chunks != request.prefetch_chunks
        || plan.request_count != request.request_count
        || plan.bytes != request.requested_bytes;
    return TilemapError::None;
}

}  // namespace stormline::tilemap

#endif  // STORMLINE_TILEMAP_STREAMING_PLAN_HPP
