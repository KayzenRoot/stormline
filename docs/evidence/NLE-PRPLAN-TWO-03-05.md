# NLE-PRPLAN-TWO-03-05 — Clip blend evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO RUNTIME BLEND`. **Base:** `71a4ab0`. **Gate:** [NLE-PRPLAN-TWO-03-05-G6-ACTIVATION](NLE-PRPLAN-TWO-03-05-G6-ACTIVATION.md). **Contract:** [two-03-animation-internal-v0](../contracts/two-03-animation-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-03-05](../work-orders/NLE-PRPLAN-TWO-03-05.md). **PR:** #828.

## Scope delivered

- `src/stormline/animation/blend_plan.hpp`: clip/blend descriptors, plan and `plan_blend`.
- `tests/core/two03_blend_tests.cpp`: BLD-01.
- Additive CMake test and TSan target.
- No runtime blend tree, pose mixing, additive evaluation, skinning, playback, sampling, renderer, GPU, audio, export, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Blend ID/revision must be nonzero; clip count is bounded by `kMaxBlendClips`.
- Clip IDs/revisions are nonzero and unique; weights must be finite and nonnegative.
- Sum is accumulated in `double`, preventing overflow for four finite `f32` maxima.
- Zero total weight fails; normalized weights are deterministic `weight/total` in `f32`.
- Additive blends require `discrete_targets`; contiguous additive metadata fails.
- Invalid input zeroes the plan and sets a typed diagnostic with source ID and clip index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two03_blend_tests.cpp -o /tmp/blend_strict
/tmp/blend_strict bld01
g++ ... -fsanitize=address,undefined -fno-omit-frame-pointer ... -o /tmp/blend_asan
/tmp/blend_asan bld01
g++ ... -fsanitize=thread ... -o /tmp/blend_tsan
setarch "$(uname -m)" -R /tmp/blend_tsan bld01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, thread or global state.
- Logical blend metadata only; no clip or pose is evaluated, composited or applied.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No runtime blend tree, pose mixing, additive evaluation, skinning, playback, sampling, rendering, GPU, audio, export, ABI, release, hardware or performance.
- `TWO-03-06`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `TWO-03-05` as `COMPLETED`, manifest `TWO03_05_COMPLETED_REST_BLOCKED`: **533 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 171 `COMPLETED`, 44 approved gates**. Checkpoint promotion remains owner-only.
