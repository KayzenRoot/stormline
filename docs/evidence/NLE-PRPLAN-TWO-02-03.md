# NLE-PRPLAN-TWO-02-03 — Signed grid/chunk evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO MAP I/O`. **Base:** `ae1d409`. **Gate:** [NLE-PRPLAN-TWO-02-03-G6-ACTIVATION](NLE-PRPLAN-TWO-02-03-G6-ACTIVATION.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-02-03](../work-orders/NLE-PRPLAN-TWO-02-03.md). **PR:** #809.

## Scope delivered

- `src/stormline/tilemap/tilemap_types.hpp`: capacities, errors, modes, diagnostic.
- `src/stormline/tilemap/grid_plan.hpp`: grid descriptor/plan and `plan_grid_cell`.
- `tests/core/two02_grid_tests.cpp`: GRD-01.
- Additive CMake target/test and TSan target.
- No renderer, GPU coordinate, map file, streaming, physics, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Grid/tile/chunk dimensions must be positive; bounds must be ordered and the cell inside them.
- Negative cells use mathematical floor division without truncating multiplication; local coordinates stay in `[0,chunk_dimension)`.
- No GPU coordinate or chunk file is created.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two02_grid_tests.cpp -o /tmp/two02_grid
/tmp/two02_grid grd01
g++ ... -fsanitize=address,undefined ... -o /tmp/two02_grid_san
/tmp/two02_grid_san grd01
g++ ... -fsanitize=thread ... -o /tmp/two02_grid_tsan
setarch "$(uname -m)" -R /tmp/two02_grid_tsan grd01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no map or visual result is claimed.

## Rollback

Revert normally; remove the two headers/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No renderer/GPU, map I/O, streaming, physics, hardware, performance, ABI or release.
- `TWO-02-04`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `TWO-02-03` as `COMPLETED`, manifest `TWO02_03_COMPLETED_REST_BLOCKED`: **544 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 162 `COMPLETED`, 42 approved gates**.
