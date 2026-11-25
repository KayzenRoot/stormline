# NLE-PRPLAN-SIM-04-06 — Ragdoll profile metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO RAGDOLL RUNTIME`. **Base:** `a4ade2a5`. **Gate:** [NLE-PRPLAN-SIM-04-06-G6-ACTIVATION](NLE-PRPLAN-SIM-04-06-G6-ACTIVATION.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-04-06](../work-orders/NLE-PRPLAN-SIM-04-06.md). **PR:** #983.

## Scope delivered

- `src/stormline/animation/skeletal/ragdoll_plan.hpp`: `RagdollProfileDesc`, `RagdollSetDesc`, `RagdollPlan`, `plan_ragdolls`.
- `tests/core/sim04_ragdoll_tests.cpp`: RAG-01.
- Additive CMake target/test and TSan target.
- No ragdoll runtime/activation, physics solver, pose evaluation, graph runtime, codec, root motion, ECS mutation, GPU, animation runtime, ABI or release claim.

## Implementation notes

- Owner ID/revision nonzero; count `0..16`; IDs nonzero and unique; revisions nonzero; body/constraint mapping IDs nonzero.
- Activation weight finite and in `[0,1]`; plan counts auto and enabled profiles; reset and typed diagnostic on failure.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict `-Werror`, ASan/UBSan and TSan builds with `rag01` — PASS.

## Errors and corrections

- None; implementation follows the corrected contract exactly.

## Security and architecture

- Header-only internal C++20; no allocation, exception, I/O, GPU, clock, thread, random source or global state. SIM-02 retains physics/ragdoll lifetime authority.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No ragdoll runtime/activation, physics solver/backend, pose evaluation, graph runtime, codec, root motion, ECS mutation, GPU, animation runtime, performance, ABI or release.
- `SIM-04-07`..`-10` remain blocked until their gates.

## Proposed checkpoint delta

After merge, record `SIM-04-06` as `COMPLETED`, manifest `SIM04_06_COMPLETED_REST_BLOCKED`: **441 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 243 `COMPLETED`, 64 approved gates**. Checkpoint promotion remains owner-only.
