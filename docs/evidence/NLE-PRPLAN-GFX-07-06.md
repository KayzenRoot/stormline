# NLE-PRPLAN-GFX-07-06 — Reconstruction strategy evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO TAA OR VENDOR SDK`. **Base:** `198e4c2`. **Gate:** [NLE-PRPLAN-GFX-07-06-G6-ACTIVATION](NLE-PRPLAN-GFX-07-06-G6-ACTIVATION.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-07-06](../work-orders/NLE-PRPLAN-GFX-07-06.md).

## Scope delivered

- `src/stormline/graphics/post/reconstruction_plan.hpp`: request/plan and `plan_reconstruction`.
- `tests/core/gfx07_reconstruction_tests.cpp`: RCN-01.
- Additive CMake test and TSan target.
- No TAA/FXAA/SMAA, FSR/DLSS/XeSS, history texture, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Native/Spatial are always safe.
- TAA requires depth, velocity and history; missing inputs degrade to Spatial.
- Vendor upscale additionally requires reactive mask and vendor availability; missing inputs degrade to Spatial.
- Unknown strategy fails closed; no accumulator or SDK is created.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx07_reconstruction_tests.cpp -o /tmp/gfx07_rcn
/tmp/gfx07_rcn rcn01
```

Exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Strategy metadata only; no temporal image, AA or visual result is claimed.

## Rollback

Revert normally; remove the reconstruction header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No motion blur or upscale yet.
- No TAA, vendor SDK, GPU, rendering, hardware, performance, ABI or release.
- `GFX-07-07`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-07-06` as `COMPLETED`, manifest `GFX07_06_COMPLETED_REST_BLOCKED`: **571 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 141 `COMPLETED`, 36 approved gates**.
