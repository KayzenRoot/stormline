# NLE-PRPLAN-GFX-03-02 — G6 contract activation

**Status:** `G6 CONTRACT ACTIVATION / NO CODE AUTHORIZED`. **Base main:** `2686632`. **Formal packet:** `NLE-PRPLAN-GFX-03-02`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-03-02](../work-orders/NLE-PRPLAN-GFX-03-02.md).

## Authorization

The owner authorized continuation on 2026-11-22. This gate freezes the contract only; implementation slices `-03`..`-08` require separate G6 activations.

## Capability admission

- Formal dependencies are `GFX-01` and `CORE-03`; neither is module-qualified.
- Admission uses completed GFX-01 RHI and CORE-03 scheduling capabilities.
- `module_completion_claimed=false`.

## Activated scope

Documentation only: exact logical graph API contract, WO, activation record, manifest/validator/tests/checkpoint. No source code is activated.

## Gate state after merge

- Manifest root `GFX03_02_APPROVED_CONTRACT_ONLY`: **614 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 106 `COMPLETED`, 28 approved gates**.
- `GFX-03-02` becomes `APPROVED_CONTRACT`; `GFX-03-03`..`-09` remain `PLANNED_BLOCKED`.
