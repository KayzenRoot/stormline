# NLE-PRPLAN-SIM-01-07 — Trigger/sensor metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO EVENT DISPATCH`. **Base:** `f42c2bd`. **Gate:** [NLE-PRPLAN-SIM-01-07-G6-ACTIVATION](NLE-PRPLAN-SIM-01-07-G6-ACTIVATION.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-01-07](../work-orders/NLE-PRPLAN-SIM-01-07.md). **PR:** pendente.

## Scope delivered

- `src/stormline/physics2d/trigger_plan.hpp`: trigger descriptors, plan and `plan_triggers`.
- `tests/core/sim01_trigger_tests.cpp`: TRG-01.
- Additive CMake test target and TSan target.
- No sensor detection, event dispatch, solver/backend, simulation, ECS mutation, GPU, physics runtime, ABI, release, hardware or performance claim.

## Implementation notes

- World ID/revision must be nonzero; trigger count is `0..64`.
- Trigger IDs are nonzero and unique; revisions nonzero; body and shape references nonzero.
- Mask bits are nonzero; at least one of enter/exit must be enabled.
- Plan reports enter, exit and both counts; no sensor event is detected or dispatched.
- Invalid input zeroes the plan and sets a typed diagnostic with the world ID and trigger index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/sim01_trigger_tests.cpp` — PASS.
- ASan/UBSan build and `trg01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `trg01` — PASS.

## Errors and corrections

- None during implementation; strict compile and sanitizers passed first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread, random source or global state.
- Logical trigger descriptors only; no event pipeline exists.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No sensor detection, event dispatch, simulation, solver/backend, ECS mutation, GPU, physics runtime, performance, ABI or release.
- `SIM-01-08`..`-10` remain blocked until their gates.
- WORLD-01/TWO-01 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `SIM-01-07` as `COMPLETED`, manifest `SIM01_07_COMPLETED_REST_BLOCKED`: **468 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 222 `COMPLETED`, 58 approved gates**. Checkpoint promotion remains owner-only.
