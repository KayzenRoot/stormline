# NLE-PRPLAN-SIM-04-05 — IK chain metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO IK SOLVER`. **Base:** `bfd07f87`. **Gate:** [NLE-PRPLAN-SIM-04-05-G6-ACTIVATION](NLE-PRPLAN-SIM-04-05-G6-ACTIVATION.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-04-05](../work-orders/NLE-PRPLAN-SIM-04-05.md). **PR:** pendente.

## Scope delivered

- `src/stormline/animation/skeletal/ik_plan.hpp`: `IkChainDesc`, `IkSetDesc`, `IkPlan`, `plan_ik`.
- `tests/core/sim04_ik_tests.cpp`: IK-01.
- Additive CMake target/test and TSan target.
- No IK solver/execution, pose evaluation, graph runtime, ragdoll, codec, root motion, ECS mutation, GPU, animation runtime, ABI or release claim.

## Implementation notes

- Owner ID/revision nonzero; chain count `0..32`; IDs nonzero and unique; revisions nonzero.
- Bone count `1..16`; iterations `0..64`; tolerance finite `>= 0`; target weight in `[0,1]`.
- Plan counts chains, total bones, max iterations and enabled chains; reset and typed diagnostic on failure.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict `-Werror`, ASan/UBSan and TSan builds with `ik01` — PASS.

## Errors and corrections

- None; implementation follows the corrected contract exactly.

## Security and architecture

- Header-only internal C++20; no allocation, exception, I/O, GPU, clock, thread, random source or global state. No solver or runtime handle.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No IK solver/execution, pose evaluation, graph runtime, ragdoll, codec, root motion, ECS mutation, GPU, animation runtime, performance, ABI or release.
- `SIM-04-06`..`-10` remain blocked until their gates.

## Proposed checkpoint delta

After merge, record `SIM-04-05` as `COMPLETED`, manifest `SIM04_05_COMPLETED_REST_BLOCKED`: **442 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 242 `COMPLETED`, 64 approved gates**. Checkpoint promotion remains owner-only.
