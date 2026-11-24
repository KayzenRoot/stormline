# NLE-PRPLAN-SIM-02-07 — Constraint metadata 3D evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO CONSTRAINT SOLVER`. **Base:** `823defb9`. **Gate:** [NLE-PRPLAN-SIM-02-07-G6-ACTIVATION](NLE-PRPLAN-SIM-02-07-G6-ACTIVATION.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-02-07](../work-orders/NLE-PRPLAN-SIM-02-07.md). **PR:** pendente.

## Scope delivered

- `src/stormline/physics3d/constraint_plan.hpp`: `ConstraintDesc`, `ConstraintSetDesc`, `ConstraintPlan`, `axis_required`, `plan_constraints`.
- `tests/core/sim02_constraint_tests.cpp`: CONSTRAINT3-01.
- Additive CMake target/test and TSan target.
- No constraint solver, joint runtime, contacts, simulation, ECS mutation, GPU, physics runtime, ABI or release claim.

## Implementation notes

- IDs/revision nonzero; kind allowlist; distinct nonzero body references; finite anchors/limits/break; `min_limit <= max_limit`; `break_impulse >= 0`.
- Hinge/Slider/ConeTwist require a unit axis; other kinds do not.
- Plan counts kinds plus motor/collide flags; reset and typed diagnostic on failure.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict `-Werror`, ASan/UBSan and TSan builds with `constraint301` — PASS.

## Errors and corrections

- None; implementation follows the frozen contract exactly.

## Security and architecture

- Header-only internal C++20; no allocation, exception, I/O, GPU, clock, thread, random source or global state. No solver state or runtime joint.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No constraint solver, joint runtime, contacts, simulation, ECS mutation, GPU, physics runtime, performance, ABI or release.
- `SIM-02-08`..`-10` remain blocked until their gates.

## Proposed checkpoint delta

After merge, record `SIM-02-07` as `COMPLETED`, manifest `SIM02_07_COMPLETED_REST_BLOCKED`: **458 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 230 `COMPLETED`, 60 approved gates**. Checkpoint promotion remains owner-only.
