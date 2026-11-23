# NLE-PRPLAN-GFX-07-05 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `c5872c6`. **Formal packet:** `NLE-PRPLAN-GFX-07-05`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-07-05](../work-orders/NLE-PRPLAN-GFX-07-05.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-07-01/-04 are approved/completed. This gate activates only logical HDR output negotiation after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependency is `GFX-06`; it is not module-qualified.
- Admission uses completed GFX-06 lighting capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/post/output_plan.hpp`
- `tests/core/gfx07_output_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-07-05.md`

HDR-01 is required. No swapchain, HDR signal, GPU or submission is permitted.

## Gate state after merge

- Manifest root `GFX07_05_READY_L1_CAPABILITY_OVERLAY`: **572 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 139 `COMPLETED`, 36 approved gates**.
- `GFX-07-05` becomes `EXECUTOR_READY`; `GFX-07-06`..`-10` remain `PLANNED_BLOCKED`.
