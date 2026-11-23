# NLE-PRPLAN-GFX-08-05 — Trail budget evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO TRAIL HISTORY`. **Base:** `4afa890`. **Gate:** [NLE-PRPLAN-GFX-08-05-G6-ACTIVATION](NLE-PRPLAN-GFX-08-05-G6-ACTIVATION.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-08-05](../work-orders/NLE-PRPLAN-GFX-08-05.md). **PR:** #779.

## Scope delivered

- `src/stormline/graphics/vfx/trail_plan.hpp`: descriptor/plan and `plan_trail`.
- `tests/core/gfx08_trail_tests.cpp`: TRL-01.
- Additive CMake test and TSan target.
- No trail history, tessellation, buffer, GPU, shader, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Source/revision must be nonzero; sample count is bounded to `2..16`.
- Ages must be finite, nonnegative and strictly increasing; widths finite positive.
- Last age must not exceed `max_age_seconds`; lifetime equals the last sample age.
- Segment/vertex caps must be nonzero; exceeding them returns `BudgetExceeded`.
- No sample history, vertex or draw is produced.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx08_trail_tests.cpp -o /tmp/gfx08_trail
/tmp/gfx08_trail trl01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/gfx08_trail_tests.cpp -o /tmp/gfx08_trail_san
/tmp/gfx08_trail_san trl01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/gfx08_trail_tests.cpp -o /tmp/gfx08_trail_tsan
setarch "$(uname -m)" -R /tmp/gfx08_trail_tsan trl01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no geometry or visual result is claimed.

## Rollback

Revert normally; remove the trail header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No trail history, GPU/compute, rendering, hardware, performance, ABI or release.
- `GFX-08-06`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-08-05` as `COMPLETED`, manifest `GFX08_05_COMPLETED_REST_BLOCKED`: **562 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 148 `COMPLETED`, 38 approved gates**.
