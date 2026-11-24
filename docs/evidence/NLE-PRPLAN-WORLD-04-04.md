# NLE-PRPLAN-WORLD-04-04 — Splat/material layer metadata evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO TEXTURE OR MATERIAL RESIDENCY`. **Base:** `a9a812d`. **Gate:** [NLE-PRPLAN-WORLD-04-04-G6-ACTIVATION](NLE-PRPLAN-WORLD-04-04-G6-ACTIVATION.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-04-04](../work-orders/NLE-PRPLAN-WORLD-04-04.md). **PR:** #897.

## Scope delivered

- `src/stormline/terrain/splat_plan.hpp`: splat layer/set descriptors, plan and `plan_splat_layers`.
- `tests/core/world04_splat_tests.cpp`: SPL-01.
- Additive CMake test target and TSan target.
- No texture residency, material graph, PBR/BRDF implementation, terrain renderer, GPU, physics, networking, editor, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Asset ID and revision must be nonzero; layer count is `1..16`.
- Layer IDs and material asset IDs are nonzero; layer IDs are unique; revisions are nonzero.
- Channel is `0..3`; weight is finite in `[0, 1]`; accumulated weight stays `<= 1.0` within `1e-6`.
- `material_count` reports distinct material asset IDs; shared materials are counted once.
- Precedence remains metadata only; no texture, sampler or shader is created.
- Invalid input zeroes the plan and sets a typed diagnostic with the asset ID and layer index.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src tests/core/world04_splat_tests.cpp` — PASS.
- ASan/UBSan build and `spl01` — PASS.
- TSan build under `setarch $(uname -m) -R` and `spl01` — PASS.

## Errors and corrections

- Adjusted the total-weight guard to allow the contract's `1e-6` tolerance; strict compile and sanitizers passed.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, clock, thread or global state.
- Logical weight/precedence metadata only; GFX-05 remains the material/texture owner.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No texture residency, material graph, PBR/BRDF, rendering, GPU, physics/networking, renderer, editor, performance, ABI or release.
- `WORLD-04-05`..`-10` remain blocked until their gates.
- WORLD-03/GFX-04 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `WORLD-04-04` as `COMPLETED`, manifest `WORLD04_04_COMPLETED_REST_BLOCKED`: **491 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 203 `COMPLETED`, 54 approved gates**. Checkpoint promotion remains owner-only.
