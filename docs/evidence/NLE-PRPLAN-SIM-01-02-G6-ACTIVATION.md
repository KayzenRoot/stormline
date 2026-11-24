# NLE-PRPLAN-SIM-01-02 — G6 contract activation

**Status:** `G6 CONTRACT ACTIVATION / DOCUMENTATION ONLY / NO CODE AUTHORIZED BY THIS RECORD`. **Base main:** `64eeff5`. **Formal packet:** `NLE-PRPLAN-SIM-01-02`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-01-02](../work-orders/NLE-PRPLAN-SIM-01-02.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-01-01 is approved. This gate freezes the exact API and allowlists; it does not authorize code.

## Capability admission

- Formal dependencies are `WORLD-01` and `TWO-01`; neither is module-qualified.
- Admission uses completed internal capabilities.
- `module_completion_claimed=false`.

## Frozen surface

- `stormline::physics2d` common types, errors, capacities and diagnostic.
- `plan_bodies` (BODY-01), `plan_shapes` (COL-01), `plan_queries` (QRY-01), `plan_joints` (JNT-01), `plan_triggers` (TRG-01), `plan_masks`/`masks_compatible` (MSK-01).
- QLF-S101..S104 integrated qualification definitions.
- Exact per-slice allowlists for `-03`..`-09`; no production `.cpp`.

No solver/backend, simulation, broadphase/narrowphase, query execution, contact/event dispatch, ECS mutation, tilemap bridge, GPU, performance, ABI or release is authorized. ADR-0031 remains `PROPOSED`.

## Gate state after merge

- Manifest root `SIM01_02_APPROVED_CONTRACT_ONLY`: **473 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 217 `COMPLETED`, 58 approved gates**.
- `SIM-01-02` becomes `APPROVED_CONTRACT`; `SIM-01-03`..`-10` remain `PLANNED_BLOCKED`.
