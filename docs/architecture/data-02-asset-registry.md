# DATA-02 — Asset Registry, Stable Identity, Dependency Graph and Provenance

**Research WO:** NLE-P00-WO-002-DATA-02 | **Issue:** #111 | **Implementation issue:** #25  
**Status:** RESEARCH PROPOSED, NOT IMPLEMENTED | **Context Lock main:** `7924f0eaf1eaf711e2316da7f4ee3dc7521afddb`  
**Risk:** LOW for documentation; **ELEVATED** for code handling persistent project state, migrations and recovery.

## 1. Purpose

Stormline's asset registry must let a professional game project scale from small 2D collections to vast 3D asset libraries and AI-generated content without breaking scene, prefab, material or script references on asset rename, move, reimport, duplicate or recovery. This document defines the proposed future service boundaries, APIs, data model, trust model, failure semantics and proof obligations. The engine, registry and code do **not** exist yet.

The essential invariant is: **Asset identity is not a path, not a hash, not a runtime pointer, and not a timestamp.**

| Concept | Purpose | Stability |
|---|---|---|
| `AssetId` | Opaque project/global namespace qualified identity of a logical asset | Stable across rename/move and content modification; intentional duplication creates a new ID unless operation is explicit alias/link |
| `AssetPath` | DATA-01 `VfsPathV1`-compatible location (project/mount) | Mutable, never permanent reference identity |
| `ContentDigest` | Revision-specific bytes fingerprint with algorithm/version tag | Changes with content; collision must not silently merge identities |
| `SourceRevision` | Fingerprint + source metadata and importer/transform version | Immutable per recorded revision, not asset identity |
| `RuntimeHandle` | Session/generation-scoped, never serialized as persistent reference | Ephemeral; invalidates on reload/unload |
| `AssetReference` | `AssetId` + optional subasset locator and expected type | Stable if target moved; explicit error if missing/ambiguous |

### Ownership boundaries
- **DATA-01 VFS**: verified scoped I/O, logical paths, authorized mounts, staged writes, file-handle ownership and recovery primitive. DATA-02 cannot bypass VFS security.
- **DATA-02**: AssetId lifecycle, metadata, dependency edges, provenance, index, query, identity-safe move/rename and reconciliation.
- **DATA-03 import**: source decoding, conversion, import receipts, derived assets; DATA-02 records their metadata but does not convert them.
- **DATA-04 serialization**: cross-module schema format, scene roundtrip, semantic diff and migration policy; DATA-02 publishes contracts but does not preempt universal serialization.
- **DATA-05 cooking**: target content bundle, signature/build manifest and streaming/patching; DATA-02 provides immutable views/IDs.
- **CORE-05**: type/ID conventions, provenance without runtime handle identity; **CORE-03**: concurrency/cancel; **CORE-06**: redacted logs/trace metrics.
- **EDITOR / CLI / MCP**: single authorized semantic command model; no raw SQLite commands, arbitrary filesystem path operations or unrestricted search.

## 2. Proposed canonical truth versus derived index

**Candidate A (preferred for evaluation):** versioned, project-portable asset metadata/manifest in the authorized DATA-01 workspace is canonical; an embedded **SQLite index is rebuildable derived state**, not the only copy of irreplaceable metadata. Metadata manifests/sidecars require atomic staged writes and explicit schema versioning. SQLite contains fast query materialization, dependency edges, directory/name lookups, optional search indexes and progress/transaction ledger; immutable receipt/hashes remain verifiable against canonical metadata.

**Candidate B:** SQLite is authoritative with write-ahead log, backup/recovery and a portable export manifest. Fewer sidecar moves and simpler atomic DB transactions, but project source-control diffs, external edits, file/DB atomicity and corruption recovery need much stronger design.

**Candidate C:** entirely text/CBOR manifests + in-memory index, no SQLite. Great baseline and smallest integration; query scaling and crash recovery require proof for large libraries.

**Proposal:** research **A** against **B/C** with real fixtures before adopting canonical persistence. Important: a SQLite transaction cannot atomically commit files in DATA-01 and rows in SQLite as one distributed transaction. A two-phase application-level journal, deterministic reconciliation or a canonical manifest with rebuildable cache is needed. **Never claim cross-file-and-DB atomicity without tests.**

### Stable identity under project operations
- **Rename/move**: preserve `AssetId`, update logical path mapping transactionally, keep references by ID intact; reject move across disallowed mount/trust scope or name collision.
- **Content edit/reimport**: preserve logical `AssetId` if semantic asset identity persists, update `SourceRevision/ContentDigest` and downstream dirty flags; original imported metadata/provenance preserved.
- **Duplicate**: create a new independent `AssetId`, optionally retain `cloned_from` provenance; duplication is not hard-linking persistent identity.
- **Delete**: tombstone and dependency impact analysis before destructive state; reversible semantic deletion with undo where contract requires, no silent cascade.
- **Project merge/import**: detect duplicated `AssetId` from copied sidecars; distinguish the same asset history from a different one, stop for explicit remap if conflict.
- **External file changes**: watch notifications are hints, never the source of truth. Schedule bounded verified rescan and content revisions; preserve stable ID when metadata proves continuity, otherwise require explicit resolution.
- **Renaming on case-insensitive mounts**: handle case/Unicode conflicts and case-only renames explicitly using DATA-01 authority.
- **Sub-assets**: mesh/material/animation entries may use `AssetId + SubassetId`; importer-defined subasset ID stability across reimport needs a separate acceptance test (DATA-03).

## 3. Proposed normalized data model (logical, no SQL adopted)

| Record | Minimum fields | Constraints |
|---|---|---|
| `AssetRecordV1` | asset_id, project_id, kind, display_name, status, logical_path?, created_revision, current_revision, schema_version | PK asset_id; namespace mapping unique where required; no host absolute path |
| `AssetRevisionV1` | asset_id, revision_id, digest_algorithm, content_digest, size, import_recipe_revision?, created_time?, fingerprint_source | immutable revision; verified content bound and version tag |
| `AssetMetadataV1` | asset_id, schema_version, typed labels/tags/custom_fields, authored_properties, provenance | quotas and validation; unknown extension namespace policy |
| `DependencyEdgeV1` | from_asset, to_asset, edge_kind, optional subasset, declared/derived, confidence, revision | allow legitimate cycles with detection and explicit policy; no infinite DFS |
| `SourceProvenanceV1` | asset_id, original_source_alias?, importer_id/version, license_status?, source_digest?, created_by_origin | do not leak private absolute paths, user identity, prompts or secrets |
| `RegistrySnapshotV1` | project_id, schema_version, revision_seq, integrity_manifest_hash, catalog_version | consistency marker and deterministic incremental query |
| `RegistryOperationV1` | op_id, expected_revision, actor_scope, command, status, recovery_token | idempotent retry, explicit per-operation error and rollback ledger |
| `AssetTombstoneV1` | asset_id, deleted_at_revision, reclaim policy, previous_dependencies | never resurrect a deleted ID accidentally |

**Data guarantees proposed:** typed/enforced unique IDs, supported schema migrations, bounded dependency graph, no dangling references silently interpreted as valid, content digests not treated as signatures, index can be reconstructed after loss where canonical truth remains intact. SQLite foreign-key enforcement is connection-configured and must be explicitly enabled and tested, not assumed.

### SQLite candidate
SQLite embedded, public-domain core, no server/subscription. Evaluate WAL for local editor concurrent readers/single writer, not network-share multi-host. Explicit `foreign_keys=ON`, `integrity_check`, `foreign_key_check`, correct `busy_timeout`, memory/cache quota, checkpoint management and backup API. WAL may lose power-fail durability under `synchronous=NORMAL`; profile `FULL` and choose policy by project data-loss risk, not default throughput. Network filesystem and browser target require separate backend/feature tier. Review build options/extensions/licensing/version before vendoring.

## 4. Identifier and digest technologies

- **UUIDv7 RFC 9562 candidate** for stable 128-bit AssetId, with CSPRNG entropy and tested monotonic/burst behavior. The timestamp field does **not** confer security, authentication or uniqueness guarantee if incorrectly generated.
- **UUIDv4** random 128-bit baseline with simple portable implementation and proven independent uniqueness. Benchmark DB insertion/locality against UUIDv7.
- **BLAKE3** candidate for fast source/content hashing and dedup/cache invalidation. Upstream license alternatives CC0 1.0 / Apache-2.0 / Apache-2.0 with LLVM exception; review exact C implementation/revision.
- **SHA-256** standard widely supported baseline for interoperability/manifest integrity; no proof of content publisher authenticity unless a separate trusted signature policy exists.
- Store `algorithm:id:hex` or typed digest bytes and algorithm field, not bare opaque hash strings. Perform full byte comparison or collision-safe fallback before replacing distinct asset references based on matching digest.

## 5. Dependency graph and queries

**Edge taxonomy (proposed):** `STRONG_RUNTIME`, `SOFT_RUNTIME`, `BUILD_ONLY`, `EDITOR_ONLY`, `GENERATED_FROM`, `OPTIONAL`. Validate referenced asset existence or represent `UNRESOLVED` explicitly. `GetDependencies`, `GetDependents`, `AnalyzeImpact`, `FindByTag`, `FindByType` and `SearchText` must be paginated, stable-sort and cap depth/output, with typed authorization and time budget.

Cycles may be valid (editor references) but must not cause unbounded traversal or endless import/cook. The registry reports cycles and defers policy to the consuming system. Derived graph updates must be transactional with metadata revision or recomputable from canonical sources.

## 6. Proposed Stormline Asset Provenance Graph (SAPG)

R&D proposal only, not a proven new invention:
1. An inspectable graph linking AssetId, source revision, importer version, project operation ID and direct/indirect dependencies.
2. Explainable "why will this material or scene rebuild?" queries for Editor, CLI and MCP without exposing source filenames or private prompts.
3. Deterministic change-impact and invalidation lists, with incremental bounded recomputation and a replayable operation receipt.
4. Undo/redo-safe rename/move, conflict explanations and recovery manifests.
5. Optional privacy-preserving attribution: opt-in origin hints, **not** raw LLM transcript archival.

**Prove-or-drop:** benchmark against a minimal SQLite edge table with recursive query and versioned source manifests. Keep SAPG only if materially better diagnostic correctness, incremental invalidation, change-impact query performance or recovery, with bounded RAM/CPU and no novel-technology claim absent prior-art evidence.

## 7. Failure/recovery, security and authorization

- **Crash/power loss**: staged canonical manifest changes, durable commit token, idempotent startup reconcile and SQLite derived-index rebuild; no dangling file/row mismatch left unreported.
- **SQLite corruption / WAL issues**: integrity check, backup restore and full metadata rescan; do not copy only `.db` while WAL active. No silently repairing the wrong asset.
- **Duplicate/ambiguous IDs**: fail closed, manual/authorized remapping, preserve provenance and old references, produce impact report before commit.
- **Untrusted metadata**: schema quotas (tag lengths/count, depth, total bytes), UTF-8 and Unicode normalization, injection-resistant SQL parameter binding and bounded query complexity.
- **Symlinks/path escape**: all host I/O must pass the DATA-01 capability boundary, never direct OS traversal from registry or MCP.
- **AI/MCP**: project-scope permission checks, transaction revision compare-and-swap, change preview + explicit commit, least-privilege filtered search, redacted provenance, audit correlation via CORE-06. Read-only query tools cannot write.
- **Network/Web**: browser persistence and multi-process collaboration require distinct approved adapter/locking and conflict policy; do not use native SQLite WAL on a network FS.
- **Disk full/permission denied/cancel**: do not leave half-renamed visible identity or silently drop source metadata; typed recoverable errors, rollback/roll-forward and missing-reference diagnostics.
- **Content ownership**: imported third-party license evidence is metadata; it does not grant usage rights or provide a legal clearance.

## 8. Detailed future test/benchmark obligations

| Future test | Required evidence |
|---|---|
| Rename/move across nested directories and type/tag filters | Exact stable AssetId and unchanged scene/prefab/material references |
| Duplicate/edit/reimport | New ID on duplicate, stable ID on update, revision/hash changes, provenance preserved |
| Dependency cycle/deletion/tombstone | Bounded graph traversal; missing references and impacted assets precisely reported |
| 1k / 100k / 1m synthetic assets (as hardware permits) | p50/p95/p99 point lookup, query, index build, rename, impact traversal; RAM/SSD/power metrics |
| Simultaneous editor reads, imports and CLI/MCP reads | Snapshot semantics, single-writer policy/backpressure, zero logical lost update |
| Kill/crash/power-loss simulation at each commit phase | Valid recovery, consistent manifest/index, no silent data loss |
| Corrupt DB, WAL, metadata and copied project | Deterministic rebuild/restore; no duplicated IDs or silent schema downgrade |
| Windows x64 / Linux x64 / macOS arm64 (+ Intel feasibility) | Native build, locks and path/case policy, actual file IO |
| Web/headless target | Functionality via adapter; no SQLite WAL/network-FS assumption, no GPU dependency |
| MCP unauthorized search/change, SQL injection, huge metadata | Scoped authorization, redaction, quota/rate/depth and no arbitrary disk access |
| A/B SQLite derived index vs manifest/in-memory | Measured ingest/lookup/recovery cost; identical fixture/query workload |

Benchmark artifacts must capture build SHA, C++ compiler, DB/vendor version, OS/filesystem/storage/CPU/RAM, fixture generator seed, payload sizes, threads, query mix, warm/cold cache policy, failure injection phase and raw results. None of these runtime tests has been executed.

## 9. Source references

- DATA-01 [VFS proposal](data-01-virtual-file-system.md), [ADR-0009](../adr/0009-data-01-vfs-policy.md).
- [Candidate technology matrix](../research/data-02-asset-registry-technology-matrix.md), [API contract](../contracts/data-02-registry-api.md), [test matrix](../testing/data-02-acceptance-matrix.md), [ADR-0010](../adr/0010-data-02-asset-identity.md).
- SQLite WAL: https://www.sqlite.org/wal.html
- SQLite public domain: https://www.sqlite.org/copyright.html
- SQLite backup: https://www.sqlite.org/backup.html
- SQLite PRAGMA: https://www.sqlite.org/pragma.html
- UUIDv7: https://www.rfc-editor.org/rfc/rfc9562.html
- BLAKE3: https://github.com/BLAKE3-team/BLAKE3

**No backend, schema or library is approved for production. The implementation issue #25 stays BLOCKED and `executor_ready=false`.**
