# NLE-PRPLAN-GFX-05-07 — Decal ordering evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PROJECTION OR BLENDING`. **Base:** `a80649f`. **Gate:** [NLE-PRPLAN-GFX-05-07-G6-ACTIVATION](NLE-PRPLAN-GFX-05-07-G6-ACTIVATION.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-05-07](../work-orders/NLE-PRPLAN-GFX-05-07.md).

## Scope delivered

- `src/stormline/graphics/material/decal.hpp`: `DecalDesc`, `DecalSet`, `DecalPlan`, `plan_decals`.
- `tests/core/gfx05_decal_tests.cpp`: DEC-01.
- Additive CMake test entry and TSan target.
- No projection, blending, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Decal IDs are nonzero/unique; layers are `<32`; positions/radius/opacity are finite; radius is `>0`; opacity is in `[0,1]`.
- Duplicate IDs return `DecalConflict`; set overflow returns `CapacityFull`.
- The plan is sorted by `(layer, id)` ascending and contains only authored IDs.
- Invalid input zeroes the plan; no partial output is returned.
- No projection, clipping, blending, sampling or draw is performed.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx05_decal_tests.cpp -o /tmp/gfx05_dec
/tmp/gfx05_dec dec01
g++ ... -fsanitize=address,undefined ... -o /tmp/gfx05_dec_asan
/tmp/gfx05_dec_asan dec01
g++ ... -fsanitize=thread ... -o /tmp/gfx05_dec_tsan
setarch "$(uname -m)" -R env TSAN_OPTIONS=halt_on_error=1 /tmp/gfx05_dec_tsan dec01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Ordering is metadata; no visual or blend result is claimed.

## Rollback

Revert normally; remove the decal header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No transparency sorting/overdraw yet.
- No projection, blending, GPU, rendering, hardware, performance, ABI or release.
- `GFX-05-08`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-05-07` as `COMPLETED`, manifest `GFX05_07_COMPLETED_REST_BLOCKED`: **590 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 126 `COMPLETED`, 32 approved gates**.
