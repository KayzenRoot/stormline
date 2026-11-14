# DATA-01 — Virtual File System, Storage Boundaries and Mount Security

**Work Order:** NLE-P00-WO-002-DATA-01 | **Research issue:** #108 | **Future implementation issue:** #24  
**Status:** PROPOSED / RESEARCH ONLY | **Date:** 2026-11-14 | **Risk:** LOW for documents; ELEVATED for actual filesystem writes and security.

## 1. Mission and separation of responsibilities

Stormline's Virtual File System (VFS) is a semantic namespace that gives tools and games predictable, versioned, secure access to project, engine, package and runtime files without leaking host OS paths or vendor-specific archive types. The future implementation must support Windows, Linux, macOS native Editor and game exports, headless server use, and future web target-specific adapters. No engine source, filesystem driver, archive codec or benchmark is implemented by this study.

- **DATA-01:** logical path validation, mount lifecycle, overlays, file read/write interface, capability checks, bounded caches and trusted platform handles.
- **CORE-01:** native OS filesystem bridge, lifecycle and platform capabilities; DATA-01 must never assume all OSes share case, Unicode or symlink behavior.
- **CORE-02:** memory resources and allocation budgets; DATA-01 may consume pressure signals and cap caches.
- **CORE-03:** jobs/cancellation; DATA-01 owns I/O work semantics, not a thread scheduler.
- **CORE-06:** events/metrics, incident diagnostics, version/build correlation and privacy.
- **DATA-02:** persistent AssetId, registry, references and provenance graph; VFS paths are **not** canonical asset identity.
- **DATA-03:** importers and decoders; VFS rejects malformed archive/path input before decoding.
- **DATA-04:** project/schema serialization, migration and transactions above byte I/O.
- **DATA-05:** cooked bundles, content hashes/patching and streaming orchestration, not DATA-01.
- **EDIT/AI:** Editor, CLI and MCP obtain narrow, validated semantic file/asset operations through the command kernel, never unrestricted absolute path access.

## 2. Proposed namespace and mount model

Proposed logical URI-like prefixes (all subject to approved ADR):
- `engine://` versioned bundled read-only core content.
- `project://` current project data in a scoped workspace.
- `asset://` alias resolved through DATA-02 **only after registry integration**, not a physical directory.
- `cache://` bounded, disposable files with separate quota and explicit invalidation.
- `user://` scoped per-project application data, not unrestricted home-directory access.
- `temp://` ephemeral isolated scratch for active transaction; cleaned after crash recovery.

**Not web URLs:** `engine://` and `project://` are internal typed identifiers. Remote HTTP/S3 mounts are **out of scope** until a separate threat model/contract approves network and auth.

`MountSpecV1` conceptual contract:
`{mount_id, virtual_root, backend_kind, source_handle, priority, write_policy, trust_level, expected_manifest?, quota_bytes?, case_policy, symlink_policy, lifetime_scope, generation}`.

**Overlay search:** Within the same namespace, use a deterministic stable priority then approved tie-break (e.g. mount ID); distinguish `FOUND`, `NOT_FOUND`, `DENIED`, `SHADOWED`, `AMBIGUOUS_CASE` and `STALE_MOUNT`. A lower-priority mount must not silently bypass permission-denied results from a protected mount. File deletion overlays require a separate explicit tombstone design; absence does not mean removal.

**Write authority:** default all packaged mounts to READ_ONLY, and only designated project/user/cache/temp roots may write with scoped capabilities. The write target is selected by explicit mount owner, not “first writable search path,” preventing silent writes into unrelated overlays. Unmount increments the generation. Open `FileHandle` policies must clearly distinguish stable pinned snapshot/descriptor vs invalidation with typed `STALE_MOUNT`; no use-after-unmount.

## 3. Planned versioned public contracts (logical schemas, not implemented C++ API)

| Contract | Responsibilities | Safety/error semantics |
|---|---|---|
| `VfsPathV1` | validated normalized logical namespace and components | reject absolute/drive/UNC escapes, `..`, NUL, ambiguous Unicode/case, length overflow |
| `MountIdV1` | opaque stable identity within session | no implicit reuse after unmount; avoid leaking host paths |
| `MountDescriptorV1` | virtual root, ordering, RO/RW, trust, quotas, generation | per-workspace capabilities; reject conflicting mount |
| `AccessCapabilityV1` | workspace id, allowed operations, roots and expiration | least privilege; no environment/token access by default |
| `OpenRequestV1` | logical path, mode, expected generation, read bounds | no follow-symlink except explicitly trusted policy; type/check failure |
| `ReadResultV1` | bounded bytes, metadata and optional checksum evidence | size/count checks and stable snapshot semantics |
| `WriteTransactionV1` | begin, stage, validate, commit/rollback and recovery state | same-filesystem temp, sync + atomic rename where supported, no partial visible state |
| `VfsManifestV1` | version, mount metadata and content hashes (where used) | distinguish integrity hashes from authenticated signatures |
| `VfsErrorV1` | code, source, optional retryability and sanitized detail | no raw host paths or secrets in MCP/log errors |

Candidate error taxonomy: `PATH_INVALID`, `PATH_ESCAPE`, `SYMLINK_DENIED`, `REPARSE_POINT_DENIED`, `CASE_COLLISION`, `MOUNT_COLLISION`, `AMBIGUOUS_OVERLAY`, `CAPABILITY_DENIED`, `READ_ONLY`, `QUOTA_EXCEEDED`, `FILE_NOT_FOUND`, `STALE_MOUNT`, `CANCELLED`, `IO_FAILURE`, `DISK_FULL`, `CHECKSUM_MISMATCH`, `ARCHIVE_UNSUPPORTED`, `ARCHIVE_CORRUPT`, `ARCHIVE_BOMB`, `RECOVERY_REQUIRED`, `BACKEND_UNAVAILABLE`, `UNKNOWN`.

**Typed handles:** `OpenFileHandle` represents an OS/codec-specific open handle via opaque ownership; never expose native file descriptors/host paths to plugins or AI by default. Handle and mount generations require lifetime tests against concurrent unmount/reload/cancellation.

## 4. Security boundary: canonicalization is not confinement

The operating system remains the authority for actual filesystem traversal; lexical removal of `..` and even `std::filesystem::canonical` are **insufficient alone** when symlinks/junctions/reparse points or races may change the resolved path between check and open. Neither ZIP APIs nor PhysicsFS alone is proof of an untrusted project sandbox.

- **Windows x64:** build safe handle-based confinement around `CreateFileW`, reparse-point inspection (`FILE_FLAG_OPEN_REPARSE_POINT` where applicable), directory identity/handle checks, ACL and share modes. Do not claim that one flag secures every intermediate component; adversarial swaps and junctions need dedicated tests.
- **Linux x64:** favor directory FD + `openat2` with `RESOLVE_BENEATH` / `RESOLVE_IN_ROOT` and explicit `RESOLVE_NO_MAGICLINKS` or `RESOLVE_NO_SYMLINKS` as policy demands, with OS feature detection. If unavailable, use a rigorously audited component-by-component dirfd/O_NOFOLLOW strategy or **deny untrusted mounts**, never quietly fall back to a lexical-only check.
- **macOS arm64 (Intel feasibility):** study `openat`, dirfd-relative component walk and symlink restrictions; implement against supported OS APIs with native concurrency tests. Do not assume Linux `openat2` exists.
- **Web:** no ambient host filesystem capability; resolve storage through approved browser/File System Access/OPFS/data fetch adapters with user permissions and lifetime/recovery rules. Browser support is PLAT-03, not a promise that native VFS security APIs compile to WASM.
- **Unicode/case:** specify normalization policy and collision handling; refuse case-ambiguous overlays on case-insensitive hosts and unsafe reserved names on Windows. Never casefold silently and modify persisted project names.

### Archive and mount input trust

Archive enumerators must reject malicious entry paths including path traversal, absolute paths, Windows drives, alternate data streams when applicable, symlink entries, duplicate/case-colliding names and nesting outside quotas. Bound:
- number of entries, maximum per-entry and total uncompressed bytes;
- compression ratio and CPU/time budget; reject decompression bombs before/during extraction or stream decode;
- recursive nesting, path length, aggregate memory and I/O quotas;
- encrypted archive capability policy (fail closed if unsupported; “encrypted” does not equal authenticated provenance);
- metadata/manifest checksum mismatch and truncated/corrupt archives.

**Read-only virtual mounting** is preferred for untrusted packs; extraction to disk is a separate permissioned operation. For compressed archive writes, inspect libzip's temporary-file/atomic replacement design but still require project-level transaction/rollback tests and filesystem durability semantics.

## 5. Technology decisions under study

- **C++20 `std::filesystem`** for path manipulations and metadata in trusted contexts only. It does not constitute a security boundary; compare a minimal owned logical `VfsPath`.
- **PhysicsFS** for mount order, archive-based lookup and portable read-only packages; upstream reports zlib license. Its search-path precedence and symlink allowance need explicit semantics; vendor library must not own Stormline security authority without tests.
- **libzip** for ZIP archive read/create/update as a conditional backend. BSD-3-Clause license, current upstream docs 1.12.1 (2026-11-14), with temporary file/replace mechanism in writer. Includes third-party components to audit at chosen revision. Do not adopt both PhysicsFS and libzip until real feature comparison proves both are necessary.
- **Owned native dir/pack backend** as independent baseline: simple directory mount table plus minimal read-only pack. Use C++20 types and optional vendor backend hidden behind typed interface.
- **SQLite** database and content-addressed asset registry belong to DATA-02/05, not the foundational VFS.
- No remote streaming, paid storage/cloud, archive encryption or DRM is promised by this document.

Official sources: https://en.cppreference.com/w/cpp/filesystem ; https://github.com/icculus/physfs ; https://www.icculus.org/physfs/docs/html/physfs_8h.html ; https://libzip.org/documentation/libzip/ ; https://libzip.org/license/ .

## 6. Proposed innovation: Stormline Asset Mount Graph (SAMG)

A research hypothesis linking a versioned `MountGraphSnapshot` to content/permission/priority changes for:
1. deterministic overlay lookup that can explain why a mount shadowed an asset;
2. incremental invalidation of changed paths and caches, with versioned mount generations;
3. explicit capability scopes for editor, runtime, plugin and MCP authors;
4. trace correlation with CORE-06 to connect mount lookup and I/O stalls to frame budget;
5. reproducible mount manifests for QA fixtures and asset provenance.

**Keep/drop criterion:** compare with a straightforward mount table + bounded cache on identical workloads. Retain SAMG only with measurable improvement to lookup latency, invalidation correctness, security diagnostics or authoring workflows without disproportionate memory/CPU/complexity. **Not an implemented invention, nor proof of uniqueness.**

## 7. Transactions, recovery and cache contract

- **Write transaction:** stage in same filesystem/directory scope; verify checksum and quotas; sync required data/metadata where OS provides semantics; rename/replace atomically as supported; record commit intent/recovery marker when multi-file update needs durability. No claim of universal atomic multi-file transaction.
- **Failure tests:** kill between staging/sync/replace, disk full, directory disappeared, permission revocation, locked file, conflict, cancellation and concurrent writers; previous valid version must remain readable where possible.
- **Cache:** keyed by `MountId + generation + normalized_path + content_version` (not path alone); bounded bytes/entry count; invalidation on unmount/overlay changes; no stale secret data after workspace close.
- **Async read:** cancellation must not mutate already committed state, close leaked OS handles, or erase a completed valid cache; producer limits and backpressure belong job budget agreement CORE-03.
- **Optional integrity:** content hash verifies bytes, not publisher authenticity; signatures/trust store are a separate ADR.

## 8. Later acceptance evidence (not yet executed)

| Scenario | Expected proof |
|---|---|
| 10k+ small files across overlapping mounts | deterministic precedence, no path/case ambiguity or unbounded cache |
| Trusted read-only pack + user project overlay | explicit permissions, no accidental writes to engine assets |
| `..`, absolute paths, UNC, device names, ADS, NUL/Unicode | typed deny and no host directory escape |
| Symlink/junction swap race under many threads | no untrusted read/write outside approved root |
| Zip-slip, zip-bomb, nested archive and huge metadata | bounded decode, no escape, correct errors |
| Unmount under concurrent I/O and streaming cancellation | safe generation/handle lifetime, no UAF or leak |
| Kill/crash mid-save, disk full, read-only state | recovery/rollback of prior valid project version |
| Windows x64, Linux x64, macOS arm64 (+ Intel feasibility) | native compiler/build and OS-specific sandbox tests |
| Web (PLAT-03 adapter) | scoped browser permission/offline lifecycle test, not claimed native parity |
| Cold/warm lookup, unpack vs virtual read, cache pressure | p50/p95/p99, CPU/RAM/file descriptors, retries/drops and exact workload SHA |
| Editor/CLI/MCP and plugins | equivalent *authorized* public commands, no path escalation or raw handle exposure |

Required reproducibility metadata: build SHA, benchmark fixture hash, OS/filesystem type, hardware, thread count, archive format/compression level, storage medium, case mode, mount ordering, version and error data. CI-hosted runners may cover functional checks; physical disk/hardware results require separate measured tests.

## 9. Security and completion gates

Before a future executor can touch code, freeze allowed namespaces and API signatures, trust model, exact file paths, source licenses/revisions and package caps, platform sandbox fallbacks, persistence/recovery contract, tests/fixtures and a new Context Lock with source SHA-256 hashes. Any HIGH/CRITICAL escape or data-corruption bug blocks release.

The research issue #108 may be closed after evidence/CI/audit/merge/checkpoint; the **implementation issue #24** remains `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS` and `executor_ready=false` until future audited, approved WOs.
