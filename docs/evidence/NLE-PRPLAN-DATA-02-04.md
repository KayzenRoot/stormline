# NLE-PRPLAN-DATA-02-04 — dependency graph evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PERSISTENCE OR ABI CLAIM`. **Base:** `3c2f7c3`. **Gate:** [NLE-PRPLAN-DATA-02-04-G6-ACTIVATION](NLE-PRPLAN-DATA-02-04-G6-ACTIVATION.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md). **WO:** [NLE-PRPLAN-DATA-02-04](../work-orders/NLE-PRPLAN-DATA-02-04.md).

## Scope delivered

- Additive dependency types/state/methods in `asset_registry.hpp`.
- `tests/core/data02_dependency_tests.cpp`: DEP-01.
- Additive CMake target/test and workflow TSan target.

No tags, queries, metadata schema, references/rename/impact, persistence, SQLite, serialization, native I/O, network, ABI or release.

## Implementation notes

- Fixed 128-edge table; duplicate same-kind edges are idempotent.
- `from` must be an active asset; missing `to` is retained as unresolved.
- Self-edges and edges closing a cycle are rejected before storage.
- Forward/reverse outputs are unique and sorted by `AssetId`; insufficient output returns `BufferFull` with the required count.
- Tombstoning a target increments `unresolved_dependencies`.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data02_dependency_tests.cpp -o /tmp/data02_dep_test
/tmp/data02_dep_test dep01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- The first cycle fixture removed `A->B` before testing `B->A`, which was not a cycle; corrected the fixture to `C->A` against existing `A->C`. Production code unchanged.

## Security and architecture

- Header-only internal C++20; bounded iterative traversal, no recursion overflow, allocation, exception, file, database or network.
- DATA-02 owns the graph; DATA-01 owns paths; other module boundaries unchanged.

## Rollback

Revert this PR normally; remove additive dependency code/test and CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No persistence, serialization, database, transaction or crash recovery.
- No tags/queries/schema/references yet.
- `DATA-02-05`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 not module-qualified; DATA-01 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-02-04` as `COMPLETED`, manifest `DATA02_04_COMPLETED_REST_BLOCKED`: **668 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 64 `COMPLETED`, 16 approved gates**. This is a proposal, not a self-promoted checkpoint.
