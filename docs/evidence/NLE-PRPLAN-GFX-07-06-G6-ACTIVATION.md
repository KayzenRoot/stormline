# NLE-PRPLAN-GFX-07-06 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `d3a49d6`. **Formal packet:** `NLE-PRPLAN-GFX-07-06`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-07-06](../work-orders/NLE-PRPLAN-GFX-07-06.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-07-01/-05 are approved/completed. This gate activates only logical reconstruction strategy after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependency is `GFX-06`; it is not module-qualified.
- Admission uses completed GFX-06 lighting capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/post/reconstruction_plan.hpp`
- `tests/core/gfx07_reconstruction_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-07-06.md`

RCN-01 is required. No TAA, vendor SDK, GPU or submission is permitted.

## Gate state after merge

- Manifest root `GFX07_06_READY_L1_CAPABILITY_OVERLAY`: **571 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 140 `COMPLETED`, 36 approved gates**.
- `GFX-07-06` becomes `EXECUTOR_READY`; `GFX-07-07`..`-10` remain `PLANNED_BLOCKED`.
