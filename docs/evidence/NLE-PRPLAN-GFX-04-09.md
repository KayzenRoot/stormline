# NLE-PRPLAN-GFX-04-09 — geometry qualification evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU OR HARDWARE QUALIFICATION`. **Base:** `8f442e6`. **Gate:** [NLE-PRPLAN-GFX-04-09-G6-ACTIVATION](NLE-PRPLAN-GFX-04-09-G6-ACTIVATION.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-04-09](../work-orders/NLE-PRPLAN-GFX-04-09.md).

## Scope delivered

- `tests/core/gfx04_geometry_qualification_tests.cpp`: QLF-G401..G404.
- Additive CMake target/tests and workflow TSan target.

No closeout, native GPU, mesh library, I/O, submission, rendering, performance, ABI or release.

## Qualification notes

- QLF-G401 integrates instances/batches, culling, LOD/HLOD, stream planning, vegetation classification and geometry budget.
- QLF-G402 repeats the integrated pipeline and compares batch/visibility/LOD/stream/vegetation/budget values.
- QLF-G403 exercises invalid instance, generation mismatch, invalid LOD, HLOD cycle, unverified chunk, invalid vegetation and overcommit, each followed by a valid operation.
- QLF-G404 performs 10,000 integrated pipelines and 10,000 invalid rejects with bounded capacities.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx04_geometry_qualification_tests.cpp -o /tmp/gfx04_qual
/tmp/gfx04_qual qlf01
/tmp/gfx04_qual qlf02
/tmp/gfx04_qual qlf03
/tmp/gfx04_qual qlf04
```

All exited 0. ASan/UBSan rebuild exited 0 for all four modes. TSan rebuild ran with `setarch -R` and exited 0 for all four modes.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- An unused diagnostic variable in QLF-G404 was removed after the first compile warning.

## Security and architecture

- Test-only C++20; no GPU, mesh library, I/O, file or network.
- Qualification is logical and CI-only; no hardware, driver, visual or performance behavior is asserted.

## Rollback

Revert normally; remove the qualification test and additive CMake/workflow entries.

## Open risks / not claimed

- No native GPU, mesh optimization/codec, streaming I/O, hardware or performance.
- No physical scene, visual golden or driver validation.
- `GFX-04-10` closeout remains blocked until its gate.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-04-09` as `COMPLETED`, manifest `GFX04_09_COMPLETED_REST_BLOCKED`: **598 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 120 `COMPLETED`, 30 approved gates**.
