# GFX-03 INTERNAL_ONLY Logical Render Graph Contract v0 (NLE-PRPLAN-GFX-03-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `2686632`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **WO:** [NLE-PRPLAN-GFX-03-02](../work-orders/NLE-PRPLAN-GFX-03-02.md).

## Objective

Freeze the first bounded GFX-03 logical API: pass/resource definitions, hazard dependency DAG with cycle detection, logical synchronization transitions, transient lifetime/alias planning and VRAM admission. No native GPU, allocator, command buffer, fence, submission, rendering, dependency, ABI or release.

## Admission and boundaries

- Formal dependencies are `GFX-01` and `CORE-03`; neither is module-qualified.
- GFX-03 owns logical graph compilation and planning.
- GFX-01 RHI capabilities/queue roles; CORE-03 CPU scheduling; CORE-02 CPU allocation; GFX-02 shader reflection; DATA-02/05 assets; GFX-04+ renderer algorithms.
- No Vulkan/D3D12/Metal/WebGPU/VMA/D3D12MA or native allocator is selected.

## Policy invariants

- **No native GPU.** Plans only; no command recording, submit, fence, swapchain, present or rendering.
- **Bounded and checked.** Fixed capacities and overflow-safe arithmetic.
- **Fail closed.** Duplicate/invalid IDs, unknown references, ambiguous writers, uninitialized reads, cycles, alias conflicts and budget overflow return typed errors.
- **Deterministic.** Stable declaration-index topological tie-break; sorted alias output.
- **Conservative aliasing.** Only transient resources with equal size/alignment and disjoint lifetimes alias.
- **No execution evidence.** A plan is not a submission, completion or pixel result.
- **No host I/O.** All APIs operate on caller-provided in-memory tables.

## Internal API (logical, exact names)

```cpp
namespace stormline::graphics::render_graph {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

inline constexpr u32 kMaxPasses = 64;
inline constexpr u32 kMaxResources = 128;
inline constexpr u32 kMaxUses = 256;
inline constexpr u32 kMaxEdges = 512;
inline constexpr u32 kMaxTransitions = 256;
inline constexpr u32 kMaxAliasGroups = 64;
inline constexpr u32 kMaxDiagnostics = 16;
inline constexpr u32 kMaxNameBytes = 32;
inline constexpr u32 kMaxAlignment = 4096;

enum class GraphError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicatePass,
    DuplicateResource,
    NotFound,
    CapacityFull,
    Cycle,
    AmbiguousWriter,
    UninitializedRead,
    InvalidUse,
    QueueUnsupported,
    AliasConflict,
    BudgetUnknown,
    BudgetExceeded,
    StaleGeneration
};

enum class ResourceKind : std::uint8_t { External, Persistent, Transient, History };
enum class Access : std::uint8_t { Read, Write, ReadWrite };
enum class PassKind : std::uint8_t { Graphics, Compute, Copy, Present };
enum class Hazard : std::uint8_t { RAW, WAR, WAW };
enum class GraphAccess : std::uint8_t { None, Read, Write };

struct GraphDiagnostic {
    GraphError code{GraphError::None};
    u32 pass_id{0};
    u32 resource_id{0};
    u32 index{0};
};

struct ResourceDesc {
    u32 id{0};
    ResourceKind kind{ResourceKind::Transient};
    u64 bytes{0};
    u32 alignment{1};
};

struct PassDesc {
    u32 id{0};
    rhi::QueueRole queue{rhi::QueueRole::Graphics};
    PassKind kind{PassKind::Graphics};
    bool side_effect{false};
};

struct UseDesc {
    u32 pass_id{0};
    u32 resource_id{0};
    Access access{Access::Read};
};

struct GraphDefinition {
    u64 device_generation{0};
    u32 resource_count{0};
    std::array<ResourceDesc, kMaxResources> resources{};
    u32 pass_count{0};
    std::array<PassDesc, kMaxPasses> passes{};
    u32 use_count{0};
    std::array<UseDesc, kMaxUses> uses{};
};

[[nodiscard]] const char* graph_error_name(GraphError error) noexcept;
[[nodiscard]] GraphError add_resource(
    GraphDefinition& graph, const ResourceDesc& resource) noexcept;
[[nodiscard]] GraphError add_pass(
    GraphDefinition& graph, const PassDesc& pass) noexcept;
[[nodiscard]] GraphError add_use(
    GraphDefinition& graph, const UseDesc& use) noexcept;
[[nodiscard]] GraphError validate_graph(
    const GraphDefinition& graph, GraphDiagnostic& diagnostic) noexcept;

struct DependencyEdge {
    u32 producer_pass{0};
    u32 consumer_pass{0};
    u32 resource_id{0};
    Hazard hazard{Hazard::RAW};
};
struct DependencyPlan {
    u32 order_count{0};
    std::array<u32, kMaxPasses> order{};
    u32 edge_count{0};
    std::array<DependencyEdge, kMaxEdges> edges{};
};
[[nodiscard]] GraphError build_dependency_plan(
    const GraphDefinition& graph, DependencyPlan& plan,
    GraphDiagnostic& diagnostic) noexcept;

struct SyncTransition {
    u32 resource_id{0};
    GraphAccess old_access{GraphAccess::None};
    GraphAccess new_access{GraphAccess::None};
    rhi::QueueRole old_queue{rhi::QueueRole::Graphics};
    rhi::QueueRole new_queue{rhi::QueueRole::Graphics};
    u32 before_pass{0};
};
struct SyncPlan {
    u32 transition_count{0};
    std::array<SyncTransition, kMaxTransitions> transitions{};
};
[[nodiscard]] GraphError plan_sync(
    const GraphDefinition& graph, const DependencyPlan& dependencies,
    SyncPlan& plan, GraphDiagnostic& diagnostic) noexcept;

struct Lifetime {
    u32 resource_id{0};
    u32 first_pass{0};
    u32 last_pass{0};
};
struct AliasGroup {
    u32 resource_count{0};
    std::array<u32, kMaxResources> resource_ids{};
    u64 bytes{0};
    u32 alignment{1};
};
struct AliasPlan {
    u32 lifetime_count{0};
    std::array<Lifetime, kMaxResources> lifetimes{};
    u32 group_count{0};
    std::array<AliasGroup, kMaxAliasGroups> groups{};
    u64 alias_saved_bytes{0};
};
[[nodiscard]] GraphError plan_transients(
    const GraphDefinition& graph, const DependencyPlan& dependencies,
    AliasPlan& plan, GraphDiagnostic& diagnostic) noexcept;

struct GpuBudgetSnapshot {
    bool known{false};
    u64 total_bytes{0};
    u64 headroom_bytes{0};
};
struct BudgetPlan {
    u64 persistent_bytes{0};
    u64 transient_peak_bytes{0};
    u64 alias_saved_bytes{0};
    u64 required_bytes{0};
    bool within_budget{false};
};
[[nodiscard]] GraphError plan_budget(
    const GraphDefinition& graph, const AliasPlan& aliases,
    const GpuBudgetSnapshot& budget, BudgetPlan& plan,
    GraphDiagnostic& diagnostic) noexcept;

}  // namespace stormline::graphics::render_graph
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `GFX-03-03`.

## Semantics

- **IDs:** pass and resource IDs are nonzero and unique; uses reference existing IDs.
- **Capacities:** 1..64 passes, 1..128 resources, 0..256 uses, 512 edges, 256 transitions, 64 alias groups.
- **Resources:** bytes 1..2^63-1; alignment power of two 1..4096.
- **Passes:** known queue role and pass kind; side-effect flag is preserved.
- **Device generation:** nonzero; every plan copies no device handle, only logical metadata.
- **Validation:** unknown references, duplicate IDs, capacity and invalid enum values return typed errors; `add_*` returns the same errors without partial mutation on failure.
- **Writer rule:** each resource has at most one writer (`Write`/`ReadWrite`); a second writer returns `AmbiguousWriter`.
- **Uninitialized read:** a `Transient` resource read with no writer returns `UninitializedRead`; external/persistent/history may be pre-initialized.
- **Dependency edges:** writer to each reader as `RAW`; edges sorted by consumer, producer, resource. Multiple writers are rejected before edge construction. WAR/WAW are represented as typed enum values reserved for future subresource ordering but not emitted in v0.
- **Topology:** Kahn's algorithm; ties choose the lowest pass declaration index. A remaining node returns `Cycle` with its pass ID.
- **Synchronization:** traverse passes in topological order and uses in declaration order; first use emits `None -> mapped access`; later changes in access or queue emit a transition. Mapping: `Read -> Read`, `Write/ReadWrite -> Write`.
- **Transients:** lifetimes are first/last topological positions; only transient resources with uses participate. Greedy grouping requires equal bytes/alignment and `last_pass < next first_pass`; groups are stable by first pass/id.
- **Alias savings:** `(resource_count - 1) * bytes` per group, checked.
- **Budget:** `known=false` or zero headroom returns `BudgetUnknown`; headroom > total is `InvalidArgument`; required = persistent (`Persistent`/`History`) + aliased transient peak, with `External` excluded and checked overflow; overcommit returns `BudgetExceeded` with `within_budget=false`.
- **Identity:** no hashing is required in this sequence; plans are compared field-by-field.
- **Threading:** single-owner unless synchronized; no allocation, exception, driver, file or network.

## Test oracles (future GFX-03-03..-08)

| ID | Scenario | Oracle |
|---|---|---|
| DEF-01 | definition validation | add/duplicate/capacity/ranges/unknown refs/enums |
| DEP-01 | dependency DAG | RAW edges, cycle, ambiguous writer, uninitialized read, stable topo order |
| SYN-01 | sync transitions | first use, access change, queue handoff, no-op same access/queue, capacity |
| TRA-01 | transients | lifetimes, disjoint alias groups, size/alignment mismatch, saved bytes |
| BUD-01 | VRAM budget | unknown/headroom/overflow/overcommit/persistent+transient accounting |
| QLF-G301 | integrated | definition->DAG->sync->transient->budget |
| QLF-G302 | deterministic repeat | identical plans field-by-field |
| QLF-G303 | failure recovery | each typed error followed by valid operation |
| QLF-G304 | bounded overload | 10,000 attempts keep capacities |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/graphics/render_graph/`. CMake adds one `INTERFACE` target linking `stormline_gfx01_rhi` and one test executable per packet; no production `.cpp`.

### `GFX-03-03` (passes/definitions)

1. `src/stormline/graphics/render_graph/graph_types.hpp`
2. `src/stormline/graphics/render_graph/graph_definition.hpp`
3. `tests/core/gfx03_graph_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-GFX-03-03.md`

### `GFX-03-04` (dependencies)

1. `src/stormline/graphics/render_graph/graph_dependency.hpp`
2. `tests/core/gfx03_dependency_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-03-04.md`

### `GFX-03-05` (barriers)

1. `src/stormline/graphics/render_graph/graph_sync.hpp`
2. `tests/core/gfx03_sync_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-03-05.md`

### `GFX-03-06` (transient resources)

1. `src/stormline/graphics/render_graph/graph_transient.hpp`
2. `tests/core/gfx03_transient_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-03-06.md`

### `GFX-03-07` (VRAM budget)

1. `src/stormline/graphics/render_graph/graph_budget.hpp`
2. `tests/core/gfx03_budget_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-03-07.md`

### `GFX-03-08` (qualification)

1. `tests/core/gfx03_graph_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-GFX-03-08.md`

`GFX-03-09` is documentary closeout only. Qualification is internal/CI-only; no native GPU, submission, rendering, hardware, ABI or release claim.

## Stop / rollback / security

Stop on stale source, missing admission, native GPU/allocator/API selection, command submission, host I/O, public ABI/release claim or HIGH/CRITICAL. Revert normally; never force push.
