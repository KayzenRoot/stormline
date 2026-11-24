# NLE-PRPLAN-WORLD-04-06 — Water body metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO WATER SIMULATION OR RENDERING`. **Base:** `482781b`. **Gate:** [NLE-PRPLAN-WORLD-04-06-G6-ACTIVATION](NLE-PRPLAN-WORLD-04-06-G6-ACTIVATION.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-04-06](../work-orders/NLE-PRPLAN-WORLD-04-06.md). **PR:** pendente.

## Scope delivered

- `src/stormline/terrain/water_plan.hpp`: body/set descriptors, plan and `plan_water`.
- `tests/core/world04_water_tests.cpp`: WAT-01.
- Additive CMake test target and TSan target.
- No water simulation, buoyancy, flow, surface renderer, physics volume, GPU, networking, editor, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Asset ID and revision must be nonzero; body count is `0..32`.
- Body keys are nonzero and unique; revisions are nonzero; classes are `Ocean`, `Lake`, `River` or `Local`.
- Bounds and surface/wave parameters must be finite; bounds are ordered; amplitude is `>= 0`; frequency is `> 0`.
- Shore completeness is reported as an incomplete count and never fabricated.
- Plan returns per-class counts and surface-height bounds; an empty set reports zero counts and zero bounds.
- Invalid input zeroes the plan and sets a typed diagnostic with the asset ID and body index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/world04_water_tests.cpp` — PASS.
- ASan/UBSan build and `wat01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `wat01` — PASS.

## Errors and corrections

- None during implementation; strict compile and sanitizers passed first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread or global state.
- Logical water intent only; PHYS/GAME/NET and GFX remain the runtime owners.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No water simulation/buoyancy/flow, rendering, physics volume, networking, editor, GPU, performance, ABI or release.
- `WORLD-04-07`..`-10` remain blocked until their gates.
- WORLD-03/GFX-04 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-04-06` as `COMPLETED`, manifest `WORLD04_06_COMPLETED_REST_BLOCKED`: **489 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 205 `COMPLETED`, 54 approved gates**. Checkpoint promotion remains owner-only.
