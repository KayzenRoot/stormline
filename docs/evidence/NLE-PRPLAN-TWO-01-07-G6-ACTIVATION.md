# NLE-PRPLAN-TWO-01-07 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `7d0b638`. **Formal packet:** `NLE-PRPLAN-TWO-01-07`. **ADR:** [ADR-0123](../adr/0123-two-01-internal-canvas-pipeline.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-01-07](../work-orders/NLE-PRPLAN-TWO-01-07.md).

## Authorization

The owner authorized continuation on 2026-11-23. TWO-01-01/-06 are approved/completed. This gate activates only the logical pixel-slap slice.

## Capability admission

- Formal dependencies are `GFX-01` and `DATA-03`; neither is module-qualified.
- Admission uses completed GFX-01/02/03/05/06/07 and DATA-03 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/canvas2d/snap_plan.hpp`
- `tests/core/two01_snap_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-TWO-01-07.md`

SNP-01 is required. No pixel sampling, rasterization, GPU or render is permitted.

## Gate state after merge

- Manifest root `TWO01_07_READY_L1_CAPABILITY_OVERLAY`: **550 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 157 `COMPLETED`, 40 approved gates**.
- `TWO-01-07` becomes `EXECUTOR_READY`; `TWO-01-08`..`-10` remain `PLANNED_BLOCKED`.
