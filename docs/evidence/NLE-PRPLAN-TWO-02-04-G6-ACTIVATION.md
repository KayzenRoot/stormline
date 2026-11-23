# NLE-PRPLAN-TWO-02-04 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `6144d4f`. **Formal packet:** `NLE-PRPLAN-TWO-02-04`. **ADR:** [ADR-0124](../adr/0124-two-02-internal-tilemap-pipeline.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-02-04](../work-orders/NLE-PRPLAN-TWO-02-04.md).

## Authorization

The owner authorized continuation on 2026-11-23. TWO-02-01/-03 are approved/completed. This gate activates only the logical tile-cell slice.

## Capability admission

- Formal dependencies are `TWO-01` and `DATA-04`; neither is module-qualified.
- Admission uses completed TWO-01 and DATA-04 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/tilemap/tile_plan.hpp`
- `tests/core/two02_tile_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-TWO-02-04.md`

TIL-01 is required. No tile rendering, sprite instance, GPU or draw is permitted.

## Gate state after merge

- Manifest root `TWO02_04_READY_L1_CAPABILITY_OVERLAY`: **543 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 162 `COMPLETED`, 42 approved gates**.
- `TWO-02-04` becomes `EXECUTOR_READY`; `TWO-02-05`..`-09` remain `PLANNED_BLOCKED`.
