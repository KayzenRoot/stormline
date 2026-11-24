# WORLD-02 — Internal logical scene/prefab metadata

**Status:** `APPROVED INTERNAL ARCHITECTURE / LOGICAL METADATA ONLY`. **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Planning policy remains:** [ADR-0027](../adr/0027-world-02-prefab-override-rebase-policy.md) `PROPOSED`. **Runtime scene/prefab claims:** none.

## 1. Purpose

Define a bounded, deterministic metadata layer that records scene hierarchy, prefab composition, variant overrides, instancing bounds and transform intent without executing a scene runtime. It answers what graph and override relationships were declared, not how nodes are stored, expanded or persisted.

## 2. Logical model

- **Scene hierarchy intent:** stable node IDs, parent `0` or existing node, single parent, cycle/depth rejection, unique sibling order.
- **Prefab composition intent:** prefab IDs/revisions, nested references, composition layers, bounded depth, cycle rejection.
- **Variant override intent:** base prefab/revision, field overrides keyed by node/type/field, duplicate detection, conflict receipt metadata.
- **Instance intent:** prefab/revision, instance ID, bounded expansion counts and depth; no entity creation.
- **Transform intent:** finite local translation/rotation/scale and `KeepLocal`/`KeepWorld` reparent mode; no matrix composition.
- **Diagnostics:** typed error plus source ID and index; outputs reset on failure.

## 3. Runtime and persistence non-goals

No scene graph runtime, node storage, prefab expansion, three-way merge engine, serializer, asset database, journal/undo, transform solver, spatial index, streaming, physics, networking, editor UI, GPU or public ABI. DATA-02/04 and WORLD-01 retain authority; ADR-0027 remains the planning policy for future runtime decisions.

## 4. Ownership boundaries

- WORLD-01 owns entity/component identity; DATA-02/04 own assets/revisions/journal.
- CORE-05 owns transform math; WORLD-03 owns spatial/streaming.
- SIM/PHYS/GAME/NET own simulation and authority.
- GFX/TWO/EDIT/UI own rendering and authoring UI.
- WORLD-02 owns only logical graph/prefab/override/transform intent metadata.

## 5. Determinism and bounds

All plans are fixed-capacity, header-only, `noexcept` and allocation-free. Capacities are frozen in `-02`; slicing and overload behavior must be deterministic across compilers. No clock, random source, file, network, audio, GPU, thread, RTTI hash or global state is allowed.

## 6. Planned slices

| Slice | Logical deliverable | Oracle |
|---|---|---|
| `-03` | scene hierarchy forest intent | HIR-01 |
| `-04` | prefab composition intent | PFC-01 |
| `-05` | variant/override intent | VAR-01 |
| `-06` | instance expansion intent | INS-01 |
| `-07` | transform/reparent intent | TRS-01 |
| `-08` | integrated qualification | QLF-S201..S204 |
| `-09` | closeout | evidence/audit |

`-02` must freeze exact types, capacities, error codes, allowlists and test fixtures before `-03` is activated.

## 7. Explicit non-goals

No runtime graph, node/component storage, prefab expansion, override merge, serializer, asset database, journal, transform evaluation, hierarchy of prefabs at runtime, instancing execution, editor, spatial streaming, physics, networking, benchmark, hardware measurement or public ABI. ADR-0027 remains the separate planning authority for those future runtime decisions.
