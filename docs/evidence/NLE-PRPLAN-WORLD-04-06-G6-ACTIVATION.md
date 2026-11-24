# NLE-PRPLAN-WORLD-04-06 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `794cf42`. **Formal packet:** `NLE-PRPLAN-WORLD-04-06`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-04-06](../work-orders/NLE-PRPLAN-WORLD-04-06.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-04-01..-05 are approved or completed. This gate activates only logical water-body metadata.

## Capability admission

- Formal dependencies are `WORLD-03` and `GFX-04`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/terrain/water_plan.hpp`
- `tests/core/world04_water_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-WORLD-04-06.md`

WAT-01 is required. No water simulation, buoyancy, surface renderer, physics volume, network, editor or GPU resource is permitted.

## Gate state after merge

- Manifest root `WORLD04_06_READY_L1_CAPABILITY_OVERLAY`: **489 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 204 `COMPLETED`, 54 approved gates**.
- `WORLD-04-06` becomes `EXECUTOR_READY`; `WORLD-04-07`..`-10` remain `PLANNED_BLOCKED`.
