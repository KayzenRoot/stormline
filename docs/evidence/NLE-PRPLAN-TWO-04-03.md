# NLE-PRPLAN-TWO-04-03 — Camera intent evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO MATRIX OR RENDER`. **Base:** `32f2650`. **Gate:** [NLE-PRPLAN-TWO-04-03-G6-ACTIVATION](NLE-PRPLAN-TWO-04-03-G6-ACTIVATION.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-04-03](../work-orders/NLE-PRPLAN-TWO-04-03.md). **PR:** #839.

## Scope delivered

- `src/stormline/hybrid/hybrid_types.hpp`: aliases, capacities, errors, enums, diagnostic and detail validators.
- `src/stormline/hybrid/camera_plan.hpp`: `CameraDesc`, `CameraPlan` and `plan_camera`.
- `tests/core/two04_camera_tests.cpp`: CAM-01.
- Additive CMake interface target/test and TSan target.
- No camera matrix, trigonometry, frustum, renderer, GPU, depth attachment, layer/sort/effect, audio, export, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Camera ID/revision nonzero; projection allowlisted.
- Near/far finite, near positive and far greater than near.
- Orthographic requires finite positive half-height and aspect; perspective requires finite `0 < fov < 180` and positive aspect.
- `primary_extent` returns half-height or FOV; no trigonometric or matrix evaluation.
- Invalid input zeroes the plan and sets a typed diagnostic.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two04_camera_tests.cpp -o /tmp/two04cam_strict
/tmp/two04cam_strict cam01
g++ ... -fsanitize=address,undefined -fno-omit-frame-pointer ... -o /tmp/two04cam_asan
/tmp/two04cam_asan cam01
g++ ... -fsanitize=thread ... -o /tmp/two04cam_tsan
setarch "$(uname -m)" -R /tmp/two04cam_tsan cam01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, thread or global state.
- Logical camera intent only; GFX-07 retains future matrix/view/output authority.

## Rollback

Revert normally; remove the headers/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No matrix, trigonometry, frustum, rendering, GPU, layers, sorting, effects, audio, export, ABI, release, hardware or performance.
- `TWO-04-04`..`-08` remain blocked until their gates.
- TWO-01/GFX-04 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `TWO-04-03` as `COMPLETED`, manifest `TWO04_03_COMPLETED_REST_BLOCKED`: **526 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 176 `COMPLETED`, 46 approved gates**. Checkpoint promotion remains owner-only.
