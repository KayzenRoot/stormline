# NLE-PRPLAN-DATA-03-09 — integrated import qualification evidence

**Status:** `INTERNAL_CI_QUALIFICATION / NOT_DECODER_OR_RELEASE_QUALIFICATION`. **Base:** `df877e2`. **Gate:** [NLE-PRPLAN-DATA-03-09-G6-ACTIVATION](NLE-PRPLAN-DATA-03-09-G6-ACTIVATION.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md). **WO:** [NLE-PRPLAN-DATA-03-09](../work-orders/NLE-PRPLAN-DATA-03-09.md).

## Scope delivered

- `tests/core/data03_import_qualification_tests.cpp`: QLF-I01..04.
- Additive CMake target/four tests and workflow TSan target.

No production change, decoder, conversion, native I/O, persistence, ABI or release.

## Qualification results

- **QLF-I01:** descriptor→PNG sniff→plan→texture validation→receipt; plan/validation/receipt fields match.
- **QLF-I02:** two independent builds yield identical format, importer, validation status, warning count and receipt presence.
- **QLF-I03:** unknown signature→valid plan, invalid texture→valid, duplicate receipt→new receipt.
- **QLF-I04:** 10,000 descriptor adds stop at four known formats, 10,000 plans and validations remain valid, 10,000 receipts stop at 64 with stable warning total.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data03_import_qualification_tests.cpp -o /tmp/data03_qlf
/tmp/data03_qlf qlf01
/tmp/data03_qlf qlf02
/tmp/data03_qlf qlf03
/tmp/data03_qlf qlf04
```

All exited 0. ASan/UBSan rebuild and all four modes exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run. This is internal logical qualification only; no decoder, hardware, ABI or release claim.

## Errors and corrections

- A generated `main` contained literal newlines inside `fprintf` strings; rewritten with escaped newlines. No production change.

## Security and architecture

- Test-only; frozen headers; no allocation, file, decoder, database or network.

## Rollback

Revert normally; remove qualification test and additive CMake/workflow entries.

## Open risks / not claimed

- No real decoder, conversion, archive, native I/O, persistence or hardware qualification.
- `DATA-03-10` remains `PLANNED_BLOCKED`.
- DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-03-09` as `COMPLETED`, manifest `DATA03_09_COMPLETED_REST_BLOCKED`: **653 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 77 `COMPLETED`, 18 approved gates**.
