# NLE-PRPLAN-GFX-02-02 — G6 contract activation

**Status:** `G6 CONTRACT ACTIVATION / NO CODE AUTHORIZED`. **Base main:** `c1f0b89`. **Formal packet:** `NLE-PRPLAN-GFX-02-02`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-02-02](../work-orders/NLE-PRPLAN-GFX-02-02.md).

## Authorization

The owner authorized continuation on 2026-11-22. This gate freezes the contract only; implementation slices `-03`..`-08` require separate G6 activations.

## Capability admission

- Formal dependencies are `GFX-01` and `DATA-03`; neither is module-qualified.
- Admission uses completed GFX-01 RHI and DATA-03 import/validation capabilities.
- `module_completion_claimed=false`.

## Activated scope

Documentation only: exact SSCL-0 API contract, WO, activation record, manifest/validator/tests/checkpoint. No source code is activated.

## Gate state after merge

- Manifest root `GFX02_02_APPROVED_CONTRACT_ONLY`: **623 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 99 `COMPLETED`, 26 approved gates**.
- `GFX-02-02` becomes `APPROVED_CONTRACT`; `GFX-02-03`..`-09` remain `PLANNED_BLOCKED`.
