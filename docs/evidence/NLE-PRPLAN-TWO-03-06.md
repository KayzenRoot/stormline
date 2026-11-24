# NLE-PRPLAN-TWO-03-06 — Cutscene sequence evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO RUNTIME SEQUENCE OR CUE DISPATCH`. **Base:** `1610d1a`. **Gate:** [NLE-PRPLAN-TWO-03-06-G6-ACTIVATION](NLE-PRPLAN-TWO-03-06-G6-ACTIVATION.md). **Contract:** [two-03-animation-internal-v0](../contracts/two-03-animation-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-03-06](../work-orders/NLE-PRPLAN-TWO-03-06.md). **PR:** #830.

## Scope delivered

- `src/stormline/animation/sequence_plan.hpp`: cue/track/sequence descriptors, plan and `plan_sequence`.
- `tests/core/two03_sequence_tests.cpp`: SEQ-01.
- Additive CMake test and TSan target.
- No runtime playback, cue dispatch, event execution, camera/audio behavior, editing UI, renderer, GPU, export, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Sequence ID/revision/timebase/duration must be nonzero.
- Nesting depth is `0..4`; greater than 4 fails with `DepthExceeded`.
- Track count is `1..16`; track IDs/revisions are nonzero and unique; track kinds are allowlisted.
- Cue count per track is `0..16`; cue IDs/revisions are nonzero and unique across the sequence; cue kinds are allowlisted.
- Cue `tick` plus `duration_ticks` must fit the sequence duration; subtraction form avoids `u64` overflow.
- Zero-duration cues at the duration boundary are valid.
- `plan.cue_count` totals cues across tracks; `plan.max_depth` returns the declared nesting depth.
- Invalid input zeroes the plan and sets a typed diagnostic.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two03_sequence_tests.cpp -o /tmp/sequence_strict
/tmp/sequence_strict seq01
g++ ... -fsanitize=address,undefined -fno-omit-frame-pointer ... -o /tmp/sequence_asan
/tmp/sequence_asan seq01
g++ ... -fsanitize=thread ... -o /tmp/sequence_tsan
setarch "$(uname -m)" -R /tmp/sequence_tsan seq01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, thread or global state.
- Logical sequence metadata only; no cue is dispatched, played or applied.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No runtime playback, cue dispatch, event execution, camera/audio behavior, editing UI, rendering, GPU, export, ABI, release, hardware or performance.
- `TWO-03-07`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `TWO-03-06` as `COMPLETED`, manifest `TWO03_06_COMPLETED_REST_BLOCKED`: **532 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 172 `COMPLETED`, 44 approved gates**. Checkpoint promotion remains owner-only.
