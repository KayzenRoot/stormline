# NLE-PRPLAN-GFX-07-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `6ad7a83`. **Formal packet:** `NLE-PRPLAN-GFX-07-03`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-07-03](../work-orders/NLE-PRPLAN-GFX-07-03.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-07-01/-02 are approved. This gate activates only logical camera/exposure validation after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependency is `GFX-06`; it is not module-qualified.
- Admission uses completed GFX-06 lighting capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/post/post_types.hpp`
- `src/stormline/graphics/post/camera_exposure.hpp`
- `tests/core/gfx07_camera_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-07-03.md`

CAM-01/EXP-01 are required. No GPU/swapchain/projection matrix/histogram/submission is permitted.

## Gate state after merge

- Manifest root `GFX07_03_READY_L1_CAPABILITY_OVERLAY`: **574 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 137 `COMPLETED`, 36 approved gates**.
- `GFX-07-03` becomes `EXECUTOR_READY`; `GFX-07-04`..`-10` remain `PLANNED_BLOCKED`.
