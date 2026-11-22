# ADR-0110 — DATA-01 governance and bounded VFS direction

**Status:** `OWNER-RATIFIED_BOUNDED_PLANNING_ONLY / NO CODE AUTHORIZED`. **Subordinate to ADR-0009 (ratified only as planning direction) and ADR-0086 (capability admission). Does not declare CORE-01 complete, approve implementation, native sandbox, dependency, public ABI, release, G3 or license.**

**Date:** 2026-11-22 | **WO:** `NLE-PRPLAN-DATA-01-01` | **Parent:** DATA-01 | **Issue:** #24.

## Context

CORE-06 closed as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. DATA-01 (`Virtual File System`) has research, architecture, ADR-0009 `PROPOSED` and a blocked code WO; no executable code exists. Its formal dependency `CORE-01` is not a qualified module. Filesystem access is a high-value security boundary for user projects, editor/CLI/MCP and AI automation; lexical path checks are not a sandbox.

## Decision

- **A:** ADR-0009 is ratified only as planning direction. No PhysicsFS, libzip, archive codec, native OS backend or dependency is selected by this ADR.
- **B:** DATA-01 begins with an owned logical namespace and in-memory mount model: normalized `VfsPath`, opaque `MountId`, read-only mount descriptors, explicit mount generation and typed errors. Host paths are not exposed in the public logical API.
- **C:** Default is read-only. Writes are restricted to explicit workspace-scoped mounts and are out of scope for the first slices. No ambient home-directory access, absolute host path, drive/UNC escape, network URL, symlink traversal or archive extraction is authorized.
- **D:** First slices are lexical path validation, in-memory mount table, deterministic overlay lookup and capability checks. Native filesystem confinement, archive packs, cache, writes, recovery and Web adapters require separate G6/security gates with real platform evidence.
- **E:** Risk is `LOW` for documentation and `ELEVATED` for implementation/security. Release class is `INTERNAL_ONLY`; no public ABI, SDK, release or sandbox claim.
- **F:** CORE-01 owns native filesystem bridge and OS capability; CORE-02 memory; CORE-03 jobs/cancellation; CORE-04 ticks; CORE-06 diagnostics; DATA-02 asset identity; DATA-03 import/decode; DATA-04 serialization/transactions; DATA-05 cooked bundles/streaming. DATA-01 owns only the logical VFS.
- **G:** No claim that lexical normalization is confinement. Any future native mount must fail closed when the OS cannot provide a proven handle-based confinement path.

## Required before code

1. `DATA-01-02` contract with exact logical API, error model, Unicode/case policy, overlay precedence, file allowlist and golden tests.
2. Individual `DATA-01-03` G6 and explicit owner authorization.
3. Tests for traversal/absolute/UNC/device/ADS/NUL/Unicode/case, mount collision, generation/stale handles and deterministic overlays.
4. Separate G6 for native OS I/O, archive/pack, cache, writes and recovery, including platform sandbox and failure evidence.
5. MSVC/GCC/Clang/AppleClang CI; no HIGH/CRITICAL; no release/ABI/sandbox claim.

## Consequence

- `DATA-01-01` may be prepared as `APPROVED_GOVERNANCE`; `DATA-01-02`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 remains not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04/CORE-05/CORE-06 not qualified.
- G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; engine not released.
- No implementation packet becomes `EXECUTOR_READY` by this ADR.
