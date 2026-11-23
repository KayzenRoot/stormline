# NLE-PRPLAN-GFX-03-04 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `0342cc5`. **Formal packet:** `NLE-PRPLAN-GFX-03-04`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-03-04](../work-orders/NLE-PRPLAN-GFX-03-04.md).

## Authorization

The owner authorized continuation on 2026-11-22. GFX-03-01..03 are approved/completed. This gate activates only dependency/hazard analysis after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-01` and `CORE-03`; neither is module-qualified.
- Admission uses completed GFX-01 and CORE-03 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/render_graph/graph_dependency.hpp`
- `tests/core/gfx03_dependency_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-03-04.md`

DEP-01 is required. No native GPU/allocator/submission is permitted.

## Gate state after merge

- Manifest root `GFX03_04_READY_L1_CAPABILITY_OVERLAY`: **612 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 107 `COMPLETED`, 28 approved gates**.
- `GFX-03-04` becomes `EXECUTOR_READY`; `GFX-03-05`..`-09` remain `PLANNED_BLOCKED`.
