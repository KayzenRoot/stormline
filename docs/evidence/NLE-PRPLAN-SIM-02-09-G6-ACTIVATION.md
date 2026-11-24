# NLE-PRPLAN-SIM-02-09 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `0907615b`. **Formal packet:** `NLE-PRPLAN-SIM-02-09`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-02-09](../work-orders/NLE-PRPLAN-SIM-02-09.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-02-01..-08 are approved or completed. This gate activates only integrated internal qualification.

## Capability admission

- Formal dependencies are `WORLD-02` and `CORE-03`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/sim02_qualification_tests.cpp` with QLF-S201..S204
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-02-09.md`

No production header may change. No solver, broadphase/narrowphase execution, query execution, contacts, simulation, ECS mutation, GPU or physics runtime is permitted.

## Gate state after merge

- Manifest root `SIM02_09_READY_L1_CAPABILITY_OVERLAY`: **456 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 231 `COMPLETED`, 60 approved gates**.
- `SIM-02-09` becomes `EXECUTOR_READY`; `SIM-02-10` remains `PLANNED_BLOCKED`.
