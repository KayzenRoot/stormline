# NLE-PRPLAN-SIM-02-03 — Rigid body metadata 3D evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PHYSICS RUNTIME`. **Base:** `03673d2e`. **Gate:** [NLE-PRPLAN-SIM-02-03-G6-ACTIVATION](NLE-PRPLAN-SIM-02-03-G6-ACTIVATION.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-02-03](../work-orders/NLE-PRPLAN-SIM-02-03.md). **PR:** #946.

## Scope delivered

- `src/stormline/physics3d/physics3d_types.hpp`: aliases, capacities, `Physics3DError`, kind enums, diagnostic and detail helpers.
- `src/stormline/physics3d/body_plan.hpp`: `BodyDesc`, `BodySetDesc`, `BodyPlan`, `plan_bodies`.
- `tests/core/sim02_body_tests.cpp`: BODY3-01.
- Additive CMake target/test and TSan target.
- No solver, broadphase, query execution, contacts, simulation, ECS mutation, GPU, physics runtime, ABI, release, hardware or performance claim.

## Implementation notes

- World ID/revision must be nonzero; body count is `0..64`.
- Body IDs nonzero and unique; revisions nonzero; kind allowlist.
- Pose components finite; quaternion unit rule `|len² − 1| <= 1e-3`; density `>= 0`; damping `0..1`.
- Plan counts kinds and enabled bodies; invalid input zeroes the plan and sets a typed diagnostic with world ID and body index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/sim02_body_tests.cpp` — PASS.
- ASan/UBSan build and `body301` — PASS.
- TSan build under `setarch $(uname -m) -R` and `body301` — PASS.

## Errors and corrections

- None during implementation; the contract was frozen before code and matched the implementation exactly.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread, random source or global state.
- Logical body descriptors only; no integration, solver handle or backend type.

## Rollback

Revert normally; remove the headers/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No solver, broadphase, query execution, contact generation, simulation, ECS mutation, GPU, physics runtime, performance, ABI or release.
- `SIM-02-04`..`-10` remain blocked until their gates.
- WORLD-02/CORE-03 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `SIM-02-03` as `COMPLETED`, manifest `SIM02_03_COMPLETED_REST_BLOCKED`: **462 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 226 `COMPLETED`, 60 approved gates**. Checkpoint promotion remains owner-only.
