# NLE-PRPLAN-SIM-01-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `180a52c`. **Formal packet:** `NLE-PRPLAN-SIM-01-03`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-01-03](../work-orders/NLE-PRPLAN-SIM-01-03.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-01-01/-02 are approved. This gate activates only logical rigid-body metadata.

## Capability admission

- Formal dependencies are `WORLD-01` and `TWO-01`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/physics2d/physics2d_types.hpp`
- `src/stormline/physics2d/body_plan.hpp`
- `tests/core/sim01_body_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-01-03.md`

BODY-01 is required. No solver/backend, simulation, broadphase/narrowphase, query execution, contact/event dispatch, ECS mutation, GPU or physics runtime is permitted.

## Gate state after merge

- Manifest root `SIM01_03_READY_L1_CAPABILITY_OVERLAY`: **472 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 217 `COMPLETED`, 58 approved gates**.
- `SIM-01-03` becomes `EXECUTOR_READY`; `SIM-01-04`..`-10` remain `PLANNED_BLOCKED`.
