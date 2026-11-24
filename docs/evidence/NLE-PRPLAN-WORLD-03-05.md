# NLE-PRPLAN-WORLD-03-05 — Origin epoch metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ORIGIN REBASE`. **Base:** `c42ce39`. **Gate:** [NLE-PRPLAN-WORLD-03-05-G6-ACTIVATION](NLE-PRPLAN-WORLD-03-05-G6-ACTIVATION.md). **Contract:** [world-03-spatial-internal-v0](../contracts/world-03-spatial-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-03-05](../work-orders/NLE-PRPLAN-WORLD-03-05.md). **PR:** pendente.

## Scope delivered

- `src/stormline/spatial/origin_plan.hpp`: epoch descriptor, plan and `plan_origin_change`.
- `tests/core/world03_origin_tests.cpp`: ORG-01.
- Additive CMake test target and TSan target.
- No origin rebase, coordinate rewrite, identity change, cell storage, streaming task, I/O, decode, cache, physics, networking, renderer, editor, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- World ID and revision must be nonzero; old and new epochs are nonzero and distinct.
- All six old/new origin coordinates must be finite; NaN and infinities are rejected with `NonFiniteValue`.
- `accepted` is true only when physics, render and network acknowledgements are all present; failure combinations still return a successful plan with `accepted=false`.
- The plan copies the old/new epoch identifiers and never mutates entity, cell or coordinate state.
- Invalid input zeroes the plan and sets a typed diagnostic with the world ID and index zero.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/world03_origin_tests.cpp` — PASS.
- ASan/UBSan build and `org01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `org01` — PASS.

## Errors and corrections

- None during implementation; the declared TSan target and CMake additions compiled first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread or global state.
- Logical origin-epoch intent only; no rebase execution, identity rewrite or spatial index exists.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No origin rebase/identity rewrite, spatial index/storage, async streaming, I/O/decode/cache, physics/networking, renderer, editor, GPU, performance, ABI or release.
- `WORLD-03-06`..`-08` remain blocked until their gates.
- WORLD-02/DATA-05 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-03-05` as `COMPLETED`, manifest `WORLD03_05_COMPLETED_REST_BLOCKED`: **498 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 198 `COMPLETED`, 52 approved gates**. Checkpoint promotion remains owner-only.
