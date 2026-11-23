# NLE-PRPLAN-GFX-08-07 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `71b27df`. **Formal packet:** `NLE-PRPLAN-GFX-08-07`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-08-07](../work-orders/NLE-PRPLAN-GFX-08-07.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-08-01/-06 are approved/completed. This gate activates only the logical density-stamp slice.

## Capability admission

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- Admission uses completed GFX-01/02/03/05/06/07 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/vfx/density_plan.hpp`
- `tests/core/gfx08_density_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-GFX-08-07.md`

DEN-01 is required. No volume, froxel, scattering, GPU, compute, shader or render is permitted.

## Gate state after merge

- Manifest root `GFX08_07_READY_L1_CAPABILITY_OVERLAY`: **560 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 149 `COMPLETED`, 38 approved gates**.
- `GFX-08-07` becomes `EXECUTOR_READY`; `GFX-08-08`..`-10` remain `PLANNED_BLOCKED`.
