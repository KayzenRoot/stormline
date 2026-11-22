# NLE-PRPLAN-CORE-05-04 — matrix/quaternion evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ABI OR RELEASE CLAIM`. **Base:** `076d6444c195a911d2625010e4ea8a1460cedc9c`. **Implementation head:** `560e028`. **Gate:** [NLE-PRPLAN-CORE-05-04-G6-ACTIVATION](NLE-PRPLAN-CORE-05-04-G6-ACTIVATION.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-04](../work-orders/NLE-PRPLAN-CORE-05-04.md).

## Scope delivered

- `src/stormline/core/math/mat.hpp`: `Mat3<T>`/`Mat4<T>` with column-major `elements[column * N + row]`, identity, multiply, transpose, translation, scaling, right-handed X/Y/Z rotations, `transform_point`/`transform_direction`, determinant and inverse.
- `src/stormline/core/math/quat.hpp`: `Quat<T>`, identity, axis-angle, normalization, Hamilton product, conjugate, dot, canonicalization and rotate.
- `tests/core/core05_matrix_quat_tests.cpp`: MATH-03, MATH-04 and MATH-05.
- Additive `CMakeLists.txt` target/CTest entries and workflow TSan target list.

No coordinate-space wrappers, units, precision/origin, IDs, SIMD, third-party math, serialization, backend clip/projection, ABI or release change.

## Implementation notes

- Matrix storage is column-major; `multiply(lhs, rhs)` computes algebraic `lhs * rhs`; `transform_point` uses `w=1`, divides by a valid non-unit `w`, and rejects zero/non-finite `w` with `SingularMatrix`.
- Determinant and inverse reject non-finite input; inverse rejects `|det| <= epsilon * scale^N` with `SingularMatrix` and non-finite results with `Overflow`.
- Quaternion axes are normalized; `rotate` requires a normalized quaternion within `8 * epsilon` and returns `InvalidQuaternion` otherwise; `canonicalized` makes `q` and `-q` identical.
- No clip-space convention, GPU layout, SIMD or cross-compiler bit-identity is claimed.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/core05_matrix_quat_tests.cpp -o /tmp/core05_matrix_quat_test
/tmp/core05_matrix_quat_test math03
/tmp/core05_matrix_quat_test math04
/tmp/core05_matrix_quat_test math05
```

All three modes exited 0. The same source rebuilt with
`-fsanitize=address,undefined -fno-omit-frame-pointer`; all three modes exited 0.

Native CI on implementation head `560e028`:
[run 45017038311](https://github.com/KayzenRoot/stormline/actions/runs/45017038311)
SUCCESS — Linux **153/153**, Linux ASan/UBSan **153/153**, TSan
**43/43**, Windows **154/154**, macOS **152/152**; allocator benchmark
1/1 per target. Docs Validation
[45017038312](https://github.com/KayzenRoot/stormline/actions/runs/45017038312)
SUCCESS; SonarCloud and Socket SUCCESS. No benchmark, hardware, SIMD or
performance result exists.

## Errors and corrections

- Initial MATH-05 fixture named `negative_x` used `{0,-1,0,0}` (negative Y); corrected to `{-1,0,0,0}` to exercise X tie-breaking. Production code was unchanged.
- No other correction was needed after local compile/test.

## Security and architecture

- Header-only internal C++20; no exception across the API, dynamic allocation, platform API, file I/O or dependency.
- CORE-05 owns the math values; CORE-01/02/03/04, GFX clip/projection, SIM solver precision, DATA serialization, WORLD origin and NET replication remain their owners.
- No secret, paid service, network or mutable global state.

## Rollback

Revert this PR normally; remove `mat.hpp`, `quat.hpp`, the matrix/quaternion test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No backend clip/projection/winding, GPU storage layout, SIMD, ABI, serialization or physics/netcode determinism.
- Near-singular threshold is scale-aware but not a universal epsilon guarantee.
- MATH-06..MATH-12 remain future packets; `CORE-05-05`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `CORE-05-04` as `COMPLETED`, manifest `CORE05_04_COMPLETED_REST_BLOCKED`: **698 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 40 `COMPLETED`, 10 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.
