# WORLD-01 — Versioned Entity, Component, Reflection and Deferred Command API v0.1

**Research issue #159 | WO NLE-P00-WO-002-WORLD-01 | Future coding #41 BLOCKED.** Semantic design only. Not a binary C++ ABI, serializer, runtime ECS library, memory layout or executable MCP server.

| Conceptual type | Core proposed fields | Invariants / owner |
|---|---|---|
| `WorldIdentityV1` | ProjectId, logical WorldId, fresh world_instance_epoch, world source revision, authority tier and quotas | world scoped, no runtime handle reused across instances |
| `EntityGuidV1` | stable portable global/project/world GUID+schema revision and DATA-04 provenance | persisted in scenes, not local runtime pointer/slot |
| `EntityHandleV1` | WorldInstanceEpoch, slot and generation, invalid sentinel | ephemeral runtime only, stale/ABA rejected, generation overflow slot retire |
| `EntityLifecycleV1` | ALIVE/DESTROY_REQUESTED/TOMBSTONED/RETIRED + tick/revision | monotonic state/owner approval, destroy once |
| `EntityGuidResolveReceiptV1` | GUID to current Handle or MISSING/UNLOADED/DELETED/STALE/WRONG_WORLD | no implicit cross-world reference |
| `ComponentTypeIdV1` | stable type identity/version independent of C++ ABI/typeid | DATA-02 provenance, explicit collision reject |
| `ComponentSchemaV1` | TypeId, schema version/hash, fields, units, defaults, rights, storage hint, ctor/move/dtor/type traits | safe reflection; DATA-04 serialization/migration owner |
| `ComponentFieldV1` | field stable ID/type/range, serialized/replicated/secret flags and allowed writers | no arbitrary pointer/plugin code/unsafe import |
| `ComponentStoragePolicyV1` | TABLE_DENSE/SPARSE_STABLE candidate, page/budget/relocation epoch | benchmark/DoD gate before selecting actual layout |
| `EntityQueryDescriptorV1` | include/exclude/optional TypeIds, changed-since epoch, world selector, stable sort option, pagination | bounded, protected fields and logical query epoch |
| `EntityQuerySnapshotV1` | result handles/validity epoch, read/write component access rights, generation and snapshot type | no retained raw pointer across structural command |
| `SystemAccessV1` | read/write sets, thread/work-group, tick, declared transient deps | CORE scheduler owns locks/barrier/jobs |
| `EntityCommandBufferV1` | project+world instance, issued tick/issuer/sequence, bounded create/destroy/add/remove/set commands and expected generations | validate, deterministic merge ordering and atomicity unit explicit |
| `EntityCommitReceiptV1` | applied transaction ID, source revision, live world epoch, created GUID→Handle, failed/partial diagnostics, changed type epochs | no silent partial world corruption |
| `EntityLifecycleReceiptV1` | create/destroy/change entry with TypeId, EntityGuid, world rev, owner, tick, reason and idempotency | consumers GFX/PHYS/NET validate before access |
| `EntityTransactionV1` | project/world, expected DATA-04 revision, staged typed patches, identity and rights, journal token | staged CAS with rollback and audit |
| `EcsQualityReceiptV1` | actual/predicted/UNKNOWN entity count, archetypes/pages/bytes, query p50/p95/p99, structural stalls and invalid refs | no fabricated performance metrics |

## Lifecycle and safe reference model
`RegisterComponentSchema (validate type+rights) -> CreateEntity (GUID and fresh Handle) -> Add/UpdateComponents (type-specified) -> QuerySnapshot (borrow epoch) -> StageEntityChange -> CommitAtTickBoundary (CORE barrier) -> PublishLifecycleReceipt -> DestroyRequested -> Tombstoned (invalidate handle) -> Retired (safe destructor/slot)`. World unload/epoch reset invalidates all runtime handles; persisted GUID may resolve again on a future reload to a **new** handle if same logical entity remains.

## Transactional and threading semantics
- A query view is bounded by `WorldEpoch+QueryEpoch+ComponentAccessMode`. Read-many/write-exclusive access enforced by declared `SystemAccessV1`, with CORE job scheduler integration; calls are forbidden after a structural-commit barrier. Even stable-address sparse components cannot leak unsynchronized mutable access.
- `EntityCommandBufferV1` stores typed commands, not arbitrary object pointers. It checks world/project/capability, expected revision, existing slot generation and component schema, quota, duplicate GUID, ordering conflicts and a predeclared atomicity guarantee before publication. Source journal/undo/redo handled through DATA-04 with a separate receipt; no claim file durability just because runtime applied.
- Default iteration order **unspecified**. Explicit `DETERMINISTIC_GUID_ASC` is a candidate ordered snapshot with measured CPU cost, no promise that unordered storage can replay deterministic physics. Component change filters have documented epochs; write permission does not equal actual changed value without proper dirty tracker.
- Snapshot/restore includes GUID+schema-versioned fields, not C++ padding/pointers/slot. Unknown fields/version only by migration policy, never byte-level reinterpretation or hidden plug-in eval. Cross-world identity must be qualified and permitted.

## Editor/CLI/MCP semantic parity
Readonly: `InspectEntity`, `ListComponentSchemas`, `ResolveEntityGuid`, `QueryEntitiesPage`, `PreviewEntityDiff`, `InspectEntityLifetimeReceipt`, `InspectEcsQualityReceipt`. Mutation: `StageEntityCreate`, `StageComponentPatch`, `StageComponentRemove`, `StageEntityDestroy`, `ValidateEntityTransaction`, `CommitEntityTransaction`, `CancelEntityOperation`. Project+WorldId+expected source revision required, per-field ACL and operation quotas, no direct memory/host/URL access; simulation authority forbids arbitrary gameplay edits. Preview labelled ESTIMATED, not a running server.

## Typed errors
`WORLD_EPOCH_STALE`, `WORLD_SCOPE_DENIED`, `ENTITY_HANDLE_INVALID`, `ENTITY_HANDLE_GENERATION_MISMATCH`, `ENTITY_GENERATION_EXHAUSTED`, `ENTITY_GUID_DUPLICATE`, `ENTITY_GUID_UNRESOLVED`, `ENTITY_WORLD_UNLOADED`, `ENTITY_ALREADY_DELETED`, `ENTITY_LIFETIME_BORROW_CONFLICT`, `ENTITY_COMMAND_CONFLICT`, `ENTITY_COMMAND_BUFFER_LIMIT`, `ENTITY_ATOMICITY_UNAVAILABLE`, `ENTITY_QUERY_EPOCH_STALE`, `ENTITY_QUERY_ACCESS_DENIED`, `COMPONENT_TYPE_COLLISION`, `COMPONENT_SCHEMA_UNSUPPORTED`, `COMPONENT_ALIGNMENT_INVALID`, `COMPONENT_DESTRUCTOR_FAILED`, `COMPONENT_MIGRATION_REQUIRED`, `COMPONENT_FIELD_REDACTED`, `COMPONENT_WRITE_AUTHORITY_DENIED`, `COMPONENT_STORAGE_EXHAUSTED`, `WORLD_CAS_CONFLICT`, `SOURCE_RECOVERY_REQUIRED`, `CAPABILITY_DENIED`, `CANCELLED`. Errors include safe code, stage, world/revision, retryability and redacted diagnostics, not raw pointer/secret.

## Future freeze/DoD gates
Approved ADR-0026, release class and 1.0 Scope/DoD, actual CORE-05 and DATA-04 implementation/merge, selected C++ compiler+Web toolchain+ABI and storage benchmark, stable GUID/handle bit layout, safe schema serialization and cross-world/NET authority, named CPU/memory p95/p99 and stress tests, input fuzz/race sanitizers, exact C++ file paths, fresh Git+raw SHA-256 Context Lock. No current code or 0/80 executor-ready status changed.
