# NLE-PRPLAN-SIM-03-06 — Decoupled camera metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO CAMERA UPDATE`. **Base:** `c0c54f3e`. **Gate:** [NLE-PRPLAN-SIM-03-06-G6-ACTIVATION](NLE-PRPLAN-SIM-03-06-G6-ACTIVATION.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-03-06](../work-orders/NLE-PRPLAN-SIM-03-06.md). **PR:** #969.

## Scope delivered

- `src/stormline/character/camera_plan.hpp`: `CameraDesc`, `CameraSetDesc`, `CameraPlan`, `plan_cameras`.
- `tests/core/sim03_camera_tests.cpp`: CAM-01.
- Additive CMake target/test and TSan target.
- No camera transform/update, device polling, motor, ECS mutation, GPU, character runtime, ABI or release claim.

## Implementation notes

- Owner ID/revision nonzero; count `0..16`; camera IDs nonzero and unique; revisions nonzero; target controller nonzero.
- Finite distance/height/yaw/pitch/damping; distance `>= 0`; pitch `-89..89`; damping `0..1`; animation independence must be true (fail closed).
- Plan counts follow-enabled and independent cameras; reset and typed diagnostic on failure.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict `-Werror`, ASan/UBSan and TSan builds with `cam01` — PASS.

## Errors and corrections

- None; implementation follows the frozen contract exactly.

## Security and architecture

- Header-only internal C++20; no allocation, exception, I/O, GPU, clock, thread, random source or global state. No transform or camera update.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No camera transform/update, device polling, motor, ECS mutation, GPU, character runtime, performance, ABI or release.
- `SIM-03-07`..`-08` remain blocked until their gates.

## Proposed checkpoint delta

After merge, record `SIM-03-06` as `COMPLETED`, manifest `SIM03_06_COMPLETED_REST_BLOCKED`: **449 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 237 `COMPLETED`, 62 approved gates**. Checkpoint promotion remains owner-only.
