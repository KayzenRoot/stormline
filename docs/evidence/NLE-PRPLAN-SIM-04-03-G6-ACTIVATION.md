# NLE-PRPLAN-SIM-04-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `2ec52f00`. **Formal packet:** `NLE-PRPLAN-SIM-04-03`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-04-03](../work-orders/NLE-PRPLAN-SIM-04-03.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-04-01 and -02 are approved. This gate activates only logical retarget profile metadata.

## Capability admission

- Formal dependencies are `SIM-03` and `DATA-03`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/animation/animation_types.hpp`
- `src/stormline/animation/retarget_plan.hpp`
- `tests/core/sim04_retarget_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-04-03.md`

RET-01 is required. No pose conversion, evaluator, graph runtime, solver, ragdoll, codec, root-motion application, ECS mutation, GPU or animation runtime is permitted.

## Gate state after merge

- Manifest root `SIM04_03_READY_L1_CAPABILITY_OVERLAY`: **444 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 239 `COMPLETED`, 64 approved gates**.
- `SIM-04-03` becomes `EXECUTOR_READY`; `SIM-04-04`..`-10` remain `PLANNED_BLOCKED`.
