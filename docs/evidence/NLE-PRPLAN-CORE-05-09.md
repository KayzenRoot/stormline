# NLE-PRPLAN-CORE-05-09 — integrated qualification evidence

**Status:** `INTERNAL QUALIFICATION / NO HARDWARE, ABI OR RELEASE CLAIM`. **Base:** `01e033922fb23b535d90628b8d99030a8462f46b`. **Gate:** [NLE-PRPLAN-CORE-05-09-G6-ACTIVATION](NLE-PRPLAN-CORE-05-09-G6-ACTIVATION.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-09](../work-orders/NLE-PRPLAN-CORE-05-09.md).

## Scope delivered

- `tests/core/core05_qualification_tests.cpp`: QLF-01 integrated vector/quaternion/matrix/coords/units/precision/ID workflow; QLF-02 1,000 repeated scalar fixtures; QLF-03 typed-error recovery; QLF-04 10^9 m coordinate/rebase fixture.
- Additive `CMakeLists.txt` target/CTest entries and workflow TSan target list.
- No production source, dependency, public ABI, serialization, SIMD or release change.

## Qualification matrix

- **QLF-01:** normalized vector, quaternion rotation, matrix/coordinate transform, 100 cm→1 m, 1 s→1000 ms, f64/f32 precision conversion, epoch rebase and 128-bit ID round-trip.
- **QLF-02:** 1,000 identical iterations produce bit-identical scalar rotation output; no mutable global state.
- **QLF-03:** zero-length, singular matrix, epoch mismatch, invalid ID and unnormalized quaternion return typed errors, followed by successful valid operations.
- **QLF-04:** 10^9 m origin with 123.5 m delta stays within `local_error_bound`; rebase preserves global exactly and stale epoch is rejected; large double transform is exact.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/core05_qualification_tests.cpp -o /tmp/core05_qualification_test
/tmp/core05_qualification_test qlf01
/tmp/core05_qualification_test qlf02
/tmp/core05_qualification_test qlf03
/tmp/core05_qualification_test qlf04
```

All four modes exited 0. The same source rebuilt with `-fsanitize=address,undefined -fno-omit-frame-pointer`; all four modes exited 0.

Native CI is executed by the PR workflow; no result is claimed here before the exact-head run. No hardware, soak, SIMD, performance, serialization or ABI qualification is claimed.

## Errors and corrections

- Initial QLF-03 declared the unnormalized-rotation result as `MathResult<Quatf>`; `rotate` returns `MathResult<Vec3f>`. Corrected the local type; production code unchanged.

## Security and architecture

- Test-only translation unit over all CORE-05 headers; no production API, exception, dynamic allocation, platform API, file I/O or dependency.
- CORE-05 owns math values; CORE-01/02/03/04 and GFX/SIM/DATA/WORLD/NET boundaries unchanged.
- No secret, paid service, network or mutable global state.

## Rollback

Revert this PR normally; remove the qualification test and additive CMake/workflow entries. No force push or history rewrite.

## Not qualified / open risks

- No physical Windows/Linux/macOS hardware matrix beyond CI runners, no soak, suspend/resume, SIMD, cross-compiler bit identity, ABI, serialization, physics/netcode integration or release.
- The qualification is internal and bounded; it does not declare CORE-05 or CORE-01 module-qualified.
- `CORE-05-10` remains the closeout packet and must record the module as not fully qualified.
- CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `CORE-05-09` as `COMPLETED`, manifest `CORE05_09_COMPLETED_REST_BLOCKED`: **693 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 45 `COMPLETED`, 10 approved gates**, and keep `CORE-05-10` blocked. This is a proposal, not a self-promoted checkpoint.
