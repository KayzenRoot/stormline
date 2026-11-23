# NLE-PRPLAN-GFX-04-07 — vegetation classification evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO VEGETATION PHYSICS OR GPU`. **Base:** `cbafa32`. **Gate:** [NLE-PRPLAN-GFX-04-07-G6-ACTIVATION](NLE-PRPLAN-GFX-04-07-G6-ACTIVATION.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-04-07](../work-orders/NLE-PRPLAN-GFX-04-07.md).

## Scope delivered

- `src/stormline/graphics/geometry/geometry_vegetation.hpp`: `classify_vegetation`.
- `tests/core/gfx04_vegetation_tests.cpp`: VEG-01.
- Additive CMake/workflow entries.

No vegetation placement/physics, geometry budget, qualification, native GPU/mesh library, submission, dependency, ABI or release.

## Implementation notes

- Only Grass/Bush/Tree categories are accepted.
- Unknown bounds remain Mesh (conservative).
- Billboard is selected only when `billboard_allowed` and the camera distance exceeds the threshold.
- Double-sided and alpha-cutout flags are preserved.
- Invalid category, bounds, camera or threshold fails closed.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx04_vegetation_tests.cpp -o /tmp/gfx04_veg
/tmp/gfx04_veg veg01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- The test initially divided by zero to construct infinity; replaced with `std::numeric_limits<f32>::infinity()`.

## Security and architecture

- Header-only internal C++20; no GPU, vegetation simulation, file or network.
- Classification is metadata; no geometry is drawn or removed.

## Rollback

Revert normally; remove the vegetation header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No vegetation placement, wind, physics, billboard generation or GPU rendering.
- No geometry budget yet.
- `GFX-04-08`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-04-07` as `COMPLETED`, manifest `GFX04_07_COMPLETED_REST_BLOCKED`: **600 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 118 `COMPLETED`, 30 approved gates**.
