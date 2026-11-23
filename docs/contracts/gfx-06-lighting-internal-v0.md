# GFX-06 INTERNAL_ONLY Logical Lighting Contract v0 (NLE-PRPLAN-GFX-06-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `533d983`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **WO:** [NLE-PRPLAN-GFX-06-02](../work-orders/NLE-PRPLAN-GFX-06-02.md).

## Objective

Freeze the first bounded GFX-06 logical API: light validation, cascade/shadow-page planning, GI fallback, probe metadata, reflection fallback and volumetric budgets. No native GPU, shadow map, ray tracing, GI/probe bake, SSR, froxel buffer, shader compiler, dependency, ABI or release.

## Admission and boundaries

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- GFX-06 owns only logical lighting plans and typed fallback metadata.
- GFX-03 graph/resources; GFX-04 casters; GFX-05 BRDF/alpha; GFX-07 output; DATA-02/04/05 identity/scene/cook.
- No Vulkan/D3D12/Metal/WebGPU, shadow-map, ray-tracing, GI/probe/SSR/froxel dependency is selected.

## Policy invariants

- **No native GPU or rendering.** Metadata/planning only; no shadow map, GPU resource, shader, descriptor, fence, upload or frame.
- **Bounded and finite.** Fixed capacities; NaN/Inf, illegal negative/zero values and count overflow are rejected.
- **Fail closed.** Unknown IDs/types/units, duplicate pages/cells, invalid cascades, stale generation and budget overflow are typed errors.
- **Deterministic.** Stable IDs and declared ordering determine output.
- **Honest fallback.** Missing page/bake/capability yields coarse fallback or typed error, never silent stale or zero light.
- **No visual/performance claim.** Plans are not shadows, light, GI, reflections, fog, images or timing results.

## Internal API (logical, exact names)

```cpp
namespace stormline::graphics::lighting {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxLights = 64;
inline constexpr u32 kMaxCascades = 4;
inline constexpr u32 kMaxShadowPages = 64;
inline constexpr u32 kMaxProbes = 64;
inline constexpr u32 kMaxProbeCells = 65536;
inline constexpr u32 kMaxVolumetrics = 16;

enum class LightingError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    InvalidLightKind,
    InvalidUnit,
    InvalidCascade,
    ShadowPageMissing,
    ShadowBudgetExceeded,
    GiUnavailable,
    InvalidProbe,
    HistoryInvalid,
    ReflectionOffscreen,
    VolumetricBudgetExceeded,
    Unsupported
};

enum class LightKind : std::uint8_t {
    Directional, Point, Spot, AreaRect, Environment, Stylized2D
};
enum class LightUnit : std::uint8_t { Lux, Candela, Luminance };
enum class ShadowMode : std::uint8_t { Disabled, Cascaded, Local };
enum class GiMode : std::uint8_t { Baked, Environment, ProbeFallback, Unsupported };
enum class ReflectionMode : std::uint8_t { ScreenSpace, Probe, Environment, Unsupported };
enum class VolumetricTier : std::uint8_t { Analytic, Froxel };

struct Vec3 {
    f32 x{0.0f};
    f32 y{0.0f};
    f32 z{0.0f};
};

struct LightingDiagnostic {
    LightingError code{LightingError::None};
    u32 light_id{0};
    u32 page_id{0};
    u32 index{0};
};

struct LightDesc {
    u32 id{0};
    u32 revision{0};
    LightKind kind{LightKind::Directional};
    LightUnit unit{LightUnit::Lux};
    Vec3 color{1.0f, 1.0f, 1.0f};
    f32 intensity{0.0f};
    Vec3 position{};
    Vec3 direction{0.0f, -1.0f, 0.0f};
    f32 range{0.0f};
    f32 inner_angle{0.0f};
    f32 outer_angle{0.0f};
    f32 width{0.0f};
    f32 height{0.0f};
    u32 channel_mask{1u};
    ShadowMode shadow{ShadowMode::Disabled};
};

struct LightSet {
    u32 count{0};
    std::array<LightDesc, kMaxLights> lights{};
};

[[nodiscard]] const char* lighting_error_name(LightingError error) noexcept;
[[nodiscard]] LightingError add_light(
    LightSet& set, const LightDesc& light) noexcept;
[[nodiscard]] LightingError validate_lights(
    const LightSet& set, LightingDiagnostic& diagnostic) noexcept;

struct CascadeRequest {
    f32 near_distance{0.0f};
    f32 far_distance{0.0f};
    u32 cascade_count{0};
    f32 lambda{0.5f};
};

struct CascadeSplit {
    f32 near_distance{0.0f};
    f32 far_distance{0.0f};
    f32 blend{0.0f};
};

struct CascadePlan {
    u32 count{0};
    std::array<CascadeSplit, kMaxCascades> cascades{};
};

[[nodiscard]] LightingError build_cascade_plan(
    const CascadeRequest& request, CascadePlan& plan,
    LightingDiagnostic& diagnostic) noexcept;

struct ShadowPage {
    u32 id{0};
    u32 light_id{0};
    f32 distance{0.0f};
    bool resident{false};
};

struct ShadowPageSet {
    u32 count{0};
    std::array<ShadowPage, kMaxShadowPages> pages{};
};

struct ShadowPagePlan {
    u32 count{0};
    std::array<u32, kMaxShadowPages> page_ids{};
    u32 resident_count{0};
    u32 missing_count{0};
    bool coarse_fallback{false};
};

[[nodiscard]] LightingError plan_shadow_pages(
    const LightSet& lights, const ShadowPageSet& pages, u32 budget_pages,
    ShadowPagePlan& plan, LightingDiagnostic& diagnostic) noexcept;

struct GiRequest {
    GiMode requested{GiMode::Baked};
    bool baked_available{false};
    bool environment_available{false};
    bool probe_available{false};
};

struct GiPlan {
    GiMode mode{GiMode::Unsupported};
    bool degraded{false};
};

[[nodiscard]] LightingError plan_gi(
    const GiRequest& request, GiPlan& plan,
    LightingDiagnostic& diagnostic) noexcept;

struct ProbeVolumeDesc {
    u32 id{0};
    u32 revision{0};
    u64 scene_generation{0};
    Vec3 origin{};
    f32 spacing{0.0f};
    u32 cells_x{0};
    u32 cells_y{0};
    u32 cells_z{0};
};

struct ProbeVolumeSet {
    u32 count{0};
    std::array<ProbeVolumeDesc, kMaxProbes> probes{};
};

struct ProbePlan {
    u32 count{0};
    std::array<u32, kMaxProbes> probe_ids{};
};

[[nodiscard]] LightingError plan_probes(
    const ProbeVolumeSet& probes, u64 expected_generation,
    ProbePlan& plan, LightingDiagnostic& diagnostic) noexcept;

struct ReflectionRequest {
    ReflectionMode preferred{ReflectionMode::ScreenSpace};
    u32 roughness_band{0};
    bool environment_available{false};
    bool probe_available{false};
    bool ssr_available{false};
};

struct ReflectionPlan {
    ReflectionMode mode{ReflectionMode::Unsupported};
    ReflectionMode fallback{ReflectionMode::Unsupported};
    bool offscreen_fallback{false};
    bool degraded{false};
};

[[nodiscard]] LightingError plan_reflections(
    const ReflectionRequest& request, ReflectionPlan& plan,
    LightingDiagnostic& diagnostic) noexcept;

struct VolumetricDesc {
    u32 id{0};
    u32 revision{0};
    f32 density{0.0f};
    f32 extinction{0.0f};
    f32 scattering{0.0f};
    f32 anisotropy{0.0f};
    VolumetricTier tier{VolumetricTier::Analytic};
    u32 step_count{0};
};

struct VolumetricSet {
    u32 count{0};
    std::array<VolumetricDesc, kMaxVolumetrics> volumes{};
};

struct VolumetricPlan {
    u32 count{0};
    std::array<u32, kMaxVolumetrics> volume_ids{};
    u32 total_steps{0};
};

[[nodiscard]] LightingError plan_volumetrics(
    const VolumetricSet& volumes, u32 max_steps,
    VolumetricPlan& plan, LightingDiagnostic& diagnostic) noexcept;

}  // namespace stormline::graphics::lighting
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `GFX-06-03`.

## Semantics

- **Lights:** IDs/revisions nonzero and unique. Kind/unit must match: Directional=Lux, Point/Spot=Candela, AreaRect/Environment/Stylized2D=Luminance. Color/intensity finite and nonnegative; intensity may be zero. Position finite; direction finite with length `>1e-6`. Point/Spot/Stylized2D require `range>0`; Spot requires `0<=inner_angle<=outer_angle<=pi/2` and `outer_angle>0`; AreaRect requires `width>0` and `height>0`; Environment ignores range/size. Shadow policy is `Cascaded` only for Directional, `Local` only for Point/Spot, otherwise `Disabled`. Unknown kind/unit/shadow values fail closed. `add_light` is atomic; validation reports the first offending index.
- **Cascades:** `near_distance>0`, `far_distance>near`, `cascade_count` in `1..4`, `lambda` in `[0,1]`. For each cascade `i=1..count`, `p=i/count`, `logarithmic=near*pow(far/near,p)`, `uniform=near+(far-near)*p`, `split=lambda*logarithmic+(1-lambda)*uniform`; the first near is `near`, each next near is the previous far, final far is `far`, and `blend` is `min(0.1,(far-near)*0.1)`. Arithmetic must be finite.
- **Shadow pages:** IDs nonzero/unique; `light_id` must exist with shadow enabled; distance finite `>=0`. Resident pages are skipped. Missing pages are sorted by `(distance, id)` ascending and admitted until `budget_pages` (`<=kMaxShadowPages`); any remaining missing page sets `coarse_fallback=true`, not silent success. `resident_count` counts requested resident pages; `missing_count` counts all nonresident requested pages.
- **GI:** `Baked` falls back to `ProbeFallback`, then `Environment`, each flagged `degraded=true`; if none exists returns `GiUnavailable`. Requested `Environment`/`ProbeFallback` either succeeds or returns `GiUnavailable`. `Unsupported` returns `Unsupported`. No dynamic GI or ray tracing exists.
- **Probes:** IDs/revisions nonzero/unique; origin finite; spacing `>0`; each cell count `>0`; checked `cells_x*cells_y*cells_z <= kMaxProbeCells`; `scene_generation` must equal `expected_generation`, otherwise `HistoryInvalid`. Output IDs sorted ascending. No bake or leak evaluation.
- **Reflections:** `roughness_band <=3`; preferred mode must be declared. `ScreenSpace` falls back to `Probe`, then `Environment`; `Probe` falls back to `Environment`; unavailable requested mode without fallback returns `ReflectionOffscreen`. `offscreen_fallback` is true only when the selected mode is `ScreenSpace` and a fallback exists; `degraded` is true when the selected mode differs from preferred.
- **Volumetrics:** IDs/revisions nonzero/unique; density/extinction/scattering finite `>=0`; anisotropy in `[-1,1]`; tier declared; `step_count>0`; `max_steps>0`. Checked total steps `<=max_steps`, otherwise `VolumetricBudgetExceeded` with no partial plan. Output IDs sorted ascending.
- **Common:** all functions are `noexcept`; no allocation, exception, file, network, GPU, thread or global state. Invalid input zeroes outputs. No plan is a shadow, light, image, bake or GPU resource.

## Test oracles (future GFX-06-03..-09)

| ID | Scenario | Oracle |
|---|---|---|
| LGT-01 | lights | add/duplicate/capacity, kinds/units, finite/range, spot/area, shadow policy |
| SHD-01 | cascades/pages | split math, invalid requests, resident/missing/budget/order/fallback |
| GI-01 | GI fallback | baked/probe/environment/degraded/unavailable |
| PRB-01 | probes | IDs/revisions, spacing/cells/generation/order, capacity |
| REF-01 | reflections | SSR/probe/environment fallback, offscreen/degraded/unavailable |
| VOL-01 | volumetrics | finite/nonnegative, anisotropy/tier/steps/budget/order |
| QLF-G601 | integrated | lights->cascades->pages->GI->probes->reflections->volumetrics |
| QLF-G602 | deterministic repeat | identical plans/orders/flags |
| QLF-G603 | failure recovery | typed error followed by valid operation |
| QLF-G604 | bounded overload | 10,000 attempts keep capacities |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/graphics/lighting/`. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp`.

### `GFX-06-03` (lights)

1. `src/stormline/graphics/lighting/lighting_types.hpp`
2. `src/stormline/graphics/lighting/light.hpp`
3. `tests/core/gfx06_light_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-GFX-06-03.md`

### `GFX-06-04` (shadows)

1. `src/stormline/graphics/lighting/shadow_plan.hpp`
2. `tests/core/gfx06_shadow_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-06-04.md`

### `GFX-06-05` (GI)

1. `src/stormline/graphics/lighting/gi_plan.hpp`
2. `tests/core/gfx06_gi_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-06-05.md`

### `GFX-06-06` (probes)

1. `src/stormline/graphics/lighting/probe_plan.hpp`
2. `tests/core/gfx06_probe_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-06-06.md`

### `GFX-06-07` (reflections)

1. `src/stormline/graphics/lighting/reflection_plan.hpp`
2. `tests/core/gfx06_reflection_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-06-07.md`

### `GFX-06-08` (volumetrics)

1. `src/stormline/graphics/lighting/volumetric_plan.hpp`
2. `tests/core/gfx06_volumetric_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-06-08.md`

### `GFX-06-09` (qualification)

1. `tests/core/gfx06_lighting_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-GFX-06-09.md`

`GFX-06-10` is documentary closeout only. Qualification is internal/CI-only; no native GPU, shadow map, ray tracing, GI/probe bake, SSR, froxel, rendering, hardware, ABI or release claim.

## Stop / rollback / security

Stop on stale source, missing admission, native GPU/shadow/ray-tracing selection, submission, host I/O, public ABI/release or HIGH/CRITICAL. Revert normally; never force push.
