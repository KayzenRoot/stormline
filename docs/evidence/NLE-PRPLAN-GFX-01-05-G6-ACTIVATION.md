# NLE-PRPLAN-GFX-01-05 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `1ef4c35`. **Formal packet:** `NLE-PRPLAN-GFX-01-05`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md). **WO:** [NLE-PRPLAN-GFX-01-05](../work-orders/NLE-PRPLAN-GFX-01-05.md).

## Authorization

The owner authorized continuation on 2026-11-22. GFX-01-01..04 are approved/completed. This gate activates only logical buffers after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `CORE-01` and `CORE-02`; neither is module-qualified.
- Admission uses completed CORE-01 and CORE-02 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/rhi/rhi_buffer.hpp`
- `tests/core/gfx01_buffer_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-01-05.md`

BUF-01 is required. No native buffer/GPU memory is permitted.

## Gate state after merge

- Manifest root `GFX01_05_READY_L1_CAPABILITY_OVERLAY`: **630 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 93 `COMPLETED`, 24 approved gates**.
- `GFX-01-05` becomes `EXECUTOR_READY`; `GFX-01-06`..`-10` remain `PLANNED_BLOCKED`.
