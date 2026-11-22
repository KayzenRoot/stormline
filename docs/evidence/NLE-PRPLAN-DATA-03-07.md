# NLE-PRPLAN-DATA-03-07 — composite validation evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO DECODER OR ABI CLAIM`. **Base:** `5a70ae6`. **Gate:** [NLE-PRPLAN-DATA-03-07-G6-ACTIVATION](NLE-PRPLAN-DATA-03-07-G6-ACTIVATION.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md). **WO:** [NLE-PRPLAN-DATA-03-07](../work-orders/NLE-PRPLAN-DATA-03-07.md).

## Scope delivered

- `src/stormline/data/import/import_validation.hpp`: `ArtifactMetadata`, `ValidationResult`, `validate_artifact`.
- `tests/core/data03_validation_tests.cpp`: VAL-01.
- Additive CMake/workflow entries.

No receipts, persistence, decoder, native I/O, network, ABI or release.

## Implementation notes

- Texture/Animation/Audio dispatch to the frozen validators; Mesh/Metadata are valid without extra rules; Unknown returns `InvalidArgument`.
- Result carries status, typed error and warning count.
- No bytes are parsed or converted.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data03_validation_tests.cpp -o /tmp/data03_val
/tmp/data03_val val01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

None introduced.

## Security and architecture

- Header-only internal C++20; no allocation, exception, decoder, file, database or network.

## Rollback

Revert normally; remove the validation header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No real decoding/conversion; no receipts yet.
- `DATA-03-08`..`-10` remain `PLANNED_BLOCKED`.
- DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-03-07` as `COMPLETED`, manifest `DATA03_07_COMPLETED_REST_BLOCKED`: **655 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 75 `COMPLETED`, 18 approved gates**.
