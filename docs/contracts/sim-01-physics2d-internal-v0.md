# SIM-01 internal 2D physics metadata contract v0

**Status:** `APPROVED CONTRACT / INTERNAL_ONLY / NO PHYSICS RUNTIME`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Architecture:** [sim-01-internal-physics-2d-metadata](../architecture/sim-01-internal-physics-2d-metadata.md). **Governance:** [sim-01-governance-v0](sim-01-governance-v0.md).

Freeze the bounded logical API for body descriptors, collision-shape descriptors, query intents, joint descriptors, trigger/sensor metadata and collision masks. No solver/backend, simulation, broadphase/narrowphase, query execution, contact/event dispatch, ECS mutation, tilemap bridge, GPU, performance, ABI or release.

## Namespace and common types

Header-only under `src/stormline/physics2d/`, namespace `stormline::physics2d`.

```cpp
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i32 = std::int32_t;
using f32 = float;

inline constexpr u32 kMaxBodies = 64;
inline constexpr u32 kMaxShapes = 128;
inline constexpr u32 kMaxQueries = 32;
inline constexpr u32 kMaxJoints = 64;
inline constexpr u32 kMaxTriggers = 64;
inline constexpr u32 kMaxMasks = 32;
inline constexpr u32 kMaxQueryResults = 1024;
inline constexpr u32 kMaxTotalQueryResults = 8192;

enum class Physics2DError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    BodyInvalid,
    ShapeInvalid,
    QueryInvalid,
    JointInvalid,
    TriggerInvalid,
    MaskInvalid,
    Incomplete,
    Unsupported
};

enum class BodyKind : std::uint8_t { Static, Kinematic, Dynamic };
enum class ShapeKind : std::uint8_t { Circle, Box, Capsule, Polygon };
enum class QueryKind : std::uint8_t { Ray, Overlap, ShapeCast };
enum class JointKind : std::uint8_t { Distance, Revolute, Prismatic, Weld };

struct Physics2DDiagnostic {
    Physics2DError code{Physics2DError::None};
    u32 world_id{0};
    u32 index{0};
};
```

## Body metadata

```cpp
struct BodyDesc {
    u32 body_id{0};
    u32 revision{0};
    BodyKind kind{BodyKind::Static};
    f32 x{0.0f};
    f32 y{0.0f};
    f32 angle{0.0f};
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

[[nodiscard]] Physics2DError plan_bodies(
    const BodySetDesc& bodies, BodyPlan& plan,
    Physics2DDiagnostic& diagnostic) noexcept;
```

Semantics: world ID/revision nonzero; body count `0..64`; body IDs nonzero and unique; revisions nonzero; kind allowlisted; pose/angle finite; density finite `>= 0`; damping finite in `[0, 1]`. The plan reports counts by kind and enabled count. No body is created.

## Collision shape metadata

```cpp
struct ShapeDesc {
    u32 shape_id{0};
    u32 body_id{0};
    u32 revision{0};
    ShapeKind kind{ShapeKind::Circle};
    f32 half_x{0.0f};
    f32 half_y{0.0f};
    f32 radius{0.0f};
    f32 density{0.0f};
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
    u32 circle_count{0};
    u32 box_count{0};
    u32 capsule_count{0};
    u32 polygon_count{0};
    u32 sensor_count{0};
};

[[nodiscard]] Physics2DError plan_shapes(
    const ShapeSetDesc& shapes, ShapePlan& plan,
    Physics2DDiagnostic& diagnostic) noexcept;
```

Semantics: world ID/revision nonzero; shape count `0..128`; shape IDs nonzero and unique; body references nonzero; revisions nonzero; kind allowlisted; all dimension fields finite and non-negative; circle/capsule require `radius > 0`; box/polygon require `half_x > 0` and `half_y > 0`; density finite `>= 0`. Plan reports counts by kind and sensor count. No shape or contact is created.

## Query intent metadata

```cpp
struct QueryDesc {
    u32 query_id{0};
    u32 revision{0};
    QueryKind kind{QueryKind::Ray};
    f32 origin_x{0.0f};
    f32 origin_y{0.0f};
    f32 direction_x{0.0f};
    f32 direction_y{0.0f};
    f32 max_distance{0.0f};
    u32 mask_bits{0};
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
    u32 shape_cast_count{0};
    u32 total_result_limit{0};
};

[[nodiscard]] Physics2DError plan_queries(
    const QuerySetDesc& queries, QueryPlan& plan,
    Physics2DDiagnostic& diagnostic) noexcept;
```

Semantics: world ID/revision nonzero; query count `0..32`; query IDs nonzero and unique; revisions nonzero; kind allowlisted; origins and directions finite; `mask_bits` nonzero; `max_results` is `1..1024`; checked total result limit `<= 8192`; ray and shape-cast require finite `max_distance > 0`, overlap allows `max_distance == 0`. No query is executed.

## Joint metadata

```cpp
struct JointDesc {
    u32 joint_id{0};
    u32 revision{0};
    JointKind kind{JointKind::Distance};
    u32 body_a{0};
    u32 body_b{0};
    f32 anchor_a_x{0.0f};
    f32 anchor_a_y{0.0f};
    f32 anchor_b_x{0.0f};
    f32 anchor_b_y{0.0f};
    f32 min_limit{0.0f};
    f32 max_limit{0.0f};
    bool collide_connected{false};
};

struct JointSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 joint_count{0};
    std::array<JointDesc, kMaxJoints> joints{};
};

struct JointPlan {
    u32 joint_count{0};
    u32 distance_count{0};
    u32 revolute_count{0};
    u32 prismatic_count{0};
    u32 weld_count{0};
    u32 collide_count{0};
};

[[nodiscard]] Physics2DError plan_joints(
    const JointSetDesc& joints, JointPlan& plan,
    Physics2DDiagnostic& diagnostic) noexcept;
```

Semantics: world ID/revision nonzero; joint count `0..64`; joint IDs nonzero and unique; revisions nonzero; kind allowlisted; both body references nonzero and distinct; anchors and limits finite; `min_limit <= max_limit`. Plan reports counts by kind and `collide_connected` count. No constraint is solved.

## Trigger/sensor metadata

```cpp
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

[[nodiscard]] Physics2DError plan_triggers(
    const TriggerSetDesc& triggers, TriggerPlan& plan,
    Physics2DDiagnostic& diagnostic) noexcept;
```

Semantics: world ID/revision nonzero; trigger count `0..64`; trigger IDs nonzero and unique; revisions nonzero; body and shape references nonzero; `mask_bits` nonzero; at least one of enter/exit enabled. Plan reports enter/exit/both counts. No event is dispatched.

## Collision mask metadata

```cpp
struct MaskDesc {
    u32 mask_id{0};
    u32 revision{0};
    u32 category_bits{0};
    u32 collision_bits{0};
    u32 group_index{0};
};

struct MaskSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 mask_count{0};
    std::array<MaskDesc, kMaxMasks> masks{};
};

struct MaskPlan {
    u32 mask_count{0};
    u32 group_count{0};
    u32 symmetric_pair_count{0};
};

[[nodiscard]] bool masks_compatible(
    const MaskDesc& a, const MaskDesc& b) noexcept;

[[nodiscard]] Physics2DError plan_masks(
    const MaskSetDesc& masks, MaskPlan& plan,
    Physics2DDiagnostic& diagnostic) noexcept;
```

Semantics: world ID/revision nonzero; mask count `0..32`; mask IDs nonzero and unique; revisions nonzero; category and collision bits nonzero. `masks_compatible` is symmetric: both category bits must match the other collision bits; a nonzero `group_index` must match on both sides and overrides the bit test. Plan reports distinct nonzero group count and the number of compatible ordered pairs `i < j`. No contact is generated.

## Common rules

All functions are `noexcept`, allocation-free, exception-free and use no file, network, audio, GPU, clock, thread, random source or global state. Invalid input resets the plan to default and sets a typed diagnostic with the world ID and index. All capacities are fixed at compile time.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| BODY-01 | bodies | unique IDs, kind allowlist, finite pose/density/damping |
| COL-01 | shapes | kind/dimension/density validity, sensor count |
| QRY-01 | queries | descriptors, finite regions, bounded result limits |
| JNT-01 | joints | distinct body refs, finite anchors/limits, kinds |
| TRG-01 | triggers | refs, mask, event enablement, counts |
| MSK-01 | masks | bit ranges, groups, symmetric compatibility |
| QLF-S101 | integrated | body -> shape -> query -> joint -> trigger -> mask |
| QLF-S102 | deterministic repeat | identical plans/counts |
| QLF-S103 | failure recovery | typed error followed by valid operation |
| QLF-S104 | bounded overload | 10,000 attempts keep caps |

## Implementation allowlists

No production `.cpp`. One `INTERFACE` target and one test executable per implementation packet.

### `SIM-01-03` (bodies)

1. `src/stormline/physics2d/physics2d_types.hpp`
2. `src/stormline/physics2d/body_plan.hpp`
3. `tests/core/sim01_body_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-SIM-01-03.md`

### `SIM-01-04` (collision shapes)

1. `src/stormline/physics2d/shape_plan.hpp`
2. `tests/core/sim01_shape_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-SIM-01-04.md`

### `SIM-01-05` (queries)

1. `src/stormline/physics2d/query_plan.hpp`
2. `tests/core/sim01_query_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-SIM-01-05.md`

### `SIM-01-06` (joints)

1. `src/stormline/physics2d/joint_plan.hpp`
2. `tests/core/sim01_joint_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-SIM-01-06.md`

### `SIM-01-07` (triggers)

1. `src/stormline/physics2d/trigger_plan.hpp`
2. `tests/core/sim01_trigger_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-SIM-01-07.md`

### `SIM-01-08` (masks)

1. `src/stormline/physics2d/mask_plan.hpp`
2. `tests/core/sim01_mask_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-SIM-01-08.md`

### `SIM-01-09` (qualification)

1. `tests/core/sim01_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-SIM-01-09.md`
