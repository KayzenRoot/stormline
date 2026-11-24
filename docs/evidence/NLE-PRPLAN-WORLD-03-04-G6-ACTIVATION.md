# NLE-PRPLAN-WORLD-03-04 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `c5cc0e5`. **Formal packet:** `NLE-PRPLAN-WORLD-03-04`. **ADR:** [ADR-0129](../adr/0129-world-03-internal-spatial-streaming-metadata.md). **Contract:** [world-03-spatial-internal-v0](../contracts/world-03-spatial-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-03-04](../work-orders/NLE-PRPLAN-WORLD-03-04.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-03-01/-02/-03 are approved or completed. This gate activates only logical interest-query metadata.

## Capability admission

- Formal dependencies are `WORLD-02` and `DATA-05`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/spatial/interest_plan.hpp`
- `tests/core/world03_interest_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-WORLD-03-04.md`

INT-01 is required. No spatial index, query result, cell storage, streaming task, I/O, decode, cache, origin rebase, physics/network, editor or GPU is permitted.

## Gate state after merge

- Manifest root `WORLD03_04_READY_L1_CAPABILITY_OVERLAY`: **499 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 196 `COMPLETED`, 52 approved gates**.
- `WORLD-03-04` becomes `EXECUTOR_READY`; `WORLD-03-05`..`-08` remain `PLANNED_BLOCKED`.
