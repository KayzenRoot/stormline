# NLE-PRPLAN-GFX-08-01 — G6 governance activation

**Status:** `G6 GOVERNANCE ACTIVATION / DOCUMENTATION ONLY`. **Base main:** `eb81362`. **Formal packet:** `NLE-PRPLAN-GFX-08-01`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-governance-v0](../contracts/gfx-08-governance-v0.md). **WO:** [NLE-PRPLAN-GFX-08-01](../work-orders/NLE-PRPLAN-GFX-08-01.md).

## Authorization

The owner authorized continuation on 2026-11-23. This gate records governance only; contract `-02` and every implementation slice require separate gates.

## Capability admission

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- Admission uses completed GFX-01/02/03/05/06/07 capabilities.
- `module_completion_claimed=false`.

## Activated scope

Documentation only: ADR-0122, internal architecture, governance contract, WO, activation record, manifest/validator/tests/checkpoint. No source code is activated.

## Gate state after merge

- Manifest root `GFX08_01_APPROVED_GOVERNANCE_ONLY`: **566 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 145 `COMPLETED`, 37 approved gates**.
- `GFX-08-01` becomes `APPROVED_GOVERNANCE`; `GFX-08-02`..`-10` remain `PLANNED_BLOCKED`.
