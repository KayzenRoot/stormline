# NLE-PRPLAN-WORLD-04-03 — Terrain patch metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO HEIGHTFIELD STORAGE OR TERRAIN RENDER`. **Base:** `5de3bd0`. **Gate:** [NLE-PRPLAN-WORLD-04-03-G6-ACTIVATION](NLE-PRPLAN-WORLD-04-03-G6-ACTIVATION.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-04-03](../work-orders/NLE-PRPLAN-WORLD-04-03.md). **PR:** pendente.

## Scope delivered

- `src/stormline/terrain/terrain_types.hpp`: aliases, capacities, errors, topology/class/tier enums and diagnostic.
- `src/stormline/terrain/terrain_patch_plan.hpp`: patch descriptors, plan and `plan_terrain_patches`.
- `tests/core/world04_terrain_tests.cpp`: TER-01.
- Additive CMake interface target/test and TSan target.
- No heightfield/mesh storage, mesh generation, terrain renderer, streamer, GPU LOD, texture residency, physics, networking, editor, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Asset ID and revision must be nonzero; patch count is `1..64`.
- Patch keys and revisions are nonzero; keys and signed `(tile_x, tile_z)` pairs are unique.
- LOD is `<= 8`; topology is `Heightfield` or `MeshSurface`.
- Neighbors are nonzero, existing, unique and never self; neighbor count is `<= 8`.
- Negative tile coordinates are valid and bounds are reported from signed `i64` values.
- Invalid input zeroes the plan and sets a typed diagnostic with the asset ID and patch index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/world04_terrain_tests.cpp` — PASS.
- ASan/UBSan build and `ter01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `ter01` — PASS.

## Errors and corrections

- None during implementation; the declared TSan target and CMake additions compiled first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread or global state.
- Logical patch metadata only; no heightfield, mesh, renderer or streamer exists.

## Rollback

Revert normally; remove the headers/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No heightfield/mesh storage, mesh generation, terrain rendering, GPU LOD, texture residency, physics/networking, renderer, editor, GPU, performance, ABI or release.
- `WORLD-04-04`..`-10` remain blocked until their gates.
- WORLD-03/GFX-04 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-04-03` as `COMPLETED`, manifest `WORLD04_03_COMPLETED_REST_BLOCKED`: **492 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 202 `COMPLETED`, 54 approved gates**. Checkpoint promotion remains owner-only.
