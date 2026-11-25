# NLE-PRPLAN-SIM-04-02 — G6 contract activation

**Status:** `G6 CONTRACT ACTIVATION / NO IMPLEMENTATION AUTHORIZED`. **Base main:** `8a595f95`. **Formal packet:** `NLE-PRPLAN-SIM-04-02`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md). **WO:** [NLE-PRPLAN-SIM-04-02](../work-orders/NLE-PRPLAN-SIM-04-02.md).

## Authorization

The owner authorized continuation on 2026-11-24. SIM-04-01 governance is approved. This gate freezes only the internal logical contract.

## Capability admission

- Formal dependencies are `SIM-03` and `DATA-03`; neither is module-qualified.
- `module_completion_claimed=false`.

## Activated scope

- `docs/contracts/sim-04-animation-internal-v0.md` with exact types, capacities, error model, oracles and allowlists `-03`..`-09`.
- WO, this evidence, activation JSON and checkpoint/manifest bookkeeping.

No source, test, CMake or workflow file may change. No pose evaluation, solver, ragdoll, codec, root-motion application, ECS mutation, GPU or animation runtime is permitted.

## Gate state after merge

- Manifest root `SIM04_02_APPROVED_CONTRACT_ONLY`: **445 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 239 `COMPLETED`, 64 approved gates**.
- `SIM-04-02` becomes `APPROVED_CONTRACT`; `SIM-04-03`..`-10` remain `PLANNED_BLOCKED`.

## Correction (2026-11-24)

The frozen contract was corrected after the baseline inspection found that TWO-03 already owns `src/stormline/animation/animation_types.hpp`, `blend_plan.hpp` and sibling headers. SIM-04 now uses `src/stormline/animation/skeletal/` with namespace `stormline::animation::skeletal`, `SkeletalError`/`SkeletalDiagnostic` and `blend_tree_plan.hpp`; no approved TWO-03 code is modified. Activation pins for `-02` and `-03` were updated to the corrected contract blob in the same work order.
