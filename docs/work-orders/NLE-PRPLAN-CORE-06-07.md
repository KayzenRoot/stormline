# NLE-PRPLAN-CORE-06-07 — Profile samples (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-06-07`. **Predecessor:** `CORE-06-06` completed. **Issue:** #23. **Base:** `72974ef539e7a69e9ad5e017d28a649ee387b5df`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md).

## OBJECTIVE

Implement bounded local profile samples: `ProfileSample`, validation and fixed `ProfileAccumulator` with count/total/min/max/drop/reset. No Tracy/Perfetto, timer adapter, sampling thread, network/file I/O, dependency, ABI or release.

## CONTEXT

CORE-06-01..06 are approved/completed. ADR-0109 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner authorized completion of CORE-06 on 2026-11-22.

## SCOPE

- `profile.hpp`: `ProfileSample`, `make_profile_sample`, fixed 64-sample `ProfileAccumulator`.
- `tests/core/core06_profile_tests.cpp`: PROF-01.
- Additive CMake target/tests and workflow TSan/path filters.
- Evidence file.

## OUT OF SCOPE

Tracy/Perfetto, timer/OS adapter, sampling thread, trace export, telemetry, network/file I/O, third-party profiler, public ABI/release, CORE-01 completion, CORE-06-08 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0008/0086/0109, `core-06-diagnostics-v0`, CORE-06 architecture, CORE-06-06 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0109; ADR-0086; PROF-01; bounded local policy, no performance claim.

## ARCHITECTURE RULES

CORE-06 owns profile sample values/accumulator; CORE-01 OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, GFX/AUD/DATA/EDIT boundaries unchanged. Header-only internal C++20; no third-party include or intrinsic.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/network/file I/O; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; valid build/scope/elapsed and fixed capacity.
- PROF-01: count/total/min/max exact, reset, full/drop, zero elapsed allowed.
- No profiler/sampling/network/file allocation; no performance guarantee.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

PROF-01 plus invalid build/zero scope/overflow fixtures. Existing full CTest suite remains required.

## DELIVERABLES

`profile.hpp`, profile tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, PROF-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, third-party/network/file/profiler listener, allowlist violation, failed test, HIGH/CRITICAL, release/ABI/performance claim. Stop and report.

## CONTEXT LOCK

Base `72974ef539e7a69e9ad5e017d28a649ee387b5df`; contract blob `b537526f0fbc8617cf899b4108d1c9ab41235199`; CORE-06-06 code PR #570 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-06-07-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-06-07.md` for implementation.
