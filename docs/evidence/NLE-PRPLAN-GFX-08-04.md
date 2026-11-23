# NLE-PRPLAN-GFX-08-04 — Ribbon budget evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO TESSELLATION`. **Base:** `9d04720`. **Gate:** [NLE-PRPLAN-GFX-08-04-G6-ACTIVATION](NLE-PRPLAN-GFX-08-04-G6-ACTIVATION.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-08-04](../work-orders/NLE-PRPLAN-GFX-08-04.md). **PR:** #777.

## Scope delivered

- `src/stormline/graphics/vfx/ribbon_plan.hpp`: descriptor/plan and `plan_ribbon`.
- `tests/core/gfx08_ribbon_tests.cpp`: RIB-01.
- Additive CMake test and TSan target.
- No tessellation, spline, vertex/strip buffer, GPU, shader, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Source/revision must be nonzero; sample count is bounded to `2..16`.
- Width and minimum sample distance must be finite positive.
- Segment/vertex caps must be nonzero; segments are `sample_count-1`, vertices are `2*sample_count`.
- Exceeding declared caps returns `BudgetExceeded`; malformed geometry returns `GeometryInvalid`.
- No vertex is produced or drawn.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx08_ribbon_tests.cpp -o /tmp/gfx08_ribbon
/tmp/gfx08_ribbon rib01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/gfx08_ribbon_tests.cpp -o /tmp/gfx08_ribbon_san
/tmp/gfx08_ribbon_san rib01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/gfx08_ribbon_tests.cpp -o /tmp/gfx08_ribbon_tsan
setarch "$(uname -m)" -R /tmp/gfx08_ribbon_tsan rib01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- First strict compile failed because `ribbon_plan.hpp` included only `vfx_types.hpp` while `detail::set_vfx_error` lives in `graph_plan.hpp`; corrected the include before any commit.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no geometry or visual result is claimed.

## Rollback

Revert normally; remove the ribbon header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No tessellation, GPU/compute, rendering, hardware, performance, ABI or release.
- `GFX-08-05`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-08-04` as `COMPLETED`, manifest `GFX08_04_COMPLETED_REST_BLOCKED`: **563 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 147 `COMPLETED`, 38 approved gates**.
