# NLE-PRPLAN-GFX-03-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `3523c7e`. **Formal packet:** `NLE-PRPLAN-GFX-03-03`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-03-03](../work-orders/NLE-PRPLAN-GFX-03-03.md).

## Authorization

The owner authorized continuation on 2026-11-22. GFX-03-01/-02 are approved. This gate activates only definition validation after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-01` and `CORE-03`; neither is module-qualified.
- Admission uses completed GFX-01 and CORE-03 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/render_graph/graph_types.hpp`
- `src/stormline/graphics/render_graph/graph_definition.hpp`
- `tests/core/gfx03_graph_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-03-03.md`

DEF-01 is required. No native GPU/allocator/submission is permitted.

## Gate state after merge

- Manifest root `GFX03_03_READY_L1_CAPABILITY_OVERLAY`: **613 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 106 `COMPLETED`, 28 approved gates**.
- `GFX-03-03` becomes `EXECUTOR_READY`; `GFX-03-04`..`-09` remain `PLANNED_BLOCKED`.
