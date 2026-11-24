# NLE-PRPLAN-SIM-01-09 — Integrated physics 2D qualification evidence

**Status:** `QUALIFICATION EVIDENCE / INTERNAL_ONLY / NO CONTACT GENERATION`. **Base:** `c1cff13c`. **Gate:** [NLE-PRPLAN-SIM-01-09-G6-ACTIVATION](NLE-PRPLAN-SIM-01-09-G6-ACTIVATION.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-01-09](../work-orders/NLE-PRPLAN-SIM-01-09.md). **PR:** pendente.

## Scope delivered

- `tests/core/sim01_qualification_tests.cpp` with QLF-S101..S104.
- Additive CMake target/tests and TSan target.
- No production header change, contact generation, broadphase, solver/backend, simulation, ECS mutation, GPU, physics runtime, ABI, release, hardware or performance claim.

## Oracle results

- QLF-S101: chained body → shape → query → joint → trigger → mask planning; counts 3/4/3/3/3/3 and one compatible mask pair.
- QLF-S102: 100 identical repeated plans with identical counts.
- QLF-S103: typed duplicate-ID failure followed by a valid plan for each of the six planners, with reset confirmed.
- QLF-S104: 10,000 bounded attempts at capacity 64/128/32/64/64/32 with caps held (query total 8192).

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/sim01_qualification_tests.cpp` — PASS.
- ASan/UBSan build and all four modes — PASS.
- TSan build under `setarch $(uname -m) -R` and modes `qlfs101`/`qlfs104` — PASS.

## Errors and corrections

- Overload trigger fixture initially had enter/exit both disabled for `index % 2 == 1 && index % 3 == 1`; corrected to always-enable enter. Strict compile and sanitizers passed after the correction.

## Security and architecture

- Internal header-only planners exercised only; no allocation, exception, file, network, audio, GPU, clock, thread, random source or global state.
- Qualification adds no collision, broadphase or runtime behavior.

## Rollback

Revert normally; remove the test, additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No contact generation, broadphase, simulation, solver/backend, ECS mutation, GPU, physics runtime, performance, ABI or release.
- `SIM-01-10` remains blocked until its gate.
- WORLD-01/TWO-01 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `SIM-01-09` as `COMPLETED`, manifest `SIM01_09_COMPLETED_REST_BLOCKED`: **466 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 224 `COMPLETED`, 58 approved gates**. Checkpoint promotion remains owner-only.
