# NLE-PRPLAN-GFX-05-08 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `63836fa`. **Formal packet:** `NLE-PRPLAN-GFX-05-08`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-05-08](../work-orders/NLE-PRPLAN-GFX-05-08.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-05-01/-07 are approved/completed. This gate activates only logical transparency ordering/overdraw metadata after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-02` and `DATA-03`; neither is module-qualified.
- Admission uses completed GFX-02 and DATA-03 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/material/transparency.hpp`
- `tests/core/gfx05_transparency_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-05-08.md`

TRN-01 is required. No blending, GPU or submission is permitted.

## Gate state after merge

- Manifest root `GFX05_08_READY_L1_CAPABILITY_OVERLAY`: **589 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 126 `COMPLETED`, 32 approved gates**.
- `GFX-05-08` becomes `EXECUTOR_READY`; `GFX-05-09`..`-10` remain `PLANNED_BLOCKED`.
