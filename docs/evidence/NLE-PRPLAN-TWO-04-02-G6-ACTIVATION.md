# NLE-PRPLAN-TWO-04-02 — G6 contract activation

**Status:** `G6 CONTRACT ACTIVATION / DOCUMENTATION ONLY / NO CODE AUTHORIZED BY THIS RECORD`. **Base main:** `dfb0953`. **Formal packet:** `NLE-PRPLAN-TWO-04-02`. **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-04-02](../work-orders/NLE-PRPLAN-TWO-04-02.md).

## Authorization

The owner authorized continuation on 2026-11-24. TWO-04-01 is approved. This gate freezes the exact API and allowlists; it does not authorize code.

## Capability admission

- Formal dependencies are `TWO-01` and `GFX-04`; neither is module-qualified.
- Admission uses completed internal capabilities.
- `module_completion_claimed=false`.

## Frozen surface

- `stormline::hybrid` common types, errors, capacities and diagnostic.
- `plan_camera` (CAM-01), `plan_layers` (LAY-01), `plan_sort` (SRT-01), `plan_effects` (EFE-01).
- QLF-T401..T404 integrated qualification definitions.
- Exact per-slice allowlists for `-03`..`-07`; no production `.cpp`.

No renderer, camera matrix/trigonometry, GPU resource, depth attachment, shader, lighting, subview execution, editor, export, hardware, ABI or release is authorized.

## Gate state after merge

- Manifest root `TWO04_02_APPROVED_CONTRACT_ONLY`: **527 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 175 `COMPLETED`, 46 approved gates**.
- `TWO-04-02` becomes `APPROVED_CONTRACT`; `TWO-04-03`..`-08` remain `PLANNED_BLOCKED`.
