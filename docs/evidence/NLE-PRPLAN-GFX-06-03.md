# NLE-PRPLAN-GFX-06-03 — Logical lights evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO GPU, SHADOW MAP OR RENDER`. **Base:** `84f0af1`. **Gate:** [NLE-PRPLAN-GFX-06-03-G6-ACTIVATION](NLE-PRPLAN-GFX-06-03-G6-ACTIVATION.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-06-03](../work-orders/NLE-PRPLAN-GFX-06-03.md).

## Scope delivered

- `src/stormline/graphics/lighting/lighting_types.hpp`: enums, capacities, diagnostic and light structures.
- `src/stormline/graphics/lighting/light.hpp`: `lighting_error_name`, `add_light`, `validate_lights`.
- `tests/core/gfx06_light_tests.cpp`: LGT-01.
- Additive CMake interface/test and TSan target.
- No GPU, shadow map, ray tracing, shader, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Light IDs/revisions are nonzero and unique; kind/unit combinations and shadow policy are validated.
- Color/intensity are finite/nonnegative; intensity may be zero. Position/direction are finite; direction must be nonzero.
- Point/Spot/Stylized2D require positive range; Spot requires ordered angles within `[0,pi/2]`; AreaRect requires positive dimensions.
- Cascaded shadows are accepted only for Directional and Local only for Point/Spot.
- `add_light` is atomic; validation reports the first offending index.
- No light, shadow map, shader or GPU resource is created.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx06_light_tests.cpp -o /tmp/gfx06_light
/tmp/gfx06_light lgt01
```

Exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Lighting metadata only; no radiance, shadow or visual result is claimed.

## Rollback

Revert normally; remove the lighting headers/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No shadows, GI, probes, reflections or volumetrics yet.
- No GPU, shadow map, ray tracing, rendering, hardware, performance, ABI or release.
- `GFX-06-04`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-06-03` as `COMPLETED`, manifest `GFX06_03_COMPLETED_REST_BLOCKED`: **584 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 130 `COMPLETED`, 34 approved gates**.
