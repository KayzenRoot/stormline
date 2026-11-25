# NLE-PRPLAN-SIM-04-08 — Sync group metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO SYNC RUNTIME`. **Base:** `5c9e8f0d`. **Gate:** [NLE-PRPLAN-SIM-04-08-G6-ACTIVATION](NLE-PRPLAN-SIM-04-08-G6-ACTIVATION.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-04-08](../work-orders/NLE-PRPLAN-SIM-04-08.md). **PR:** #987.

## Scope delivered

- `src/stormline/animation/skeletal/sync_plan.hpp`: `SyncGroupDesc`, `SyncSetDesc`, `SyncPlan`, `plan_sync`.
- `tests/core/sim04_sync_tests.cpp`: SYNC-01.
- Additive CMake target/test and TSan target.
- No runtime synchronization, codec, pose evaluation, graph runtime, root motion, ECS mutation, GPU, animation runtime, ABI or release claim.

## Implementation notes

- Owner ID/revision nonzero; group count `0..32`; IDs nonzero and unique; revisions nonzero; leader nonzero.
- Member count `1..32`; phase finite in `[0,1]`; plan counts phased and enabled groups; reset and typed diagnostic on failure.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict `-Werror`, ASan/UBSan and TSan builds with `sync01` — PASS.

## Errors and corrections

- None; implementation follows the corrected contract exactly.

## Security and architecture

- Header-only internal C++20; no allocation, exception, I/O, GPU, clock, thread, random source or global state. No runtime synchronization.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No runtime synchronization, codec, pose evaluation, graph runtime, root motion, ECS mutation, GPU, animation runtime, performance, ABI or release.
- `SIM-04-09`..`-10` remain blocked until their gates.

## Proposed checkpoint delta

After merge, record `SIM-04-08` as `COMPLETED`, manifest `SIM04_08_COMPLETED_REST_BLOCKED`: **439 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 245 `COMPLETED`, 64 approved gates**. Checkpoint promotion remains owner-only.
