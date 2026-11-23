# NLE-PRPLAN-GFX-03-01 — G6 governance activation

**Status:** `G6 GOVERNANCE ACTIVATION / DOCUMENTATION ONLY`. **Base main:** `4abac08`. **Formal packet:** `NLE-PRPLAN-GFX-03-01`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **Contract:** [gfx-03-governance-v0](../contracts/gfx-03-governance-v0.md). **WO:** [NLE-PRPLAN-GFX-03-01](../work-orders/NLE-PRPLAN-GFX-03-01.md).

## Authorization

The owner authorized continuation on 2026-11-22. This gate records governance only; contract `-02` and every implementation slice require separate gates.

## Capability admission

- Formal dependencies are `GFX-01` and `CORE-03`; neither is module-qualified.
- Admission uses completed GFX-01 RHI and CORE-03 scheduling/dependency capabilities.
- `module_completion_claimed=false`.

## Activated scope

Documentation only: ADR-0117, internal architecture, governance contract, WO, manifest/validator/tests/checkpoint. No source code is activated.

## Gate state after merge

- Manifest root `GFX03_01_APPROVED_GOVERNANCE_ONLY`: **615 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 106 `COMPLETED`, 27 approved gates**.
- `GFX-03-01` becomes `APPROVED_GOVERNANCE`; `GFX-03-02`..`-09` remain `PLANNED_BLOCKED`.
