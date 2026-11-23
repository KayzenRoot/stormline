# NLE-PRPLAN-GFX-02-04 — logical reflection evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE COMPILER, LAYOUT OR GPU`. **Base:** `c048ac8`. **Gate:** [NLE-PRPLAN-GFX-02-04-G6-ACTIVATION](NLE-PRPLAN-GFX-02-04-G6-ACTIVATION.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-02-04](../work-orders/NLE-PRPLAN-GFX-02-04.md).

## Scope delivered

- `src/stormline/graphics/shader/shader_reflection.hpp`: `reflect_shader`.
- `tests/core/gfx02_reflection_tests.cpp`: REF-01.
- Additive CMake/workflow entries.

No variants, cache, incremental qualification, native compiler/layout, GPU, dependency, ABI or release.

## Implementation notes

- Validates module name, stage, binding count, names, unique names, types and kinds before writing output.
- Assigns slots deterministically from 0 per binding kind in declaration order.
- Emits logical size/alignment metadata: float/int/uint/bool 4/4, vec2 8/8, vec3 12/16, vec4 16/16, mat3 48/16, mat4 64/16.
- Enforces 32 inputs, 32 outputs and 32 uniforms; invalid IR fails closed.
- Preserves module name, stage, binding count and source fingerprint.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx02_reflection_tests.cpp -o /tmp/gfx02_reflect
/tmp/gfx02_reflect ref01
```

Exited 0. ASan/UBSan rebuild exited 0. TSan rebuild ran with `setarch -R` and exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- REF-01 first detected that per-kind counts were not incremented during validation, so the capacity oracle did not fire. The validation pass now counts and limits each kind before reflection assignment.
- The test needed `<string>` for `std::to_string`; include corrected.

## Security and architecture

- Header-only internal C++20; no compiler process, native layout, driver, GPU, allocator, file or network.
- Reflection is logical metadata only and is not a native pipeline layout or ABI.

## Rollback

Revert normally; remove the reflection header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No variants, cache or incremental invalidation yet.
- No native shader compilation, target layout, pipeline or GPU execution.
- `GFX-02-05`..`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-02-04` as `COMPLETED`, manifest `GFX02_04_COMPLETED_REST_BLOCKED`: **621 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 101 `COMPLETED`, 26 approved gates**.
