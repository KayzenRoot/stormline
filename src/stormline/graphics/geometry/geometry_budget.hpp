#ifndef STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_BUDGET_HPP
#define STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_BUDGET_HPP

#include "stormline/graphics/geometry/geometry_instance.hpp"

namespace stormline::graphics::geometry {

namespace detail {

inline bool checked_add_u64(u64 left, u64 right, u64& out) noexcept {
    if (right > 0xFFFFFFFFFFFFFFFFULL - left) {
        return false;
    }
    out = left + right;
    return true;
}

}  // namespace detail

[[nodiscard]] inline GeometryError validate_geometry_budget(
    const GeometryMetricSet& set, const GeometryBudget& budget,
    GeometryBudgetPlan& plan, GeometryDiagnostic& diagnostic) noexcept {
    plan = GeometryBudgetPlan{};
    if (set.count == 0 || set.count > kMaxMeshes
        || budget.max_vertices == 0 || budget.max_triangles == 0
        || budget.max_bytes == 0) {
        return detail::set_error(
            diagnostic, GeometryError::InvalidArgument, 0, 0, 0);
    }
    u64 vertices = 0;
    u64 triangles = 0;
    u64 bytes = 0;
    for (u32 index = 0; index < set.count; ++index) {
        const GeometryMetrics& metrics = set.meshes[index];
        if (metrics.mesh_id == 0 || metrics.vertex_count == 0
            || metrics.triangle_count == 0 || metrics.byte_count == 0) {
            return detail::set_error(
                diagnostic, GeometryError::InvalidArgument, 0, metrics.mesh_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (set.meshes[previous].mesh_id == metrics.mesh_id) {
                return detail::set_error(
                    diagnostic, GeometryError::DuplicateId, 0, metrics.mesh_id,
                    index);
            }
        }
        if (!detail::checked_add_u64(vertices, metrics.vertex_count, vertices)
            || !detail::checked_add_u64(triangles, metrics.triangle_count, triangles)
            || !detail::checked_add_u64(bytes, metrics.byte_count, bytes)) {
            return detail::set_error(
                diagnostic, GeometryError::InvalidArgument, 0, metrics.mesh_id,
                index);
        }
    }
    plan.total_vertices = vertices;
    plan.total_triangles = triangles;
    plan.total_bytes = bytes;
    plan.within_budget = vertices <= budget.max_vertices
        && triangles <= budget.max_triangles && bytes <= budget.max_bytes;
    if (!plan.within_budget) {
        return detail::set_error(
            diagnostic, GeometryError::GeometryBudgetExceeded, 0, 0, 0);
    }
    return GeometryError::None;
}

}  // namespace stormline::graphics::geometry

#endif  // STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_BUDGET_HPP
