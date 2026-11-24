# NLE-PRPLAN-WORLD-03-06 — Streaming plan metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO STREAMING TASK OR I/O`. **Base:** `3bba470`. **Gate:** [NLE-PRPLAN-WORLD-03-06-G6-ACTIVATION](NLE-PRPLAN-WORLD-03-06-G6-ACTIVATION.md). **Contract:** [world-03-spatial-internal-v0](../contracts/world-03-spatial-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-03-06](../work-orders/NLE-PRPLAN-WORLD-03-06.md). **PR:** pendente.

## Scope delivered

- `src/stormline/spatial/streaming_plan.hpp`: streaming cell/plan descriptors and `plan_streaming`.
- `tests/core/world03_streaming_tests.cpp`: STR-01.
- Additive CMake test target and TSan target.
- No task creation/cancellation, I/O, decode, cache, bundle execution, origin rebase, spatial index, physics, networking, renderer, editor, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- World ID and revision must be nonzero; cell count is `0..64`.
- Cell keys are nonzero and unique; priorities are allowlisted.
- Request generation is nonzero; cancel generation is `<=` request generation, so immediate cancellation is representable.
- Per-cell byte budget is `<= 1 GiB`; totals use checked `u64` accumulation and reset the plan on overflow.
- `pinned_count` and `prefetch_count` report priority counts; optional and evict cells contribute only to the total.
- Invalid input zeroes the plan and sets a typed diagnostic with the world ID and cell index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/world03_streaming_tests.cpp` — PASS.
- ASan/UBSan build and `str01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `str01` — PASS.

## Errors and corrections

- None during implementation; the declared TSan target and CMake additions compiled first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread or global state.
- Logical streaming-plan metadata only; no task, I/O, decode, cache or bundle execution and no asynchronous engine code is added.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No task creation/cancellation, I/O/decode/cache, bundle execution, origin rebase, spatial index/storage, physics/networking, renderer, editor, GPU, performance, ABI or release.
- `WORLD-03-07`..`-08` remain blocked until their gates.
- WORLD-02/DATA-05 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-03-06` as `COMPLETED`, manifest `WORLD03_06_COMPLETED_REST_BLOCKED`: **497 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 199 `COMPLETED`, 52 approved gates**. Checkpoint promotion remains owner-only.
