# WORLD-01 governance contract v0 — internal logical entity metadata

**Status:** `APPROVED GOVERNANCE / INTERNAL_ONLY / NO ECS RUNTIME`. **ADR:** [ADR-0127](../adr/0127-world-01-internal-entity-metadata.md). **Architecture:** [world-01-internal-entity-metadata](../architecture/world-01-internal-entity-metadata.md). **Planning-only policy:** [ADR-0026](../adr/0026-world-01-entity-identity-storage-policy.md) remains `PROPOSED`.

## 1. Scope

This contract governs the internal WORLD-01 sequence: logical world/entity identity, component schema intent, lifecycle transition intent, query intent and reflection field intent. It does not authorize ECS storage, runtime handles, allocations, threading, serialization, persistence, hierarchy, spatial indexing, physics, networking, editor UI, benchmarks or public ABI.

## 2. Invariants

1. **GOV-001 Fail closed:** invalid IDs, generations, epochs, schemas, states, capacities or field bounds produce a typed error and zeroed output; no silent fallback.
2. **GOV-002 Single authority:** DATA-02/DATA-04 own persistent identity/scenes, WORLD-02 hierarchy, WORLD-03 spatial, CORE memory/jobs/math, SIM/PHYS/GAME/NET runtime authority.
3. **GOV-003 Identity separation:** persistent GUIDs and transient world/slot/generation handles are distinct; runtime handles are never serialized or treated as stable source identity.
4. **GOV-004 Determinism:** fixed-capacity plans, stable ordering where required, no allocation, exception, file, network, audio, GPU, clock, thread, RTTI hash or global state.
5. **GOV-005 No runtime claim:** no archetype/sparse-set storage, pointer access, borrow checking, structural command buffer, job system, change detection, serializer or benchmark.
6. **GOV-006 Diagnostics:** every error carries a typed code, source ID and bounded index; output plans are reset before validation.
7. **GOV-007 Traceability:** one stable Work Order ID across issue, branch, PR, evidence and corrections; exact allowlists per slice.

## 3. Planned API areas (frozen only in `-02`)

- World identity intent: project/world IDs, instance epoch, revision, capacities.
- Entity handle intent: slot, generation, epoch, invalidation/retirement.
- Component schema intent: stable type ID, version, bounded fields/kinds.
- Lifecycle intent: alive/destroy-requested/tombstoned/retired and double-destroy receipt.
- Query intent: required/excluded component type IDs and epoch.
- Reflection intent: allowlisted field names/kinds/units/bounds.
- Common diagnostic and capacity types under `src/stormline/world/`.

Exact type names, capacities, error enums and allowlists are frozen by `WORLD-01-02` before implementation. No code may be created from this governance contract alone.

## 4. Slice oracles

| ID | Scenario | Oracle |
|---|---|---|
| ENT-01 | entity handles | nonzero slot/epoch, generation validity, retirement, stale rejection |
| CMP-01 | component schemas | stable type IDs, versions, bounded fields, duplicate/collision rejection |
| LIF-01 | lifecycle | allowed transitions, double-destroy receipt, tombstone/retire |
| QRY-01 | queries | required/excluded sets, unique type IDs, bounded results |
| REF-01 | reflection | allowlisted fields/kinds/units/bounds, no addresses/callbacks |
| QLF-W101 | integrated | world -> entity -> schema -> lifecycle -> query -> reflection |
| QLF-W102 | deterministic repeat | identical plans/order |
| QLF-W103 | failure recovery | typed error followed by valid operation |
| QLF-W104 | bounded overload | 10,000 attempts keep caps |

## 5. Out of scope

ECS storage engine, archetype/sparse sets, allocator, pointer/borrow semantics, jobs/threads, change detection, serialization/migration, persistence/undo, scene hierarchy/prefabs, spatial streaming, physics, gameplay, networking, editor, GPU, audio, export, performance, ABI, release and production readiness.

## 6. Qualification statement

Passing internal CI qualification is not physical, OS, security, soak, concurrency, performance or server-authority qualification. WORLD-01 may close only as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
