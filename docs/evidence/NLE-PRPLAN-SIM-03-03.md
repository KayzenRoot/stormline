# NLE-PRPLAN-SIM-03-03 — Controller profile metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO CHARACTER RUNTIME`. **Base:** `5b1a28ac`. **Gate:** [NLE-PRPLAN-SIM-03-03-G6-ACTIVATION](NLE-PRPLAN-SIM-03-03-G6-ACTIVATION.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-03-03](../work-orders/NLE-PRPLAN-SIM-03-03.md). **PR:** pendente.

## Scope delivered

- `src/stormline/character/character_types.hpp`: aliases, capacities, `CharacterError`, dimension/mode enums, diagnostic and detail helpers.
- `src/stormline/character/controller_plan.hpp`: `ControllerDesc`, `ControllerSetDesc`, `ControllerPlan`, `plan_controllers`.
- `tests/core/sim03_controller_tests.cpp`: CTRL-01.
- Additive CMake target/test and TSan target.
- No motor, sweeper, contacts, solver, input layer, camera update, ECS mutation, GPU, character runtime, ABI or release claim.

## Implementation notes

- Owner ID/revision nonzero; count `0..32`; controller IDs nonzero and unique; revisions nonzero; dimension/mode allowlists.
- 2D: half_x/half_y `> 0`, half_z `== 0`, unit up axis with `up_z == 0`. 3D: all half extents `> 0`, unit up axis.
- Max slope `0..90`; step height finite and `>= 0`; plan counts dimensions, modes and enabled controllers; reset and typed diagnostic on failure.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict `-Werror`, ASan/UBSan and TSan builds with `ctrl01` — PASS.

## Errors and corrections

- None; implementation follows the frozen contract exactly.

## Security and architecture

- Header-only internal C++20; no allocation, exception, I/O, GPU, clock, thread, random source or global state. No motor state or contact query.

## Rollback

Revert normally; remove the headers/test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No motor, sweeper, contacts, solver/backend, input devices, camera update, ECS mutation, GPU, character runtime, performance, ABI or release.
- `SIM-03-04`..`-08` remain blocked until their gates.

## Proposed checkpoint delta

After merge, record `SIM-03-03` as `COMPLETED`, manifest `SIM03_03_COMPLETED_REST_BLOCKED`: **452 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 234 `COMPLETED`, 62 approved gates**. Checkpoint promotion remains owner-only.
