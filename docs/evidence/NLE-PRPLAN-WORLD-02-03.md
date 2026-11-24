# NLE-PRPLAN-WORLD-02-03 — Scene hierarchy evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO SCENE RUNTIME OR STORAGE`. **Base:** `d01a605`. **Gate:** [NLE-PRPLAN-WORLD-02-03-G6-ACTIVATION](NLE-PRPLAN-WORLD-02-03-G6-ACTIVATION.md). **Contract:** [world-02-scene-internal-v0](../contracts/world-02-scene-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-02-03](../work-orders/NLE-PRPLAN-WORLD-02-03.md). **PR:** #867.

## Scope delivered

- `src/stormline/scene/scene_types.hpp`: aliases, capacities, errors, reparent mode and diagnostic.
- `src/stormline/scene/hierarchy_plan.hpp`: node/hierarchy descriptors, plan and `plan_scene_hierarchy`.
- `tests/core/world02_hierarchy_tests.cpp`: HIR-01.
- Additive CMake interface target/test and TSan target.
- No scene runtime, node storage, prefab expansion, serializer, journal, transform math, spatial, physics, networking, editor, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Scene ID/revision nonzero; node count `1..64`.
- Node IDs/revisions nonzero and unique.
- Parent is `0` (root) or an existing node; self-parent, missing parents and cycles fail.
- Depth is one for a root; greater than 16 fails with `DepthExceeded`.
- `(parent_id, sibling_order)` pairs are unique; the same order under different parents is allowed.
- Outputs node count, root count and maximum depth; display names/paths are not identity.
- Invalid input zeroes the plan and sets a typed diagnostic.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict GCC flags, ASan/UBSan and TSan all passed for HIR-01. The first sibling-order fixture used the same parent and was corrected to a different parent before evidence.

## Errors and corrections

- Corrected the "same order different parent" fixture to reparent node 3 under node 2; strict compile and sanitizers then passed.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, thread or global state.
- Logical hierarchy intent only; no node storage or transform math exists.

## Rollback

Revert normally; remove the headers/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No scene runtime/node storage, prefab expansion, serializer/journal, transform math, spatial, physics, networking, editor, GPU, performance, ABI or release.
- `WORLD-02-04`..`-09` remain blocked until their gates.
- WORLD-01/DATA-02 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-02-03` as `COMPLETED`, manifest `WORLD02_03_COMPLETED_REST_BLOCKED`: **509 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 189 `COMPLETED`, 50 approved gates**. Checkpoint promotion remains owner-only.
