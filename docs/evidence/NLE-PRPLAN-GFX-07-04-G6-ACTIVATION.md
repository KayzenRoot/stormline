# NLE-PRPLAN-GFX-07-04 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `c6e4aa9`. **Formal packet:** `NLE-PRPLAN-GFX-07-04`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-07-04](../work-orders/NLE-PRPLAN-GFX-07-04.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-07-01/-03 are approved/completed. This gate activates only logical tone/color planning after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependency is `GFX-06`; it is not module-qualified.
- Admission uses completed GFX-06 lighting capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/post/tone_color.hpp`
- `tests/core/gfx07_color_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-07-04.md`

COL-01 is required. No tone mapper, LUT/OCIO, GPU or submission is permitted.

## Gate state after merge

- Manifest root `GFX07_04_READY_L1_CAPABILITY_OVERLAY`: **573 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 138 `COMPLETED`, 36 approved gates**.
- `GFX-07-04` becomes `EXECUTOR_READY`; `GFX-07-05`..`-10` remain `PLANNED_BLOCKED`.
