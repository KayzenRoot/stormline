# NLE-PRPLAN-GFX-01-07 — logical synchronization evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU SYNCHRONIZATION CLAIM`. **Base:** `5116155`. **Gate:** [NLE-PRPLAN-GFX-01-07-G6-ACTIVATION](NLE-PRPLAN-GFX-01-07-G6-ACTIVATION.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md). **WO:** [NLE-PRPLAN-GFX-01-07](../work-orders/NLE-PRPLAN-GFX-01-07.md).

## Scope delivered

- `src/stormline/graphics/rhi/rhi_sync.hpp`: `validate_barrier`.
- `tests/core/gfx01_sync_tests.cpp`: SYN-01.
- Additive CMake/workflow entries.

No features/qualification, native fence/timeline/GPU, rendering, shader, dependency, ABI or release.

## Implementation notes

- Device must be Ready; otherwise `DeviceLost`.
- Handle requires current device generation, slot range, used slot, slot generation and matching resource class.
- Access bits must be nonzero and subset of `0x3F`; stage bits must be nonzero and subset of `0xF`.
- A fully identical access/stage pair is rejected as `SyncInvalid`; no real GPU synchronization is performed.
- No state is mutated and no allocation occurs.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx01_sync_tests.cpp -o /tmp/gfx01_sync_test
/tmp/gfx01_sync_test syn01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0; the raw WSL invocation fails with `ThreadSanitizer: unexpected memory mapping` before main, which is an environment ASLR limitation, not a test failure.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- Initial test fixture expected `InvalidDescriptor` before device init; the established API returns `DeviceLost`. Fixture corrected before the passing run.
- Local TSan required ASLR disabled through `setarch -R`; CI already applies this.

## Security and architecture

- Header-only internal C++20; no GPU, driver, allocator, file or network.
- Barrier validation is logical only and makes no ordering or hazard claim.

## Rollback

Revert normally; remove sync header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No native fences, timelines, barriers or GPU synchronization.
- No feature-tier implementation or qualification yet.
- `GFX-01-08`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-01-07` as `COMPLETED`, manifest `GFX01_07_COMPLETED_REST_BLOCKED`: **627 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 96 `COMPLETED`, 24 approved gates**.
