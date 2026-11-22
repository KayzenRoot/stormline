# NLE-PRPLAN-DATA-03-05 — animation metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO DECODER OR ABI CLAIM`. **Base:** `d187bfb`. **Gate:** [NLE-PRPLAN-DATA-03-05-G6-ACTIVATION](NLE-PRPLAN-DATA-03-05-G6-ACTIVATION.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md). **WO:** [NLE-PRPLAN-DATA-03-05](../work-orders/NLE-PRPLAN-DATA-03-05.md).

## Scope delivered

- `src/stormline/data/import/animation_metadata.hpp`: `AnimationMetadata` and `validate_animation`.
- `tests/core/data03_animation_tests.cpp`: ANIM-01.
- Additive CMake/workflow entries.

No decoder, conversion, audio/composite validation, receipts, persistence, native I/O, network, ABI or release.

## Implementation notes

- Joints 1..256, tracks 1..256, keyframes 1..4096, duration 1..3,600,000 ms.
- Invalid values return `InvalidAnimation`; valid values produce zero warnings.
- No bytes are parsed or converted.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data03_animation_tests.cpp -o /tmp/data03_anim
/tmp/data03_anim anim01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

None introduced.

## Security and architecture

- Header-only internal C++20; no allocation, exception, decoder, file, database or network.

## Rollback

Revert normally; remove the animation header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No real animation decoding/conversion or file validation.
- No audio/composite validation or receipts yet.
- `DATA-03-06`..`-10` remain `PLANNED_BLOCKED`.
- DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-03-05` as `COMPLETED`, manifest `DATA03_05_COMPLETED_REST_BLOCKED`: **657 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 73 `COMPLETED`, 18 approved gates**.
