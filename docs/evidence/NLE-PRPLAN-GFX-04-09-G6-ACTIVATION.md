# NLE-PRPLAN-GFX-04-09 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `15c30b8`. **Formal packet:** `NLE-PRPLAN-GFX-04-09`. **ADR:** [ADR-0118](../adr/0118-gfx-04-internal-geometry-pipeline.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-04-09](../work-orders/NLE-PRPLAN-GFX-04-09.md).

## Authorization

The owner authorized continuation on 2026-11-23. GFX-04-01..08 are approved/completed. This gate activates only CI qualification after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-03` and `DATA-05`; neither is module-qualified.
- Admission uses completed GFX-03 and DATA-05 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/gfx04_geometry_qualification_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-04-09.md`

QLF-G401..G404 are required. No native GPU/mesh library/I/O/hardware qualification is permitted.

## Gate state after merge

- Manifest root `GFX04_09_READY_L1_CAPABILITY_OVERLAY`: **598 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 119 `COMPLETED`, 30 approved gates**.
- `GFX-04-09` becomes `EXECUTOR_READY`; `GFX-04-10` remains `PLANNED_BLOCKED`.
