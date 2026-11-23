# NLE-PRPLAN-GFX-08-05 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `ded41b4`. **Formal packet:** `NLE-PRPLAN-GFX-08-05`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-08-05](../work-orders/NLE-PRPLAN-GFX-08-05.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-08-01/-04 are approved/completed. This gate activates only the logical trail-budget slice.

## Capability admission

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- Admission uses completed GFX-01/02/03/05/06/07 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/vfx/trail_plan.hpp`
- `tests/core/gfx08_trail_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-GFX-08-05.md`

TRL-01 is required. No trail history, tessellation, GPU, compute, shader or render is permitted.

## Gate state after merge

- Manifest root `GFX08_05_READY_L1_CAPABILITY_OVERLAY`: **562 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 147 `COMPLETED`, 38 approved gates**.
- `GFX-08-05` becomes `EXECUTOR_READY`; `GFX-08-06`..`-10` remain `PLANNED_BLOCKED`.
