# WORLD-02 internal scene/prefab metadata contract v0

**Status:** `APPROVED CONTRACT / INTERNAL_ONLY / NO SCENE RUNTIME`. **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Architecture:** [world-02-internal-scene-prefab-metadata](../architecture/world-02-internal-scene-prefab-metadata.md). **Governance:** [world-02-governance-v0](world-02-governance-v0.md).

Freeze the bounded logical API for scene hierarchy, prefab composition, variants/overrides, instancing and transform intent. No runtime scene graph, prefab expansion, override merge, serializer, persistence, journal, transform math, spatial index, physics, networking, editor, GPU, performance, ABI or release.

## Namespace and common types

Header-only under `src/stormline/scene/`, namespace `stormline::scene`.

```cpp
using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxSceneNodes = 64;
inline constexpr u32 kMaxSceneDepth = 16;
inline constexpr u32 kMaxPrefabRefs = 16;
inline constexpr u32 kMaxPrefabDepth = 4;
inline constexpr u32 kMaxVariantOverrides = 32;
inline constexpr u32 kMaxSceneInstances = 16;
inline constexpr u32 kMaxInstanceExpansion = 4096;

enum class SceneError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    HierarchyInvalid,
    PrefabInvalid,
    VariantInvalid,
    InstanceInvalid,
    TransformInvalid,
    DepthExceeded,
    Unsupported
};

enum class ReparentMode : std::uint8_t { KeepLocal, KeepWorld };

struct SceneDiagnostic {
    SceneError code{SceneError::None};
    u32 source_id{0};
    u32 index{0};
};
```

## Scene hierarchy intent

```cpp
struct SceneNodeDesc {
    u32 node_id{0};
    u32 revision{0};
    u32 parent_id{0};
    u32 sibling_order{0};
};

struct SceneHierarchyDesc {
    u32 scene_id{0};
    u32 revision{0};
    u32 node_count{0};
    std::array<SceneNodeDesc, kMaxSceneNodes> nodes{};
};

struct SceneHierarchyPlan {
    u32 node_count{0};
    u32 root_count{0};
    u32 max_depth{0};
};

[[nodiscard]] SceneError plan_scene_hierarchy(
    const SceneHierarchyDesc& hierarchy, SceneHierarchyPlan& plan,
    SceneDiagnostic& diagnostic) noexcept;
```

Semantics: scene ID/revision nonzero; node count `1..64`; node IDs/revisions nonzero and unique; parent is `0` (root) or an existing node; self-parent and cycles fail; depth `<=16`; `(parent_id, sibling_order)` pairs are unique. `max_depth` treats a root as depth one. Display names/paths are not identity.

## Prefab composition intent

```cpp
struct PrefabRefDesc {
    u32 prefab_id{0};
    u32 revision{0};
};

struct PrefabSourceDesc {
    u32 prefab_id{0};
    u32 revision{0};
    u32 depth{0};
    u32 nested_count{0};
    std::array<PrefabRefDesc, kMaxPrefabRefs> nested{};
};

struct PrefabCompositionPlan {
    u32 nested_count{0};
    u32 depth{0};
};

[[nodiscard]] SceneError plan_prefab_composition(
    const PrefabSourceDesc& prefab, PrefabCompositionPlan& plan,
    SceneDiagnostic& diagnostic) noexcept;
```

Semantics: prefab ID/revision nonzero; depth `0..4`; nested count `0..16`; nested prefab IDs/revisions nonzero and unique; self-reference fails. No nested graph beyond this descriptor is traversed.

## Prefab variant/override intent

```cpp
struct VariantOverrideDesc {
    u32 node_id{0};
    u32 component_type_id{0};
    u32 field_id{0};
    bool base_changed{false};
    bool variant_changed{false};
};

struct PrefabVariantDesc {
    u32 variant_id{0};
    u32 revision{0};
    u32 base_prefab_id{0};
    u32 base_revision{0};
    u32 override_count{0};
    std::array<VariantOverrideDesc, kMaxVariantOverrides> overrides{};
};

struct PrefabVariantPlan {
    u32 override_count{0};
};

[[nodiscard]] SceneError plan_prefab_variant(
    const PrefabVariantDesc& variant, PrefabVariantPlan& plan,
    SceneDiagnostic& diagnostic) noexcept;
```

Semantics: variant/base IDs and revisions nonzero; override count `1..32`; node/type/field IDs nonzero; `{node,type,field}` keys unique; `base_changed && variant_changed` fails with `VariantInvalid`. No merge, rebase or persistence occurs.

## Instance intent

```cpp
struct PrefabInstanceDesc {
    u32 instance_id{0};
    u32 revision{0};
    u32 prefab_id{0};
    u32 prefab_revision{0};
    u32 expansion_count{0};
    u32 expansion_depth{0};
};

struct PrefabInstanceSetDesc {
    u32 scene_id{0};
    u32 revision{0};
    u32 instance_count{0};
    std::array<PrefabInstanceDesc, kMaxSceneInstances> instances{};
};

struct PrefabInstancePlan {
    u32 instance_count{0};
    u32 total_expansion{0};
    u32 max_depth{0};
};

[[nodiscard]] SceneError plan_prefab_instances(
    const PrefabInstanceSetDesc& instances, PrefabInstancePlan& plan,
    SceneDiagnostic& diagnostic) noexcept;
```

Semantics: scene ID/revision nonzero; instance count `0..16`; instance/prefab IDs and revisions nonzero; instance IDs unique; expansion count `1..4096`; depth `0..4`; total expansion accumulated in checked `u32`. No entity is created or expanded.

## Transform/reparent intent

```cpp
struct SceneTransformDesc {
    u32 node_id{0};
    u32 revision{0};
    f32 x{0.0f};
    f32 y{0.0f};
    f32 z{0.0f};
    f32 rotation_x{0.0f};
    f32 rotation_y{0.0f};
    f32 rotation_z{0.0f};
    f32 scale_x{1.0f};
    f32 scale_y{1.0f};
    f32 scale_z{1.0f};
    ReparentMode mode{ReparentMode::KeepLocal};
};

struct SceneTransformSetDesc {
    u32 scene_id{0};
    u32 revision{0};
    u32 node_count{0};
    std::array<SceneTransformDesc, kMaxSceneNodes> nodes{};
};

struct SceneTransformPlan {
    u32 node_count{0};
    u32 keep_local_count{0};
    u32 keep_world_count{0};
};

[[nodiscard]] SceneError plan_scene_transforms(
    const SceneTransformSetDesc& transforms, SceneTransformPlan& plan,
    SceneDiagnostic& diagnostic) noexcept;
```

Semantics: scene ID/revision nonzero; node count `1..64`; node IDs/revisions nonzero and unique; all nine transform components finite; scale components nonzero; reparent mode allowlisted. No matrix multiplication, inverse, world transform or physics authority is produced.

## Common rules

All functions are `noexcept`, allocation-free, exception-free and use no file, network, audio, GPU, clock, thread, RTTI hash or global state. Invalid input resets the plan to default and sets a typed diagnostic with source ID and index.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| HIR-01 | hierarchy | unique nodes, parent/root, cycle/depth, sibling order |
| PFC-01 | composition | prefab depth, nested IDs, self-reference, capacity |
| VAR-01 | variants | base identity, override keys, conflicts, capacity |
| INS-01 | instancing | instance identity, expansion bounds, depth, totals |
| TRS-01 | transforms | finite TRS, nonzero scale, reparent mode, capacity |
| QLF-S201 | integrated | hierarchy -> composition -> variant -> instance -> transform |
| QLF-S202 | deterministic repeat | identical plans/counts |
| QLF-S203 | failure recovery | typed error followed by valid operation |
| QLF-S204 | bounded overload | 10,000 attempts keep caps |

## Implementation allowlists

No production `.cpp`. One `INTERFACE` target and one test executable per implementation packet.

### `WORLD-02-03` (hierarchy)

1. `src/stormline/scene/scene_types.hpp`
2. `src/stormline/scene/hierarchy_plan.hpp`
3. `tests/core/world02_hierarchy_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-WORLD-02-03.md`

### `WORLD-02-04` (composition)

1. `src/stormline/scene/prefab_composition_plan.hpp`
2. `tests/core/world02_composition_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-02-04.md`

### `WORLD-02-05` (variants)

1. `src/stormline/scene/prefab_variant_plan.hpp`
2. `tests/core/world02_variant_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-02-05.md`

### `WORLD-02-06` (instancing)

1. `src/stormline/scene/instance_plan.hpp`
2. `tests/core/world02_instance_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-02-06.md`

### `WORLD-02-07` (transforms)

1. `src/stormline/scene/transform_plan.hpp`
2. `tests/core/world02_transform_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-02-07.md`

### `WORLD-02-08` (qualification)

1. `tests/core/world02_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-WORLD-02-08.md`
