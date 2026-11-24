# NLE-PRPLAN-TWO-04-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `3c4f030`. **Formal packet:** `NLE-PRPLAN-TWO-04-03`. **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-04-03](../work-orders/NLE-PRPLAN-TWO-04-03.md).

## Authorization

The owner authorized continuation on 2026-11-24. TWO-04-01/-02 are approved. This gate activates only logical camera intent metadata.

## Capability admission

- Formal dependencies are `TWO-01` and `GFX-04`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/hybrid/hybrid_types.hpp`
- `src/stormline/hybrid/camera_plan.hpp`
- `tests/core/two04_camera_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-TWO-04-03.md`

CAM-01 is required. No camera matrix, trigonometry, frustum, renderer, GPU, layer, sort, effect, audio or export is permitted.

## Gate state after merge

- Manifest root `TWO04_03_READY_L1_CAPABILITY_OVERLAY`: **526 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 175 `COMPLETED`, 46 approved gates**.
- `TWO-04-03` becomes `EXECUTOR_READY`; `TWO-04-04`..`-08` remain `PLANNED_BLOCKED`.
