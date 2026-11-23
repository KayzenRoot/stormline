# NLE-PRPLAN-GFX-07-08 — Render-scale/upscale evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO UPSCALER OR IMAGE`. **Base:** `37c8afe`. **Gate:** [NLE-PRPLAN-GFX-07-08-G6-ACTIVATION](NLE-PRPLAN-GFX-07-08-G6-ACTIVATION.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-07-08](../work-orders/NLE-PRPLAN-GFX-07-08.md). **PR:** #768.

## Scope delivered

- `src/stormline/graphics/post/upscale_plan.hpp`: request/plan and `plan_upscale`.
- `tests/core/gfx07_upscale_tests.cpp`: UPS-01.
- Additive CMake test and TSan target.
- No FSR/DLSS/XeSS, sharpening kernel, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Strategy is validated against the four declared reconstruction strategies; unknown values fail closed with `InvalidArgument`.
- Render/output dimensions must be positive; output must not be smaller than render.
- The scale fraction is reduced by GCD of render and output width; height-only mismatch keeps `1/1`.
- `reconstructed` is true exactly when render dimensions differ from output dimensions.
- `Native` with differing dimensions returns `Unsupported`; other strategies return metadata only.
- No image, kernel, SDK or upscaled pixel is produced.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx07_upscale_tests.cpp -o /tmp/gfx07_ups
/tmp/gfx07_ups ups01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/gfx07_upscale_tests.cpp -o /tmp/gfx07_ups_san
/tmp/gfx07_ups_san ups01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/gfx07_upscale_tests.cpp -o /tmp/gfx07_ups_tsan
setarch "$(uname -m)" -R /tmp/gfx07_ups_tsan ups01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no upscaler, SDK, kernel or visual result is claimed.

## Rollback

Revert normally; remove the upscale header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No upscaler, sharpening, GPU, rendering, hardware, performance, ABI or release.
- `GFX-07-09`/`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-07-08` as `COMPLETED`, manifest `GFX07_08_COMPLETED_REST_BLOCKED`: **569 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 143 `COMPLETED`, 36 approved gates**.
