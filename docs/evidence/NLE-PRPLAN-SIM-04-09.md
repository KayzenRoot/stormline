# NLE-PRPLAN-SIM-04-09 — Integrated skeletal animation qualification evidence

**Status:** `QUALIFICATION EVIDENCE / INTERNAL_ONLY / NO ANIMATION RUNTIME`. **Base:** `8353f279`. **Gate:** [NLE-PRPLAN-SIM-04-09-G6-ACTIVATION](NLE-PRPLAN-SIM-04-09-G6-ACTIVATION.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-04-09](../work-orders/NLE-PRPLAN-SIM-04-09.md). **PR:** #989.

## Scope delivered

- `tests/core/sim04_qualification_tests.cpp` with QLF-S401..S404.
- Additive CMake target/tests and TSan target.
- No production header change, pose evaluator, graph runtime, IK/ragdoll/codec/sync runtime, root motion, ECS mutation, GPU, animation runtime, ABI or release claim.

## Oracle results

- QLF-S401: chained retarget → blend → IK → ragdoll → compression → sync; counts 2/3/3/3/3/3 with expected sub-counts.
- QLF-S402: 100 identical repeated plans with identical counts.
- QLF-S403: typed duplicate-ID failure followed by a valid plan for each of the six planners, with reset confirmed.
- QLF-S404: 10,000 bounded attempts at capacity 16/64/32/16/16/32 with caps held.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/sim04_qualification_tests.cpp` — PASS.
- ASan/UBSan build and all four modes — PASS.
- TSan build under `setarch $(uname -m) -R` and modes `qlfs401`/`qlfs404` — PASS.

## Errors and corrections

- None; qualification exercises the frozen planners unchanged.

## Security and architecture

- Internal header-only planners exercised only; no allocation, exception, file, network, audio, GPU, clock, thread, random source or global state.
- Qualification adds no pose, solver, codec or runtime behavior.

## Rollback

Revert normally; remove the test, additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No pose evaluator, graph runtime, IK/ragdoll/codec/sync runtime, root motion, ECS mutation, GPU, animation runtime, performance, ABI or release.
- `SIM-04-10` remains blocked until its gate.
- SIM-03/DATA-03 not module-qualified; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `SIM-04-09` as `COMPLETED`, manifest `SIM04_09_COMPLETED_REST_BLOCKED`: **438 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 246 `COMPLETED`, 64 approved gates**. Checkpoint promotion remains owner-only.
