# NLE-PRPLAN-SIM-02-05 — Broadphase layer metadata 3D evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO BROADPHASE EXECUTION`. **Base:** `3e1d1d53`. **Gate:** [NLE-PRPLAN-SIM-02-05-G6-ACTIVATION](NLE-PRPLAN-SIM-02-05-G6-ACTIVATION.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-02-05](../work-orders/NLE-PRPLAN-SIM-02-05.md). **PR:** #950.

## Scope delivered

- `src/stormline/physics3d/layer_plan.hpp`: `LayerDesc`, `LayerSetDesc`, `LayerPlan`, `layers_compatible`, `plan_layers`.
- `tests/core/sim02_layer_tests.cpp`: BROAD3-01.
- Additive CMake target/test and TSan target.
- No AABB tree, sweep, narrowphase, contacts, solver, simulation, ECS mutation, GPU, physics runtime, ABI or release claim.

## Implementation notes

- World ID/revision nonzero; count `0..32`; layer IDs nonzero and unique; revision nonzero; layer/mask bits nonzero.
- `layers_compatible` is symmetric: nonzero group on either side requires equal nonzero groups and overrides bit tests; otherwise both layer masks must intersect the other mask.
- Plan reports distinct nonzero groups and compatible ordered pairs `i < j`; reset and typed diagnostic on failure.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict `-Werror`, ASan/UBSan and TSan builds with `broad301` — PASS.

## Errors and corrections

- None; implementation follows the frozen contract exactly.

## Security and architecture

- Header-only internal C++20; no allocation, exception, I/O, GPU, clock, thread, random source or global state. No candidate generation or collision pipeline.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No AABB tree, sweep, narrowphase, contacts, solver/backend, simulation, ECS mutation, GPU, physics runtime, performance, ABI or release.
- `SIM-02-06`..`-10` remain blocked until their gates.

## Proposed checkpoint delta

After merge, record `SIM-02-05` as `COMPLETED`, manifest `SIM02_05_COMPLETED_REST_BLOCKED`: **460 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 228 `COMPLETED`, 60 approved gates**. Checkpoint promotion remains owner-only.
