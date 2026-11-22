# NLE-PRPLAN-CORE-06-08 — Local opt-in telemetry (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-06-08`. **Predecessor:** `CORE-06-07` completed. **Issue:** #23. **Base:** `07caee3493de5744c9933ea82090d4774a459825`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md).

## OBJECTIVE

Implement local opt-in telemetry: default-disabled `TelemetryBuffer`, local-only policy, explicit enable, bounded events and drops. No network, upload, analytics service, file I/O, dependency, ABI or release.

## CONTEXT

CORE-06-01..07 are approved/completed. ADR-0109 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner authorized completion of CORE-06 on 2026-11-22.

## SCOPE

- `telemetry.hpp`: `TelemetryPolicy`, `TelemetryEvent`, validation and fixed 64-event local buffer.
- `tests/core/core06_telemetry_tests.cpp`: TEL-01.
- Additive CMake target/tests and workflow TSan/path filters.
- Evidence file.

## OUT OF SCOPE

Network socket, upload, cloud/analytics service, consent UI, persistence, serialization, external telemetry SDK, public ABI/release, CORE-01 completion, CORE-06-09 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0008/0086/0109, `core-06-diagnostics-v0`, CORE-06 architecture, CORE-06-07 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0109; ADR-0086; TEL-01; default OFF, local-only, no network.

## ARCHITECTURE RULES

CORE-06 owns local telemetry buffer/policy; DATA/EDIT/QA/AI consent/privacy remain their owners; no network or cloud. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/network/file I/O; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; default disabled; non-local policy rejected; bounded events/drops.
- TEL-01: `record` off → `NotEnabled`; explicit enable; full/drop; invalid event.
- No network/upload/file/service; no privacy or consent claim.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

TEL-01 plus invalid build/time/event/value/name and non-local policy. Existing full CTest suite remains required.

## DELIVERABLES

`telemetry.hpp`, telemetry tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TEL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, network/upload/cloud/file, third-party telemetry, allowlist violation, failed test, HIGH/CRITICAL, release/ABI/privacy claim. Stop and report.

## CONTEXT LOCK

Base `07caee3493de5744c9933ea82090d4774a459825`; contract blob `b537526f0fbc8617cf899b4108d1c9ab41235199`; CORE-06-07 code PR #572 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-06-08-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-06-08.md` for implementation.
