# NLE-PRPLAN-WORLD-01-06 — Query intent evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO STORAGE ITERATION OR RESULTS`. **Base:** `8de5299`. **Gate:** [NLE-PRPLAN-WORLD-01-06-G6-ACTIVATION](NLE-PRPLAN-WORLD-01-06-G6-ACTIVATION.md). **Contract:** [world-01-entity-internal-v0](../contracts/world-01-entity-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-01-06](../work-orders/NLE-PRPLAN-WORLD-01-06.md). **PR:** #858.

## Scope delivered

- `src/stormline/world/query_plan.hpp`: query descriptor, plan and `plan_entity_query`.
- `tests/core/world01_query_tests.cpp`: QRY-01.
- Additive CMake test and TSan target.
- No storage access, iteration, result set, cache, jobs, borrow checker, reflection, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Query ID/revision/world epoch nonzero.
- Required count `1..8`; excluded count `0..8`.
- Type IDs nonzero; each set unique; no type appears in both sets.
- Outputs required/excluded counts; invalid input resets and sets a typed diagnostic.
- No storage is read and no result is produced.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict GCC flags, ASan/UBSan and TSan all passed for QRY-01.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, thread or global state.
- Logical query intent only; no iteration, cache or borrow semantics.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No storage access/iteration, result set, cache, jobs, borrow checker, reflection, hierarchy, spatial, physics, networking, editor, GPU, performance, ABI or release.
- `WORLD-01-07`..`-09` remain blocked until their gates.
- CORE-05/DATA-04 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-01-06` as `COMPLETED`, manifest `WORLD01_06_COMPLETED_REST_BLOCKED`: **515 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 185 `COMPLETED`, 48 approved gates**. Checkpoint promotion remains owner-only.
