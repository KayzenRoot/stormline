#ifndef STORMLINE_PHYSICS2D_TRIGGER_PLAN_HPP
#define STORMLINE_PHYSICS2D_TRIGGER_PLAN_HPP

#include <array>

#include "stormline/physics2d/physics2d_types.hpp"

namespace stormline::physics2d {

struct TriggerDesc {
    u32 trigger_id{0};
    u32 revision{0};
    u32 body_id{0};
    u32 shape_id{0};
    u32 mask_bits{0};
    bool enter_enabled{false};
    bool exit_enabled{false};
};

struct TriggerSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 trigger_count{0};
    std::array<TriggerDesc, kMaxTriggers> triggers{};
};

struct TriggerPlan {
    u32 trigger_count{0};
    u32 enter_count{0};
    u32 exit_count{0};
    u32 both_count{0};
};

[[nodiscard]] inline Physics2DError plan_triggers(
    const TriggerSetDesc& triggers, TriggerPlan& plan,
    Physics2DDiagnostic& diagnostic) noexcept {
    plan = TriggerPlan{};
    diagnostic = Physics2DDiagnostic{};
    if (triggers.world_id == 0 || triggers.revision == 0) {
        return detail::set_physics2d_error(
            diagnostic, Physics2DError::InvalidArgument, triggers.world_id,
            0);
    }
    if (triggers.trigger_count > kMaxTriggers) {
        return detail::set_physics2d_error(
            diagnostic, Physics2DError::CapacityFull, triggers.world_id, 0);
    }
    for (u32 index = 0; index < triggers.trigger_count; ++index) {
        const TriggerDesc& trigger = triggers.triggers[index];
        if (trigger.trigger_id == 0 || trigger.revision == 0
            || trigger.body_id == 0 || trigger.shape_id == 0
            || trigger.mask_bits == 0
            || (!trigger.enter_enabled && !trigger.exit_enabled)) {
            return detail::set_physics2d_error(
                diagnostic, Physics2DError::TriggerInvalid,
                triggers.world_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (triggers.triggers[previous].trigger_id
                == trigger.trigger_id) {
                return detail::set_physics2d_error(
                    diagnostic, Physics2DError::DuplicateId,
                    triggers.world_id, index);
            }
        }
    }
    plan.trigger_count = triggers.trigger_count;
    for (u32 index = 0; index < triggers.trigger_count; ++index) {
        const TriggerDesc& trigger = triggers.triggers[index];
        if (trigger.enter_enabled) {
            ++plan.enter_count;
        }
        if (trigger.exit_enabled) {
            ++plan.exit_count;
        }
        if (trigger.enter_enabled && trigger.exit_enabled) {
            ++plan.both_count;
        }
    }
    return Physics2DError::None;
}

}  // namespace stormline::physics2d

#endif  // STORMLINE_PHYSICS2D_TRIGGER_PLAN_HPP
