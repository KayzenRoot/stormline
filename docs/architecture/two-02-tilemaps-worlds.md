# TWO-02 — Stormline Tilemaps & 2D Worlds Architecture

**WO:** NLE-P00-WO-002-TWO-02 | **Research #150** | **Future implementation #38: OPEN/BLOCKED**  
**Context Lock BASE:** `11beaafb5122a29fdeb8a45aa01e4f90c1a6517a`. **Status: PROPOSED RESEARCH, DOCS ONLY.** No C++ tilemap code, editor save/load, real streaming, collision engine, GPU screenshot, demo, real benchmark or finalized release. Current risk LOW docs; future ELEVATED file corruption/memory/scene seams/physics interface.

## 1. Mission: large, editable, reliable 2D worlds
Make 2D world construction first-class with typed layer/cell/tileset authoring, stable tile IDs, orthogonal 2D default candidate, controlled projection options (isometric/staggered/hex), parallax/animation handoffs, deterministic grid algorithms, infinite sparse chunks with **64-bit logical coordinates**, safe streaming/edit/undo/recovery, portable native and WebGL2/ WebGPU via TWO-01 Canvas rather than separate tile GPU renderer.

Product quality is **measurable**, not a current guarantee. Catalog requires “Editor save/reopen, streaming and collision correspondence”; these are **future acceptance objectives**, not delivered capabilities. 60 FPS/huge worlds cannot be claimed without specified device/scene and evidence.

## 2. Strict subsystem boundaries
| Authority | TWO-02 may author or consume | It MUST NOT duplicate |
|---|---|---|
| CORE-05/06 | signed grid coordinate, world/local rebasing, tick, timers, tracing | bespoke jobs/timer/float-origin engine |
| DATA-01/02 | project, stable TilesetId/TileId/MapId/LevelId/chunk and asset rights | private filesystem or scene/asset registry |
| DATA-03 | untrusted Tiled TMX/JSON, LDtk JSON/ldtkl, tileset images XML/CSV import and sandbox/sanitizer | uncontrolled XML/JSON/XML entity decompression/path access |
| DATA-04 | durable editable world and undo/redo, journal, compare-and-swap expected revision, checksum, migrations, serialization | its own file-save engine or unjournaled edits |
| DATA-05 | chunk cache/cook/stream source, texture atlas and async I/O, dependency DAG, resource manifests/CRC and recovery | independent asset cooker/stream scheduler |
| TWO-01 | sprite/Canvas layer and batching, UV/material, clipping/pixel art and draw order | private tile renderer, layer drawing GPU backend |
| TWO-03 | animated tiles and sequencing/timeline, editor animation UI | full sprite/tile timeline engine here |
| TWO-04 | mixed depth 2.5D composition/projection ownership | universal 3D hybrid renderer |
| GFX-01/02/03 | GPU limits, shaders, RenderGraph/upload/fence, VRAM/resource retire, device loss | separate GPU allocator/upload shader compiler |
| GFX-05/06/07/08 | atlas/color/PBR/alpha, lighting occluders, camera/parallax/output, VFX sprites | second material, light/shadow, post stack, particle sim |
| WORLD/PHYS/NET/NAV | authoritative entities/spawns, collision shapes in physics, deterministic gameplay/network, nav grid/mesh | physics contacts, collision gameplay truth or nav solver in TWO-02 |
| EDIT/AI/MCP | author world cells/layers with bounded semantic changes + audited diff | arbitrary script execution, raw host file import or asset leakage |

**Important:** owner catalog only lists TWO-01 and DATA-04 mandatory dependency edges, but DATA-03/05, GFX-03, PHYS and WORLD etc are **contract/feature dependencies** that must be frozen/reconciled by future approved source hierarchy before code. Researching these dependencies does not mark them implemented.

## 3. Canonical tilemap data model
- `TileMapAssetV1`: MapId/project+world/level IDs and revisions, orientation, tile logical width/height, finite or infinite extent, world origin/rebase policy, layer hierarchy, version/provenance and references to licensed tileset assets.
- `TileSetDefinitionV1`: owner DATA-02 asset identifier + revision, tile stable GUID/local ID, atlas rect/texture material, collision authoring metadata, variants/weight/terrain tags and animation link to TWO-03. Multiple tilesets, stable references independent of Tiled import GIDs. No saved reference to external Tiled `firstgid` as canonical TileId.
- `TileLayerV1`: layer stable ID/group parent, draw sort order, visibility/opacity/blend, 2D parallax factor per camera, material mask/light channel, chunk index, transform and projection. Mixed image/object/group layers map to separate typed variants through normal DATA-04 scene structure, not a raw unbounded JSON map property bag.
- `TileCellV1`: signed x/y global cell coordinates, TileId/variant, flip/rotate transform with orientation-specific constraints, per-cell bounded typed metadata and revision. Empty tile sentinel defined, not ID 0 accidentally.
- `TileChunkKeyV1`: MapId/LayerId, integer chunkX/chunkY, chunkSizeVersion. `TileChunkV1`: signed chunk origin, tile array/spans, bounds, dirty cells, optional compressed serialized payload, deterministic hash and source/cooked epoch. Sparse missing chunks are **unallocated empty**, not serialized gigantic zero buffers.
- Exact coordinate rule: on signed cell coordinate and positive chunk width `C`, `chunk = floor(cell/C)` mathematical **floor toward minus infinity** and `local = cell - chunk*C` in `[0,C)`. Never use a truncating-toward-zero integer division for negative cells. Example with C=32: cell -1 => chunk -1 and local 31; cell -32 => chunk -1 local 0; cell -33 => chunk -2 local 31. Use safe checked 64-bit products, disallow overflow and negative/zero chunk sizes. Global persistent tile key 64-bit signed; keep **relative local camera/GPU coordinates** bounded/translated to avoid precision loss. Even 64-bit may overflow under extreme external input, so enforce configured world bounds.
- Layer and chunk metadata owns revision, not a hidden mutable pointer into Canvas. On delete, redo, reimport, atlas repack, world rebase or tileset change, invalidate/cook only affected boundaries and dependent neighbors; fix idempotency and stale generation issues.

## 4. Orthogonal, isometric, staggered and hexagonal grids
- **NECESSARY baseline candidate** orthogonal square/rectangle tile grid and parallax; projection types `ISOMETRIC`, `STAGGERED`, `HEX_AXIAL` are IMPORTANT but **not** implicitly required for first coding slice without approved scope.
- For isometric/staggered/hex, define precise grid-to-world/world-to-cell, tie-breaking at edges, half-cell stagger parity, coordinate handedness, tile anchor/height offsets, projection reference under rotation and camera DPI snapping. Hex cube/axial/offset conversions require negative/parity tests; no fudged square grid collisions.
- Sort policy must preserve TWO-01 painter semantics: layer-order, stable cell/instance submission, optional Y/depth sort only where authored/required. Large overlapping tall tiles can span chunks, so conservative culling and bounds must include overlap and prevent visible boundary popping.
- Parallax `ParallaxLayerV1`: per-axis factors, infinite scroll/repeat if explicitly authored and seam-safe, camera reference, layer mask, fixed decimal semantics. Screen DPI zoom changes do not alter world collision coordinates. Parallax is purely render transform unless authored as true world geometry.
- Animated tile frame/timing link is **TWO-03** semantic reference, not second animator. Static map serialization must remain valid without the animation component.

## 5. World streaming, latency and memory pressure
- Streaming is **demand-driven and bounded** by camera/visibility/priority, plus optional player future trajectory: visible chunk ring, prefetch ring, load priority, hysteresis, maximum jobs/bytes/time, per-layer dependency graph and reason-coded metrics. No unbounded speculative world generation or write-on-camera “world persistence.”
- Proposed state machine `UNLOADED -> REQUESTED -> FETCHING -> VALIDATING -> DECODED -> COOKED/READY -> SUBMITTED -> VISIBLE`, with `CANCELLING/FAILED/EVICTING`. State transitions carry Map/Chunk/Layer/revision/device generation and cancel tokens. Missing data strategy explicit: distinguish truly empty chunk, unavailable/offline, corrupt and canceled. NEVER silently treat a corrupt collision-bearing chunk as empty walkable world.
- Atomic persistence via DATA-04 journal + DATA-05 cooked cache; transactional tile edits update dirty chunk and seam neighbors and must invalidate cached Canvas batches/physics metadata atomically with revision receipts. **Render visibility and physics activation** must share acknowledged generation/cutover contract (or adopt a safe boundary state); no rendered tile/solid collision from different revisions that permits a player to pass through a wall.
- Lifecycle on teleport/world rebase/map unload/camera resize/network rollback/cooked chunk corruption: cancel stale requests, fence-retire TWO-01/GFX-03 GPU tile batches, preserve last-good immutable world snapshots, do not delete unapplied dirty edits or write incomplete data. Background save and crash recovery require source-of-truth DATA-04 record.
- Bounds: resident chunk count/tiles, CPU decoded bytes, compressed disk/page sizes, outstanding requests, GPU tile instances/atlas residency, culling work, cook budget, load time and frame p50/p95/p99; unknown VRAM on Web is UNKNOWN, not guessed. Choose LRU or clock-like evictions with protected “currently visible/dirty/physics-critical” set; never evict dirty uncommitted source.
- WebGL2 fallback uses TWO-01 bounded sprite batches and CPU visibility/chunk generation with no compute/SSBO dependence; WebGPU/Metal/Vulkan/DX12 may accelerate culling/instance plans behind GFX-03 with feature proof, never require dedicated tile compute shader.

## 6. Collision-authoring contract and safety
- Tileset cell metadata supports bounded geometry: axis-aligned rectangles, convex polygons and edge segments (and optional one-way/slope flags) in **stable tile-local units** with transforms for flip/rotate/projection. Hollow/concave require explicit decomposition by physics owner, no invalid self-intersections/zero normals/nonfinite vertices.
- Physics service owns broadphase, narrowphase, authoritative collision contacts and dynamic/kinematic bodies. TWO-02 emits `TileCollisionSnapshotV1` containing map/chunk/layer/tile epoch, transformed shapes, solidity/one-way flags, material IDs, revision and cutover condition; physics acknowledges `CollisionActivationReceiptV1` before gameplay treats the region as ready. No fake “collision matches” if the world is rendered but physics not integrated.
- Navigation graphs/waypoints, pathfinding, destructible object gameplay, spawn triggers and network authority remain external; source layer metadata may reference owner contract but not implement those systems. Avoid reusing sprite visual bounds as collision shapes.
- Multi-layer collision precedence and one-way platform rules must be specified; collision geometry changes atomically across seam/wall boundary. Missing critical chunk -> safe **BLOCKED_PENDING_PHYSICS** or controlled loading gate, not silently open world.

## 7. Terrain painting, auto-tiling and authored rules
- `TileTerrainRuleSetV1`: bounded tileset terrain ID/tags, 4/8 neighbor bitmask or Wang edge/corner constraints, deterministic tie-break, explicit seed and variant weights with safe normalization. Radius/local dependency and dirty-neighbor invalidation ensure no seams between chunks/camera loads.
- Brushes: stamp, line, rectangle/fill, palette, object placement, erase, flood-fill only under explicit total visited-cell/time/area quota; long operations become staged/cancelable chunk batches with preview and DATA-04 rollback. No infinitely recursive fill.
- GPU shading can add aesthetic variety but tile selection/persistent geometry must not depend on nondeterministic GPU random or camera distance, else edits/saves and multiplayer replay mismatch. Procedural world generation with terrain biomes is OPTIONAL FUTURE not required to close TWO-02.
- Rule migration and external source edits map external terrain tags into stable internal IDs, not copy arbitrary JS scripts from Tiled. Rule changes invalidate neighboring chunks deterministically. Autotile partial/unsupported cases warn rather than choose arbitrary unsafe tile.

## 8. Tiled/LDtk interop, licensing and untrusted input
- **Tiled** tool is GPL (upstream `src/tiled` and plugins), while **libtiled** and TMX rasterizer are BSD-2-Clause in upstream `COPYING`. *External map file compatibility is not linking the GPL editor into proprietary/unknown-license engine.* No code or tool installed by research. Respect license for exact imported or redistributed source.
- Tiled **TMX and JSON** support finite/infinite maps, `chunk` arrays, external tileset `tsx`, tileset `firstgid`, base64+zlib/gzip/zstd, orientation-specific diagonal/hex flip flags in the top FOUR bits of 32-bit GID. Strip flags before resolving tileset/local ID; hex 60/120-degree rotation differs from orthogonal diagonal flip; GIDs map-relative and must be converted to stable internal TileId. Map layer order is rendering order. Validate compression expansion limits, decompressed bytes width*height*4, overlapping/duplicate chunks, negative offsets, UTF-8 and property names.
- **LDtk** MIT editor. JSON schema version 1.5.3 reference includes stable `iid`, tilesets/intgrid/auto layers and optional external `.ldtkl` files referenced by `externalRelPath`; external layer files must resolve **within project sandbox** and import must be transactional, offline and fail-closed for missing/renamed/rogue paths. LDtk auto-layer rules and Tiled Wang sets have distinct semantics: exact translation or an explicit unsupported warning, not pretend bitwise equivalence.
- External Tiled/LDtk editor may be used **separately** by an artist, but the engine must offer its own map edit semantics and avoid being locked to those tools. Do not copy sample sprites or maps whose copyright is unknown. All texture/data/tileset and source metadata goes through DATA-03; no embedded code/JS/Lua execution, host path traversal, remote URL, symlink escape or XML entity/zip bomb.
- Godot TileMapLayer is a **comparative design warning**, not adopted code. Its official docs mention rendering/physics quadrant batching and a **16-bit signed serialized tile coordinate limit**, including wrap outside `[-32768,32767]`. Stormline must explicitly test far coordinates and avoid hidden signed-16 range in canonical map persistence; GPU offsets remain local.
- Compare independent Tiled/LDtk sources via published file formats and own parser or vetted minimal library only after version/license/security evidence. Not a plugin requirement and no source licensed by assuming a map file is “free art.”

## 9. Unified Editor/CLI/MCP security
- Readonly semantic `InspectTileMap`, `InspectTileSet`, `InspectTileChunk`, `PreviewMapStreamBudget`, `PreviewTerrainPaint`, `InspectCollisionAuthoring`, `GetMapStreamReceipt`. Preview only ESTIMATED, not measured streaming.
- Mutation commands `StageTileEdit`, `StageTileBatch`, `StageTerrainRules`, `ValidateTileMapTransaction`, `CommitTileMapTransaction`, `CancelTileMapOperation`. Project-scoped roles, map/layer/cell range limits, expected revisions, per-batch quota, DATA-04 journal/rollback and auditable diff. Explicit import and license validation via DATA-03; no direct host file or remote asset path access.
- Rejections typed `COORDINATE_OUT_OF_BOUNDS`, `INVALID_ORIENTATION`, `STREAMING_BUDGET_EXCEEDED`, `CHUNK_INTEGRITY_FAILED`, `PHYSICS_GENERATION_NOT_ACKED`, `SOURCE_RIGHTS_DENIED`, `IMPORT_SUSPICIOUS_PATH`, etc. Include safe stale revision/owner, retryability and fallbacks, not leaked paths or passwords.

## 10. Experimental (optional) research: SWSP
**Stormline World Seam Predictor (SWSP)**, optional PROVE-OR-DROP: conservative camera/actor-motion-based chunk prefetch, plus neighbor seam integrity and authored collision activation fence. Compare standard radius prefetch + hysteresis/LRU. Reject if added complexity, CPU/power overhead, cache overfetch or map pop/replay regression. Not claimed novel, faster or implemented.

## 11. Code activation gates
Owner-approved release class, DoD and exact 1.0 content; implemented and audited TWO-01 & DATA-04 mandatory code, API agreement with DATA-03/05/PHYS/GFX, exact .tmx/.ldtk parser versions and rights, chunk file schema/checksum/migration, original fixture maps and hardware native/Web platforms, no HIGH/CRITICAL, security fuzz, measured frame+disk+VRAM+collision correspondence, exact C++ paths/ABI/Context Lock SHA-256. **Issue #38 remains OPEN/BLOCKED and all 80 WOs executor_ready=false.**

## Official and primary technical sources (research, not integrated)
- Tiled editor current capabilities/infinite maps/auto tiling: https://www.mapeditor.org/
- Tiled upstream distinct license inventory (GPL editor, BSD-2-Clause libtiled): https://github.com/mapeditor/tiled/blob/master/COPYING
- Tiled TMX map chunks, compression options: https://docs.mapeditor.org/en/latest/reference/tmx-map-format/
- Tiled JSON tilemap/tileset source: https://github.com/mapeditor/tiled/blob/master/docs/reference/json-map-format.rst
- Tiled Global Tile IDs 4 flag bits and hex rotation: https://docs.mapeditor.org/en/stable/reference/global-tile-ids/
- Tiled Wang Sets / terrains, procedural painting: https://docs.mapeditor.org/en/stable/manual/terrain/
- LDtk MIT LICENSE: https://github.com/deepnight/ldtk/blob/master/LICENSE
- LDtk JSON spec with optional separate .ldtkl levels and stable IID: https://github.com/deepnight/ldtk/blob/master/docs/JSON_DOC.md
- Godot 4.6 TileMapLayer batching/collision quadrant, serialized signed-16 cell-coordinate limitation: https://docs.godotengine.org/en/4.6/classes/class_tilemaplayer.html
- W3C WebGPU constraints and device capability negotiation: https://www.w3.org/TR/webgpu/
