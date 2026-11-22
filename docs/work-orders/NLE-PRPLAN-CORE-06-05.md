# NLE-PRPLAN-CORE-06-05 — Counters (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-06-05`. **Predecessor:** `CORE-06-04` completed. **Issue:** #23. **Base:** `2b4283c9b73196d23282c8b9b55c7cf27aa7660c`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md).

## OBJECTIVE

Implement bounded local counters: `CounterSample`, finite/nonzero validation and fixed `CounterSet` with duplicate-ID update and drop accounting. No crash, profile, telemetry, network, file I/O, dependency, ABI or release.

## CONTEXT

CORE-06-01..04 are approved/completed. ADR-0109 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner authorized completion of CORE-06 on 2026-11-22.

## SCOPE

- `counter.hpp`: `CounterUnit`, `CounterSample`, `make_counter_sample`, fixed 64-slot `CounterSet`.
- `tests/core/core06_counter_tests.cpp`: COUNTER-01.
- Additive CMake target/tests and workflow TSan/path filters.
- Evidence file.

## OUT OF SCOPE

Crash, profiling, telemetry, network/file sink, third-party metrics, serialization, public ABI/release, CORE-01 completion, CORE-06-06 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0008/0086/0109, `core-06-diagnostics-v0`, CORE-06 architecture, CORE-06-04 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0109; ADR-0086; COUNTER-01; finite values, bounded cardinality, no exception/file/network.

## ARCHITECTURE RULES

CORE-06 owns counter values/local set; CORE-01 OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, GFX/AUD/DATA/EDIT boundaries unchanged. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/network/file I/O; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; finite values only, nonzero counter ID, capacity 64.
- COUNTER-01: valid, NaN/Inf, zero ID/time, duplicate update, full/drop, find miss.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

COUNTER-01 plus invalid build/time/id/value and duplicate/full fixtures. Existing full CTest suite remains required.

## DELIVERABLES

`counter.hpp`, counter tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, COUNTER-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, third-party/network/file I/O, crash/profile/telemetry code, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `2b4283c9b73196d23282c8b9b55c7cf27aa7660c`; contract blob `b537526f0fbc8617cf899b4108d1c9ab41235199`; CORE-06-04 code PR #566 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-06-05-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-06-05.md` for implementation.
