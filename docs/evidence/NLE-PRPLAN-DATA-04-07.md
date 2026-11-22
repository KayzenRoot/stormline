# NLE-PRPLAN-DATA-04-07 — integrated scene qualification evidence

**Status:** `INTERNAL_CI_QUALIFICATION / NOT_CODEC_OR_RELEASE_QUALIFICATION`. **Base:** `686a1b2`. **Gate:** [NLE-PRPLAN-DATA-04-07-G6-ACTIVATION](NLE-PRPLAN-DATA-04-07-G6-ACTIVATION.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md). **WO:** [NLE-PRPLAN-DATA-04-07](../work-orders/NLE-PRPLAN-DATA-04-07.md).

## Scope delivered

- `tests/core/data04_scene_qualification_tests.cpp`: QLF-S01..04.
- Additive CMake target/four tests and workflow TSan target.

No production change, codec, persistence, native I/O, ABI or release.

## Qualification results

- **QLF-S01:** init→entities→component→asset ref→patch→diff; revision and added diff verified.
- **QLF-S02:** two independent builds yield identical revision/counts/diff count.
- **QLF-S03:** invalid schema→valid, duplicate→valid, stale patch→valid, diff scene mismatch typed.
- **QLF-S04:** 10,000 entity adds stop at 64, components at 128, refs at 64; 10,000 valid patches advance revision to 10001.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data04_scene_qualification_tests.cpp -o /tmp/data04_qlf
/tmp/data04_qlf qlf01
/tmp/data04_qlf qlf02
/tmp/data04_qlf qlf03
/tmp/data04_qlf qlf04
```

All exited 0. ASan/UBSan rebuild and all four modes exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run. This is internal logical qualification only; no codec, hardware, ABI or release claim.

## Errors and corrections

None introduced.

## Security and architecture

- Test-only; frozen headers; no allocation, codec, file, database or network.

## Rollback

Revert normally; remove qualification test and additive CMake/workflow entries.

## Open risks / not claimed

- No JSON/CBOR, persistence, migration, native I/O or hardware qualification.
- `DATA-04-08` remains `PLANNED_BLOCKED`.
- CORE-05/DATA-02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-04-07` as `COMPLETED`, manifest `DATA04_07_COMPLETED_REST_BLOCKED`: **645 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 83 `COMPLETED`, 20 approved gates**.
