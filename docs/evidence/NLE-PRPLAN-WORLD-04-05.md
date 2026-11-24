# NLE-PRPLAN-WORLD-04-05 — Vegetation placement metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO INSTANCE BUFFER OR VEGETATION RUNTIME`. **Base:** `ad86cd4`. **Gate:** [NLE-PRPLAN-WORLD-04-05-G6-ACTIVATION](NLE-PRPLAN-WORLD-04-05-G6-ACTIVATION.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-04-05](../work-orders/NLE-PRPLAN-WORLD-04-05.md). **PR:** pendente.

## Scope delivered

- `src/stormline/terrain/vegetation_plan.hpp`: group/set descriptors, plan and `plan_vegetation`.
- `tests/core/world04_vegetation_tests.cpp`: VEG-01.
- Additive CMake test target and TSan target.
- No instance buffer, GPU instancing, collider, physics, renderer, streamer, networking, editor, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Asset ID and revision must be nonzero; group count is `0..32`.
- Group keys and prototype asset IDs are nonzero; group keys are unique; revisions are nonzero.
- `1 <= instance_count <= density_limit <= 4096`; checked total is `<= 4096`.
- Group bounds are finite and ordered; NaN/infinities are rejected separately from reversed ranges.
- `collider_group_count` reports authored collider intent; no collider is created.
- Invalid input zeroes the plan and sets a typed diagnostic with the asset ID and group index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/world04_vegetation_tests.cpp` — PASS.
- ASan/UBSan build and `veg01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `veg01` — PASS.

## Errors and corrections

- Split non-finite and reversed-bound diagnostics before testing; strict compile and sanitizers passed.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread or global state.
- Logical placement metadata only; GFX-04, PHYS and WORLD-05 remain the runtime owners.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No instance buffer, GPU instancing, collider/physics, rendering, networking, editor, performance, ABI or release.
- `WORLD-04-06`..`-10` remain blocked until their gates.
- WORLD-03/GFX-04 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-04-05` as `COMPLETED`, manifest `WORLD04_05_COMPLETED_REST_BLOCKED`: **490 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 204 `COMPLETED`, 54 approved gates**. Checkpoint promotion remains owner-only.
