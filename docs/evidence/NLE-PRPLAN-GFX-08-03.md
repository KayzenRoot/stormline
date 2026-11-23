# NLE-PRPLAN-GFX-08-03 — Particle graph/emitter evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PARTICLE SIMULATION`. **Base:** `357114d`. **Gate:** [NLE-PRPLAN-GFX-08-03-G6-ACTIVATION](NLE-PRPLAN-GFX-08-03-G6-ACTIVATION.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-08-03](../work-orders/NLE-PRPLAN-GFX-08-03.md). **PR:** #775.

## Scope delivered

- `src/stormline/graphics/vfx/vfx_types.hpp`: capacities, error/kind/port/policy enums and diagnostic.
- `src/stormline/graphics/vfx/graph_plan.hpp`: graph descriptor, plan and `validate_graph`.
- `src/stormline/graphics/vfx/emitter_plan.hpp`: emitter/budget descriptors and `plan_emitter`.
- `tests/core/gfx08_particle_tests.cpp`: VFX-01 and SPAWN-01.
- Additive CMake target/tests and TSan target.
- No particle simulation, PRNG stream, GPU, compute, shader, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Graph validation checks IDs/revisions, fixed node/edge caps, unique IDs, allowlisted kinds/ports, edge endpoints, self/duplicate edges, port-type agreement and cycles; a topological order is returned.
- Emitter validation checks IDs/revisions, simulation policy, finite positive lifetime, budget caps, checked spawn+burst overflow and per-tick/alive limits.
- Errors are typed and plans reset to defaults on failure.
- No particle state, spawn, simulation step or draw exists.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx08_particle_tests.cpp -o /tmp/gfx08_particle
/tmp/gfx08_particle vfx01
/tmp/gfx08_particle spawn01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/gfx08_particle_tests.cpp -o /tmp/gfx08_particle_san
/tmp/gfx08_particle_san vfx01
/tmp/gfx08_particle_san spawn01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/gfx08_particle_tests.cpp -o /tmp/gfx08_particle_tsan
setarch "$(uname -m)" -R /tmp/gfx08_particle_tsan vfx01
setarch "$(uname -m)" -R /tmp/gfx08_particle_tsan spawn01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- No implementation defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no particle, image or visual result is claimed.

## Rollback

Revert normally; remove the three headers/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No particle simulation, GPU/compute, sort/OIT, rendering, hardware, performance, ABI or release.
- `GFX-08-04`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-08-03` as `COMPLETED`, manifest `GFX08_03_COMPLETED_REST_BLOCKED`: **564 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 146 `COMPLETED`, 38 approved gates**.
