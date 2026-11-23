# NLE-PRPLAN-GFX-05-02 — G6 contract activation

**Status:** `G6 CONTRACT ACTIVATION / NO CODE AUTHORIZED`. **Base main:** `11d658e`. **Formal packet:** `NLE-PRPLAN-GFX-05-02`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-05-02](../work-orders/NLE-PRPLAN-GFX-05-02.md).

## Authorization

The owner authorized continuation on 2026-11-23. This gate freezes the contract only; implementation slices `-03`..`-09` require separate G6 activations.

## Capability admission

- Formal dependencies are `GFX-02` and `DATA-03`; neither is module-qualified.
- Admission uses completed GFX-02 shader/reflection/variant capabilities and DATA-03 texture import/validation capabilities.
- `module_completion_claimed=false`.

## Activated scope

Documentation only: exact logical material/texture API contract, WO, activation record, manifest/validator/tests/checkpoint. No source code is activated.

## Gate state after merge

- Manifest root `GFX05_02_APPROVED_CONTRACT_ONLY`: **595 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 121 `COMPLETED`, 32 approved gates**.
- `GFX-05-02` becomes `APPROVED_CONTRACT`; `GFX-05-03`..`-10` remain `PLANNED_BLOCKED`.
