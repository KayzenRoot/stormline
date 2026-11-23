# NLE-PRPLAN-TWO-02-08 — G6 qualification activation

**Status:** `G6 QUALIFICATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `bc90d00`. **Formal packet:** `NLE-PRPLAN-TWO-02-08`. **ADR:** [ADR-0124](../adr/0124-two-02-internal-tilemap-pipeline.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-02-08](../work-orders/NLE-PRPLAN-TWO-02-08.md).

## Authorization

The owner authorized continuation on 2026-11-23. TWO-02-01/-07 are approved/completed. This gate activates only internal integrated qualification.

## Capability admission

- Formal dependencies are `TWO-01` and `DATA-04`; neither is module-qualified.
- Admission uses completed TWO-01 and DATA-04 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/two02_tilemap_qualification_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-TWO-02-08.md`

QLF-T201..T204 are required. No renderer, GPU, importer, streaming I/O, collision solver, physics or visual output is permitted.

## Gate state after merge

- Manifest root `TWO02_08_READY_L1_CAPABILITY_OVERLAY`: **539 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 166 `COMPLETED`, 42 approved gates**.
- `TWO-02-08` becomes `EXECUTOR_READY`; `TWO-02-09` remains `PLANNED_BLOCKED`.
