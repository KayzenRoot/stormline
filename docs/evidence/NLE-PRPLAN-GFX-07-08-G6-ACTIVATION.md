# NLE-PRPLAN-GFX-07-08 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `145df17`. **Formal packet:** `NLE-PRPLAN-GFX-07-08`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-07-08](../work-orders/NLE-PRPLAN-GFX-07-08.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-07-01/-07 are approved/completed. This gate activates only logical render-scale/upscale metadata after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependency is `GFX-06`; it is not module-qualified.
- Admission uses completed GFX-06 lighting capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/post/upscale_plan.hpp`
- `tests/core/gfx07_upscale_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-07-08.md`

UPS-01 is required. No upscaler, SDK, GPU or submission is permitted.

## Gate state after merge

- Manifest root `GFX07_08_READY_L1_CAPABILITY_OVERLAY`: **569 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 142 `COMPLETED`, 36 approved gates**.
- `GFX-07-08` becomes `EXECUTOR_READY`; `GFX-07-09`..`-10` remain `PLANNED_BLOCKED`.
