# NLE-PRPLAN-WORLD-05-01 — G6 governance activation

**Status:** `G6 GOVERNANCE ACTIVATION / DOCUMENTATION ONLY / NO CODE AUTHORIZED BY THIS RECORD`. **Base main:** `479123b`. **Formal packet:** `NLE-PRPLAN-WORLD-05-01`. **ADR:** [ADR-0131](../adr/0131-world-05-internal-procedural-generation-metadata.md). **Governance contract:** [world-05-governance-v0](../contracts/world-05-governance-v0.md). **WO:** [NLE-PRPLAN-WORLD-05-01](../work-orders/NLE-PRPLAN-WORLD-05-01.md).

## Authorization

The owner authorized continuation on 2026-11-24. WORLD-04 and DATA-03 internal sequences are complete. This gate approves governance only; it does not authorize code.

## Capability admission

- Formal dependencies are `WORLD-04` and `DATA-03`; neither is module-qualified.
- Admission uses completed internal capabilities.
- `module_completion_claimed=false`.

## Approved surface

- Logical seed/domain, graph topology, rule, biome, geometry and content generator metadata.
- Oracles SEED-01, GRAPH-01, RULE-01, BIOME-01, GEO-01, GEN-01 and QLF-W501..W504.
- Slice gates `-02`..`-10` remain individually blocked.

No graph evaluation, RNG/noise, WFC, asset import, cook/cache, source writes, mesh generation, GPU preview, physics/network coordination, editor, performance, ABI or release is authorized. ADR-0030 remains `PROPOSED`.

## Gate state after merge

- Manifest root `WORLD05_01_APPROVED_GOVERNANCE_ONLY`: **484 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 209 `COMPLETED`, 55 approved gates**.
- `WORLD-05-01` becomes `APPROVED_GOVERNANCE`; `WORLD-05-02`..`-10` remain `PLANNED_BLOCKED`.
