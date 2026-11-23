# NLE-PRPLAN-TWO-02-06 — Parallax evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO SCROLL EXECUTION`. **Base:** `04ab7f9`. **Gate:** [NLE-PRPLAN-TWO-02-06-G6-ACTIVATION](NLE-PRPLAN-TWO-02-06-G6-ACTIVATION.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-02-06](../work-orders/NLE-PRPLAN-TWO-02-06.md). **PR:** #815.

## Scope delivered

- `src/stormline/tilemap/parallax_plan.hpp`: descriptor/plan and `plan_parallax`.
- `tests/core/two02_parallax_tests.cpp`: PRX-01.
- Additive CMake test and TSan target.
- No render transform, scrolling, GPU, renderer, importer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Layer ID/revision must be nonzero; factors finite in `[0,4]`.
- Repeat flags are preserved; no scroll transform is executed.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two02_parallax_tests.cpp -o /tmp/two02_prx
/tmp/two02_prx prx01
g++ ... -fsanitize=address,undefined ... -o /tmp/two02_prx_san
/tmp/two02_prx_san prx01
g++ ... -fsanitize=thread ... -o /tmp/two02_prx_tsan
setarch "$(uname -m)" -R /tmp/two02_prx_tsan prx01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no parallax or visual result is claimed.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No render transform/scrolling, GPU, render, hardware, performance, ABI or release.
- `TWO-02-07`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `TWO-02-06` as `COMPLETED`, manifest `TWO02_06_COMPLETED_REST_BLOCKED`: **541 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 165 `COMPLETED`, 42 approved gates**.
