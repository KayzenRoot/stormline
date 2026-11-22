# DATA-01 INTERNAL_ONLY Virtual File System Governance Contract v0 (NLE-PRPLAN-DATA-01-01)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `866309f708924ae2d9a0d9ac2519c22272602222`. **ADR:** [ADR-0110](../adr/0110-data-01-governance-slice.md), [ADR-0009](../adr/0009-data-01-vfs-policy.md) planning-only. **WO:** [NLE-PRPLAN-DATA-01-01](../work-orders/NLE-PRPLAN-DATA-01-01.md).

## Objective

Record ownership, security boundaries, release/risk classes and gates before DATA-01 implementation. No VFS API, dependency, native I/O, archive codec, write path, network or public ABI is authorized.

## Admission and boundaries

- Formal `CORE-01` dependency remains; admission is limited to completed `CORE-01-03/-06/-07/-08/-12/-13` capabilities under ADR-0110/ADR-0086. CORE-01 module completion is **not** claimed.
- DATA-01 owns logical path validation, mount table/overlays, capabilities, generations and local cache contracts.
- CORE-01 owns native OS filesystem bridge; CORE-02 memory; CORE-03 jobs/cancellation; CORE-04 ticks; CORE-06 diagnostics; DATA-02 asset identity; DATA-03 import/decode; DATA-04 serialization; DATA-05 bundles/streaming.
- No PhysicsFS, libzip, archive codec, SQLite, network, cloud, editor UI or MCP raw-filesystem access is a core dependency.

## Policy invariants

1. **Logical namespace only.** Host paths, drive letters, UNC and native file descriptors do not appear in public logical values or errors.
2. **Read-only default.** No write, delete, rename, extraction or archive creation in the first slices.
3. **Path validation before I/O.** Reject absolute paths, `..`, NUL, UNC/drive prefixes, Windows reserved names, device/ADS syntax, overlong paths and ambiguous Unicode/case.
4. **No lexical-sandbox claim.** Normalization is validation, not OS confinement; native backends require separate handle-based security evidence.
5. **Deterministic mounts.** Mount priority, stable tie-break and `SHADOWED`/`AMBIGUOUS` outcomes are explicit; no silent first-match write authority.
6. **Generation fencing.** Unmount/reload increments generation; stale handles/mounts return typed `StaleMount`.
7. **Bounded metadata.** No unbounded path/component count, attributes or cache; errors are sanitized and contain no secrets or host paths.
8. **No network.** Remote mounts, HTTP/S3, telemetry and cloud storage are out of scope.
9. **Release boundary.** Internal-only; no public ABI, sandbox certification, data-loss guarantee or release claim.

## First-slice scope (future, blocked)

Subject to `DATA-01-02` contract:

- `DATA-01-03` `VfsPath` validation: relative logical path, component normalization, traversal/absolute/UNC/device/ADS/NUL rejection, bounded length.
- `DATA-01-04` in-memory read-only mount table: mount IDs, roots, priority, generation, lookup result taxonomy.
- `DATA-01-05` overlays: deterministic precedence, shadowing/ambiguity outcomes, no implicit write.
- `DATA-01-06` capabilities: explicit read permission and workspace scope, no ambient authority.
- `DATA-01-07` cache: bounded key/value contract only after mount generation exists.
- `DATA-01-08` storage abstraction: interface values only; native OS/archive backends require separate G6.
- `DATA-01-09` qualification and `-10` closeout remain blocked.

## Gate state after merge

- Manifest root `DATA01_01_APPROVED_GOVERNANCE_ONLY`: **681 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 54 `COMPLETED`, 13 approved gates**.
- `DATA-01-01` becomes `APPROVED_GOVERNANCE`; `DATA-01-02`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, native path/OS I/O, dependency selection, traversal acceptance, secret/path exposure, write/delete/extract/network, public ABI/release or HIGH/CRITICAL. Unmerged: close the branch. After merge: normal revert PR; never force push.

No implementation is authorized by this governance contract. `DATA-01-02` requires its own audited contract and `DATA-01-03` its own G6.
