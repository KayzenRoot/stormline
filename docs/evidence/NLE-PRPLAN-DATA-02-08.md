# NLE-PRPLAN-DATA-02-08 — references and rename evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PERSISTENCE OR ABI CLAIM`. **Base:** `c61878c`. **Gate:** [NLE-PRPLAN-DATA-02-08-G6-ACTIVATION](NLE-PRPLAN-DATA-02-08-G6-ACTIVATION.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md). **WO:** [NLE-PRPLAN-DATA-02-08](../work-orders/NLE-PRPLAN-DATA-02-08.md).

## Scope delivered

- Additive `AssetReference`, `make_reference`, `resolve_reference`, `rename` and `impact` in `asset_registry.hpp`.
- `tests/core/data02_reference_tests.cpp`: REF-01.
- Additive CMake target/test and workflow TSan target.

No persistence, SQLite, serialization, native I/O, network, ABI or release.

## Implementation notes

- References hold `AssetId` and resolve current record; kind check is optional via `Unknown`.
- Missing and tombstoned targets return typed errors; no record escapes on failure.
- Rename revalidates the path, checks project-scoped collision, preserves ID, increments revision and leaves old path unmapped.
- Impact traverses reverse dependency edges with fixed visited/stack arrays, excludes self, sorts ascending and returns `BufferFull` with required count.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data02_reference_tests.cpp -o /tmp/data02_ref_test
/tmp/data02_ref_test ref01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- The test used an unqualified `VfsPath`; corrected to `vfs::VfsPath`. Production code unchanged.

## Security and architecture

- Header-only internal C++20; bounded traversal, no allocation, exception, file, database or network.
- Identity is preserved on rename; references never store a path.

## Rollback

Revert normally; remove additive reference/rename/impact code/test and CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No persistence, serialization, database, transaction or crash recovery.
- No qualification of physical/hardware, ABI or release.
- `DATA-02-09`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 not module-qualified; DATA-01 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-02-08` as `COMPLETED`, manifest `DATA02_08_COMPLETED_REST_BLOCKED`: **664 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 68 `COMPLETED`, 16 approved gates**. This is a proposal, not a self-promoted checkpoint.
