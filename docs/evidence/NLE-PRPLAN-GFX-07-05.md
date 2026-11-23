# NLE-PRPLAN-GFX-07-05 — HDR output negotiation evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO SWAPCHAIN OR HDR SIGNAL`. **Base:** `d507b50`. **Gate:** [NLE-PRPLAN-GFX-07-05-G6-ACTIVATION](NLE-PRPLAN-GFX-07-05-G6-ACTIVATION.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-07-05](../work-orders/NLE-PRPLAN-GFX-07-05.md).

## Scope delivered

- `src/stormline/graphics/post/output_plan.hpp`: capability/request/plan and `plan_output`.
- `tests/core/gfx07_output_tests.cpp`: HDR-01.
- Additive CMake test and TSan target.
- No swapchain, HDR monitor, PQ/HLG signal, OS negotiation, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- HDR10 PQ is selected only when display, swapchain, OS and PQ capability flags are all true and HDR is preferred.
- Otherwise SDR sRGB is selected; `degraded=true` only when HDR was preferred but unavailable.
- An internal float format never implies HDR; no display or signal is created.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx07_output_tests.cpp -o /tmp/gfx07_out
/tmp/gfx07_out hdr01
```

Exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Output policy only; no HDR signal, image or visual result is claimed.

## Rollback

Revert normally; remove the output header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No reconstruction, motion blur or upscale yet.
- No swapchain, HDR output, GPU, rendering, hardware, performance, ABI or release.
- `GFX-07-06`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-07-05` as `COMPLETED`, manifest `GFX07_05_COMPLETED_REST_BLOCKED`: **572 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 140 `COMPLETED`, 36 approved gates**.
