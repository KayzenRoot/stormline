# NLE-PRPLAN-GFX-08-07 — Volumetric density stamp evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO VOLUME RENDERING`. **Base:** `8142504`. **Gate:** [NLE-PRPLAN-GFX-08-07-G6-ACTIVATION](NLE-PRPLAN-GFX-08-07-G6-ACTIVATION.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-08-07](../work-orders/NLE-PRPLAN-GFX-08-07.md). **PR:** #783.

## Scope delivered

- `src/stormline/graphics/vfx/density_plan.hpp`: descriptor/plan and `plan_density_stamp`.
- `tests/core/gfx08_density_tests.cpp`: DEN-01.
- Additive CMake test and TSan target.
- No volume, froxel, scattering, ray march, GPU, shader, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Stamp ID/revision must be nonzero; density/extinction/extents/lifetime/max density must be finite.
- Density and extinction are nonnegative; extents, lifetime and max density are positive.
- Density above the declared cap clamps to the cap with `clamped=true`; extinction is preserved.
- GFX-06 remains the owner of scattering, fog grids and any rendered volume.
- No volume is created, sampled or drawn.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx08_density_tests.cpp -o /tmp/gfx08_density
/tmp/gfx08_density den01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/gfx08_density_tests.cpp -o /tmp/gfx08_density_san
/tmp/gfx08_density_san den01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/gfx08_density_tests.cpp -o /tmp/gfx08_density_tsan
setarch "$(uname -m)" -R /tmp/gfx08_density_tsan den01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no volumetric or visual result is claimed.

## Rollback

Revert normally; remove the density header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No volume, froxel, scattering, GPU/compute, rendering, hardware, performance, ABI or release.
- `GFX-08-08`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-08-07` as `COMPLETED`, manifest `GFX08_07_COMPLETED_REST_BLOCKED`: **560 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 150 `COMPLETED`, 38 approved gates**.
