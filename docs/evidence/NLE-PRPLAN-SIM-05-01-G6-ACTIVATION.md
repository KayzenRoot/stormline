# NLE-PRPLAN-SIM-05-01 — G6 governance activation

**Status:** `G6 GOVERNANCE ACTIVATION / NO IMPLEMENTATION AUTHORIZED`. **Base main:** `84b0064a`. **Formal packet:** `NLE-PRPLAN-SIM-05-01`. **ADR:** [ADR-0136](../adr/0136-sim-05-internal-navigation-behavior-metadata.md). **Architecture:** [sim-05-internal-navigation-behavior-metadata](../architecture/sim-05-internal-navigation-behavior-metadata.md). **Contract:** [sim-05-governance-v0](../contracts/sim-05-governance-v0.md). **WO:** [NLE-PRPLAN-SIM-05-01](../work-orders/NLE-PRPLAN-SIM-05-01.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-05 follows the completed internal sequences of WORLD-03 and SIM-02. This gate approves only logical governance and metadata boundaries.

## Capability admission

- Formal dependencies are `WORLD-03` and `SIM-02`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- ADR-0136, internal architecture and governance contract.
- WO, this evidence, activation JSON and checkpoint/manifest bookkeeping.

No source, test, CMake or workflow file may change. No navmesh build, pathfinding, steering, behavior runtime, perception, ECS mutation, GPU or runtime is permitted.

## Gate state after merge

- Manifest root `SIM05_01_APPROVED_GOVERNANCE_ONLY`: **436 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 247 `COMPLETED`, 65 approved gates**.
- `SIM-05-01` becomes `APPROVED_GOVERNANCE`; `SIM-05-02`..`-08` remain `PLANNED_BLOCKED`.
