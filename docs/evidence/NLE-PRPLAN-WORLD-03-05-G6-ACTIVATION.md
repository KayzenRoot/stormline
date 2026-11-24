# NLE-PRPLAN-WORLD-03-05 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `9e353ca`. **Formal packet:** `NLE-PRPLAN-WORLD-03-05`. **ADR:** [ADR-0129](../adr/0129-world-03-internal-spatial-streaming-metadata.md). **Contract:** [world-03-spatial-internal-v0](../contracts/world-03-spatial-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-03-05](../work-orders/NLE-PRPLAN-WORLD-03-05.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-03-01/-02/-03/-04 are approved or completed. This gate activates only logical origin-epoch metadata.

## Capability admission

- Formal dependencies are `WORLD-02` and `DATA-05`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/spatial/origin_plan.hpp`
- `tests/core/world03_origin_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-WORLD-03-05.md`

ORG-01 is required. No origin rebase, identity rewrite, cell storage, streaming task, I/O, decode, cache, physics/network, editor or GPU is permitted.

## Gate state after merge

- Manifest root `WORLD03_05_READY_L1_CAPABILITY_OVERLAY`: **498 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 197 `COMPLETED`, 52 approved gates**.
- `WORLD-03-05` becomes `EXECUTOR_READY`; `WORLD-03-06`..`-08` remain `PLANNED_BLOCKED`.
