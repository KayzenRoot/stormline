# NLE-PRPLAN-GFX-05-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `6e51af6`. **Formal packet:** `NLE-PRPLAN-GFX-05-03`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-05-03](../work-orders/NLE-PRPLAN-GFX-05-03.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-05-01/-02 are approved. This gate activates only logical PBR material validation after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-02` and `DATA-03`; neither is module-qualified.
- Admission uses completed GFX-02 and DATA-03 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/material/material_types.hpp`
- `src/stormline/graphics/material/pbr_material.hpp`
- `tests/core/gfx05_material_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-05-03.md`

PBR-01 is required. No native GPU/codec/upload/submission is permitted.

## Gate state after merge

- Manifest root `GFX05_03_READY_L1_CAPABILITY_OVERLAY`: **594 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 121 `COMPLETED`, 32 approved gates**.
- `GFX-05-03` becomes `EXECUTOR_READY`; `GFX-05-04`..`-10` remain `PLANNED_BLOCKED`.
