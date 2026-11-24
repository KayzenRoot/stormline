# NLE-PRPLAN-SIM-01-08 — Collision mask metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO CONTACT GENERATION`. **Base:** `4c16311`. **Gate:** [NLE-PRPLAN-SIM-01-08-G6-ACTIVATION](NLE-PRPLAN-SIM-01-08-G6-ACTIVATION.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-01-08](../work-orders/NLE-PRPLAN-SIM-01-08.md). **PR:** #939.

## Scope delivered

- `src/stormline/physics2d/mask_plan.hpp`: mask descriptors, plan, `plan_masks` and `masks_compatible`.
- `tests/core/sim01_mask_tests.cpp`: MSK-01.
- Additive CMake test target and TSan target.
- No contact generation, broadphase, solver/backend, simulation, ECS mutation, GPU, physics runtime, ABI, release, hardware or performance claim.

## Implementation notes

- World ID/revision must be nonzero; mask count is `0..32`.
- Mask IDs are nonzero and unique; revisions nonzero; category and collision bits nonzero.
- `masks_compatible` is symmetric: a nonzero group on either side requires equal nonzero groups and overrides the bit test; otherwise both category masks must intersect the other collision mask.
- Plan reports distinct nonzero group count and compatible ordered pairs `i < j`; no contact is generated.
- Invalid input zeroes the plan and sets a typed diagnostic with the world ID and mask index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/sim01_mask_tests.cpp` — PASS.
- ASan/UBSan build and `msk01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `msk01` — PASS.

## Errors and corrections

- Corrected the capacity pair-count fixture to 240 (120 same-group + 120 bit-compatible pairs); strict compile and sanitizers passed.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread, random source or global state.
- Logical mask descriptors only; physics layers are independent of render layers.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No contact generation, broadphase, simulation, solver/backend, ECS mutation, GPU, physics runtime, performance, ABI or release.
- `SIM-01-09`..`-10` remain blocked until their gates.
- WORLD-01/TWO-01 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `SIM-01-08` as `COMPLETED`, manifest `SIM01_08_COMPLETED_REST_BLOCKED`: **467 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 223 `COMPLETED`, 58 approved gates**. Checkpoint promotion remains owner-only.
