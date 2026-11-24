# NLE-PRPLAN-SIM-01-05 — Query intent metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO QUERY EXECUTION`. **Base:** `6773d56`. **Gate:** [NLE-PRPLAN-SIM-01-05-G6-ACTIVATION](NLE-PRPLAN-SIM-01-05-G6-ACTIVATION.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-01-05](../work-orders/NLE-PRPLAN-SIM-01-05.md). **PR:** pendente.

## Scope delivered

- `src/stormline/physics2d/query_plan.hpp`: query descriptors, plan and `plan_queries`.
- `tests/core/sim01_query_tests.cpp`: QRY-01.
- Additive CMake test target and TSan target.
- No query execution, result set, broadphase, contacts, solver/backend, simulation, ECS mutation, GPU, physics runtime, ABI, release, hardware or performance claim.

## Implementation notes

- World ID/revision must be nonzero; query count is `0..32`.
- Query IDs are nonzero and unique; revisions nonzero; kind is `Ray`, `Overlap` or `ShapeCast`.
- Origins/directions and distance are finite; mask bits are nonzero; `max_results` is `1..1024`.
- Ray/shape-cast require `max_distance > 0`; overlap allows `0`.
- Checked total result limit is `<= 8192`; plan reports kind counts and total limit.
- Invalid input zeroes the plan and sets a typed diagnostic with the world ID and query index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/sim01_query_tests.cpp` — PASS.
- ASan/UBSan build and `qry01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `qry01` — PASS.

## Errors and corrections

- None during implementation; strict compile and sanitizers passed first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread, random source or global state.
- Logical query intent only; no query processor or result set exists.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No query execution/result sets, broadphase, contacts, simulation, solver/backend, ECS mutation, GPU, physics runtime, performance, ABI or release.
- `SIM-01-06`..`-10` remain blocked until their gates.
- WORLD-01/TWO-01 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `SIM-01-05` as `COMPLETED`, manifest `SIM01_05_COMPLETED_REST_BLOCKED`: **470 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 220 `COMPLETED`, 58 approved gates**. Checkpoint promotion remains owner-only.
