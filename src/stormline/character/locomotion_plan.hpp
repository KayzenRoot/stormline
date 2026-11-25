#ifndef STORMLINE_CHARACTER_LOCOMOTION_PLAN_HPP
#define STORMLINE_CHARACTER_LOCOMOTION_PLAN_HPP

#include <array>

#include "stormline/character/character_types.hpp"

namespace stormline::character {

struct LocomotionDesc {
    u32 locomotion_id{0};
    u32 revision{0};
    u32 controller_id{0};
    f32 walk_speed{0.0f};
    f32 run_speed{0.0f};
    f32 air_speed{0.0f};
    f32 acceleration{0.0f};
    f32 deceleration{0.0f};
    f32 jump_height{0.0f};
    u32 jump_buffer_ticks{0};
    u32 coyote_ticks{0};
    f32 dash_speed{0.0f};
    u32 dash_ticks{0};
    bool enabled{false};
};

struct LocomotionSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 locomotion_count{0};
    std::array<LocomotionDesc, kMaxLocomotion> locomotion{};
};

struct LocomotionPlan {
    u32 locomotion_count{0};
    u32 ground_count{0};
    u32 air_count{0};
    u32 jump_count{0};
    u32 dash_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] inline CharacterError plan_locomotion(
    const LocomotionSetDesc& locomotion, LocomotionPlan& plan,
    CharacterDiagnostic& diagnostic) noexcept {
    plan = LocomotionPlan{};
    diagnostic = CharacterDiagnostic{};
    if (locomotion.owner_id == 0 || locomotion.revision == 0) {
        return detail::set_character_error(
            diagnostic, CharacterError::InvalidArgument, locomotion.owner_id,
            0);
    }
    if (locomotion.locomotion_count > kMaxLocomotion) {
        return detail::set_character_error(
            diagnostic, CharacterError::CapacityFull, locomotion.owner_id, 0);
    }
    for (u32 index = 0; index < locomotion.locomotion_count; ++index) {
        const LocomotionDesc& entry = locomotion.locomotion[index];
        if (entry.locomotion_id == 0 || entry.revision == 0
            || entry.controller_id == 0) {
            return detail::set_character_error(
                diagnostic, CharacterError::LocomotionInvalid,
                locomotion.owner_id, index);
        }
        if (!detail::finite(entry.walk_speed)
            || !detail::finite(entry.run_speed)
            || !detail::finite(entry.air_speed)
            || !detail::finite(entry.acceleration)
            || !detail::finite(entry.deceleration)
            || !detail::finite(entry.jump_height)
            || !detail::finite(entry.dash_speed)) {
            return detail::set_character_error(
                diagnostic, CharacterError::NonFiniteValue,
                locomotion.owner_id, index);
        }
        if (!(entry.walk_speed >= 0.0f) || !(entry.run_speed >= 0.0f)
            || !(entry.air_speed >= 0.0f) || !(entry.jump_height >= 0.0f)
            || !(entry.dash_speed >= 0.0f)) {
            return detail::set_character_error(
                diagnostic, CharacterError::OutOfRange, locomotion.owner_id,
                index);
        }
        if (!(entry.run_speed >= entry.walk_speed)) {
            return detail::set_character_error(
                diagnostic, CharacterError::OutOfRange, locomotion.owner_id,
                index);
        }
        if (!(entry.acceleration > 0.0f) || !(entry.deceleration > 0.0f)) {
            return detail::set_character_error(
                diagnostic, CharacterError::OutOfRange, locomotion.owner_id,
                index);
        }
        if (entry.jump_buffer_ticks > kMaxTickWindow
            || entry.coyote_ticks > kMaxTickWindow
            || entry.dash_ticks > kMaxTickWindow) {
            return detail::set_character_error(
                diagnostic, CharacterError::OutOfRange, locomotion.owner_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (locomotion.locomotion[previous].locomotion_id
                == entry.locomotion_id) {
                return detail::set_character_error(
                    diagnostic, CharacterError::DuplicateId,
                    locomotion.owner_id, index);
            }
        }
    }
    plan.locomotion_count = locomotion.locomotion_count;
    for (u32 index = 0; index < locomotion.locomotion_count; ++index) {
        const LocomotionDesc& entry = locomotion.locomotion[index];
        if (entry.walk_speed > 0.0f) {
            ++plan.ground_count;
        }
        if (entry.air_speed > 0.0f) {
            ++plan.air_count;
        }
        if (entry.jump_height > 0.0f) {
            ++plan.jump_count;
        }
        if (entry.dash_speed > 0.0f) {
            ++plan.dash_count;
        }
        if (entry.enabled) {
            ++plan.enabled_count;
        }
    }
    return CharacterError::None;
}

}  // namespace stormline::character

#endif  // STORMLINE_CHARACTER_LOCOMOTION_PLAN_HPP
