#ifndef STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_CULL_HPP
#define STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_CULL_HPP

#include "stormline/graphics/geometry/geometry_instance.hpp"

#include <cmath>

namespace stormline::graphics::geometry {

namespace detail {

inline bool finite_vec(const Vec3& value) noexcept {
    return std::isfinite(value.x) && std::isfinite(value.y)
        && std::isfinite(value.z);
}

inline bool valid_plane(const Plane& plane) noexcept {
    if (!finite_vec(plane.normal) || !std::isfinite(plane.distance)) {
        return false;
    }
    const f32 length_squared = plane.normal.x * plane.normal.x
        + plane.normal.y * plane.normal.y + plane.normal.z * plane.normal.z;
    return length_squared >= 0.99f && length_squared <= 1.01f;
}

}  // namespace detail

[[nodiscard]] inline GeometryError cull_instances(
    const InstanceSet& set, const ViewFrustum& view,
    CullResult& result, GeometryDiagnostic& diagnostic) noexcept {
    result = CullResult{};
    const GeometryError validation = validate_instances(set, diagnostic);
    if (validation != GeometryError::None) {
        return validation;
    }
    if (view.scene_generation == 0
        || view.scene_generation != set.scene_generation) {
        return detail::set_error(
            diagnostic, GeometryError::GenerationMismatch, 0, 0, 0);
    }
    if (view.plane_count == 0 || view.plane_count > kMaxPlanes
        || !std::isfinite(view.max_distance) || view.max_distance <= 0.0f
        || !detail::finite_vec(view.camera)) {
        return detail::set_error(
            diagnostic, GeometryError::InvalidCamera, 0, 0, 0);
    }
    for (u32 index = 0; index < view.plane_count; ++index) {
        if (!detail::valid_plane(view.planes[index])) {
            return detail::set_error(
                diagnostic, GeometryError::InvalidCamera, 0, 0, index);
        }
    }

    for (u32 index = 0; index < set.count; ++index) {
        const InstanceDesc& instance = set.instances[index];
        bool visible = true;
        if (instance.bounds.known) {
            const f32 dx = instance.bounds.center.x - view.camera.x;
            const f32 dy = instance.bounds.center.y - view.camera.y;
            const f32 dz = instance.bounds.center.z - view.camera.z;
            const f32 limit = view.max_distance + instance.bounds.radius;
            const f32 distance_squared = dx * dx + dy * dy + dz * dz;
            if (distance_squared > limit * limit) {
                visible = false;
            }
            if (visible) {
                for (u32 plane_index = 0; plane_index < view.plane_count;
                     ++plane_index) {
                    const Plane& plane = view.planes[plane_index];
                    const f32 distance =
                        plane.normal.x * instance.bounds.center.x
                        + plane.normal.y * instance.bounds.center.y
                        + plane.normal.z * instance.bounds.center.z
                        + plane.distance;
                    if (distance < -instance.bounds.radius) {
                        visible = false;
                        break;
                    }
                }
            }
        }
        if (visible) {
            result.visible_ids[result.visible_count] = instance.id;
            ++result.visible_count;
        }
    }
    result.culled_count = set.count - result.visible_count;
    return GeometryError::None;
}

}  // namespace stormline::graphics::geometry

#endif  // STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_CULL_HPP
