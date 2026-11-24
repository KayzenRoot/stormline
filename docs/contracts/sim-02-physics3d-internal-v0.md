# SIM-02 internal contract v0 — logical 3D physics metadata

**Status:** `FROZEN INTERNAL API / LOGICAL METADATA ONLY / NO PHYSICS RUNTIME`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Architecture:** [sim-02-internal-physics-3d-metadata](../architecture/sim-02-internal-physics-3d-metadata.md). **Governance:** [sim-02-governance-v0](sim-02-governance-v0.md). **Planning-only policy:** [ADR-0032](../adr/0032-sim-02-engine-owned-3d-physics-and-collider-publication.md) remains `PROPOSED`.

This contract freezes the exact C++20 header-only logical API for the SIM-02 internal sequence. It creates no solver, broadphase, query execution, contact, simulation, ECS mutation, GPU or runtime behavior. Every slice below is separately gated; this document alone authorizes no code.

## Common types

Namespace `stormline::physics3d`, headers under `src/stormline/physics3d/`.

```cpp
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i32 = std::int32_t;
using f32 = float;

inline constexpr u32 kMaxBodies = 64;
inline constexpr u32 kMaxShapes = 128;
inline constexpr u32 kMaxLayers = 32;
inline constexpr u32 kMaxQueries = 32;
inline constexpr u32 kMaxConstraints = 64;
inline constexpr u32 kMaxIntegrations = 64;
inline constexpr u32 kMaxQueryResults = 1024;
inline constexpr u32 kMaxTotalQueryResults = 8192;

enum class Physics3DError : std::uint8_t {
    None, InvalidArgument, DuplicateId, NotFound, CapacityFull,
    NonFiniteValue, OutOfRange, BodyInvalid, ShapeInvalid, LayerInvalid,
    QueryInvalid, ConstraintInvalid, IntegrationInvalid, Incomplete,
    Unsupported
};

struct Physics3DDiagnostic {
    Physics3DError code{Physics3DError::None};
    u32 world_id{0};
    u32 index{0};
};
```

Shared detail helpers: `set_physics3d_error`, `finite(f32)`, kind allowlist checks, `checked_add_u32`. Unit quaternion rule: all four components finite and `|qx²+qy²+qz²+qw² − 1| <= 1e-3`. Unit axis rule: finite, nonzero, and `|x²+y²+z² − 1| <= 1e-3`.

## `SIM-02-03` (bodies)

```cpp
enum class BodyKind : std::uint8_t { Static, Kinematic, Dynamic };

struct BodyDesc {
    u32 body_id{0};
    u32 revision{0};
    BodyKind kind{BodyKind::Static};
    f32 x{0.0f};
    f32 y{0.0f};
    f32 z{0.0f};
    f32 qx{0.0f};
    f32 qy{0.0f};
    f32 qz{0.0f};
    f32 qw{1.0f};
    f32 density{0.0f};
    f32 damping{0.0f};
    bool enabled{false};
    bool bullet{false};
};

struct BodySetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 body_count{0};
    std::array<BodyDesc, kMaxBodies> bodies{};
};

struct BodyPlan {
    u32 body_count{0};
    u32 static_count{0};
    u32 kinematic_count{0};
    u32 dynamic_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] Physics3DError plan_bodies(
    const BodySetDesc& bodies, BodyPlan& plan,
    Physics3DDiagnostic& diagnostic) noexcept;
```

Semantics: world ID/revision nonzero; count `0..64`; body IDs nonzero and unique; revisions nonzero; kind allowlist; pose finite; quaternion unit rule; density `>= 0`; damping `0..1`. Plan counts kinds and enabled bodies. No integration or simulation.

## `SIM-02-04` (shapes)

```cpp
enum class ShapeKind : std::uint8_t {
    Sphere, Box, Capsule, Convex, Compound, Mesh, Heightfield
};

struct ShapeDesc {
    u32 shape_id{0};
    u32 body_id{0};
    u32 revision{0};
    ShapeKind kind{ShapeKind::Sphere};
    f32 half_x{0.0f};
    f32 half_y{0.0f};
    f32 half_z{0.0f};
    f32 radius{0.0f};
    f32 half_height{0.0f};
    f32 density{0.0f};
    u32 material_id{0};
    bool sensor{false};
};

struct ShapeSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 shape_count{0};
    std::array<ShapeDesc, kMaxShapes> shapes{};
};

struct ShapePlan {
    u32 shape_count{0};
    u32 sphere_count{0};
    u32 box_count{0};
    u32 capsule_count{0};
    u32 convex_count{0};
    u32 compound_count{0};
    u32 mesh_count{0};
    u32 heightfield_count{0};
    u32 sensor_count{0};
};

[[nodiscard]] Physics3DError plan_shapes(
    const ShapeSetDesc& shapes, ShapePlan& plan,
    Physics3DDiagnostic& diagnostic) noexcept;
```

Semantics: world ID/revision nonzero; count `0..128`; IDs/revision nonzero; kind allowlist; unique shape IDs; all dimensions finite. Sphere: radius `> 0`. Capsule: radius `> 0` and half_height `>= 0`. Box/Convex/Compound/Mesh/Heightfield: half_x/half_y/half_z `> 0`. Material ID nonzero. Density `>= 0`. No mesh import or narrowphase.

## `SIM-02-05` (broadphase layers)

```cpp
struct LayerDesc {
    u32 layer_id{0};
    u32 revision{0};
    u32 layer_bits{0};
    u32 mask_bits{0};
    u32 group_index{0};
};

struct LayerSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 layer_count{0};
    std::array<LayerDesc, kMaxLayers> layers{};
};

struct LayerPlan {
    u32 layer_count{0};
    u32 group_count{0};
    u32 compatible_pair_count{0};
};

[[nodiscard]] bool layers_compatible(
    const LayerDesc& a, const LayerDesc& b) noexcept;

[[nodiscard]] Physics3DError plan_layers(
    const LayerSetDesc& layers, LayerPlan& plan,
    Physics3DDiagnostic& diagnostic) noexcept;
```

Semantics: world ID/revision nonzero; count `0..32`; layer IDs nonzero and unique; revision nonzero; layer_bits and mask_bits nonzero. `layers_compatible` is symmetric: a nonzero group on either side requires equal nonzero groups and overrides bit tests; otherwise both layer masks must intersect the other mask. Plan reports distinct nonzero groups and compatible ordered pairs `i < j`. No AABB tree, sweep or candidate generation.

## `SIM-02-06` (queries)

```cpp
enum class QueryKind : std::uint8_t { Ray, Overlap, Sweep, ShapeCast };

struct QueryDesc {
    u32 query_id{0};
    u32 revision{0};
    QueryKind kind{QueryKind::Ray};
    f32 origin_x{0.0f};
    f32 origin_y{0.0f};
    f32 origin_z{0.0f};
    f32 direction_x{0.0f};
    f32 direction_y{0.0f};
    f32 direction_z{0.0f};
    f32 max_distance{0.0f};
    u32 layer_bits{0};
    u32 max_results{0};
};

struct QuerySetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 query_count{0};
    std::array<QueryDesc, kMaxQueries> queries{};
};

struct QueryPlan {
    u32 query_count{0};
    u32 ray_count{0};
    u32 overlap_count{0};
    u32 sweep_count{0};
    u32 shape_cast_count{0};
    u32 total_result_limit{0};
};

[[nodiscard]] Physics3DError plan_queries(
    const QuerySetDesc& queries, QueryPlan& plan,
    Physics3DDiagnostic& diagnostic) noexcept;
```

Semantics: IDs/revision nonzero; kind allowlist; layer_bits nonzero; finite origin/direction/max_distance; max_results `1..1024`; total limit `<= 8192` checked with overflow-safe addition. Ray/Sweep/ShapeCast: direction norm² `> 0` and max_distance `> 0`. Overlap: max_distance `>= 0`. No query execution.

## `SIM-02-07` (constraints)

```cpp
enum class ConstraintKind : std::uint8_t {
    Fixed, Distance, Hinge, Slider, ConeTwist, SixDof
};

struct ConstraintDesc {
    u32 constraint_id{0};
    u32 revision{0};
    ConstraintKind kind{ConstraintKind::Fixed};
    u32 body_a{0};
    u32 body_b{0};
    f32 anchor_a_x{0.0f};
    f32 anchor_a_y{0.0f};
    f32 anchor_a_z{0.0f};
    f32 anchor_b_x{0.0f};
    f32 anchor_b_y{0.0f};
    f32 anchor_b_z{0.0f};
    f32 axis_x{0.0f};
    f32 axis_y{0.0f};
    f32 axis_z{1.0f};
    f32 min_limit{0.0f};
    f32 max_limit{0.0f};
    f32 break_impulse{0.0f};
    bool motor_enabled{false};
    bool collide_connected{false};
};

struct ConstraintSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 constraint_count{0};
    std::array<ConstraintDesc, kMaxConstraints> constraints{};
};

struct ConstraintPlan {
    u32 constraint_count{0};
    u32 fixed_count{0};
    u32 distance_count{0};
    u32 hinge_count{0};
    u32 slider_count{0};
    u32 cone_twist_count{0};
    u32 six_dof_count{0};
    u32 motor_count{0};
    u32 collide_count{0};
};

[[nodiscard]] Physics3DError plan_constraints(
    const ConstraintSetDesc& constraints, ConstraintPlan& plan,
    Physics3DDiagnostic& diagnostic) noexcept;
```

Semantics: IDs/revision nonzero; kind allowlist; body references nonzero and distinct; anchors finite; min_limit `<=` max_limit; break_impulse finite and `>= 0`. Hinge/Slider/ConeTwist require a unit axis; others do not. Unique constraint IDs. Plan counts kinds plus motor/collide flags. No solver.

## `SIM-02-08` (integrations)

```cpp
enum class IntegrationKind : std::uint8_t { Scene, Streaming, Authority, Tick };

struct IntegrationDesc {
    u32 integration_id{0};
    u32 revision{0};
    IntegrationKind kind{IntegrationKind::Scene};
    u32 world_id{0};
    u32 scene_id{0};
    u32 cell_id{0};
    u32 tick_hz{0};
    u32 authority_bits{0};
};

struct IntegrationSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 integration_count{0};
    std::array<IntegrationDesc, kMaxIntegrations> integrations{};
};

struct IntegrationPlan {
    u32 integration_count{0};
    u32 scene_count{0};
    u32 streaming_count{0};
    u32 authority_count{0};
    u32 tick_count{0};
    u32 min_tick_hz{0};
    u32 max_tick_hz{0};
};

[[nodiscard]] Physics3DError plan_integrations(
    const IntegrationSetDesc& integrations, IntegrationPlan& plan,
    Physics3DDiagnostic& diagnostic) noexcept;
```

Semantics: set world ID/revision nonzero; count `0..64`; IDs/revision nonzero and unique; kind allowlist; descriptor world_id nonzero and equal to the set world ID. Scene requires scene_id nonzero. Streaming requires cell_id nonzero. Authority requires authority_bits nonzero. Tick requires tick_hz `1..240`; plan tracks min/max tick. No ECS mutation or bridge execution.

## Common rules

All functions are `noexcept`, allocation-free, exception-free and use no file, network, audio, GPU, clock, thread, random source or global state. Invalid input resets the plan to default and sets a typed diagnostic with the world ID and index. All capacities are fixed at compile time.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| BODY3-01 | bodies | unique IDs, kind allowlist, finite pose/quaternion, density/damping |
| SHAPE3-01 | shapes | kind/dimension/density validity, material refs, sensor count |
| BROAD3-01 | layers | bit ranges, groups, symmetric compatibility |
| QUERY3-01 | queries | descriptors, finite regions, bounded result limits |
| CONSTRAINT3-01 | constraints | distinct body refs, finite anchors/limits, unit axes, kinds |
| INTEGRATION3-01 | integrations | kind allowlist, world/scene/cell/authority refs, tick bounds |
| QLF-S201 | integrated | body -> shape -> layers -> query -> constraint -> integration |
| QLF-S202 | deterministic repeat | identical plans/counts |
| QLF-S203 | failure recovery | typed error followed by valid operation |
| QLF-S204 | bounded overload | 10,000 attempts keep caps |

## Implementation allowlists

No production `.cpp`. One `INTERFACE` target and one test executable per implementation packet. `physics3d_types.hpp` may be introduced only by `-03` and only the declared helpers may be added by later slices; later packets must not modify earlier production headers.

### `SIM-02-03` (bodies)

1. `src/stormline/physics3d/physics3d_types.hpp`
2. `src/stormline/physics3d/body_plan.hpp`
3. `tests/core/sim02_body_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`

### `SIM-02-04` (shapes)

1. `src/stormline/physics3d/shape_plan.hpp`
2. `tests/core/sim02_shape_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`

### `SIM-02-05` (broadphase layers)

1. `src/stormline/physics3d/layer_plan.hpp`
2. `tests/core/sim02_layer_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`

### `SIM-02-06` (queries)

1. `src/stormline/physics3d/query_plan.hpp`
2. `tests/core/sim02_query_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`

### `SIM-02-07` (constraints)

1. `src/stormline/physics3d/constraint_plan.hpp`
2. `tests/core/sim02_constraint_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`

### `SIM-02-08` (integrations)

1. `src/stormline/physics3d/integration_plan.hpp`
2. `tests/core/sim02_integration_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`

### `SIM-02-09` (qualification)

1. `tests/core/sim02_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-SIM-02-09.md`

### `SIM-02-10` (closeout)

Evidence only; no production, test, CMake or workflow file.

## Out of scope

Solver/backend (Jolt/PhysX/Bullet/Rapier), broadphase/narrowphase execution, contacts/events, query execution, simulation, fixed tick, ECS mutation, mesh/heightfield import, scene/streaming bridges, GPU, editor, audio, export, performance, ABI, release and production readiness. ADR-0032 remains `PROPOSED`.
