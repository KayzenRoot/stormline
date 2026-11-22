# NLE-PRPLAN-DATA-01-09 — integrated VFS qualification evidence

**Status:** `INTERNAL_CI_QUALIFICATION / NOT_PHYSICAL_OR_RELEASE_QUALIFICATION / NO ABI CLAIM`. **Base:** `30bbafc`. **Gate:** [NLE-PRPLAN-DATA-01-09-G6-ACTIVATION](NLE-PRPLAN-DATA-01-09-G6-ACTIVATION.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md). **WO:** [NLE-PRPLAN-DATA-01-09](../work-orders/NLE-PRPLAN-DATA-01-09.md).

## Scope delivered

- `tests/core/data01_vfs_qualification_tests.cpp`: QLF-01..04.
- Additive CMake target/four tests and workflow TSan target list.
- This evidence file.

No production header, API, behavior, native I/O, archive, persistence, dependency, ABI or release change.

## Qualification results

- **QLF-01 integrated VFS:** path→mount→overlay→capability→cache→memory storage; highest-priority mount selected, relative suffix and `shadowed_count` correct, capability allowed/denied as granted, cache and storage bytes match.
- **QLF-02 deterministic repeat:** two independent builds yield identical resolve status/mount/relative/generation/shadow count and identical cache/storage bytes and statuses.
- **QLF-03 failure recovery:** traversal rejected then valid path accepted; mount collision then valid add; overlay miss then hit; capability denied then granted; cache miss/stale then hit; storage miss then hit/erase. Every typed failure is followed by a successful valid operation.
- **QLF-04 bounded overload:** 10,000 mount adds, 10,000 cache puts and 10,000 storage puts beyond fixed capacities; capacities stay 32/64/64, mount generation stays 32, cache `dropped` equals 10,000, and existing entries remain readable.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data01_vfs_qualification_tests.cpp -o /tmp/data01_vfs_qual
/tmp/data01_vfs_qual qlf01
/tmp/data01_vfs_qual qlf02
/tmp/data01_vfs_qual qlf03
/tmp/data01_vfs_qual qlf04
```

All exited 0. ASan/UBSan rebuild and all four modes exited 0.

Native CI is executed by the PR workflow; no result is claimed here before the exact-head run. This is qualification of internal logical behavior in CI, not of physical hardware, OS sandboxing, archive security, performance, ABI or release.

## Errors and corrections

- Initial QLF-01 expectation treated `base/other.bin` as unresolved even though the `base` mount matches it; corrected to assert the base mount with zero shadows. No production change.
- An initial generated test file was truncated by the shell heredoc and was fully rewritten before build; no truncated content was committed.

## Security and architecture

- Test-only change using the frozen internal headers; no host path, file descriptor, OS call, network, allocation or dependency.
- No sandbox or confinement claim; lexical path validation is not OS confinement.
- Single-owner test objects; no mutable global state.

## Rollback

Revert this PR normally; remove the qualification test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No native filesystem confinement, archive codec, host writes, persistence, hardware, soak, performance, ABI or release qualification.
- `DATA-01-10` remains `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-01-09` as `COMPLETED`, manifest `DATA01_09_COMPLETED_REST_BLOCKED`: **673 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 61 `COMPLETED`, 14 approved gates**, and keep `DATA-01-10` blocked. This is a proposal, not a self-promoted checkpoint.
