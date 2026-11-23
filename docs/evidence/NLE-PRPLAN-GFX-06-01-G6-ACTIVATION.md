# NLE-PRPLAN-GFX-06-01 — G6 governance activation

**Status:** `G6 GOVERNANCE ACTIVATION / DOCUMENTATION ONLY`. **Base main:** `de396b2`. **Formal packet:** `NLE-PRPLAN-GFX-06-01`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Contract:** [gfx-06-governance-v0](../contracts/gfx-06-governance-v0.md). **WO:** [NLE-PRPLAN-GFX-06-01](../work-orders/NLE-PRPLAN-GFX-06-01.md).

## Authorization

The owner authorized continuation on 2026-11-23. This gate records governance only; contract `-02` and every implementation slice require separate gates.

## Capability admission

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- Admission uses completed GFX-03 render-graph and GFX-05 material/texture capabilities.
- `module_completion_claimed=false`.

## Activated scope

Documentation only: ADR-0120, internal architecture, governance contract, WO, activation record, manifest/validator/tests/checkpoint. No source code is activated.

## Gate state after merge

- Manifest root `GFX06_01_APPROVED_GOVERNANCE_ONLY`: **586 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 129 `COMPLETED`, 33 approved gates**.
- `GFX-06-01` becomes `APPROVED_GOVERNANCE`; `GFX-06-02`..`-10` remain `PLANNED_BLOCKED`.
