# NLE-PRPLAN-GFX-02-01 — G6 governance activation

**Status:** `G6 GOVERNANCE ACTIVATION / DOCUMENTATION ONLY`. **Base main:** `a4c37e3`. **Formal packet:** `NLE-PRPLAN-GFX-02-01`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **Contract:** [gfx-02-governance-v0](../contracts/gfx-02-governance-v0.md). **WO:** [NLE-PRPLAN-GFX-02-01](../work-orders/NLE-PRPLAN-GFX-02-01.md).

## Authorization

The owner authorized continuation on 2026-11-22. This gate records governance only; contract `-02` and every implementation slice require separate gates.

## Capability admission

- Formal dependencies are `GFX-01` and `DATA-03`; neither is module-qualified.
- Admission uses completed GFX-01 RHI and DATA-03 import/validation capabilities.
- `module_completion_claimed=false`.

## Activated scope

Documentation only: ADR-0116, internal architecture, governance contract, WO, manifest/validator/tests/checkpoint. No source code is activated.

## Gate state after merge

- Manifest root `GFX02_01_APPROVED_GOVERNANCE_ONLY`: **624 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 99 `COMPLETED`, 25 approved gates**.
- `GFX-02-01` becomes `APPROVED_GOVERNANCE`; `GFX-02-02`..`-09` remain `PLANNED_BLOCKED`.
