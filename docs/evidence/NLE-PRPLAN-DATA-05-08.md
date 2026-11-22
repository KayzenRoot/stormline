# NLE-PRPLAN-DATA-05-08 — bundle qualification evidence

**Status:** `INTERNAL_CI_QUALIFICATION / NOT_CODEC_OR_RELEASE_QUALIFICATION`. **Base:** `b1e276f`. **Gate:** [NLE-PRPLAN-DATA-05-08-G6-ACTIVATION](NLE-PRPLAN-DATA-05-08-G6-ACTIVATION.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md). **WO:** [NLE-PRPLAN-DATA-05-08](../work-orders/NLE-PRPLAN-DATA-05-08.md).

## Scope delivered

- `tests/core/data05_bundle_qualification_tests.cpp`: QLF-B01..04.
- Additive CMake target/four tests and workflow TSan target.

No production change, external codec, signing, network, persistence, ABI or release.

## Qualification results

- **QLF-B01:** target/cook→RLE→manifest/store→stream→patch; roundtrip and reuse verified.
- **QLF-B02:** two independent sequences produce identical cook/encoded/fingerprint/stream/reuse values.
- **QLF-B03:** invalid target→valid; empty RLE→valid; uninitialized manifest→valid; verify succeeds.
- **QLF-B04:** 10,000 cook/RLE/manifest attempts keep fixed capacities; 64 manifest entries.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data05_bundle_qualification_tests.cpp -o /tmp/data05_qlf
/tmp/data05_qlf qlf01
/tmp/data05_qlf qlf02
/tmp/data05_qlf qlf03
/tmp/data05_qlf qlf04
```

All exited 0. ASan/UBSan rebuild and all four modes exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run. Internal logical qualification only; no codec, signing, hardware, ABI or release claim.

## Errors and corrections

- The empty-RLE fixture passed a value where an output span was required; corrected to a scratch buffer. No production change.

## Security and architecture

- Test-only; frozen headers; no allocation, codec, file, database or network.

## Rollback

Revert normally; remove qualification test and additive CMake/workflow entries.

## Open risks / not claimed

- No external codec, signing, network, persistence or hardware qualification.
- `DATA-05-09` remains `PLANNED_BLOCKED`.
- DATA-03/DATA-04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-05-08` as `COMPLETED`, manifest `DATA05_08_COMPLETED_REST_BLOCKED`: **636 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 90 `COMPLETED`, 22 approved gates**.
