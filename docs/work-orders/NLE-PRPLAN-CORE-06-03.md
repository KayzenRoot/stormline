# NLE-PRPLAN-CORE-06-03 — Diagnostics types and logs (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-06-03`. **Predecessor:** `CORE-06-02` contract. **Issue:** #23. **Base:** `ce6858841d38d06c116eca3a9f7f7009dd16de5c`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md).

## OBJECTIVE

Implement the first CORE-06 slice: bounded text/typed errors/IDs plus logs (`LogRecord`, `DiagnosticSink`, `LogBuffer`, `Logger`). No traces, counters, crash envelope, profile, telemetry, network, file I/O, dependency, ABI or release.

## CONTEXT

CORE-06-01 governance and CORE-06-02 contract are approved. ADR-0109 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner authorized completion of CORE-06 on 2026-11-22.

## SCOPE

- `diagnostics_types.hpp`: enums, errors, IDs, time, bounded text, `DiagResult`.
- `log.hpp`: attributes, log record, validation, sink, fixed log buffer, per-producer logger.
- `tests/core/core06_log_tests.cpp`: LOG-01/02/03.
- Additive CMake target/tests and workflow TSan/path filters.
- Evidence file.

## OUT OF SCOPE

Traces, counters, crash handler/envelope, profiling, telemetry, network/file sinks, third-party logging, serialization, public ABI/release, CORE-01 completion, CORE-06-04 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0008/0086/0109, `core-06-diagnostics-v0`, CORE-06 architecture, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0109; ADR-0086; LOG-01/02/03; bounded text, drops, no exception/file/network.

## ARCHITECTURE RULES

CORE-06 owns facade/semantics/local buffers; CORE-01 OS crash/lifecycle; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; GFX/AUD/DATA/EDIT boundaries unchanged. Header-only internal C++20; no third-party include or intrinsic.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/network/file I/O; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; bounded text/attrs and typed validation.
- LOG-01 overlong/NUL exact-max fixtures; LOG-02 capacity/drop/shutdown; LOG-03 per-producer sequence/build/time round-trip.
- No allocation, file, network, third-party type or exception across API.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

LOG-01/02/03 plus invalid build/time/attributes and post-shutdown errors. Existing full CTest suite remains required.

## DELIVERABLES

`diagnostics_types.hpp`, `log.hpp`, log tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, LOG-01/02/03, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, third-party/network/file I/O, trace/counter/crash/profile/telemetry code, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `ce6858841d38d06c116eca3a9f7f7009dd16de5c`; contract blob `b537526f0fbc8617cf899b4108d1c9ab41235199`; CORE-06-02 gate PR #562.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-06-03-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-06-03.md` for implementation.
