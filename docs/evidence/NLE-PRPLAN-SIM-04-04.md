# NLE-PRPLAN-SIM-04-04 — Blend tree metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO GRAPH EVALUATION`. **Base:** `871dd91d`. **Gate:** [NLE-PRPLAN-SIM-04-04-G6-ACTIVATION](NLE-PRPLAN-SIM-04-04-G6-ACTIVATION.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-04-04](../work-orders/NLE-PRPLAN-SIM-04-04.md). **PR:** #979.

## Scope delivered

- `src/stormline/animation/skeletal/blend_tree_plan.hpp`: `BlendNodeDesc`, `BlendSetDesc`, `BlendPlan`, `plan_blends`.
- `tests/core/sim04_blend_tests.cpp`: BLEND-01.
- Additive CMake target/test and TSan target.
- No graph evaluation, blend execution, pose evaluation, solver, ragdoll, codec, root motion, ECS mutation, GPU, animation runtime, ABI or release claim.

## Implementation notes

- Owner ID/revision nonzero; count `0..64`; node IDs nonzero and unique; revisions nonzero; kind allowlist.
- Weight and threshold finite and in `[0,1]`; plan counts kinds and enabled nodes; reset and typed diagnostic on failure.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict `-Werror`, ASan/UBSan and TSan builds with `blend01` — PASS.

## Errors and corrections

- None; implementation follows the corrected contract exactly.

## Security and architecture

- Header-only internal C++20; no allocation, exception, I/O, GPU, clock, thread, random source or global state. No graph evaluation or runtime handle.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No graph evaluation, blend execution, pose evaluation, solver, ragdoll, codec, root motion, ECS mutation, GPU, animation runtime, performance, ABI or release.
- `SIM-04-05`..`-10` remain blocked until their gates.

## Proposed checkpoint delta

After merge, record `SIM-04-04` as `COMPLETED`, manifest `SIM04_04_COMPLETED_REST_BLOCKED`: **443 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 241 `COMPLETED`, 64 approved gates**. Checkpoint promotion remains owner-only.
