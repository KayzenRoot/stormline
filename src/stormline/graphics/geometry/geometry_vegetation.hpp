#ifndef STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_VEGETATION_HPP
#define STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_VEGETATION_HPP

#include "stormline/graphics/geometry/geometry_instance.hpp"

#include <cmath>

namespace stormline::graphics::geometry {

[[nodiscard]] inline GeometryError classify_vegetation(
    const InstanceDesc& instance, const VegetationRequest& request,
    VegetationDecision& decision, GeometryDiagnostic& diagnostic) noexcept {
    decision = VegetationDecision{};
    if (instance.id == 0
        || (instance.vegetation != VegetationKind::Grass
            && instance.vegetation != VegetationKind::Bush
            && instance.vegetation != VegetationKind::Tree)
        || !detail::valid_bounds(instance.bounds)) {
        return detail::set_error(
            diagnostic, GeometryError::InvalidArgument, instance.id,
            instance.mesh_id, 0);
    }
    if (!std::isfinite(request.billboard_distance)
        || request.billboard_distance <= 0.0f
        || !std::isfinite(request.camera.x) || !std::isfinite(request.camera.y)
        || !std::isfinite(request.camera.z)) {
        return detail::set_error(
            diagnostic, GeometryError::InvalidArgument, instance.id,
            instance.mesh_id, 0);
    }

    decision.instance_id = instance.id;
    decision.render_class = VegetationRenderClass::Mesh;
    decision.double_sided = instance.double_sided;
    decision.alpha_cutout = instance.alpha_cutout;
    if (instance.bounds.known && instance.billboard_allowed) {
        const f32 dx = instance.bounds.center.x - request.camera.x;
        const f32 dy = instance.bounds.center.y - request.camera.y;
        const f32 dz = instance.bounds.center.z - request.camera.z;
        const f32 distance_squared = dx * dx + dy * dy + dz * dz;
        if (distance_squared > request.billboard_distance * request.billboard_distance) {
            decision.render_class = VegetationRenderClass::Billboard;
        }
    }
    return GeometryError::None;
}

}  // namespace stormline::graphics::geometry

#endif  // STORMLINE_GRAPHICS_GEOMETRY_GEOMETRY_VEGETATION_HPP
