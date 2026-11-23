# NLE-PRPLAN-TWO-01-03 — Sprite draw metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO SPRITE DRAW`. **Base:** `cd656e9`. **Gate:** [NLE-PRPLAN-TWO-01-03-G6-ACTIVATION](NLE-PRPLAN-TWO-01-03-G6-ACTIVATION.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-01-03](../work-orders/NLE-PRPLAN-TWO-01-03.md). **PR:** #792.

## Scope delivered

- `src/stormline/graphics/canvas2d/canvas_types.hpp`: capacities, errors, modes, diagnostic.
- `src/stormline/graphics/canvas2d/sprite_plan.hpp`: descriptor/plan and `plan_sprite`.
- `tests/core/two01_sprite_tests.cpp`: SPR-01.
- Additive CMake target/test and TSan target.
- No sprite instance, vertex, buffer, atlas upload, sampler, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Sprite/asset/atlas/layer IDs and revisions must be nonzero.
- Region dimensions must be positive; pivot and tint must be finite; tint channels are bounded to `[0,1]`.
- Plans copy stable IDs and mark visibility; no draw or instance exists.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two01_sprite_tests.cpp -o /tmp/two01_sprite
/tmp/two01_sprite spr01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/two01_sprite_tests.cpp -o /tmp/two01_sprite_san
/tmp/two01_sprite_san spr01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/two01_sprite_tests.cpp -o /tmp/two01_sprite_tsan
setarch "$(uname -m)" -R /tmp/two01_sprite_tsan spr01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no sprite or visual result is claimed.

## Rollback

Revert normally; remove the two headers/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No sprite draw, batching, atlas upload, GPU, render, hardware, performance, ABI or release.
- `TWO-01-04`..`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `TWO-01-03` as `COMPLETED`, manifest `TWO01_03_COMPLETED_REST_BLOCKED`: **554 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 154 `COMPLETED`, 40 approved gates**.
