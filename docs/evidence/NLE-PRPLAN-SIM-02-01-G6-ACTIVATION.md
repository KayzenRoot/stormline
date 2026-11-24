# NLE-PRPLAN-SIM-02-01 — G6 governance activation

**Status:** `G6 GOVERNANCE ACTIVATION / NO IMPLEMENTATION AUTHORIZED`. **Base main:** `1c7a6880`. **Formal packet:** `NLE-PRPLAN-SIM-02-01`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Architecture:** [sim-02-internal-physics-3d-metadata](../architecture/sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-governance-v0](../contracts/sim-02-governance-v0.md). **WO:** [NLE-PRPLAN-SIM-02-01](../work-orders/NLE-PRPLAN-SIM-02-01.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-02 follows the completed internal sequences of WORLD-02 and CORE-03. This gate approves only logical governance and metadata boundaries.

## Capability admission

- Formal dependencies are `WORLD-02` and `CORE-03`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- ADR-0133, internal architecture and governance contract.
- WO, this evidence, activation JSON and checkpoint/manifest bookkeeping.

No source, test, CMake or workflow file may change. No solver, backend, broadphase, query execution, contact, simulation, ECS mutation, GPU or physics runtime is permitted.

## Gate state after merge

- Manifest root `SIM02_01_APPROVED_GOVERNANCE_ONLY`: **464 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 225 `COMPLETED`, 59 approved gates**.
- `SIM-02-01` becomes `APPROVED_GOVERNANCE`; `SIM-02-02`..`-10` remain `PLANNED_BLOCKED`.
