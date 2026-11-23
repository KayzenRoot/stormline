# NLE-PRPLAN-GFX-03-03 — graph definitions and passes evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU OR SUBMISSION`. **Base:** `1b970f6`. **Gate:** [NLE-PRPLAN-GFX-03-03-G6-ACTIVATION](NLE-PRPLAN-GFX-03-03-G6-ACTIVATION.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-03-03](../work-orders/NLE-PRPLAN-GFX-03-03.md).

## Scope delivered

- `src/stormline/graphics/render_graph/graph_types.hpp`: bounded types, enums, plans and diagnostics.
- `src/stormline/graphics/render_graph/graph_definition.hpp`: add/validate operations.
- `tests/core/gfx03_graph_tests.cpp`: DEF-01.
- Additive CMake/workflow entries.

No dependency DAG, sync, transients, budget, qualification, native GPU/allocator, submission, dependency, ABI or release.

## Implementation notes

- Passes/resources/uses are fixed arrays with nonzero unique IDs and typed enums.
- Capacity is 64 passes, 128 resources and 256 uses.
- Resource bytes are 1..2^63-1; alignment is a power of two 1..4096.
- Add operations validate before mutation and reject duplicates/capacity/enum/range errors.
- `validate_graph` rechecks raw tables and references, returning a bounded diagnostic with code/index/pass/resource.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx03_graph_tests.cpp -o /tmp/gfx03_graph
/tmp/gfx03_graph def01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- The test initially referenced `rhi::QueueRole` without a namespace alias; `graph_types.hpp` now exposes `render_graph::rhi` as an alias to the GFX-01 namespace.
- `validate_graph` distinguishes empty tables (`InvalidArgument`) from over-capacity tables (`CapacityFull`).

## Security and architecture

- Header-only internal C++20; no GPU, allocator, driver, submission, file or network.
- This is logical metadata only; no command buffer or render output exists.

## Rollback

Revert normally; remove the two headers/test and additive CMake/workflow entries.

## Open risks / not claimed

- No dependency graph, sync transitions, transient aliasing or VRAM budget yet.
- No native GPU, allocator, command submission, rendering or hardware.
- `GFX-03-04`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-03-03` as `COMPLETED`, manifest `GFX03_03_COMPLETED_REST_BLOCKED`: **613 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 107 `COMPLETED`, 28 approved gates**.
