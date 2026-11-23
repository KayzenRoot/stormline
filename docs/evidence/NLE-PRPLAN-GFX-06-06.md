# NLE-PRPLAN-GFX-06-06 — Probe metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PROBE BAKE OR GPU`. **Base:** `277b006`. **Gate:** [NLE-PRPLAN-GFX-06-06-G6-ACTIVATION](NLE-PRPLAN-GFX-06-06-G6-ACTIVATION.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-06-06](../work-orders/NLE-PRPLAN-GFX-06-06.md).

## Scope delivered

- `src/stormline/graphics/lighting/probe_plan.hpp`: probe descriptor/set/plan and `plan_probes`.
- `tests/core/gfx06_probe_tests.cpp`: PRB-01.
- Additive CMake test and TSan target.
- No probe bake, SH evaluation, GPU upload, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- IDs/revisions are nonzero/unique; generation must match the expected scene.
- Origin and spacing are finite; spacing is positive; each cell count is positive.
- Checked cell product must not exceed `kMaxProbeCells`.
- Output IDs are sorted ascending; invalid input zeroes the plan.
- No probe is baked, relocated or sampled.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx06_probe_tests.cpp -o /tmp/gfx06_probe
/tmp/gfx06_probe prb01
```

Exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no bake, SH or visual result is claimed.

## Rollback

Revert normally; remove the probe header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No reflections or volumetrics yet.
- No probe bake, GPU, rendering, hardware, performance, ABI or release.
- `GFX-06-07`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-06-06` as `COMPLETED`, manifest `GFX06_06_COMPLETED_REST_BLOCKED`: **581 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 133 `COMPLETED`, 34 approved gates**.
