# NLE-PRPLAN-TWO-04-06 — Hybrid effect bridge evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO LIGHTING OR SUBVIEW EXECUTION`. **Base:** `13e0119`. **Gate:** [NLE-PRPLAN-TWO-04-06-G6-ACTIVATION](NLE-PRPLAN-TWO-04-06-G6-ACTIVATION.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-04-06](../work-orders/NLE-PRPLAN-TWO-04-06.md). **PR:** #845.

## Scope delivered

- `src/stormline/hybrid/effect_plan.hpp`: effect/set descriptors, plan and `plan_effects`.
- `tests/core/two04_effect_tests.cpp`: EFE-01.
- Additive CMake test and TSan target.
- No renderer, GPU, evaluated lighting/shadows, subview execution, editor, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Scene ID/revision nonzero; effect count `0..8`.
- Effect/layer IDs and revisions nonzero; effect IDs unique; fallback reasons allowlisted.
- Subview width/height are both zero or both `1..16384`; depth `0..4`.
- Nonzero subview depth requires a declared extent.
- Outputs total effects, lit, shadow and subview counts plus maximum subview depth.
- Invalid input zeroes the plan and sets a typed diagnostic.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict GCC flags, ASan/UBSan and TSan all passed for EFE-01.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, thread or global state.
- Logical effect bridge intent only; GFX-06 and GFX-03/07 retain runtime authority.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No renderer, lighting, shadows, subview execution, editor, audio, export, ABI, release, hardware or performance.
- `TWO-04-07`/`-08` remain blocked until their gates.
- TWO-01/GFX-04 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `TWO-04-06` as `COMPLETED`, manifest `TWO04_06_COMPLETED_REST_BLOCKED`: **523 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 179 `COMPLETED`, 46 approved gates**. Checkpoint promotion remains owner-only.
