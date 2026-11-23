# NLE-PRPLAN-GFX-03-04 — hazard dependency DAG evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU OR SUBMISSION`. **Base:** `2f9c49d`. **Gate:** [NLE-PRPLAN-GFX-03-04-G6-ACTIVATION](NLE-PRPLAN-GFX-03-04-G6-ACTIVATION.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-03-04](../work-orders/NLE-PRPLAN-GFX-03-04.md).

## Scope delivered

- `src/stormline/graphics/render_graph/graph_dependency.hpp`: writer/reader analysis, edges, cycle detection and topological order.
- `tests/core/gfx03_dependency_tests.cpp`: DEP-01.
- Additive CMake/workflow entries.

No sync transitions, transients, budget, qualification, native GPU/allocator, submission, dependency, ABI or release.

## Implementation notes

- One writer per resource; a second writer returns `AmbiguousWriter`.
- Transient reads require a writer; external/persistent/history may be pre-initialized.
- Writer-to-reader `RAW` edges are deduplicated and sorted by consumer/producer/resource.
- Kahn ordering chooses the lowest pass declaration index among ready nodes.
- A remaining node returns `Cycle` with its pass ID.
- `ReadWrite` acts as both writer and reader; self-edges are skipped.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx03_dependency_tests.cpp -o /tmp/gfx03_dep
/tmp/gfx03_dep dep01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- No implementation defect after the first compile; the namespace alias for `rhi::QueueRole` from the previous slice was sufficient.

## Security and architecture

- Header-only internal C++20; no GPU, allocator, driver, submission, file or network.
- Plans are logical; no barrier or command buffer is emitted.

## Rollback

Revert normally; remove the dependency header/test and additive CMake/workflow entries.

## Open risks / not claimed

- WAR/WAW are reserved enum values only; v0 enforces one writer and emits RAW.
- No sync transitions, transient aliasing, VRAM budget, GPU execution or rendering.
- `GFX-03-05`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-03-04` as `COMPLETED`, manifest `GFX03_04_COMPLETED_REST_BLOCKED`: **612 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 108 `COMPLETED`, 28 approved gates**.
