# DATA-02 — Asset Registry API and Transaction Contract (PROPOSED)

**Research WO:** NLE-P00-WO-002-DATA-02 | **Version:** conceptual v0.1 | **Status:** NOT IMPLEMENTED  
**Dependencies:** DATA-01 VFS, CORE-02/03/05/06 contracts; DATA-04 owns general serialization.

This is a **language-neutral semantic contract**, not generated C++ headers or MCP schemas. Future approved implementation must lock public names, ABI, schema and field types.

## Owned opaque types
- `ProjectId`: namespace for IDs and permissions.
- `AssetId`: 128-bit persistent logical identity (UUIDv7 candidate).
- `AssetPath`: validated DATA-01 logical URI path, not host path.
- `AssetRevision`: opaque monotonically comparable revision within an asset.
- `ContentDigest`: `{algorithm, bytes, byte_count?}`, distinct from AssetId.
- `SubassetLocator`: stable in-asset key when importer supports deterministic keys.
- `RegistrySnapshotToken`: project, schema version, change sequence and expiry.
- `OperationId`: idempotency token and recovery correlation ID.

## Proposed operations

| Operation | Input | Output/behavior | Required checks |
|---|---|---|---|
| `GetAsset` | AssetId, snapshot?, capability | AssetDescriptor or typed missing/tombstone/stale | project scope, schema revision |
| `ResolveByPath` | VfsPath, mount generation, capability | AssetId or ambiguous/not found | cannot treat path as ID, collision detection |
| `ListAssets` | bounded filter, cursor and requested fields | stable ordered page | limit output, permission-scoped, no raw paths |
| `GetDependencies` | AssetId, depth and edge filters | bounded typed edges | cycle detection, explicit unresolved edges |
| `AnalyzeImpact` | AssetId, proposed change, snapshot | preview of dependents/rebuild work | time/depth budget; no write side effect |
| `BeginRegistryTransaction` | project, expected snapshot rev, operation ID, actor capability | scoped transaction handle | authorization, idempotence, compare-and-swap |
| `MoveOrRenameAsset` | transaction, AssetId, expected rev, destination VfsPath | stage move, return impact/warnings | DATA-01 permission checks, identity preserved |
| `DuplicateAsset` | transaction, source ID, destination, provenance hint | fresh AssetId, staged file copy | no ID reuse/collision; quotas |
| `SetMetadata` | transaction, AssetId, typed patch/schema | staged metadata revision | untrusted JSON/schema limits, no hidden secrets |
| `CommitTransaction` | transaction, expected rev, approved preview hash | commit receipt + new snapshot token | staged journal and recovery; no DB+file faux atomicity |
| `RollbackTransaction` | transaction/operation ID | reversible staged state or clear typed conflict | no deleting committed valid data |
| `RescanReconcile` | project and scoped mount, capped work budget | deterministic diff/recovery report | watcher hints not truth, no privileged traversal |
| `RebuildDerivedIndex` | verified canonical metadata snapshot, budget | new index/health report | never overwrite unreconciled canonical truth |

## Error taxonomy
`INVALID_ASSET_ID`, `ASSET_NOT_FOUND`, `ASSET_TOMBSTONED`, `REFERENCE_UNRESOLVED`, `DUPLICATE_ASSET_ID`, `AMBIGUOUS_PATH`, `STALE_SNAPSHOT`, `REVISION_CONFLICT`, `SCHEMA_UNSUPPORTED`, `METADATA_INVALID`, `DEPENDENCY_CYCLE`, `ACCESS_DENIED`, `VFS_DENIED`, `UNSUPPORTED_STORAGE`, `QUOTA_EXCEEDED`, `INDEX_CORRUPT`, `RECOVERY_REQUIRED`, `DB_BUSY`, `CANCELLED`, `IO_FAILURE`, `UNKNOWN`. Stable error codes, sanitized context and retryability must be specified in a future API ADR.

## Multi-step project operation state machine
`PREPARED -> STAGED -> COMMIT_INTENT -> SOURCE_COMMITTED -> INDEX_RECONCILED -> COMPLETE` or `ROLLED_BACK` / `RECOVERY_REQUIRED`.

**Critical:** this is an *application-level reconciliation contract*, not an ACID distributed transaction. Crash injection at each transition must determine exactly which canonical state is visible and whether roll-forward or rollback is safe. No silent half-rename or duplicated ID.

## Example acceptance scenario (conceptual)
1. Create `AssetId=A` for `project://Textures/wood.png`; material `M` references `A`, not its path.
2. Save baseline manifest/snapshot; move `A` to `project://Art/Surfaces/wood.png` through authorized semantic transaction.
3. Commit, crash/restart/rebuild derived index; `A` remains the ID and `M` resolves unchanged.
4. Duplicate `A` to another independent texture: new `AssetId=B`; content digest may match but A != B.
5. Delete or corrupt metadata for `A`: report an unresolved reference and recovery action, never silently choose another asset.
6. Unauthorized MCP actor attempts to move project asset outside allowed workspace: deny before any host I/O.

## AI/MCP security
Tools/resources reflect these semantic contracts, use capability and project scope, restrict page size/filter/fields, return sanitized metadata and preflight previews. Writes require explicit approved authorization and validated transaction preconditions. No SQL strings, absolute path reads, raw file handles, unrestricted project scans or private LLM prompt logs.

## Implementation gate
No C++ interface generated and no MCP tool registered from this document. API shape remains PROPOSED pending future module-specific activation, actual repository source paths, accepted tests and ADR.
