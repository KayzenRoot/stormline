# NLE-PRPLAN-WORLD-05-04 — Generator graph topology evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO GRAPH EVALUATION`. **Base:** `b804a27`. **Gate:** [NLE-PRPLAN-WORLD-05-04-G6-ACTIVATION](NLE-PRPLAN-WORLD-05-04-G6-ACTIVATION.md). **Contract:** [world-05-procedural-internal-v0](../contracts/world-05-procedural-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-05-04](../work-orders/NLE-PRPLAN-WORLD-05-04.md). **PR:** pendente.

## Scope delivered

- `src/stormline/procedural/graph_plan.hpp`: node/edge/set descriptors, plan and `plan_graph`.
- `tests/core/world05_graph_tests.cpp`: GRAPH-01.
- Additive CMake test target and TSan target.
- No graph evaluation, interpreter, RNG/noise, WFC, asset I/O, cook/cache, GPU, physics, networking, editor, ABI, release, hardware or performance claim.

## Implementation notes

- Graph ID/revision must be nonzero; node count is `1..64`; edge count is `<=128`.
- Node IDs, algorithm IDs/versions, input/output types and declared fan-out are validated; node IDs are unique.
- Edges have unique IDs and unique `(from,to)` pairs, nonzero endpoints, no self-edge and must reference existing nodes.
- Actual fan-out is `<=8`.
- Kahn topological processing detects cycles and computes DAG depth; depth greater than `16` is rejected.
- Plan reports node/edge counts, roots, leaves and maximum depth; no node is executed.
- Invalid input zeroes the plan and sets a typed diagnostic with the graph ID and index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/world05_graph_tests.cpp` — PASS.
- ASan/UBSan build and `graph01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `graph01` — PASS.

## Errors and corrections

- None during implementation; strict compile and sanitizers passed first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread, random source or global state.
- Logical topology only; no graph interpreter or artifact production exists.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No graph evaluation, interpreter, RNG/noise, WFC, asset I/O, cook/cache, GPU, physics/networking, editor, performance, ABI or release.
- `WORLD-05-05`..`-10` remain blocked until their gates.
- WORLD-04/DATA-03 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-05-04` as `COMPLETED`, manifest `WORLD05_04_COMPLETED_REST_BLOCKED`: **481 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 211 `COMPLETED`, 56 approved gates**. Checkpoint promotion remains owner-only.
