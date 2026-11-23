# TWO-01 INTERNAL_ONLY Canvas Contract v0 (NLE-PRPLAN-TWO-01-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `40020ae`. **ADR:** [ADR-0123](../adr/0123-two-01-internal-canvas-pipeline.md). **WO:** [NLE-PRPLAN-TWO-01-02](../work-orders/NLE-PRPLAN-TWO-01-02.md).

## Objective

Freeze the first bounded TWO-01 logical API: sprite/atlas/layer/orthographic-camera/pixel-snap validation and 2D light-request metadata. No GPU renderer, sprite draw, atlas upload, text/vector/font engine, lighting, dependency, ABI or release.

## Admission and boundaries

- Formal dependencies are `GFX-01` and `DATA-03`; neither is module-qualified.
- TWO-01 owns logical canvas plans and typed fallback metadata.
- GFX-01 device/presentation; GFX-02 shaders; GFX-03 resources/fences; GFX-05 textures/materials; GFX-06 lighting; GFX-07 output/post; DATA-02/03/04/05 assets.
- No Vulkan/D3D12/Metal/WebGPU, sprite/text/vector engine, atlas cooker, font engine, codec or hardware driver is selected.

## Policy invariants

- **No GPU or image output.** Metadata/planning only; no instance, upload, sampler, draw, composite or pixel.
- **Bounded and finite.** Fixed capacities; NaN/Inf, zero/negative dimensions, overflow and illegal references are rejected.
- **Fail closed.** Unknown layers/assets/atlases, stale revisions and invalid modes are typed errors or declared safe degradation.
- **Painter order is semantic.** Declared layer/order is never reordered for batching.
- **Deterministic.** Stable IDs, declared order and checked caps determine output.
- **No visual/performance claim.** Plans are not frames, sprites, text, 60 FPS, VRAM or DPI results.

## Internal API (logical, exact names)

```cpp
namespace stormline::graphics::canvas2d {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxLayers = 16;
inline constexpr u32 kMaxAtlasRegions = 64;
inline constexpr u32 kMaxLights = 8;

enum class CanvasError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    SpriteInvalid,
    AtlasInvalid,
    LayerOrderInvalid,
    CameraInvalid,
    SnapInvalid,
    LightBudgetExceeded,
    MaterialMismatch,
    Unsupported
};

enum class BlendMode : std::uint8_t { Opaque, Mask, Blend, Additive };
enum class FilterMode : std::uint8_t { Nearest, Linear };
enum class SnapMode : std::uint8_t { None, Integer };
enum class FalloffKind : std::uint8_t { Constant, Linear, Radial };

struct CanvasDiagnostic {
    CanvasError code{CanvasError::None};
    u32 source_id{0};
    u32 index{0};
};

struct SpriteDrawDesc {
    u32 sprite_id{0};
    u32 revision{0};
    u32 asset_id{0};
    u32 asset_revision{0};
    u32 atlas_id{0};
    u32 layer_id{0};
    u32 region_x{0};
    u32 region_y{0};
    u32 region_width{0};
    u32 region_height{0};
    f32 pivot_x{0.0f};
    f32 pivot_y{0.0f};
    bool flip_x{false};
    bool flip_y{false};
    f32 tint_r{1.0f};
    f32 tint_g{1.0f};
    f32 tint_b{1.0f};
    f32 tint_a{1.0f};
};

struct SpritePlan {
    u32 sprite_id{0};
    u32 asset_id{0};
    u32 atlas_id{0};
    u32 layer_id{0};
    bool visible{false};
};

[[nodiscard]] CanvasError plan_sprite(
    const SpriteDrawDesc& sprite, SpritePlan& plan,
    CanvasDiagnostic& diagnostic) noexcept;

struct AtlasRegion {
    u32 region_id{0};
    u32 revision{0};
    u32 x{0};
    u32 y{0};
    u32 width{0};
    u32 height{0};
};

struct AtlasDesc {
    u32 atlas_id{0};
    u32 revision{0};
    u32 width{0};
    u32 height{0};
    u32 gutter{0};
    u32 mip_count{0};
    u32 region_count{0};
    std::array<AtlasRegion, kMaxAtlasRegions> regions{};
};

struct AtlasPlan {
    u32 atlas_id{0};
    u32 region_count{0};
    u32 mip_count{0};
};

[[nodiscard]] CanvasError plan_atlas(
    const AtlasDesc& atlas, AtlasPlan& plan,
    CanvasDiagnostic& diagnostic) noexcept;

struct CanvasLayerDesc {
    u32 layer_id{0};
    u32 revision{0};
    u32 order{0};
    f32 opacity{1.0f};
    BlendMode blend{BlendMode::Blend};
    bool visible{true};
    u32 clip_depth{0};
};

struct CanvasLayerSet {
    u32 count{0};
    std::array<CanvasLayerDesc, kMaxLayers> layers{};
};

struct LayerPlan {
    u32 count{0};
    std::array<u32, kMaxLayers> order{};
};

[[nodiscard]] CanvasError plan_layers(
    const CanvasLayerSet& layers, LayerPlan& plan,
    CanvasDiagnostic& diagnostic) noexcept;

struct CanvasCameraDesc {
    u32 viewport_width{0};
    u32 viewport_height{0};
    f32 position_x{0.0f};
    f32 position_y{0.0f};
    f32 zoom{1.0f};
    f32 dpi_scale{1.0f};
    bool letterbox{false};
};

struct CameraPlan {
    f32 effective_zoom{1.0f};
    f32 dpi_scale{1.0f};
    bool letterbox{false};
};

[[nodiscard]] CanvasError plan_camera(
    const CanvasCameraDesc& camera, CameraPlan& plan,
    CanvasDiagnostic& diagnostic) noexcept;

struct CanvasSnapDesc {
    SnapMode mode{SnapMode::None};
    FilterMode filter{FilterMode::Linear};
    f32 scale_x{1.0f};
    f32 scale_y{1.0f};
    f32 offset_x{0.0f};
    f32 offset_y{0.0f};
};

struct SnapPlan {
    SnapMode mode{SnapMode::None};
    FilterMode filter{FilterMode::Linear};
    f32 snapped_offset_x{0.0f};
    f32 snapped_offset_y{0.0f};
    bool degraded{false};
};

[[nodiscard]] CanvasError plan_snap(
    const CanvasSnapDesc& snap, SnapPlan& plan,
    CanvasDiagnostic& diagnostic) noexcept;

struct CanvasLightDesc {
    u32 light_id{0};
    u32 revision{0};
    f32 intensity{1.0f};
    f32 radius{1.0f};
    f32 color_r{1.0f};
    f32 color_g{1.0f};
    f32 color_b{1.0f};
    u32 layer_id{0};
    FalloffKind falloff{FalloffKind::Radial};
};

struct CanvasLightBudget {
    u32 max_lights{0};
    f32 max_intensity{0.0f};
};

struct LightPlan {
    u32 light_id{0};
    f32 intensity{0.0f};
    f32 radius{0.0f};
    bool clamped{false};
};

[[nodiscard]] CanvasError plan_light(
    const CanvasLightDesc& light, const CanvasLightBudget& budget,
    LightPlan& plan, CanvasDiagnostic& diagnostic) noexcept;

}  // namespace stormline::graphics::canvas2d
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `TWO-01-03`.

## Semantics

- **Sprite:** IDs/revisions nonzero; region width/height positive; pivot and tint finite; tint in `[0,1]`; layer reference nonzero; plan copies stable IDs and marks visible. No UV/instance is produced.
- **Atlas:** IDs/revisions nonzero; dimensions positive; gutter nonnegative; mip count `1..16`; region count within cap; region IDs unique; `x+width<=atlas_width`, `y+height<=atlas_height` checked in 64-bit; invalid bounds `AtlasInvalid`.
- **Layers:** IDs/revisions nonzero and unique; orders unique; opacity finite in `[0,1]`; blend enum declared; clip depth `0..8`; plan returns IDs sorted by declared order, preserving painter order.
- **Camera:** viewport dimensions positive; position finite; zoom/DPI finite positive; plan computes `effective_zoom=zoom*dpi_scale`; no matrix.
- **Snap:** scales/offsets finite positive; integer mode with non-integral scale degrades to continuous equality semantics with `degraded=true`; snapped offsets rounded to nearest integer when integer mode.
- **Lights:** IDs/revisions nonzero; intensity nonnegative; radius positive; color finite in `[0,1]`; layer reference nonzero; falloff declared; budget caps positive; intensity above cap clamps with `clamped=true`.
- **Common:** all functions `noexcept`; no allocation, exception, file, network, GPU, thread or global state. Invalid input zeroes/defaults outputs and sets the diagnostic.

## Test oracles (future TWO-01-03..-09)

| ID | Scenario | Oracle |
|---|---|---|
| SPR-01 | sprites | IDs, region, pivot/tint bounds, layer ref |
| ATL-01 | atlases | dimensions/gutter/mips, region bounds, duplicates |
| LAY-01 | layers | unique IDs/orders, opacity/blend/clip, painter order |
| CAM-01 | camera | viewport/position/zoom/DPI, effective zoom |
| SNP-01 | pixel snapping | modes, scales, offsets, integer degradation |
| LGT-01 | 2D lights | finite color/intensity/radius, budget clamp |
| QLF-T101 | integrated | sprite->atlas->layers->camera->snap->light |
| QLF-T102 | deterministic repeat | identical plans/orders/flags |
| QLF-T103 | failure recovery | typed error followed by valid operation |
| QLF-T104 | bounded overload | 10,000 attempts keep caps |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/graphics/canvas2d/`. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp`.

### `TWO-01-03` (sprites)

1. `src/stormline/graphics/canvas2d/canvas_types.hpp`
2. `src/stormline/graphics/canvas2d/sprite_plan.hpp`
3. `tests/core/two01_sprite_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-TWO-01-03.md`

### `TWO-01-04` (atlases)

1. `src/stormline/graphics/canvas2d/atlas_plan.hpp`
2. `tests/core/two01_atlas_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-01-04.md`

### `TWO-01-05` (layers)

1. `src/stormline/graphics/canvas2d/layer_plan.hpp`
2. `tests/core/two01_layer_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-01-05.md`

### `TWO-01-06` (camera)

1. `src/stormline/graphics/canvas2d/camera_plan.hpp`
2. `tests/core/two01_camera_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-01-06.md`

### `TWO-01-07` (pixel snapping)

1. `src/stormline/graphics/canvas2d/snap_plan.hpp`
2. `tests/core/two01_snap_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-01-07.md`

### `TWO-01-08` (lights)

1. `src/stormline/graphics/canvas2d/light_plan.hpp`
2. `tests/core/two01_light_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-01-08.md`

### `TWO-01-09` (qualification)

1. `tests/core/two01_canvas_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-TWO-01-09.md`
