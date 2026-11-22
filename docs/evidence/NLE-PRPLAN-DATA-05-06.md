# NLE-PRPLAN-DATA-05-06 — manifest fingerprint evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NON-CRYPTOGRAPHIC FINGERPRINT`. **Base:** `b546b76`. **Gate:** [NLE-PRPLAN-DATA-05-06-G6-ACTIVATION](NLE-PRPLAN-DATA-05-06-G6-ACTIVATION.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md). **WO:** [NLE-PRPLAN-DATA-05-06](../work-orders/NLE-PRPLAN-DATA-05-06.md).

## Scope delivered

- `src/stormline/data/bundle/bundle_manifest.hpp`: `fnv1a64`, `verify_chunk`.
- `tests/core/data05_manifest_tests.cpp`: MAN-01.
- Additive CMake/workflow entries.

No signing, trust, patch plan, network, persistence, native I/O, ABI or release.

## Implementation notes

- FNV-1a 64 is non-cryptographic and proves accidental integrity only.
- Verification checks chunk existence, exact length and fingerprint.
- No signature or publisher-authenticity claim.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data05_manifest_tests.cpp -o /tmp/data05_man
/tmp/data05_man man01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

None introduced.

## Security and architecture

- Header-only internal C++20; no cryptography, allocation, file, network or database.

## Rollback

Revert normally; remove manifest header/test and additive CMake/workflow entries.

## Open risks / not claimed

- FNV is not authentication or collision-resistant.
- No patch plan yet.
- `DATA-05-07`..`-09` remain `PLANNED_BLOCKED`.
- DATA-03/DATA-04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-05-06` as `COMPLETED`, manifest `DATA05_06_COMPLETED_REST_BLOCKED`: **638 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 88 `COMPLETED`, 22 approved gates**.
