# NLE-PRPLAN-GFX-05-06 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `2ee232b`. **Formal packet:** `NLE-PRPLAN-GFX-05-06`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-05-06](../work-orders/NLE-PRPLAN-GFX-05-06.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-05-01/-05 are approved/completed. This gate activates only logical sampler/filter profile validation after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-02` and `DATA-03`; neither is module-qualified.
- Admission uses completed GFX-02 and DATA-03 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/material/texture_sampler.hpp`
- `tests/core/gfx05_sampler_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-05-06.md`

SMP-01 is required. No GPU/driver sampler object, upload or submission is permitted.

## Gate state after merge

- Manifest root `GFX05_06_READY_L1_CAPABILITY_OVERLAY`: **591 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 124 `COMPLETED`, 32 approved gates**.
- `GFX-05-06` becomes `EXECUTOR_READY`; `GFX-05-07`..`-10` remain `PLANNED_BLOCKED`.
