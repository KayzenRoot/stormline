# NLE-PRPLAN-SIM-03-05 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `ac9bb206`. **Formal packet:** `NLE-PRPLAN-SIM-03-05`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-03-05](../work-orders/NLE-PRPLAN-SIM-03-05.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-03-01..-04 are approved or completed. This gate activates only logical input-response metadata.

## Capability admission

- Formal dependencies are `SIM-01` and `SIM-02`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/character/input_plan.hpp`
- `tests/core/sim03_input_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-03-05.md`

INPUT-01 is required. No device polling, event dispatch, motor, camera update, ECS mutation, GPU or character runtime is permitted.

## Gate state after merge

- Manifest root `SIM03_05_READY_L1_CAPABILITY_OVERLAY`: **450 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 235 `COMPLETED`, 62 approved gates**.
- `SIM-03-05` becomes `EXECUTOR_READY`; `SIM-03-06`..`-08` remain `PLANNED_BLOCKED`.
