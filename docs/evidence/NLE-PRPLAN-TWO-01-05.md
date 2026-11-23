# NLE-PRPLAN-TWO-01-05 — Layer order evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO COMPOSITING`. **Base:** `23f2cb6`. **Gate:** [NLE-PRPLAN-TWO-01-05-G6-ACTIVATION](NLE-PRPLAN-TWO-01-05-G6-ACTIVATION.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-01-05](../work-orders/NLE-PRPLAN-TWO-01-05.md). **PR:** #796.

## Scope delivered

- `src/stormline/graphics/canvas2d/layer_plan.hpp`: descriptors/plan and `plan_layers`.
- `tests/core/two01_layer_tests.cpp`: LAY-01.
- Additive CMake test and TSan target.
- No compositing, sorting for batching, clip execution, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Layer IDs/revisions must be nonzero; IDs and declared orders must be unique.
- Opacity is finite in `[0,1]`; clip depth is `0..8`; blend mode must be declared.
- The plan returns layer IDs sorted by declared order, preserving painter order; no layer is composited or reordered for batching.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two01_layer_tests.cpp -o /tmp/two01_layer
/tmp/two01_layer lay01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/two01_layer_tests.cpp -o /tmp/two01_layer_san
/tmp/two01_layer_san lay01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/two01_layer_tests.cpp -o /tmp/two01_layer_tsan
setarch "$(uname -m)" -R /tmp/two01_layer_tsan lay01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- Initial implementation required contiguous orders, exceeding the contract; corrected to stable sorting by unique declared order before commit.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no composite or visual result is claimed.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No compositing, clipping execution, GPU, render, hardware, performance, ABI or release.
- `TWO-01-06`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `TWO-01-05` as `COMPLETED`, manifest `TWO01_05_COMPLETED_REST_BLOCKED`: **552 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 156 `COMPLETED`, 40 approved gates**.
