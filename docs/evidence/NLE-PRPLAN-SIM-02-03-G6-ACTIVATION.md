# NLE-PRPLAN-SIM-02-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `9968eb68`. **Formal packet:** `NLE-PRPLAN-SIM-02-03`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-02-03](../work-orders/NLE-PRPLAN-SIM-02-03.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-02-01 and -02 are approved. This gate activates only logical rigid-body metadata.

## Capability admission

- Formal dependencies are `WORLD-02` and `CORE-03`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/physics3d/physics3d_types.hpp`
- `src/stormline/physics3d/body_plan.hpp`
- `tests/core/sim02_body_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-02-03.md`

BODY3-01 is required. No solver, broadphase, query execution, contacts, simulation, ECS mutation, GPU or physics runtime is permitted.

## Gate state after merge

- Manifest root `SIM02_03_READY_L1_CAPABILITY_OVERLAY`: **462 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 225 `COMPLETED`, 60 approved gates**.
- `SIM-02-03` becomes `EXECUTOR_READY`; `SIM-02-04`..`-10` remain `PLANNED_BLOCKED`.
