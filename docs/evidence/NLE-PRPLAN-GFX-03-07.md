# NLE-PRPLAN-GFX-03-07 — logical VRAM budget evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE HEAP OR ALLOCATION`. **Base:** `490ad7c`. **Gate:** [NLE-PRPLAN-GFX-03-07-G6-ACTIVATION](NLE-PRPLAN-GFX-03-07-G6-ACTIVATION.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-03-07](../work-orders/NLE-PRPLAN-GFX-03-07.md).

## Scope delivered

- `src/stormline/graphics/render_graph/graph_budget.hpp`: `plan_budget`.
- `tests/core/gfx03_budget_tests.cpp`: BUD-01.
- Additive CMake/workflow entries.

No qualification/closeout, native heap/allocator, GPU, submission, dependency, ABI or release.

## Implementation notes

- Unknown snapshot, zero total or zero headroom returns `BudgetUnknown`.
- Headroom greater than total returns `InvalidArgument`.
- Persistent and history resources are summed; external and transient resources are excluded from persistent accounting.
- Transient peak is the sum of alias-group bytes; savings are copied from the alias plan.
- Required bytes are computed with checked addition; overcommit returns `BudgetExceeded` with `within_budget=false` and populated values.
- Empty alias groups are invalid.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx03_budget_tests.cpp -o /tmp/gfx03_bud
/tmp/gfx03_bud bud01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- No implementation defect after the first compile.

## Security and architecture

- Header-only internal C++20; no GPU, heap, allocator, driver, submission, file or network.
- Budget numbers are logical estimates, not measured VRAM or allocation success.

## Rollback

Revert normally; remove the budget header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No native allocation, budget enforcement on a GPU, residency, eviction or fallback.
- `GFX-03-08`/`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-03-07` as `COMPLETED`, manifest `GFX03_07_COMPLETED_REST_BLOCKED`: **609 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 111 `COMPLETED`, 28 approved gates**.
