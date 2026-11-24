#include "stormline/world/component_schema_plan.hpp"
#include "stormline/world/entity_identity_plan.hpp"
#include "stormline/world/lifecycle_plan.hpp"
#include "stormline/world/query_plan.hpp"
#include "stormline/world/reflection_plan.hpp"

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

WorldIdentityDesc make_world() {
    WorldIdentityDesc desc{};
    desc.world_epoch = 7;
    desc.slot_count = 4;
    desc.slots[0] = EntitySlotDesc{1, true, false};
    desc.slots[1] = EntitySlotDesc{2, true, false};
    desc.slots[2] = EntitySlotDesc{0, false, false};
    desc.slots[3] = EntitySlotDesc{3, false, true};
    return desc;
}

ComponentRegistryDesc make_components() {
    ComponentRegistryDesc desc{};
    desc.world_epoch = 7;
    desc.type_count = 2;
    desc.types[0].type_id = 1;
    desc.types[0].version = 1;
    desc.types[0].field_count = 1;
    desc.types[0].fields[0] = ComponentFieldDesc{1, FieldKind::U32, 0.0f, 100.0f};
    desc.types[1].type_id = 2;
    desc.types[1].version = 1;
    desc.types[1].field_count = 1;
    desc.types[1].fields[0]
        = ComponentFieldDesc{1, FieldKind::EntityRef, 0.0f, 0.0f};
    return desc;
}

LifecycleBatchDesc make_lifecycle() {
    LifecycleBatchDesc desc{};
    desc.world_epoch = 7;
    desc.slot_count = 4;
    desc.transition_count = 3;
    desc.transitions[0] = LifecycleTransitionDesc{
        0, 1, EntityState::Alive, EntityState::DestroyRequested};
    desc.transitions[1] = LifecycleTransitionDesc{
        1, 2, EntityState::DestroyRequested, EntityState::Tombstoned};
    desc.transitions[2] = LifecycleTransitionDesc{
        2, 3, EntityState::Tombstoned, EntityState::Retired};
    return desc;
}

EntityQueryDesc make_query() {
    EntityQueryDesc desc{};
    desc.query_id = 1;
    desc.revision = 1;
    desc.world_epoch = 7;
    desc.required_count = 2;
    desc.required_types[0] = 1;
    desc.required_types[1] = 2;
    desc.excluded_count = 1;
    desc.excluded_types[0] = 3;
    return desc;
}

ReflectionSetDesc make_reflection() {
    ReflectionSetDesc desc{};
    desc.world_epoch = 7;
    desc.type_count = 2;
    desc.types[0].type_id = 1;
    desc.types[0].version = 1;
    desc.types[0].field_count = 1;
    desc.types[0].fields[0] = ReflectionFieldDesc{
        1, 100, FieldKind::U32, 0.0f, 100.0f, true, true};
    desc.types[1].type_id = 2;
    desc.types[1].version = 1;
    desc.types[1].field_count = 1;
    desc.types[1].fields[0] = ReflectionFieldDesc{
        1, 200, FieldKind::EntityRef, 0.0f, 0.0f, false, true};
    return desc;
}

struct IntegratedPlans {
    WorldIdentityPlan identity{};
    ComponentRegistryPlan components{};
    LifecyclePlan lifecycle{};
    EntityQueryPlan query{};
    ReflectionPlan reflection{};
    WorldDiagnostic diagnostic{};
};

bool plan_all(const WorldIdentityDesc& world,
              const ComponentRegistryDesc& components,
              const LifecycleBatchDesc& lifecycle,
              const EntityQueryDesc& query,
              const ReflectionSetDesc& reflection,
              IntegratedPlans& plans) {
    return plan_world_identity(world, plans.identity, plans.diagnostic)
               == WorldError::None
        && plan_component_registry(components, plans.components,
                                   plans.diagnostic)
               == WorldError::None
        && plan_lifecycle(lifecycle, plans.lifecycle, plans.diagnostic)
               == WorldError::None
        && plan_entity_query(query, plans.query, plans.diagnostic)
               == WorldError::None
        && plan_reflection(reflection, plans.reflection, plans.diagnostic)
               == WorldError::None;
}

bool run_qlfw101() {
    begin();
    const WorldIdentityDesc world = make_world();
    const ComponentRegistryDesc components = make_components();
    const LifecycleBatchDesc lifecycle = make_lifecycle();
    const EntityQueryDesc query = make_query();
    const ReflectionSetDesc reflection = make_reflection();
    IntegratedPlans plans{};

    expect(plan_all(world, components, lifecycle, query, reflection, plans),
           "integrated plans");
    expect(plans.identity.slot_count == 4
               && plans.identity.occupied_count == 2
               && plans.identity.retired_count == 1,
           "integrated identity");
    expect(plans.components.type_count == 2
               && plans.components.field_count == 2,
           "integrated components");
    expect(plans.lifecycle.transition_count == 3
               && plans.lifecycle.retire_count == 1,
           "integrated lifecycle");
    expect(plans.query.required_count == 2 && plans.query.excluded_count == 1,
           "integrated query");
    expect(plans.reflection.type_count == 2
               && plans.reflection.field_count == 2
               && plans.reflection.editable_count == 1
               && plans.reflection.serialized_count == 2,
           "integrated reflection");
    expect(plans.diagnostic.code == WorldError::None,
           "integrated diagnostic");
    return finish();
}

bool run_qlfw102() {
    begin();
    const WorldIdentityDesc world = make_world();
    const ComponentRegistryDesc components = make_components();
    const LifecycleBatchDesc lifecycle = make_lifecycle();
    const EntityQueryDesc query = make_query();
    const ReflectionSetDesc reflection = make_reflection();
    IntegratedPlans first{};
    IntegratedPlans second{};

    expect(plan_all(world, components, lifecycle, query, reflection, first),
           "first integrated");
    expect(plan_all(world, components, lifecycle, query, reflection, second),
           "second integrated");
    expect(first.identity.slot_count == second.identity.slot_count
               && first.identity.occupied_count
                   == second.identity.occupied_count,
           "repeat identity");
    expect(first.components.type_count == second.components.type_count
               && first.components.field_count
                   == second.components.field_count,
           "repeat components");
    expect(first.lifecycle.transition_count
               == second.lifecycle.transition_count
               && first.lifecycle.retire_count
                   == second.lifecycle.retire_count,
           "repeat lifecycle");
    expect(first.query.required_count == second.query.required_count
               && first.query.excluded_count == second.query.excluded_count,
           "repeat query");
    expect(first.reflection.editable_count
               == second.reflection.editable_count
               && first.reflection.serialized_count
                   == second.reflection.serialized_count,
           "repeat reflection");
    return finish();
}

bool run_qlfw103() {
    begin();
    WorldIdentityDesc world = make_world();
    ComponentRegistryDesc components = make_components();
    LifecycleBatchDesc lifecycle = make_lifecycle();
    EntityQueryDesc query = make_query();
    ReflectionSetDesc reflection = make_reflection();
    IntegratedPlans plans{};
    EntityHandlePlan handle_plan{};

    world.world_epoch = 0;
    expect(plan_world_identity(world, plans.identity, plans.diagnostic)
               == WorldError::InvalidArgument,
           "identity failure");
    world = make_world();
    expect(plan_world_identity(world, plans.identity, plans.diagnostic)
               == WorldError::None,
           "identity recovery");
    expect(plan_entity_handle(EntityHandleDesc{0, 1, 7}, world, handle_plan,
                              plans.diagnostic)
               == WorldError::None,
           "handle recovery");

    components.types[0].type_id = 0;
    expect(plan_component_registry(components, plans.components,
                                   plans.diagnostic)
               == WorldError::ComponentInvalid,
           "component failure");
    components = make_components();
    expect(plan_component_registry(components, plans.components,
                                   plans.diagnostic)
               == WorldError::None,
           "component recovery");

    lifecycle.transitions[0].to = EntityState::Tombstoned;
    expect(plan_lifecycle(lifecycle, plans.lifecycle, plans.diagnostic)
               == WorldError::LifecycleInvalid,
           "lifecycle failure");
    lifecycle = make_lifecycle();
    expect(plan_lifecycle(lifecycle, plans.lifecycle, plans.diagnostic)
               == WorldError::None,
           "lifecycle recovery");

    query.excluded_types[0] = 1;
    expect(plan_entity_query(query, plans.query, plans.diagnostic)
               == WorldError::DuplicateId,
           "query failure");
    query = make_query();
    expect(plan_entity_query(query, plans.query, plans.diagnostic)
               == WorldError::None,
           "query recovery");

    reflection.types[0].fields[0].name_id = 0;
    expect(plan_reflection(reflection, plans.reflection, plans.diagnostic)
               == WorldError::ReflectionInvalid,
           "reflection failure");
    reflection = make_reflection();
    expect(plan_reflection(reflection, plans.reflection, plans.diagnostic)
               == WorldError::None,
           "reflection recovery");
    return finish();
}

bool run_qlfw104() {
    begin();
    constexpr u32 kAttempts = 10000;
    for (u32 attempt = 0; attempt < kAttempts; ++attempt) {
        WorldIdentityDesc world = make_world();
        ComponentRegistryDesc components = make_components();
        LifecycleBatchDesc lifecycle = make_lifecycle();
        EntityQueryDesc query = make_query();
        ReflectionSetDesc reflection = make_reflection();
        IntegratedPlans plans{};
        if (attempt % 97 == 0) {
            world.world_epoch = 0;
            expect(plan_world_identity(world, plans.identity, plans.diagnostic)
                       == WorldError::InvalidArgument,
                   "overload identity failure");
            expect(plans.identity.slot_count == 0,
                   "overload identity reset");
            world = make_world();
        }
        if (attempt % 89 == 0) {
            components.types[1].type_id = 1;
            expect(plan_component_registry(components, plans.components,
                                           plans.diagnostic)
                       == WorldError::DuplicateId,
                   "overload component failure");
            components = make_components();
        }
        if (attempt % 83 == 0) {
            lifecycle.transitions[0].from = EntityState::Retired;
            expect(plan_lifecycle(lifecycle, plans.lifecycle, plans.diagnostic)
                       == WorldError::LifecycleInvalid,
                   "overload lifecycle failure");
            lifecycle = make_lifecycle();
        }
        if (attempt % 79 == 0) {
            query.required_count = 0;
            expect(plan_entity_query(query, plans.query, plans.diagnostic)
                       == WorldError::QueryInvalid,
                   "overload query failure");
            query = make_query();
        }
        if (attempt % 73 == 0) {
            reflection.types[0].fields[0].range_min = 2.0f;
            reflection.types[0].fields[0].range_max = 1.0f;
            expect(plan_reflection(reflection, plans.reflection,
                                   plans.diagnostic)
                       == WorldError::OutOfRange,
                   "overload reflection failure");
            reflection = make_reflection();
        }
        expect(plan_all(world, components, lifecycle, query, reflection, plans),
               "overload plans");
        expect(plans.identity.slot_count <= kMaxWorldEntities,
               "identity cap");
        expect(plans.identity.occupied_count <= kMaxWorldEntities,
               "occupied cap");
        expect(plans.components.type_count <= kMaxComponentTypes,
               "component cap");
        expect(plans.lifecycle.transition_count <= kMaxWorldEntities,
               "lifecycle cap");
        expect(plans.query.required_count <= kMaxQueryTypes
                   && plans.query.excluded_count <= kMaxQueryTypes,
               "query cap");
        expect(plans.reflection.type_count <= kMaxComponentTypes
                   && plans.reflection.field_count
                       <= kMaxComponentTypes * kMaxComponentFields,
               "reflection cap");
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world01_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlfw101") { success = run_qlfw101(); }
    else if (mode == "qlfw102") { success = run_qlfw102(); }
    else if (mode == "qlfw103") { success = run_qlfw103(); }
    else if (mode == "qlfw104") { success = run_qlfw104(); }
    else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
