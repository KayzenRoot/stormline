# NLE-PRPLAN-TWO-02-04 — Tile cell evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO TILE DRAW`. **Base:** `cabb61e`. **Gate:** [NLE-PRPLAN-TWO-02-04-G6-ACTIVATION](NLE-PRPLAN-TWO-02-04-G6-ACTIVATION.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-02-04](../work-orders/NLE-PRPLAN-TWO-02-04.md). **PR:** #811.

## Scope delivered

- `src/stormline/tilemap/tile_plan.hpp`: descriptor/plan and `plan_tile_cell`.
- `tests/core/two02_tile_tests.cpp`: TIL-01.
- Additive CMake test and TSan target.
- No tile instance, sprite, buffer, GPU, renderer, importer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Map/layer/revision and orientation/transform are validated.
- Empty cells require zero tile ID/revision and no transform; non-empty require nonzero tile ID/revision.
- Non-orthogonal transforms are unsupported in this slice; no tile is drawn.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two02_tile_tests.cpp -o /tmp/two02_tile
/tmp/two02_tile til01
g++ ... -fsanitize=address,undefined ... -o /tmp/two02_tile_san
/tmp/two02_tile_san til01
g++ ... -fsanitize=thread ... -o /tmp/two02_tile_tsan
setarch "$(uname -m)" -R /tmp/two02_tile_tsan til01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- First test run failed on the reset oracle (`empty` is false after reset); corrected the fixture before commit.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no tile or visual result is claimed.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No tile renderer/sprite draw, GPU, importer, physics, hardware, performance, ABI or release.
- `TWO-02-05`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `TWO-02-04` as `COMPLETED`, manifest `TWO02_04_COMPLETED_REST_BLOCKED`: **543 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 163 `COMPLETED`, 42 approved gates**.
