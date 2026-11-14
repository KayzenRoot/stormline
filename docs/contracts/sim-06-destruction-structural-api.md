# SIM-06 — Destruction, Structural State and Effect Receipts: Semantic API v0.1

**Research #189 | WO NLE-P00-WO-002-SIM-06 | Future coding #51 OPEN/BLOCKED.** **PROPOSED SEMANTICS ONLY**, not a compiled C++ ABI, persisted wire layout or adopted SDK.

## Typed source/runtime contract
| Contract | Fields (candidate) | Authority / validation |
|---|---|---|
| `DestructibleAssetV1` | ProjectId, AssetId, source revision/hash/rights, material/Chunk/Bond graph, collision proxy/LOD references, physical units | DATA-03/04/05 validated/cooked; finite manifest, no unconstrained mesh bytes |
| `FractureCookManifestV1` | importer/cooker version, seed/recipe, source hash, ChunkGuid/BondGuid indices, mass/inertia/convex hull hashes, content sizes, capability tier | immutable cooked derived asset; bounded counts and checksum, versioned migration |
| `MaterialResponseV1` | profileId/revision, toughness per material, thresholds, directional toughness, supported damage types, crack stages, impulse clamps | finite nonnegative units, no arbitrary script, GAME controls actual hit authority |
| `DestructibleHandleV1` | WorldId/WorldEpoch, EntityGuid and generation, source revision, destructible slot/generation, OriginEpoch | reject reused target, foreign world and stale origin |
| `ChunkHandleV1` | parent DestructibleHandle, ChunkGuid, generation, PHYS BodyHandle or immutable anchor/cluster ID, source collision revision | SIM-02 alone approves physical body/constraint; no native pointer |
| `BondStateV1` | BondGuid, active/broken/softened stage, cumulative energy, neighbor chunk IDs, break provenance TickId | bounded monotonic damage schema with explicit repair/migration policies |
| `DamageIntentV1` | EventId, producer/authority epoch, target handle, TickId, hit point/normal, impulse/energy with units, area/radius/type and declared action revision | only GAME/NET authorized or SIM-02 trusted contact-derived event, idempotent, finite and quota |
| `FracturePlanV1` | parent source epoch, damaged bonds/chunks, staged PHYS bodies, expected WORLD cell leases, expected collider/nav/rebuild receipts, cost estimate | internal only, no direct mutation, resource quotas and fail closed |
| `PhysicsFractureAckV1` | WorldEpoch, Body/Constraint generations, accepted BodyHandle list, collision source revision, post-step status | authoritative SIM-02 acknowledgment, never inferred from VFX |
| `WorldTopologyAckV1` | CellId/lease, WORLD-04 terrain revision, collider revision, NavTopologyEpoch revocation/rebuild, publish barrier | WORLD-03/04, SIM-02 and SIM-05 agreement; unready marks region unavailable |
| `DestructionReceiptV1` | EventId, TickId, requested vs committed chunks/bonds, PHYS and WORLD/Navigation ACK hashes, state/status, authoritative structural revision | immutable post-barrier proof with completeness and stable pagination |
| `VisualDebrisIntentV1` | DestructionReceipt reference, source FX asset/rev, random seed, effect lod/tier, capped particle/mesh/decal/light/audio requests | client VFX only, GFX-08/GFX-05/GFX-06/AUD owners, no damage or collision |
| `ImpactMarkV1` | parent surface/generation, impact TickId, material/decay policy, source triangle/surface mapping ID, visual-only or owned topology edit ref | GFX-05 cosmetic or WORLD-04 authored persistent edit; never GPU triangle pointer |
| `StructuralSnapshotV1` | world/cell/entity revision, ordered broken bonds/chunk activation, transforms/body generation mapping, source hashes, checkpoint cursor | DATA-04/NET authority, source consistency, migration/recovery/rollback policy |
| `DestructionCapabilitiesV1` | 2D crack decal, prefracture 3D, max physical chunks, terrain edits, supported platforms/precision, headless, VFX tiers | measured supported features only; no universal GPU/voxel promises |
| `DestructionErrorV1` | typed code, source/epoch, rejected reason, last safe state, recoverability, bounded redacted diagnostics | never claim physics commit success without PHYS receipt |

## Semantic operations and safe stages
1. `StageDestructibleProfile(asset, expectedSourceRevision, principal)`: validate schema, material, rights/cook candidates and DATA-04 CAS; dry-run and journal via common Editor/CLI/MCP kernel.
2. `StageFractureCookRecipe(recipe, expectedRevision, principal)`: limited offline-only build through DATA-03/05; no raw path or trusted network fetch from MCP.
3. `AttachDestructible(entity, sourceHash, worldEpoch)`: validated prefab/source and PHYS readiness, generation handle at safe world barrier.
4. `SubmitDamageIntent(target, tick, eventId, principal)`: **privileged GAME/NET service only** with dedup; external editor authoring API cannot use it to kill live NPCs or modify unowned assets.
5. `EvaluateDamageAtTick(world, tick)`: internal deterministic ordered bounded bond graph traversal; outputs `FracturePlan`, not direct solver callback writes.
6. `StageFracturePhysics(plan, expectedPhysEpoch)`: SIM-02 validates body mass/shape and constraints at pre-step barrier, returns actual ack.
7. `StageWorldTopologyAndNavInvalidation(plan, expectedCellEpoch)`: WORLD-03/04 and SIM-05 reserve/revoke safe traversability; collision/nav asset source version checks.
8. `CommitStructuralChangeAtBarrier(plan, acks)`: coordinator publishes coherent state only after all mandatory owner ACKs; otherwise typed PENDING/ABORT with explicit last safe collision state.
9. `ReadDestructionReceipts(world, cursor, maxRecords, principal)`: immutable paged, redacted to NET/GAME role, dropped-event counts and revision hash.
10. `QueueCosmeticResponse(acceptedReceipt, fxProfile, platformCapabilities)`: bounds and sends nonauthoritative GFX-08/GFX-05/AUD requests; visually degraded but GAME result retained.
11. `StageImpactMarkOrTerrainEdit(surface, expectedTerrainRevision, principal)`: cosmetic GFX-05 mark or WORLD-04 authored edit via transactional review, never untrusted immediate collision change.
12. `SnapshotStructuralState/RestoreStructuralState(sourceRevision, cursor)`: only at accepted authoritative checkpoint, idempotent replay/journal recovery; verify legacy source revision and safe missing chunk migration.
13. `DetachDestructible(handle)`: deferred retirement after PHYS/GFX/WORLD leases complete, invalidate generation and cancel jobs.

## Error catalog and checks
`INVALID_ASSET`, `BAD_SOURCE_RIGHTS`, `MALFORMED_CHUNK_GRAPH`, `NONFINITE_IMPULSE`, `NEGATIVE_MASS`, `INVALID_CONTACT_OR_NORMAL`, `UNAUTHORIZED_DAMAGE`, `DUPLICATE_EVENT_CONFLICT`, `STALE_WORLD_EPOCH`, `STALE_HANDLE`, `STALE_ORIGIN_EPOCH`, `SOURCE_REVISION_MISMATCH`, `COLLIDER_NOT_READY`, `NAV_INVALIDATION_PENDING`, `CELL_UNLOADING`, `PHYSICS_REJECTED`, `PARTIAL_COMMIT_ABORT`, `BUDGET_EXCEEDED`, `UNSUPPORTED_RUNTIME_FRACTURE`, `VFX_CAPABILITY_UNAVAILABLE`, `DECOMPRESSION_LIMIT`, `MIGRATION_CONFLICT`, `INTERNAL_FAILURE`.

## Formal invariants / future proof obligations
- Each accepted `DamageEventId` produces <=1 authoritative structural commit; duplicate identical replays receive same receipt, contradictory duplicates fail. COMMIT requires PHYS + WORLD/nav readiness under same source epoch, otherwise fail closed and persist no false break.
- Cosmetic GPU/particles are not part of replay-physics truth; headless state invariant under graphics tier. When resource budget exhausted, a safe structural simplification must be explicitly represented, not silently drop gameplay-critical shards.
- Persistent structure and terrain changes must be crash-recoverable, replay/version/rights checked, with no direct partially saved physics/scene state.
- Proposed schemas are not wire ABI or field layout. Future implementation selects exact binary version, endian, migration, numeric budgets, error semantics, rollback and test vectors, independent of native Blast/Jolt/OpenVDB types.
