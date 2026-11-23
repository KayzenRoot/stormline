# NLE-PRPLAN-GFX-07-09 — Integrated post-processing qualification evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / LOGICAL QUALIFICATION ONLY`. **Base:** `711e085`. **Gate:** [NLE-PRPLAN-GFX-07-09-G6-ACTIVATION](NLE-PRPLAN-GFX-07-09-G6-ACTIVATION.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-07-09](../work-orders/NLE-PRPLAN-GFX-07-09.md). **PR:** #770.

## Scope delivered

- `tests/core/gfx07_post_qualification_tests.cpp`: QLF-G701..G704.
- Additive CMake target/tests and TSan target.
- No GPU, swapchain, HDR signal, tone mapper, LUT/OCIO, TAA, upscaler, renderer, dependency, ABI, release, hardware or performance claim.

## Qualification results

- **QLF-G701:** one camera traverses camera/exposure/color/output/reconstruction/blur/upscale; HDR selection, vendor reconstruction, motion blur and 1/2 scale fraction are asserted together.
- **QLF-G702:** two full pipelines plus 100 repeats produce identical plans, flags and fractions.
- **QLF-G703:** duplicate camera, invalid exposure, unsupported color transfer, blur without velocity and native upscale mismatch each return the typed error; a valid operation succeeds immediately after each failure.
- **QLF-G704:** 8-camera capacity is filled; 10,000 additional admissions stay `CapacityFull` with count unchanged; 10,000 valid upscale plans keep the reduced 5/8 fraction stable.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx07_post_qualification_tests.cpp -o /tmp/gfx07_qlf
/tmp/gfx07_qlf qlfg701
/tmp/gfx07_qlf qlfg702
/tmp/gfx07_qlf qlfg703
/tmp/gfx07_qlf qlfg704
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/gfx07_post_qualification_tests.cpp -o /tmp/gfx07_qlf_san
/tmp/gfx07_qlf_san qlfg701..qlfg704
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/gfx07_post_qualification_tests.cpp -o /tmp/gfx07_qlf_tsan
setarch "$(uname -m)" -R /tmp/gfx07_qlf_tsan qlfg701..qlfg704
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Test-only translation unit; header-only production metadata unchanged.
- No allocation, exception, file, network, GPU or global production state.
- Logical qualification only; no image, signal, kernel, SDK or hardware result is claimed.

## Rollback

Revert normally; remove the qualification test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No native GPU, swapchain, HDR signal, tone mapper, LUT/OCIO, TAA, upscaler, rendering, hardware, performance, ABI or release.
- `GFX-07-10` remains blocked until its gate.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-07-09` as `COMPLETED`, manifest `GFX07_09_COMPLETED_REST_BLOCKED`: **568 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 144 `COMPLETED`, 36 approved gates**.
