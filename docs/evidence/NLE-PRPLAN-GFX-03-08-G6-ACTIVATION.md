# NLE-PRPLAN-GFX-03-08 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `8da2f35`. **Formal packet:** `NLE-PRPLAN-GFX-03-08`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-03-08](../work-orders/NLE-PRPLAN-GFX-03-08.md).

## Authorization

The owner authorized continuation on 2026-11-22. GFX-03-01..07 are approved/completed. This gate activates only CI qualification after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-01` and `CORE-03`; neither is module-qualified.
- Admission uses completed GFX-01 and CORE-03 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/gfx03_graph_qualification_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-03-08.md`

QLF-G301..G304 are required. No native GPU/allocator/submission/hardware qualification is permitted.

## Gate state after merge

- Manifest root `GFX03_08_READY_L1_CAPABILITY_OVERLAY`: **608 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 111 `COMPLETED`, 28 approved gates**.
- `GFX-03-08` becomes `EXECUTOR_READY`; `GFX-03-09` remains `PLANNED_BLOCKED`.
