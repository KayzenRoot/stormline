# NLE-PRPLAN-GFX-07-09 — G6 qualification activation

**Status:** `G6 QUALIFICATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `bac24a7`. **Formal packet:** `NLE-PRPLAN-GFX-07-09`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-07-09](../work-orders/NLE-PRPLAN-GFX-07-09.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-07-01/-08 are approved/completed. This gate activates only internal integrated qualification after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependency is `GFX-06`; it is not module-qualified.
- Admission uses completed GFX-01/02/03/05/06 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/gfx07_post_qualification_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-07-09.md`

QLF-G701..G704 are required. No native GPU, swapchain, HDR signal, tone mapper, LUT/OCIO, TAA, upscaler, rendering or hardware qualification is permitted.

## Gate state after merge

- Manifest root `GFX07_09_READY_L1_CAPABILITY_OVERLAY`: **568 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 143 `COMPLETED`, 36 approved gates**.
- `GFX-07-09` becomes `EXECUTOR_READY`; `GFX-07-10` remains `PLANNED_BLOCKED`.
