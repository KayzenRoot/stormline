# NLE-PRPLAN-GFX-06-02 — G6 contract activation

**Status:** `G6 CONTRACT ACTIVATION / NO CODE AUTHORIZED`. **Base main:** `533d983`. **Formal packet:** `NLE-PRPLAN-GFX-06-02`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-06-02](../work-orders/NLE-PRPLAN-GFX-06-02.md).

## Authorization

The owner authorized continuation on 2026-11-23. This gate freezes the contract only; implementation slices `-03`..`-09` require separate G6 activations.

## Capability admission

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- Admission uses completed GFX-03 render-graph and GFX-05 material/texture capabilities.
- `module_completion_claimed=false`.

## Activated scope

Documentation only: exact logical lighting API contract, WO, activation record, manifest/validator/tests/checkpoint. No source code is activated.

## Gate state after merge

- Manifest root `GFX06_02_APPROVED_CONTRACT_ONLY`: **585 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 129 `COMPLETED`, 34 approved gates**.
- `GFX-06-02` becomes `APPROVED_CONTRACT`; `GFX-06-03`..`-10` remain `PLANNED_BLOCKED`.
