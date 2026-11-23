# NLE-PRPLAN-GFX-04-08 — geometry budget evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO MESH OPTIMIZATION, CODEC OR GPU`. **Base:** `d144d7b`. **Gate:** [NLE-PRPLAN-GFX-04-08-G6-ACTIVATION](NLE-PRPLAN-GFX-04-08-G6-ACTIVATION.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-04-08](../work-orders/NLE-PRPLAN-GFX-04-08.md).

## Scope delivered

- `src/stormline/graphics/geometry/geometry_budget.hpp`: `validate_geometry_budget`.
- `tests/core/gfx04_budget_tests.cpp`: GEO-01.
- Additive CMake/workflow entries.

No qualification/closeout, native mesh optimization/library, codec, GPU, submission, dependency, ABI or release.

## Implementation notes

- Metric sets require unique nonzero mesh IDs and positive vertex/triangle/byte counts.
- Totals use checked 64-bit additions; overflow fails closed.
- Budget maxima must be nonzero; overcommit returns `GeometryBudgetExceeded` with populated totals and `within_budget=false`.
- Exact-boundary values are accepted.
- No mesh is modified, simplified or decoded.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx04_budget_tests.cpp -o /tmp/gfx04_bud
/tmp/gfx04_bud geo01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- No implementation defect after the first compile.

## Security and architecture

- Header-only internal C++20; no GPU, codec, file or network.
- Budget is logical/estimated; no allocation or reduction is claimed.

## Rollback

Revert normally; remove the budget header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No mesh optimization, simplification, quantization, codec or GPU resource allocation.
- `GFX-04-09`/`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-04-08` as `COMPLETED`, manifest `GFX04_08_COMPLETED_REST_BLOCKED`: **599 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 119 `COMPLETED`, 30 approved gates**.
