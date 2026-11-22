# NLE-PRPLAN-DATA-01-05 — overlays evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ABI OR RELEASE CLAIM`. **Base:** `835017b`. **Implementation head:** `2f69c0b`. **Gate:** [NLE-PRPLAN-DATA-01-05-G6-ACTIVATION](NLE-PRPLAN-DATA-01-05-G6-ACTIVATION.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md). **WO:** [NLE-PRPLAN-DATA-01-05](../work-orders/NLE-PRPLAN-DATA-01-05.md).

## Scope delivered

- `src/stormline/data/vfs/vfs_overlay.hpp`: `LookupResult` and deterministic `resolve`.
- `tests/core/data01_overlay_tests.cpp`: OVERLAY-01.
- Additive CMake target/test and workflow TSan target list.

No capabilities, cache, storage, native filesystem, archive, writes, network, serialization, ABI or release.

## Implementation notes

- Highest priority wins; equal priority chooses lower `MountId`.
- Only component-boundary prefixes match (`a` does not match `ab`).
- Relative suffix, mount generation and `shadowed_count` are returned.
- No match returns `NotFound`; empty table is valid.
- Fixed values only; no allocation, file, network or platform call.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data01_overlay_tests.cpp -o /tmp/data01_overlay_test
/tmp/data01_overlay_test overlay01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI on implementation head `2f69c0b`: [run 45055997398](https://github.com/KayzenRoot/stormline/actions/runs/45055997398) SUCCESS — Linux **178/178**, ASan/UBSan **178/178**, TSan **53/53**, Windows **179/179**, macOS **177/177**. Docs [45055997402](https://github.com/KayzenRoot/stormline/actions/runs/45055997402) SUCCESS; SonarCloud e Socket SUCCESS. No native OS/sandbox or performance result exists.

## Errors and corrections

No production or test correction was needed after local compile/test.

## Security and architecture

- Header-only internal C++20; no exception, dynamic allocation, platform API, file I/O, network or dependency.
- DATA-01 owns logical overlays; CORE-01/02/03/04/06 and DATA-02..05 boundaries unchanged.
- No secret, paid service or mutable global state.

## Rollback

Revert this PR normally; remove `vfs_overlay.hpp`, the overlay test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No capabilities, cache, storage, native confinement, archive or writes.
- No sandbox, ABI, release or performance claim.
- `DATA-01-06`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-01-05` as `COMPLETED`, manifest `DATA01_05_COMPLETED_REST_BLOCKED`: **677 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 57 `COMPLETED`, 14 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.
