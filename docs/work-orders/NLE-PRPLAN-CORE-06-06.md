# NLE-PRPLAN-CORE-06-06 — Local crash envelope (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-06-06`. **Predecessor:** `CORE-06-05` completed. **Issue:** #23. **Base:** `56a31a7e9a79cf5e9a92a58bd840711b51023145`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md).

## OBJECTIVE

Implement a local bounded `CrashEnvelope` value with preceding log records. No signal handler, dump parsing, symbolication, file/network upload, platform crash API, dependency, ABI or release.

## CONTEXT

CORE-06-01..05 are approved/completed. ADR-0109 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner authorized completion of CORE-06 on 2026-11-22.

## SCOPE

- `crash.hpp`: `CrashEnvelope`, bounded preceding-record copy and validation.
- `tests/core/core06_crash_tests.cpp`: CRASH-01.
- Additive CMake target/tests and workflow TSan/path filters.
- Evidence file.

## OUT OF SCOPE

Signal handler, minidump, dump parser, symbolication, crash upload, networking, file I/O, profiling, telemetry, third-party crash library, public ABI/release, CORE-01 completion, CORE-06-07 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0008/0086/0109, `core-06-diagnostics-v0`, CORE-06 architecture, CORE-06-05 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0109; ADR-0086; CRASH-01; bounded local-only, no handler/upload claim.

## ARCHITECTURE RULES

CORE-06 owns crash envelope value; CORE-01 owns OS crash/process lifecycle; GFX/AUD/DATA/WORLD/NET boundaries unchanged. Header-only internal C++20; no third-party include or platform API.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/network/file I/O; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; valid build/session/time/reason and bounded preceding copy.
- CRASH-01: >16 or null+count rejected; exact copy and no side effects.
- No handler/dump/upload/file/network code; no crash-capture guarantee.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

CRASH-01 plus invalid build/session/time/count/pointer fixtures. Existing full CTest suite remains required.

## DELIVERABLES

`crash.hpp`, crash tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CRASH-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, third-party/network/file/handler/dump, crash-upload claim, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `56a31a7e9a79cf5e9a92a58bd840711b51023145`; contract blob `b537526f0fbc8617cf899b4108d1c9ab41235199`; CORE-06-05 code PR #568 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-06-06-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-06-06.md` for implementation.
