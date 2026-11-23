# NLE-PRPLAN-GFX-06-05 — GI fallback evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO GI BAKE OR GPU`. **Base:** `efe03ce`. **Gate:** [NLE-PRPLAN-GFX-06-05-G6-ACTIVATION](NLE-PRPLAN-GFX-06-05-G6-ACTIVATION.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-06-05](../work-orders/NLE-PRPLAN-GFX-06-05.md).

## Scope delivered

- `src/stormline/graphics/lighting/gi_plan.hpp`: `GiRequest`, `GiPlan`, `plan_gi`.
- `tests/core/gfx06_gi_tests.cpp`: GI-01.
- Additive CMake test and TSan target.
- No GI bake, probe evaluation, ray tracing, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Baked GI falls back to probe, then environment, marking `degraded=true`.
- Each requested mode either succeeds or returns `GiUnavailable`; `Unsupported` and unknown enums fail closed.
- Output is reset on every error; no partial mode is emitted.
- No bake data is read and no probe environment is sampled.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx06_gi_tests.cpp -o /tmp/gfx06_gi
/tmp/gfx06_gi gi01
```

Exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- The first draft included only `lighting_types.hpp`; it was changed to include `light.hpp` so the audited `detail::set_light_error` helper is visible. The strict compile then passed.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Fallback is metadata; no radiance, bake or visual result is claimed.

## Rollback

Revert normally; remove the GI header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No probes, reflections or volumetrics yet.
- No GI bake, probe eval, ray tracing, GPU, rendering, hardware, performance, ABI or release.
- `GFX-06-06`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-06-05` as `COMPLETED`, manifest `GFX06_05_COMPLETED_REST_BLOCKED`: **582 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 132 `COMPLETED`, 34 approved gates**.
