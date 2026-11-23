# NLE-PRPLAN-GFX-03-05 — logical synchronization transitions evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE BARRIER, FENCE OR SUBMISSION`. **Base:** `4768c05`. **Gate:** [NLE-PRPLAN-GFX-03-05-G6-ACTIVATION](NLE-PRPLAN-GFX-03-05-G6-ACTIVATION.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-03-05](../work-orders/NLE-PRPLAN-GFX-03-05.md).

## Scope delivered

- `src/stormline/graphics/render_graph/graph_sync.hpp`: `plan_sync`.
- `tests/core/gfx03_sync_tests.cpp`: SYN-01.
- Additive CMake/workflow entries.

No transient aliasing, budget, qualification, native barrier/fence, GPU/allocator, submission, dependency, ABI or release.

## Implementation notes

- Traverses the dependency topological order and uses declaration order.
- First use emits a `None -> mapped access` initialization transition; later access or queue changes emit transitions.
- Repeated identical uses in the same pass/queue emit no extra transition.
- Invalid, short or duplicate dependency orders return `InvalidArgument`.
- Plan is bounded to 256 transitions and reports `CapacityFull` if exceeded.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx03_sync_tests.cpp -o /tmp/gfx03_sync
/tmp/gfx03_sync syn01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- No implementation defect after the first compile.

## Security and architecture

- Header-only internal C++20; no GPU, allocator, driver, fence, submission, file or network.
- Transitions are logical metadata; they do not execute or prove GPU synchronization.

## Rollback

Revert normally; remove the sync header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No native barrier, semaphore, timeline or queue submission.
- No transient aliasing or VRAM budget yet.
- `GFX-03-06`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-03-05` as `COMPLETED`, manifest `GFX03_05_COMPLETED_REST_BLOCKED`: **611 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 109 `COMPLETED`, 28 approved gates**.
