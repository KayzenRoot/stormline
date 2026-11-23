# NLE-PRPLAN-GFX-07-03 — Camera and exposure evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO GPU, SWAPCHAIN OR MATRIX`. **Base:** `ba1f978`. **Gate:** [NLE-PRPLAN-GFX-07-03-G6-ACTIVATION](NLE-PRPLAN-GFX-07-03-G6-ACTIVATION.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-07-03](../work-orders/NLE-PRPLAN-GFX-07-03.md).

## Scope delivered

- `src/stormline/graphics/post/post_types.hpp`: errors, projection/color/reconstruction enums, diagnostic, camera/view and set structures.
- `src/stormline/graphics/post/camera_exposure.hpp`: `post_error_name`, `add_camera`, `validate_cameras`, `plan_exposure`.
- `tests/core/gfx07_camera_tests.cpp`: CAM-01/EXP-01.
- Additive CMake interface/test and TSan target.
- No GPU, swapchain, projection matrix, histogram, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Camera IDs/revisions and scene generation are nonzero; projection is declared; aspect/near/far/dimensions/jitter are finite and valid.
- Perspective FOV is in `(0,pi)`; orthographic height is positive; jitter is world-only.
- Exposure EV/min/max, adaptation times and percentiles are finite and ordered; manual EV stays inside the range.
- No matrix is inverted, no image is metered and no exposure is applied.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx07_camera_tests.cpp -o /tmp/gfx07_cam
/tmp/gfx07_cam cam01
```

Exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- The orthographic-height test initially left the projection as perspective, so the field was ignored; the fixture was corrected to set orthographic projection before the strict run.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Camera/exposure metadata only; no projection matrix, histogram or visual result is claimed.

## Rollback

Revert normally; remove the post headers/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No tone/color, HDR, reconstruction, motion blur or upscale yet.
- No GPU, swapchain, rendering, display, hardware, performance, ABI or release.
- `GFX-07-04`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-07-03` as `COMPLETED`, manifest `GFX07_03_COMPLETED_REST_BLOCKED`: **574 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 138 `COMPLETED`, 36 approved gates**.
