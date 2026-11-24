# NLE-PRPLAN-TWO-03-04 — 2D bone hierarchy evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO POSE OR SKINNING`. **Base:** `ccede59`. **Gate:** [NLE-PRPLAN-TWO-03-04-G6-ACTIVATION](NLE-PRPLAN-TWO-03-04-G6-ACTIVATION.md). **Contract:** [two-03-animation-internal-v0](../contracts/two-03-animation-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-03-04](../work-orders/NLE-PRPLAN-TWO-03-04.md). **PR:** #826.

## Scope delivered

- `src/stormline/animation/skeleton_plan.hpp`: bone/skeleton descriptors, plan and `plan_skeleton`.
- `tests/core/two03_skeleton_tests.cpp`: BON-01.
- Additive CMake test and TSan target.
- No pose evaluation, skinning, IK, runtime hierarchy, playback, sampling, renderer, GPU, audio, export, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Skeleton ID and revision must be nonzero; bone count is bounded by `kMaxBones`.
- Bone IDs/revisions are nonzero and unique; local transforms must be finite.
- Parent is `0` (root) or an existing bone ID; missing parents fail.
- Self-parent and multi-bone cycles fail; each parent chain is walked with a bounded visited set.
- Depth is one for a root and increases per parent; greater than 16 fails with `DepthExceeded`.
- `root_count` counts parent-zero bones; `max_depth` is the deepest validated chain.
- Invalid input zeroes the plan and sets a typed diagnostic with source ID and bone index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two03_skeleton_tests.cpp -o /tmp/skeleton_strict
/tmp/skeleton_strict bon01
g++ ... -fsanitize=address,undefined -fno-omit-frame-pointer ... -o /tmp/skeleton_asan
/tmp/skeleton_asan bon01
g++ ... -fsanitize=thread ... -o /tmp/skeleton_tsan
setarch "$(uname -m)" -R /tmp/skeleton_tsan bon01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, thread or global state.
- Logical hierarchy metadata only; no transform is composed, evaluated or applied.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No pose evaluation, skinning, IK, runtime hierarchy, playback, sampling, rendering, GPU, audio, export, ABI, release, hardware or performance.
- `TWO-03-05`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `TWO-03-04` as `COMPLETED`, manifest `TWO03_04_COMPLETED_REST_BLOCKED`: **534 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 170 `COMPLETED`, 44 approved gates**. Checkpoint promotion remains owner-only.
