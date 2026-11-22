# NLE-PRPLAN-CORE-06-04 — Traces (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-06-04`. **Predecessor:** `CORE-06-03` completed. **Issue:** #23. **Base:** `7187cf2750cb3a8fda32b5dfceb7acad00fa98e8`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md).

## OBJECTIVE

Implement bounded local traces: `SpanRecord`, `make_span`, `complete_span` and fixed `TraceBuffer`. No counters, crash, profile, telemetry, network, file I/O, profiler adapter, dependency, ABI or release.

## CONTEXT

CORE-06-01/02/03 are approved/completed. ADR-0109 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner authorized completion of CORE-06 on 2026-11-22.

## SCOPE

- `trace.hpp`: `SpanRecord`, validation, completion, fixed 128-span buffer with drop accounting.
- `tests/core/core06_trace_tests.cpp`: TRACE-01 and QLF-style valid/error fixtures.
- Additive CMake target/tests and workflow TSan/path filters.
- Evidence file.

## OUT OF SCOPE

Counters, crash handler/envelope, profiling, telemetry, network/file sink, third-party tracing, serialization, public ABI/release, CORE-01 completion, CORE-06-05 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0008/0086/0109, `core-06-diagnostics-v0`, CORE-06 architecture, CORE-06-03 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0109; ADR-0086; TRACE-01; per-producer sequence, bounded buffer, no exception/file/network.

## ARCHITECTURE RULES

CORE-06 owns span values/local buffer; CORE-01 OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, GFX/AUD/DATA/EDIT boundaries unchanged. Header-only internal C++20; no third-party include or intrinsic.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/network/file I/O; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; valid root/non-root spans, completion ordering, trace buffer capacity/drop.
- TRACE-01 complete; no counters/crash/profile/telemetry code.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

TRACE-01 plus invalid build/trace/span/time/name, double completion and buffer overflow. Existing full CTest suite remains required.

## DELIVERABLES

`trace.hpp`, trace tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TRACE-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, third-party/network/file I/O, counter/crash/profile/telemetry code, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `7187cf2750cb3a8fda32b5dfceb7acad00fa98e8`; contract blob `b537526f0fbc8617cf899b4108d1c9ab41235199`; CORE-06-03 code PR #564 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-06-04-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-06-04.md` for implementation.
