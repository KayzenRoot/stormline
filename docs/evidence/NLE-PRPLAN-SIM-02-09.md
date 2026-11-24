# NLE-PRPLAN-SIM-02-09 — Integrated 3D physics metadata qualification evidence

**Status:** `QUALIFICATION EVIDENCE / INTERNAL_ONLY / NO PHYSICS RUNTIME`. **Base:** `decfde6d`. **Gate:** [NLE-PRPLAN-SIM-02-09-G6-ACTIVATION](NLE-PRPLAN-SIM-02-09-G6-ACTIVATION.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-02-09](../work-orders/NLE-PRPLAN-SIM-02-09.md). **PR:** #958.

## Scope delivered

- `tests/core/sim02_qualification_tests.cpp` with QLF-S201..S204.
- Additive CMake target/tests and TSan target.
- No production header change, solver, broadphase/query execution, contacts, simulation, ECS mutation, GPU, physics runtime, ABI or release claim.

## Oracle results

- QLF-S201: chained body → shape → layer → query → constraint → integration; counts 3/4/3/3/3/4 with one compatible layer pair and min tick 60.
- QLF-S202: 100 identical repeated plans with identical counts.
- QLF-S203: typed duplicate-ID failure followed by a valid plan for each of the six planners, with reset confirmed.
- QLF-S204: 10,000 bounded attempts at capacity 64/128/32/32/64/64 with caps held (query total 8192).

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/sim02_qualification_tests.cpp` — PASS.
- ASan/UBSan build and all four modes — PASS.
- TSan build under `setarch $(uname -m) -R` and modes `qlfs201`/`qlfs204` — PASS.

## Errors and corrections

- None; qualification exercises the frozen planners unchanged.

## Security and architecture

- Internal header-only planners exercised only; no allocation, exception, file, network, audio, GPU, clock, thread, random source or global state.
- Qualification adds no collision, broadphase or runtime behavior.

## Rollback

Revert normally; remove the test, additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No solver, broadphase/query execution, contact, simulation, ECS mutation, GPU, physics runtime, performance, ABI or release.
- `SIM-02-10` remains blocked until its gate.
- WORLD-02/CORE-03 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `SIM-02-09` as `COMPLETED`, manifest `SIM02_09_COMPLETED_REST_BLOCKED`: **456 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 232 `COMPLETED`, 60 approved gates**. Checkpoint promotion remains owner-only.
