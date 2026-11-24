# WORLD-01 internal entity metadata contract v0

**Status:** `APPROVED CONTRACT / INTERNAL_ONLY / NO ECS RUNTIME`. **ADR:** [ADR-0127](../adr/0127-world-01-internal-entity-metadata.md). **Architecture:** [world-01-internal-entity-metadata](../architecture/world-01-internal-entity-metadata.md). **Governance:** [world-01-governance-v0](world-01-governance-v0.md).

Freeze the bounded logical API for world/entity identity, component schema intent, lifecycle intent, query intent and reflection intent. No ECS storage, allocator, threading, serialization, persistence, hierarchy, spatial index, physics, networking, editor, GPU, performance, ABI or release.

## Namespace and common types

Header-only under `src/stormline/world/`, namespace `stormline::world`.

```cpp
using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxWorldEntities = 64;
inline constexpr u32 kMaxComponentTypes = 32;
inline constexpr u32 kMaxComponentFields = 16;
inline constexpr u32 kMaxQueryTypes = 8;
inline constexpr u32 kMaxQueryResults = 64;

enum class WorldError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    EntityInvalid,
    ComponentInvalid,
    LifecycleInvalid,
    QueryInvalid,
    ReflectionInvalid,
    Unsupported
};

enum class EntityState : std::uint8_t {
    Alive, DestroyRequested, Tombstoned, Retired
};

enum class FieldKind : std::uint8_t {
    Bool, U32, I32, F32, StringId, EntityRef
};

struct WorldDiagnostic {
    WorldError code{WorldError::None};
    u32 source_id{0};
    u32 index{0};
};
```

## Entity identity intent

```cpp
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

[[nodiscard]] WorldError plan_world_identity(
    const WorldIdentityDesc& world, WorldIdentityPlan& plan,
    WorldDiagnostic& diagnostic) noexcept;

[[nodiscard]] WorldError plan_entity_handle(
    const EntityHandleDesc& handle, const WorldIdentityDesc& world,
    EntityHandlePlan& plan, WorldDiagnostic& diagnostic) noexcept;
```

Semantics: world epoch nonzero; slot count `1..64`; occupied slots have generation `>0`; retired slots are not occupied; occupied and retired are mutually exclusive. `plan_entity_handle` validates epoch match, slot in range, nonzero generation, and generation equality with the occupied slot. Invalid or stale handles fail with `EntityInvalid`. No pointer or serialization of runtime handles.

## Component schema intent

```cpp
struct ComponentFieldDesc {
    u32 field_id{0};
    FieldKind kind{FieldKind::U32};
    f32 range_min{0.0f};
    f32 range_max{0.0f};
};

struct ComponentSchemaDesc {
    u32 type_id{0};
    u32 version{0};
    u32 field_count{0};
    std::array<ComponentFieldDesc, kMaxComponentFields> fields{};
};

struct ComponentRegistryDesc {
    u32 world_epoch{0};
    u32 type_count{0};
    std::array<ComponentSchemaDesc, kMaxComponentTypes> types{};
};

struct ComponentRegistryPlan {
    u32 type_count{0};
    u32 field_count{0};
};

[[nodiscard]] WorldError plan_component_registry(
    const ComponentRegistryDesc& registry, ComponentRegistryPlan& plan,
    WorldDiagnostic& diagnostic) noexcept;
```

Semantics: world epoch nonzero; type count `1..32`; type IDs/versions nonzero and unique; field count `1..16`; field IDs nonzero and unique within a type; field kinds allowlisted; range values finite with `range_min <= range_max`. No memory layout, alignment, construction or RTTI identity is represented.

## Lifecycle intent

```cpp
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

[[nodiscard]] WorldError plan_lifecycle(
    const LifecycleBatchDesc& batch, LifecyclePlan& plan,
    WorldDiagnostic& diagnostic) noexcept;
```

Semantics: world epoch nonzero; slot count `1..64`; transition count `1..64`; each slot is below slot count and generation is nonzero; states allowlisted. Allowed transitions: `Alive -> DestroyRequested`, `DestroyRequested -> Tombstoned`, `Tombstoned -> Retired`, plus same-state idempotent transitions. Other transitions fail with `LifecycleInvalid`. Duplicate slots in one batch fail. No storage mutation occurs.

## Query intent

```cpp
struct EntityQueryDesc {
    u32 query_id{0};
    u32 revision{0};
    u32 world_epoch{0};
    u32 required_count{0};
    u32 excluded_count{0};
    std::array<u32, kMaxQueryTypes> required_types{};
    std::array<u32, kMaxQueryTypes> excluded_types{};
};

struct EntityQueryPlan {
    u32 required_count{0};
    u32 excluded_count{0};
};

[[nodiscard]] WorldError plan_entity_query(
    const EntityQueryDesc& query, EntityQueryPlan& plan,
    WorldDiagnostic& diagnostic) noexcept;
```

Semantics: query ID/revision/world epoch nonzero; required count `1..8`; excluded count `0..8`; type IDs nonzero; each set unique; no type ID appears in both sets. No storage access or result iteration occurs.

## Reflection intent

```cpp
struct ReflectionFieldDesc {
    u32 field_id{0};
    u32 name_id{0};
    FieldKind kind{FieldKind::U32};
    f32 range_min{0.0f};
    f32 range_max{0.0f};
    bool editable{false};
    bool serialized{false};
};

struct ReflectionTypeDesc {
    u32 type_id{0};
    u32 version{0};
    u32 field_count{0};
    std::array<ReflectionFieldDesc, kMaxComponentFields> fields{};
};

struct ReflectionSetDesc {
    u32 world_epoch{0};
    u32 type_count{0};
    std::array<ReflectionTypeDesc, kMaxComponentTypes> types{};
};

struct ReflectionPlan {
    u32 type_count{0};
    u32 field_count{0};
    u32 editable_count{0};
    u32 serialized_count{0};
};

[[nodiscard]] WorldError plan_reflection(
    const ReflectionSetDesc& reflection, ReflectionPlan& plan,
    WorldDiagnostic& diagnostic) noexcept;
```

Semantics: world epoch nonzero; type count `1..32`; type IDs/versions nonzero and unique; field count `1..16`; field and name IDs nonzero and unique within a type; kinds allowlisted; ranges finite with `range_min <= range_max`. Reflection is metadata only: no addresses, callbacks, type names, dynamic code or serialization codec.

## Common rules

All functions are `noexcept`, allocation-free, exception-free and use no file, network, audio, GPU, clock, thread, RTTI hash or global state. Invalid input resets the plan to default and sets a typed diagnostic with source ID and index.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| ENT-01 | entity identity/handles | epoch/slot/generation validity, stale rejection, retirement |
| CMP-01 | component schemas | unique IDs, versions, field bounds, capacity |
| LIF-01 | lifecycle | allowed transitions, idempotence, duplicates |
| QRY-01 | queries | required/excluded sets, uniqueness, overlap rejection |
| REF-01 | reflection | field/name identity, kinds, bounds, counts |
| QLF-W101 | integrated | identity -> schema -> lifecycle -> query -> reflection |
| QLF-W102 | deterministic repeat | identical plans/counts |
| QLF-W103 | failure recovery | typed error followed by valid operation |
| QLF-W104 | bounded overload | 10,000 attempts keep caps |

## Implementation allowlists

No production `.cpp`. One `INTERFACE` target and one test executable per implementation packet.

### `WORLD-01-03` (identity)

1. `src/stormline/world/world_types.hpp`
2. `src/stormline/world/entity_identity_plan.hpp`
3. `tests/core/world01_identity_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-WORLD-01-03.md`

### `WORLD-01-04` (components)

1. `src/stormline/world/component_schema_plan.hpp`
2. `tests/core/world01_component_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-01-04.md`

### `WORLD-01-05` (lifecycle)

1. `src/stormline/world/lifecycle_plan.hpp`
2. `tests/core/world01_lifecycle_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-01-05.md`

### `WORLD-01-06` (queries)

1. `src/stormline/world/query_plan.hpp`
2. `tests/core/world01_query_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-01-06.md`

### `WORLD-01-07` (reflection)

1. `src/stormline/world/reflection_plan.hpp`
2. `tests/core/world01_reflection_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-01-07.md`

### `WORLD-01-08` (qualification)

1. `tests/core/world01_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-WORLD-01-08.md`
