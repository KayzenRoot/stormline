# NLE-PRPLAN-DATA-02-03 — stable asset identity evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PERSISTENCE OR ABI CLAIM`. **Base:** `0810a1e`. **Gate:** [NLE-PRPLAN-DATA-02-03-G6-ACTIVATION](NLE-PRPLAN-DATA-02-03-G6-ACTIVATION.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md). **WO:** [NLE-PRPLAN-DATA-02-03](../work-orders/NLE-PRPLAN-DATA-02-03.md).

## Scope delivered

- `src/stormline/data/registry/registry_types.hpp`: opaque 128-bit `AssetId`, `ProjectId`, kinds/status, capacities and typed errors.
- `src/stormline/data/registry/asset_registry.hpp`: fixed 64-asset core with add/find/path lookup/tombstone.
- `tests/core/data02_id_tests.cpp`: ID-01.
- Additive CMake target/test and workflow TSan/path filters.

No dependencies, tags, queries, metadata schema, references, persistence, SQLite, serialization, native I/O, network, ABI or release.

## Implementation notes

- Identity is `{high, low}` with zero reserved invalid; path collision is project-scoped.
- Path is revalidated on add; forged length and invalid bytes are rejected.
- Duplicate ID and duplicate path are distinct typed errors.
- Tombstone reserves ID/path, changes status and increments revision; double tombstone and missing ID are typed.
- Fixed capacity 64; overflow returns `CapacityFull` without eviction.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data02_id_tests.cpp -o /tmp/data02_id_test
/tmp/data02_id_test id01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run. No persistence or performance result exists.

## Errors and corrections

- The first test compile needed the sibling `vfs` namespace alias inside `data::registry`; added `namespace vfs = stormline::data::vfs;`. Production API unchanged.

## Security and architecture

- Header-only internal C++20; no allocation, exception, platform API, file I/O, database, network or dependency.
- DATA-02 owns identity; DATA-01 owns `VfsPath`; CORE and DATA-03..05 boundaries unchanged.
- No host path, secret or mutable global state.

## Rollback

Revert this PR normally; remove the registry headers, ID test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No persistence, serialization, database, crash recovery or native filesystem.
- No dependencies/tags/queries/schema/references yet.
- `DATA-02-04`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 not module-qualified; DATA-01 `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; CORE-02 NOT_QUALIFIED; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-02-03` as `COMPLETED`, manifest `DATA02_03_COMPLETED_REST_BLOCKED`: **669 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 63 `COMPLETED`, 16 approved gates**, and keep later packets blocked. This is a proposal, not a self-promoted checkpoint.
