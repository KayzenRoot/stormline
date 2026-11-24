# NLE-PRPLAN-WORLD-02-06 — Prefab instancing evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ENTITY CREATION OR EXPANSION`. **Base:** `23f637f`. **Gate:** [NLE-PRPLAN-WORLD-02-06-G6-ACTIVATION](NLE-PRPLAN-WORLD-02-06-G6-ACTIVATION.md). **Contract:** [world-02-scene-internal-v0](../contracts/world-02-scene-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-02-06](../work-orders/NLE-PRPLAN-WORLD-02-06.md). **PR:** #873.

## Scope delivered

- `src/stormline/scene/instance_plan.hpp`: instance/set descriptors, plan and `plan_prefab_instances`.
- `tests/core/world02_instance_tests.cpp`: INS-01.
- Additive CMake test and TSan target.
- No runtime instancing, entity creation, prefab expansion, serializer, journal, transform, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Scene ID/revision nonzero; instance count `0..16`.
- Instance/prefab IDs and revisions nonzero; instance IDs unique.
- Expansion count `1..4096`; depth `0..4`; total expansion accumulated in checked `u32`.
- Outputs instance count, total expansion and maximum depth.
- No entity is created or expanded; invalid input resets and sets a typed diagnostic.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict GCC flags, ASan/UBSan and TSan all passed for INS-01.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, thread or global state.
- Logical instance intent only; WORLD-01 owns entity creation.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No runtime instancing/entity creation/expansion, serializer/journal, transform math, spatial, physics, networking, editor, GPU, performance, ABI or release.
- `WORLD-02-07`..`-09` remain blocked until their gates.
- WORLD-01/DATA-02 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-02-06` as `COMPLETED`, manifest `WORLD02_06_COMPLETED_REST_BLOCKED`: **506 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 192 `COMPLETED`, 50 approved gates**. Checkpoint promotion remains owner-only.
