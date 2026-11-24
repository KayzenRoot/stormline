# NLE-PRPLAN-WORLD-02-08 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `8819d57`. **Formal packet:** `NLE-PRPLAN-WORLD-02-08`. **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Contract:** [world-02-scene-internal-v0](../contracts/world-02-scene-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-02-08](../work-orders/NLE-PRPLAN-WORLD-02-08.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-02-01..-07 are approved. This gate activates only integrated internal qualification fixtures.

## Capability admission

- Formal dependencies are `WORLD-01` and `DATA-02`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/world02_qualification_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-WORLD-02-08.md`

QLF-S201..S204 are required. Qualification is internal CI only; no runtime scene, expansion, merge, serializer, hardware or performance qualification is claimed.

## Gate state after merge

- Manifest root `WORLD02_08_READY_L1_CAPABILITY_OVERLAY`: **504 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 193 `COMPLETED`, 50 approved gates**.
- `WORLD-02-08` becomes `EXECUTOR_READY`; `WORLD-02-09` remains `PLANNED_BLOCKED`.
