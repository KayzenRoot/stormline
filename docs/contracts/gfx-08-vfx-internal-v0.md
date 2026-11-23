# GFX-08 INTERNAL_ONLY VFX Contract v0 (NLE-PRPLAN-GFX-08-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `65d3f7b`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **WO:** [NLE-PRPLAN-GFX-08-02](../work-orders/NLE-PRPLAN-GFX-08-02.md).

## Objective

Freeze the first bounded GFX-08 logical API: acyclic VFX graph validation, emitter/spawn budgets, ribbon and trail geometry budgets, transparency/blend policy, volumetric density-stamp metadata and pool/quality budgets. No CPU/GPU simulation, compute, sorting, OIT, volumetric rendering, shader, SDK, dependency, ABI or release.

## Admission and boundaries

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- GFX-08 owns logical VFX graph and effect plans with typed failure metadata.
- GFX-01 device capability; GFX-02 shaders; GFX-03 graph/resources/fences; GFX-04 visibility/depth; GFX-05 materials/alpha; GFX-06 lighting/volumetrics; GFX-07 HDR/post; DATA-02/03/04/05 asset identity/import/authoring/cook.
- No Vulkan/D3D12/Metal/WebGPU, compute backend, particle SDK, volume codec, GPU sorting library, OIT runtime or frame-generation dependency is selected.

## Policy invariants

- **No simulation or image output.** Metadata/planning only; no particle state, PRNG stream, compute dispatch, sort, OIT, volume sample, draw or pixel.
- **Bounded and finite.** Fixed capacities; NaN/Inf, zero dimensions/lifetimes, overflow, cycles and illegal references are rejected.
- **Fail closed.** Unknown node kinds/ports, stale graph revisions/generations, invalid blends and exhausted pools are typed errors or declared safe degradation.
- **Deterministic.** Stable IDs, declared order and checked caps determine output.
- **Cosmetic only.** VFX never becomes gameplay-authoritative for damage, collision, hit validation or network state.
- **Ownership preserved.** GFX-06 owns lighting/scattering; GFX-05 materials; GFX-03 resources; DATA owns durable assets.

## Internal API (logical, exact names)

```cpp
namespace stormline::graphics::vfx {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxGraphNodes = 16;
inline constexpr u32 kMaxGraphEdges = 32;
inline constexpr u32 kMaxEmitters = 8;
inline constexpr u32 kMaxRibbonSamples = 16;
inline constexpr u32 kMaxTrailSamples = 16;

enum class VfxError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    GraphCycle,
    GraphTooComplex,
    PortTypeMismatch,
    SpawnBudgetExceeded,
    GeometryInvalid,
    MaterialMismatch,
    DensityInvalid,
    PoolExhausted,
    StaleGeneration,
    BudgetExceeded,
    Unsupported
};

enum class VfxNodeKind : std::uint8_t {
    Emitter, Init, Force, Update, Event, Render, Output
};
enum class VfxPortType : std::uint8_t {
    Flow, Scalar, Vector, Color, Material, Geometry
};
enum class SimulationPolicy : std::uint8_t {
    CpuReference, CpuRender, GpuCompute
};
enum class BlendMode : std::uint8_t {
    Opaque, Mask, Blend, Additive
};
enum class DepthPolicy : std::uint8_t {
    TestAndWrite, TestOnly, Disabled
};

struct VfxDiagnostic {
    VfxError code{VfxError::None};
    u32 source_id{0};
    u32 node_id{0};
    u32 index{0};
};

struct VfxGraphNode {
    u32 node_id{0};
    u32 revision{0};
    VfxNodeKind kind{VfxNodeKind::Emitter};
    VfxPortType input_type{VfxPortType::Flow};
    VfxPortType output_type{VfxPortType::Flow};
};

struct VfxGraphEdge {
    u32 source_node{0};
    u32 target_node{0};
    VfxPortType port_type{VfxPortType::Flow};
};

struct VfxGraphDesc {
    u32 graph_id{0};
    u32 revision{0};
    u32 node_count{0};
    std::array<VfxGraphNode, kMaxGraphNodes> nodes{};
    u32 edge_count{0};
    std::array<VfxGraphEdge, kMaxGraphEdges> edges{};
};

struct VfxGraphPlan {
    u32 node_count{0};
    u32 edge_count{0};
    std::array<u32, kMaxGraphNodes> order{};
    bool acyclic{false};
};

[[nodiscard]] VfxError validate_graph(
    const VfxGraphDesc& graph, VfxGraphPlan& plan,
    VfxDiagnostic& diagnostic) noexcept;

struct VfxEmitterDesc {
    u32 emitter_id{0};
    u32 revision{0};
    u32 graph_id{0};
    u32 graph_revision{0};
    u32 spawn_per_tick{0};
    u32 burst_count{0};
    f32 lifetime_seconds{0.0f};
    u64 seed{0};
    SimulationPolicy policy{SimulationPolicy::CpuReference};
};

struct VfxSpawnBudget {
    u32 max_spawn_per_tick{0};
    u32 max_alive{0};
};

struct VfxEmitterPlan {
    u32 spawn_per_tick{0};
    u32 alive_capacity{0};
    SimulationPolicy policy{SimulationPolicy::CpuReference};
};

[[nodiscard]] VfxError plan_emitter(
    const VfxEmitterDesc& emitter, const VfxSpawnBudget& budget,
    VfxEmitterPlan& plan, VfxDiagnostic& diagnostic) noexcept;

struct VfxRibbonDesc {
    u32 source_id{0};
    u32 revision{0};
    u32 sample_count{0};
    f32 width{0.0f};
    f32 min_sample_distance{0.0f};
    u32 max_segments{0};
    u32 max_vertices{0};
};

struct VfxRibbonPlan {
    u32 segments{0};
    u32 vertices{0};
};

[[nodiscard]] VfxError plan_ribbon(
    const VfxRibbonDesc& ribbon, VfxRibbonPlan& plan,
    VfxDiagnostic& diagnostic) noexcept;

struct VfxTrailSample {
    f32 age_seconds{0.0f};
    f32 width{0.0f};
};

struct VfxTrailDesc {
    u32 source_id{0};
    u32 revision{0};
    u32 sample_count{0};
    std::array<VfxTrailSample, kMaxTrailSamples> samples{};
    u32 max_segments{0};
    u32 max_vertices{0};
    f32 max_age_seconds{0.0f};
};

struct VfxTrailPlan {
    u32 segments{0};
    u32 vertices{0};
    f32 lifetime_seconds{0.0f};
};

[[nodiscard]] VfxError plan_trail(
    const VfxTrailDesc& trail, VfxTrailPlan& plan,
    VfxDiagnostic& diagnostic) noexcept;

struct VfxBlendDesc {
    u32 material_id{0};
    u32 material_revision{0};
    BlendMode blend{BlendMode::Opaque};
    DepthPolicy depth{DepthPolicy::TestAndWrite};
    bool premultiplied_alpha{false};
    bool sort_required{false};
    bool oit_approximation_allowed{false};
};

struct VfxBlendPlan {
    BlendMode blend{BlendMode::Opaque};
    DepthPolicy depth{DepthPolicy::TestAndWrite};
    bool needs_sort{false};
    bool oit_approx{false};
};

[[nodiscard]] VfxError plan_blend(
    const VfxBlendDesc& description, VfxBlendPlan& plan,
    VfxDiagnostic& diagnostic) noexcept;

struct VfxDensityStampDesc {
    u32 stamp_id{0};
    u32 revision{0};
    f32 density{0.0f};
    f32 extinction{0.0f};
    f32 extent_x{0.0f};
    f32 extent_y{0.0f};
    f32 extent_z{0.0f};
    f32 lifetime_seconds{0.0f};
    f32 max_density{0.0f};
};

struct VfxDensityPlan {
    f32 density{0.0f};
    f32 extinction{0.0f};
    bool clamped{false};
};

[[nodiscard]] VfxError plan_density_stamp(
    const VfxDensityStampDesc& stamp, VfxDensityPlan& plan,
    VfxDiagnostic& diagnostic) noexcept;

struct VfxQualityBudget {
    u32 max_particles{0};
    u32 max_ribbons{0};
    u32 max_trails{0};
    u32 max_light_requests{0};
};

struct VfxPoolDesc {
    u32 pool_id{0};
    u32 capacity{0};
    u32 generation{0};
    u32 expected_generation{0};
    u32 particles{0};
    u32 ribbons{0};
    u32 trails{0};
    u32 light_requests{0};
};

struct VfxPoolPlan {
    u32 admitted_particles{0};
    u32 admitted_ribbons{0};
    u32 admitted_trails{0};
    u32 admitted_lights{0};
    u32 available{0};
    bool degraded{false};
};

[[nodiscard]] VfxError plan_pool(
    const VfxPoolDesc& pool, const VfxQualityBudget& budget,
    VfxPoolPlan& plan, VfxDiagnostic& diagnostic) noexcept;

}  // namespace stormline::graphics::vfx
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `GFX-08-03`.

## Semantics

- **Graph:** IDs/revisions nonzero; node/edge counts within fixed caps; node IDs unique; allowlisted kinds and ports; edge endpoints exist; no self/duplicate edges; edge type must match source output and target input; cycles reject with `GraphCycle`; topological order returned.
- **Emitter/spawn:** IDs/revisions nonzero; lifetime finite `>0`; policy declared; budget caps `>0`; checked `spawn_per_tick+burst_count`; overflow `OutOfRange`; over per-tick or alive cap `SpawnBudgetExceeded`.
- **Ribbon:** source/revision nonzero; `2<=sample_count<=16`; finite positive width/distance; segments `sample_count-1`, vertices `2*sample_count`; over declared caps `BudgetExceeded`; invalid input `GeometryInvalid`.
- **Trail:** source/revision nonzero; `2<=sample_count<=16`; ages finite nonnegative and strictly increasing; widths finite positive; last age `<=max_age_seconds`; over caps `BudgetExceeded`; invalid order/duplicates `GeometryInvalid`.
- **Blend:** material ID/revision nonzero; enums declared; Opaque/Mask require depth write; Blend/Additive require no depth write; premultiplied alpha only for Blend/Additive; sort only meaningful for Blend; OIT only for Blend; invalid combinations `MaterialMismatch` or `Unsupported`.
- **Density stamp:** IDs nonzero; density/extinction finite nonnegative; extents/lifetime/max density finite positive; density above cap clamps to cap with `clamped=true`; malformed values `DensityInvalid` or `NonFiniteValue`.
- **Pool/quality:** pool ID/capacity nonzero; generation must equal expected; budget caps positive; checked total requested; over pool capacity `PoolExhausted`; per-domain requests clamp to budget caps with `degraded=true` and exact admitted counts.
- **Common:** all functions `noexcept`; no allocation, exception, file, network, GPU, thread or global state. Invalid input zeroes/defaults outputs and sets the diagnostic.

## Test oracles (future GFX-08-03..-09)

| ID | Scenario | Oracle |
|---|---|---|
| VFX-01 | graph | IDs/counts/kinds/ports, duplicate/self edges, cycle, topological order |
| SPAWN-01 | emitter | IDs, lifetime, spawn+burst overflow, per-tick/alive caps |
| RIB-01 | ribbon | sample range, width/distance, segment/vertex caps |
| TRL-01 | trail | ordered ages, widths, max age, segment/vertex caps |
| BLD-01 | blend | opaque/mask/blend/additive depth and sort/OIT policy |
| DEN-01 | density | finite values, extents, lifetime, density clamp |
| POOL-01 | pool | generation mismatch, capacity, per-domain quality clamps |
| QLF-G801 | integrated | graph->emitter->ribbon->trail->blend->density->pool |
| QLF-G802 | deterministic repeat | identical plans/flags/counts |
| QLF-G803 | failure recovery | typed error followed by valid operation |
| QLF-G804 | bounded overload | 10,000 attempts keep caps |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/graphics/vfx/`. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp`.

### `GFX-08-03` (particle graph/emitter)

1. `src/stormline/graphics/vfx/vfx_types.hpp`
2. `src/stormline/graphics/vfx/graph_plan.hpp`
3. `src/stormline/graphics/vfx/emitter_plan.hpp`
4. `tests/core/gfx08_particle_tests.cpp`
5. `CMakeLists.txt`
6. `.github/workflows/core01-internal-headless.yml`
7. `docs/evidence/NLE-PRPLAN-GFX-08-03.md`

### `GFX-08-04` (ribbons)

1. `src/stormline/graphics/vfx/ribbon_plan.hpp`
2. `tests/core/gfx08_ribbon_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-08-04.md`

### `GFX-08-05` (trails)

1. `src/stormline/graphics/vfx/trail_plan.hpp`
2. `tests/core/gfx08_trail_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-08-05.md`

### `GFX-08-06` (transparency)

1. `src/stormline/graphics/vfx/blend_plan.hpp`
2. `tests/core/gfx08_blend_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-08-06.md`

### `GFX-08-07` (volumetrics)

1. `src/stormline/graphics/vfx/density_plan.hpp`
2. `tests/core/gfx08_density_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-08-07.md`

### `GFX-08-08` (pooling)

1. `src/stormline/graphics/vfx/pool_plan.hpp`
2. `tests/core/gfx08_pool_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-08-08.md`

### `GFX-08-09` (qualification)

1. `tests/core/gfx08_vfx_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-GFX-08-09.md`
