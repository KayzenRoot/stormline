# NLE-PRPLAN-GFX-07-07 — Motion blur policy evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO BLUR OR VELOCITY SAMPLING`. **Base:** `0547a39`. **Gate:** [NLE-PRPLAN-GFX-07-07-G6-ACTIVATION](NLE-PRPLAN-GFX-07-07-G6-ACTIVATION.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-07-07](../work-orders/NLE-PRPLAN-GFX-07-07.md).

## Scope delivered

- `src/stormline/graphics/post/motion_blur.hpp`: descriptor/plan and `plan_motion_blur`.
- `tests/core/gfx07_motion_blur_tests.cpp`: MBL-01.
- Additive CMake test and TSan target.
- No blur, motion vector, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Disabled or reduced-motion input always yields `enabled=false`.
- Enabling requires positive finite velocity; otherwise `Unsupported`.
- Shutter angle is finite in `[0,360]`; velocity is finite nonnegative.
- No vector is generated, sampled or blurred.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx07_motion_blur_tests.cpp -o /tmp/gfx07_mbl
/tmp/gfx07_mbl mbl01
```

Exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Policy only; no blur, motion vector or visual result is claimed.

## Rollback

Revert normally; remove the motion-blur header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No upscale yet.
- No blur, motion vectors, GPU, rendering, hardware, performance, ABI or release.
- `GFX-07-08`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-07-07` as `COMPLETED`, manifest `GFX07_07_COMPLETED_REST_BLOCKED`: **570 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 142 `COMPLETED`, 36 approved gates**.
