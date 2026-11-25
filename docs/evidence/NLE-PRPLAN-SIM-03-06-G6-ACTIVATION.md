# NLE-PRPLAN-SIM-03-06 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `9a1bf649`. **Formal packet:** `NLE-PRPLAN-SIM-03-06`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-03-06](../work-orders/NLE-PRPLAN-SIM-03-06.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-03-01..-05 are approved or completed. This gate activates only logical decoupled-camera metadata.

## Capability admission

- Formal dependencies are `SIM-01` and `SIM-02`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/character/camera_plan.hpp`
- `tests/core/sim03_camera_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-03-06.md`

CAM-01 is required. No camera transform/update, device polling, motor, ECS mutation, GPU or character runtime is permitted.

## Gate state after merge

- Manifest root `SIM03_06_READY_L1_CAPABILITY_OVERLAY`: **449 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 236 `COMPLETED`, 62 approved gates**.
- `SIM-03-06` becomes `EXECUTOR_READY`; `SIM-03-07`..`-08` remain `PLANNED_BLOCKED`.
