# NLE-PRPLAN-CORE-05-08 — stable IDs evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ABI OR RELEASE CLAIM`. **Base:** `e693e09a74c40c2a8078d4606668f02109cb8a3a`. **Gate:** [NLE-PRPLAN-CORE-05-08-G6-ACTIVATION](NLE-PRPLAN-CORE-05-08-G6-ACTIVATION.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-08](../work-orders/NLE-PRPLAN-CORE-05-08.md).

## Scope delivered

- `src/stormline/core/math/ids.hpp`: `PersistentId` 128-bit opaco, `RuntimeHandle`, `IdBytes`, validade, geração atual, encode/decode big-endian.
- `tests/core/core05_id_tests.cpp`: MATH-10/MATH-11, zero-ID, byte fixture, geração e reciclagem.
- Additive `CMakeLists.txt` target/CTest entries and workflow TSan target list.

No ECS, asset pipeline, persistence, serialization format, SIMD, third-party math, ABI or release change.

## Implementation notes

- `PersistentId{0,0}` invalid; equality is value equality, not address identity.
- `RuntimeHandle.index == 0` or `generation == 0` invalid; `handle_is_current` rejects invalid and mismatched generations.
- `encode_persistent_id` writes `high` then `low` as 16 big-endian bytes; `decode_persistent_id` rejects all-zero bytes with `InvalidId`.
- Slot recycling with a new generation cannot validate the old handle. No pointer/index-as-persistent-identity exists.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/core05_id_tests.cpp -o /tmp/core05_id_test
/tmp/core05_id_test math10
/tmp/core05_id_test math11
```

Both modes exited 0. The same source rebuilt with `-fsanitize=address,undefined -fno-omit-frame-pointer`; both modes exited 0.

Native CI is executed by the PR workflow; no result is claimed here before the exact-head run. No benchmark, hardware, SIMD or performance result exists.

## Errors and corrections

No production or test correction was needed after local compile/test.

## Security and architecture

- Header-only internal C++20; no exception across the API, dynamic allocation, platform API, file I/O or dependency.
- CORE-05 owns ID value contracts; WORLD owns ECS lifecycle, DATA owns persistence and NET owns replication.
- No secret, paid service, network or mutable global state.

## Rollback

Revert this PR normally; remove `ids.hpp`, the ID test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No ECS, persistence, serialization, replication, collision generation, SIMD, ABI or release.
- ID generation/collision policy and storage format remain DATA/WORLD responsibilities.
- MATH-12 remains the qualification/quality packet; `CORE-05-09`/`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `CORE-05-08` as `COMPLETED`, manifest `CORE05_08_COMPLETED_REST_BLOCKED`: **694 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 44 `COMPLETED`, 10 approved gates**, and keep `CORE-05-09`/`-10` blocked. This is a proposal, not a self-promoted checkpoint.
