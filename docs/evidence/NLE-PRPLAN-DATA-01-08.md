# NLE-PRPLAN-DATA-01-08 — storage evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ABI OR RELEASE CLAIM`. **Base:** `ca9ea16`. **Gate:** [NLE-PRPLAN-DATA-01-08-G6-ACTIVATION](NLE-PRPLAN-DATA-01-08-G6-ACTIVATION.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md). **WO:** [NLE-PRPLAN-DATA-01-08](../work-orders/NLE-PRPLAN-DATA-01-08.md).

## Scope delivered

- `src/stormline/data/vfs/vfs_storage.hpp`: `StorageDescriptor`, `StorageBackend`, fixed 64-file `MemoryStorage`.
- `tests/core/data01_storage_tests.cpp`: STORAGE-01.
- Additive CMake target/test and workflow TSan target list.

No native filesystem, archive, host write, persistence, network, serialization, ABI or release.

## Implementation notes

- Fixed in-memory table of 64 files with 256 bytes per file; no allocation.
- Path is revalidated on every operation; forged lengths are rejected before `view`.
- Duplicate path updates in place; full table returns `BufferFull` without eviction.
- `read` returns `BufferFull` with required size; missing paths return `NotFound`.
- `erase` compacts the table; `StorageBackend&` dispatch is exercised.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data01_storage_tests.cpp -o /tmp/data01_storage_test
/tmp/data01_storage_test storage01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed here before the exact-head run. No native OS/sandbox or performance result exists.

## Errors and corrections

None introduced. The invalid-path fixture exercises the typed `PathEscape` result and the oversized-length guard.

## Security and architecture

- Header-only internal C++20; no exception, dynamic allocation, platform API, file I/O, network or dependency.
- DATA-01 owns logical storage values; CORE-01/02/03/04/06 and DATA-02..05 boundaries unchanged.
- No secret, paid service or mutable global state.

## Rollback

Revert this PR normally; remove `vfs_storage.hpp`, the storage test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No native backend, archive, persistence or host writes; no cross-process storage.
- No sandbox, ABI, release or performance claim.
- `DATA-01-09`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-01-08` as `COMPLETED`, manifest `DATA01_08_COMPLETED_REST_BLOCKED`: **674 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 60 `COMPLETED`, 14 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.
