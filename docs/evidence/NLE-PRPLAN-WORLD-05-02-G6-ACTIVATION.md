# NLE-PRPLAN-WORLD-05-02 — G6 contract activation

**Status:** `G6 CONTRACT ACTIVATION / DOCUMENTATION ONLY / NO CODE AUTHORIZED BY THIS RECORD`. **Base main:** `6e4bd10`. **Formal packet:** `NLE-PRPLAN-WORLD-05-02`. **ADR:** [ADR-0131](../adr/0131-world-05-internal-procedural-generation-metadata.md). **Contract:** [world-05-procedural-internal-v0](../contracts/world-05-procedural-internal-v0.md). **WO:** [NLE-PRPLAN-WORLD-05-02](../work-orders/NLE-PRPLAN-WORLD-05-02.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-05-01 is approved. This gate freezes the exact API and allowlists; it does not authorize code.

## Capability admission

- Formal dependencies are `WORLD-04` and `DATA-03`; neither is module-qualified.
- Admission uses completed internal capabilities.
- `module_completion_claimed=false`.

## Frozen surface

- `stormline::procedural` common types, errors, capacities and diagnostic.
- `plan_seed_domains` (SEED-01), `plan_graph` (GRAPH-01), `plan_rules` (RULE-01), `plan_biomes` (BIOME-01), `plan_geometry` (GEO-01), `plan_generators` (GEN-01).
- QLF-W501..W504 integrated qualification definitions.
- Exact per-slice allowlists for `-03`..`-09`; no production `.cpp`.

No graph evaluation, RNG/noise, WFC, asset I/O, cook/cache, source writes, mesh generation, GPU preview, renderer, editor, GPU, performance, ABI or release is authorized. ADR-0030 remains `PROPOSED`.

## Gate state after merge

- Manifest root `WORLD05_02_APPROVED_CONTRACT_ONLY`: **483 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 209 `COMPLETED`, 56 approved gates**.
- `WORLD-05-02` becomes `APPROVED_CONTRACT`; `WORLD-05-03`..`-10` remain `PLANNED_BLOCKED`.
