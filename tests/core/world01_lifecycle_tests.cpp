#include "stormline/world/lifecycle_plan.hpp"

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

LifecycleTransitionDesc transition(
    u32 slot, u32 generation, EntityState from, EntityState to) {
    LifecycleTransitionDesc desc{};
    desc.slot = slot;
    desc.generation = generation;
    desc.from = from;
    desc.to = to;
    return desc;
}

LifecycleBatchDesc batch() {
    LifecycleBatchDesc desc{};
    desc.world_epoch = 11;
    desc.slot_count = 4;
    desc.transition_count = 4;
    desc.transitions[0] = transition(
        0, 1, EntityState::Alive, EntityState::DestroyRequested);
    desc.transitions[1] = transition(
        1, 2, EntityState::DestroyRequested, EntityState::Tombstoned);
    desc.transitions[2] = transition(
        2, 3, EntityState::Tombstoned, EntityState::Retired);
    desc.transitions[3] = transition(
        3, 4, EntityState::Alive, EntityState::Alive);
    return desc;
}

bool run_lif01() {
    begin();
    LifecycleBatchDesc transitions = batch();
    LifecyclePlan plan{};
    WorldDiagnostic diagnostic{};

    expect(plan_lifecycle(transitions, plan, diagnostic) == WorldError::None,
           "valid lifecycle");
    expect(plan.transition_count == 4 && plan.retire_count == 1
               && plan.idempotent_count == 1,
           "valid plan");
    LifecyclePlan repeat{};
    expect(plan_lifecycle(transitions, repeat, diagnostic) == WorldError::None,
           "repeat lifecycle");
    expect(plan.transition_count == repeat.transition_count
               && plan.retire_count == repeat.retire_count
               && plan.idempotent_count == repeat.idempotent_count,
           "deterministic plan");

    transitions.world_epoch = 0;
    expect(plan_lifecycle(transitions, plan, diagnostic)
               == WorldError::InvalidArgument,
           "zero epoch");
    expect(plan.transition_count == 0 && plan.retire_count == 0,
           "reset on zero epoch");
    transitions = batch();
    transitions.slot_count = 0;
    expect(plan_lifecycle(transitions, plan, diagnostic)
               == WorldError::LifecycleInvalid,
           "zero slots");
    transitions.slot_count = kMaxWorldEntities + 1;
    expect(plan_lifecycle(transitions, plan, diagnostic)
               == WorldError::LifecycleInvalid,
           "slot overflow");
    transitions = batch();
    transitions.transition_count = 0;
    expect(plan_lifecycle(transitions, plan, diagnostic)
               == WorldError::LifecycleInvalid,
           "zero transitions");
    transitions.transition_count = kMaxWorldEntities + 1;
    expect(plan_lifecycle(transitions, plan, diagnostic)
               == WorldError::LifecycleInvalid,
           "transition overflow");

    transitions = batch();
    transitions.transitions[0].slot = 4;
    expect(plan_lifecycle(transitions, plan, diagnostic)
               == WorldError::LifecycleInvalid,
           "slot out of range");
    transitions = batch();
    transitions.transitions[0].generation = 0;
    expect(plan_lifecycle(transitions, plan, diagnostic)
               == WorldError::LifecycleInvalid,
           "zero generation");
    transitions = batch();
    transitions.transitions[0].from = static_cast<EntityState>(200);
    expect(plan_lifecycle(transitions, plan, diagnostic)
               == WorldError::LifecycleInvalid,
           "invalid from state");
    transitions = batch();
    transitions.transitions[0].to = static_cast<EntityState>(200);
    expect(plan_lifecycle(transitions, plan, diagnostic)
               == WorldError::LifecycleInvalid,
           "invalid to state");
    transitions = batch();
    transitions.transitions[1].slot = 0;
    expect(plan_lifecycle(transitions, plan, diagnostic)
               == WorldError::DuplicateId,
           "duplicate slot");

    transitions = batch();
    transitions.transitions[0] = transition(
        0, 1, EntityState::Alive, EntityState::Tombstoned);
    expect(plan_lifecycle(transitions, plan, diagnostic)
               == WorldError::LifecycleInvalid,
           "alive to tombstoned");
    transitions = batch();
    transitions.transitions[0] = transition(
        0, 1, EntityState::Retired, EntityState::Alive);
    expect(plan_lifecycle(transitions, plan, diagnostic)
               == WorldError::LifecycleInvalid,
           "retired to alive");
    transitions = batch();
    transitions.transitions[0] = transition(
        0, 1, EntityState::DestroyRequested, EntityState::Retired);
    expect(plan_lifecycle(transitions, plan, diagnostic)
               == WorldError::LifecycleInvalid,
           "destroy requested to retired");
    transitions = batch();
    transitions.transitions[0] = transition(
        0, 1, EntityState::Retired, EntityState::Retired);
    expect(plan_lifecycle(transitions, plan, diagnostic) == WorldError::None,
           "retired idempotent");

    transitions = batch();
    transitions.slot_count = kMaxWorldEntities;
    transitions.transition_count = kMaxWorldEntities;
    for (u32 index = 0; index < kMaxWorldEntities; ++index) {
        transitions.transitions[index] = transition(
            index, index + 1, EntityState::Alive, EntityState::Alive);
    }
    expect(plan_lifecycle(transitions, plan, diagnostic) == WorldError::None,
           "capacity lifecycle");
    expect(plan.transition_count == kMaxWorldEntities
               && plan.idempotent_count == kMaxWorldEntities
               && plan.retire_count == 0,
           "capacity counts");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world01_lifecycle_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "lif01") { success = run_lif01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
