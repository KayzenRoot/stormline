# NLE-PRPLAN-WORLD-05-03 — Seed/domain metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO RNG OR NOISE`. **Base:** `1b9bc6b`. **Gate:** [NLE-PRPLAN-WORLD-05-03-G6-ACTIVATION](NLE-PRPLAN-WORLD-05-03-G6-ACTIVATION.md). **Contract:** [world-05-procedural-internal-v0](../contracts/world-05-procedural-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-05-03](../work-orders/NLE-PRPLAN-WORLD-05-03.md). **PR:** pendente.

## Scope delivered

- `src/stormline/procedural/procedural_types.hpp`: aliases, capacities, errors, primitive/category enums and diagnostic.
- `src/stormline/procedural/seed_plan.hpp`: seed/domain descriptors, plan and `plan_seed_domains`.
- `tests/core/world05_seed_tests.cpp`: SEED-01.
- Additive CMake interface target/test and TSan target.
- No RNG, noise, graph evaluator, asset I/O, cook/cache, GPU, physics, networking, editor, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Project and graph IDs must be nonzero; seed halves must not both be zero.
- Domain count is `1..16`; domain IDs and derivation versions are nonzero and unique; duplicate domain IDs fail.
- Channel count is `1..8`; checked total channels stay `<= 128`.
- The plan echoes seed halves and domain/channel counts; it produces no random stream.
- Invalid input zeroes the plan and sets a typed diagnostic with the project ID and domain index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/world05_seed_tests.cpp` — PASS.
- ASan/UBSan build and `seed01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `seed01` — PASS.

## Errors and corrections

- None during implementation; strict compile and sanitizers passed first time.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread, random source or global state.
- Logical seed intent only; no RNG or generation execution exists.

## Rollback

Revert normally; remove the headers/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No RNG/noise, graph evaluation, asset I/O, cook/cache, GPU, physics/networking, editor, performance, ABI or release.
- `WORLD-05-04`..`-10` remain blocked until their gates.
- WORLD-04/DATA-03 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-05-03` as `COMPLETED`, manifest `WORLD05_03_COMPLETED_REST_BLOCKED`: **482 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 210 `COMPLETED`, 56 approved gates**. Checkpoint promotion remains owner-only.
