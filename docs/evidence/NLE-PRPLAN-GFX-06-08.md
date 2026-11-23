# NLE-PRPLAN-GFX-06-08 — Volumetric metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO FROXEL BUFFER OR GPU`. **Base:** `d11287e`. **Gate:** [NLE-PRPLAN-GFX-06-08-G6-ACTIVATION](NLE-PRPLAN-GFX-06-08-G6-ACTIVATION.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-06-08](../work-orders/NLE-PRPLAN-GFX-06-08.md).

## Scope delivered

- `src/stormline/graphics/lighting/volumetric_plan.hpp`: descriptor/set/plan and `plan_volumetrics`.
- `tests/core/gfx06_volumetric_tests.cpp`: VOL-01.
- Additive CMake test and TSan target.
- No froxel buffer, shadowed fog, particles, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- IDs/revisions are nonzero/unique; density/extinction/scattering are finite nonnegative.
- Anisotropy is in `[-1,1]`; tier is declared; step count is positive.
- Checked total steps must not exceed `max_steps`; otherwise `VolumetricBudgetExceeded` with no partial plan.
- Output IDs are sorted ascending.
- No volume is integrated, shadowed or rendered.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx06_volumetric_tests.cpp -o /tmp/gfx06_vol
/tmp/gfx06_vol vol01
```

Exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- VOL-01 initially checked a stale diagnostic index after a capacity failure; the oracle was corrected to assert the capacity error code.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Budget metadata only; no froxel, fog or visual result is claimed.

## Rollback

Revert normally; remove the volumetric header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No qualification/closeout yet.
- No froxel, shadowed fog, particles, GPU, rendering, hardware, performance, ABI or release.
- `GFX-06-09`/`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-06-08` as `COMPLETED`, manifest `GFX06_08_COMPLETED_REST_BLOCKED`: **579 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 135 `COMPLETED`, 34 approved gates**.
