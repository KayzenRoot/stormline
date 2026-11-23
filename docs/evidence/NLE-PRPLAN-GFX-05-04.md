# NLE-PRPLAN-GFX-05-04 — Texture metadata and virtual pages evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO GPU, CODEC, UPLOAD OR RESIDENCY`. **Base:** `4c9736c`. **Gate:** [NLE-PRPLAN-GFX-05-04-G6-ACTIVATION](NLE-PRPLAN-GFX-05-04-G6-ACTIVATION.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-05-04](../work-orders/NLE-PRPLAN-GFX-05-04.md).

## Scope delivered

- `src/stormline/graphics/material/virtual_texture.hpp`: texture metadata, `add_texture`, `validate_textures`, page request types and `plan_pages`.
- `tests/core/gfx05_texture_tests.cpp`: VTX-01.
- Additive CMake test entry and TSan target.
- No GPU, codec/decoder, upload, residency service, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Texture IDs are nonzero/unique; dimensions are `1..16384`; levels are `1..12` and equal the capped `floor(log2(max(width,height)))+1`.
- `BaseColor` requires sRGB; `Normal`, `Orm`, `Height` and `Occlusion` require linear. `Emissive` accepts either. `Depth32Float` is rejected for `BaseColor`/`Emissive` and requires linear.
- Virtual-page IDs are nonzero, unique and within `1..page_count`; residency is a logical set, not a real cache.
- Requests retain declaration order. Resident pages are skipped; over-budget/over-capacity requests set `truncated=true` and return the admitted prefix.
- `page_count * page_size` and admitted bytes use checked 64-bit arithmetic; no allocation, decode or upload occurs.
- Invalid input fails closed before any plan is emitted.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx05_texture_tests.cpp -o /tmp/gfx05_tex
/tmp/gfx05_tex vtx01
g++ ... -fsanitize=address,undefined ... -o /tmp/gfx05_tex_asan
/tmp/gfx05_tex_asan vtx01
g++ ... -fsanitize=thread ... -o /tmp/gfx05_tex_tsan
setarch "$(uname -m)" -R env TSAN_OPTIONS=halt_on_error=1 /tmp/gfx05_tex_tsan vtx01
```

All exited 0. CMake is unavailable locally; the additive target/test wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- The first heredoc write truncated the tail of `virtual_texture.hpp`; the incomplete line was removed, `<limits>` was added and the remaining `plan_pages` body was appended. The first strict compile after the fix passed.
- No runtime or sanitizer defect was observed.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU, codec or global state.
- Page planning is metadata; no residency, eviction, upload or sampling behavior is claimed.

## Rollback

Revert normally; remove the texture header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No mip metadata, samplers, decals or transparency yet.
- No native GPU, texture codec, upload, residency service, rendering, hardware, performance, ABI or release.
- `GFX-05-05`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-05-04` as `COMPLETED`, manifest `GFX05_04_COMPLETED_REST_BLOCKED`: **593 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 123 `COMPLETED`, 32 approved gates**.
