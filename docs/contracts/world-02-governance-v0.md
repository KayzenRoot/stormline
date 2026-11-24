# WORLD-02 governance contract v0 — internal logical scene/prefab metadata

**Status:** `APPROVED GOVERNANCE / INTERNAL_ONLY / NO SCENE RUNTIME`. **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Architecture:** [world-02-internal-scene-prefab-metadata](../architecture/world-02-internal-scene-prefab-metadata.md). **Planning-only policy:** [ADR-0027](../adr/0027-world-02-prefab-override-rebase-policy.md) remains `PROPOSED`.

## 1. Scope

This contract governs the internal WORLD-02 sequence: logical scene hierarchy, prefab composition, variant overrides, instancing bounds and transform/reparent intent. It does not authorize runtime scene graphs, prefab expansion, override merge, serialization, persistence, transform math, spatial indexing, physics, networking, editor UI, benchmarks or public ABI.

## 2. Invariants

1. **GOV-001 Fail closed:** invalid IDs, parents, depths, revisions, overrides, transforms or capacities produce a typed error and zeroed output; no silent fallback.
2. **GOV-002 Single authority:** WORLD-01 owns entities/components, DATA-02/04 own assets/revisions/journal, CORE-05 owns math, WORLD-03 spatial, SIM/PHYS/GAME/NET simulation authority.
3. **GOV-003 Identity separation:** node/prefab/instance identities are stable logical IDs distinct from runtime entity handles and display names/paths.
4. **GOV-004 Determinism:** fixed-capacity plans, stable sibling ordering, no allocation, exception, file, network, audio, GPU, clock, thread, RTTI hash or global state.
5. **GOV-005 No runtime claim:** no scene graph runtime, expansion, override merge, serializer, journal, transform solver, instancing execution or benchmark.
6. **GOV-006 Diagnostics:** every error carries a typed code, source ID and bounded index; output plans are reset before validation.
7. **GOV-007 Traceability:** one stable Work Order ID across issue, branch, PR, evidence and corrections; exact allowlists per slice.

## 3. Planned API areas (frozen only in `-02`)

- Scene hierarchy intent: node IDs, parent, sibling order, roots, depth/cycle bounds.
- Prefab composition intent: prefab IDs/revisions, nested references, composition layers/depths.
- Variant override intent: base prefab/revision, node/type/field override keys, conflicts.
- Instance intent: prefab reference, instance ID, expansion counts/depth.
- Transform intent: finite local TRS and reparent mode.
- Common diagnostic and capacity types under `src/stormline/scene/`.

Exact type names, capacities, error enums and allowlists are frozen by `WORLD-02-02` before implementation. No code may be created from this governance contract alone.

## 4. Slice oracles

| ID | Scenario | Oracle |
|---|---|---|
| HIR-01 | hierarchy | unique nodes, single parent, roots, cycle/depth, sibling order |
| PFC-01 | composition | prefab identity, nested DAG, depth/cycle, layers |
| VAR-01 | variants | base revision, override keys, duplicates, conflict receipts |
| INS-01 | instancing | instance identity, fan-out bounds, depth |
| TRS-01 | transforms | finite TRS, reparent mode, bounds |
| QLF-S201 | integrated | hierarchy -> prefab -> variant -> instance -> transform |
| QLF-S202 | deterministic repeat | identical plans/counts |
| QLF-S203 | failure recovery | typed error followed by valid operation |
| QLF-S204 | bounded overload | 10,000 attempts keep caps |

## 5. Out of scope

Scene runtime, node/component storage, prefab expansion, override merge/rebase execution, serializer/migration, asset database, journal/undo, transform evaluation, spatial streaming, physics, gameplay, networking, editor, GPU, audio, export, performance, ABI, release and production readiness.

## 6. Qualification statement

Passing internal CI qualification is not physical, OS, security, soak, concurrency, persistence, performance or authoring qualification. WORLD-02 may close only as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
