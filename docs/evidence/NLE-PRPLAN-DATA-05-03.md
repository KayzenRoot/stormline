# NLE-PRPLAN-DATA-05-03 — target/cook plan evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO CODEC OR ABI CLAIM`. **Base:** `13eac5c`. **Gate:** [NLE-PRPLAN-DATA-05-03-G6-ACTIVATION](NLE-PRPLAN-DATA-05-03-G6-ACTIVATION.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md). **WO:** [NLE-PRPLAN-DATA-05-03](../work-orders/NLE-PRPLAN-DATA-05-03.md).

## Scope delivered

- `src/stormline/data/bundle/bundle_types.hpp`: errors, target enums, quotas, records.
- `src/stormline/data/bundle/cook_plan.hpp`: `validate_target`, `make_cook_plan`.
- `tests/core/data05_target_tests.cpp`: TGT-01.
- Additive CMake/workflow entries.

No RLE/stream/manifest/patch, codec, persistence, native I/O, network, ABI or release.

## Implementation notes

- Target requires nonzero ID, known OS/arch, flags subset `0x7F`, quality tier 1..3.
- Cook plan accepts 1..64 unique valid DATA-02 AssetIds with nonzero source revisions.
- Estimated bytes = asset count × 256, bounded by the fixed asset cap.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data05_target_tests.cpp -o /tmp/data05_tgt
/tmp/data05_tgt tgt01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- The test needed the DATA-02 `registry` namespace alias; added. Production code unchanged.

## Security and architecture

- Header-only internal C++20; no allocation, codec, file, database or network.

## Rollback

Revert normally; remove bundle headers/test and additive CMake/workflow entries.

## Open risks / not claimed

- No RLE/stream/manifest/patch yet.
- No codec/signing/persistence/native I/O.
- `DATA-05-04`..`-09` remain `PLANNED_BLOCKED`.
- DATA-03/DATA-04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-05-03` as `COMPLETED`, manifest `DATA05_03_COMPLETED_REST_BLOCKED`: **641 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 85 `COMPLETED`, 22 approved gates**.
