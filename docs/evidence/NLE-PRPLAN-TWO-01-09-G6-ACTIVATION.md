# NLE-PRPLAN-TWO-01-09 — G6 qualification activation

**Status:** `G6 QUALIFICATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `517f573`. **Formal packet:** `NLE-PRPLAN-TWO-01-09`. **ADR:** [ADR-0123](../adr/0123-two-01-internal-canvas-pipeline.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-01-09](../work-orders/NLE-PRPLAN-TWO-01-09.md).

## Authorization

The owner authorized continuation on 2026-11-23. TWO-01-01/-08 are approved/completed. This gate activates only internal integrated qualification.

## Capability admission

- Formal dependencies are `GFX-01` and `DATA-03`; neither is module-qualified.
- Admission uses completed GFX-01/02/03/05/06/07 and DATA-03 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/two01_canvas_qualification_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-TWO-01-09.md`

QLF-T101..T104 are required. No renderer, GPU, rasterization, text/vector, lighting execution or visual output is permitted.

## Gate state after merge

- Manifest root `TWO01_09_READY_L1_CAPABILITY_OVERLAY`: **548 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 159 `COMPLETED`, 40 approved gates**.
- `TWO-01-09` becomes `EXECUTOR_READY`; `TWO-01-10` remains `PLANNED_BLOCKED`.
