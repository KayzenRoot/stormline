# NLE-PRPLAN-SIM-01-01 — G6 governance activation

**Status:** `G6 GOVERNANCE ACTIVATION / DOCUMENTATION ONLY / NO CODE AUTHORIZED BY THIS RECORD`. **Base main:** `bd9c366`. **Formal packet:** `NLE-PRPLAN-SIM-01-01`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Governance contract:** [sim-01-governance-v0](../contracts/sim-01-governance-v0.md). **WO:** [NLE-PRPLAN-SIM-01-01](../work-orders/NLE-PRPLAN-SIM-01-01.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-01 and TWO-01 internal sequences are complete. This gate approves governance only; it does not authorize code.

## Capability admission

- Formal dependencies are `WORLD-01` and `TWO-01`; neither is module-qualified.
- Admission uses completed internal capabilities.
- `module_completion_claimed=false`.

## Approved surface

- Logical body, collision shape, query, joint, trigger and collision-mask metadata.
- Oracles BODY-01, COL-01, QRY-01, JNT-01, TRG-01, MSK-01 and QLF-S101..S104.
- Slice gates `-02`..`-10` remain individually blocked.

No solver/backend, simulation, broadphase/narrowphase, query execution, contact/event dispatch, ECS mutation, tilemap bridge, physics runtime, GPU, performance, ABI or release is authorized. ADR-0031 remains `PROPOSED`.

## Gate state after merge

- Manifest root `SIM01_01_APPROVED_GOVERNANCE_ONLY`: **474 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 217 `COMPLETED`, 57 approved gates**.
- `SIM-01-01` becomes `APPROVED_GOVERNANCE`; `SIM-01-02`..`-10` remain `PLANNED_BLOCKED`.
