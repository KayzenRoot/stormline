# NLE-PRPLAN-DATA-04-03 — versioned schema evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO CODEC OR ABI CLAIM`. **Base:** `0fdd79e`. **Gate:** [NLE-PRPLAN-DATA-04-03-G6-ACTIVATION](NLE-PRPLAN-DATA-04-03-G6-ACTIVATION.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md). **WO:** [NLE-PRPLAN-DATA-04-03](../work-orders/NLE-PRPLAN-DATA-04-03.md).

## Scope delivered

- `src/stormline/data/scene/scene_types.hpp`: IDs, errors, capacities, schema/entity/component records.
- `src/stormline/data/scene/scene_schema.hpp`: `validate_schema`.
- `tests/core/data04_schema_tests.cpp`: SCH-01.
- Additive CMake/workflow entries.

No document, patch, diff, codec, persistence, native I/O, network, ABI or release.

## Implementation notes

- Schema ID 1, version 1..3, capabilities subset `0x3`, canonicalization version 1.
- Unknown schema/version/capability/canonicalization return typed errors.
- No bytes are parsed or produced.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data04_schema_tests.cpp -o /tmp/data04_sch
/tmp/data04_sch sch01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

None introduced.

## Security and architecture

- Header-only internal C++20; no allocation, codec, file, database or network.

## Rollback

Revert normally; remove scene headers/test and additive CMake/workflow entries.

## Open risks / not claimed

- No document/patch/diff yet.
- No JSON/CBOR/persistence/native I/O.
- `DATA-04-04`..`-08` remain `PLANNED_BLOCKED`.
- CORE-05/DATA-02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-04-03` as `COMPLETED`, manifest `DATA04_03_COMPLETED_REST_BLOCKED`: **649 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 79 `COMPLETED`, 20 approved gates**.
