# NLE-PRPLAN-SIM-03-07 — Integrated character motor metadata qualification evidence

**Status:** `QUALIFICATION EVIDENCE / INTERNAL_ONLY / NO CHARACTER RUNTIME`. **Base:** `4ad2ccf0`. **Gate:** [NLE-PRPLAN-SIM-03-07-G6-ACTIVATION](NLE-PRPLAN-SIM-03-07-G6-ACTIVATION.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-03-07](../work-orders/NLE-PRPLAN-SIM-03-07.md). **PR:** #971.

## Scope delivered

- `tests/core/sim03_qualification_tests.cpp` with QLF-S301..S304.
- Additive CMake target/tests and TSan target.
- No production header change, motor, sweeper, contact, input device, camera update, ECS mutation, GPU, character runtime, ABI or release claim.

## Oracle results

- QLF-S301: chained controller → locomotion → input → camera; counts 2/2/3/2 with expected sub-counts.
- QLF-S302: 100 identical repeated plans with identical counts.
- QLF-S303: typed duplicate-ID failure followed by a valid plan for each of the four planners, with reset confirmed.
- QLF-S304: 10,000 bounded attempts at capacity 32/32/64/16 with caps held.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/sim03_qualification_tests.cpp` — PASS.
- ASan/UBSan build and all four modes — PASS.
- TSan build under `setarch $(uname -m) -R` and modes `qlfs301`/`qlfs304` — PASS.

## Errors and corrections

- None; qualification exercises the frozen planners unchanged.

## Security and architecture

- Internal header-only planners exercised only; no allocation, exception, file, network, audio, GPU, clock, thread, random source or global state.
- Qualification adds no movement, contact or runtime behavior.

## Rollback

Revert normally; remove the test, additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No motor, sweeper, contacts, solver/backend, input devices, camera update, ECS mutation, GPU, character runtime, performance, ABI or release.
- `SIM-03-08` remains blocked until its gate.
- SIM-01/SIM-02 not module-qualified; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `SIM-03-07` as `COMPLETED`, manifest `SIM03_07_COMPLETED_REST_BLOCKED`: **448 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 238 `COMPLETED`, 62 approved gates**. Checkpoint promotion remains owner-only.
