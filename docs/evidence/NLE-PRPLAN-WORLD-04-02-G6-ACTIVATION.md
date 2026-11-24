# NLE-PRPLAN-WORLD-04-02 — G6 contract activation

**Status:** `G6 CONTRACT ACTIVATION / DOCUMENTATION ONLY / NO CODE AUTHORIZED BY THIS RECORD`. **Base main:** `c2e32d2`. **Formal packet:** `NLE-PRPLAN-WORLD-04-02`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-04-02](../work-orders/NLE-PRPLAN-WORLD-04-02.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-04-01 is approved. This gate freezes the exact API and allowlists; it does not authorize code.

## Capability admission

- Formal dependencies are `WORLD-03` and `GFX-04`; neither is module-qualified.
- Admission uses completed internal capabilities.
- `module_completion_claimed=false`.

## Frozen surface

- `stormline::terrain` common types, errors, capacities and diagnostic.
- `plan_terrain_patches` (TER-01), `plan_splat_layers` (SPL-01), `plan_vegetation` (VEG-01), `plan_water` (WAT-01), `plan_sky` (SKY-01), `plan_weather` (CLI-01).
- QLF-W401..W404 integrated qualification definitions.
- Exact per-slice allowlists for `-03`..`-09`; no production `.cpp`.

No heightfield/mesh storage, mesh generation, terrain/water rendering, GPU LOD, texture residency, vegetation instancing, atmosphere/weather simulation, physics/network coordination, renderer, editor, GPU, performance, ABI or release is authorized. ADR-0029 remains `PROPOSED`.

## Gate state after merge

- Manifest root `WORLD04_02_APPROVED_CONTRACT_ONLY`: **493 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 201 `COMPLETED`, 54 approved gates**.
- `WORLD-04-02` becomes `APPROVED_CONTRACT`; `WORLD-04-03`..`-10` remain `PLANNED_BLOCKED`.
