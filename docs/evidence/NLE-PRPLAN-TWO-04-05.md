# NLE-PRPLAN-TWO-04-05 — Deterministic sort evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO GPU SORT OR DRAW LIST`. **Base:** `79dcdb5`. **Gate:** [NLE-PRPLAN-TWO-04-05-G6-ACTIVATION](NLE-PRPLAN-TWO-04-05-G6-ACTIVATION.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-04-05](../work-orders/NLE-PRPLAN-TWO-04-05.md). **PR:** #843.

## Scope delivered

- `src/stormline/hybrid/sort_plan.hpp`: sort object/descriptor, plan and `plan_sort`.
- `tests/core/two04_sort_tests.cpp`: SRT-01.
- Additive CMake test and TSan target.
- No renderer, GPU sort, draw list, depth attachment, matrix, lighting, effect, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Scene ID/revision nonzero; object count `1..64`.
- Object IDs/revisions nonzero and unique; depth keys finite.
- Stable insertion sort by ascending `layer_order`, then `depth_key`, then `tie_breaker`; equal keys keep original order.
- `plan.order` contains object IDs in deterministic order; no GPU sort or draw submission.
- Invalid input zeroes the plan and sets a typed diagnostic.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict GCC flags, ASan/UBSan and TSan all passed for SRT-01.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, thread or global state.
- Logical sort intent only; no draw list or painter implementation is created.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No renderer, GPU sort, draw list, depth attachment, matrix, lighting, effects, editor, audio, export, ABI, release, hardware or performance.
- `TWO-04-06`..`-08` remain blocked until their gates.
- TWO-01/GFX-04 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `TWO-04-05` as `COMPLETED`, manifest `TWO04_05_COMPLETED_REST_BLOCKED`: **524 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 178 `COMPLETED`, 46 approved gates**. Checkpoint promotion remains owner-only.
