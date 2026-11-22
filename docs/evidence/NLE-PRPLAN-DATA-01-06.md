# NLE-PRPLAN-DATA-01-06 — capabilities evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ABI OR RELEASE CLAIM`. **Base:** `cbeed64`. **Implementation head:** `821051c`. **Gate:** [NLE-PRPLAN-DATA-01-06-G6-ACTIVATION](NLE-PRPLAN-DATA-01-06-G6-ACTIVATION.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md). **WO:** [NLE-PRPLAN-DATA-01-06](../work-orders/NLE-PRPLAN-DATA-01-06.md).

## Scope delivered

- `src/stormline/data/vfs/vfs_capability.hpp`: `AccessCapability` and bounded `CapabilitySet`.
- `tests/core/data01_capability_tests.cpp`: CAP-01.
- Additive CMake target/test and workflow TSan target list.

No cache, storage, native filesystem, archive, writes, network, serialization, ABI or release.

## Implementation notes

- `grant` requires valid workspace/mount and `read=true`; duplicate workspace/mount updates; full set returns `BufferFull`.
- `revoke` removes the exact workspace/mount pair; missing returns `NotFound`.
- `allows` is true only for an exact read capability; no ambient authority.
- Fixed capacity 16; no allocation, file, network or platform call.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data01_capability_tests.cpp -o /tmp/data01_capability_test
/tmp/data01_capability_test cap01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI on implementation head `821051c`: [run 45057852330](https://github.com/KayzenRoot/stormline/actions/runs/45057852330) SUCCESS — Linux **179/179**, ASan/UBSan **179/179**, TSan **53/53**, Windows **180/180**, macOS **178/178**. Docs [45057852423](https://github.com/KayzenRoot/stormline/actions/runs/45057852423) SUCCESS; SonarCloud e Socket SUCCESS. No native OS/sandbox or performance result exists.

## Errors and corrections

No production or test correction was needed after local compile/test.

## Security and architecture

- Header-only internal C++20; no exception, dynamic allocation, platform API, file I/O, network or dependency.
- DATA-01 owns logical capabilities; CORE-01/02/03/04/06 and DATA-02..05 boundaries unchanged.
- No secret, paid service or mutable global state.

## Rollback

Revert this PR normally; remove `vfs_capability.hpp`, the capability test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No cache, storage, native confinement, archive or writes; no auth/identity/expiry model.
- No sandbox, ABI, release or performance claim.
- `DATA-01-07`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-01-06` as `COMPLETED`, manifest `DATA01_06_COMPLETED_REST_BLOCKED`: **676 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 58 `COMPLETED`, 14 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.
