# NLE-PRPLAN-SIM-03-01 — G6 governance activation

**Status:** `G6 GOVERNANCE ACTIVATION / NO IMPLEMENTATION AUTHORIZED`. **Base main:** `7a868c02`. **Formal packet:** `NLE-PRPLAN-SIM-03-01`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Architecture:** [sim-03-internal-character-motor-metadata](../architecture/sim-03-internal-character-motor-metadata.md). **Contract:** [sim-03-governance-v0](../contracts/sim-03-governance-v0.md). **WO:** [NLE-PRPLAN-SIM-03-01](../work-orders/NLE-PRPLAN-SIM-03-01.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-03 follows the completed internal sequences of SIM-01 and SIM-02. This gate approves only logical governance and metadata boundaries.

## Capability admission

- Formal dependencies are `SIM-01` and `SIM-02`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- ADR-0134, internal architecture and governance contract.
- WO, this evidence, activation JSON and checkpoint/manifest bookkeeping.

No source, test, CMake or workflow file may change. No motor, sweeper, contact execution, input device, camera update, ECS mutation, GPU or character runtime is permitted.

## Gate state after merge

- Manifest root `SIM03_01_APPROVED_GOVERNANCE_ONLY`: **454 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 233 `COMPLETED`, 61 approved gates**.
- `SIM-03-01` becomes `APPROVED_GOVERNANCE`; `SIM-03-02`..`-08` remain `PLANNED_BLOCKED`.
