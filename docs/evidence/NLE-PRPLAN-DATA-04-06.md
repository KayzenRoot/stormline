# NLE-PRPLAN-DATA-04-06 — semantic diff evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO CODEC OR ABI CLAIM`. **Base:** `12192fe`. **Gate:** [NLE-PRPLAN-DATA-04-06-G6-ACTIVATION](NLE-PRPLAN-DATA-04-06-G6-ACTIVATION.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md). **WO:** [NLE-PRPLAN-DATA-04-06](../work-orders/NLE-PRPLAN-DATA-04-06.md).

## Scope delivered

- `src/stormline/data/scene/scene_diff.hpp`: `DiffKind`, `DiffEntry`, `diff`.
- `tests/core/data04_diff_tests.cpp`: DIFF-01.
- Additive CMake/workflow entries.

No qualification/closeout, codec, persistence, native I/O, network, ABI or release.

## Implementation notes

- Compares entities by stable ID; emits Added/Removed/EnabledChanged/NameChanged.
- Sorted by entity ID then kind; identical entities emit nothing.
- Buffer-full returns required count; scene ID mismatch is `InvalidArgument`.
- Bounded to 128 entries.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data04_diff_tests.cpp -o /tmp/data04_diff
/tmp/data04_diff diff01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

None introduced.

## Security and architecture

- Header-only internal C++20; fixed arrays, no allocation, codec, file, database or network.

## Rollback

Revert normally; remove diff header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No qualification yet; no JSON/CBOR/persistence/native I/O.
- `DATA-04-07`..`-08` remain `PLANNED_BLOCKED`.
- CORE-05/DATA-02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-04-06` as `COMPLETED`, manifest `DATA04_06_COMPLETED_REST_BLOCKED`: **646 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 82 `COMPLETED`, 20 approved gates**.
