# NLE-PRPLAN-DATA-02-07 — metadata schema evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO SERIALIZATION OR ABI CLAIM`. **Base:** `660ae5b`. **Gate:** [NLE-PRPLAN-DATA-02-07-G6-ACTIVATION](NLE-PRPLAN-DATA-02-07-G6-ACTIVATION.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md). **WO:** [NLE-PRPLAN-DATA-02-07](../work-orders/NLE-PRPLAN-DATA-02-07.md).

## Scope delivered

- Additive `MetadataEntry`, `make_metadata_entry`, `set_metadata` and `metadata` in `asset_registry.hpp`.
- `tests/core/data02_schema_tests.cpp`: SCHEMA-01.
- Additive CMake target/test and workflow TSan target.

No references/rename/impact, serialization, persistence, SQLite, native I/O, network, ABI or release.

## Implementation notes

- Schema version 1 only; 0..8 entries per asset; key 1..32 `[A-Za-z0-9_.-]`; value 0..64 printable ASCII.
- Duplicate keys and forged entry bytes are rejected before mutation.
- Replacement is atomic: previous metadata stays if validation fails.
- Empty set clears metadata and schema version; tombstoned/missing assets return typed errors.
- Fixed metadata table of 64 assets x 8 entries.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data02_schema_tests.cpp -o /tmp/data02_schema_test
/tmp/data02_schema_test schema01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- `set_metadata` initially returned `InvalidSchema` for an invalid ID; corrected to `InvalidArgument` before version validation. No API change.
- Directly constructed entries were initially trusted; added full key/value byte validation before atomic replacement.

## Security and architecture

- Header-only internal C++20; fixed table, no allocation, exception, file, database, network or serialization.
- DATA-02 owns metadata; DATA-01 owns paths; boundaries unchanged.

## Rollback

Revert normally; remove additive metadata code/test and CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No serialization, persistence, database, migration or crash recovery.
- No references/rename/impact yet.
- `DATA-02-08`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 not module-qualified; DATA-01 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-02-07` as `COMPLETED`, manifest `DATA02_07_COMPLETED_REST_BLOCKED`: **665 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 67 `COMPLETED`, 16 approved gates**. This is a proposal, not a self-promoted checkpoint.
