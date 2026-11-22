# NLE-PRPLAN-DATA-04-05 — atomic patch evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO CODEC OR ABI CLAIM`. **Base:** `9d3695d`. **Gate:** [NLE-PRPLAN-DATA-04-05-G6-ACTIVATION](NLE-PRPLAN-DATA-04-05-G6-ACTIVATION.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md). **WO:** [NLE-PRPLAN-DATA-04-05](../work-orders/NLE-PRPLAN-DATA-04-05.md).

## Scope delivered

- `src/stormline/data/scene/scene_patch.hpp`: `PatchOp`, `PatchOperation`, `ScenePatch`, `apply_patch`.
- `tests/core/data04_patch_tests.cpp`: PATCH-01.
- Additive CMake/workflow entries.

No diff, codec, persistence, native I/O, network, ABI or release.

## Implementation notes

- Operation ID, scene ID and base revision are checked before mutation.
- All operations are applied to a copy; any failure leaves the original unchanged.
- Add entity, remove entity (cascading components/refs) and set-enabled are supported; success bumps revision.
- Patch is bounded to 64 operations.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data04_patch_tests.cpp -o /tmp/data04_patch
/tmp/data04_patch patch01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

None introduced.

## Security and architecture

- Header-only internal C++20; fixed arrays, no allocation, codec, file, database or network.

## Rollback

Revert normally; remove patch header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No diff yet; no JSON/CBOR/persistence/native I/O.
- `DATA-04-06`..`-08` remain `PLANNED_BLOCKED`.
- CORE-05/DATA-02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-04-05` as `COMPLETED`, manifest `DATA04_05_COMPLETED_REST_BLOCKED`: **647 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 81 `COMPLETED`, 20 approved gates**.
