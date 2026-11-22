# NLE-PRPLAN-DATA-01-03 — Virtual paths (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-01-03`. **Predecessor:** `DATA-01-02` contract. **Issue:** #24. **Base:** `f83193a6c3bc682f1148bfd9e322a004af06d9f3`. **ADR:** [ADR-0110](../adr/0110-data-01-governance-slice.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md).

## OBJECTIVE

Implement the first DATA-01 slice: typed errors/IDs, bounded ASCII `VfsPath` validation and prefix checks. No mounts, overlays, capabilities, cache, storage, native I/O, dependency, ABI or release.

## CONTEXT

DATA-01-01 governance and DATA-01-02 contract are approved. ADR-0110 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner instructed continuation on 2026-11-22.

## SCOPE

- `vfs_types.hpp`: `VfsError`, `MountId`, `WorkspaceId`, `VfsPath`, bounds and validity.
- `vfs_path.hpp`: `make_path`, `view`, `empty`, `is_prefix` with ASCII/traversal/reserved-name rules.
- `tests/core/data01_path_tests.cpp`: PATH-01.
- Additive CMake target/tests and workflow path/TSan filters.
- Evidence file.

## OUT OF SCOPE

Mount table, overlay, capability, cache, storage, native filesystem, archive, writes, network, serialization, public ABI/release, CORE-01 completion, DATA-01-04 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0009/0086/0110, `data-01-vfs-v0`, DATA-01 architecture, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0110; ADR-0086; PATH-01; ASCII-only, relative-only, no traversal/reserved names, bounded capacity, no host leakage.

## ARCHITECTURE RULES

DATA-01 owns logical paths; CORE-01 native OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, CORE-06 diagnostics, DATA-02..05 higher layers. Header-only internal C++20; no third-party include or intrinsic.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/native I/O/network; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; PATH-01 valid/invalid matrix, bounds and prefix behavior.
- No mount/overlay/capability/cache/storage/native I/O code.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

PATH-01: empty root, max total/component, traversal/absolute/UNC/backslash/colon/NUL/control/non-ASCII, `.`/`..`, trailing dot/space, reserved device names, overlong total/component, `is_prefix` boundaries. Existing full CTest suite remains required.

## DELIVERABLES

`vfs_types.hpp`, `vfs_path.hpp`, path tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, PATH-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, third-party/native I/O, mount/overlay/capability/cache/storage code, traversal acceptance, allowlist violation, failed test, HIGH/CRITICAL, release/ABI/sandbox claim. Stop and report.

## CONTEXT LOCK

Base `f83193a6c3bc682f1148bfd9e322a004af06d9f3`; contract blob `8f85e3a68c2ff90e26a344b47d96f57ae90fdfe9`; DATA-01-02 gate PR #579.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-01-03-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-DATA-01-03.md` for implementation.
