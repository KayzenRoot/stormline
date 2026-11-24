# NLE-PRPLAN-WORLD-04-05 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `aa60d1b`. **Formal packet:** `NLE-PRPLAN-WORLD-04-05`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-04-05](../work-orders/NLE-PRPLAN-WORLD-04-05.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-04-01..-04 are approved or completed. This gate activates only logical vegetation placement metadata.

## Capability admission

- Formal dependencies are `WORLD-03` and `GFX-04`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/terrain/vegetation_plan.hpp`
- `tests/core/world04_vegetation_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-WORLD-04-05.md`

VEG-01 is required. No instance buffer, GPU instancing, collider, physics, network, editor or GPU resource is permitted.

## Gate state after merge

- Manifest root `WORLD04_05_READY_L1_CAPABILITY_OVERLAY`: **490 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 203 `COMPLETED`, 54 approved gates**.
- `WORLD-04-05` becomes `EXECUTOR_READY`; `WORLD-04-06`..`-10` remain `PLANNED_BLOCKED`.
