# NLE-PRPLAN-GFX-08-04 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `b8fd0c4`. **Formal packet:** `NLE-PRPLAN-GFX-08-04`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-08-04](../work-orders/NLE-PRPLAN-GFX-08-04.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-08-01/-03 are approved/completed. This gate activates only the logical ribbon-budget slice.

## Capability admission

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- Admission uses completed GFX-01/02/03/05/06/07 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/vfx/ribbon_plan.hpp`
- `tests/core/gfx08_ribbon_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-GFX-08-04.md`

RIB-01 is required. No tessellation, spline, GPU, compute, shader or render is permitted.

## Gate state after merge

- Manifest root `GFX08_04_READY_L1_CAPABILITY_OVERLAY`: **563 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 146 `COMPLETED`, 38 approved gates**.
- `GFX-08-04` becomes `EXECUTOR_READY`; `GFX-08-05`..`-10` remain `PLANNED_BLOCKED`.
