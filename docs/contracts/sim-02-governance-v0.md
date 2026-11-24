# SIM-02 governance contract v0 — internal logical 3D physics metadata

**Status:** `APPROVED GOVERNANCE / INTERNAL_ONLY / NO PHYSICS RUNTIME`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Architecture:** [sim-02-internal-physics-3d-metadata](../architecture/sim-02-internal-physics-3d-metadata.md). **Planning-only policy:** [ADR-0032](../adr/0032-sim-02-engine-owned-3d-physics-and-collider-publication.md) remains `PROPOSED`.

## 1. Scope

This contract governs the internal SIM-02 sequence: logical rigid-body descriptors, collision-shape descriptors, broadphase layer metadata, query intents, constraint descriptors and integration references. It does not authorize a solver, backend adoption, simulation, contact generation, broadphase/narrowphase execution, query execution, event dispatch, ECS mutation, scene bridge, editor UI or public ABI.

## 2. Invariants

1. **GOV-001 Fail closed:** invalid identities, types, dimensions, scales, masks or budgets produce a typed error and zeroed output; no silent fallback.
2. **GOV-002 Single authority:** WORLD-01/02/03/04 own entities/scenes/streaming/terrain, CORE-03/05/06 own scheduling/math/tick, DATA-02..05 assets/journal/cook, GAME/NET runtime authority.
3. **GOV-003 Identity separation:** body/shape/constraint metadata is not a solver handle and never exposes backend types or raw pointers.
4. **GOV-004 Determinism:** fixed-capacity plans, stable ordering where required, no allocation, exception, file, network, audio, GPU, clock, thread or global state.
5. **GOV-005 No runtime claim:** no solver, simulation, broadphase/narrowphase execution, query result, contact, event dispatch, replay or benchmark.
6. **GOV-006 Diagnostics:** every error carries a typed code, source ID and bounded index; output plans are reset before validation.
7. **GOV-007 Traceability:** one stable Work Order ID across issue, branch, PR, evidence and corrections; exact allowlists per slice.

## 3. Planned API areas (frozen only in `-02`)

- Body intent: type, pose, mass/damping flags, entity reference.
- Shape intent: kind, finite dimensions, density, material reference.
- Broadphase intent: layer/mask/group descriptors and candidate-intent flags.
- Query intent: ray/overlap/sweep/cast descriptors and result limits.
- Constraint intent: kind, anchors, axis, limits, motor and break policy.
- Integration intent: tick/profile, scene, streaming and authority references.
- Common diagnostic and capacity types under `src/stormline/physics3d/`.

Exact type names, capacities, error enums and allowlists are frozen by `SIM-02-02` before implementation. No code may be created from this governance contract alone.

## 4. Slice oracles

| ID | Scenario | Oracle |
|---|---|---|
| BODY3-01 | bodies | unique IDs, type allowlist, finite pose/mass/damping, entity refs |
| SHAPE3-01 | shapes | kind/dimension/density validity, material refs |
| BROAD3-01 | broadphase layers | bit ranges, layer/group rules, candidate intent |
| QUERY3-01 | queries | descriptors, finite regions, bounded limits |
| CONSTRAINT3-01 | constraints | body refs, anchors/axes, limits, motor policy |
| INTEGRATION3-01 | integrations | tick/scene/streaming/authority references |
| QLF-S201 | integrated | body -> shape -> broadphase -> query -> constraint -> integration |
| QLF-S202 | deterministic repeat | identical plans/counts |
| QLF-S203 | failure recovery | typed error followed by valid operation |
| QLF-S204 | bounded overload | 10,000 attempts keep caps |

## 5. Out of scope

Solver/backend, simulation, broadphase/narrowphase execution, contacts, query execution, event dispatch, ECS mutation, replay/snapshot, scene/streaming bridges, editor, GPU, audio, export, performance, ABI, release and production readiness.

## 6. Qualification statement

Passing internal CI qualification is not the catalog's 3D collision/scale/memory/headless-simulation suite, determinism, replay, security, soak or performance qualification. SIM-02 may close only as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
