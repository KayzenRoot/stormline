# NLE-PRPLAN-SIM-02-08 — Integration metadata 3D evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO RUNTIME BRIDGE`. **Base:** `f0f9eb4c`. **Gate:** [NLE-PRPLAN-SIM-02-08-G6-ACTIVATION](NLE-PRPLAN-SIM-02-08-G6-ACTIVATION.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-02-08](../work-orders/NLE-PRPLAN-SIM-02-08.md). **PR:** pendente.

## Scope delivered

- `src/stormline/physics3d/integration_plan.hpp`: `IntegrationDesc`, `IntegrationSetDesc`, `IntegrationPlan`, `plan_integrations`.
- `tests/core/sim02_integration_tests.cpp`: INTEGRATION3-01.
- Additive CMake target/test and TSan target.
- No ECS mutation, scene/physics bridge, streaming execution, tick runtime, solver, GPU, physics runtime, ABI or release claim.

## Implementation notes

- Set world ID/revision nonzero; count `0..64`; IDs/revision nonzero and unique; kind allowlist; descriptor world must equal set world.
- Scene requires scene_id; Streaming requires cell_id; Authority requires authority_bits; Tick requires `1..240` Hz with min/max tracking.
- Plan counts kinds; reset and typed diagnostic on failure.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict `-Werror`, ASan/UBSan and TSan builds with `integration301` — PASS.

## Errors and corrections

- None; implementation follows the frozen contract exactly.

## Security and architecture

- Header-only internal C++20; no allocation, exception, I/O, GPU, clock, thread, random source or global state. No ECS write or bridge execution.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No ECS mutation, bridge, streaming, tick runtime, solver/backend, simulation, GPU, physics runtime, performance, ABI or release.
- `SIM-02-09`..`-10` remain blocked until their gates.

## Proposed checkpoint delta

After merge, record `SIM-02-08` as `COMPLETED`, manifest `SIM02_08_COMPLETED_REST_BLOCKED`: **457 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 231 `COMPLETED`, 60 approved gates**. Checkpoint promotion remains owner-only.
