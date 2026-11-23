# NLE-PRPLAN-GFX-04-03 — geometry instances and batches evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU OR MESH LIBRARY`. **Base:** `a3a4cb8`. **Gate:** [NLE-PRPLAN-GFX-04-03-G6-ACTIVATION](NLE-PRPLAN-GFX-04-03-G6-ACTIVATION.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-04-03](../work-orders/NLE-PRPLAN-GFX-04-03.md).

## Scope delivered

- `src/stormline/graphics/geometry/geometry_types.hpp`: bounded geometry types and plan structures.
- `src/stormline/graphics/geometry/geometry_instance.hpp`: add/validate instances and deterministic batches.
- `tests/core/gfx04_instance_tests.cpp`: INS-01.
- Additive CMake/workflow entries.

No culling, LOD/HLOD, streaming, vegetation, budget, qualification, native GPU/mesh library, submission, dependency, ABI or release.

## Implementation notes

- Instance IDs/mesh/material are nonzero and unique; scene generation is nonzero.
- Bounds radius must be finite and nonnegative; known bounds require finite center.
- Unknown bounds are accepted and remain visible for later culling.
- Batches group by `(mesh_id, material_id)`, sorted by mesh/material; instance indices preserve declaration order.
- Capacities are 128 instances and 32 batches.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx04_instance_tests.cpp -o /tmp/gfx04_ins
/tmp/gfx04_ins ins01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- The test fixture initially used a nonexistent `EXPECT_EQ` macro and a stray label; corrected before the passing run.

## Security and architecture

- Header-only internal C++20; no GPU, mesh library, decoder, file or network.
- Instance/batch metadata preserves authored IDs; no render or draw occurs.

## Rollback

Revert normally; remove the two headers/test and additive CMake/workflow entries.

## Open risks / not claimed

- No culling, LOD/HLOD, streaming, vegetation or geometry budget yet.
- No native GPU, mesh codec, submission or rendering.
- `GFX-04-04`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-04-03` as `COMPLETED`, manifest `GFX04_03_COMPLETED_REST_BLOCKED`: **604 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 114 `COMPLETED`, 30 approved gates**.
