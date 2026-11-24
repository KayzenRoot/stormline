# NLE-PRPLAN-TWO-04-04 — Layer intent evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO RENDER OR DEPTH ATTACHMENT`. **Base:** `c22d266`. **Gate:** [NLE-PRPLAN-TWO-04-04-G6-ACTIVATION](NLE-PRPLAN-TWO-04-04-G6-ACTIVATION.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-04-04](../work-orders/NLE-PRPLAN-TWO-04-04.md). **PR:** #841.

## Scope delivered

- `src/stormline/hybrid/layer_plan.hpp`: object/layer/set descriptors, plan and `plan_layers`.
- `tests/core/two04_layer_tests.cpp`: LAY-01.
- Additive CMake test and TSan target.
- No renderer, depth attachment, matrix, lighting, sort, effect, GPU, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Scene ID/revision nonzero; layer count `1..16`.
- Layer IDs/revisions nonzero; modes and alpha policies allowlisted; author orders unique.
- Object count per layer bounded by `kMaxHybridObjects`; object IDs/revisions nonzero, kinds allowlisted, depth keys finite and IDs unique across the scene.
- `OrderedCanvasOverlay` and `IsolatedSubview` forbid depth test/write.
- `SharedDepthWorld` with `Blended` alpha forbids depth write; depth write requires depth test.
- Counts report layers, total objects, depth-writing layers and canvas layers.
- Invalid input zeroes the plan and sets a typed diagnostic.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict GCC flags, ASan/UBSan and TSan all passed for LAY-01. First compile exposed a missing `<array>` include; fixed before any evidence was recorded.

## Errors and corrections

- Added `<array>` to `layer_plan.hpp`; strict compile, ASan/UBSan and TSan then passed.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, audio, GPU, thread or global state.
- Logical layer intent only; TWO-01 painter order, GFX-03 depth attachments and GFX-05 alpha remain authoritative.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No renderer, depth attachment, matrix, lighting, sorting, effects, editor, audio, export, ABI, release, hardware or performance.
- `TWO-04-05`..`-08` remain blocked until their gates.
- TWO-01/GFX-04 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `TWO-04-04` as `COMPLETED`, manifest `TWO04_04_COMPLETED_REST_BLOCKED`: **525 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 177 `COMPLETED`, 46 approved gates**. Checkpoint promotion remains owner-only.
