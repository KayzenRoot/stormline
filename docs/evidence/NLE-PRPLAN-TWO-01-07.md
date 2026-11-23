# NLE-PRPLAN-TWO-01-07 — Pixel snapping evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PIXEL SAMPLING`. **Base:** `360cc77`. **Gate:** [NLE-PRPLAN-TWO-01-07-G6-ACTIVATION](NLE-PRPLAN-TWO-01-07-G6-ACTIVATION.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-01-07](../work-orders/NLE-PRPLAN-TWO-01-07.md). **PR:** #800.

## Scope delivered

- `src/stormline/graphics/canvas2d/snap_plan.hpp`: descriptor/plan and `plan_snap`.
- `tests/core/two01_snap_tests.cpp`: SNP-01.
- Additive CMake test and TSan target.
- No pixel sampling, rasterization, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Modes/filters must be declared; scales must be finite positive; offsets finite.
- Integer mode rounds offsets to nearest integer and marks `degraded=true` when either scale is non-integral.
- Continuous mode preserves offsets unchanged; no pixel is sampled.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two01_snap_tests.cpp -o /tmp/two01_snap
/tmp/two01_snap snp01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/two01_snap_tests.cpp -o /tmp/two01_snap_san
/tmp/two01_snap_san snp01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/two01_snap_tests.cpp -o /tmp/two01_snap_tsan
setarch "$(uname -m)" -R /tmp/two01_snap_tsan snp01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no pixel or visual result is claimed.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No pixel sampling/rasterization, GPU, render, hardware, performance, ABI or release.
- `TWO-01-08`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `TWO-01-07` as `COMPLETED`, manifest `TWO01_07_COMPLETED_REST_BLOCKED`: **550 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 158 `COMPLETED`, 40 approved gates**.
