# NLE-PRPLAN-WORLD-04-07 — Sky/environment profile metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ATMOSPHERE OR LIGHT RENDERER`. **Base:** `f9ac15b`. **Gate:** [NLE-PRPLAN-WORLD-04-07-G6-ACTIVATION](NLE-PRPLAN-WORLD-04-07-G6-ACTIVATION.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-04-07](../work-orders/NLE-PRPLAN-WORLD-04-07.md). **PR:** pendente.

## Scope delivered

- `src/stormline/terrain/sky_plan.hpp`: profile/set descriptors, plan and `plan_sky`.
- `tests/core/world04_sky_tests.cpp`: SKY-01.
- Additive CMake test target and TSan target.
- No atmosphere/light/fog renderer, HDR/post pipeline, GPU, time authority, physics, networking, editor, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Asset ID and revision must be nonzero; profile count is `1..16`.
- Profile IDs are nonzero and unique; revisions are nonzero; tiers are `Low`, `Medium`, `High` or `Ultra`.
- `time_of_day` is finite in `[0, 24)`; cloud coverage is finite in `[0, 1]`; fog density is finite `>= 0`.
- Sun and moon directions are finite with at least one nonzero component each; no normalization is performed.
- Plan returns tier counts and maximum cloud coverage. No light, atmosphere or renderer is created.
- Invalid input zeroes the plan and sets a typed diagnostic with the asset ID and profile index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/world04_sky_tests.cpp` — PASS.
- ASan/UBSan build and `sky01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `sky01` — PASS.

## Errors and corrections

- None during implementation; strict compile and sanitizers passed first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread or global state.
- Logical sky parameters only; GFX-06/07 and GAME/NET remain the runtime owners.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No atmosphere/light/fog rendering, HDR/post, GPU, physics/networking, editor, performance, ABI or release.
- `WORLD-04-08`..`-10` remain blocked until their gates.
- WORLD-03/GFX-04 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-04-07` as `COMPLETED`, manifest `WORLD04_07_COMPLETED_REST_BLOCKED`: **488 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 206 `COMPLETED`, 54 approved gates**. Checkpoint promotion remains owner-only.
