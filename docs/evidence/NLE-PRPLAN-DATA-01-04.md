# NLE-PRPLAN-DATA-01-04 — mounts evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ABI OR RELEASE CLAIM`. **Base:** `d8dd352`. **Gate:** [NLE-PRPLAN-DATA-01-04-G6-ACTIVATION](NLE-PRPLAN-DATA-01-04-G6-ACTIVATION.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md). **WO:** [NLE-PRPLAN-DATA-01-04](../work-orders/NLE-PRPLAN-DATA-01-04.md).

## Scope delivered

- `src/stormline/data/vfs/vfs_mount.hpp`: `MountMode`, `MountInfo`, bounded read-only `MountTable`.
- `tests/core/data01_mount_tests.cpp`: MOUNT-01.
- Additive CMake target/test and workflow TSan target list.

No overlays, capabilities, cache, storage, native filesystem, archive, writes, network, serialization, ABI or release.

## Implementation notes

- Add requires valid ID, read-only mode, unique ID/root and capacity; stores table generation+1.
- Remove shifts entries and increments generation; missing ID returns `NotFound`.
- Find/at copy values; out-of-range returns false.
- Fixed capacity 32; no allocation, file, network or platform call.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data01_mount_tests.cpp -o /tmp/data01_mount_test
/tmp/data01_mount_test mount01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed here before the exact-head run. No native OS/sandbox or performance result exists.

## Errors and corrections

- Initial test ignored the `[[nodiscard]]` result of `make_path`, failing `-Werror`; corrected with an explicit `(void)` cast in the fixture helper.

## Security and architecture

- Header-only internal C++20; no exception, dynamic allocation, platform API, file I/O, network or dependency.
- DATA-01 owns logical mounts; CORE-01/02/03/04/06 and DATA-02..05 boundaries unchanged.
- No secret, paid service or mutable global state.

## Rollback

Revert this PR normally; remove `vfs_mount.hpp`, the mount test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No overlay resolution, permissions/capabilities, cache, storage, native confinement, archive or writes.
- No sandbox, ABI, release or performance claim.
- `DATA-01-05`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-01-04` as `COMPLETED`, manifest `DATA01_04_COMPLETED_REST_BLOCKED`: **678 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 56 `COMPLETED`, 14 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.
