#ifndef STORMLINE_CHARACTER_CONTROLLER_PLAN_HPP
#define STORMLINE_CHARACTER_CONTROLLER_PLAN_HPP

#include <array>

#include "stormline/character/character_types.hpp"

namespace stormline::character {

struct ControllerDesc {
    u32 controller_id{0};
    u32 revision{0};
    u32 entity_id{0};
    ControllerDimension dimension{ControllerDimension::TwoD};
    ControllerMode mode{ControllerMode::Kinematic};
    f32 half_x{0.0f};
    f32 half_y{0.0f};
    f32 half_z{0.0f};
    f32 up_x{0.0f};
    f32 up_y{1.0f};
    f32 up_z{0.0f};
    f32 max_slope_degrees{45.0f};
    f32 step_height{0.0f};
    bool snap_to_ground{true};
    bool slide_on_slope{true};
    bool enabled{false};
};

struct ControllerSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 controller_count{0};
    std::array<ControllerDesc, kMaxControllers> controllers{};
};

struct ControllerPlan {
    u32 controller_count{0};
    u32 two_d_count{0};
    u32 three_d_count{0};
    u32 kinematic_count{0};
    u32 dynamic_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] inline CharacterError plan_controllers(
    const ControllerSetDesc& controllers, ControllerPlan& plan,
    CharacterDiagnostic& diagnostic) noexcept {
    plan = ControllerPlan{};
    diagnostic = CharacterDiagnostic{};
    if (controllers.owner_id == 0 || controllers.revision == 0) {
        return detail::set_character_error(
            diagnostic, CharacterError::InvalidArgument, controllers.owner_id,
            0);
    }
    if (controllers.controller_count > kMaxControllers) {
        return detail::set_character_error(
            diagnostic, CharacterError::CapacityFull, controllers.owner_id,
            0);
    }
    for (u32 index = 0; index < controllers.controller_count; ++index) {
        const ControllerDesc& controller = controllers.controllers[index];
        if (controller.controller_id == 0 || controller.revision == 0
            || !detail::valid_dimension(controller.dimension)
            || !detail::valid_mode(controller.mode)) {
            return detail::set_character_error(
                diagnostic, CharacterError::ControllerInvalid,
                controllers.owner_id, index);
        }
        if (!detail::finite(controller.half_x)
            || !detail::finite(controller.half_y)
            || !detail::finite(controller.half_z)
            || !detail::finite(controller.max_slope_degrees)
            || !detail::finite(controller.step_height)) {
            return detail::set_character_error(
                diagnostic, CharacterError::NonFiniteValue,
                controllers.owner_id, index);
        }
        if (controller.dimension == ControllerDimension::TwoD) {
            if (!(controller.half_x > 0.0f) || !(controller.half_y > 0.0f)
                || controller.half_z != 0.0f) {
                return detail::set_character_error(
                    diagnostic, CharacterError::ControllerInvalid,
                    controllers.owner_id, index);
            }
        } else if (!(controller.half_x > 0.0f)
                   || !(controller.half_y > 0.0f)
                   || !(controller.half_z > 0.0f)) {
            return detail::set_character_error(
                diagnostic, CharacterError::ControllerInvalid,
                controllers.owner_id, index);
        }
        if (!detail::unit_axis(controller.up_x, controller.up_y,
                               controller.up_z)) {
            return detail::set_character_error(
                diagnostic, CharacterError::ControllerInvalid,
                controllers.owner_id, index);
        }
        if (controller.dimension == ControllerDimension::TwoD
            && controller.up_z != 0.0f) {
            return detail::set_character_error(
                diagnostic, CharacterError::ControllerInvalid,
                controllers.owner_id, index);
        }
        if (!(controller.max_slope_degrees >= 0.0f)
            || !(controller.max_slope_degrees <= 90.0f)
            || !(controller.step_height >= 0.0f)) {
            return detail::set_character_error(
                diagnostic, CharacterError::OutOfRange, controllers.owner_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (controllers.controllers[previous].controller_id
                == controller.controller_id) {
                return detail::set_character_error(
                    diagnostic, CharacterError::DuplicateId,
                    controllers.owner_id, index);
            }
        }
    }
    plan.controller_count = controllers.controller_count;
    for (u32 index = 0; index < controllers.controller_count; ++index) {
        const ControllerDesc& controller = controllers.controllers[index];
        switch (controller.dimension) {
            case ControllerDimension::TwoD:
                ++plan.two_d_count;
                break;
            case ControllerDimension::ThreeD:
                ++plan.three_d_count;
                break;
        }
        switch (controller.mode) {
            case ControllerMode::Kinematic:
                ++plan.kinematic_count;
                break;
            case ControllerMode::Dynamic:
                ++plan.dynamic_count;
                break;
        }
        if (controller.enabled) {
            ++plan.enabled_count;
        }
    }
    return CharacterError::None;
}

}  // namespace stormline::character

#endif  // STORMLINE_CHARACTER_CONTROLLER_PLAN_HPP
