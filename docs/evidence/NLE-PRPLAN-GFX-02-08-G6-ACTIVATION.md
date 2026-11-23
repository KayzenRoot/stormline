# NLE-PRPLAN-GFX-02-08 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `378c7af`. **Formal packet:** `NLE-PRPLAN-GFX-02-08`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-02-08](../work-orders/NLE-PRPLAN-GFX-02-08.md).

## Authorization

The owner authorized continuation on 2026-11-22. GFX-02-01..07 are approved/completed. This gate activates only CI qualification after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-01` and `DATA-03`; neither is module-qualified.
- Admission uses completed GFX-01 and DATA-03 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/gfx02_shader_qualification_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-02-08.md`

QLF-S01..S04 are required. No native compiler/GPU/hardware qualification is permitted.

## Gate state after merge

- Manifest root `GFX02_08_READY_L1_CAPABILITY_OVERLAY`: **617 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 104 `COMPLETED`, 26 approved gates**.
- `GFX-02-08` becomes `EXECUTOR_READY`; `GFX-02-09` remains `PLANNED_BLOCKED`.
