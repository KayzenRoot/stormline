# NLE-PRPLAN-TWO-02-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `b56ae04`. **Formal packet:** `NLE-PRPLAN-TWO-02-03`. **ADR:** [ADR-0124](../adr/0124-two-02-internal-tilemap-pipeline.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-02-03](../work-orders/NLE-PRPLAN-TWO-02-03.md).

## Authorization

The owner authorized continuation on 2026-11-23. TWO-02-01/-02 are approved. This gate activates only the logical grid slice.

## Capability admission

- Formal dependencies are `TWO-01` and `DATA-04`; neither is module-qualified.
- Admission uses completed TWO-01 and DATA-04 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/tilemap/tilemap_types.hpp`
- `src/stormline/tilemap/grid_plan.hpp`
- `tests/core/two02_grid_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-TWO-02-03.md`

GRD-01 is required. No renderer, GPU, map I/O or streaming is permitted.

## Gate state after merge

- Manifest root `TWO02_03_READY_L1_CAPABILITY_OVERLAY`: **544 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 161 `COMPLETED`, 42 approved gates**.
- `TWO-02-03` becomes `EXECUTOR_READY`; `TWO-02-04`..`-09` remain `PLANNED_BLOCKED`.
