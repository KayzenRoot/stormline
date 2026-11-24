# NLE-PRPLAN-WORLD-02-06 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `b0a2135`. **Formal packet:** `NLE-PRPLAN-WORLD-02-06`. **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Contract:** [world-02-scene-internal-v0](../contracts/world-02-scene-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-02-06](../work-orders/NLE-PRPLAN-WORLD-02-06.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-02-01..-05 are approved. This gate activates only logical prefab instance metadata.

## Capability admission

- Formal dependencies are `WORLD-01` and `DATA-02`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/scene/instance_plan.hpp`
- `tests/core/world02_instance_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-WORLD-02-06.md`

INS-01 is required. No runtime instancing, entity creation, prefab expansion, serializer, journal, transform, editor or GPU is permitted.

## Gate state after merge

- Manifest root `WORLD02_06_READY_L1_CAPABILITY_OVERLAY`: **506 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 191 `COMPLETED`, 50 approved gates**.
- `WORLD-02-06` becomes `EXECUTOR_READY`; `WORLD-02-07`..`-09` remain `PLANNED_BLOCKED`.
