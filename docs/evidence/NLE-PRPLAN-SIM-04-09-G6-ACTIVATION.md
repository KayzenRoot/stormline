# NLE-PRPLAN-SIM-04-09 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `47ffe5cd`. **Formal packet:** `NLE-PRPLAN-SIM-04-09`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-04-09](../work-orders/NLE-PRPLAN-SIM-04-09.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-04-01..-08 are approved or completed. This gate activates only integrated internal qualification.

## Capability admission

- Formal dependencies are `SIM-03` and `DATA-03`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/sim04_qualification_tests.cpp` with QLF-S401..S404
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-04-09.md`

No production header may change. No pose evaluator, graph runtime, IK/ragdoll/codec/sync runtime, root motion, ECS mutation, GPU or animation runtime is permitted.

## Gate state after merge

- Manifest root `SIM04_09_READY_L1_CAPABILITY_OVERLAY`: **438 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 245 `COMPLETED`, 64 approved gates**.
- `SIM-04-09` becomes `EXECUTOR_READY`; `SIM-04-10` remains `PLANNED_BLOCKED`.
