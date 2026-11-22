# NLE-PRPLAN-GFX-01-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `255e8e2`. **Formal packet:** `NLE-PRPLAN-GFX-01-03`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md). **WO:** [NLE-PRPLAN-GFX-01-03](../work-orders/NLE-PRPLAN-GFX-01-03.md).

## Authorization

The owner authorized continuation on 2026-11-22. GFX-01-01..02 are approved. This gate activates only logical adapters/devices after Docs Validation and pt-BR audit; it does not authorize a native GPU backend.

## Capability admission

- Formal dependencies are `CORE-01` and `CORE-02`; neither is module-qualified.
- Admission uses completed CORE-01 and CORE-02 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/rhi/rhi_types.hpp`
- `src/stormline/graphics/rhi/rhi_device.hpp` core
- `tests/core/gfx01_device_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-01-03.md`

DEV-01 is required. No native GPU, render or shader is permitted.

## Gate state after merge

- Manifest root `GFX01_03_READY_L1_CAPABILITY_OVERLAY`: **632 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 91 `COMPLETED`, 24 approved gates**.
- `GFX-01-03` becomes `EXECUTOR_READY`; `GFX-01-04`..`-10` remain `PLANNED_BLOCKED`.
