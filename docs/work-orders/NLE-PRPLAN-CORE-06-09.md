# NLE-PRPLAN-CORE-06-09 — Integrated diagnostics qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — code authorized only after this gate merges.** **Gate:** G6 qualification + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-06-09`. **Predecessor:** `CORE-06-08` completed. **Issue:** #23. **Base:** `51342e965bbb38144869e665f71801d3183821c6`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md).

## OBJECTIVE

Add an integrated internal qualification test over all completed CORE-06 headers: logs, traces, counters, crash envelope, profile samples and local opt-in telemetry together. Exercise bounded overload, per-producer sequence and typed-error recovery. No production API, network, crash handler, profiler, serialization, ABI or release is authorized.

## CONTEXT

CORE-06-01..08 are approved/completed. ADR-0109 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner authorized completion of CORE-06 on 2026-11-22.

## SCOPE

- `tests/core/core06_diagnostics_qualification_tests.cpp`: QLF-D01 integrated, QLF-D02 repeatability, QLF-D03 recovery, QLF-D04 bounded overload.
- Additive CMake target/CTest entries and workflow TSan target list.
- Evidence file.
- No production source change.

## OUT OF SCOPE

New diagnostics API, network/upload/crash handler/profiler adapter, serialization, hardware/soak/performance qualification, public ABI/release, CORE-01 completion, CORE-06-10 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0008/0086/0109, `core-06-diagnostics-v0`, CORE-06 architecture, all CORE-06 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0109; ADR-0086; LOG/TRACE/COUNTER/CRASH/PROF/TEL integrated; no network/file/performance claim.

## ARCHITECTURE RULES

CORE-06 owns diagnostic values/local buffers; CORE-01 OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, GFX/AUD/DATA/EDIT boundaries unchanged. Test-only includes; header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/network/file I/O; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; all CORE-06 headers compile together.
- QLF-D01 log→trace→counter→profile→crash→telemetry flow with deterministic values.
- QLF-D02 repeated runs identical; QLF-D03 typed errors recover; QLF-D04 10,000 attempts keep fixed capacities and count drops.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no production/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

QLF-D01..04; existing full CTest suite remains required. Internal/CI-only, not hardware/soak/performance/crash qualification.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-D01..04, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, production API change, third-party/network/file/profiler/crash upload, allowlist violation, failed test, HIGH/CRITICAL, hardware/ABI/release claim. Stop and report.

## CONTEXT LOCK

Base `51342e965bbb38144869e665f71801d3183821c6`; contract blob `b537526f0fbc8617cf899b4108d1c9ab41235199`; CORE-06-08 code PR #574 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-06-09-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-06-09.md` for qualification results.
