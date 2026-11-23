# NLE-PRPLAN-TWO-01-08 — 2D light request evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO LIGHTING EXECUTION`. **Base:** `5939153`. **Gate:** [NLE-PRPLAN-TWO-01-08-G6-ACTIVATION](NLE-PRPLAN-TWO-01-08-G6-ACTIVATION.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-01-08](../work-orders/NLE-PRPLAN-TWO-01-08.md). **PR:** #802.

## Scope delivered

- `src/stormline/graphics/canvas2d/light_plan.hpp`: descriptors/plan and `plan_light`.
- `tests/core/two01_light_tests.cpp`: LGT-01.
- Additive CMake test and TSan target.
- No light, shadow, normal map, scissor mask, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Light ID/revision/layer must be nonzero; falloff must be declared.
- Intensity is finite nonnegative; radius finite positive; color channels finite in `[0,1]`.
- Budget must declare at least one light and a finite nonnegative intensity cap.
- Intensity above the cap clamps with `clamped=true`; GFX-06 owns actual lights and shadows.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two01_light_tests.cpp -o /tmp/two01_light
/tmp/two01_light lgt01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer -Isrc tests/core/two01_light_tests.cpp -o /tmp/two01_light_san
/tmp/two01_light_san lgt01
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=thread -fno-omit-frame-pointer -Isrc tests/core/two01_light_tests.cpp -o /tmp/two01_light_tsan
setarch "$(uname -m)" -R /tmp/two01_light_tsan lgt01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no light or visual result is claimed.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No lighting/shadow execution, GPU, render, hardware, performance, ABI or release.
- `TWO-01-09`/`-10` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `TWO-01-08` as `COMPLETED`, manifest `TWO01_08_COMPLETED_REST_BLOCKED`: **549 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 159 `COMPLETED`, 40 approved gates**.
