# TWO-04 internal hybrid composition contract v0

**Status:** `APPROVED CONTRACT / INTERNAL_ONLY / NO RUNTIME RENDERING`. **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Architecture:** [two-04-internal-hybrid-composition](../architecture/two-04-internal-hybrid-composition.md). **Governance:** [two-04-governance-v0](two-04-governance-v0.md).

Freeze the bounded logical API for camera intent, 2D/3D layer intent, deterministic sort intent and hybrid effect bridge intent. No renderer, matrix evaluation, GPU resource, depth attachment, shader, lighting, subview execution, importer, export, dependency, ABI or release.

## Namespace and common types

Header-only under `src/stormline/hybrid/`, namespace `stormline::hybrid`.

```cpp
using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxHybridLayers = 16;
inline constexpr u32 kMaxHybridObjects = 64;
inline constexpr u32 kMaxHybridEffects = 8;
inline constexpr u32 kMaxSubviewDepth = 4;
inline constexpr u32 kMaxSubviewExtent = 16384;

enum class HybridError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    CameraInvalid,
    LayerInvalid,
    SortInvalid,
    EffectInvalid,
    ViewInvalid,
    DepthExceeded,
    Unsupported
};

enum class ProjectionKind : std::uint8_t { Orthographic, Perspective };
enum class CompositionMode : std::uint8_t {
    SharedDepthWorld, OrderedCanvasOverlay, IsolatedSubview
};
enum class AlphaPolicy : std::uint8_t { Opaque, Masked, Blended };
enum class ObjectKind : std::uint8_t { Sprite, Mesh, Vfx, Ui };
enum class FallbackReason : std::uint8_t {
    None, Unavailable, Unsupported, BudgetExceeded, ProjectionMismatch
};

struct HybridDiagnostic {
    HybridError code{HybridError::None};
    u32 source_id{0};
    u32 index{0};
};
```

## Camera intent

```cpp
struct CameraDesc {
    u32 camera_id{0};
    u32 revision{0};
    ProjectionKind projection{ProjectionKind::Orthographic};
    f32 near_plane{0.0f};
    f32 far_plane{0.0f};
    f32 ortho_half_height{0.0f};
    f32 ortho_aspect{0.0f};
    f32 perspective_fov_degrees{0.0f};
    f32 perspective_aspect{0.0f};
};

struct CameraPlan {
    ProjectionKind projection{ProjectionKind::Orthographic};
    f32 near_plane{0.0f};
    f32 far_plane{0.0f};
    f32 primary_extent{0.0f};
    f32 aspect{0.0f};
};

[[nodiscard]] HybridError plan_camera(
    const CameraDesc& camera, CameraPlan& plan,
    HybridDiagnostic& diagnostic) noexcept;
```

Semantics: ID/revision nonzero; projection allowlisted; near/far finite, `near > 0`, `far > near`; orthographic requires finite positive half-height and aspect; perspective requires finite `0 < fov < 180` and positive aspect. `primary_extent` returns half-height for orthographic and FOV for perspective. No matrix or trigonometric evaluation.

## Layer intent

```cpp
struct HybridObjectRef {
    u32 object_id{0};
    u32 revision{0};
    ObjectKind kind{ObjectKind::Sprite};
    f32 depth_key{0.0f};
};

struct HybridLayerDesc {
    u32 layer_id{0};
    u32 revision{0};
    CompositionMode mode{CompositionMode::OrderedCanvasOverlay};
    u32 author_order{0};
    bool depth_test{false};
    bool depth_write{false};
    AlphaPolicy alpha{AlphaPolicy::Opaque};
    u32 object_count{0};
    std::array<HybridObjectRef, kMaxHybridObjects> objects{};
};

struct HybridLayerSetDesc {
    u32 scene_id{0};
    u32 revision{0};
    u32 layer_count{0};
    std::array<HybridLayerDesc, kMaxHybridLayers> layers{};
};

struct HybridLayerPlan {
    u32 layer_count{0};
    u32 object_count{0};
    u32 depth_write_count{0};
    u32 canvas_count{0};
};

[[nodiscard]] HybridError plan_layers(
    const HybridLayerSetDesc& layers, HybridLayerPlan& plan,
    HybridDiagnostic& diagnostic) noexcept;
```

Semantics: scene/layer IDs and revisions nonzero; layer count `1..16`; layer author orders unique; mode/alpha allowlisted; object count bounded; object IDs/revisions nonzero and unique across the scene; depth keys finite. `OrderedCanvasOverlay` and `IsolatedSubview` forbid depth test/write. `SharedDepthWorld` with `Blended` alpha forbids depth write. Depth write requires depth test. Outputs total objects, depth-writing layers and ordered-canvas layers.

## Sort intent

```cpp
struct HybridSortObject {
    u32 object_id{0};
    u32 revision{0};
    u32 layer_order{0};
    f32 depth_key{0.0f};
    u32 tie_breaker{0};
};

struct HybridSortDesc {
    u32 scene_id{0};
    u32 revision{0};
    u32 object_count{0};
    std::array<HybridSortObject, kMaxHybridObjects> objects{};
};

struct HybridSortPlan {
    u32 object_count{0};
    std::array<u32, kMaxHybridObjects> order{};
};

[[nodiscard]] HybridError plan_sort(
    const HybridSortDesc& sort, HybridSortPlan& plan,
    HybridDiagnostic& diagnostic) noexcept;
```

Semantics: scene ID/revision nonzero; object count `1..64`; IDs/revisions nonzero and unique; depth keys finite. Ordering is ascending `layer_order`, then ascending `depth_key`, then ascending `tie_breaker`, then original index. `plan.order` contains object IDs in that deterministic order. No GPU sort or draw list is produced.

## Hybrid effect bridge intent

```cpp
struct HybridEffectDesc {
    u32 effect_id{0};
    u32 revision{0};
    u32 layer_id{0};
    bool lit{false};
    bool shadow_proxy{false};
    u32 subview_width{0};
    u32 subview_height{0};
    u32 subview_depth{0};
    FallbackReason fallback{FallbackReason::None};
};

struct HybridEffectSetDesc {
    u32 scene_id{0};
    u32 revision{0};
    u32 effect_count{0};
    std::array<HybridEffectDesc, kMaxHybridEffects> effects{};
};

struct HybridEffectPlan {
    u32 effect_count{0};
    u32 lit_count{0};
    u32 shadow_count{0};
    u32 subview_count{0};
    u32 max_subview_depth{0};
};

[[nodiscard]] HybridError plan_effects(
    const HybridEffectSetDesc& effects, HybridEffectPlan& plan,
    HybridDiagnostic& diagnostic) noexcept;
```

Semantics: scene/effect/layer IDs and revisions nonzero; effect count `0..8`; effect IDs unique; fallback reason allowlisted. Subview width/height are both zero or both `1..16384`; subview depth `0..4`. A nonzero depth requires a declared subview extent. Outputs lit, shadow and subview counts plus maximum depth.

## Common rules

All functions are `noexcept`, allocation-free, exception-free and use no file, network, audio, GPU, clock, thread or global state. Invalid input resets the plan to default and sets a typed diagnostic with source ID and index.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| CAM-01 | camera intent | projection kind, finite positive parameters, near < far, bounds |
| LAY-01 | layers | unique IDs/orders, explicit mode, depth/alpha policy validity |
| SRT-01 | sorting | deterministic stable order, ties, capacity, unique IDs |
| EFE-01 | effect bridges | lit/shadow intent, subview bounds/recursion, fallback enum |
| QLF-T401 | integrated | camera -> layer -> sort -> effect |
| QLF-T402 | deterministic repeat | identical plans/order |
| QLF-T403 | failure recovery | typed error followed by valid operation |
| QLF-T404 | bounded overload | 10,000 attempts keep caps |

## Implementation allowlists

No production `.cpp`. One `INTERFACE` target and one test executable per implementation packet.

### `TWO-04-03` (camera)

1. `src/stormline/hybrid/hybrid_types.hpp`
2. `src/stormline/hybrid/camera_plan.hpp`
3. `tests/core/two04_camera_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-TWO-04-03.md`

### `TWO-04-04` (layers)

1. `src/stormline/hybrid/layer_plan.hpp`
2. `tests/core/two04_layer_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-04-04.md`

### `TWO-04-05` (sorting)

1. `src/stormline/hybrid/sort_plan.hpp`
2. `tests/core/two04_sort_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-04-05.md`

### `TWO-04-06` (effects)

1. `src/stormline/hybrid/effect_plan.hpp`
2. `tests/core/two04_effect_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-04-06.md`

### `TWO-04-07` (qualification)

1. `tests/core/two04_hybrid_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-TWO-04-07.md`
