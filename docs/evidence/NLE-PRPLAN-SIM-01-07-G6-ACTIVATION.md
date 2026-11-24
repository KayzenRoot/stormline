# NLE-PRPLAN-SIM-01-07 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `f5ddeea`. **Formal packet:** `NLE-PRPLAN-SIM-01-07`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-01-07](../work-orders/NLE-PRPLAN-SIM-01-07.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-01-01..-06 are approved or completed. This gate activates only logical trigger/sensor metadata.

## Capability admission

- Formal dependencies are `WORLD-01` and `TWO-01`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/physics2d/trigger_plan.hpp`
- `tests/core/sim01_trigger_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-01-07.md`

TRG-01 is required. No sensor detection, event dispatch, solver/backend, simulation, ECS mutation, GPU or physics runtime is permitted.

## Gate state after merge

- Manifest root `SIM01_07_READY_L1_CAPABILITY_OVERLAY`: **468 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 221 `COMPLETED`, 58 approved gates**.
- `SIM-01-07` becomes `EXECUTOR_READY`; `SIM-01-08`..`-10` remain `PLANNED_BLOCKED`.
