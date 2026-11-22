# NLE-PRPLAN-CORE-05-06 — explicit units evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ABI OR RELEASE CLAIM`. **Base:** `9398306c611c31aa851916a8ddac1678bf6621d9`. **Implementation head:** `8447c91`. **Gate:** [NLE-PRPLAN-CORE-05-06-G6-ACTIVATION](NLE-PRPLAN-CORE-05-06-G6-ACTIVATION.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-06](../work-orders/NLE-PRPLAN-CORE-05-06.md).

## Scope delivered

- `src/stormline/core/math/units.hpp`: `Meters`, `Centimeters`, `Millimeters`, `Seconds`, `Milliseconds`, `Radians`, `Degrees`, `Quantity<T,Unit>`, same-unit add/subtract/scale and explicit conversions.
- `tests/core/core05_unit_tests.cpp`: MATH-07, typed non-finite/overflow and compile-time unit separation.
- Additive `CMakeLists.txt` target/CTest entry and workflow TSan target list.

No precision/origin, IDs, backend conversion, SIMD, third-party math, serialization, ABI or release change.

## Implementation notes

- Units are distinct C++ types; cross-unit assignment/conversion is a compile-time error.
- Conversion helpers reject non-finite input/factor with `NonFinite` and non-finite results with `Overflow`; no implicit f32/f64 narrowing.
- Degrees/radians use the contract constants; centimeters/millimeters use decimal scale; seconds/milliseconds use 1000.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/core05_unit_tests.cpp -o /tmp/core05_unit_test
/tmp/core05_unit_test math07
```

Exited 0. The same source rebuilt with `-fsanitize=address,undefined -fno-omit-frame-pointer`; exited 0.

Native CI on implementation head `8447c91`: [run 45019046736](https://github.com/KayzenRoot/stormline/actions/runs/45019046736) SUCCESS — Linux **155/155**, ASan/UBSan **155/155**, TSan **45/45**, Windows **156/156**, macOS **154/154**; allocator 1/1 per target. Docs [45019046797](https://github.com/KayzenRoot/stormline/actions/runs/45019046797) SUCCESS; SonarCloud and Socket SUCCESS. No benchmark, hardware, SIMD or performance result exists.

## Errors and corrections

No production or test correction was needed after local compile/test.

## Security and architecture

- Header-only internal C++20; no exception across the API, dynamic allocation, platform API, file I/O or dependency.
- CORE-05 owns unit-bearing values; CORE-04 owns time ticks; SIM/PHYS/GFX/NET/DATA boundaries unchanged.
- No secret, paid service, network or mutable global state.

## Rollback

Revert this PR normally; remove `units.hpp`, the unit test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No precision/origin, stable IDs, backend conversion, SIMD, ABI or serialization.
- No implicit conversion or unit-aware serialization format.
- MATH-08..MATH-12 remain future packets; `CORE-05-07`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `CORE-05-06` as `COMPLETED`, manifest `CORE05_06_COMPLETED_REST_BLOCKED`: **696 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 42 `COMPLETED`, 10 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.
