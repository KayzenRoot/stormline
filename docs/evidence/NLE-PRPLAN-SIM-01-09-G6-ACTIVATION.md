# NLE-PRPLAN-SIM-01-09 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `b9833f50`. **Formal packet:** `NLE-PRPLAN-SIM-01-09`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-01-09](../work-orders/NLE-PRPLAN-SIM-01-09.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-01-01..-08 are approved or completed. This gate activates only integrated internal qualification.

## Capability admission

- Formal dependencies are `WORLD-01` and `TWO-01`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/sim01_qualification_tests.cpp` with QLF-S101..S104
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-01-09.md`

No production header may change. No contact generation, broadphase, solver/backend, simulation, ECS mutation, GPU or physics runtime is permitted.

## Gate state after merge

- Manifest root `SIM01_09_READY_L1_CAPABILITY_OVERLAY`: **466 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 223 `COMPLETED`, 58 approved gates**.
- `SIM-01-09` becomes `EXECUTOR_READY`; `SIM-01-10` remains `PLANNED_BLOCKED`.
