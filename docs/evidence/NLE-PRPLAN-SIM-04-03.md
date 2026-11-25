# NLE-PRPLAN-SIM-04-03 — Retarget profile metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO POSE EVALUATION`. **Base:** `5e0c6e25`. **Gate:** [NLE-PRPLAN-SIM-04-03-G6-ACTIVATION](NLE-PRPLAN-SIM-04-03-G6-ACTIVATION.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-04-03](../work-orders/NLE-PRPLAN-SIM-04-03.md). **PR:** #977.

## Scope delivered

- `src/stormline/animation/skeletal/skeletal_types.hpp`: aliases, capacities, `SkeletalError`, `BlendKind`, `SkeletalDiagnostic` and detail helpers.
- `src/stormline/animation/skeletal/retarget_plan.hpp`: `RetargetJointPair`, `RetargetProfileDesc`, `RetargetSetDesc`, `RetargetPlan`, `plan_retargets`.
- `tests/core/sim04_retarget_tests.cpp`: RET-01.
- Additive CMake target/test and TSan target.
- No pose conversion/evaluation, graph runtime, solver, ragdoll, codec, root motion, ECS mutation, GPU, animation runtime, ABI or release claim.

## Implementation notes

- Owner ID/revision nonzero; profile count `0..16`; profile IDs nonzero and unique; revisions nonzero; bind scale finite and `> 0`.
- Pair count `0..64`; source/target joints nonzero and unique per side within a profile.
- Plan counts profiles, total pairs and enabled profiles; reset and typed diagnostic on failure.
- Uses the corrected `stormline::animation::skeletal` namespace; TWO-03 headers are untouched.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict `-Werror`, ASan/UBSan and TSan builds with `ret01` — PASS.

## Errors and corrections

- Baseline collision with TWO-03 resolved in the contract correction PR #976 before implementation; no TWO-03 file was changed.

## Security and architecture

- Header-only internal C++20; no allocation, exception, I/O, GPU, clock, thread, random source or global state. No pose conversion or runtime handle.

## Rollback

Revert normally; remove the headers/test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No pose conversion/evaluation, graph runtime, solver, ragdoll, codec, root motion, ECS mutation, GPU, animation runtime, performance, ABI or release.
- `SIM-04-04`..`-10` remain blocked until their gates.

## Proposed checkpoint delta

After merge, record `SIM-04-03` as `COMPLETED`, manifest `SIM04_03_COMPLETED_REST_BLOCKED`: **444 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 240 `COMPLETED`, 64 approved gates**. Checkpoint promotion remains owner-only.
