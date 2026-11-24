# NLE-PRPLAN-WORLD-01-05 — Lifecycle transition evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO STORAGE MUTATION OR DESTRUCTION`. **Base:** `8bf2c32`. **Gate:** [NLE-PRPLAN-WORLD-01-05-G6-ACTIVATION](NLE-PRPLAN-WORLD-01-05-G6-ACTIVATION.md). **Contract:** [world-01-entity-internal-v0](../contracts/world-01-entity-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-01-05](../work-orders/NLE-PRPLAN-WORLD-01-05.md). **PR:** #856.

## Scope delivered

- `src/stormline/world/lifecycle_plan.hpp`: transition/batch descriptors, plan and `plan_lifecycle`.
- `tests/core/world01_lifecycle_tests.cpp`: LIF-01.
- Additive CMake test and TSan target.
- No storage mutation, entity destruction, allocator, serializer, query, reflection, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- World epoch nonzero; slot count `1..64`; transition count `1..64`.
- Slots must be below slot count; generations nonzero; states allowlisted.
- Allowed transitions: `Alive -> DestroyRequested`, `DestroyRequested -> Tombstoned`, `Tombstoned -> Retired`, plus same-state idempotence.
- All other transitions fail with `LifecycleInvalid`; duplicate slots fail with `DuplicateId`.
- Outputs total transitions, retirements and idempotent receipts; invalid input resets and sets a typed diagnostic.
- No entity is mutated or destroyed; DATA-04 owns durable tombstones and undo.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict GCC flags, ASan/UBSan and TSan all passed for LIF-01. The first capacity fixture used slot 4..63 with slot_count 4 and failed as expected; slot_count was corrected to 64 before evidence.

## Errors and corrections

- Corrected the capacity fixture to use `slot_count = 64`; strict compile and sanitizers then passed.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, thread or global state.
- Logical transition intent only; no runtime destruction occurs.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No storage mutation, destruction, allocator, serializer, queries, reflection, hierarchy, spatial, physics, networking, editor, GPU, performance, ABI or release.
- `WORLD-01-06`..`-09` remain blocked until their gates.
- CORE-05/DATA-04 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-01-05` as `COMPLETED`, manifest `WORLD01_05_COMPLETED_REST_BLOCKED`: **516 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 184 `COMPLETED`, 48 approved gates**. Checkpoint promotion remains owner-only.
