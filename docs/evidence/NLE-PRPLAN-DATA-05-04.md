# NLE-PRPLAN-DATA-05-04 — bounded RLE evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO EXTERNAL CODEC CLAIM`. **Base:** `b7c8b0e`. **Gate:** [NLE-PRPLAN-DATA-05-04-G6-ACTIVATION](NLE-PRPLAN-DATA-05-04-G6-ACTIVATION.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md). **WO:** [NLE-PRPLAN-DATA-05-04](../work-orders/NLE-PRPLAN-DATA-05-04.md).

## Scope delivered

- `src/stormline/data/bundle/rle.hpp`: `rle_encode`, `rle_decode`.
- `tests/core/data05_rle_tests.cpp`: RLE-01.
- Additive CMake/workflow entries.

No external codec, streaming, manifest, patch, persistence, native I/O, network, ABI or release.

## Implementation notes

- Input/output capped at 256 bytes; runs split at 255.
- Encode/decode return exact required size on `BufferFull`.
- Empty/odd/zero-run inputs are typed failures; decoded total over 256 is `CompressionLimit`.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data05_rle_tests.cpp -o /tmp/data05_rle
/tmp/data05_rle rle01
```

Exited 0. ASan/UBSan rebuild exited 0.

## Errors and corrections

- The run-split fixture passed 300 bytes against the 256-byte contract cap; corrected the span to 256. Production code unchanged.

## Security and architecture

- Header-only internal C++20; no allocation, codec library, file, database or network.

## Rollback

Revert normally; remove RLE header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No external compression codec or wire-format compatibility.
- No manifest/stream/patch yet.
- `DATA-05-05`..`-09` remain `PLANNED_BLOCKED`.
- DATA-03/DATA-04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-05-04` as `COMPLETED`, manifest `DATA05_04_COMPLETED_REST_BLOCKED`: **640 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 86 `COMPLETED`, 22 approved gates**.
