# NLE-PRPLAN-GFX-01-03 — logical device evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU CLAIM`. **Base:** `9e0995c`. **Gate:** [NLE-PRPLAN-GFX-01-03-G6-ACTIVATION](NLE-PRPLAN-GFX-01-03-G6-ACTIVATION.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md). **WO:** [NLE-PRPLAN-GFX-01-03](../work-orders/NLE-PRPLAN-GFX-01-03.md).

## Scope delivered

- `src/stormline/graphics/rhi/rhi_types.hpp`: errors, backend/state/queue/resource enums, descriptors/handles.
- `src/stormline/graphics/rhi/rhi_device.hpp`: Null adapter, device init/close/loss/recover and capabilities.
- `tests/core/gfx01_device_tests.cpp`: DEV-01.
- Additive CMake/workflow entries.

No queues/resources/barriers/features, native GPU, shader, swapchain, rendering, dependency, ABI or release.

## Implementation notes

- Exactly one Null adapter with compute/indirect features.
- Init requires matching adapter, known feature bits and tier 1.
- Loss/recovery increments device generation; close disposes.
- Resource/queue/barrier methods are declared for later slices but not implemented here; no native code.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx01_device_tests.cpp -o /tmp/gfx01_dev
/tmp/gfx01_dev dev01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

None introduced.

## Security and architecture

- Header-only internal C++20; no GPU, driver, allocation, file, network or database.

## Rollback

Revert normally; remove RHI headers/test and additive CMake/workflow entries.

## Open risks / not claimed

- No native GPU/backend, queues/resources/barriers/features yet.
- No rendering/shader/swapchain/GPU timing/ABI/release.
- `GFX-01-04`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-01-03` as `COMPLETED`, manifest `GFX01_03_COMPLETED_REST_BLOCKED`: **632 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 92 `COMPLETED`, 24 approved gates**.
