# NLE-PRPLAN-TWO-03-07 — Rational timeline evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO CLOCK OR PLAYBACK`. **Base:** `df141a8`. **Gate:** [NLE-PRPLAN-TWO-03-07-G6-ACTIVATION](NLE-PRPLAN-TWO-03-07-G6-ACTIVATION.md). **Contract:** [two-03-animation-internal-v0](../contracts/two-03-animation-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-03-07](../work-orders/NLE-PRPLAN-TWO-03-07.md). **PR:** #832.

## Scope delivered

- `src/stormline/animation/timeline_plan.hpp`: timeline descriptor, plan and `plan_timeline`.
- `tests/core/two03_timeline_tests.cpp`: TML-01.
- Additive CMake test and TSan target.
- No clock, playback, seek/reverse runtime, audio scheduling, export/codec, editor UI, renderer, GPU, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Timeline ID/revision, fps numerator/denominator, duration and sample rate must be positive.
- Loop region requires `loop_end > loop_start` and `loop_end <= duration`; loop length is returned.
- Sample mapping is `floor(duration_frames * fps_denominator * sample_rate / fps_numerator)`.
- Both multiplications are checked against `u64` overflow before division.
- Integer division is deterministic; no rounding or floating point is used.
- Invalid input zeroes the plan and sets a typed diagnostic.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two03_timeline_tests.cpp -o /tmp/timeline_strict
/tmp/timeline_strict tml01
g++ ... -fsanitize=address,undefined -fno-omit-frame-pointer ... -o /tmp/timeline_asan
/tmp/timeline_asan tml01
g++ ... -fsanitize=thread ... -o /tmp/timeline_tsan
setarch "$(uname -m)" -R /tmp/timeline_tsan tml01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, thread or global state.
- Logical timeline metadata only; no clock is read and no sample is scheduled.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No clock, playback, seek/reverse runtime, audio scheduling, export/codec, editor UI, rendering, GPU, ABI, release, hardware or performance.
- `TWO-03-08`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `TWO-03-07` as `COMPLETED`, manifest `TWO03_07_COMPLETED_REST_BLOCKED`: **531 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 173 `COMPLETED`, 44 approved gates**. Checkpoint promotion remains owner-only.
