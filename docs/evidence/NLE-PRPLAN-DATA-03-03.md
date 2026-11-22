# NLE-PRPLAN-DATA-03-03 — importer planning evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO DECODER OR ABI CLAIM`. **Base:** `3e2e4d0`. **Gate:** [NLE-PRPLAN-DATA-03-03-G6-ACTIVATION](NLE-PRPLAN-DATA-03-03-G6-ACTIVATION.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md). **WO:** [NLE-PRPLAN-DATA-03-03](../work-orders/NLE-PRPLAN-DATA-03-03.md).

## Scope delivered

- `src/stormline/data/import/import_types.hpp`: errors, formats, artifacts, quotas, descriptor.
- `src/stormline/data/import/importer_registry.hpp`: fixed registry, signature sniffing, import plan.
- `tests/core/data03_importer_tests.cpp`: IMP-01.
- Additive CMake/workflow entries.

No decoder, conversion, metadata validation, receipts, persistence, native I/O, network, ABI or release.

## Implementation notes

- Descriptors require nonzero ID/version, known format/artifact, bounded ASCII extension; duplicate ID or format is rejected.
- Signatures: Png 8 bytes, Jpeg 3, Glb 4, Wav RIFF+WAVE 12; prefix truncation is typed, unknown magic is typed.
- Plan requires a valid nonempty DATA-01 path, matching declared format when present, and a registered importer.
- Capacity is fixed at 16; under the frozen four known formats the format-uniqueness rule makes the capacity branch defensive rather than reachable in IMP-01.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data03_importer_tests.cpp -o /tmp/data03_imp
/tmp/data03_imp imp01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- The test initially filled the registry with repeated Png descriptors, which the contract rejects as duplicate format; removed that unreachable capacity fixture. Production code unchanged.

## Security and architecture

- Header-only internal C++20; no allocation, exception, decoder, file, archive, database or network.
- Signature checks are prefix classification only, not full decoding or validation.

## Rollback

Revert normally; remove import headers/test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No real decoder/conversion; no texture/animation/audio validation or receipts yet.
- No persistence, native I/O, network, hardware, ABI or release.
- `DATA-03-04`..`-10` remain `PLANNED_BLOCKED`.
- DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-03-03` as `COMPLETED`, manifest `DATA03_03_COMPLETED_REST_BLOCKED`: **659 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 71 `COMPLETED`, 18 approved gates**. This is a proposal, not a self-promoted checkpoint.
