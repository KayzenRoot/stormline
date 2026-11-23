# NLE-PRPLAN-GFX-03-08 — logical render graph qualification evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU OR HARDWARE QUALIFICATION`. **Base:** `8297fc9`. **Gate:** [NLE-PRPLAN-GFX-03-08-G6-ACTIVATION](NLE-PRPLAN-GFX-03-08-G6-ACTIVATION.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-03-08](../work-orders/NLE-PRPLAN-GFX-03-08.md).

## Scope delivered

- `tests/core/gfx03_graph_qualification_tests.cpp`: QLF-G301..G304.
- Additive CMake target/tests and workflow TSan target.

No closeout, native GPU, allocator, submission, rendering, performance, ABI or release.

## Qualification notes

- QLF-G301 integrates definitions, dependency order/edges, sync transitions, transient lifetimes/aliases and budget admission.
- QLF-G302 repeats the integrated pipeline and compares order/edge/transition/lifetime/group/required fields.
- QLF-G303 exercises invalid graph, ambiguous writer, uninitialized read, cycle, invalid dependency orders and budget unknown/overcommit, each followed by a valid operation.
- QLF-G304 performs 10,000 integrated pipelines and 10,000 invalid rejects with bounded capacities.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx03_graph_qualification_tests.cpp -o /tmp/gfx03_qual
/tmp/gfx03_qual qlf01
/tmp/gfx03_qual qlf02
/tmp/gfx03_qual qlf03
/tmp/gfx03_qual qlf04
```

All exited 0. ASan/UBSan rebuild exited 0 for all four modes. TSan rebuild ran with `setarch -R` and exited 0 for all four modes.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- The initial test file omitted the sync header; include corrected before the passing run.

## Security and architecture

- Test-only C++20; no GPU, allocator, driver, submission, file or network.
- Qualification is logical and CI-only; no hardware, driver, visual or performance behavior is asserted.

## Rollback

Revert normally; remove the qualification test and additive CMake/workflow entries.

## Open risks / not claimed

- No native GPU, allocator, submission, barrier/fence execution, rendering or hardware.
- No performance, residency, eviction, ABI or release.
- `GFX-03-09` closeout remains blocked until its gate.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-03-08` as `COMPLETED`, manifest `GFX03_08_COMPLETED_REST_BLOCKED`: **608 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 112 `COMPLETED`, 28 approved gates**.
