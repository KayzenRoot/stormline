# NLE-PRPLAN-DATA-01-03 — virtual paths evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ABI OR RELEASE CLAIM`. **Base:** `085bf1c`. **Gate:** [NLE-PRPLAN-DATA-01-03-G6-ACTIVATION](NLE-PRPLAN-DATA-01-03-G6-ACTIVATION.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md). **WO:** [NLE-PRPLAN-DATA-01-03](../work-orders/NLE-PRPLAN-DATA-01-03.md).

## Scope delivered

- `src/stormline/data/vfs/vfs_types.hpp`: `VfsError`, `VfsPath`, `MountId`, `WorkspaceId`, bounds and validity.
- `src/stormline/data/vfs/vfs_path.hpp`: `make_path`, `view`, `empty`, `is_prefix` with ASCII/traversal/reserved-name rules.
- `tests/core/data01_path_tests.cpp`: PATH-01.
- Additive CMake INTERFACE target/test and workflow path/TSan filters.

No mounts, overlays, capabilities, cache, storage, native filesystem, archive, writes, network, serialization, ABI or release.

## Implementation notes

- Empty path is the logical root.
- Valid paths are relative ASCII, max 512 bytes, components 1..64, no leading/trailing `/`, `//`, backslash, colon, NUL/control/non-ASCII, `.`/`..`, trailing dot/space or Windows reserved device name.
- `is_prefix` respects component boundaries; `view` is zero-copy over fixed storage.
- No allocation, file, network or platform call.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data01_path_tests.cpp -o /tmp/data01_path_test
/tmp/data01_path_test path01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed here before the exact-head run. No native OS/sandbox or performance result exists.

## Errors and corrections

- Initial PATH-01 backslash fixture was written as a C++ escape (`""`), exercising a bell byte rather than backslash. Corrected to `std::string(1, '\') + "a"`; production code unchanged.

## Security and architecture

- Header-only internal C++20; no exception, dynamic allocation, platform API, file I/O, network or dependency.
- DATA-01 owns logical paths; CORE-01/02/03/04/06 and DATA-02..05 boundaries unchanged.
- No secret, paid service or mutable global state.

## Rollback

Revert this PR normally; remove the two headers, path test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No Unicode normalization/casefold, host filesystem, symlink/junction confinement, archive, mount, overlay, permissions, cache or writes.
- No sandbox, ABI, release or performance claim.
- `DATA-01-04`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-01-03` as `COMPLETED`, manifest `DATA01_03_COMPLETED_REST_BLOCKED`: **679 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 55 `COMPLETED`, 14 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.
