# ADR-0111 — DATA-02 governance and bounded registry direction

**Status:** `OWNER-RATIFIED_BOUNDED_PLANNING_ONLY / NO CODE AUTHORIZED`. **Subordinate to ADR-0010 (planning only) and ADR-0086 (capability admission). Does not declare DATA-01 or CORE-01 complete, approve persistence, SQLite, dependency, public ABI, release, G3 or license.**

**Date:** 2026-11-22 | **WO:** `NLE-PRPLAN-DATA-02-01` | **Parent:** DATA-02 | **Issue:** #25.

## Context

DATA-01 closed its internal logical VFS sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. DATA-02 (`Asset Registry & Metadata`) has research, architecture, ADR-0010 `PROPOSED`, a conceptual language-neutral API and a blocked code WO; no executable registry code exists. Asset identity, references and dependency state are high-value correctness boundaries for scenes, editor, CLI and AI automation. A path, hash or runtime pointer is not persistent identity.

## Decision

- **A:** ADR-0010 is ratified only as planning direction. No SQLite, BLAKE3, UUID library, serialization format, archive, network or third-party dependency is selected by this ADR.
- **B:** The first DATA-02 sequence is an owned logical, fixed-capacity, in-memory registry: opaque 128-bit `AssetId`, `ProjectId`, validated DATA-01 `VfsPath`, asset kind/status/revision, dependency edges, tags, bounded queries, typed metadata schema and ID-based references.
- **C:** Identity is never a path, content digest, timestamp or runtime pointer. Rename/move may update a logical path while preserving `AssetId`; duplication would require a distinct new ID.
- **D:** The first sequence has no persistence, serialization, SQLite, host filesystem access, file writes, crash recovery, transactions, MCP tools, editor UI or network. Canonical persistence and recovery require separate G6/security gates with real evidence.
- **E:** Risk is `LOW` for documentation and `ELEVATED` for implementation/state handling. Release class is `INTERNAL_ONLY`; no public ABI, SDK, release, data-loss or sandbox claim.
- **F:** DATA-01 owns logical VFS; CORE-01 native OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, CORE-06 diagnostics; DATA-02 owns asset identity/metadata/references; DATA-03 import/decode; DATA-04 serialization/scene transactions; DATA-05 bundles/streaming.
- **G:** Cycles and unresolved references must be reported explicitly. No traversal may be unbounded. Typed errors must not leak host paths, secrets or private provenance.

## Required before code

1. `DATA-02-02` contract with exact C++ API, error model, capacities, ordering, cycle/unresolved policy, file allowlist and per-slice test oracles.
2. Individual G6 activation and explicit owner authorization per implementation slice.
3. Tests for duplicate IDs, path collision, tombstone, stable ordering, cycle detection, unresolved references, tag/schema quotas and bounded overload.
4. Separate G6 for persistence, serialization, SQLite, migrations, crash recovery, MCP and native I/O.
5. GCC/Clang/MSVC/AppleClang CI; no HIGH/CRITICAL; no release/ABI/persistence claim.

## Consequence

- `DATA-02-01` may be prepared as `APPROVED_GOVERNANCE`; `DATA-02-02`..`-10` remain `PLANNED_BLOCKED`.
- DATA-01 remains `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; CORE-01 is not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04/CORE-05/CORE-06 not qualified.
- G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; engine not released.
- No implementation packet becomes `EXECUTOR_READY` by this ADR.
