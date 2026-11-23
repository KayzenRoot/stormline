# TWO-02 INTERNAL_ONLY Tilemap Contract v0 (NLE-PRPLAN-TWO-02-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `fa7f2bd`. **ADR:** [ADR-0124](../adr/0124-two-02-internal-tilemap-pipeline.md). **WO:** [NLE-PRPLAN-TWO-02-02](../work-orders/NLE-PRPLAN-TWO-02-02.md).

## Objective

Freeze the first bounded TWO-02 logical API: signed grid/chunk math, tile cells, collision-authoring shapes, parallax and streaming plans. No tile renderer, importer, persistence, chunk I/O, collision solver, physics, dependency, ABI or release.

## Admission and boundaries

- Formal dependencies are `TWO-01` and `DATA-04`; neither is module-qualified.
- TWO-02 owns logical grid/chunk, tile, collision-authoring, parallax and streaming plans.
- TWO-01 Canvas; DATA-02/03/04/05 assets/authoring/cook; GFX GPU; PHYS/WORLD collision/entities.
- No renderer, file format, codec, cache, physics engine, navigation system or hardware driver is selected.

## Policy invariants

- **No renderer or I/O.** Metadata/planning only; no tile instance, buffer, texture, draw, file, cache or async job.
- **Signed floor math.** Negative cells use mathematical floor division; truncation and overflow fail closed.
- **Bounded and finite.** Fixed capacities; NaN/Inf, zero/negative dimensions, overflow and out-of-bounds cells are rejected.
- **Collision metadata is not physics.** PHYS owns contacts/solver/activation.
- **Deterministic.** Stable IDs, signed coordinates and declared order determine output.

## Internal API (logical, exact names)

```cpp
namespace stormline::tilemap {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;
using f32 = float;

inline constexpr u32 kMaxCollisionShapes = 8;
inline constexpr u32 kMaxStreamingChunks = 256;

enum class TilemapError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    CoordinateOutOfBounds,
    GridInvalid,
    TileInvalid,
    CollisionInvalid,
    ParallaxInvalid,
    StreamingInvalid,
    BudgetExceeded,
    StaleRevision,
    Unsupported
};

enum class TileOrientation : std::uint8_t {
    Orthogonal, Isometric, Staggered, HexAxial
};
enum class TileTransform : std::uint8_t {
    None, FlipX, FlipY, Rotate90, Rotate180, Rotate270
};
enum class CollisionShapeKind : std::uint8_t { Rect, Segment };
enum class ChunkState : std::uint8_t {
    Unloaded, Requested, Fetching, Cancelled, Failed, Ready
};

struct TilemapDiagnostic {
    TilemapError code{TilemapError::None};
    u32 source_id{0};
    u32 index{0};
};

struct GridDesc {
    u32 map_id{0};
    u32 revision{0};
    u32 tile_width{0};
    u32 tile_height{0};
    u32 chunk_width{0};
    u32 chunk_height{0};
    i64 min_cell_x{0};
    i64 min_cell_y{0};
    i64 max_cell_x{0};
    i64 max_cell_y{0};
};

struct GridCellPlan {
    i64 chunk_x{0};
    i64 chunk_y{0};
    u32 local_x{0};
    u32 local_y{0};
};

[[nodiscard]] TilemapError plan_grid_cell(
    const GridDesc& grid, i64 cell_x, i64 cell_y, GridCellPlan& plan,
    TilemapDiagnostic& diagnostic) noexcept;

struct TileCellDesc {
    u32 map_id{0};
    u32 layer_id{0};
    u32 revision{0};
    i64 cell_x{0};
    i64 cell_y{0};
    u32 tile_id{0};
    u32 tile_revision{0};
    bool empty{false};
    TileOrientation orientation{TileOrientation::Orthogonal};
    TileTransform transform{TileTransform::None};
};

struct TileCellPlan {
    u32 tile_id{0};
    bool empty{false};
    TileTransform transform{TileTransform::None};
};

[[nodiscard]] TilemapError plan_tile_cell(
    const TileCellDesc& cell, TileCellPlan& plan,
    TilemapDiagnostic& diagnostic) noexcept;

struct CollisionShapeDesc {
    u32 shape_id{0};
    u32 revision{0};
    CollisionShapeKind kind{CollisionShapeKind::Rect};
    f32 x{0.0f};
    f32 y{0.0f};
    f32 width{0.0f};
    f32 height{0.0f};
    bool solid{true};
    bool one_way{false};
};

struct TileCollisionDesc {
    u32 tile_id{0};
    u32 revision{0};
    u32 shape_count{0};
    std::array<CollisionShapeDesc, kMaxCollisionShapes> shapes{};
};

struct TileCollisionPlan {
    u32 shape_count{0};
    u32 solid_count{0};
};

[[nodiscard]] TilemapError plan_tile_collision(
    const TileCollisionDesc& collision, TileCollisionPlan& plan,
    TilemapDiagnostic& diagnostic) noexcept;

struct ParallaxLayerDesc {
    u32 layer_id{0};
    u32 revision{0};
    f32 factor_x{1.0f};
    f32 factor_y{1.0f};
    bool repeat_x{false};
    bool repeat_y{false};
};

struct ParallaxPlan {
    f32 factor_x{1.0f};
    f32 factor_y{1.0f};
    bool repeat_x{false};
    bool repeat_y{false};
};

[[nodiscard]] TilemapError plan_parallax(
    const ParallaxLayerDesc& parallax, ParallaxPlan& plan,
    TilemapDiagnostic& diagnostic) noexcept;

struct StreamingBudget {
    u32 max_visible_chunks{0};
    u32 max_prefetch_chunks{0};
    u32 max_requests{0};
    u64 max_bytes{0};
};

struct StreamingRequest {
    u32 map_id{0};
    u32 revision{0};
    u32 visible_chunks{0};
    u32 prefetch_chunks{0};
    u32 request_count{0};
    u64 requested_bytes{0};
    u32 failed_chunks{0};
};

struct StreamingPlan {
    u32 visible_chunks{0};
    u32 prefetch_chunks{0};
    u32 request_count{0};
    u64 bytes{0};
    bool degraded{false};
};

[[nodiscard]] TilemapError plan_streaming(
    const StreamingRequest& request, const StreamingBudget& budget,
    StreamingPlan& plan, TilemapDiagnostic& diagnostic) noexcept;

}  // namespace stormline::tilemap
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `TWO-02-03`.

## Semantics

- **Grid:** IDs nonzero; tile/chunk dimensions positive; min/max bounds ordered; cell inside bounds; chunk uses mathematical floor division for negative cells; local coordinates in `[0,chunk_dimension)`; overflow `CoordinateOutOfBounds`.
- **Tile cell:** map/layer/revision nonzero; empty cells require `tile_id==0`, zero tile revision and `transform==None`; non-empty require nonzero tile ID/revision; orientation/transform declared; non-orthogonal transforms unsupported in this slice.
- **Collision authoring:** tile/shape IDs nonzero and unique; count bounded; rect width/height positive; segment finite with nonzero extent; solid/one-way flags preserved; no contact/solver is produced.
- **Parallax:** layer ID/revision nonzero; factors finite in `[0,4]`; repeat flags preserved; no scroll transform.
- **Streaming:** map ID/revision nonzero; budget caps positive; failures `<=` request count; per-domain requests clamp to budgets with `degraded=true`; no I/O or residency mutation.
- **Common:** all functions `noexcept`; no allocation, exception, file, network, GPU, thread or global state. Invalid input zeroes/defaults outputs and sets the diagnostic.

## Test oracles (future TWO-02-03..-08)

| ID | Scenario | Oracle |
|---|---|---|
| GRD-01 | grid/chunk math | bounds, negative floor division, local coords |
| TIL-01 | tile cells | IDs, empty sentinel, orientation/transform |
| COL-01 | collision authoring | shape IDs, rect/segment bounds, flags |
| PRX-01 | parallax | IDs, factors, repeat flags |
| STR-01 | streaming | IDs, budget clamps, failures, degraded receipt |
| QLF-T201 | integrated | grid->tile->collision->parallax->streaming |
| QLF-T202 | deterministic repeat | identical plans/flags/counts |
| QLF-T203 | failure recovery | typed error followed by valid operation |
| QLF-T204 | bounded overload | 10,000 attempts keep caps |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/tilemap/`. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp`.

### `TWO-02-03` (grid)

1. `src/stormline/tilemap/tilemap_types.hpp`
2. `src/stormline/tilemap/grid_plan.hpp`
3. `tests/core/two02_grid_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-TWO-02-03.md`

### `TWO-02-04` (tiles)

1. `src/stormline/tilemap/tile_plan.hpp`
2. `tests/core/two02_tile_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-02-04.md`

### `TWO-02-05` (collision shapes)

1. `src/stormline/tilemap/collision_plan.hpp`
2. `tests/core/two02_collision_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-02-05.md`

### `TWO-02-06` (parallax)

1. `src/stormline/tilemap/parallax_plan.hpp`
2. `tests/core/two02_parallax_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-02-06.md`

### `TWO-02-07` (streaming)

1. `src/stormline/tilemap/streaming_plan.hpp`
2. `tests/core/two02_streaming_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-TWO-02-07.md`

### `TWO-02-08` (qualification)

1. `tests/core/two02_tilemap_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-TWO-02-08.md`
