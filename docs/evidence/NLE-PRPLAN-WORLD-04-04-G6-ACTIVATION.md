# NLE-PRPLAN-WORLD-04-04 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `9a4f237`. **Formal packet:** `NLE-PRPLAN-WORLD-04-04`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-04-04](../work-orders/NLE-PRPLAN-WORLD-04-04.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-04-01..-03 are approved or completed. This gate activates only logical splat/material layer metadata.

## Capability admission

- Formal dependencies are `WORLD-03` and `GFX-04`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/terrain/splat_plan.hpp`
- `tests/core/world04_splat_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-WORLD-04-04.md`

SPL-01 is required. No texture residency, material graph, PBR blending, terrain renderer, GPU, physics/network, editor or GPU resource is permitted.

## Gate state after merge

- Manifest root `WORLD04_04_READY_L1_CAPABILITY_OVERLAY`: **491 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 202 `COMPLETED`, 54 approved gates**.
- `WORLD-04-04` becomes `EXECUTOR_READY`; `WORLD-04-05`..`-10` remain `PLANNED_BLOCKED`.
