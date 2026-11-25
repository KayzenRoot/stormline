#ifndef STORMLINE_CHARACTER_CAMERA_PLAN_HPP
#define STORMLINE_CHARACTER_CAMERA_PLAN_HPP

#include <array>

#include "stormline/character/character_types.hpp"

namespace stormline::character {

struct CameraDesc {
    u32 camera_id{0};
    u32 revision{0};
    u32 target_controller_id{0};
    f32 distance{0.0f};
    f32 height{0.0f};
    f32 yaw_offset_degrees{0.0f};
    f32 pitch_degrees{0.0f};
    f32 position_damping{0.0f};
    f32 rotation_damping{0.0f};
    bool follow_enabled{false};
    bool independent_from_animation{true};
};

struct CameraSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 camera_count{0};
    std::array<CameraDesc, kMaxCameras> cameras{};
};

struct CameraPlan {
    u32 camera_count{0};
    u32 follow_count{0};
    u32 independent_count{0};
};

[[nodiscard]] inline CharacterError plan_cameras(
    const CameraSetDesc& cameras, CameraPlan& plan,
    CharacterDiagnostic& diagnostic) noexcept {
    plan = CameraPlan{};
    diagnostic = CharacterDiagnostic{};
    if (cameras.owner_id == 0 || cameras.revision == 0) {
        return detail::set_character_error(
            diagnostic, CharacterError::InvalidArgument, cameras.owner_id, 0);
    }
    if (cameras.camera_count > kMaxCameras) {
        return detail::set_character_error(
            diagnostic, CharacterError::CapacityFull, cameras.owner_id, 0);
    }
    for (u32 index = 0; index < cameras.camera_count; ++index) {
        const CameraDesc& camera = cameras.cameras[index];
        if (camera.camera_id == 0 || camera.revision == 0
            || camera.target_controller_id == 0
            || !camera.independent_from_animation) {
            return detail::set_character_error(
                diagnostic, CharacterError::CameraInvalid, cameras.owner_id,
                index);
        }
        if (!detail::finite(camera.distance) || !detail::finite(camera.height)
            || !detail::finite(camera.yaw_offset_degrees)
            || !detail::finite(camera.pitch_degrees)
            || !detail::finite(camera.position_damping)
            || !detail::finite(camera.rotation_damping)) {
            return detail::set_character_error(
                diagnostic, CharacterError::NonFiniteValue, cameras.owner_id,
                index);
        }
        if (!(camera.distance >= 0.0f)
            || !(camera.pitch_degrees >= -89.0f)
            || !(camera.pitch_degrees <= 89.0f)
            || !(camera.position_damping >= 0.0f)
            || !(camera.position_damping <= 1.0f)
            || !(camera.rotation_damping >= 0.0f)
            || !(camera.rotation_damping <= 1.0f)) {
            return detail::set_character_error(
                diagnostic, CharacterError::OutOfRange, cameras.owner_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (cameras.cameras[previous].camera_id == camera.camera_id) {
                return detail::set_character_error(
                    diagnostic, CharacterError::DuplicateId, cameras.owner_id,
                    index);
            }
        }
    }
    plan.camera_count = cameras.camera_count;
    for (u32 index = 0; index < cameras.camera_count; ++index) {
        const CameraDesc& camera = cameras.cameras[index];
        if (camera.follow_enabled) {
            ++plan.follow_count;
        }
        if (camera.independent_from_animation) {
            ++plan.independent_count;
        }
    }
    return CharacterError::None;
}

}  // namespace stormline::character

#endif  // STORMLINE_CHARACTER_CAMERA_PLAN_HPP
