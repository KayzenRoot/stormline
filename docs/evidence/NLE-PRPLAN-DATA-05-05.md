# NLE-PRPLAN-DATA-05-05 — streaming evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NETWORK OR PERSISTENCE CLAIM`. **Base:** `d3ac11a`. **Gate:** [NLE-PRPLAN-DATA-05-05-G6-ACTIVATION](NLE-PRPLAN-DATA-05-05-G6-ACTIVATION.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md). **WO:** [NLE-PRPLAN-DATA-05-05](../work-orders/NLE-PRPLAN-DATA-05-05.md).

## Scope delivered

- `src/stormline/data/bundle/stream_window.hpp`: manifest entries/table, chunk store, stream window.
- `tests/core/data05_stream_tests.cpp`: STR-01.
- Additive CMake/workflow entries.

No fingerprint verification, patch plan, network, persistence, native I/O, ABI or release.

## Implementation notes

- Manifest entries have checked offset+length, non-overlap, unique chunk ID and 4096-byte total cap.
- Store holds 64 chunks of 256 bytes; duplicate/missing/buffer errors typed.
- Window binds generation, copies/validates store length, enforces budget, idempotent request.
- Generation change invalidates an existing window with `StaleGeneration`.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data05_stream_tests.cpp -o /tmp/data05_stream
/tmp/data05_stream str01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

None introduced.

## Security and architecture

- Header-only internal C++20; fixed arrays, no allocation, file, network or database.

## Rollback

Revert normally; remove stream header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No fingerprint verification yet; no network/persistence streaming.
- `DATA-05-06`..`-09` remain `PLANNED_BLOCKED`.
- DATA-03/DATA-04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-05-05` as `COMPLETED`, manifest `DATA05_05_COMPLETED_REST_BLOCKED`: **639 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 87 `COMPLETED`, 22 approved gates**.
