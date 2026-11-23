# NLE-PRPLAN-GFX-05-03 — Logical PBR material evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO GPU, CODEC OR PIXEL`. **Base:** `f77413e`. **Gate:** [NLE-PRPLAN-GFX-05-03-G6-ACTIVATION](NLE-PRPLAN-GFX-05-03-G6-ACTIVATION.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-05-03](../work-orders/NLE-PRPLAN-GFX-05-03.md).

## Scope delivered

- `src/stormline/graphics/material/material_types.hpp`: bounded enums, capacities, error and PBR/material structures.
- `src/stormline/graphics/material/pbr_material.hpp`: `material_error_name`, `add_material`, `validate_materials`.
- `tests/core/gfx05_material_tests.cpp`: PBR-01.
- Additive CMake interface/test entries and TSan target.
- No texture upload, codec/decoder, GPU, shader compiler, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Material IDs and revisions must be nonzero; IDs are unique in `MaterialSet`.
- All PBR parameters must be finite. Base color, emissive, metallic, roughness, occlusion and alpha cutoff are in `[0,1]`; `normal_scale` is `>0`.
- `Mask` requires a nonzero cutoff. Unknown model/alpha enum values fail closed.
- `add_material` is atomic on capacity, duplicate, structural or parameter failure.
- `validate_materials` reports the first offending index and material ID; no input is modified.
- No pixel is read, decoded, sampled, blended or rendered.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx05_material_tests.cpp -o /tmp/gfx05_mat
/tmp/gfx05_mat pbr01
g++ ... -fsanitize=address,undefined ... -o /tmp/gfx05_mat_asan
/tmp/gfx05_mat_asan pbr01
g++ ... -fsanitize=thread ... -o /tmp/gfx05_mat_tsan
setarch "$(uname -m)" -R env TSAN_OPTIONS=halt_on_error=1 /tmp/gfx05_mat_tsan pbr01
```

All exited 0. CMake is unavailable locally; the additive target/test wiring is validated by the exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- The first heredoc write truncated the tail of `pbr_material.hpp`; the incomplete line was removed and the remaining `validate_materials` body was appended. The first strict compile then passed.
- No runtime or sanitizer defect was observed.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU, codec, thread or global state.
- Parameters are metadata; no BRDF evaluation or visual behavior is claimed.

## Rollback

Revert normally; remove the material headers/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No textures, virtual pages, mips, samplers, decals or transparency yet.
- No native GPU, texture codec, upload, rendering, hardware, performance, ABI or release.
- `GFX-05-04`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-05-03` as `COMPLETED`, manifest `GFX05_03_COMPLETED_REST_BLOCKED`: **594 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 122 `COMPLETED`, 32 approved gates**.
