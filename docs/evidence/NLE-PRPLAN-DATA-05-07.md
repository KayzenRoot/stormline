# NLE-PRPLAN-DATA-05-07 — incremental reuse evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO DOWNLOAD OR PERSISTENCE CLAIM`. **Base:** `16eaa21`. **Gate:** [NLE-PRPLAN-DATA-05-07-G6-ACTIVATION](NLE-PRPLAN-DATA-05-07-G6-ACTIVATION.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md). **WO:** [NLE-PRPLAN-DATA-05-07](../work-orders/NLE-PRPLAN-DATA-05-07.md).

## Scope delivered

- `src/stormline/data/bundle/patch_plan.hpp`: `PatchPlan`, `make_patch_plan`.
- Additive `BundleManifest::at` accessor in `stream_window.hpp` to iterate entries safely.
- `tests/core/data05_patch_tests.cpp`: PAT-01.
- Additive CMake/workflow entries.

No download, signing, persistence, native I/O, network, ABI or release.

## Implementation notes

- Base/target generations must be nonzero and different, otherwise `PatchConflict`.
- Same chunk ID and fingerprint counts reuse; missing/different fingerprint counts fetch.
- Counts bounded by target manifest size.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data05_patch_tests.cpp -o /tmp/data05_patch
/tmp/data05_patch pat01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- Patch planning needed entry iteration; added an additive `BundleManifest::at` accessor rather than assuming dense chunk IDs. No behavior change to streaming.

## Security and architecture

- Header-only internal C++20; no allocation, download, signing, file, database or network.

## Rollback

Revert normally; remove patch header/test, revert the accessor and additive CMake/workflow entries.

## Open risks / not claimed

- No download/install, signature/trust, persistence or recovery.
- No qualification yet; `DATA-05-08`..`-09` remain `PLANNED_BLOCKED`.
- DATA-03/DATA-04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-05-07` as `COMPLETED`, manifest `DATA05_07_COMPLETED_REST_BLOCKED`: **637 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 89 `COMPLETED`, 22 approved gates**.
