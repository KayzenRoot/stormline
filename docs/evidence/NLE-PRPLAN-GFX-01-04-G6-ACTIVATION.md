# NLE-PRPLAN-GFX-01-04 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `90b247c`. **Formal packet:** `NLE-PRPLAN-GFX-01-04`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md). **WO:** [NLE-PRPLAN-GFX-01-04](../work-orders/NLE-PRPLAN-GFX-01-04.md).

## Authorization

The owner authorized continuation on 2026-11-22. GFX-01-01..03 are approved/completed. This gate activates only logical queue roles after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `CORE-01` and `CORE-02`; neither is module-qualified.
- Admission uses completed CORE-01 and CORE-02 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/rhi/rhi_queue.hpp`
- `tests/core/gfx01_queue_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-01-04.md`

QUE-01 is required. No native queue/GPU is permitted.

## Gate state after merge

- Manifest root `GFX01_04_READY_L1_CAPABILITY_OVERLAY`: **631 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 92 `COMPLETED`, 24 approved gates**.
- `GFX-01-04` becomes `EXECUTOR_READY`; `GFX-01-05`..`-10` remain `PLANNED_BLOCKED`.
