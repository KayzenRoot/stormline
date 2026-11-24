# WORLD-01 — Internal logical entity/component metadata

**Status:** `APPROVED INTERNAL ARCHITECTURE / LOGICAL METADATA ONLY`. **ADR:** [ADR-0127](../adr/0127-world-01-internal-entity-metadata.md). **Planning policy remains:** [ADR-0026](../adr/0026-world-01-entity-identity-storage-policy.md) `PROPOSED`. **Runtime ECS claims:** none.

## 1. Purpose

Define a bounded, deterministic metadata layer that records world identity, entity handle generations, component schemas, lifecycle intents, queries and reflection fields without executing an ECS runtime. It answers what identity and schema a world requested, not how components are stored in memory or iterated by jobs.

## 2. Logical model

- **World identity intent:** project/world IDs, world instance epoch, revision and bounded capacity.
- **Entity handle intent:** slot index, generation, world epoch; invalidation on generation exhaustion; no serialization of runtime handles.
- **Component schema intent:** stable type ID, schema version, bounded field count, field kinds and constraints; no raw memory layout.
- **Lifecycle intent:** `Alive`, `DestroyRequested`, `Tombstoned`, `Retired`; double-destroy receipts and stale-handle rejection.
- **Query intent:** required/excluded component type IDs, world epoch, bounded query cache metadata.
- **Reflection intent:** allowlisted field names, kinds, units and numeric bounds; no object addresses or callbacks.
- **Diagnostics:** typed error plus source ID and index; outputs reset on failure.

## 3. Storage and runtime non-goals

No archetype tables, sparse sets, chunk allocators, component byte storage, pointer access, structural command buffers, job scheduling, borrow checking, change detection, serialization codec, persistence, scene hierarchy, spatial index or network replication. Those remain future decisions under ADR-0026 and other module owners.

## 4. Ownership boundaries

- DATA-02/DATA-04 own persistent identities, scenes, revisions, journals and CAS.
- WORLD-02 owns hierarchy/prefabs; WORLD-03 owns spatial/streaming.
- CORE-01/02/03/05 own memory, jobs, clocks and math.
- SIM/PHYS/GAME/NET own physics, gameplay and network authority.
- GFX/TWO own rendering and animation; WORLD-01 owns only logical metadata.

## 5. Determinism and bounds

All plans are fixed-capacity, header-only, `noexcept` and allocation-free. Capacities are frozen in `-02`; slicing and overload behavior must be deterministic across compilers. No clock, random source, file, network, audio, GPU, thread, RTTI hash or global state is allowed.

## 6. Planned slices

| Slice | Logical deliverable | Oracle |
|---|---|---|
| `-03` | generational entity handle intent | ENT-01 |
| `-04` | component type/schema intent | CMP-01 |
| `-05` | lifecycle transition intent | LIF-01 |
| `-06` | query intent | QRY-01 |
| `-07` | reflection field intent | REF-01 |
| `-08` | integrated qualification | QLF-W101..W104 |
| `-09` | closeout | evidence/audit |

`-02` must freeze exact types, capacities, error codes, allowlists and test fixtures before `-03` is activated.

## 7. Explicit non-goals

No ECS runtime, storage engine, archetype/sparse-set layout, allocator, thread/borrow enforcement, serialization, scene source, hierarchy, spatial index, physics, gameplay authority, editor UI, benchmark, hardware measurement or public ABI. ADR-0026 remains the separate planning authority for those future runtime decisions.
