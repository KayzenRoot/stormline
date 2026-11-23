# NLE-PRPLAN-GFX-05-01 — G6 governance activation

**Status:** `G6 GOVERNANCE ACTIVATION / DOCUMENTATION ONLY`. **Base main:** `eafb62a`. **Formal packet:** `NLE-PRPLAN-GFX-05-01`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-governance-v0](../contracts/gfx-05-governance-v0.md). **WO:** [NLE-PRPLAN-GFX-05-01](../work-orders/NLE-PRPLAN-GFX-05-01.md).

## Authorization

The owner authorized continuation on 2026-11-23. This gate records governance only; contract `-02` and every implementation slice require separate gates.

## Capability admission

- Formal dependencies are `GFX-02` and `DATA-03`; neither is module-qualified.
- Admission uses completed GFX-02 shader and DATA-03 import/validation capabilities.
- `module_completion_claimed=false`.

## Activated scope

Documentation only: ADR-0119, internal architecture, governance contract, WO, manifest/validator/tests/checkpoint. No source code is activated.

## Gate state after merge

- Manifest root `GFX05_01_APPROVED_GOVERNANCE_ONLY`: **596 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 121 `COMPLETED`, 31 approved gates**.
- `GFX-05-01` becomes `APPROVED_GOVERNANCE`; `GFX-05-02`..`-10` remain `PLANNED_BLOCKED`.
