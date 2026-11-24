# NLE-PRPLAN-SIM-01-04 — Collision shape metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO COLLISION`. **Base:** `958d020`. **Gate:** [NLE-PRPLAN-SIM-01-04-G6-ACTIVATION](NLE-PRPLAN-SIM-01-04-G6-ACTIVATION.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-01-04](../work-orders/NLE-PRPLAN-SIM-01-04.md). **PR:** pendente.

## Scope delivered

- `src/stormline/physics2d/shape_plan.hpp`: shape descriptors, plan and `plan_shapes`.
- `tests/core/sim01_shape_tests.cpp`: COL-01.
- Additive CMake test target and TSan target.
- No broadphase/narrowphase, contact manifold, solver/backend, simulation, ECS mutation, GPU, physics runtime, ABI, release, hardware or performance claim.

## Implementation notes

- World ID/revision must be nonzero; shape count is `0..128`.
- Shape IDs are nonzero and unique; body references and revisions are nonzero.
- Kind is `Circle`, `Box`, `Capsule` or `Polygon`.
- Circle/capsule require `radius > 0`; box/polygon require `half_x > 0` and `half_y > 0`; all dimensions finite; density finite `>= 0`.
- Plan reports kind counts and sensor count; no shape, contact or collision is created.
- Invalid input zeroes the plan and sets a typed diagnostic with the world ID and shape index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/sim01_shape_tests.cpp` — PASS.
- ASan/UBSan build and `col01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `col01` — PASS.

## Errors and corrections

- None during implementation; strict compile and sanitizers passed first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread, random source or global state.
- Logical shape descriptors only; no collision pipeline exists.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No broadphase/narrowphase, contacts, simulation, solver/backend, ECS mutation, GPU, physics runtime, performance, ABI or release.
- `SIM-01-05`..`-10` remain blocked until their gates.
- WORLD-01/TWO-01 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `SIM-01-04` as `COMPLETED`, manifest `SIM01_04_COMPLETED_REST_BLOCKED`: **471 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 219 `COMPLETED`, 58 approved gates**. Checkpoint promotion remains owner-only.
