# NLE-PRPLAN-GFX-04-06 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `edb2058`. **Formal packet:** `NLE-PRPLAN-GFX-04-06`. **ADR:** [ADR-0118](../adr/0118-gfx-04-internal-geometry-pipeline.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-04-06](../work-orders/NLE-PRPLAN-GFX-04-06.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-04-01..05 are approved/completed. This gate activates only stream request planning after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-03` and `DATA-05`; neither is module-qualified.
- Admission uses completed GFX-03 and DATA-05 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/geometry/geometry_stream.hpp`
- `tests/core/gfx04_stream_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-04-06.md`

STR-01 is required. No native I/O/network/codec/GPU/submission is permitted.

## Gate state after merge

- Manifest root `GFX04_06_READY_L1_CAPABILITY_OVERLAY`: **601 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 116 `COMPLETED`, 30 approved gates**.
- `GFX-04-06` becomes `EXECUTOR_READY`; `GFX-04-07`..`-10` remain `PLANNED_BLOCKED`.
