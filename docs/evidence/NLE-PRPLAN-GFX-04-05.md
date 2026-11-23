# NLE-PRPLAN-GFX-04-05 — LOD and HLOD evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU OR MESH LIBRARY`. **Base:** `ba27c71`. **Gate:** [NLE-PRPLAN-GFX-04-05-G6-ACTIVATION](NLE-PRPLAN-GFX-04-05-G6-ACTIVATION.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-04-05](../work-orders/NLE-PRPLAN-GFX-04-05.md).

## Scope delivered

- `src/stormline/graphics/geometry/geometry_lod.hpp`: LOD chain validation/selection and HLOD hierarchy validation/selection.
- `tests/core/gfx04_lod_tests.cpp`: LOD-01.
- Additive CMake/workflow entries.

No streaming, vegetation, budget, qualification, native GPU/mesh library, submission, dependency, ABI or release.

## Implementation notes

- LOD chains require level 0 error 0, positive/nonincreasing triangle counts and nondecreasing finite errors.
- Projected error is `error / max(distance,1) * screen_scale`; the coarsest level within the threshold is selected.
- Nonzero previous levels are retained when they are finer and still within 1.25x threshold (hysteresis); unknown bounds select level 0.
- HLOD validates unique IDs, existing parents and acyclic ancestry.
- HLOD selection considers only the root subtree and chooses the highest error within the limit, falling back to the root.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx04_lod_tests.cpp -o /tmp/gfx04_lod
/tmp/gfx04_lod lod01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- Initial hysteresis kept level 0 permanently because level 0 always meets the threshold. Hysteresis is now limited to nonzero previous levels, allowing initial coarsening while stabilizing later refinement.

## Security and architecture

- Header-only internal C++20; no GPU, mesh library, file or network.
- LOD/HLOD plans are metadata; no mesh simplification or draw is performed.

## Rollback

Revert normally; remove the LOD header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No mesh simplification, crack stitching, proxy generation or GPU LOD selection.
- No streaming/vegetation/budget yet.
- `GFX-04-06`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-04-05` as `COMPLETED`, manifest `GFX04_05_COMPLETED_REST_BLOCKED`: **602 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 116 `COMPLETED`, 30 approved gates**.
