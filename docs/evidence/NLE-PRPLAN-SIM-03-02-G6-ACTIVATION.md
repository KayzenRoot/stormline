# NLE-PRPLAN-SIM-03-02 — G6 contract activation

**Status:** `G6 CONTRACT ACTIVATION / NO IMPLEMENTATION AUTHORIZED`. **Base main:** `c36e620a`. **Formal packet:** `NLE-PRPLAN-SIM-03-02`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-03-02](../work-orders/NLE-PRPLAN-SIM-03-02.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-03-01 governance is approved. This gate freezes only the internal logical contract.

## Capability admission

- Formal dependencies are `SIM-01` and `SIM-02`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `docs/contracts/sim-03-character-internal-v0.md` with exact types, capacities, error model, oracles and allowlists `-03`..`-07`.
- WO, this evidence, activation JSON and checkpoint/manifest bookkeeping.

No source, test, CMake or workflow file may change. No motor, sweeper, contact, input device, camera update, ECS mutation, GPU or character runtime is permitted.

## Gate state after merge

- Manifest root `SIM03_02_APPROVED_CONTRACT_ONLY`: **453 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 233 `COMPLETED`, 62 approved gates**.
- `SIM-03-02` becomes `APPROVED_CONTRACT`; `SIM-03-03`..`-08` remain `PLANNED_BLOCKED`.
