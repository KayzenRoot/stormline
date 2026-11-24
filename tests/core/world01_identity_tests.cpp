#include "stormline/world/entity_identity_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::world;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

WorldIdentityDesc world() {
    WorldIdentityDesc desc{};
    desc.world_epoch = 7;
    desc.slot_count = 4;
    desc.slots[0] = EntitySlotDesc{1, true, false};
    desc.slots[1] = EntitySlotDesc{0, false, false};
    desc.slots[2] = EntitySlotDesc{3, true, false};
    desc.slots[3] = EntitySlotDesc{2, false, true};
    return desc;
}

EntityHandleDesc handle(u32 slot, u32 generation) {
    EntityHandleDesc desc{};
    desc.slot = slot;
    desc.generation = generation;
    desc.world_epoch = 7;
    return desc;
}

bool run_ent01() {
    begin();
    WorldIdentityDesc identity = world();
    WorldIdentityPlan plan{};
    WorldDiagnostic diagnostic{};

    expect(plan_world_identity(identity, plan, diagnostic) == WorldError::None,
           "valid world");
    expect(plan.slot_count == 4 && plan.occupied_count == 2
               && plan.retired_count == 1,
           "valid identity plan");
    WorldIdentityPlan repeat{};
    expect(plan_world_identity(identity, repeat, diagnostic) == WorldError::None,
           "repeat world");
    expect(plan.occupied_count == repeat.occupied_count
               && plan.retired_count == repeat.retired_count,
           "deterministic identity");

    identity.world_epoch = 0;
    expect(plan_world_identity(identity, plan, diagnostic)
               == WorldError::InvalidArgument,
           "zero epoch");
    expect(plan.slot_count == 0 && plan.occupied_count == 0,
           "reset on zero epoch");
    identity = world();
    identity.slot_count = 0;
    expect(plan_world_identity(identity, plan, diagnostic)
               == WorldError::EntityInvalid,
           "zero slots");
    identity.slot_count = kMaxWorldEntities + 1;
    expect(plan_world_identity(identity, plan, diagnostic)
               == WorldError::EntityInvalid,
           "slot overflow");

    identity = world();
    identity.slots[0].retired = true;
    expect(plan_world_identity(identity, plan, diagnostic)
               == WorldError::EntityInvalid,
           "occupied and retired");
    identity = world();
    identity.slots[0].generation = 0;
    expect(plan_world_identity(identity, plan, diagnostic)
               == WorldError::EntityInvalid,
           "occupied zero generation");

    identity = world();
    EntityHandlePlan handle_plan{};
    expect(plan_entity_handle(handle(0, 1), identity, handle_plan, diagnostic)
               == WorldError::None,
           "valid handle");
    expect(handle_plan.valid && handle_plan.slot == 0
               && handle_plan.generation == 1
               && handle_plan.world_epoch == 7,
           "valid handle plan");
    expect(plan_entity_handle(handle(0, 2), identity, handle_plan, diagnostic)
               == WorldError::EntityInvalid,
           "stale generation");
    expect(!handle_plan.valid && handle_plan.slot == 0,
           "reset on stale");
    expect(plan_entity_handle(handle(1, 1), identity, handle_plan, diagnostic)
               == WorldError::EntityInvalid,
           "free slot");
    expect(plan_entity_handle(handle(3, 2), identity, handle_plan, diagnostic)
               == WorldError::EntityInvalid,
           "retired slot");
    expect(plan_entity_handle(handle(4, 1), identity, handle_plan, diagnostic)
               == WorldError::EntityInvalid,
           "slot out of range");
    expect(plan_entity_handle(handle(0, 0), identity, handle_plan, diagnostic)
               == WorldError::EntityInvalid,
           "zero generation");
    EntityHandleDesc wrong_epoch = handle(0, 1);
    wrong_epoch.world_epoch = 8;
    expect(plan_entity_handle(wrong_epoch, identity, handle_plan, diagnostic)
               == WorldError::EntityInvalid,
           "epoch mismatch");
    wrong_epoch.world_epoch = 0;
    expect(plan_entity_handle(wrong_epoch, identity, handle_plan, diagnostic)
               == WorldError::EntityInvalid,
           "zero handle epoch");

    WorldIdentityDesc broken = world();
    broken.world_epoch = 0;
    expect(plan_entity_handle(handle(0, 1), broken, handle_plan, diagnostic)
               == WorldError::EntityInvalid,
           "invalid world for handle");
    broken = world();
    broken.slot_count = kMaxWorldEntities + 1;
    expect(plan_entity_handle(handle(0, 1), broken, handle_plan, diagnostic)
               == WorldError::EntityInvalid,
           "oversized world for handle");

    identity = world();
    identity.slot_count = kMaxWorldEntities;
    for (u32 index = 0; index < kMaxWorldEntities; ++index) {
        identity.slots[index] = EntitySlotDesc{index + 1, true, false};
    }
    expect(plan_world_identity(identity, plan, diagnostic) == WorldError::None,
           "capacity identity");
    expect(plan.occupied_count == kMaxWorldEntities, "capacity count");
    expect(plan_entity_handle(handle(kMaxWorldEntities - 1,
                                     kMaxWorldEntities),
                              identity, handle_plan, diagnostic)
               == WorldError::None,
           "capacity handle");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world01_identity_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "ent01") { success = run_ent01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
