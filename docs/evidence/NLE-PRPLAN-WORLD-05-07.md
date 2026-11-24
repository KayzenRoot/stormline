# NLE-PRPLAN-WORLD-05-07 — Geometry recipe metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO MESH GENERATION`. **Base:** `6eb82b2`. **Gate:** [NLE-PRPLAN-WORLD-05-07-G6-ACTIVATION](NLE-PRPLAN-WORLD-05-07-G6-ACTIVATION.md). **Contract:** [world-05-procedural-internal-v0](../contracts/world-05-procedural-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-05-07](../work-orders/NLE-PRPLAN-WORLD-05-07.md). **PR:** #920.

## Scope delivered

- `src/stormline/procedural/geometry_plan.hpp`: recipe/set descriptors, plan and `plan_geometry`.
- `tests/core/world05_geometry_tests.cpp`: GEO-01.
- Additive CMake test target and TSan target.
- No mesh generation, geometry buffer, GPU resource, asset I/O, cook/cache, physics, networking, editor, ABI, release, hardware or performance claim.

## Implementation notes

- Graph ID/revision must be nonzero; recipe count is `0..32`.
- Recipe IDs, revisions and source asset IDs are nonzero; recipe IDs are unique.
- Primitive is `Box`, `Plane`, `Sphere` or `Heightfield`.
- Unit scale is finite and `> 0`; LOD count is `1..8`.
- Plan reports primitive counts and maximum unit scale; no mesh is produced.
- Invalid input zeroes the plan and sets a typed diagnostic with the graph ID and recipe index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/world05_geometry_tests.cpp` — PASS.
- ASan/UBSan build and `geo01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `geo01` — PASS.

## Errors and corrections

- None during implementation; strict compile and sanitizers passed first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread, random source or global state.
- Logical geometry recipe metadata only; GFX-04 remains the mesh pipeline owner.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No mesh generation, geometry buffer, GPU, asset I/O, cook/cache, physics/networking, editor, performance, ABI or release.
- `WORLD-05-08`..`-10` remain blocked until their gates.
- WORLD-04/DATA-03 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-05-07` as `COMPLETED`, manifest `WORLD05_07_COMPLETED_REST_BLOCKED`: **478 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 214 `COMPLETED`, 56 approved gates**. Checkpoint promotion remains owner-only.
