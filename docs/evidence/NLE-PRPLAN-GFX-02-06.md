# NLE-PRPLAN-GFX-02-06 — in-memory cache identity evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PERSISTENCE OR NATIVE CACHE`. **Base:** `02636b3`. **Gate:** [NLE-PRPLAN-GFX-02-06-G6-ACTIVATION](NLE-PRPLAN-GFX-02-06-G6-ACTIVATION.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-02-06](../work-orders/NLE-PRPLAN-GFX-02-06.md).

## Scope delivered

- `src/stormline/graphics/shader/shader_cache.hpp`: `make_cache_key` and `ShaderCache`.
- `tests/core/gfx02_cache_tests.cpp`: CAC-01.
- Additive CMake/workflow entries.

No persistence, incremental, qualification, native compiler, driver cache, GPU, dependency, ABI or release.

## Implementation notes

- Cache keys hash the variant fingerprint, recipe, switch mask, stage and dependency fingerprint with FNV-1a 64 over a fixed big-endian field encoding.
- Key and payload fingerprints are nonzero; zero is reserved as invalid/empty.
- Cache capacity is 64 entries; duplicate key+payload is idempotent; same key with a different payload returns `CacheMismatch`.
- Lookup returns `CacheMiss` without side effects; `clear` resets all entries.
- No allocation, persistence, file, process, driver or GPU access.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx02_cache_tests.cpp -o /tmp/gfx02_cache
/tmp/gfx02_cache cac01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- The first cache-key byte encoder used decrementing shift loops; rewritten as explicit byte shifts for clarity and to avoid analyzer concerns. No behavioral defect observed.

## Security and architecture

- Header-only internal C++20; no persistence, compiler process, driver, GPU, allocator, file or network.
- FNV-1a 64 is accidental identity only, not authentication, trust or cache integrity.

## Rollback

Revert normally; remove the cache header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No persistence, eviction policy beyond capacity, concurrency or cross-process cache.
- No incremental invalidation yet.
- `GFX-02-07`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-02-06` as `COMPLETED`, manifest `GFX02_06_COMPLETED_REST_BLOCKED`: **619 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 103 `COMPLETED`, 26 approved gates**.
