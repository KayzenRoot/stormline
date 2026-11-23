# NLE-PRPLAN-GFX-01-08 — logical feature-tier evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU FEATURE CLAIM`. **Base:** `0e55096`. **Gate:** [NLE-PRPLAN-GFX-01-08-G6-ACTIVATION](NLE-PRPLAN-GFX-01-08-G6-ACTIVATION.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md). **WO:** [NLE-PRPLAN-GFX-01-08](../work-orders/NLE-PRPLAN-GFX-01-08.md).

## Scope delivered

- `src/stormline/graphics/rhi/rhi_feature.hpp`: supported tier, feature predicate and tier predicate.
- `tests/core/gfx01_feature_tests.cpp`: TIER-01.
- Additive CMake/workflow entries.

No qualification/closeout, native GPU, raytracing, mesh shader, rendering, shader, dependency, ABI or release.

## Implementation notes

- `kSupportedTier` is 1, matching the frozen contract.
- `features_supported` requires a nonzero request, only known `kAllFeatures` bits, and a subset of the available adapter flags.
- `tier_supported` accepts only tier 1; zero, two and maximum values fail closed.
- TIER-01 also exercises existing device init behavior for each supported/unsupported feature and tier, plus capability preservation across loss/recovery.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx01_feature_tests.cpp -o /tmp/gfx01_feature
/tmp/gfx01_feature tier01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- No test or implementation failures after the first compile.
- Local TSan requires ASLR disabled through `setarch -R`; CI already applies this.

## Security and architecture

- Header-only internal C++20; no GPU, driver, allocator, file or network.
- Feature/tier decisions remain logical metadata; no renderer policy or hardware capability is inferred.

## Rollback

Revert normally; remove feature header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No native feature detection, raytracing, mesh shader or hardware qualification.
- No qualification or closeout yet; `GFX-01-09`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-01-08` as `COMPLETED`, manifest `GFX01_08_COMPLETED_REST_BLOCKED`: **626 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 97 `COMPLETED`, 24 approved gates**.
