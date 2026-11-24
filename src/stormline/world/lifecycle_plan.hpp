#ifndef STORMLINE_WORLD_LIFECYCLE_PLAN_HPP
#define STORMLINE_WORLD_LIFECYCLE_PLAN_HPP

#include <array>

#include "stormline/world/world_types.hpp"

namespace stormline::world {

struct LifecycleTransitionDesc {
    u32 slot{0};
    u32 generation{0};
    EntityState from{EntityState::Alive};
    EntityState to{EntityState::Alive};
};

struct LifecycleBatchDesc {
    u32 world_epoch{0};
    u32 slot_count{0};
    u32 transition_count{0};
    std::array<LifecycleTransitionDesc, kMaxWorldEntities> transitions{};
};

struct LifecyclePlan {
    u32 transition_count{0};
    u32 retire_count{0};
    u32 idempotent_count{0};
};

namespace detail {

inline bool lifecycle_allowed(EntityState from, EntityState to) noexcept {
    if (from == to) {
        return true;
    }
    if (from == EntityState::Alive && to == EntityState::DestroyRequested) {
        return true;
    }
    if (from == EntityState::DestroyRequested
        && to == EntityState::Tombstoned) {
        return true;
    }
    return from == EntityState::Tombstoned && to == EntityState::Retired;
}

}  // namespace detail

[[nodiscard]] inline WorldError plan_lifecycle(
    const LifecycleBatchDesc& batch, LifecyclePlan& plan,
    WorldDiagnostic& diagnostic) noexcept {
    plan = LifecyclePlan{};
    diagnostic = WorldDiagnostic{};
    if (batch.world_epoch == 0) {
        return detail::set_world_error(
            diagnostic, WorldError::InvalidArgument, batch.world_epoch, 0);
    }
    if (batch.slot_count == 0 || batch.slot_count > kMaxWorldEntities) {
        return detail::set_world_error(
            diagnostic, WorldError::LifecycleInvalid, batch.world_epoch, 0);
    }
    if (batch.transition_count == 0
        || batch.transition_count > kMaxWorldEntities) {
        return detail::set_world_error(
            diagnostic, WorldError::LifecycleInvalid, batch.world_epoch, 0);
    }
    LifecyclePlan computed{};
    computed.transition_count = batch.transition_count;
    for (u32 index = 0; index < batch.transition_count; ++index) {
        const LifecycleTransitionDesc& transition = batch.transitions[index];
        if (transition.slot >= batch.slot_count
            || transition.generation == 0
            || !detail::valid_state(transition.from)
            || !detail::valid_state(transition.to)) {
            return detail::set_world_error(
                diagnostic, WorldError::LifecycleInvalid, batch.world_epoch,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (batch.transitions[previous].slot == transition.slot) {
                return detail::set_world_error(
                    diagnostic, WorldError::DuplicateId, batch.world_epoch,
                    index);
            }
        }
        if (!detail::lifecycle_allowed(transition.from, transition.to)) {
            return detail::set_world_error(
                diagnostic, WorldError::LifecycleInvalid, batch.world_epoch,
                index);
        }
        if (transition.from == transition.to) {
            ++computed.idempotent_count;
        }
        if (transition.to == EntityState::Retired) {
            ++computed.retire_count;
        }
    }
    plan = computed;
    return WorldError::None;
}

}  // namespace stormline::world

#endif  // STORMLINE_WORLD_LIFECYCLE_PLAN_HPP
