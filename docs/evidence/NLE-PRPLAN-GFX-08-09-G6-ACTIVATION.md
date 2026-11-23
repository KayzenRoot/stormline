# NLE-PRPLAN-GFX-08-09 — G6 qualification activation

**Status:** `G6 QUALIFICATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `02adcbf`. **Formal packet:** `NLE-PRPLAN-GFX-08-09`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-08-09](../work-orders/NLE-PRPLAN-GFX-08-09.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-08-01/-08 are approved/completed. This gate activates only internal integrated qualification.

## Capability admission

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- Admission uses completed GFX-01/02/03/05/06/07 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/gfx08_vfx_qualification_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-GFX-08-09.md`

QLF-G801..G804 are required. No particle simulation, GPU, compute, sort, OIT, volume or render is permitted.

## Gate state after merge

- Manifest root `GFX08_09_READY_L1_CAPABILITY_OVERLAY`: **558 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 151 `COMPLETED`, 38 approved gates**.
- `GFX-08-09` becomes `EXECUTOR_READY`; `GFX-08-10` remains `PLANNED_BLOCKED`.
