# NLE-PRPLAN-GFX-08-09 — Integrated VFX qualification evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / LOGICAL QUALIFICATION ONLY`. **Base:** `352ca4c`. **Gate:** [NLE-PRPLAN-GFX-08-09-G6-ACTIVATION](NLE-PRPLAN-GFX-08-09-G6-ACTIVATION.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-08-09](../work-orders/NLE-PRPLAN-GFX-08-09.md). **PR:** #787.

## Scope delivered

- `tests/core/gfx08_vfx_qualification_tests.cpp`: QLF-G801..G804.
- Additive CMake target/tests and TSan target.
- No particle simulation, GPU, compute, sort/OIT, volume, renderer, dependency, ABI, release, hardware or performance claim.

## Qualification results

- **QLF-G801:** one pipeline traverses graph, emitter/spawn, ribbon, trail, blend, density and pool; plan values are asserted together.
- **QLF-G802:** two full pipelines plus 100 repeats produce identical plans, counts and flags.
- **QLF-G803:** graph cycle, spawn cap, ribbon vertex cap, unordered trail ages, blend depth mismatch, invalid density and pool exhaustion each return typed errors; a valid operation succeeds immediately after each failure.
- **QLF-G804:** 10,000 over-cap graph/pool attempts stay bounded and reset, followed by 10,000 complete pipeline runs.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx08_vfx_qualification_tests.cpp -o /tmp/gfx08_qlf
/tmp/gfx08_qlf qlfg801..qlfg804
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/gfx08_vfx_qualification_tests.cpp -o /tmp/gfx08_qlf_san
/tmp/gfx08_qlf_san qlfg801..qlfg804
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/gfx08_vfx_qualification_tests.cpp -o /tmp/gfx08_qlf_tsan
setarch "$(uname -m)" -R /tmp/gfx08_qlf_tsan qlfg801..qlfg804
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Test-only translation unit; header-only production metadata unchanged.
- No allocation, exception, file, network, GPU or global production state.
- Logical qualification only; no image, particle, signal, kernel, SDK or hardware result is claimed.

## Rollback

Revert normally; remove the qualification test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No particle simulation, GPU/compute, sort/OIT, volume, rendering, hardware, performance, ABI or release.
- `GFX-08-10` remains blocked until its gate.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-08-09` as `COMPLETED`, manifest `GFX08_09_COMPLETED_REST_BLOCKED`: **558 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 152 `COMPLETED`, 38 approved gates**.
