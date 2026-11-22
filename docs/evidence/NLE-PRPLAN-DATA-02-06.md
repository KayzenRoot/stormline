# NLE-PRPLAN-DATA-02-06 — deterministic queries evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PERSISTENCE OR ABI CLAIM`. **Base:** `8f0a0b6`. **Gate:** [NLE-PRPLAN-DATA-02-06-G6-ACTIVATION](NLE-PRPLAN-DATA-02-06-G6-ACTIVATION.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md). **WO:** [NLE-PRPLAN-DATA-02-06](../work-orders/NLE-PRPLAN-DATA-02-06.md).

## Scope delivered

- Additive `AssetQuery` and `query` in `asset_registry.hpp`.
- `tests/core/data02_query_tests.cpp`: QUERY-01.
- Additive CMake target/test and workflow TSan target.

No metadata schema, references/rename/impact, persistence, SQLite, serialization, native I/O, network, ABI or release.

## Implementation notes

- Active assets only; exact project scope.
- Optional kind, tag and DATA-01 component-boundary prefix filters.
- Results sorted ascending by `AssetId`; caller-owned output and offset cursor.
- `next_offset` is zero when exhausted, otherwise the next page start.
- Empty output and invalid project/tag/prefix return `InvalidArgument`; no match returns zero.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data02_query_tests.cpp -o /tmp/data02_query_test
/tmp/data02_query_test query01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- The pagination fixture kept the prefix filter active and expected wrong rows; corrected the fixture to clear the prefix. Production code unchanged.
- A `query` implementation was lost by a local reset before commit and was reapplied verbatim from the tested source; the committed file is the tested one.

## Security and architecture

- Header-only internal C++20; fixed arrays, no allocation, exception, file, database or network.
- DATA-02 owns queries; DATA-01 owns prefix semantics; boundaries unchanged.

## Rollback

Revert normally; remove additive query code/test and CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No persistence, serialization, database or crash recovery.
- No schema/references yet.
- `DATA-02-07`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 not module-qualified; DATA-01 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-02-06` as `COMPLETED`, manifest `DATA02_06_COMPLETED_REST_BLOCKED`: **666 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 66 `COMPLETED`, 16 approved gates**. This is a proposal, not a self-promoted checkpoint.
