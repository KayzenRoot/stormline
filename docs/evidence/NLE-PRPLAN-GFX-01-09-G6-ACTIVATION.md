# NLE-PRPLAN-GFX-01-09 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `b580648`. **Formal packet:** `NLE-PRPLAN-GFX-01-09`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md). **WO:** [NLE-PRPLAN-GFX-01-09](../work-orders/NLE-PRPLAN-GFX-01-09.md).

## Authorization

The owner authorized continuation on 2026-11-22. GFX-01-01..08 are approved/completed. This gate activates only internal CI qualification after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `CORE-01` and `CORE-02`; neither is module-qualified.
- Admission uses completed CORE-01 and CORE-02 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/gfx01_rhi_qualification_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-01-09.md`

QLF-G01..G04 are required. No native GPU, driver, hardware, rendering or performance qualification is permitted.

## Gate state after merge

- Manifest root `GFX01_09_READY_L1_CAPABILITY_OVERLAY`: **626 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 97 `COMPLETED`, 24 approved gates**.
- `GFX-01-09` becomes `EXECUTOR_READY`; `GFX-01-10` remains `PLANNED_BLOCKED`.
