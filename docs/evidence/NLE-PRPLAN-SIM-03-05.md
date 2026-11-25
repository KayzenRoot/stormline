# NLE-PRPLAN-SIM-03-05 — Input response metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO INPUT DEVICES`. **Base:** `baadb9a8`. **Gate:** [NLE-PRPLAN-SIM-03-05-G6-ACTIVATION](NLE-PRPLAN-SIM-03-05-G6-ACTIVATION.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-03-05](../work-orders/NLE-PRPLAN-SIM-03-05.md). **PR:** pendente.

## Scope delivered

- `src/stormline/character/input_plan.hpp`: `InputActionDesc`, `InputSetDesc`, `InputPlan`, `plan_input`.
- `tests/core/sim03_input_tests.cpp`: INPUT-01.
- Additive CMake target/test and TSan target.
- No device polling, event dispatch, motor, camera update, ECS mutation, GPU, character runtime, ABI or release claim.

## Implementation notes

- Owner ID/revision nonzero; count `0..64`; action IDs nonzero and unique; revisions nonzero; axis index `0..7`.
- Dead zone `0..1`; scale finite and nonzero; buffer ticks `0..240`.
- Plan counts axis actions, buffered actions and enabled actions; reset and typed diagnostic on failure.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict `-Werror`, ASan/UBSan and TSan builds with `input01` — PASS.

## Errors and corrections

- None; implementation follows the frozen contract exactly.

## Security and architecture

- Header-only internal C++20; no allocation, exception, I/O, GPU, clock, thread, random source or global state. No device polling or event dispatch.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No device polling, event dispatch, motor, camera update, ECS mutation, GPU, character runtime, performance, ABI or release.
- `SIM-03-06`..`-08` remain blocked until their gates.

## Proposed checkpoint delta

After merge, record `SIM-03-05` as `COMPLETED`, manifest `SIM03_05_COMPLETED_REST_BLOCKED`: **450 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 236 `COMPLETED`, 62 approved gates**. Checkpoint promotion remains owner-only.
