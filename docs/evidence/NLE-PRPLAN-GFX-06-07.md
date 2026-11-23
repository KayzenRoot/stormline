# NLE-PRPLAN-GFX-06-07 — Reflection fallback evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO SSR, RAY QUERY OR GPU`. **Base:** `76d19b9`. **Gate:** [NLE-PRPLAN-GFX-06-07-G6-ACTIVATION](NLE-PRPLAN-GFX-06-07-G6-ACTIVATION.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-06-07](../work-orders/NLE-PRPLAN-GFX-06-07.md).

## Scope delivered

- `src/stormline/graphics/lighting/reflection_plan.hpp`: `ReflectionRequest`, `ReflectionPlan`, `plan_reflections`.
- `tests/core/gfx06_reflection_tests.cpp`: REF-01.
- Additive CMake test and TSan target.
- No SSR march, ray query, probe evaluation, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Roughness band is `<=3`; preferred mode must be a declared enum.
- Screen-space falls back to probe, then environment; probe falls back to environment.
- Missing requested mode without fallback returns `ReflectionOffscreen`.
- `offscreen_fallback` is true only for selected SSR with a fallback; `degraded` records a selected mode different from the preferred one.
- No reflection is marched, ray traced or sampled.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx06_reflection_tests.cpp -o /tmp/gfx06_ref
/tmp/gfx06_ref ref01
```

Exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- The draft switch handled declared modes but not an arbitrary invalid enum; an explicit validity check was added before selecting, returning `InvalidArgument`. The strict compile and test then passed.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Fallback is metadata; no reflection, image or visual result is claimed.

## Rollback

Revert normally; remove the reflection header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No volumetrics yet.
- No SSR, ray tracing, GPU, rendering, hardware, performance, ABI or release.
- `GFX-06-08`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-06-07` as `COMPLETED`, manifest `GFX06_07_COMPLETED_REST_BLOCKED`: **580 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 134 `COMPLETED`, 34 approved gates**.
