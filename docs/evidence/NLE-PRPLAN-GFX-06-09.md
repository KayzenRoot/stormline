# NLE-PRPLAN-GFX-06-09 — Integrated lighting qualification evidence

**Status:** `QUALIFICATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU, SHADOW MAP OR HARDWARE`. **Base:** `08c48a0`. **Gate:** [NLE-PRPLAN-GFX-06-09-G6-ACTIVATION](NLE-PRPLAN-GFX-06-09-G6-ACTIVATION.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-06-09](../work-orders/NLE-PRPLAN-GFX-06-09.md).

## Scope delivered

- `tests/core/gfx06_lighting_qualification_tests.cpp`: QLF-G601..G604.
- Additive CMake target/tests and workflow TSan target.
- No closeout, native GPU, shadow map, ray tracing, GI/probe bake, SSR, froxel, rendering, driver/hardware, visual golden, performance, ABI or release.

## Qualification notes

- QLF-G601 integrates lights, cascades, shadow pages, GI fallback, probes, reflections and volumetric budget; asserts counts, ordering, fallback flags and step totals.
- QLF-G602 repeats the pipeline and compares every output field.
- QLF-G603 exercises duplicate light, invalid cascade, duplicate page, unavailable GI, stale probe, offscreen reflection and volumetric budget, each followed by a valid operation.
- QLF-G604 performs 10,000 integrated pipelines and 10,000 invalid light rejects under fixed capacities.

These are logical/CI oracles; they do not qualify a GPU, driver, hardware, visual output or performance.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx06_lighting_qualification_tests.cpp -o /tmp/gfx06_qual
/tmp/gfx06_qual qlf01
/tmp/gfx06_qual qlf02
/tmp/gfx06_qual qlf03
/tmp/gfx06_qual qlf04
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Test-only C++20; no GPU, shadow map, I/O, file or network.
- Qualification is logical and CI-only; no hardware, driver, visual or performance behavior is asserted.

## Rollback

Revert normally; remove the qualification test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No native GPU, shadow map, ray tracing, GI/probe bake, SSR, froxel, rendering, hardware, performance or visual golden.
- `GFX-06-10` closeout remains blocked until its gate.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-06-09` as `COMPLETED`, manifest `GFX06_09_COMPLETED_REST_BLOCKED`: **578 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 136 `COMPLETED`, 34 approved gates**.
