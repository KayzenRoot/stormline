# NLE-PRPLAN-SIM-01-03 — Rigid body metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PHYSICS SOLVER`. **Base:** `3125557`. **Gate:** [NLE-PRPLAN-SIM-01-03-G6-ACTIVATION](NLE-PRPLAN-SIM-01-03-G6-ACTIVATION.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-01-03](../work-orders/NLE-PRPLAN-SIM-01-03.md). **PR:** pendente.

## Scope delivered

- `src/stormline/physics2d/physics2d_types.hpp`: aliases, capacities, errors, body/shape/query/joint enums and diagnostic.
- `src/stormline/physics2d/body_plan.hpp`: body descriptors, plan and `plan_bodies`.
- `tests/core/sim01_body_tests.cpp`: BODY-01.
- Additive CMake interface target/test and TSan target.
- No solver, backend dependency, simulation, broadphase/narrowphase, ECS mutation, GPU, physics runtime, ABI, release, hardware or performance claim.

## Implementation notes

- World ID/revision must be nonzero; body count is `0..64`.
- Body IDs and revisions are nonzero and unique; kind is `Static`, `Kinematic` or `Dynamic`.
- Pose and angle must be finite; density is finite `>= 0`; damping is finite in `[0, 1]`.
- Plan reports kind counts and enabled count; no body is created or simulated.
- Invalid input zeroes the plan and sets a typed diagnostic with the world ID and body index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/sim01_body_tests.cpp` — PASS.
- ASan/UBSan build and `body01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `body01` — PASS.

## Errors and corrections

- None during implementation; strict compile and sanitizers passed first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread, random source or global state.
- Logical body descriptors only; no solver, backend or simulation exists.

## Rollback

Revert normally; remove the headers/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No solver/backend, simulation, collision, queries, contacts/events, ECS mutation, GPU, physics runtime, performance, ABI or release.
- `SIM-01-04`..`-10` remain blocked until their gates.
- WORLD-01/TWO-01 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `SIM-01-03` as `COMPLETED`, manifest `SIM01_03_COMPLETED_REST_BLOCKED`: **472 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 218 `COMPLETED`, 58 approved gates**. Checkpoint promotion remains owner-only.
