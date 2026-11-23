# NLE-PRPLAN-GFX-05-08 — Transparency ordering and overdraw evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO BLENDING, GPU OR OVERDRAW MEASUREMENT`. **Base:** `fd7d55e`. **Gate:** [NLE-PRPLAN-GFX-05-08-G6-ACTIVATION](NLE-PRPLAN-GFX-05-08-G6-ACTIVATION.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-05-08](../work-orders/NLE-PRPLAN-GFX-05-08.md).

## Scope delivered

- `src/stormline/graphics/material/transparency.hpp`: `TransparentItem`, `TransparentSet`, `TransparencyPlan`, `plan_transparency`.
- `tests/core/gfx05_transparency_tests.cpp`: TRN-01.
- Additive CMake test entry and TSan target.
- No blending, GPU, renderer, performance, dependency, ABI, release, hardware or measured overdraw claim.

## Implementation notes

- Items require nonzero unique IDs, finite depth, `Blend`/`Transmission` alpha and `depth_write=false`.
- `Blend` accepts `AlphaBlend`/`Premultiplied`; `Transmission` requires `AlphaBlend`.
- Output is back-to-front: depth descending, then ID ascending for ties.
- `max_items` is `1..64`; a set larger than it returns `TransparencyBudgetExceeded`.
- `overdraw_count` is admitted items after the first; no GPU overdraw is measured.
- Invalid input zeroes the plan.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx05_transparency_tests.cpp -o /tmp/gfx05_trn
/tmp/gfx05_trn trn01
g++ ... -fsanitize=address,undefined ... -o /tmp/gfx05_trn_asan
/tmp/gfx05_trn_asan trn01
g++ ... -fsanitize=thread ... -o /tmp/gfx05_trn_tsan
setarch "$(uname -m)" -R env TSAN_OPTIONS=halt_on_error=1 /tmp/gfx05_trn_tsan trn01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Ordering/budget are metadata; no blend, pixel or frame-time result is claimed.

## Rollback

Revert normally; remove the transparency header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No qualification/closeout yet.
- No blending, GPU, rendering, measured overdraw, performance, ABI or release.
- `GFX-05-09`/`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-05-08` as `COMPLETED`, manifest `GFX05_08_COMPLETED_REST_BLOCKED`: **589 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 127 `COMPLETED`, 32 approved gates**.
