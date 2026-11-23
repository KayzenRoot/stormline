# NLE-PRPLAN-TWO-01-04 — Atlas metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ATLAS PACKING OR UPLOAD`. **Base:** `1806b15`. **Gate:** [NLE-PRPLAN-TWO-01-04-G6-ACTIVATION](NLE-PRPLAN-TWO-01-04-G6-ACTIVATION.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-01-04](../work-orders/NLE-PRPLAN-TWO-01-04.md). **PR:** #794.

## Scope delivered

- `src/stormline/graphics/canvas2d/atlas_plan.hpp`: descriptors/plan and `plan_atlas`.
- `tests/core/two01_atlas_tests.cpp`: ATL-01.
- Additive CMake test and TSan target.
- No atlas packing, upload, sampler, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Atlas ID/revision must be nonzero; dimensions positive; mip count `1..16`.
- Region count is bounded; region IDs/revisions nonzero and unique.
- Region extents are checked in 64-bit against atlas bounds.
- No atlas is packed, uploaded or sampled.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two01_atlas_tests.cpp -o /tmp/two01_atlas
/tmp/two01_atlas atl01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/two01_atlas_tests.cpp -o /tmp/two01_atlas_san
/tmp/two01_atlas_san atl01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/two01_atlas_tests.cpp -o /tmp/two01_atlas_tsan
setarch "$(uname -m)" -R /tmp/two01_atlas_tsan atl01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no atlas or visual result is claimed.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No atlas packing/upload, GPU, render, hardware, performance, ABI or release.
- `TWO-01-05`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `TWO-01-04` as `COMPLETED`, manifest `TWO01_04_COMPLETED_REST_BLOCKED`: **553 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 155 `COMPLETED`, 40 approved gates**.
