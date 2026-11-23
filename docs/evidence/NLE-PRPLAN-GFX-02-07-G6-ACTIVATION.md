# NLE-PRPLAN-GFX-02-07 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `ff683bb`. **Formal packet:** `NLE-PRPLAN-GFX-02-07`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-02-07](../work-orders/NLE-PRPLAN-GFX-02-07.md).

## Authorization

The owner authorized continuation on 2026-11-22. GFX-02-01..06 are approved/completed. This gate activates only dependency-revision invalidation after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-01` and `DATA-03`; neither is module-qualified.
- Admission uses completed GFX-01 and DATA-03 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/shader/shader_incremental.hpp`
- `tests/core/gfx02_incremental_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-02-07.md`

INC-01 is required. No persistence, file watching or native compiler is permitted.

## Gate state after merge

- Manifest root `GFX02_07_READY_L1_CAPABILITY_OVERLAY`: **618 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 103 `COMPLETED`, 26 approved gates**.
- `GFX-02-07` becomes `EXECUTOR_READY`; `GFX-02-08`..`-09` remain `PLANNED_BLOCKED`.
