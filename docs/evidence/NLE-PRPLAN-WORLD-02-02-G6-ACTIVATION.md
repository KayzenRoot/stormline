# NLE-PRPLAN-WORLD-02-02 — G6 contract activation

**Status:** `G6 CONTRACT ACTIVATION / DOCUMENTATION ONLY / NO CODE AUTHORIZED BY THIS RECORD`. **Base main:** `4eaebbc`. **Formal packet:** `NLE-PRPLAN-WORLD-02-02`. **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Contract:** [world-02-scene-internal-v0](../contracts/world-02-scene-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-02-02](../work-orders/NLE-PRPLAN-WORLD-02-02.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-02-01 is approved. This gate freezes the exact API and allowlists; it does not authorize code.

## Capability admission

- Formal dependencies are `WORLD-01` and `DATA-02`; neither is module-qualified.
- Admission uses completed internal capabilities.
- `module_completion_claimed=false`.

## Frozen surface

- `stormline::scene` common types, errors, capacities and diagnostic.
- `plan_scene_hierarchy` (HIR-01), `plan_prefab_composition` (PFC-01), `plan_prefab_variant` (VAR-01), `plan_prefab_instances` (INS-01), `plan_scene_transforms` (TRS-01).
- QLF-S201..S204 integrated qualification definitions.
- Exact per-slice allowlists for `-03`..`-08`; no production `.cpp`.

No scene runtime, prefab expansion, override merge, serializer, persistence, journal, transform math, spatial index, physics, networking, editor, GPU, performance, ABI or release is authorized.

## Gate state after merge

- Manifest root `WORLD02_02_APPROVED_CONTRACT_ONLY`: **510 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 188 `COMPLETED`, 50 approved gates**.
- `WORLD-02-02` becomes `APPROVED_CONTRACT`; `WORLD-02-03`..`-09` remain `PLANNED_BLOCKED`.
