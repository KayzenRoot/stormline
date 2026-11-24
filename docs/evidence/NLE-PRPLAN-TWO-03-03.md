# NLE-PRPLAN-TWO-03-03 — Flipbook authoring evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PLAYBACK OR SAMPLING`. **Base:** `35f797a`. **Gate:** [NLE-PRPLAN-TWO-03-03-G6-ACTIVATION](NLE-PRPLAN-TWO-03-03-G6-ACTIVATION.md). **Contract:** [two-03-animation-internal-v0](../contracts/two-03-animation-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-03-03](../work-orders/NLE-PRPLAN-TWO-03-03.md). **PR:** #824.

## Scope delivered

- `src/stormline/animation/animation_types.hpp`: aliases, capacities, errors, track kinds, diagnostic and bounded detail helpers.
- `src/stormline/animation/flipbook_plan.hpp`: descriptors/plan and `plan_flipbook`.
- `tests/core/two03_flipbook_tests.cpp`: FLB-01.
- Additive CMake interface target/test and TSan target.
- No playback, sampling, frame advance, renderer, GPU, audio, export, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Clip ID, revision and timebase denominator must be nonzero.
- Frame count is bounded by `kMaxFlipbookFrames`; zero or excess fails.
- Frame IDs are nonzero and unique; sprite and atlas region IDs are nonzero; holds are positive.
- Total frames is accumulated with a checked `u64` guard. With 64 frames of at most `u32` holds the guard cannot overflow, so it remains defensive and is not exercised destructively in FLB-01.
- Invalid input zeroes the plan and sets a typed diagnostic with source ID and frame index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two03_flipbook_tests.cpp -o /tmp/flipbook_strict
/tmp/flipbook_strict flb01
g++ ... -fsanitize=address,undefined -fno-omit-frame-pointer ... -o /tmp/flipbook_asan
/tmp/flipbook_asan flb01
g++ ... -fsanitize=thread ... -o /tmp/flipbook_tsan
setarch "$(uname -m)" -R /tmp/flipbook_tsan flb01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, thread or global state.
- Logical frame metadata only; no frame is sampled, played or drawn.

## Rollback

Revert normally; remove the headers/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No playback, sampling, rendering, GPU, audio, export, ABI, release, hardware or performance.
- `TWO-03-04`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `TWO-03-03` as `COMPLETED`, manifest `TWO03_03_COMPLETED_REST_BLOCKED`: **535 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 169 `COMPLETED`, 44 approved gates**. Checkpoint promotion remains owner-only.
