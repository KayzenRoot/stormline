# NLE-PRPLAN-SIM-04-08 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `790b4359`. **Formal packet:** `NLE-PRPLAN-SIM-04-08`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-04-08](../work-orders/NLE-PRPLAN-SIM-04-08.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-04-01..-07 are approved or completed. This gate activates only logical sync group metadata.

## Capability admission

- Formal dependencies are `SIM-03` and `DATA-03`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/animation/skeletal/sync_plan.hpp`
- `tests/core/sim04_sync_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-04-08.md`

SYNC-01 is required. No runtime synchronization, codec, pose evaluation, graph runtime, root motion, ECS mutation, GPU or animation runtime is permitted.

## Gate state after merge

- Manifest root `SIM04_08_READY_L1_CAPABILITY_OVERLAY`: **439 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 244 `COMPLETED`, 64 approved gates**.
- `SIM-04-08` becomes `EXECUTOR_READY`; `SIM-04-09`..`-10` remain `PLANNED_BLOCKED`.
