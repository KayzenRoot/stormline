# NLE-PRPLAN-GFX-01-04 — logical queue evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU CLAIM`. **Base:** `53f614d`. **Gate:** [NLE-PRPLAN-GFX-01-04-G6-ACTIVATION](NLE-PRPLAN-GFX-01-04-G6-ACTIVATION.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md). **WO:** [NLE-PRPLAN-GFX-01-04](../work-orders/NLE-PRPLAN-GFX-01-04.md).

## Scope delivered

- `src/stormline/graphics/rhi/rhi_queue.hpp`: out-of-class `queue_supported`, `submit`, `submit_count`.
- Additive `submit_count_` state in `rhi_device.hpp`.
- `tests/core/gfx01_queue_tests.cpp`: QUE-01.
- Additive CMake/workflow entries.

No buffers/textures/sync/features, native queue, rendering, shader, dependency, ABI or release.

## Implementation notes

- Graphics and Transfer are available in Ready state; Compute requires the compute feature.
- Submit requires Ready, supported role and 1..64 commands; increments a logical counter.
- Loss blocks queue support and submit until recovery.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx01_queue_tests.cpp -o /tmp/gfx01_que
/tmp/gfx01_que que01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- Queue accounting needed an additive private counter; added to `rhi_device.hpp`. No native code.

## Security and architecture

- Header-only internal C++20; no GPU, driver, allocation, file or network.

## Rollback

Revert normally; remove queue header/test, the counter and additive CMake/workflow entries.

## Open risks / not claimed

- No native queue or GPU; no buffers/textures/sync/features yet.
- No rendering/shader/swapchain/GPU timing/ABI/release.
- `GFX-01-05`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-01-04` as `COMPLETED`, manifest `GFX01_04_COMPLETED_REST_BLOCKED`: **631 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 93 `COMPLETED`, 24 approved gates**.
