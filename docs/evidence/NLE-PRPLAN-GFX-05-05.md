# NLE-PRPLAN-GFX-05-05 — Texture mip metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO IMAGE DECODE OR MIP GENERATION`. **Base:** `1967c6b`. **Gate:** [NLE-PRPLAN-GFX-05-05-G6-ACTIVATION](NLE-PRPLAN-GFX-05-05-G6-ACTIVATION.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-05-05](../work-orders/NLE-PRPLAN-GFX-05-05.md).

## Scope delivered

- `src/stormline/graphics/material/texture_mip.hpp`: `MipLevel`, `MipChain`, `build_mip_chain`.
- `tests/core/gfx05_mip_tests.cpp`: MIP-01.
- Additive CMake test entry and TSan target.
- No decoder, mip generator, upload, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- The chain is derived only from validated `TextureDesc` metadata.
- Level dimensions are `max(1, dimension >> level)`; the count is the validated capped level count.
- Bytes per pixel are 4 for `Rgba8Unorm`, `Rgba8Srgb` and `Depth32Float`; 8 for `Rgba16Float`.
- Level bytes use checked 64-bit multiplication; overflow returns `InvalidMipChain`.
- Zero/excess/mismatched levels return `InvalidMipChain`; invalid dimensions/format/color use return `InvalidArgument`.
- No pixels are read, decoded, generated, uploaded or sampled.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx05_mip_tests.cpp -o /tmp/gfx05_mip
/tmp/gfx05_mip mip01
g++ ... -fsanitize=address,undefined ... -o /tmp/gfx05_mip_asan
/tmp/gfx05_mip_asan mip01
g++ ... -fsanitize=thread ... -o /tmp/gfx05_mip_tsan
setarch "$(uname -m)" -R env TSAN_OPTIONS=halt_on_error=1 /tmp/gfx05_mip_tsan mip01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU, codec or global state.
- Mip chains are metadata; no image is produced.

## Rollback

Revert normally; remove the mip header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No samplers, decals or transparency yet.
- No image decoder, mip generator, upload, GPU, rendering, hardware, performance, ABI or release.
- `GFX-05-06`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-05-05` as `COMPLETED`, manifest `GFX05_05_COMPLETED_REST_BLOCKED`: **592 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 124 `COMPLETED`, 32 approved gates**.
