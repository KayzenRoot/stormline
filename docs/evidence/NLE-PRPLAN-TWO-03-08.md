# NLE-PRPLAN-TWO-03-08 — Integrated animation qualification evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / QUALIFICATION IS CI-ONLY`. **Base:** `9c85537`. **Gate:** [NLE-PRPLAN-TWO-03-08-G6-ACTIVATION](NLE-PRPLAN-TWO-03-08-G6-ACTIVATION.md). **Contract:** [two-03-animation-internal-v0](../contracts/two-03-animation-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-03-08](../work-orders/NLE-PRPLAN-TWO-03-08.md). **PR:** #834.

## Scope delivered

- `tests/core/two03_animation_qualification_tests.cpp`: QLF-T301..T304.
- Additive CMake executable/tests and TSan target.
- No runtime, pose, skinning, playback, audio, export, GPU, hardware, performance, dependency, ABI or release qualification.

## Qualification fixtures

- **QLF-T301 integrated:** valid flipbook, skeleton, blend, sequence and timeline plans in one pass; counts, normalized weights, depths and sample mapping verified.
- **QLF-T302 deterministic repeat:** each planner is called twice with identical descriptors; every plan field and normalized weight matches exactly.
- **QLF-T303 failure recovery:** each planner receives one typed-invalid descriptor, then a valid descriptor; failure code is exact and recovery returns `None`.
- **QLF-T304 bounded overload:** 10,000 iterations call all five planners; every 97th/89th/83rd iteration injects one typed failure and restores the fixture; all returned plans remain within `kMaxFlipbookFrames`, `kMaxBones`, `kMaxBlendClips`, `kMaxSequenceTracks`, `kMaxSequenceCues` and `kMaxSequenceDepth`.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two03_animation_qualification_tests.cpp -o /tmp/two03q_strict
/tmp/two03q_strict qlft301
/tmp/two03q_strict qlft302
/tmp/two03q_strict qlft303
/tmp/two03q_strict qlft304
g++ ... -fsanitize=address,undefined -fno-omit-frame-pointer ... -o /tmp/two03q_asan
/tmp/two03q_asan qlft301..qlft304
g++ ... -fsanitize=thread ... -o /tmp/two03q_tsan
setarch "$(uname -m)" -R /tmp/two03q_tsan qlft301..qlft304
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only planners under test; no production file changed.
- No allocation, exception, file, network, audio, GPU, thread or global state.
- Qualification exercises planner contracts only; it is not physical, OS, security, soak or performance qualification.

## Rollback

Revert normally; remove the test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No runtime, pose, skinning, playback, audio, export, GPU, hardware, performance, ABI or release qualification.
- `TWO-03-09` remains blocked until its gate.
- CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `TWO-03-08` as `COMPLETED`, manifest `TWO03_08_COMPLETED_REST_BLOCKED`: **530 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 174 `COMPLETED`, 44 approved gates**. Checkpoint promotion remains owner-only.
