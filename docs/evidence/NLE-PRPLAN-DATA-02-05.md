# NLE-PRPLAN-DATA-02-05 — bounded tags evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PERSISTENCE OR ABI CLAIM`. **Base:** `6ac7980`. **Gate:** [NLE-PRPLAN-DATA-02-05-G6-ACTIVATION](NLE-PRPLAN-DATA-02-05-G6-ACTIVATION.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md). **WO:** [NLE-PRPLAN-DATA-02-05](../work-orders/NLE-PRPLAN-DATA-02-05.md).

## Scope delivered

- Additive `AssetRegistry::Tag` and tag storage/methods in `asset_registry.hpp`.
- `tests/core/data02_tag_tests.cpp`: TAG-01.
- Additive CMake target/test and workflow TSan target.

No queries, metadata schema, references/rename/impact, persistence, SQLite, serialization, native I/O, network, ABI or release.

## Implementation notes

- Tag text is 1..32 printable ASCII excluding space, `/`, `:`, backslash and control; case-sensitive.
- Duplicate same tag is idempotent; per-asset quota is 8.
- `tags_of` preserves insertion order and returns `BufferFull` with required count.
- Missing/tombstoned assets return `NotFound`/`Tombstoned`; remove-missing returns `NotFound`.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data02_tag_tests.cpp -o /tmp/data02_tag_test
/tmp/data02_tag_test tag01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- A generated backslash character literal was malformed; replaced with an explicit `0x5C` byte comparison. No API change.

## Security and architecture

- Header-only internal C++20; fixed tag table, no allocation, exception, file, database or network.
- DATA-02 owns tags; DATA-01 owns paths; MODULE boundaries unchanged.

## Rollback

Revert normally; remove additive tag code/test and CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No persistence, serialization, database or crash recovery.
- No queries/schema/references yet.
- `DATA-02-06`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 not module-qualified; DATA-01 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-02-05` as `COMPLETED`, manifest `DATA02_05_COMPLETED_REST_BLOCKED`: **667 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 65 `COMPLETED`, 16 approved gates**. This is a proposal, not a self-promoted checkpoint.
