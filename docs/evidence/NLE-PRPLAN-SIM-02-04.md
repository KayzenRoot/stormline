# NLE-PRPLAN-SIM-02-04 — Collision shape metadata 3D evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NARROWPHASE`. **Base:** `7865a643`. **Gate:** [NLE-PRPLAN-SIM-02-04-G6-ACTIVATION](NLE-PRPLAN-SIM-02-04-G6-ACTIVATION.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-02-04](../work-orders/NLE-PRPLAN-SIM-02-04.md). **PR:** #948.

## Scope delivered

- `src/stormline/physics3d/shape_plan.hpp`: `ShapeDesc`, `ShapeSetDesc`, `ShapePlan`, `plan_shapes`.
- `tests/core/sim02_shape_tests.cpp`: SHAPE3-01.
- Additive CMake test target/TSan target.
- No narrowphase, mesh/heightfield import, contacts, solver, simulation, ECS mutation, GPU, physics runtime, ABI or release claim.

## Implementation notes

- World ID/revision nonzero; count `0..128`; IDs, revisions and material IDs nonzero; kind allowlist; unique shape IDs.
- Sphere: radius `> 0`. Capsule: radius `> 0`, half_height `>= 0`. Box/Convex/Compound/Mesh/Heightfield: half extents `> 0`.
- Finite dimensions/density; density `>= 0`; plan counts kinds and sensors; reset and typed diagnostic on failure.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict `-Werror`, ASan/UBSan and TSan builds with `shape301` — PASS.

## Errors and corrections

- None; implementation follows the frozen contract exactly.

## Security and architecture

- Header-only internal C++20; no allocation, exception, I/O, GPU, clock, thread, random source or global state. No mesh cooking or collision pipeline.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No narrowphase, import, contacts, solver/backend, broadphase, simulation, ECS mutation, GPU, physics runtime, performance, ABI or release.
- `SIM-02-05`..`-10` remain blocked until their gates.

## Proposed checkpoint delta

After merge, record `SIM-02-04` as `COMPLETED`, manifest `SIM02_04_COMPLETED_REST_BLOCKED`: **461 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 227 `COMPLETED`, 60 approved gates**. Checkpoint promotion remains owner-only.
