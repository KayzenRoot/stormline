# NLE-PRPLAN-DATA-02-04 — Bounded dependency graph (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + DATA-01 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-02-04`. **Predecessor:** `DATA-02-03` identity. **Issue:** #25. **Base:** `84ba217`. **ADR:** [ADR-0111](../adr/0111-data-02-governance-slice.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md).

## OBJECTIVE

Add typed dependency edges to `AssetRegistry`: add/remove/query forward and reverse edges, duplicate handling, unresolved targets, cycle rejection and fixed capacity. No persistence, serialization, native I/O, network or ABI.

## CONTEXT

DATA-02-01..03 are approved/completed. The registry core owns IDs and paths. DATA-01 is internally complete but not qualified. The owner authorized DATA-01..04 completion on 2026-11-22.

## SCOPE

- `asset_registry.hpp` additive dependency methods/state.
- `tests/core/data02_dependency_tests.cpp`: DEP-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Tags, queries, metadata schema, references/rename/impact; persistence, SQLite, serialization, native filesystem, network, MCP, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0010/0086/0111, `data-02-registry-v0`, DATA-02-03 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0111; DEP-01; bounded 128 edges, cycle rejection, unresolved retention, deterministic sorted output, typed errors.

## ARCHITECTURE RULES

DATA-02 owns the logical graph; DATA-01 owns paths; CORE-01 native OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, CORE-06 diagnostics, DATA-03/04/05 higher layers. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/native I/O/network/persistence; CORE-01 not module-qualified; DATA-01 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; DEP-01 add/remove/duplicate/unresolved/cycle/forward/reverse/sorted/capacity.
- No persistence/serialization/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

DEP-01 multiple kinds, duplicate same kind, self/cycle rejection, unresolved target, tombstone effect, buffer-full required count, missing source, capacity 128. Existing suite remains required.

## DELIVERABLES

Additive `asset_registry.hpp`, dependency tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, DEP-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, persistence/native I/O, unbounded traversal, cycle accepted, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `84ba217`; contract blob `ada255f8b4dc3d468adabaaecb074bfa3cfdbd1d`; DATA-02-03 code PR #598 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-02-04-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-DATA-02-04.md` for implementation.
