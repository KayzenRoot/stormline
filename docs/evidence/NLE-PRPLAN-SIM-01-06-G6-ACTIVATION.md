# NLE-PRPLAN-SIM-01-06 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `e7c602e`. **Formal packet:** `NLE-PRPLAN-SIM-01-06`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-01-06](../work-orders/NLE-PRPLAN-SIM-01-06.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-01-01..-05 are approved or completed. This gate activates only logical joint metadata.

## Capability admission

- Formal dependencies are `WORLD-01` and `TWO-01`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/physics2d/joint_plan.hpp`
- `tests/core/sim01_joint_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-01-06.md`

JNT-01 is required. No constraint solver, joint runtime, simulation, ECS mutation, GPU or physics runtime is permitted.

## Gate state after merge

- Manifest root `SIM01_06_READY_L1_CAPABILITY_OVERLAY`: **469 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 220 `COMPLETED`, 58 approved gates**.
- `SIM-01-06` becomes `EXECUTOR_READY`; `SIM-01-07`..`-10` remain `PLANNED_BLOCKED`.
