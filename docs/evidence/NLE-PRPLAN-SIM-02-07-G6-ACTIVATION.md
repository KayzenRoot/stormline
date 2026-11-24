# NLE-PRPLAN-SIM-02-07 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `a81e446e`. **Formal packet:** `NLE-PRPLAN-SIM-02-07`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-02-07](../work-orders/NLE-PRPLAN-SIM-02-07.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-02-01..-06 are approved or completed. This gate activates only logical constraint metadata.

## Capability admission

- Formal dependencies are `WORLD-02` and `CORE-03`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/physics3d/constraint_plan.hpp`
- `tests/core/sim02_constraint_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-02-07.md`

CONSTRAINT3-01 is required. No constraint solver, joint runtime, contacts, simulation, ECS mutation, GPU or physics runtime is permitted.

## Gate state after merge

- Manifest root `SIM02_07_READY_L1_CAPABILITY_OVERLAY`: **458 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 229 `COMPLETED`, 60 approved gates**.
- `SIM-02-07` becomes `EXECUTOR_READY`; `SIM-02-08`..`-10` remain `PLANNED_BLOCKED`.
