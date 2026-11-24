# NLE-PRPLAN-SIM-02-06 — Query intent metadata 3D evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO QUERY EXECUTION`. **Base:** `c9b89191`. **Gate:** [NLE-PRPLAN-SIM-02-06-G6-ACTIVATION](NLE-PRPLAN-SIM-02-06-G6-ACTIVATION.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-02-06](../work-orders/NLE-PRPLAN-SIM-02-06.md). **PR:** pendente.

## Scope delivered

- `src/stormline/physics3d/query_plan.hpp`: `QueryDesc`, `QuerySetDesc`, `QueryPlan`, `plan_queries`.
- `tests/core/sim02_query_tests.cpp`: QUERY3-01.
- Additive CMake target/test and TSan target.
- No query execution, result set, broadphase, contacts, solver, simulation, ECS mutation, GPU, physics runtime, ABI or release claim.

## Implementation notes

- IDs/revision nonzero; kind allowlist; layer bits nonzero; finite origin/direction/max_distance; max_results `1..1024`; total limit `<= 8192` with overflow-safe addition.
- Ray/Sweep/ShapeCast: nonzero direction and positive max_distance. Overlap: max_distance `>= 0`.
- Plan counts kinds and total result limit; reset and typed diagnostic on failure.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict `-Werror`, ASan/UBSan and TSan builds with `query301` — PASS.

## Errors and corrections

- None; implementation follows the frozen contract exactly.

## Security and architecture

- Header-only internal C++20; no allocation, exception, I/O, GPU, clock, thread, random source or global state. No hit result or collision pipeline.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No query execution, broadphase, contacts, solver/backend, simulation, ECS mutation, GPU, physics runtime, performance, ABI or release.
- `SIM-02-07`..`-10` remain blocked until their gates.

## Proposed checkpoint delta

After merge, record `SIM-02-06` as `COMPLETED`, manifest `SIM02_06_COMPLETED_REST_BLOCKED`: **459 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 229 `COMPLETED`, 60 approved gates**. Checkpoint promotion remains owner-only.
