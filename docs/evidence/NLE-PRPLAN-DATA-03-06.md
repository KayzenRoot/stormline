# NLE-PRPLAN-DATA-03-06 — audio metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO DECODER OR ABI CLAIM`. **Base:** `a631eee`. **Gate:** [NLE-PRPLAN-DATA-03-06-G6-ACTIVATION](NLE-PRPLAN-DATA-03-06-G6-ACTIVATION.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md). **WO:** [NLE-PRPLAN-DATA-03-06](../work-orders/NLE-PRPLAN-DATA-03-06.md).

## Scope delivered

- `src/stormline/data/import/audio_metadata.hpp`: `AudioMetadata` and `validate_audio`.
- `tests/core/data03_audio_tests.cpp`: AUDIO-01.
- Additive CMake/workflow entries.

No decoder, conversion, composite validation, receipts, persistence, native I/O, network, ABI or release.

## Implementation notes

- Sample rate 8000..192000; channels 1..8; bits 8/16/24/32; frames 1..10,000,000.
- Invalid values return `InvalidAudio`; valid values produce zero warnings.
- No bytes are parsed or converted.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data03_audio_tests.cpp -o /tmp/data03_audio
/tmp/data03_audio audio01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

None introduced.

## Security and architecture

- Header-only internal C++20; no allocation, exception, decoder, file, database or network.

## Rollback

Revert normally; remove the audio header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No real audio decoding/conversion or file validation.
- No composite validation or receipts yet.
- `DATA-03-07`..`-10` remain `PLANNED_BLOCKED`.
- DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-03-06` as `COMPLETED`, manifest `DATA03_06_COMPLETED_REST_BLOCKED`: **656 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 74 `COMPLETED`, 18 approved gates**.
