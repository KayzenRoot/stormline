# NLE-PRPLAN-GFX-02-05 — deterministic variant evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE COMPILER OR PIPELINE SPECIALIZATION`. **Base:** `72e6a0c`. **Gate:** [NLE-PRPLAN-GFX-02-05-G6-ACTIVATION](NLE-PRPLAN-GFX-02-05-G6-ACTIVATION.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-02-05](../work-orders/NLE-PRPLAN-GFX-02-05.md).

## Scope delivered

- `src/stormline/graphics/shader/shader_variant.hpp`: `plan_variants`.
- `tests/core/gfx02_variant_tests.cpp`: VAR-01.
- Additive CMake/workflow entries.

No cache, incremental, qualification, native compiler, pipeline specialization, GPU, dependency, ABI or release.

## Implementation notes

- Requires nonzero recipe version, at most 16 static switches, and 1..64 maximum variants.
- Enumerates masks from 0 to `2^switch_count - 1` in ascending order.
- Each key carries the IR source fingerprint, recipe version, switch mask and stage.
- Rejects combinations beyond the maximum with `VariantLimit`; structural input errors use `InvalidArgument`.
- The plan is logical metadata; no shader is compiled or specialized.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx02_variant_tests.cpp -o /tmp/gfx02_variant
/tmp/gfx02_variant var01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- VAR-01 initially compared a repeat plan against an output that later invalid calls had reset; the test now retains an explicit expected plan. No implementation defect.

## Security and architecture

- Header-only internal C++20; no compiler process, pipeline specialization, driver, GPU, allocator, file or network.
- Variant keys are metadata only and do not guarantee byte-identical compiled artifacts.

## Rollback

Revert normally; remove the variant header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No cache or incremental invalidation yet.
- No native shader compilation, pipeline specialization, GPU artifact or hardware behavior.
- `GFX-02-06`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-02-05` as `COMPLETED`, manifest `GFX02_05_COMPLETED_REST_BLOCKED`: **620 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 102 `COMPLETED`, 26 approved gates**.
