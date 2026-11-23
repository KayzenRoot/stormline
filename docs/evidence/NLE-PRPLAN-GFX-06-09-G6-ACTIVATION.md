# NLE-PRPLAN-GFX-06-09 — G6 qualification activation

**Status:** `G6 QUALIFICATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `0e254e1`. **Formal packet:** `NLE-PRPLAN-GFX-06-09`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-06-09](../work-orders/NLE-PRPLAN-GFX-06-09.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-06-01/-08 are approved/completed. This gate activates only internal integrated qualification after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- Admission uses completed GFX-03 and GFX-05 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/gfx06_lighting_qualification_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-06-09.md`

QLF-G601..G604 are required. No native GPU, shadow map, ray tracing, GI/probe bake, SSR, froxel, rendering or hardware qualification is permitted.

## Gate state after merge

- Manifest root `GFX06_09_READY_L1_CAPABILITY_OVERLAY`: **578 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 135 `COMPLETED`, 34 approved gates**.
- `GFX-06-09` becomes `EXECUTOR_READY`; `GFX-06-10` remains `PLANNED_BLOCKED`.
