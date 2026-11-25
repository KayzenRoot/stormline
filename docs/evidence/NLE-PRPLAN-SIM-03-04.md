# NLE-PRPLAN-SIM-03-04 — Locomotion metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO MOVEMENT SIMULATION`. **Base:** `11f3afbb`. **Gate:** [NLE-PRPLAN-SIM-03-04-G6-ACTIVATION](NLE-PRPLAN-SIM-03-04-G6-ACTIVATION.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-03-04](../work-orders/NLE-PRPLAN-SIM-03-04.md). **PR:** pendente.

## Scope delivered

- `src/stormline/character/locomotion_plan.hpp`: `LocomotionDesc`, `LocomotionSetDesc`, `LocomotionPlan`, `plan_locomotion`.
- `tests/core/sim03_locomotion_tests.cpp`: LOCO-01.
- Additive CMake target/test and TSan target.
- No movement simulation, motor, sweeper, contacts, solver, input layer, camera update, ECS mutation, GPU, character runtime, ABI or release claim.

## Implementation notes

- Owner ID/revision nonzero; count `0..32`; IDs nonzero and unique; revisions nonzero; controller_id nonzero.
- Finite speeds/acceleration/deceleration/jump/dash; walk/run/air/jump/dash `>= 0`; run `>=` walk; acceleration and deceleration `> 0`; buffer/coyote/dash ticks `0..240`.
- Plan counts nonzero ground/air/jump/dash policies and enabled entries; reset and typed diagnostic on failure.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict `-Werror`, ASan/UBSan and TSan builds with `loco01` — PASS.

## Errors and corrections

- Test helper naming and one stray typo were corrected before verification; strict/sanitizer runs passed.

## Security and architecture

- Header-only internal C++20; no allocation, exception, I/O, GPU, clock, thread, random source or global state. No movement or contact gating.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No movement simulation, motor, sweeper, contacts, solver/backend, input devices, camera update, ECS mutation, GPU, character runtime, performance, ABI or release.
- `SIM-03-05`..`-08` remain blocked until their gates.

## Proposed checkpoint delta

After merge, record `SIM-03-04` as `COMPLETED`, manifest `SIM03_04_COMPLETED_REST_BLOCKED`: **451 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 235 `COMPLETED`, 62 approved gates**. Checkpoint promotion remains owner-only.
