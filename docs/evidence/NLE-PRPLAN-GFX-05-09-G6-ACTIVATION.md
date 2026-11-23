# NLE-PRPLAN-GFX-05-09 — G6 qualification activation

**Status:** `G6 QUALIFICATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `953dc83`. **Formal packet:** `NLE-PRPLAN-GFX-05-09`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-05-09](../work-orders/NLE-PRPLAN-GFX-05-09.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-05-01/-08 are approved/completed. This gate activates only internal integrated qualification after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-02` and `DATA-03`; neither is module-qualified.
- Admission uses completed GFX-02 and DATA-03 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/gfx05_material_qualification_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-05-09.md`

QLF-G501..G504 are required. No native GPU, codec, upload, rendering or hardware qualification is permitted.

## Gate state after merge

- Manifest root `GFX05_09_READY_L1_CAPABILITY_OVERLAY`: **588 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 127 `COMPLETED`, 32 approved gates**.
- `GFX-05-09` becomes `EXECUTOR_READY`; `GFX-05-10` remains `PLANNED_BLOCKED`.
