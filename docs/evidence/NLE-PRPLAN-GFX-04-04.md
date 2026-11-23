# NLE-PRPLAN-GFX-04-04 — conservative culling evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU OR OCCLUSION QUERY`. **Base:** `d126d09`. **Gate:** [NLE-PRPLAN-GFX-04-04-G6-ACTIVATION](NLE-PRPLAN-GFX-04-04-G6-ACTIVATION.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-04-04](../work-orders/NLE-PRPLAN-GFX-04-04.md).

## Scope delivered

- `src/stormline/graphics/geometry/geometry_cull.hpp`: `cull_instances`.
- `tests/core/gfx04_cull_tests.cpp`: CUL-01.
- Additive CMake/workflow entries.

No LOD/HLOD, stream, vegetation, budget, qualification, native GPU/occlusion, mesh library, submission, dependency, ABI or release.

## Implementation notes

- Unknown bounds remain visible.
- Distance culling uses `|camera-center| > max_distance + radius`.
- Plane culling requires `dot(normal,center)+distance < -radius`; normals must be unit length within tolerance.
- Scene generation, camera, distance and plane validity are checked before culling.
- Visible IDs preserve declaration order; culled count is derived.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx04_cull_tests.cpp -o /tmp/gfx04_cul
/tmp/gfx04_cul cul01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- No implementation defect after the first compile.

## Security and architecture

- Header-only internal C++20; no GPU, occlusion query, mesh library, file or network.
- Conservative culling favors overdraw over uncertain exclusion.

## Rollback

Revert normally; remove the cull header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No GPU occlusion, temporal history, Hi-Z or indirect draw.
- No LOD/HLOD/stream/vegetation/budget yet.
- `GFX-04-05`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-04-04` as `COMPLETED`, manifest `GFX04_04_COMPLETED_REST_BLOCKED`: **603 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 115 `COMPLETED`, 30 approved gates**.
