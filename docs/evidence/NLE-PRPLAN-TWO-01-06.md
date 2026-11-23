# NLE-PRPLAN-TWO-01-06 — Camera metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PROJECTION MATRIX`. **Base:** `f8a54dd`. **Gate:** [NLE-PRPLAN-TWO-01-06-G6-ACTIVATION](NLE-PRPLAN-TWO-01-06-G6-ACTIVATION.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-01-06](../work-orders/NLE-PRPLAN-TWO-01-06.md). **PR:** #798.

## Scope delivered

- `src/stormline/graphics/canvas2d/camera_plan.hpp`: descriptor/plan and `plan_camera`.
- `tests/core/two01_camera_tests.cpp`: CAM-01.
- Additive CMake test and TSan target.
- No projection matrix, GPU view, swapchain, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Viewport dimensions must be positive; position must be finite.
- Zoom and DPI scale must be finite positive; effective zoom is the checked product.
- Letterbox policy is preserved; no matrix or GPU view is produced.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two01_camera_tests.cpp -o /tmp/two01_camera
/tmp/two01_camera cam01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/two01_camera_tests.cpp -o /tmp/two01_camera_san
/tmp/two01_camera_san cam01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/two01_camera_tests.cpp -o /tmp/two01_camera_tsan
setarch "$(uname -m)" -R /tmp/two01_camera_tsan cam01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no camera or visual result is claimed.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No matrix, GPU, swapchain, render, hardware, performance, ABI or release.
- `TWO-01-07`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `TWO-01-06` as `COMPLETED`, manifest `TWO01_06_COMPLETED_REST_BLOCKED`: **551 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 157 `COMPLETED`, 40 approved gates**.
