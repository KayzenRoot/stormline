# NLE-PRPLAN-CORE-05-05 — coordinate-space evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ABI OR RELEASE CLAIM`. **Base:** `8367761d87c3f8147c649ef53b5247ff9f3f68cd`. **Implementation head:** `7b9b4cc`. **Gate:** [NLE-PRPLAN-CORE-05-05-G6-ACTIVATION](NLE-PRPLAN-CORE-05-05-G6-ACTIVATION.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-05](../work-orders/NLE-PRPLAN-CORE-05-05.md).

## Scope delivered

- `src/stormline/core/math/coords.hpp`: `WorldSpace`, `LocalSpace`, `ViewSpace`, `ClipSpace`, `PixelSpace`, `Position3<T,Space>`, `Direction3<T,Space>`, `Transform3<T,From,To>`, identity, compose, position/direction transform and inverse.
- `tests/core/core05_coord_tests.cpp`: MATH-06 plus compile-time mismatch fixtures.
- Additive `CMakeLists.txt` target/CTest entry and workflow TSan target list.

No units, precision/origin, IDs, backend clip/projection, SIMD, third-party math, serialization, ABI or release change.

## Implementation notes

- `compose(parent, child)` requires `parent: B->C`, `child: A->B`, and returns `A->C` with `parent.matrix * child.matrix`.
- `transform_position` propagates matrix errors; `transform_direction` ignores translation and preserves the named target space.
- `inverse` reverses the space tags and propagates singular/non-finite errors.
- Cross-space `Position3`/`Direction3`/`Transform3` assignment is rejected at compile time; no world/view/clip/pixel adapter or backend projection exists in this slice.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/core05_coord_tests.cpp -o /tmp/core05_coord_test
/tmp/core05_coord_test math06
```

Exited 0. The same source rebuilt with
`-fsanitize=address,undefined -fno-omit-frame-pointer`; exited 0.

Native CI on implementation head `7b9b4cc`: [run 45018105762](https://github.com/KayzenRoot/stormline/actions/runs/45018105762) SUCCESS — Linux **154/154**, ASan/UBSan **154/154**, TSan **44/44**, Windows **155/155**, macOS **153/153**; allocator 1/1 per target. Docs [45018105715](https://github.com/KayzenRoot/stormline/actions/runs/45018105715) SUCCESS; SonarCloud and Socket SUCCESS. No benchmark, hardware, SIMD or performance result exists.

## Errors and corrections

No production or test correction was needed after local compile/test.

## Security and architecture

- Header-only internal C++20; no exception across the API, dynamic allocation, platform API, file I/O or dependency.
- CORE-05 owns coordinate-space wrappers; GFX owns backend clip/projection and winding; SIM/PHYS/WORLD/NET/DATA boundaries unchanged.
- No secret, paid service, network or mutable global state.

## Rollback

Revert this PR normally; remove `coords.hpp`, the coordinate test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No backend clip/projection, winding, world/view/pixel conversion, GPU layout, SIMD, ABI or serialization.
- No origin rebase, unit conversion or stable-ID behavior in this slice.
- MATH-07..MATH-12 remain future packets; `CORE-05-06`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `CORE-05-05` as `COMPLETED`, manifest `CORE05_05_COMPLETED_REST_BLOCKED`: **697 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 41 `COMPLETED`, 10 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.
