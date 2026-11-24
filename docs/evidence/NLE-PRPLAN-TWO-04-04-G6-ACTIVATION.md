# NLE-PRPLAN-TWO-04-04 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `922fb85`. **Formal packet:** `NLE-PRPLAN-TWO-04-04`. **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-04-04](../work-orders/NLE-PRPLAN-TWO-04-04.md).

## Authorization

The owner authorized continuation on 2026-11-24. TWO-04-01..-03 are approved. This gate activates only logical layer intent metadata.

## Capability admission

- Formal dependencies are `TWO-01` and `GFX-04`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/hybrid/layer_plan.hpp`
- `tests/core/two04_layer_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-TWO-04-04.md`

LAY-01 is required. No renderer, depth attachment, sort, effect, matrix, GPU, audio or export is permitted.

## Gate state after merge

- Manifest root `TWO04_04_READY_L1_CAPABILITY_OVERLAY`: **525 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 176 `COMPLETED`, 46 approved gates**.
- `TWO-04-04` becomes `EXECUTOR_READY`; `TWO-04-05`..`-08` remain `PLANNED_BLOCKED`.
