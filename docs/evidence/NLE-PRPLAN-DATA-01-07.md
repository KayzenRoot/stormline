# NLE-PRPLAN-DATA-01-07 — cache evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ABI OR RELEASE CLAIM`. **Base:** `00ec299`. **Gate:** [NLE-PRPLAN-DATA-01-07-G6-ACTIVATION](NLE-PRPLAN-DATA-01-07-G6-ACTIVATION.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md). **WO:** [NLE-PRPLAN-DATA-01-07](../work-orders/NLE-PRPLAN-DATA-01-07.md).

## Scope delivered

- `src/stormline/data/vfs/vfs_cache.hpp`: `CacheKey`, fixed 64-entry `PathCache`.
- `tests/core/data01_cache_tests.cpp`: CACHE-01.
- Additive CMake target/test and workflow TSan target list.

No storage backend, native filesystem, archive, writes, network, serialization, ABI or release.

## Implementation notes

- Key is `(mount, generation, path)`; duplicate key updates in place.
- `get` distinguishes `NotFound` from `StaleMount`; insufficient output returns `BufferFull` with required size.
- `invalidate_mount` removes all matching entries; clear resets size/dropped.
- Fixed capacity 64 and 256 bytes per entry; no allocation, file or network.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data01_cache_tests.cpp -o /tmp/data01_cache_test
/tmp/data01_cache_test cache01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed here before the exact-head run. No native OS/sandbox or performance result exists.

## Errors and corrections

- Initial cache test filled the same cache that already held an entry and expected all 64 additions to succeed; corrected to use a separate empty cache and match exact capacity/invalidation counts. Production code unchanged.

## Security and architecture

- Header-only internal C++20; no exception, dynamic allocation, platform API, file I/O, network or dependency.
- DATA-01 owns logical cache; CORE-01/02/03/04/06 and DATA-02..05 boundaries unchanged.
- No secret, paid service or mutable global state.

## Rollback

Revert this PR normally; remove `vfs_cache.hpp`, the cache test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No storage backend, native confinement, archive or writes; no cross-process cache.
- No sandbox, ABI, release or performance claim.
- `DATA-01-08`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-01-07` as `COMPLETED`, manifest `DATA01_07_COMPLETED_REST_BLOCKED`: **675 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 59 `COMPLETED`, 14 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.
