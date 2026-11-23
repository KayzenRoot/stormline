# NLE-PRPLAN-GFX-03-06 — transient lifetime and alias evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE HEAP OR ALLOCATOR`. **Base:** `b925b14`. **Gate:** [NLE-PRPLAN-GFX-03-06-G6-ACTIVATION](NLE-PRPLAN-GFX-03-06-G6-ACTIVATION.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-03-06](../work-orders/NLE-PRPLAN-GFX-03-06.md).

## Scope delivered

- `src/stormline/graphics/render_graph/graph_transient.hpp`: lifetime and conservative alias planning.
- `tests/core/gfx03_transient_tests.cpp`: TRA-01.
- Additive CMake/workflow entries.

No VRAM budget, qualification, native heap/allocator, GPU, submission, dependency, ABI or release.

## Implementation notes

- Lifetimes use first/last topological positions for used transient resources only.
- Lifetimes are sorted by first position then resource ID.
- Alias groups require equal bytes/alignment and the new lifetime starts after every existing member's last position.
- Persistent, history and external resources never alias; unused transients are skipped.
- Alias savings are `(members - 1) * bytes` with checked addition.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx03_transient_tests.cpp -o /tmp/gfx03_tra
/tmp/gfx03_tra tra01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- The initial grouping check compared a new lifetime only against the group's first member, which could alias overlapping later members. The grouping now checks the maximum last position of every group member before accepting an alias.

## Security and architecture

- Header-only internal C++20; no GPU, heap, allocator, driver, submission, file or network.
- Alias plans are logical estimates; no allocation or VRAM savings is claimed.

## Rollback

Revert normally; remove the transient header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No native heap, aliasing execution, fence safety or VRAM budget.
- `GFX-03-07`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-03-06` as `COMPLETED`, manifest `GFX03_06_COMPLETED_REST_BLOCKED`: **610 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 110 `COMPLETED`, 28 approved gates**.
