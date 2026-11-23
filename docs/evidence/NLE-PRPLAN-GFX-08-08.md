# NLE-PRPLAN-GFX-08-08 — Pooling/quality evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO POOL ALLOCATION`. **Base:** `e315c8e`. **Gate:** [NLE-PRPLAN-GFX-08-08-G6-ACTIVATION](NLE-PRPLAN-GFX-08-08-G6-ACTIVATION.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-08-08](../work-orders/NLE-PRPLAN-GFX-08-08.md). **PR:** #785.

## Scope delivered

- `src/stormline/graphics/vfx/pool_plan.hpp`: descriptors/plan and `plan_pool`.
- `tests/core/gfx08_pool_tests.cpp`: POOL-01.
- Additive CMake test and TSan target.
- No pool allocation, GPU resource, compute, sort, shader, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Pool ID/capacity must be nonzero; generation must match expected generation.
- Quality-budget caps must all be nonzero.
- Total requested work is summed in 64 bits and checked against pool capacity; overflow/exhaustion returns `PoolExhausted`.
- Per-domain requests clamp to budget caps; any clamp sets `degraded=true`, with exact admitted counts and remaining capacity.
- No pool is allocated and no resource-generation state is mutated.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx08_pool_tests.cpp -o /tmp/gfx08_pool
/tmp/gfx08_pool pool01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/gfx08_pool_tests.cpp -o /tmp/gfx08_pool_san
/tmp/gfx08_pool_san pool01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/gfx08_pool_tests.cpp -o /tmp/gfx08_pool_tsan
setarch "$(uname -m)" -R /tmp/gfx08_pool_tsan pool01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no pool, resource or visual result is claimed.

## Rollback

Revert normally; remove the pool header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No pool allocation, GPU/compute, rendering, hardware, performance, ABI or release.
- `GFX-08-09`/`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-08-08` as `COMPLETED`, manifest `GFX08_08_COMPLETED_REST_BLOCKED`: **559 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 151 `COMPLETED`, 38 approved gates**.
