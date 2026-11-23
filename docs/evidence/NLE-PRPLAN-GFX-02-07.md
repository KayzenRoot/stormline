# NLE-PRPLAN-GFX-02-07 — dependency-revision incremental evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO FILE WATCHING OR PERSISTENCE`. **Base:** `1163967`. **Gate:** [NLE-PRPLAN-GFX-02-07-G6-ACTIVATION](NLE-PRPLAN-GFX-02-07-G6-ACTIVATION.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-02-07](../work-orders/NLE-PRPLAN-GFX-02-07.md).

## Scope delivered

- `src/stormline/graphics/shader/shader_incremental.hpp`: dependency fingerprint and incremental plan.
- `tests/core/gfx02_incremental_tests.cpp`: INC-01.
- Additive CMake/workflow entries.

No file watching, persistence, qualification, native compiler, GPU, dependency manager, ABI or release.

## Implementation notes

- Dependencies are 1..32 opaque `{id, revision}` pairs with nonzero values and unique IDs.
- Fingerprints canonicalize entries by ascending ID, making input order irrelevant.
- Rebuild is required when the previous dependency fingerprint is zero/different or the previous cache key is zero.
- The plan returns the current fingerprint; no filesystem, process or network access occurs.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx02_incremental_tests.cpp -o /tmp/gfx02_inc
/tmp/gfx02_inc inc01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- INC-01 initially reused the fingerprint output variable for invalid cases, resetting the expected baseline before the initial plan assertion. A preserved expected fingerprint corrected the fixture.

## Security and architecture

- Header-only internal C++20; no file watching, persistence, compiler process, driver, GPU, allocator, file or network.
- Dependency IDs are opaque metadata; no DATA-02 identity or external package manager is claimed.

## Rollback

Revert normally; remove the incremental header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No file watching, persistence, journal, automatic dependency discovery or crash recovery.
- No native shader compilation, pipeline or GPU execution.
- `GFX-02-08`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-02-07` as `COMPLETED`, manifest `GFX02_07_COMPLETED_REST_BLOCKED`: **618 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 104 `COMPLETED`, 26 approved gates**.
