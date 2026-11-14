# TWO-02 — Typed Tilemap, Chunk, Terrain and Collision Metadata API v0.1

**Research WO NLE-P00-WO-002-TWO-02 | #150 | Code #38 BLOCKED.** Conceptual semantics only, NOT C++ ABI, executable Editor/CLI/MCP, on-disk format, GPU API or network protocol.

| Type | Versioned fields | Invariants and source-of-truth owner |
|---|---|---|
| `TileMapAssetV1` | project+MapId/revision, LevelId/world, orientation, tile size, finite/infinite bounds, layers, DATA-02/04 source identity, rights | DATA-04 durable source, no duplicated world scene store |
| `TilesetReferenceV1` | TilesetId/revision, stable TileId mapping, texture/atlas/material DATA-03/05 refs, terrain/collision/animation links | no map-local Tiled GID persisted as stable TileId |
| `TileLayerV1` | LayerId/group parent, render/z/visibility/opacity, parallax, material/receiver masks, chunk index | TWO-01 painter order, no illegal alpha reorder |
| `TileGridProjectionV1` | orthogonal/isometric/staggered/hex enum, cell size/origin/axes, 2D world-to-grid/gamut, tie-break | inverse transform/negative cell bounds and orientation flags valid |
| `TileCellV1` | signed `int64` global grid x/y, TileId+variant/rotation/flip, bounded static metadata | nearest neighbor/depth/motion choices explicit |
| `TileChunkKeyV1` | MapId/LayerId, signed floor-division chunkX/chunkY, size schema and source epoch | mathematical floor for negatives, checked 64-bit indices |
| `TileChunkSnapshotV1` | tile array/spans, origin, bounds and version, source/cooked data hash and integrity status | DATA-04/05 source+cache, no unbounded raw payload |
| `TileTerrainRuleSetV1` | biome/tag/neighbor/Wang edge & corner mapping, deterministic variant weights, explicit seed and local radius | finite staged rule, cross-chunk neighbor invalidation |
| `ParallaxLayerPlanV1` | LayerId/camera ID, per-axis factor, scroll/repeat region, opacity and clip, last camera/origin epoch | Canvas2D presentation, no collision coordinate shift |
| `TileCollisionAuthoringV1` | Tileset/TileId, AABB/convex poly/edge local coords, material, one-way/slope typed flags, layer mask | no gameplay contacts or physics engine in TWO-02 |
| `TileCollisionSnapshotV1` | MapId/LayerId/chunk revision, derived shape geometry with transform and physics owner target | must match visual revision/authoritative chunk state |
| `CollisionActivationReceiptV1` | PHYS ack source generation, stable collision revision, activation frame and stale/mismatch reason | PHYS owner ack, never fake collision-ready state |
| `MapStreamingPlanV1` | camera+chunk visible/prefetch sets, priority/dependencies, bounded jobs/bytes/hysteresis/eviction, generation and cancellation | DATA-05 job/read path, GFX-03 upload/fence, WEB memory source UNKNOWN |
| `TileMapEditTransactionV1` | project/MapId/LayerId, expected revision, staged changed cells/chunks, neighbor diffs, author role, journal/rollback token | DATA-04 CAS and save/reopen, not direct filesystem write |
| `TileMapImportReceiptV1` | source tool/version/formats, copyright, sandbox asset refs, warnings/losses, stable ID mapping, compression limits | DATA-03 untrusted parser rights and fail-closed |
| `MapStreamingReceiptV1` | requested/resident/failed/evicted chunks, visual/physics ack, p50/p95/p99 actual/estimated/UNKNOWN, mem/cache/bytes and quality loss | diagnostics redacted; zero fabricated hardware or collision PASS |

## Logical state machine
`SOURCE_MAP_VALIDATED -> EDIT_JOURNAL_COMMITTED -> COOKED_CHUNKS_HASHED -> CHUNK_REQUESTED -> CHUNK_BYTES_VALIDATED -> CHUNK_READY -> RENDER_BATCH_GENERATION_SUBMITTED -> GPU_FENCE_COMPLETE -> PHYSICS_GENERATION_ACKED (when required) -> WORLD_VISIBLE/INTERACTIVE`. These are **distinct readiness axes**: draw availability != physics collision available. Failure/cancel/source revision/device loss => typed safe fallback, no unjournaled dirty loss or stale tile GPU buffer. Missing collision-critical chunk blocks interaction or preserves safe last-good barrier, not invisible floor.

## Negative integer chunk math
For `chunkWidth>0`: `chunkX = floor(cellX/chunkWidth)`, `localX = cellX - chunkX*chunkWidth`; same Y. With width 32: `-1 -> -1,31`; `-32 -> -1,0`; `-33 -> -2,31`. Validate multiplication overflow, signed min, tile grid bounds and chunk widths. GPU uses bounded origin-relative floats and device-checked instance buffers.

## Authoring Editor / CLI / MCP
Read-only: `InspectTileMap`, `InspectTileset`, `InspectTileChunk`, `InspectTerrainRule`, `PreviewTilePaint`, `PreviewMapStreamingBudget`, `InspectTileCollisionMetadata`, `GetMapStreamingReceipt`, `InspectTileMapImportWarnings`. All project/camera/asset scoped, expensive operations paginated and preview labeled ESTIMATED.
Mutations: `StageTileEdit`, `StageTileBatch`, `StageTerrainRuleEdit`, `ValidateTileMapTransaction`, `CommitTileMapTransaction`, `CancelTileMapOperation`, with expected DATA-04 revision, role + per-chunk/time/cell quotas, deterministic replay/undo/redo and atomic cross-chunk dirty invalidation. Source import via DATA-03 sandbox only; source export rights and path capability explicit.

## Typed errors
`TILEMAP_INVALID`, `TILESET_MISSING`, `TILE_ID_UNRESOLVED`, `COORDINATE_OVERFLOW`, `CHUNK_SIZE_INVALID`, `CHUNK_GRID_MISMATCH`, `CHUNK_INTEGRITY_FAILED`, `CHUNK_NOT_FOUND`, `CHUNK_LOAD_CANCELLED`, `CHUNK_RETRY_EXHAUSTED`, `WORLD_STREAMING_BUDGET_EXCEEDED`, `WORLD_DIRTY_EVICTION_DENIED`, `LAYER_ALPHA_ORDER_MISMATCH`, `PROJECTION_UNSUPPORTED`, `HEX_FLAG_INVALID`, `TERRAIN_RULE_INCOMPLETE`, `COLLISION_GEOMETRY_INVALID`, `PHYSICS_GENERATION_NOT_ACKED`, `COLLISION_SOURCE_REVISION_STALE`, `TMX_DECOMPRESS_LIMIT`, `TMX_TILE_FLAG_INVALID`, `EXTERNAL_LEVEL_SANDBOX_DENIED`, `TILEMAP_SOURCE_RIGHTS_DENIED`, `UNTRUSTED_SCRIPT_DENIED`, `SCENE_REVISION_CONFLICT`, `CAPABILITY_DENIED`, `CANCELLED`, `RECOVERY_REQUIRED`. Redact paths/user data, include correlation id, retryability and source/draw/physics stage.

## Implementation freeze
Exact stable binary schema and API types, approved orientation scope, owner-approved release/DoD, GFX/TWO-01 & DATA-04 code verified, PHYS and DATA-05 atomic generation contract, import license/BOM and zlib/zstd parser caps, GPU hardware/Web/Editor tests, negative coordinate and corruption goldens, real p95/p99 budget and fresh SHA-256 Context Lock. Future code #38 remains blocked.
