# GFX-04 INTERNAL_ONLY Logical Geometry Pipeline Contract v0 (NLE-PRPLAN-GFX-04-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `35d6b31`. **ADR:** [ADR-0118](../adr/0118-gfx-04-internal-geometry-pipeline.md). **WO:** [NLE-PRPLAN-GFX-04-02](../work-orders/NLE-PRPLAN-GFX-04-02.md).

## Objective

Freeze the first bounded GFX-04 logical API: instance validation/batching, conservative frustum/distance culling, LOD/HLOD selection, verified-chunk stream request planning, vegetation classification and geometry budget validation. No native GPU, mesh shader, indirect draw, mesh codec, streaming service, dependency, ABI or release.

## Admission and boundaries

- Formal dependencies are `GFX-03` and `DATA-05`; neither is module-qualified.
- GFX-04 owns logical geometry visibility/detail planning.
- GFX-03 render graph; DATA-05 verified chunks; DATA-02 identities; GFX-01 RHI; CORE-05 coordinates; GFX-05 materials.
- No Vulkan/D3D12/Metal/WebGPU, meshoptimizer, mesh codec or stream service is selected.

## Policy invariants

- **No native GPU or mesh library.** Metadata/planning only; no submission, decode, simplification or rendering.
- **Conservative visibility.** Unknown bounds are visible; culling requires a full sphere/plane or distance exclusion.
- **Bounded.** Fixed instance/mesh/LOD/chunk/batch/plane capacities and checked arithmetic.
- **Fail closed.** Duplicate/unknown IDs, invalid bounds/camera, generation mismatch, cycles, invalid LOD chains and unverified chunks are typed errors.
- **Verified chunks only.** Stream planning accepts verified metadata; no file/network access.
- **Authored identity preserved.** Derived IDs are metadata.
- **No execution evidence.** A plan is not a draw, stream, render or hardware result.

## Internal API (logical, exact names)

```cpp
namespace stormline::graphics::geometry {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxInstances = 128;
inline constexpr u32 kMaxMeshes = 64;
inline constexpr u32 kMaxLodLevels = 8;
inline constexpr u32 kMaxChunks = 64;
inline constexpr u32 kMaxBatches = 32;
inline constexpr u32 kMaxPlanes = 6;
inline constexpr u32 kMaxStreamRequests = 64;
inline constexpr u32 kMaxNameBytes = 32;

enum class GeometryError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    InvalidBounds,
    UnknownBounds,
    InvalidCamera,
    GenerationMismatch,
    HierarchyCycle,
    InvalidLodChain,
    UnverifiedChunk,
    StreamBudgetExceeded,
    GeometryBudgetExceeded
};

enum class VegetationKind : std::uint8_t { None, Grass, Bush, Tree };
enum class VegetationRenderClass : std::uint8_t { Mesh, Billboard, Skip };

struct Vec3 {
    f32 x{0.0f};
    f32 y{0.0f};
    f32 z{0.0f};
};

struct Plane {
    Vec3 normal{};
    f32 distance{0.0f};
};

struct SphereBounds {
    Vec3 center{};
    f32 radius{0.0f};
    bool known{false};
};

struct GeometryDiagnostic {
    GeometryError code{GeometryError::None};
    u32 instance_id{0};
    u32 mesh_id{0};
    u32 index{0};
};

struct InstanceDesc {
    u32 id{0};
    u32 mesh_id{0};
    u32 material_id{0};
    SphereBounds bounds{};
    VegetationKind vegetation{VegetationKind::None};
    bool double_sided{false};
    bool alpha_cutout{false};
    bool billboard_allowed{false};
};

struct InstanceSet {
    u64 scene_generation{0};
    u32 count{0};
    std::array<InstanceDesc, kMaxInstances> instances{};
};

[[nodiscard]] const char* geometry_error_name(GeometryError error) noexcept;
[[nodiscard]] GeometryError add_instance(
    InstanceSet& set, const InstanceDesc& instance) noexcept;
[[nodiscard]] GeometryError validate_instances(
    const InstanceSet& set, GeometryDiagnostic& diagnostic) noexcept;

struct InstanceBatch {
    u32 mesh_id{0};
    u32 material_id{0};
    u32 count{0};
    std::array<u32, kMaxInstances> instance_indices{};
};
struct BatchPlan {
    u32 count{0};
    std::array<InstanceBatch, kMaxBatches> batches{};
};
[[nodiscard]] GeometryError plan_batches(
    const InstanceSet& set, BatchPlan& plan,
    GeometryDiagnostic& diagnostic) noexcept;

struct ViewFrustum {
    u64 scene_generation{0};
    u32 plane_count{0};
    std::array<Plane, kMaxPlanes> planes{};
    Vec3 camera{};
    f32 max_distance{0.0f};
};
struct CullResult {
    u32 visible_count{0};
    std::array<u32, kMaxInstances> visible_ids{};
    u32 culled_count{0};
};
[[nodiscard]] GeometryError cull_instances(
    const InstanceSet& set, const ViewFrustum& view,
    CullResult& result, GeometryDiagnostic& diagnostic) noexcept;

struct LodLevel {
    f32 geometric_error{0.0f};
    u32 triangle_count{0};
};
struct LodChain {
    u64 scene_generation{0};
    u32 mesh_id{0};
    u32 level_count{0};
    std::array<LodLevel, kMaxLodLevels> levels{};
};
[[nodiscard]] GeometryError validate_lod_chain(
    const LodChain& chain, GeometryDiagnostic& diagnostic) noexcept;

struct LodRequest {
    Vec3 camera{};
    f32 screen_scale{1.0f};
    f32 max_screen_error{0.0f};
    u32 previous_level{0};
};
struct LodSelection {
    u32 mesh_id{0};
    u32 level{0};
    u32 triangle_count{0};
    f32 projected_error{0.0f};
};
[[nodiscard]] GeometryError select_lod(
    const LodChain& chain, const SphereBounds& bounds,
    const LodRequest& request, LodSelection& selection,
    GeometryDiagnostic& diagnostic) noexcept;

struct HlodNode {
    u32 mesh_id{0};
    u32 parent_mesh_id{0};
    f32 geometric_error{0.0f};
    u32 triangle_count{0};
    bool proxy{false};
};
struct HlodSet {
    u64 scene_generation{0};
    u32 count{0};
    std::array<HlodNode, kMaxMeshes> nodes{};
};
[[nodiscard]] GeometryError validate_hlod(
    const HlodSet& set, GeometryDiagnostic& diagnostic) noexcept;

struct HlodSelection {
    u32 mesh_id{0};
    f32 geometric_error{0.0f};
    bool proxy{false};
};
[[nodiscard]] GeometryError select_hlod(
    const HlodSet& set, u32 root_mesh_id, f32 max_error,
    HlodSelection& selection, GeometryDiagnostic& diagnostic) noexcept;

struct GeometryChunk {
    u32 chunk_id{0};
    u32 mesh_id{0};
    u32 lod_level{0};
    u32 bytes{0};
    bool verified{false};
};
struct ChunkSet {
    u64 scene_generation{0};
    u32 count{0};
    std::array<GeometryChunk, kMaxChunks> chunks{};
};
struct ResidentChunks {
    u32 count{0};
    std::array<u32, kMaxChunks> chunk_ids{};
};
struct StreamPlan {
    u32 count{0};
    std::array<u32, kMaxStreamRequests> chunk_ids{};
    u32 total_bytes{0};
    bool truncated{false};
};
[[nodiscard]] GeometryError plan_stream(
    const ChunkSet& chunks, const ResidentChunks& resident,
    u32 byte_budget, StreamPlan& plan,
    GeometryDiagnostic& diagnostic) noexcept;

struct VegetationRequest {
    Vec3 camera{};
    f32 billboard_distance{0.0f};
};
struct VegetationDecision {
    u32 instance_id{0};
    VegetationRenderClass render_class{VegetationRenderClass::Mesh};
    bool double_sided{false};
    bool alpha_cutout{false};
};
[[nodiscard]] GeometryError classify_vegetation(
    const InstanceDesc& instance, const VegetationRequest& request,
    VegetationDecision& decision, GeometryDiagnostic& diagnostic) noexcept;

struct GeometryMetrics {
    u32 mesh_id{0};
    u32 vertex_count{0};
    u32 triangle_count{0};
    u32 byte_count{0};
};
struct GeometryMetricSet {
    u32 count{0};
    std::array<GeometryMetrics, kMaxMeshes> meshes{};
};
struct GeometryBudget {
    u64 max_vertices{0};
    u64 max_triangles{0};
    u64 max_bytes{0};
};
struct GeometryBudgetPlan {
    u64 total_vertices{0};
    u64 total_triangles{0};
    u64 total_bytes{0};
    bool within_budget{false};
};
[[nodiscard]] GeometryError validate_geometry_budget(
    const GeometryMetricSet& set, const GeometryBudget& budget,
    GeometryBudgetPlan& plan, GeometryDiagnostic& diagnostic) noexcept;

}  // namespace stormline::graphics::geometry
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `GFX-04-03`.

## Semantics

- **Instances:** IDs/mesh/material nonzero, unique; scene generation nonzero; radius finite and >=0; bounds-known flag preserved.
- **Batches:** group by `(mesh_id, material_id)`, sorted by mesh then material; instance indices retain declaration order.
- **Culling:** plane normals must be finite unit vectors; scene generation must match; unknown bounds remain visible; distance uses `|camera-center| <= max_distance + radius`; a plane excludes only when `dot(normal,center)+distance < -radius`. Any invalid camera/mismatch fails closed; no uncertain cull.
- **LOD:** 1..8 levels; level 0 error 0; triangle counts positive/nonincreasing; errors finite/nondecreasing. Projected error = `geometric_error / max(distance,1) * screen_scale`; choose the coarsest level within `max_screen_error`. If the previous level is finer and still within 1.25x threshold, keep it (hysteresis). Unknown bounds select level 0.
- **HLOD:** unique mesh IDs, parent exists or 0, acyclic. Selection walks only the root's subtree and picks the highest `geometric_error <= max_error`; otherwise the root. No mutation of authored IDs.
- **Streaming:** chunk IDs unique; mesh nonzero; LOD 0..7; bytes positive; unverified chunk in the set returns `UnverifiedChunk`. Resident chunks are skipped. Remaining requests are sorted by mesh, LOD, chunk ID and admitted until the byte budget; excess is reported via `truncated=true`, not silently dropped.
- **Vegetation:** only Grass/Bush/Tree accepted; `billboard_allowed` and bounds-known decide Mesh vs Billboard at `billboard_distance`; flags are preserved.
- **Geometry budget:** metric mesh IDs unique; vertex/triangle counts positive; checked totals; exceed returns `GeometryBudgetExceeded` with populated totals.
- **Threading:** single-owner unless synchronized; no allocation, exception, driver, file or network.

## Test oracles (future GFX-04-03..-09)

| ID | Scenario | Oracle |
|---|---|---|
| INS-01 | instancing/batching | add/duplicate/capacity/bounds, batch grouping/order |
| CUL-01 | conservative culling | visible/unknown-bounds/distance/plane/stale-generation/invalid camera |
| LOD-01 | LOD/HLOD | chain ordering, selection/hysteresis/unknown bounds, hierarchy cycle |
| STR-01 | stream planning | verified/unverified/resident/budget/sorted/truncated |
| VEG-01 | vegetation | class/flags/threshold/invalid category |
| GEO-01 | geometry budget | totals/overflow/exceeded/duplicates |
| QLF-G401 | integrated | instances->batch->cull->LOD/HLOD->stream->vegetation->budget |
| QLF-G402 | deterministic repeat | identical plans |
| QLF-G403 | failure recovery | typed error followed by valid operation |
| QLF-G404 | bounded overload | 10,000 attempts keep capacities |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/graphics/geometry/`. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp`.

### `GFX-04-03` (instancing)

1. `src/stormline/graphics/geometry/geometry_types.hpp`
2. `src/stormline/graphics/geometry/geometry_instance.hpp`
3. `tests/core/gfx04_instance_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-GFX-04-03.md`

### `GFX-04-04` (culling)

1. `src/stormline/graphics/geometry/geometry_cull.hpp`
2. `tests/core/gfx04_cull_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-04-04.md`

### `GFX-04-05` (HLOD)

1. `src/stormline/graphics/geometry/geometry_lod.hpp`
2. `tests/core/gfx04_lod_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-04-05.md`

### `GFX-04-06` (mesh streaming)

1. `src/stormline/graphics/geometry/geometry_stream.hpp`
2. `tests/core/gfx04_stream_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-04-06.md`

### `GFX-04-07` (vegetation)

1. `src/stormline/graphics/geometry/geometry_vegetation.hpp`
2. `tests/core/gfx04_vegetation_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-04-07.md`

### `GFX-04-08` (geometry optimization)

1. `src/stormline/graphics/geometry/geometry_budget.hpp`
2. `tests/core/gfx04_budget_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-04-08.md`

### `GFX-04-09` (qualification)

1. `tests/core/gfx04_geometry_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-GFX-04-09.md`

`GFX-04-10` is documentary closeout only. Qualification is internal/CI-only; no native GPU, mesh library, submission, rendering, hardware, ABI or release claim.

## Stop / rollback / security

Stop on stale source, missing admission, native GPU/mesh library/codec selection, submission, host I/O, public ABI/release claim or HIGH/CRITICAL. Revert normally; never force push.
