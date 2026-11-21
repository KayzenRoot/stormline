# NLE-PRPLAN-CORE-03-09 — Integrated CORE-03 qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — test-only code authorized only after this gate merges.** **Gate:** G6 qualification + D2 admission. **Formal packet:** `NLE-PRPLAN-CORE-03-09`. **Predecessors:** `CORE-03-03` implementation and `CORE-03-04`..`08` satisfaction closeouts. **Issue:** #20. **Base:** `6a3f245b3647b4b708b239147ec3c666fa5fef2c`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **Contract:** [core-03-qualification-v0](../contracts/core-03-qualification-v0.md).

## OBJECTIVE

Qualify the implemented `TaskGraph`/`JobExecutor` together under deterministic integrated load, 10,000-task stress, recovery/overload and report-only timing. Test-only; no production change.

## CONTEXT

`CORE-03-03` delivered the frozen contract implementation with JOB-01..10. `CORE-03-04`..`08` were closed as satisfied by that implementation. The owner instructed continuation on 2026-11-21. `CORE-03-09` is the planned integrated qualification; CORE-02 remains `NOT_QUALIFIED` and the formal dependency remains recorded.

## SCOPE

- New executable `core03_jobs_qualification_test` with QLF-01 integrated, QLF-02 10,000-task stress, QLF-03 recovery, QLF-04 overload/backpressure and QLF-05 report-only benchmark.
- Additive CMake/CTest and TSan target inclusion.
- Exact evidence file.

## OUT OF SCOPE

Production source changes, new API/types, performance thresholds, p95 ranking, allocator selection, technology selection, memory/GPU/audio/network qualification, public ABI, release, full Q4, CORE-02 completion and `CORE-03-10`.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0105, both CORE-03 contracts, CORE-03-03 evidence/PR #508, CORE-03-04..08 closeouts, JOB-01..10 tests, CMake/workflow, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0105 D2; qualification contract QLF-01..QLF-05; no production change.

## ARCHITECTURE RULES

Test-only; public CORE-03 API plus C++20 standard library; no SDL/third-party; no global allocator override; CORE-01/02/04/06/GFX-03/AUD-01 boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service; CORE-02 `NOT_QUALIFIED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-01..QLF-05 implemented and passing.
- 10,000+ tasks across 100+ jobs; every fence completes; stats balanced.
- QueueFull without mutation; recovery after cancellation storm/overflow with a fresh executor.
- TSan/ASan/UBSan and Linux/Windows/macOS exact-head CI.
- No production-code/threshold/ABI/release claim; pt-BR audit `APPROVED`.

## TESTS

QLF-01 integrated; QLF-02 10,000-task stress; QLF-03 recovery; QLF-04 overload; QLF-05 report-only benchmark. Full existing CTest suite on all targets.

## DELIVERABLES

Test source, additive CMake/workflow, evidence, exact-head CI, pt-BR audit. No production/API change.

## REVIEW FORMAT

pt-BR: base/head, files, QLF matrix, stress/recovery evidence, benchmark report-only, regression/sanitizers, no overclaim. `APPROVED`/`CORRECTION REQUIRED`/`BLOCKED`.

## STOP CONDITION

Stale context, gate not merged, production change outside allowlist, deadlock/race/leak, missing 10k stress, threshold/ABI/release overclaim, HIGH/CRITICAL. Stop and report.

## CONTEXT LOCK

Base `6a3f245b3647b4b708b239147ec3c666fa5fef2c`; implementation contract blob `36b03944504b6b8e74907f773ead6901ce8705b0`; CORE-03-03 merge `3a697f6869f7081d9a05089d84ab6021c6e6a550`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-03-09-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-03-09.md` for qualification results.
