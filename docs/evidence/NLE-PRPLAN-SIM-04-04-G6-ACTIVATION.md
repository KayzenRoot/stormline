# NLE-PRPLAN-SIM-04-04 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `90ea070b`. **Formal packet:** `NLE-PRPLAN-SIM-04-04`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-04-04](../work-orders/NLE-PRPLAN-SIM-04-04.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-04-01..-03 are approved or completed. This gate activates only logical blend-tree node metadata.

## Capability admission

- Formal dependencies are `SIM-03` and `DATA-03`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/animation/skeletal/blend_tree_plan.hpp`
- `tests/core/sim04_blend_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-04-04.md`

BLEND-01 is required. No graph evaluation, blend execution, pose evaluation, solver, ragdoll, codec, root motion, ECS mutation, GPU or animation runtime is permitted.

## Gate state after merge

- Manifest root `SIM04_04_READY_L1_CAPABILITY_OVERLAY`: **443 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 240 `COMPLETED`, 64 approved gates**.
- `SIM-04-04` becomes `EXECUTOR_READY`; `SIM-04-05`..`-10` remain `PLANNED_BLOCKED`.
