# NLE-PRPLAN-SIM-01-06 — Joint metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO CONSTRAINT SOLVER`. **Base:** `9bdf96c`. **Gate:** [NLE-PRPLAN-SIM-01-06-G6-ACTIVATION](NLE-PRPLAN-SIM-01-06-G6-ACTIVATION.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-01-06](../work-orders/NLE-PRPLAN-SIM-01-06.md). **PR:** #935.

## Scope delivered

- `src/stormline/physics2d/joint_plan.hpp`: joint descriptors, plan and `plan_joints`.
- `tests/core/sim01_joint_tests.cpp`: JNT-01.
- Additive CMake test target and TSan target.
- No constraint solver, joint runtime, solver/backend, simulation, ECS mutation, GPU, physics runtime, ABI, release, hardware or performance claim.

## Implementation notes

- World ID/revision must be nonzero; joint count is `0..64`.
- Joint IDs are nonzero and unique; revisions nonzero; body references nonzero and distinct.
- Kind is `Distance`, `Revolute`, `Prismatic` or `Weld`.
- Anchors and limits are finite; `min_limit <= max_limit`.
- Plan reports kind counts and `collide_connected` count; no constraint is solved.
- Invalid input zeroes the plan and sets a typed diagnostic with the world ID and joint index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/sim01_joint_tests.cpp` — PASS.
- ASan/UBSan build and `jnt01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `jnt01` — PASS.

## Errors and corrections

- None during implementation; strict compile and sanitizers passed first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread, random source or global state.
- Logical joint descriptors only; no constraint solver exists.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No constraint solver/runtime, simulation, solver/backend, ECS mutation, GPU, physics runtime, performance, ABI or release.
- `SIM-01-07`..`-10` remain blocked until their gates.
- WORLD-01/TWO-01 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `SIM-01-06` as `COMPLETED`, manifest `SIM01_06_COMPLETED_REST_BLOCKED`: **469 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 221 `COMPLETED`, 58 approved gates**. Checkpoint promotion remains owner-only.
