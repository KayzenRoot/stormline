# NLE-PRPLAN-GFX-07-07 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `f272c66`. **Formal packet:** `NLE-PRPLAN-GFX-07-07`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-07-07](../work-orders/NLE-PRPLAN-GFX-07-07.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-07-01/-06 are approved/completed. This gate activates only logical motion-blur policy after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependency is `GFX-06`; it is not module-qualified.
- Admission uses completed GFX-06 lighting capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/post/motion_blur.hpp`
- `tests/core/gfx07_motion_blur_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-07-07.md`

MBL-01 is required. No motion vector generation, blur, GPU or submission is permitted.

## Gate state after merge

- Manifest root `GFX07_07_READY_L1_CAPABILITY_OVERLAY`: **570 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 141 `COMPLETED`, 36 approved gates**.
- `GFX-07-07` becomes `EXECUTOR_READY`; `GFX-07-08`..`-10` remain `PLANNED_BLOCKED`.
