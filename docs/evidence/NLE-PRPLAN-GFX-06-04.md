# NLE-PRPLAN-GFX-06-04 — Logical shadow planning evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO SHADOW MAP OR GPU RESOURCE`. **Base:** `7f5a365`. **Gate:** [NLE-PRPLAN-GFX-06-04-G6-ACTIVATION](NLE-PRPLAN-GFX-06-04-G6-ACTIVATION.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-06-04](../work-orders/NLE-PRPLAN-GFX-06-04.md).

## Scope delivered

- `src/stormline/graphics/lighting/shadow_plan.hpp`: cascade planning and shadow-page request planning.
- `tests/core/gfx06_shadow_tests.cpp`: SHD-01.
- Additive CMake test and TSan target.
- No shadow map, depth texture, page table, GPU resource, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Cascades require `0 < near < far`, `1..4` cascades and `lambda` in `[0,1]`.
- Practical splits combine logarithmic/uniform distances; the final far is exact and every split is finite/increasing.
- Page IDs are nonzero/unique; each light must exist and have shadow enabled; distances are finite/nonnegative.
- Resident pages are counted and skipped. Missing pages are sorted by distance then ID and admitted until budget.
- Any unadmitted missing page sets `coarse_fallback=true`; no partial success is hidden.
- No shadow map or page table is allocated.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx06_shadow_tests.cpp -o /tmp/gfx06_shadow
/tmp/gfx06_shadow shd01
```

Exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Plans are metadata; no shadow map, depth buffer or visual result is claimed.

## Rollback

Revert normally; remove the shadow header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No GI, probes, reflections or volumetrics yet.
- No shadow map, GPU, ray tracing, rendering, hardware, performance, ABI or release.
- `GFX-06-05`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-06-04` as `COMPLETED`, manifest `GFX06_04_COMPLETED_REST_BLOCKED`: **583 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 131 `COMPLETED`, 34 approved gates**.
