# NLE-PRPLAN-GFX-08-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `754f7b5`. **Formal packet:** `NLE-PRPLAN-GFX-08-03`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-08-03](../work-orders/NLE-PRPLAN-GFX-08-03.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-08-01/-02 are approved. This gate activates only the logical graph/emitter slice.

## Capability admission

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- Admission uses completed GFX-01/02/03/05/06/07 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/vfx/vfx_types.hpp`
- `src/stormline/graphics/vfx/graph_plan.hpp`
- `src/stormline/graphics/vfx/emitter_plan.hpp`
- `tests/core/gfx08_particle_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-GFX-08-03.md`

VFX-01 and SPAWN-01 are required. No particle simulation, compute, GPU, sort, OIT, shader or render is permitted.

## Gate state after merge

- Manifest root `GFX08_03_READY_L1_CAPABILITY_OVERLAY`: **564 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 145 `COMPLETED`, 38 approved gates**.
- `GFX-08-03` becomes `EXECUTOR_READY`; `GFX-08-04`..`-10` remain `PLANNED_BLOCKED`.
