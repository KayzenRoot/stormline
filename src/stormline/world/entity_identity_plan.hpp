#ifndef STORMLINE_WORLD_ENTITY_IDENTITY_PLAN_HPP
#define STORMLINE_WORLD_ENTITY_IDENTITY_PLAN_HPP

#include <array>

#include "stormline/world/world_types.hpp"

namespace stormline::world {

struct EntitySlotDesc {
    u32 generation{0};
    bool occupied{false};
    bool retired{false};
};

struct WorldIdentityDesc {
    u32 world_epoch{0};
    u32 slot_count{0};
    std::array<EntitySlotDesc, kMaxWorldEntities> slots{};
};

struct WorldIdentityPlan {
    u32 slot_count{0};
    u32 occupied_count{0};
    u32 retired_count{0};
};

struct EntityHandleDesc {
    u32 slot{0};
    u32 generation{0};
    u32 world_epoch{0};
};

struct EntityHandlePlan {
    bool valid{false};
    u32 slot{0};
    u32 generation{0};
    u32 world_epoch{0};
};

[[nodiscard]] inline WorldError plan_world_identity(
    const WorldIdentityDesc& world, WorldIdentityPlan& plan,
    WorldDiagnostic& diagnostic) noexcept {
    plan = WorldIdentityPlan{};
    diagnostic = WorldDiagnostic{};
    if (world.world_epoch == 0) {
        return detail::set_world_error(
            diagnostic, WorldError::InvalidArgument, world.world_epoch, 0);
    }
    if (world.slot_count == 0 || world.slot_count > kMaxWorldEntities) {
        return detail::set_world_error(
            diagnostic, WorldError::EntityInvalid, world.world_epoch, 0);
    }
    WorldIdentityPlan computed{};
    computed.slot_count = world.slot_count;
    for (u32 index = 0; index < world.slot_count; ++index) {
        const EntitySlotDesc& slot = world.slots[index];
        if (slot.occupied && slot.retired) {
            return detail::set_world_error(
                diagnostic, WorldError::EntityInvalid, world.world_epoch,
                index);
        }
        if (slot.occupied && slot.generation == 0) {
            return detail::set_world_error(
                diagnostic, WorldError::EntityInvalid, world.world_epoch,
                index);
        }
        if (slot.occupied) {
            ++computed.occupied_count;
        }
        if (slot.retired) {
            ++computed.retired_count;
        }
    }
    plan = computed;
    return WorldError::None;
}

[[nodiscard]] inline WorldError plan_entity_handle(
    const EntityHandleDesc& handle, const WorldIdentityDesc& world,
    EntityHandlePlan& plan, WorldDiagnostic& diagnostic) noexcept {
    plan = EntityHandlePlan{};
    diagnostic = WorldDiagnostic{};
    if (world.world_epoch == 0 || world.slot_count == 0
        || world.slot_count > kMaxWorldEntities) {
        return detail::set_world_error(
            diagnostic, WorldError::EntityInvalid, handle.world_epoch,
            handle.slot);
    }
    if (handle.world_epoch == 0 || handle.world_epoch != world.world_epoch
        || handle.slot >= world.slot_count || handle.generation == 0) {
        return detail::set_world_error(
            diagnostic, WorldError::EntityInvalid, handle.world_epoch,
            handle.slot);
    }
    const EntitySlotDesc& slot = world.slots[handle.slot];
    if (!slot.occupied || slot.retired
        || slot.generation != handle.generation) {
        return detail::set_world_error(
            diagnostic, WorldError::EntityInvalid, handle.world_epoch,
            handle.slot);
    }
    plan.valid = true;
    plan.slot = handle.slot;
    plan.generation = handle.generation;
    plan.world_epoch = handle.world_epoch;
    return WorldError::None;
}

}  // namespace stormline::world

#endif  // STORMLINE_WORLD_ENTITY_IDENTITY_PLAN_HPP
