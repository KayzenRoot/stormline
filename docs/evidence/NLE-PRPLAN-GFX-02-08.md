# NLE-PRPLAN-GFX-02-08 — logical shader pipeline qualification evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU, COMPILER OR HARDWARE QUALIFICATION`. **Base:** `bfa295d`. **Gate:** [NLE-PRPLAN-GFX-02-08-G6-ACTIVATION](NLE-PRPLAN-GFX-02-08-G6-ACTIVATION.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-02-08](../work-orders/NLE-PRPLAN-GFX-02-08.md).

## Scope delivered

- `tests/core/gfx02_shader_qualification_tests.cpp`: QLF-S01..S04.
- Additive CMake target/tests and workflow TSan target.

No closeout, native compiler, GPU, hardware, rendering, performance, ABI or release.

## Qualification notes

- QLF-S01 integrates source parsing, IR, reflection slots, variant planning, cache key/put/get, dependency fingerprint and incremental decision.
- QLF-S02 repeats the integrated sequence and compares source/reflection/variant/cache/dependency values.
- QLF-S03 exercises typed failures for empty/token source, invalid reflection, variant recipe/limit, cache mismatch/full, dependency and incremental, each followed by a valid operation.
- QLF-S04 performs 10,000 parse accept/reject cycles, 10,000 reflections, 10,000 variant plans, 10,000 idempotent cache puts and 10,000 incremental plans with bounded capacities.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx02_shader_qualification_tests.cpp -o /tmp/gfx02_qual
/tmp/gfx02_qual qlf01
/tmp/gfx02_qual qlf02
/tmp/gfx02_qual qlf03
/tmp/gfx02_qual qlf04
```

All exited 0. ASan/UBSan rebuild exited 0 for all four modes. TSan rebuild ran with `setarch -R` and exited 0 for all four modes.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- QLF-S03 filled the cache without clearing its existing entry, exceeding capacity early. A `clear` before the fill fixture corrected the test. No implementation defect.

## Security and architecture

- Test-only C++20; no compiler process, driver, GPU, persistence, file or network.
- Qualification is logical and CI-only; no hardware, driver, visual or performance behavior is asserted.

## Rollback

Revert normally; remove the qualification test and additive CMake/workflow entries.

## Open risks / not claimed

- No native shader compilation, GPU artifact, pipeline, rendering, hardware or performance.
- No persistence, file watching, remote cache, ABI or release.
- `GFX-02-09` closeout remains blocked until its gate.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-02-08` as `COMPLETED`, manifest `GFX02_08_COMPLETED_REST_BLOCKED`: **617 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 105 `COMPLETED`, 26 approved gates**.
