# NLE-PRPLAN-CORE-04-04 — G6 Timeline activation

**Status:** `G6 IMPLEMENTATION PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `60cd2dfbaf38ee43b332f0b2274816a9b739736e`. **Formal packet:** `NLE-PRPLAN-CORE-04-04`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md). **Contract:** [core-04-timeline-v0](../contracts/core-04-timeline-v0.md). **WO:** [NLE-PRPLAN-CORE-04-04](../work-orders/NLE-PRPLAN-CORE-04-04.md).

## Authorization

The owner instructed continuation on 2026-11-22. CORE-04-01/02/03 are approved/completed; this gate activates only `CORE-04-04` after Docs Validation and pt-BR audit. It does not activate `CORE-04-05`..`-10`, select a timing SDK, approve release/ABI or declare CORE-01 complete.

## CORE-01 capability admission

Same bounded set as CORE-04-01/02/03: `-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests, `-13` capability graph; `module_completion_claimed=false`.

## Bounded technical slice

- `Timeline` over the frozen `ClockSource`; exact rational accumulator with carried remainder.
- Pause/resume/single-step, interpolation alpha, clamp, DropExcess/Carry debt, replay header, typed errors.
- TICK-03..TICK-12 tests; additive CMake/workflow; evidence.
- No third-party timing type, public ABI or release.

## Gate state after merge

- Manifest root `CORE04_04_READY_L1_CAPABILITY_OVERLAY`: **708 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 31 `COMPLETED`, 8 approved gates**.
- `CORE-04-04` becomes `EXECUTOR_READY`; `CORE-04-05`..`-10` remain `PLANNED_BLOCKED`.
- Selector allows only `NLE-PRPLAN-CORE-04-04`; every other ID exits 2; registry byte-identical.

## Proof obligations

TICK-03..12; rational 24 h exact; pause/step; catch-up/drop/carry; time scale; lifecycle; determinism; TSan/ASan/UBSan; Linux/Windows/macOS; exact-head CI; no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
