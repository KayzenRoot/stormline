# NLE-PRPLAN-WORLD-03-04 — Interest query metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO SPATIAL INDEX OR QUERY RESULT`. **Base:** `8be1767`. **Gate:** [NLE-PRPLAN-WORLD-03-04-G6-ACTIVATION](NLE-PRPLAN-WORLD-03-04-G6-ACTIVATION.md). **Contract:** [world-03-spatial-internal-v0](../contracts/world-03-spatial-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-03-04](../work-orders/NLE-PRPLAN-WORLD-03-04.md). **PR:** #884.

## Scope delivered

- `src/stormline/spatial/interest_plan.hpp`: bounds, source/set descriptors, plan and `plan_interest`.
- `tests/core/world03_interest_tests.cpp`: INT-01.
- Additive CMake test target and TSan target.
- No spatial index, query result, cell storage, streaming task, I/O, decode, cache, origin rebase, physics, networking, renderer, editor, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- World ID and revision must be nonzero; source count is `0..16`.
- Source IDs and revisions are nonzero and unique; roles are allowlisted.
- Bounds must be finite with `min_x < max_x` and `min_z < max_z`; priority remains metadata only.
- Union bounds aggregate the minimum/maximum extents; an empty set reports an empty zero union.
- `required_complete` counts as complete, otherwise incomplete; the two counts sum to the source count.
- Invalid input zeroes the plan and sets a typed diagnostic with the source ID (or world ID for set-level faults) and source index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/world03_interest_tests.cpp` — PASS.
- ASan/UBSan build and `int01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `int01` — PASS.

## Errors and corrections

- None during implementation; the declared TSan target and CMake additions compiled first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread or global state.
- Logical interest metadata only; no spatial index, query result, cell storage or streaming runtime exists.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No spatial index/query results, async streaming, I/O/decode/cache, origin rebase, physics/networking, renderer, editor, GPU, performance, ABI or release.
- `WORLD-03-05`..`-08` remain blocked until their gates.
- WORLD-02/DATA-05 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-03-04` as `COMPLETED`, manifest `WORLD03_04_COMPLETED_REST_BLOCKED`: **499 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 197 `COMPLETED`, 52 approved gates**. Checkpoint promotion remains owner-only.
