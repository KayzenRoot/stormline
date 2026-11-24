# NLE-PRPLAN-TWO-04-07 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / TEST AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `efd3a4f`. **Formal packet:** `NLE-PRPLAN-TWO-04-07`. **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-04-07](../work-orders/NLE-PRPLAN-TWO-04-07.md).

## Authorization

The owner authorized continuation on 2026-11-24. TWO-04-01..-06 are approved. This gate activates only integrated internal qualification fixtures.

## Capability admission

- Formal dependencies are `TWO-01` and `GFX-04`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `tests/core/two04_hybrid_qualification_tests.cpp`
- additive CMake/workflow and `docs/evidence/NLE-PRPLAN-TWO-04-07.md`

QLF-T401..T404 are required. Qualification is internal CI only; no runtime, rendering, GPU, lighting, hardware or performance qualification is claimed.

## Gate state after merge

- Manifest root `TWO04_07_READY_L1_CAPABILITY_OVERLAY`: **522 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 179 `COMPLETED`, 46 approved gates**.
- `TWO-04-07` becomes `EXECUTOR_READY`; `TWO-04-08` remains `PLANNED_BLOCKED`.
