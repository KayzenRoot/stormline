#ifndef STORMLINE_PHYSICS3D_QUERY_PLAN_HPP
#define STORMLINE_PHYSICS3D_QUERY_PLAN_HPP

#include <array>

#include "stormline/physics3d/physics3d_types.hpp"

namespace stormline::physics3d {

struct QueryDesc {
    u32 query_id{0};
    u32 revision{0};
    QueryKind kind{QueryKind::Ray};
    f32 origin_x{0.0f};
    f32 origin_y{0.0f};
    f32 origin_z{0.0f};
    f32 direction_x{0.0f};
    f32 direction_y{0.0f};
    f32 direction_z{0.0f};
    f32 max_distance{0.0f};
    u32 layer_bits{0};
    u32 max_results{0};
};

struct QuerySetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 query_count{0};
    std::array<QueryDesc, kMaxQueries> queries{};
};

struct QueryPlan {
    u32 query_count{0};
    u32 ray_count{0};
    u32 overlap_count{0};
    u32 sweep_count{0};
    u32 shape_cast_count{0};
    u32 total_result_limit{0};
};

[[nodiscard]] inline Physics3DError plan_queries(
    const QuerySetDesc& queries, QueryPlan& plan,
    Physics3DDiagnostic& diagnostic) noexcept {
    plan = QueryPlan{};
    diagnostic = Physics3DDiagnostic{};
    if (queries.world_id == 0 || queries.revision == 0) {
        return detail::set_physics3d_error(
            diagnostic, Physics3DError::InvalidArgument, queries.world_id, 0);
    }
    if (queries.query_count > kMaxQueries) {
        return detail::set_physics3d_error(
            diagnostic, Physics3DError::CapacityFull, queries.world_id, 0);
    }
    for (u32 index = 0; index < queries.query_count; ++index) {
        const QueryDesc& query = queries.queries[index];
        if (query.query_id == 0 || query.revision == 0
            || !detail::valid_query_kind(query.kind)
            || query.layer_bits == 0) {
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::QueryInvalid, queries.world_id,
                index);
        }
        if (!detail::finite(query.origin_x)
            || !detail::finite(query.origin_y)
            || !detail::finite(query.origin_z)
            || !detail::finite(query.direction_x)
            || !detail::finite(query.direction_y)
            || !detail::finite(query.direction_z)
            || !detail::finite(query.max_distance)) {
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::NonFiniteValue, queries.world_id,
                index);
        }
        if (query.max_results == 0
            || query.max_results > kMaxQueryResults) {
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::OutOfRange, queries.world_id,
                index);
        }
        if (query.kind == QueryKind::Ray || query.kind == QueryKind::Sweep
            || query.kind == QueryKind::ShapeCast) {
            if (!detail::nonzero_direction(query.direction_x,
                                          query.direction_y,
                                          query.direction_z)
                || !(query.max_distance > 0.0f)) {
                return detail::set_physics3d_error(
                    diagnostic, Physics3DError::OutOfRange, queries.world_id,
                    index);
            }
        } else if (!(query.max_distance >= 0.0f)) {
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::OutOfRange, queries.world_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (queries.queries[previous].query_id == query.query_id) {
                return detail::set_physics3d_error(
                    diagnostic, Physics3DError::DuplicateId, queries.world_id,
                    index);
            }
        }
    }
    plan.query_count = queries.query_count;
    for (u32 index = 0; index < queries.query_count; ++index) {
        const QueryDesc& query = queries.queries[index];
        switch (query.kind) {
            case QueryKind::Ray:
                ++plan.ray_count;
                break;
            case QueryKind::Overlap:
                ++plan.overlap_count;
                break;
            case QueryKind::Sweep:
                ++plan.sweep_count;
                break;
            case QueryKind::ShapeCast:
                ++plan.shape_cast_count;
                break;
        }
        if (!detail::checked_add_u32(plan.total_result_limit,
                                     query.max_results)
            || plan.total_result_limit > kMaxTotalQueryResults) {
            plan = QueryPlan{};
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::OutOfRange, queries.world_id,
                index);
        }
    }
    return Physics3DError::None;
}

}  // namespace stormline::physics3d

#endif  // STORMLINE_PHYSICS3D_QUERY_PLAN_HPP
