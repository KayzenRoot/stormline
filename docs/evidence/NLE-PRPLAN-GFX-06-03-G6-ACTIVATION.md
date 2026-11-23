# NLE-PRPLAN-GFX-06-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `4b49b09`. **Formal packet:** `NLE-PRPLAN-GFX-06-03`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-06-03](../work-orders/NLE-PRPLAN-GFX-06-03.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-06-01/-02 are approved. This gate activates only logical light validation after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- Admission uses completed GFX-03 and GFX-05 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/lighting/lighting_types.hpp`
- `src/stormline/graphics/lighting/light.hpp`
- `tests/core/gfx06_light_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-06-03.md`

LGT-01 is required. No native GPU/shadow map/ray tracing/submission is permitted.

## Gate state after merge

- Manifest root `GFX06_03_READY_L1_CAPABILITY_OVERLAY`: **584 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 129 `COMPLETED`, 34 approved gates**.
- `GFX-06-03` becomes `EXECUTOR_READY`; `GFX-06-04`..`-10` remain `PLANNED_BLOCKED`.
