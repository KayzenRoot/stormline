# NLE-PRPLAN-TWO-03-07 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `8878ee1`. **Formal packet:** `NLE-PRPLAN-TWO-03-07`. **ADR:** [ADR-0125](../adr/0125-two-03-internal-animation-pipeline.md). **Contract:** [two-03-animation-internal-v0](../contracts/two-03-animation-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-03-07](../work-orders/NLE-PRPLAN-TWO-03-07.md).

## Authorization

The owner authorized continuation on 2026-11-23. TWO-03-01..-06 are approved. This gate activates only the logical timeline metadata slice.

## Capability admission

- Formal dependency is `TWO-01`; it is not module-qualified.
- Admission uses completed TWO-01 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/animation/timeline_plan.hpp`
- `tests/core/two03_timeline_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-TWO-03-07.md`

TML-01 is required. No clock, playback, seek/reverse runtime, audio scheduling, export/codec, editor UI, GPU or render is permitted.

## Gate state after merge

- Manifest root `TWO03_07_READY_L1_CAPABILITY_OVERLAY`: **531 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 172 `COMPLETED`, 44 approved gates**.
- `TWO-03-07` becomes `EXECUTOR_READY`; `TWO-03-08`..`-09` remain `PLANNED_BLOCKED`.
