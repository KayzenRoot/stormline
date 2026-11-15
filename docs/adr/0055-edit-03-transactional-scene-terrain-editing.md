# ADR-0055 — Semantic Scene Edits, Versioned Prefab Overrides and Non-destructive Terrain Layers

**STATUS PROPOSED / NOT OWNER APPROVED / NOT ADOPTED** | 2026-11-15 | research #260, Work Order NLE-P00-WO-002-EDIT-03, future coding #70 OPEN/BLOCKED. BASE `e0463818e6dda79cabd26e49f81eca38cd507782`. Code license NLE-D009 OPEN, release class UNDECIDED, exact DoD/stack unapproved.

## Context
A professional engine editor must let authors alter hierarchy, inspector properties, transforms, prefabs, world streaming cells and terrain without losing authored state after save, crash, recomposition or regeneration. The formal predecessors **EDIT-02 and WORLD-04** are only research documented/ADRs PROPOSED. DATA-04 owns canonical source serializer/CAS, WORLD-01 owns entities and generational IDs, WORLD-04 owns terrain/biome/streaming model, and GFX owns viewport. A second mutable scene graph in the editor or GPU-only terrain source would cause drift and data corruption. Vendor Unreal/Unity/Godot/OpenUSD patterns are references, not licensed importable code.

## Proposed architectural decision, not implementation authorization
Define an original **typed SceneEditCommand/Preview/Transaction/Receipt** orchestrator. Every authoring command targets stable EntityId+generation, Prefab AssetId/InstanceId or TerrainCellId+revision with explicit document revision/permission, and produces a **semantic before/after diff** under bounded memory. Render viewport and hierarchy UI are nonauthoritative projections; DATA-04 commits canonical source and WORLD-01/WORLD-04 validate their own invariants. UI host undo remains EDIT-01; scene history is scene-scoped with safe inverse/rebase only if expected revision still matches; atomic cross-file updates require journal/rollback/recovery, no fake distributed ACID.

**Transforms:** local/parent/world, explicit pivot and snap, quaternion normalization, parent inverse tolerance and large-world origin shifts, reject NaN/Inf and singular transform operations. Preview is cancellable and one grouped transaction at release, no accidental repeated parent-child transform. Picking includes frame/cell/world generation to reject stale GPU results; GFX resource never owned by EDIT-03.

**Prefabs:** versioned definition AssetId, nested stable child IDs, ordered overlay/override patch and provenance, explicit apply/revert/rebase with conflict and source integrity validation. Circular nested references denied. Edit an instance does not mutate source or siblings unless explicit elevated "apply to source" confirmation. Future foreign USD layer interoperability is optional adapter, not required native format.

**Terrain:** WORLD-04 canonical tiles; EDIT-03 authors **non-destructive stack of manual/procedural delta layers** with deterministic stroke samples/seed, idempotency, neighbor seams and tile revisions. Separate sculpt heights, weightmap/splatmap, foliage density/instances, erode/spline/holes. Source layers persist under DATA-04; GFX LOD/height mesh, preview splat textures and HLOD are regenerable caches. WORLD-05 procedural graph owner, not reimplemented in editor. Rebuild cannot silently erase manual layers. Heightfield limitations vs voxel caves explicit.

**Collaboration:** local-first single writer per scene/cell with DATA-04 expected source revision and clear readonly/conflict state; remote collaborative OT/CRDT/fan-out **FUTURE separate approval**, no promise transparent multiwriter correctness. AI/MCP/CLI invoke same permissioned semantic operations and explicit user approval for destructive baking, mass erase and prefab source writes; no generic shell or invisible filesystem effects. Malformed assets, plugin scripts and import pipelines are hostile input, quota/manifest/schema and VFS grants enforced by owners.

## Alternatives and outcomes
| Candidate | Attraction | Issue / verdict |
|---|---|---|
| Editor duplicates ECS hierarchy and writes raw scene bytes | simple first prototype | diverging entity refs/source of truth, undo corruption; **reject** |
| Per-frame mouse delta writes directly to scene | low latency | unbounded history, race on GPU picking and crashes; **reject** |
| GPU terrain preview texture as only persisted state | fast painting | unrecoverable device loss and nonportable format; **reject** |
| Flatten generated terrain on every edit | easy mesh output | destroys provenance and reversibility, lacks prefab-style override; **reject default** |
| Always source-edit prefab when moving instance | globally consistent | destroys sibling isolation, surprises author; **reject** |
| OpenUSD composition as *only* Stormline native scene format | sophisticated layers | complexity/portability and legal/transitive overhead for first scene edits; **not selected** |
| Original semantic command transaction+versioned prefabs+terrain layers | deterministic audit/rollback, owns no second data store | preview/commit consistency and source IO tests required; **leading proposal** |
| Realtime multiplayer scene collaboration now | appealing creativity | distributed conflicts, locks, costs/security and DoD expansion; **FUTURE** |

## Adoption/stop obligations
Future actual code requires owner-approved source data contracts/WORLD-04 concrete terrain model and selected GFX/Editor backend, verified DATA-04 atomicity and migration, schema/asset/instance stable IDs and reflection owner, original artwork/template rights, tagged third-party license analysis, real 2D+3D/terrain save-reopen-undo/redo and bad input/runtime test evidence across approved Windows/Linux/macOS tiers, input/accessible keyboard and real performance baselines. HIGH/CRITICAL data corruption, path escape, scene loss, unauthorized mass edits, leaking private assets or known ASan failures block advancement. **ADR-0055 remains PROPOSED when merged; all 128 tests FUTURE/NOT EXECUTED, 80 coding packets BLOCKED.**
