# NLE-PRPLAN-GFX-04-06 — verified mesh stream planning evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE I/O OR NETWORK`. **Base:** `07c3f9c`. **Gate:** [NLE-PRPLAN-GFX-04-06-G6-ACTIVATION](NLE-PRPLAN-GFX-04-06-G6-ACTIVATION.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-04-06](../work-orders/NLE-PRPLAN-GFX-04-06.md).

## Scope delivered

- `src/stormline/graphics/geometry/geometry_stream.hpp`: `plan_stream`.
- `tests/core/gfx04_stream_tests.cpp`: STR-01.
- Additive CMake/workflow entries.

No vegetation, geometry budget, qualification, native I/O/network, codec, GPU, submission, dependency, ABI or release.

## Implementation notes

- Chunk IDs are unique/nonzero; mesh IDs nonzero; LOD 0..7; bytes positive; unverified chunks fail closed.
- Resident IDs must exist and be unique; resident chunks are skipped.
- Candidates sort by mesh ID, LOD level and chunk ID.
- Requests are admitted until the byte budget; remaining work sets `truncated=true`.
- No bytes are fetched, decoded, uploaded or persisted.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx04_stream_tests.cpp -o /tmp/gfx04_str
/tmp/gfx04_str str01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- No implementation defect after the first compile.

## Security and architecture

- Header-only internal C++20; no I/O, network, codec, GPU, file or persistence.
- Requests reference caller-provided verified metadata only; no trust or signature is claimed.

## Rollback

Revert normally; remove the stream header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No actual streaming, DATA-05 verification, decode, upload or residency.
- No vegetation/budget yet.
- `GFX-04-07`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-04-06` as `COMPLETED`, manifest `GFX04_06_COMPLETED_REST_BLOCKED`: **601 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 117 `COMPLETED`, 30 approved gates**.
