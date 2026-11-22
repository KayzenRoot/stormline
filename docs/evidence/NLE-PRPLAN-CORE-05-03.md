# NLE-PRPLAN-CORE-05-03 — scalar/error/vector evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ABI OR RELEASE CLAIM`. **Base:** `b3ff90ac961bd86cadd91afebb62e95169c7967c`. **Implementation head:** `d75bc45`. **Gate:** [NLE-PRPLAN-CORE-05-03-G6-ACTIVATION](NLE-PRPLAN-CORE-05-03-G6-ACTIVATION.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-03](../work-orders/NLE-PRPLAN-CORE-05-03.md).

## Scope delivered

- `src/stormline/core/math/math_types.hpp`: `f32`/`f64`, `kPi`/degree constants, `kMathSchemaVersion`, `MathError`, `MathResult<T>`, `Vec2/3/4` and aliases.
- `src/stormline/core/math/vec.hpp`: component add/subtract/scale, dot, 3D cross, length squared/length, normalize, finite and approximation for `Vec2/3/4`.
- `tests/core/core05_vector_tests.cpp`: MATH-01, MATH-02 and typed `MathResult`/error fixtures.
- Additive `CMakeLists.txt` INTERFACE target `stormline_core05_math`, `stormline_core05_vector_test` and CTest entries.
- Additive workflow path filter and TSan build/test inclusion for `core05_`.

No matrix, quaternion, coordinate-space, unit, precision/origin, ID, SIMD, third-party, serialization, ABI or release change.

## Implementation notes

- The scalar reference path is the only implementation; no intrinsic, fast-math, FMA or third-party include.
- `length` uses `std::hypot` to avoid avoidable intermediate overflow; `length_squared` is the direct dot product and may overflow by contract.
- `normalized` returns `ZeroLength`, `NonFinite` or `Overflow` without propagating NaN/infinity; `MathResult` defaults to success with a zero value.
- `finite_value` is a local constexpr predicate so `finite` remains constexpr in C++20; `approx_equal` rejects negative/non-finite tolerances and non-finite operands.
- MATH-02 checks right-handed `cross(+X,+Y)=+Z`, `cross(+Y,-Z)=-X`, `cross(+X,-Z)=+Y`, orthogonality and `+Y` up / `-Z` forward fixtures.

## Commands and results

Executed locally on WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/core05_vector_tests.cpp -o /tmp/core05_vector_test
/tmp/core05_vector_test math01
/tmp/core05_vector_test math02
/tmp/core05_vector_test errors
```

All three modes exited 0. The same source was rebuilt with
`-fsanitize=address,undefined -fno-omit-frame-pointer`; all three modes exited 0.

CMake/native CI on head `d75bc45`:
[run 45015876063](https://github.com/KayzenRoot/stormline/actions/runs/45015876063)
SUCCESS — Linux **150/150**, Linux ASan/UBSan **150/150**, TSan
**40/40**, Windows **151/151**, macOS **149/149**; allocator benchmark
1/1 per target. Docs Validation
[45015876133](https://github.com/KayzenRoot/stormline/actions/runs/45015876133)
SUCCESS; SonarCloud and Socket SUCCESS. No benchmark, hardware, SIMD or
performance result exists.

## Errors and corrections

- Initial MATH-02 draft expected `cross(-Z,+X)=+Y`; the right-handed result is `-Y`. Replaced with `cross(+X,-Z)=+Y` and kept the `+Y` up / `-Z` forward invariants.
- No production API correction was needed after local compile/test.

## Security and architecture

- Header-only internal C++20; no exceptions cross the API, no dynamic allocation, no platform API and no dependency.
- CORE-05 owns the math values; CORE-01/02/03/04 and GFX/SIM/DATA/WORLD/NET boundaries are unchanged.
- No secret, paid service, network, file I/O or mutable global state.

## Rollback

Revert this PR normally; delete `src/stormline/core/math/math_types.hpp`, `vec.hpp`, the vector test, and the additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No cross-compiler bit identity, SIMD path, GPU storage layout, ABI, serialization or physics/netcode determinism.
- `length_squared` overflow is documented; callers needing checked magnitude use `length`.
- MATH-03..MATH-12 remain future packets; `CORE-05-04`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `CORE-05-03` as `COMPLETED`, manifest `CORE05_03_COMPLETED_REST_BLOCKED`: **699 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 39 `COMPLETED`, 10 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.

## Completion (2026-11-22)

- Code PR [#539](https://github.com/KayzenRoot/stormline/pull/539) squash-merged as `11486b2df91e71c287139d632d5829c4a89a287b`.
- Final implementation head `f47acef9cfbd339d721cf8cf269bbc0260687877`; exact-head native run [45016159363](https://github.com/KayzenRoot/stormline/actions/runs/45016159363) SUCCESS: Linux 150/150, ASan/UBSan 150/150, TSan 40/40, Windows 151/151, macOS 149/149.
- pt-BR audit [APPROVED](https://github.com/KayzenRoot/stormline/pull/539#issuecomment-7078320932).
- Manifest after closeout: `CORE05_03_COMPLETED_REST_BLOCKED` — 699 blocked, 0 ready, 39 completed, 10 approved gates. `CORE-05-04` remains `PLANNED_BLOCKED`.
- This completion does not claim CORE-05 module completion, ABI, release, SIMD, hardware qualification or broad numerical determinism.
