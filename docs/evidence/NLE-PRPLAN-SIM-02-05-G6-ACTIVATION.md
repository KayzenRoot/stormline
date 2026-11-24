# NLE-PRPLAN-SIM-02-05 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `98d8a727`. **Formal packet:** `NLE-PRPLAN-SIM-02-05`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-02-05](../work-orders/NLE-PRPLAN-SIM-02-05.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-02-01..-04 are approved or completed. This gate activates only logical broadphase-layer metadata.

## Capability admission

- Formal dependencies are `WORLD-02` and `CORE-03`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/physics3d/layer_plan.hpp`
- `tests/core/sim02_layer_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-02-05.md`

BROAD3-01 is required. No AABB tree, sweep, narrowphase, contacts, solver, simulation, ECS mutation, GPU or physics runtime is permitted.

## Gate state after merge

- Manifest root `SIM02_05_READY_L1_CAPABILITY_OVERLAY`: **460 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 227 `COMPLETED`, 60 approved gates**.
- `SIM-02-05` becomes `EXECUTOR_READY`; `SIM-02-06`..`-10` remain `PLANNED_BLOCKED`.
