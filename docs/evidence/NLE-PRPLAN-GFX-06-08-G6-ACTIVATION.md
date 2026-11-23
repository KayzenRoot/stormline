# NLE-PRPLAN-GFX-06-08 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `0925f30`. **Formal packet:** `NLE-PRPLAN-GFX-06-08`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-06-08](../work-orders/NLE-PRPLAN-GFX-06-08.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-06-01/-07 are approved/completed. This gate activates only logical volumetric metadata/budget after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- Admission uses completed GFX-03 and GFX-05 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/lighting/volumetric_plan.hpp`
- `tests/core/gfx06_volumetric_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-06-08.md`

VOL-01 is required. No froxel buffer, GPU or submission is permitted.

## Gate state after merge

- Manifest root `GFX06_08_READY_L1_CAPABILITY_OVERLAY`: **579 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 134 `COMPLETED`, 34 approved gates**.
- `GFX-06-08` becomes `EXECUTOR_READY`; `GFX-06-09`..`-10` remain `PLANNED_BLOCKED`.
