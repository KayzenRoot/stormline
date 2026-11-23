# NLE-PRPLAN-TWO-02-05 — Collision authoring evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO COLLISION SOLVER`. **Base:** `2516ce8`. **Gate:** [NLE-PRPLAN-TWO-02-05-G6-ACTIVATION](NLE-PRPLAN-TWO-02-05-G6-ACTIVATION.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-02-05](../work-orders/NLE-PRPLAN-TWO-02-05.md). **PR:** #813.

## Scope delivered

- `src/stormline/tilemap/collision_plan.hpp`: descriptors/plan and `plan_tile_collision`.
- `tests/core/two02_collision_tests.cpp`: COL-01.
- Additive CMake test and TSan target.
- No collision solver, contact, broadphase, physics activation, navigation, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Tile ID/revision must be nonzero; shape count is bounded.
- Shape IDs/revisions are nonzero and unique; kinds and finite coordinates are validated.
- Rect extents must be positive; segments must have a nonzero extent; one-way requires solid.
- PHY remains authoritative; no contact or activation receipt is produced.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two02_collision_tests.cpp -o /tmp/two02_col
/tmp/two02_col col01
g++ ... -fsanitize=address,undefined ... -o /tmp/two02_col_san
/tmp/two02_col_san col01
g++ ... -fsanitize=thread ... -o /tmp/two02_col_tsan
setarch "$(uname -m)" -R /tmp/two02_col_tsan col01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no collision behavior is claimed.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No solver, contacts, physics, navigation, GPU, render, hardware, performance, ABI or release.
- `TWO-02-06`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `TWO-02-05` as `COMPLETED`, manifest `TWO02_05_COMPLETED_REST_BLOCKED`: **542 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 164 `COMPLETED`, 42 approved gates**.
