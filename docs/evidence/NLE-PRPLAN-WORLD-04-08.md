# NLE-PRPLAN-WORLD-04-08 — Weather visual intent metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO CLIMATE SIMULATION OR WEATHER AUTHORITY`. **Base:** `194e41c`. **Gate:** [NLE-PRPLAN-WORLD-04-08-G6-ACTIVATION](NLE-PRPLAN-WORLD-04-08-G6-ACTIVATION.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-04-08](../work-orders/NLE-PRPLAN-WORLD-04-08.md). **PR:** pendente.

## Scope delivered

- `src/stormline/terrain/weather_plan.hpp`: zone/set descriptors, plan and `plan_weather`.
- `tests/core/world04_weather_tests.cpp`: CLI-01.
- Additive CMake test target and TSan target.
- No climate simulation, weather authority, particle system, wetness, GPU, physics, networking, editor, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Asset ID and revision must be nonzero; zone count is `0..32`.
- Zone IDs are nonzero and unique; revisions, source ticks and source revisions are nonzero.
- Rain/snow intensities are finite in `[0, 1]`; wind speed and fog density are finite `>= 0`.
- Acknowledgement counts are reported as authored; no acknowledgement is fabricated.
- Plan returns acknowledged/pending counts and intensity maxima; an empty set reports zeros.
- Invalid input zeroes the plan and sets a typed diagnostic with the asset ID and zone index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/world04_weather_tests.cpp` — PASS.
- ASan/UBSan build and `cli01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `cli01` — PASS.

## Errors and corrections

- None during implementation; strict compile and sanitizers passed first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread or global state.
- Logical weather visual intent only; GAME/NET, CORE-06 and GFX-08 remain the runtime owners.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No climate simulation, weather authority, particles/wetness, rendering, GPU, physics/networking, editor, performance, ABI or release.
- `WORLD-04-09`..`-10` remain blocked until their gates.
- WORLD-03/GFX-04 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-04-08` as `COMPLETED`, manifest `WORLD04_08_COMPLETED_REST_BLOCKED`: **487 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 207 `COMPLETED`, 54 approved gates**. Checkpoint promotion remains owner-only.
