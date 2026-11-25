# NLE-PRPLAN-SIM-03-07 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `694a50e8`. **Formal packet:** `NLE-PRPLAN-SIM-03-07`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-03-07](../work-orders/NLE-PRPLAN-SIM-03-07.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-03-01..-06 are approved or completed. This gate activates only integrated internal qualification.

## Capability admission

- Formal dependencies are `SIM-01` and `SIM-02`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/sim03_qualification_tests.cpp` with QLF-S301..S304
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-SIM-03-07.md`

No production header may change. No motor, sweeper, contact execution, input device, camera update, ECS mutation, GPU or character runtime is permitted.

## Gate state after merge

- Manifest root `SIM03_07_READY_L1_CAPABILITY_OVERLAY`: **448 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 237 `COMPLETED`, 62 approved gates**.
- `SIM-03-07` becomes `EXECUTOR_READY`; `SIM-03-08` remains `PLANNED_BLOCKED`.
