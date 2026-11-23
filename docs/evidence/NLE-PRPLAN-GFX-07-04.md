# NLE-PRPLAN-GFX-07-04 — Tone/color plan evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO TONE MAPPER OR LUT`. **Base:** `1719d8a`. **Gate:** [NLE-PRPLAN-GFX-07-04-G6-ACTIVATION](NLE-PRPLAN-GFX-07-04-G6-ACTIVATION.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-07-04](../work-orders/NLE-PRPLAN-GFX-07-04.md).

## Scope delivered

- `src/stormline/graphics/post/tone_color.hpp`: color plan descriptor/plan and `plan_color`.
- `tests/core/gfx07_color_tests.cpp`: COL-01.
- Additive CMake test and TSan target.
- No tone mapper, LUT/OCIO runtime, shader, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Input/output transfer and tone curve are declared enums; output is sRGB for this slice.
- Exposure stops are finite in `[-16,16]`; white point is finite and positive.
- Any already-applied tone/gamma flag returns `DoubleTransferGuard`.
- Invalid transfers return `ColorSpaceMismatch`; non-sRGB output returns `Unsupported`.
- No pixel is transformed and no LUT is read.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx07_color_tests.cpp -o /tmp/gfx07_color
/tmp/gfx07_color col01
```

Exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Color/tone policy only; no image or color-accuracy result is claimed.

## Rollback

Revert normally; remove the tone/color header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No HDR, reconstruction, motion blur or upscale yet.
- No tone mapper, LUT/OCIO, GPU, rendering, hardware, performance, ABI or release.
- `GFX-07-05`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-07-04` as `COMPLETED`, manifest `GFX07_04_COMPLETED_REST_BLOCKED`: **573 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 139 `COMPLETED`, 36 approved gates**.
