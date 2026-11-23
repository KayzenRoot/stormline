# NLE-PRPLAN-GFX-08-06 — Transparency/blend evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO SORT OR OIT`. **Base:** `3d52a3e`. **Gate:** [NLE-PRPLAN-GFX-08-06-G6-ACTIVATION](NLE-PRPLAN-GFX-08-06-G6-ACTIVATION.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-08-06](../work-orders/NLE-PRPLAN-GFX-08-06.md). **PR:** #781.

## Scope delivered

- `src/stormline/graphics/vfx/blend_plan.hpp`: descriptor/plan and `plan_blend`.
- `tests/core/gfx08_blend_tests.cpp`: BLD-01.
- Additive CMake test and TSan target.
- No sort, OIT, blend execution, pixel, GPU, shader, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Material ID/revision must be nonzero; blend/depth enums must be declared.
- Opaque/Mask require depth write and reject premultiplied alpha, sorting or OIT.
- Blend requires no depth write; sort and OIT are metadata flags only.
- Additive requires no depth write, rejects sorting and OIT.
- No pixel is blended or sorted; OIT remains explicitly approximate and unexecuted.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx08_blend_tests.cpp -o /tmp/gfx08_blend
/tmp/gfx08_blend bld01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/gfx08_blend_tests.cpp -o /tmp/gfx08_blend_san
/tmp/gfx08_blend_san bld01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/gfx08_blend_tests.cpp -o /tmp/gfx08_blend_tsan
setarch "$(uname -m)" -R /tmp/gfx08_blend_tsan bld01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no composite or visual result is claimed.

## Rollback

Revert normally; remove the blend header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No sort, OIT, GPU/compute, rendering, hardware, performance, ABI or release.
- `GFX-08-07`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-08-06` as `COMPLETED`, manifest `GFX08_06_COMPLETED_REST_BLOCKED`: **561 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 149 `COMPLETED`, 38 approved gates**.
