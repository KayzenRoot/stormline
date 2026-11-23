#ifndef STORMLINE_GRAPHICS_POST_CAMERA_EXPOSURE_HPP
#define STORMLINE_GRAPHICS_POST_CAMERA_EXPOSURE_HPP

#include "stormline/graphics/post/post_types.hpp"

#include <cmath>

namespace stormline::graphics::post {

namespace detail {

inline PostError set_post_error(
    PostDiagnostic& diagnostic, PostError code, u32 camera_id,
    u32 index) noexcept {
    diagnostic = PostDiagnostic{code, camera_id, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return std::isfinite(value);
}

inline bool valid_projection(ProjectionKind projection) noexcept {
    return projection == ProjectionKind::Perspective
        || projection == ProjectionKind::Orthographic;
}

inline u32 find_camera(const CameraSet& set, u32 id) noexcept {
    for (u32 index = 0; index < set.count; ++index) {
        if (set.cameras[index].camera_id == id) {
            return index;
        }
    }
    return kMaxCameras;
}

inline PostError validate_camera(const CameraViewDesc& camera) noexcept {
    if (camera.camera_id == 0 || camera.revision == 0
        || camera.scene_generation == 0) {
        return PostError::InvalidCamera;
    }
    if (!valid_projection(camera.projection)) {
        return PostError::InvalidProjection;
    }
    if (!finite(camera.vertical_fov_radians) || !finite(camera.aspect)
        || !finite(camera.ortho_height) || !finite(camera.near_distance)
        || !finite(camera.far_distance) || !finite(camera.jitter.x)
        || !finite(camera.jitter.y) || !finite(camera.previous_jitter.x)
        || !finite(camera.previous_jitter.y)) {
        return PostError::NonFiniteValue;
    }
    if (!(camera.aspect > 0.0f) || !(camera.near_distance > 0.0f)
        || !(camera.far_distance > camera.near_distance)
        || camera.render_width == 0 || camera.render_height == 0
        || camera.output_width == 0 || camera.output_height == 0) {
        return PostError::InvalidCamera;
    }
    if (!camera.jitter_world_only) {
        return PostError::InvalidCamera;
    }
    if (camera.projection == ProjectionKind::Perspective) {
        if (!(camera.vertical_fov_radians > 0.0f)
            || !(camera.vertical_fov_radians < kPi)) {
            return PostError::InvalidProjection;
        }
    } else if (!(camera.ortho_height > 0.0f)) {
        return PostError::InvalidProjection;
    }
    return PostError::None;
}

}  // namespace detail

[[nodiscard]] inline const char* post_error_name(PostError error) noexcept {
    switch (error) {
        case PostError::None: return "None";
        case PostError::InvalidArgument: return "InvalidArgument";
        case PostError::DuplicateId: return "DuplicateId";
        case PostError::NotFound: return "NotFound";
        case PostError::CapacityFull: return "CapacityFull";
        case PostError::NonFiniteValue: return "NonFiniteValue";
        case PostError::OutOfRange: return "OutOfRange";
        case PostError::InvalidProjection: return "InvalidProjection";
        case PostError::InvalidCamera: return "InvalidCamera";
        case PostError::ColorSpaceMismatch: return "ColorSpaceMismatch";
        case PostError::DoubleTransferGuard: return "DoubleTransferGuard";
        case PostError::HdrUnavailable: return "HdrUnavailable";
        case PostError::HistoryInvalid: return "HistoryInvalid";
        case PostError::TemporalUnsupported: return "TemporalUnsupported";
        case PostError::BudgetExceeded: return "BudgetExceeded";
        case PostError::Unsupported: return "Unsupported";
    }
    return "Unknown";
}

[[nodiscard]] inline PostError add_camera(
    CameraSet& set, const CameraViewDesc& camera) noexcept {
    if (set.count >= kMaxCameras) {
        return PostError::CapacityFull;
    }
    const PostError validation = detail::validate_camera(camera);
    if (validation != PostError::None) {
        return validation;
    }
    if (detail::find_camera(set, camera.camera_id) != kMaxCameras) {
        return PostError::DuplicateId;
    }
    set.cameras[set.count] = camera;
    ++set.count;
    return PostError::None;
}

[[nodiscard]] inline PostError validate_cameras(
    const CameraSet& set, PostDiagnostic& diagnostic) noexcept {
    diagnostic = PostDiagnostic{};
    if (set.count > kMaxCameras) {
        return detail::set_post_error(
            diagnostic, PostError::InvalidArgument, 0, 0);
    }
    for (u32 index = 0; index < set.count; ++index) {
        const CameraViewDesc& camera = set.cameras[index];
        const PostError validation = detail::validate_camera(camera);
        if (validation != PostError::None) {
            return detail::set_post_error(
                diagnostic, validation, camera.camera_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (set.cameras[previous].camera_id == camera.camera_id) {
                return detail::set_post_error(
                    diagnostic, PostError::DuplicateId, camera.camera_id,
                    index);
            }
        }
    }
    return PostError::None;
}

struct ExposureDesc {
    f32 ev100{0.0f};
    bool auto_exposure{false};
    f32 min_ev{-8.0f};
    f32 max_ev{8.0f};
    f32 dark_adapt_seconds{1.0f};
    f32 bright_adapt_seconds{1.0f};
    f32 low_percentile{0.1f};
    f32 high_percentile{0.9f};
    bool flash_resilient{true};
};

struct ExposurePlan {
    f32 ev100{0.0f};
    bool auto_exposure{false};
    bool flash_resilient{true};
};

[[nodiscard]] inline PostError plan_exposure(
    const ExposureDesc& exposure, ExposurePlan& plan,
    PostDiagnostic& diagnostic) noexcept {
    plan = ExposurePlan{};
    diagnostic = PostDiagnostic{};
    if (!detail::finite(exposure.ev100) || !detail::finite(exposure.min_ev)
        || !detail::finite(exposure.max_ev)
        || !detail::finite(exposure.dark_adapt_seconds)
        || !detail::finite(exposure.bright_adapt_seconds)
        || !detail::finite(exposure.low_percentile)
        || !detail::finite(exposure.high_percentile)) {
        return detail::set_post_error(
            diagnostic, PostError::NonFiniteValue, 0, 0);
    }
    if (exposure.min_ev > exposure.max_ev || !(exposure.dark_adapt_seconds > 0.0f)
        || !(exposure.bright_adapt_seconds > 0.0f)
        || exposure.low_percentile < 0.0f
        || exposure.high_percentile > 100.0f
        || !(exposure.low_percentile < exposure.high_percentile)) {
        return detail::set_post_error(
            diagnostic, PostError::OutOfRange, 0, 0);
    }
    if (!exposure.auto_exposure
        && (exposure.ev100 < exposure.min_ev
            || exposure.ev100 > exposure.max_ev)) {
        return detail::set_post_error(
            diagnostic, PostError::OutOfRange, 0, 0);
    }
    plan.ev100 = exposure.ev100;
    plan.auto_exposure = exposure.auto_exposure;
    plan.flash_resilient = exposure.flash_resilient;
    return PostError::None;
}

}  // namespace stormline::graphics::post

#endif  // STORMLINE_GRAPHICS_POST_CAMERA_EXPOSURE_HPP
