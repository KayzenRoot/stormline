# WORLD-03 internal spatial/streaming metadata contract v0

**Status:** `APPROVED CONTRACT / INTERNAL_ONLY / NO STREAMING RUNTIME`. **ADR:** [ADR-0129](../adr/0129-world-03-internal-spatial-streaming-metadata.md). **Architecture:** [world-03-internal-spatial-streaming-metadata](../architecture/world-03-internal-spatial-streaming-metadata.md). **Governance:** [world-03-governance-v0](world-03-governance-v0.md).

Freeze the bounded logical API for cells, interest queries, origin epoch intent and streaming plan metadata. No async tasks, I/O, decode, cache, origin rebase, spatial query result, physics/network coordination, renderer, editor, GPU, performance, ABI or release.

## Namespace and common types

Header-only under `src/stormline/spatial/`, namespace `stormline::spatial`.

```cpp
using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;
using f32 = float;

inline constexpr u32 kMaxSpatialCells = 64;
inline constexpr u32 kMaxInterestSources = 16;
inline constexpr u32 kMaxStreamingCells = 64;
inline constexpr u64 kMaxCellBytes = 1024ull * 1024ull * 1024ull;

enum class SpatialError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    CellInvalid,
    InterestInvalid,
    OriginInvalid,
    StreamInvalid,
    Incomplete,
    Unsupported
};

enum class InterestRole : std::uint8_t {
    Player, Camera, Ai, Quest, Net, Audio, Editor
};

enum class CellPriority : std::uint8_t {
    Pinned, Prefetch, Optional, Evict
};

struct SpatialDiagnostic {
    SpatialError code{SpatialError::None};
    u32 source_id{0};
    u32 index{0};
};
```

## Cell metadata

```cpp
struct CellDesc {
    u64 cell_key{0};
    i64 x{0};
    i64 z{0};
    u32 revision{0};
};

struct CellSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 cell_count{0};
    std::array<CellDesc, kMaxSpatialCells> cells{};
};

struct CellPlan {
    u32 cell_count{0};
    i64 min_x{0};
    i64 max_x{0};
    i64 min_z{0};
    i64 max_z{0};
};

[[nodiscard]] bool cell_floor_div(
    i64 value, i64 cell_size, i64& result) noexcept;

[[nodiscard]] SpatialError plan_cells(
    const CellSetDesc& cells, CellPlan& plan,
    SpatialDiagnostic& diagnostic) noexcept;
```

Semantics: world ID/revision nonzero; cell count `1..64`; cell keys nonzero and unique; `(x,z)` pairs unique; cell revisions nonzero; negative coordinates are valid. `cell_floor_div` requires positive `cell_size` and uses mathematical floor division (for example `-1 / 4 -> -1`); overflow of `INT64_MIN / -1` is rejected. Plan returns count and coordinate bounds.

## Interest query metadata

```cpp
struct InterestBounds {
    f32 min_x{0.0f};
    f32 min_z{0.0f};
    f32 max_x{0.0f};
    f32 max_z{0.0f};
};

struct InterestSourceDesc {
    u32 source_id{0};
    u32 revision{0};
    InterestRole role{InterestRole::Player};
    InterestBounds bounds{};
    u32 priority{0};
    bool required_complete{false};
};

struct InterestSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 source_count{0};
    std::array<InterestSourceDesc, kMaxInterestSources> sources{};
};

struct InterestPlan {
    u32 source_count{0};
    u32 complete_count{0};
    u32 incomplete_count{0};
    InterestBounds union_bounds{};
};

[[nodiscard]] SpatialError plan_interest(
    const InterestSetDesc& interest, InterestPlan& plan,
    SpatialDiagnostic& diagnostic) noexcept;
```

Semantics: world ID/revision nonzero; source count `0..16`; source IDs/revisions nonzero and unique; roles allowlisted; bounds finite with `min_x < max_x` and `min_z < max_z`; priority is metadata only. `required_complete` increments `complete_count`; otherwise `incomplete_count`. `union_bounds` is the union of all source bounds. No spatial index or result is produced.

## Origin epoch metadata

```cpp
struct OriginEpochDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 old_epoch{0};
    u32 new_epoch{0};
    f32 old_x{0.0f};
    f32 old_y{0.0f};
    f32 old_z{0.0f};
    f32 new_x{0.0f};
    f32 new_y{0.0f};
    f32 new_z{0.0f};
    bool physics_ack{false};
    bool render_ack{false};
    bool network_ack{false};
};

struct OriginPlan {
    u32 old_epoch{0};
    u32 new_epoch{0};
    bool accepted{false};
};

[[nodiscard]] SpatialError plan_origin_change(
    const OriginEpochDesc& origin, OriginPlan& plan,
    SpatialDiagnostic& diagnostic) noexcept;
```

Semantics: world ID/revision nonzero; old/new epochs nonzero and distinct; all origin coordinates finite. `accepted` is true only when physics, render and network acknowledgements are all present. No rebase is executed and no durable cell/entity identity changes.

## Streaming plan metadata

```cpp
struct StreamingCellDesc {
    u64 cell_key{0};
    u32 revision{0};
    CellPriority priority{CellPriority::Optional};
    u32 request_generation{0};
    u32 cancel_generation{0};
    u64 byte_budget{0};
};

struct StreamingPlanDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 cell_count{0};
    std::array<StreamingCellDesc, kMaxStreamingCells> cells{};
};

struct StreamingPlan {
    u32 cell_count{0};
    u32 pinned_count{0};
    u32 prefetch_count{0};
    u64 total_bytes{0};
};

[[nodiscard]] SpatialError plan_streaming(
    const StreamingPlanDesc& streaming, StreamingPlan& plan,
    SpatialDiagnostic& diagnostic) noexcept;
```

Semantics: world ID/revision nonzero; cell count `0..64`; cell keys nonzero and unique; priorities allowlisted; request generation nonzero; cancel generation `<= request generation`; per-cell byte budget `<= 1 GiB`; total bytes accumulated in checked `u64`. Pinned and prefetch counts are reported. No task is created, cancelled or executed.

## Common rules

All functions are `noexcept`, allocation-free, exception-free and use no file, network, audio, GPU, clock, thread or global state. Invalid input resets the plan to default and sets a typed diagnostic with source ID and index.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| CEL-01 | cells | floor division, signed coords, unique keys, bounds |
| INT-01 | interest | bounds, roles, priorities, union, completeness |
| ORG-01 | origin | epoch change, finite origins, owner acknowledgements |
| STR-01 | streaming plan | keys, priorities, generations, byte budgets, totals |
| QLF-W301 | integrated | cells -> interest -> origin -> streaming |
| QLF-W302 | deterministic repeat | identical plans/counts |
| QLF-W303 | failure recovery | typed error followed by valid operation |
| QLF-W304 | bounded overload | 10,000 attempts keep caps |

## Implementation allowlists

No production `.cpp`. One `INTERFACE` target and one test executable per implementation packet.

### `WORLD-03-03` (cells)

1. `src/stormline/spatial/spatial_types.hpp`
2. `src/stormline/spatial/cell_plan.hpp`
3. `tests/core/world03_cell_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-WORLD-03-03.md`

### `WORLD-03-04` (interest)

1. `src/stormline/spatial/interest_plan.hpp`
2. `tests/core/world03_interest_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-03-04.md`

### `WORLD-03-05` (origin)

1. `src/stormline/spatial/origin_plan.hpp`
2. `tests/core/world03_origin_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-03-05.md`

### `WORLD-03-06` (streaming)

1. `src/stormline/spatial/streaming_plan.hpp`
2. `tests/core/world03_streaming_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-WORLD-03-06.md`

### `WORLD-03-07` (qualification)

1. `tests/core/world03_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-WORLD-03-07.md`
