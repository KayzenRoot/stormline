# NLE-PRPLAN-SIM-04-07 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `2b2c0d9e`. **Formal packet:** `NLE-PRPLAN-SIM-04-07`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-04-07](../work-orders/NLE-PRPLAN-SIM-04-07.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-04-01..-06 are approved or completed. This gate activates only logical compression profile metadata.

## Capability admission

- Formal dependencies are `SIM-03` and `DATA-03`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/animation/skeletal/compression_plan.hpp`
- `tests/core/sim04_compression_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-04-07.md`

CMP-01 is required. No codec, pose evaluation, graph runtime, solver, ragdoll, root motion, ECS mutation, GPU or animation runtime is permitted.

## Gate state after merge

- Manifest root `SIM04_07_READY_L1_CAPABILITY_OVERLAY`: **440 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 243 `COMPLETED`, 64 approved gates**.
- `SIM-04-07` becomes `EXECUTOR_READY`; `SIM-04-08`..`-10` remain `PLANNED_BLOCKED`.
