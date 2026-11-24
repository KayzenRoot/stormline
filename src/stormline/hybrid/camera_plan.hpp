#ifndef STORMLINE_HYBRID_CAMERA_PLAN_HPP
#define STORMLINE_HYBRID_CAMERA_PLAN_HPP

#include "stormline/hybrid/hybrid_types.hpp"

namespace stormline::hybrid {

struct CameraDesc {
    u32 camera_id{0};
    u32 revision{0};
    ProjectionKind projection{ProjectionKind::Orthographic};
    f32 near_plane{0.0f};
    f32 far_plane{0.0f};
    f32 ortho_half_height{0.0f};
    f32 ortho_aspect{0.0f};
    f32 perspective_fov_degrees{0.0f};
    f32 perspective_aspect{0.0f};
};

struct CameraPlan {
    ProjectionKind projection{ProjectionKind::Orthographic};
    f32 near_plane{0.0f};
    f32 far_plane{0.0f};
    f32 primary_extent{0.0f};
    f32 aspect{0.0f};
};

[[nodiscard]] inline HybridError plan_camera(
    const CameraDesc& camera, CameraPlan& plan,
    HybridDiagnostic& diagnostic) noexcept {
    plan = CameraPlan{};
    diagnostic = HybridDiagnostic{};
    if (camera.camera_id == 0 || camera.revision == 0) {
        return detail::set_hybrid_error(
            diagnostic, HybridError::InvalidArgument, camera.camera_id, 0);
    }
    if (!detail::valid_projection(camera.projection)) {
        return detail::set_hybrid_error(
            diagnostic, HybridError::CameraInvalid, camera.camera_id, 0);
    }
    if (!detail::finite(camera.near_plane)
        || !detail::finite(camera.far_plane)) {
        return detail::set_hybrid_error(
            diagnostic, HybridError::NonFiniteValue, camera.camera_id, 0);
    }
    if (!(camera.near_plane > 0.0f) || !(camera.far_plane > camera.near_plane)) {
        return detail::set_hybrid_error(
            diagnostic, HybridError::CameraInvalid, camera.camera_id, 0);
    }
    if (camera.projection == ProjectionKind::Orthographic) {
        if (!detail::finite(camera.ortho_half_height)
            || !detail::finite(camera.ortho_aspect)) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::NonFiniteValue, camera.camera_id, 0);
        }
        if (!(camera.ortho_half_height > 0.0f)
            || !(camera.ortho_aspect > 0.0f)) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::CameraInvalid, camera.camera_id, 0);
        }
        plan.primary_extent = camera.ortho_half_height;
        plan.aspect = camera.ortho_aspect;
    } else {
        if (!detail::finite(camera.perspective_fov_degrees)
            || !detail::finite(camera.perspective_aspect)) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::NonFiniteValue, camera.camera_id, 0);
        }
        if (!(camera.perspective_fov_degrees > 0.0f)
            || !(camera.perspective_fov_degrees < 180.0f)
            || !(camera.perspective_aspect > 0.0f)) {
            return detail::set_hybrid_error(
                diagnostic, HybridError::CameraInvalid, camera.camera_id, 0);
        }
        plan.primary_extent = camera.perspective_fov_degrees;
        plan.aspect = camera.perspective_aspect;
    }
    plan.projection = camera.projection;
    plan.near_plane = camera.near_plane;
    plan.far_plane = camera.far_plane;
    return HybridError::None;
}

}  // namespace stormline::hybrid

#endif  // STORMLINE_HYBRID_CAMERA_PLAN_HPP
