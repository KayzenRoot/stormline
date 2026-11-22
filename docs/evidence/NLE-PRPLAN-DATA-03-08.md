# NLE-PRPLAN-DATA-03-08 — provenance receipts evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PERSISTENCE OR ABI CLAIM`. **Base:** `54fb551`. **Gate:** [NLE-PRPLAN-DATA-03-08-G6-ACTIVATION](NLE-PRPLAN-DATA-03-08-G6-ACTIVATION.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md). **WO:** [NLE-PRPLAN-DATA-03-08](../work-orders/NLE-PRPLAN-DATA-03-08.md).

## Scope delivered

- `src/stormline/data/import/import_receipt.hpp`: `ImportReceipt`, `ReceiptLog`.
- `tests/core/data03_receipt_tests.cpp`: REC-01.
- Additive CMake/workflow entries.

No persistence, serialization, decoder, native I/O, network, ABI or release.

## Implementation notes

- Fixed 64 receipts; operation ID unique; DATA-02 `AssetId` required; format/importer/version/artifact count validated.
- `warning_total` saturates at `u32` max.
- Receipts carry logical provenance only; nothing is written or serialized.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data03_receipt_tests.cpp -o /tmp/data03_rec
/tmp/data03_rec rec01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

None introduced.

## Security and architecture

- Header-only internal C++20; fixed arrays, no allocation, file, database or network.

## Rollback

Revert normally; remove receipt header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No persistence/serialization/durable provenance.
- No qualification yet; `DATA-03-09`..`-10` remain `PLANNED_BLOCKED`.
- DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-03-08` as `COMPLETED`, manifest `DATA03_08_COMPLETED_REST_BLOCKED`: **654 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 76 `COMPLETED`, 18 approved gates**.
