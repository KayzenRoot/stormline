# NLE-PRPLAN-CORE-03-09 — G6 qualification activation

**Status:** `G6 QUALIFICATION PROPOSAL / TEST-ONLY CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `6a3f245b3647b4b708b239147ec3c666fa5fef2c`. **Formal packet:** `NLE-PRPLAN-CORE-03-09`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **Contract:** [core-03-qualification-v0](../contracts/core-03-qualification-v0.md). **WO:** [NLE-PRPLAN-CORE-03-09](../work-orders/NLE-PRPLAN-CORE-03-09.md).

## Authorization

The owner instructed continuation on 2026-11-21 after the CORE-03-04..08 satisfaction closeouts. This gate activates only `CORE-03-09`: a test-only integrated qualification of the already implemented CORE-03 scheduler after Docs Validation and pt-BR audit.

It does not add production code, select a scheduler/allocator, approve release/ABI, alter CORE-02 status, or activate `CORE-03-10`.

## D2 capability admission

- Formal `CORE-02` dependency remains; CORE-02 is `NOT_QUALIFIED`.
- Admission uses completed `CORE-02-03..09` capabilities only; `module_completion_claimed=false`.
- CORE-03-03 is the production implementation; this packet only qualifies it.

## Bounded technical slice

- `tests/core/core03_jobs_qualification_tests.cpp` with QLF-01 integrated, QLF-02 10,000-task stress, QLF-03 recovery, QLF-04 overload/backpressure and QLF-05 report-only benchmark.
- Additive CMake/CTest and TSan target inclusion.
- No production source, threshold, ranking, dependency, ABI or release.

## Gate state after merge

- Manifest root `CORE03_09_READY_L1_CAPABILITY_OVERLAY`: **713 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY` (`CORE-03-09`), 28 `COMPLETED`, 6 approved gates**.
- `CORE-03-09` becomes `EXECUTOR_READY`; `CORE-03-10` remains `PLANNED_BLOCKED`.
- Selector allows only `NLE-PRPLAN-CORE-03-09`; every other ID exits 2; registry byte-identical.

## Proof obligations

QLF-01..QLF-05; 10,000+ tasks across 100+ jobs; recovery/overload; TSan/ASan/UBSan; Linux/Windows/macOS; exact-head CI; no HIGH/CRITICAL.

No code/native PASS is claimed by this gate.
