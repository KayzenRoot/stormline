# NLE-PRPLAN-GFX-05-06 — Sampler and filter profile evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO GPU SAMPLER OR DRIVER`. **Base:** `fca8bbe`. **Gate:** [NLE-PRPLAN-GFX-05-06-G6-ACTIVATION](NLE-PRPLAN-GFX-05-06-G6-ACTIVATION.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-05-06](../work-orders/NLE-PRPLAN-GFX-05-06.md).

## Scope delivered

- `src/stormline/graphics/material/texture_sampler.hpp`: `SamplerProfile`, `validate_sampler`.
- `tests/core/gfx05_sampler_tests.cpp`: SMP-01.
- Additive CMake test entry and TSan target.
- No GPU sampler object, driver, upload, rendering, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Format, min/mag/mip filters and wrap modes must be declared enum values.
- LOD bias/min/max are finite and within `[-16,16]`; `lod_min <= lod_max`.
- Anisotropy is a power of two in `[1,16]`.
- `compare=true` requires `Depth32Float`.
- Validation is pure metadata; no sampler is created, bound or executed.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx05_sampler_tests.cpp -o /tmp/gfx05_smp
/tmp/gfx05_smp smp01
g++ ... -fsanitize=address,undefined ... -o /tmp/gfx05_smp_asan
/tmp/gfx05_smp_asan smp01
g++ ... -fsanitize=thread ... -o /tmp/gfx05_smp_tsan
setarch "$(uname -m)" -R env TSAN_OPTIONS=halt_on_error=1 /tmp/gfx05_smp_tsan smp01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU, driver or global state.
- Sampler validation is metadata; no filtering behavior is claimed.

## Rollback

Revert normally; remove the sampler header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No decals or transparency yet.
- No GPU sampler, driver, upload, rendering, hardware, performance, ABI or release.
- `GFX-05-07`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-05-06` as `COMPLETED`, manifest `GFX05_06_COMPLETED_REST_BLOCKED`: **591 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 125 `COMPLETED`, 32 approved gates**.
