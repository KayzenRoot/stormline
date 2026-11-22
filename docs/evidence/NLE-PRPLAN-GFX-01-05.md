# NLE-PRPLAN-GFX-01-05 — logical buffer evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU OR MEMORY CLAIM`. **Base:** `8d5db58`. **Gate:** [NLE-PRPLAN-GFX-01-05-G6-ACTIVATION](NLE-PRPLAN-GFX-01-05-G6-ACTIVATION.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md). **WO:** [NLE-PRPLAN-GFX-01-05](../work-orders/NLE-PRPLAN-GFX-01-05.md).

## Scope delivered

- `src/stormline/graphics/rhi/rhi_buffer.hpp`: `create_buffer`, `release`, `resource_info`.
- Additive resource-slot state in `rhi_device.hpp`.
- `tests/core/gfx01_buffer_tests.cpp`: BUF-01.
- Additive CMake/workflow entries.

No textures/sync/features, native buffer/GPU memory, rendering, shader, dependency, ABI or release.

## Implementation notes

- Buffers 1..4096 bytes, usage subset `0x3F`, power-of-two alignment 1..256.
- 64 resource slots; handles carry device generation, slot and slot generation.
- Release invalidates the slot generation; stale/double release fails; device loss blocks resource access.
- Capacity is fixed; no allocator or GPU mapping.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx01_buffer_tests.cpp -o /tmp/gfx01_buf
/tmp/gfx01_buf buf01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- Release/resource_info initially allowed access while the device was Lost; corrected to `DeviceLost`. No native code.

## Security and architecture

- Header-only internal C++20; no GPU, driver, allocator, file or network.

## Rollback

Revert normally; remove buffer header/test, resource-slot state and additive CMake/workflow entries.

## Open risks / not claimed

- No native buffer/GPU memory or allocator.
- No textures/sync/features yet.
- `GFX-01-06`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-01-05` as `COMPLETED`, manifest `GFX01_05_COMPLETED_REST_BLOCKED`: **630 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 94 `COMPLETED`, 24 approved gates**.
