# WORLD-03 — Typed Spatial Query, Residency, Origin and Streaming Transaction API v0.1

**Research #165 | WO NLE-P00-WO-002-WORLD-03 | future code #43 BLOCKED.**  
This is a versioned semantic proposal, not a compiled C++ ABI, GPU kernel, JSON wire contract, runtime scheduler API or active MCP service.

| Proposed type | Required meaning and fields | Hard invariant / owner |
|---|---|---|
| `WorldSpatialContextV1` | ProjectId, WorldId/WorldInstanceEpoch, scene source revision, global units, origin epoch, index geometry kind | WORLD-01/02 and CORE-05 authority, no cross-world alias |
| `SpatialCellIdV1` | canonical integer grid level+coord X/Y/Z or X/Z, deterministic negative floor division, world/source key | invariant under camera/origin rebasing; signed overflow rejects |
| `CellDependencyManifestV1` | CellId, DATA-05 cooked source AssetIds/hashes/deps, SceneId/PrefabId revision, content safety/rights | DATA-02/04/05 source owners, NO raw arbitrary URL |
| `SpatialBoundsV1` | finite global-space AABB/sphere/capsule candidate, entity/source id and border overlap representation | checked global units; no physics contact claim |
| `SpatialQueryV1` | world/epoch, shape, owner role, layer masks, exact candidate policy, bounded limit/page cursor, revision | `COMPLETE / MAY_BE_INCOMPLETE`, no foreign world data |
| `SpatialQueryReceiptV1` | unique qualified EntityGuid/SceneInstanceId hits, bounds refinement, queried resident/missing cell counts, completeness and epoch | deterministic stable sort only on request, false negatives forbidden when COMPLETE |
| `SpatialInterestSourceV1` | owner/capability, source id, global pose/velocity, shape and horizon, expected world tick, priority and required sim pins | NET/PHYS/AI/GAME authority for critical scopes |
| `CellPriorityPlanV1` | required pinned/prefetch/optional/evict eligible, per source reason, bounds, quota, plan generation, hysteresis | no eviction of live critical lease, plan may be rejected |
| `CellStreamStateV1` | ABSENT/REQUESTED/FETCHING/DECODED_VALIDATED/CPU_STAGED/GPU_STAGED/READY_TO_COMMIT/ACTIVE/COOLING/EVICTING/FAILED/CANCELLED | legal transitions, no ACTIVE before owner ACKs |
| `CellRequestTokenV1` | WorldEpoch+CellGeneration+PlanGeneration+AssetRevision/Hash, cancellation and retry group | obsolete async completion cannot resurrect unloaded cell |
| `CellLeaseV1` | owner type/id, cell gen, pin reason (physics/AI/renderer/net/audio/quest), expiry/ref token and fence | no negative/ref stolen; release only by owner, lockfree policy TBD |
| `CellCommitIntentV1` | CPU staged asset manifest, source CAS, WORLD-01 entity intents, PHYS collision ACK, GFX GPU staging, barrier tick, idempotency | DATA-05 I/O, WORLD-01 ECS and CORE tick are authoritative |
| `CellPublicationReceiptV1` | published cell/revision/epoch and completeness, per owner readiness, source vs runtime state, recovery-needed | no invisible collider when ACTIVE says ready |
| `WorldOriginShiftIntentV1` | old/new global offset+origin epoch, CORE-05 proposal, per owner ACK, precision deltas, rollback | no unilateral transform/physics/network shift |
| `StreamingBudgetV1` | CPU ms/tick; I/O bytes, decompressed stage bytes, pending tasks, resident cell/Entity pins, GPU VRAM as external receipts | bounded and versioned target, no invented numeric pass |
| `StreamingQualityReceiptV1` | plan, actual/ESTIMATED/UNKNOWN timings, p50/p95/p99 phases, stalls, peak bytes, miss count, source and hardware tags | measured vs predicted explicit; no 60fps claim |
| `WorldStreamingPolicyEditV1` | project/source version, expected DATA-04 CAS, capped cell size/prefetch/priority/lease rules and actor permissions | AI-native scoped edit, not NET client world control |

## Proposed lifecycle and safe publication
`InterestSources -> ComputeCellPlan -> IssueData05Requests -> ValidateHash/SourceRevision/Generation -> StageCPU/OptionalGPU -> PrepareWorld01+PHYS+GFX owner intents -> CORE tick commit barrier -> Publish ACTIVE snapshot -> Cooling -> Check lease/fence+epoch -> Evict and dispose after owner ACK`. Source CPU/GPU/PHYS publication cannot be blindly treated as a single atomic disk+memory transaction; pending/last-good/safe barrier semantics are mandatory.

## Query and origin rules
- `SpatialQuery` result from index on unloaded cells must carry missing coverage `MAY_BE_INCOMPLETE`. An `EXACT` request with unstreamed cells either loads under quotas or rejects with `EXACT_QUERY_REQUIRES_RESIDENCY`; must **not** return a false empty “all clear.” Loaded-cell query results refined by actual geometric bounds; broadphase false positives are acceptable only if labeled candidates.
- Cell membership owner `CellId` persists globally and a large overlapping entity appears once in a deduped query. Origin rebase only changes local render/physics representation with owner ACKs and epoch; persisted cell IDs and EntityGuids unaffected. Remote client can only declare bounded/untrusted hints, not authorize critical pins or replicated content.
- `ACTIVE` is an explicitly versioned collection of required assets, entity lifecycle and collision readiness acknowledgements for requested completeness. Optional visual GPU staging may lag only if the quality receipt declares this and gameplay completeness remains truthful.
- `EvictCell` with leases/critical owners returns `PINNED` and must not remove collision/world data. Headless server skips GPU entirely. Cancelled work that arrives late is rejected using WorldEpoch+RequestGeneration.

## Editor/CLI/MCP parity
Readonly: `InspectSpatialCells`, `QuerySpatialInterest`, `InspectInterestSource`, `PreviewStreamingPlan`, `InspectCellLeases`, `InspectCellReadiness`, `GetWorldOriginState`, `GetStreamingQualityReceipt`. Mutations only `StageStreamingPolicyEdit`, `ValidateStreamingPolicyEdit`, `CommitStreamingPolicyEdit`, `CancelStreamingPolicyEdit`, all limited to project/world and DATA-04 expected revision with role+quota. No arbitrary memory/storage IO/network coordinates/shader/server physics authority.

## Typed errors
`WORLD_SPATIAL_EPOCH_STALE`, `WORLD_CELL_COORD_OVERFLOW`, `WORLD_CELL_SOURCE_MISSING`, `WORLD_CELL_CYCLE_DEPENDENCY`, `SPATIAL_BOUNDS_INVALID`, `SPATIAL_QUERY_INCOMPLETE`, `EXACT_QUERY_REQUIRES_RESIDENCY`, `SPATIAL_QUERY_LIMIT`, `SPATIAL_QUERY_ROLE_DENIED`, `CELL_REQUEST_STALE_GENERATION`, `CELL_ASSET_HASH_MISMATCH`, `CELL_CONTENT_REJECTED`, `CELL_DECOMPRESS_LIMIT`, `CELL_IMPORT_RIGHTS_DENIED`, `CELL_STAGE_BUDGET_EXCEEDED`, `CELL_COMMIT_ACK_PENDING`, `CELL_PARTIAL_PUBLICATION_DENIED`, `CELL_LEASE_PINNED`, `CELL_LEASE_INVALID`, `CELL_EVICTION_FENCE_PENDING`, `CELL_RETRY_BACKOFF`, `CELL_IO_UNAVAILABLE`, `CELL_DEVICE_LOST`, `WORLD_ORIGIN_ACK_PENDING`, `WORLD_ORIGIN_EPOCH_MISMATCH`, `WORLD_ORIGIN_PRECISION_EXCEEDED`, `STREAMING_BUDGET_UNSATISFIABLE`, `STREAMING_SAFE_LOADING_BARRIER`, `STREAMING_PROJECT_CAPABILITY_DENIED`, `STREAMING_POLICY_CAS_CONFLICT`, `CANCELLED`, `RECOVERY_REQUIRED`. Safe diagnostics include project/world/scene and task epoch, retryability and redacted resource IDs; never private host paths/secret tokens.

## Before selecting code
Owner-approved 1.0 release class, ADR-0028, Scope/DoD and numeric budgets, implemented/audited WORLD-02 and DATA-05 predecessor code, CORE-05/06/WORLD-01/PHYS/NET/GFX contracts, platform target list, exact C++ ABI/types/file inventory, raw SHA-256 Context Lock and native/Web/headless + security/perf evidence. None satisfied now; #43 remains OPEN/BLOCKED.
