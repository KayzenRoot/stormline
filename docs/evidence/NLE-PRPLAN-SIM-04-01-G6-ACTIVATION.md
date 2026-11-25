# NLE-PRPLAN-SIM-04-01 — G6 governance activation

**Status:** `G6 GOVERNANCE ACTIVATION / NO IMPLEMENTATION AUTHORIZED`. **Base main:** `ebd5d0b7`. **Formal packet:** `NLE-PRPLAN-SIM-04-01`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Architecture:** [sim-04-internal-skeletal-animation-metadata](../architecture/sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-governance-v0](../contracts/sim-04-governance-v0.md). **WO:** [NLE-PRPLAN-SIM-04-01](../work-orders/NLE-PRPLAN-SIM-04-01.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-04 follows the completed internal sequences of SIM-03 and DATA-03. This gate approves only logical governance and metadata boundaries.

## Capability admission

- Formal dependencies are `SIM-03` and `DATA-03`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- ADR-0135, internal architecture and governance contract.
- WO, this evidence, activation JSON and checkpoint/manifest bookkeeping.

No source, test, CMake or workflow file may change. No pose evaluation, solver, ragdoll, codec, root-motion application, ECS mutation, GPU or animation runtime is permitted.

## Gate state after merge

- Manifest root `SIM04_01_APPROVED_GOVERNANCE_ONLY`: **446 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 239 `COMPLETED`, 63 approved gates**.
- `SIM-04-01` becomes `APPROVED_GOVERNANCE`; `SIM-04-02`..`-10` remain `PLANNED_BLOCKED`.
