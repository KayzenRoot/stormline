#ifndef STORMLINE_CHARACTER_INPUT_PLAN_HPP
#define STORMLINE_CHARACTER_INPUT_PLAN_HPP

#include <array>

#include "stormline/character/character_types.hpp"

namespace stormline::character {

struct InputActionDesc {
    u32 action_id{0};
    u32 revision{0};
    u32 axis_index{0};
    f32 dead_zone{0.0f};
    f32 scale{1.0f};
    u32 buffer_ticks{0};
    bool consume_on_use{false};
    bool enabled{false};
};

struct InputSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 action_count{0};
    std::array<InputActionDesc, kMaxInputActions> actions{};
};

struct InputPlan {
    u32 action_count{0};
    u32 axis_count{0};
    u32 buffered_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] inline CharacterError plan_input(
    const InputSetDesc& input, InputPlan& plan,
    CharacterDiagnostic& diagnostic) noexcept {
    plan = InputPlan{};
    diagnostic = CharacterDiagnostic{};
    if (input.owner_id == 0 || input.revision == 0) {
        return detail::set_character_error(
            diagnostic, CharacterError::InvalidArgument, input.owner_id, 0);
    }
    if (input.action_count > kMaxInputActions) {
        return detail::set_character_error(
            diagnostic, CharacterError::CapacityFull, input.owner_id, 0);
    }
    for (u32 index = 0; index < input.action_count; ++index) {
        const InputActionDesc& action = input.actions[index];
        if (action.action_id == 0 || action.revision == 0
            || action.axis_index > 7) {
            return detail::set_character_error(
                diagnostic, CharacterError::InputInvalid, input.owner_id,
                index);
        }
        if (!detail::finite(action.dead_zone)
            || !detail::finite(action.scale)) {
            return detail::set_character_error(
                diagnostic, CharacterError::NonFiniteValue, input.owner_id,
                index);
        }
        if (!(action.dead_zone >= 0.0f) || !(action.dead_zone <= 1.0f)
            || action.scale == 0.0f) {
            return detail::set_character_error(
                diagnostic, CharacterError::OutOfRange, input.owner_id,
                index);
        }
        if (action.buffer_ticks > kMaxTickWindow) {
            return detail::set_character_error(
                diagnostic, CharacterError::OutOfRange, input.owner_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (input.actions[previous].action_id == action.action_id) {
                return detail::set_character_error(
                    diagnostic, CharacterError::DuplicateId, input.owner_id,
                    index);
            }
        }
    }
    plan.action_count = input.action_count;
    for (u32 index = 0; index < input.action_count; ++index) {
        const InputActionDesc& action = input.actions[index];
        if (action.axis_index != 0) {
            ++plan.axis_count;
        }
        if (action.buffer_ticks != 0) {
            ++plan.buffered_count;
        }
        if (action.enabled) {
            ++plan.enabled_count;
        }
    }
    return CharacterError::None;
}

}  // namespace stormline::character

#endif  // STORMLINE_CHARACTER_INPUT_PLAN_HPP
