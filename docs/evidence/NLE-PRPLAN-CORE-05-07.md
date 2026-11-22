# NLE-PRPLAN-CORE-05-07 — precision/origin evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ABI OR RELEASE CLAIM`. **Base:** `7a4728dd0b249f94434fd3e780d47cb8a1461488`. **Implementation head:** `89a3255`. **Gate:** [NLE-PRPLAN-CORE-05-07-G6-ACTIVATION](NLE-PRPLAN-CORE-05-07-G6-ACTIVATION.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-07](../work-orders/NLE-PRPLAN-CORE-05-07.md).

## Scope delivered

- `src/stormline/core/math/precision.hpp`: `OriginEpoch`, `WorldPosition` f64, `LocalPosition` f32, `Origin`, `to_local`, `to_world`, `rebase` and `local_error_bound`.
- `tests/core/core05_precision_tests.cpp`: MATH-08/MATH-09, epoch mismatch, f32 range overflow, non-finite and exact global preservation.
- Additive `CMakeLists.txt` target/CTest entries and workflow TSan target list.

No stable IDs, serialization, backend conversion, SIMD, third-party math, ABI or release change.

## Implementation notes

- Global position is `f64` truth; local payload is `f32` relative to a matching `OriginEpoch`.
- `to_local` subtracts in `f64`, rejects epoch mismatch with `InvalidOriginEpoch`, rejects `f32` range overflow, and returns the rounded local payload.
- `to_world` adds in `f64` and rejects non-finite results with `Overflow`.
- `rebase` preserves `global_meters` exactly, advances only the epoch, and rejects stale/non-advancing/duplicate epochs. No gameplay movement or WORLD orchestration is implemented.
- `local_error_bound` uses `2^-24 * max(1, |delta|)` as a documented budget, not a general accumulated-error guarantee.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/core05_precision_tests.cpp -o /tmp/core05_precision_test
/tmp/core05_precision_test math08
/tmp/core05_precision_test math09
```

Both modes exited 0. The same source rebuilt with `-fsanitize=address,undefined -fno-omit-frame-pointer`; both modes exited 0.

Native CI on implementation head `89a3255`: [run 45020065167](https://github.com/KayzenRoot/stormline/actions/runs/45020065167) SUCCESS — Linux **157/157**, ASan/UBSan **157/157**, TSan **47/47**, Windows **158/158**, macOS **156/156**; allocator 1/1 per target. Docs [45020065200](https://github.com/KayzenRoot/stormline/actions/runs/45020065200) SUCCESS; SonarCloud and Socket SUCCESS. No benchmark, hardware, SIMD or performance result exists.

## Errors and corrections

- Initial test attempted an f64 `to_world` overflow by adding an `f32` maximum to a `f64` maximum; this cannot overflow and also caused a narrowing initializer. Removed that invalid fixture; `Overflow` remains covered by the f32 `to_local` range fixture and `NonFinite` by input checks.

## Security and architecture

- Header-only internal C++20; no exception across the API, dynamic allocation, platform API, file I/O or dependency.
- CORE-05 supplies pure checked conversion; WORLD owns origin-shift orchestration at the CORE-04/CORE-03 barrier; SIM/GFX/NET/DATA boundaries unchanged.
- No secret, paid service, network or mutable global state.

## Rollback

Revert this PR normally; remove `precision.hpp`, the precision test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No serialization, stable IDs, origin orchestration, network replication, SIMD, ABI or bit-exact numerical determinism.
- No hardware, benchmark or cross-compiler numerical qualification.
- MATH-10..MATH-12 remain future packets; `CORE-05-08`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `CORE-05-07` as `COMPLETED`, manifest `CORE05_07_COMPLETED_REST_BLOCKED`: **695 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 43 `COMPLETED`, 10 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.
