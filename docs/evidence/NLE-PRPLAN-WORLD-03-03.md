# NLE-PRPLAN-WORLD-03-03 — Spatial cell metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO SPATIAL INDEX OR STORAGE`. **Base:** `9c41aef`. **Gate:** [NLE-PRPLAN-WORLD-03-03-G6-ACTIVATION](NLE-PRPLAN-WORLD-03-03-G6-ACTIVATION.md). **Contract:** [world-03-spatial-internal-v0](../contracts/world-03-spatial-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-03-03](../work-orders/NLE-PRPLAN-WORLD-03-03.md). **PR:** pendente.

## Scope delivered

- `src/stormline/spatial/spatial_types.hpp`: aliases, capacities, errors, roles, priorities and diagnostic.
- `src/stormline/spatial/cell_plan.hpp`: cell descriptors, cell-set plan and `plan_cells`, plus `cell_floor_div`.
- `tests/core/world03_cell_tests.cpp`: CEL-01.
- Additive CMake interface target/test and TSan target.
- No spatial index, cell storage, streaming task, I/O, decode, cache, origin rebase, physics, networking, renderer, editor, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- World ID and revision must be nonzero; cell count is `1..64`.
- Cell keys and revisions are nonzero; keys and `(x, z)` pairs are unique per set.
- Negative coordinates are valid and bounds are reported from signed `i64` values.
- `cell_floor_div` requires a positive cell size and uses mathematical floor division; `INT64_MIN / -1` is rejected.
- Invalid input zeroes the plan and sets a typed diagnostic with the world ID as source and the cell slot as index.
- Diagnostics use `CellInvalid` for zero count/keys/revisions, `CapacityFull` above 64 cells and `DuplicateId` for repeated keys or coordinates.
- The types header additionally holds internal `detail` helpers for finite floats, role/priority allowlists and checked `u64` accumulation; they are not public API and are not used by CEL-01 yet.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/world03_cell_tests.cpp` — PASS.
- ASan/UBSan build and `cel01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `cel01` — PASS.

## Errors and corrections

- Reordered the `cell_floor_div` guards so the `INT64_MIN / -1` overflow rejection precedes the non-positive-size rejection; strict compile and sanitizers then passed.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread or global state.
- Logical cell metadata intent only; no spatial index, cell storage, query result or streaming runtime exists.

## Rollback

Revert normally; remove the headers/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No spatial index/storage, async streaming, I/O/decode/cache, origin rebase, spatial query results, physics/networking, renderer, editor, GPU, performance, ABI or release.
- `WORLD-03-04`..`-08` remain blocked until their gates.
- WORLD-02/DATA-05 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-03-03` as `COMPLETED`, manifest `WORLD03_03_COMPLETED_REST_BLOCKED`: **500 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 196 `COMPLETED`, 52 approved gates**. Checkpoint promotion remains owner-only.
