# NLE-PRPLAN-SIM-02-02 — G6 contract activation

**Status:** `G6 CONTRACT ACTIVATION / NO IMPLEMENTATION AUTHORIZED`. **Base main:** `229e2ff9`. **Formal packet:** `NLE-PRPLAN-SIM-02-02`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-02-02](../work-orders/NLE-PRPLAN-SIM-02-02.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-02-01 governance is approved. This gate freezes only the internal logical contract.

## Capability admission

- Formal dependencies are `WORLD-02` and `CORE-03`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `docs/contracts/sim-02-physics3d-internal-v0.md` with exact types, capacities, error model, oracles and allowlists `-03`..`-09`.
- WO, this evidence, activation JSON and checkpoint/manifest bookkeeping.

No source, test, CMake or workflow file may change. No solver, backend, broadphase, query execution, contact, simulation, ECS mutation, GPU or physics runtime is permitted.

## Gate state after merge

- Manifest root `SIM02_02_APPROVED_CONTRACT_ONLY`: **464 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 225 `COMPLETED`, 60 approved gates**.
- `SIM-02-02` becomes `APPROVED_CONTRACT`; `SIM-02-03`..`-10` remain `PLANNED_BLOCKED`.
