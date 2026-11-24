# SIM-02 — Internal logical 3D physics metadata

**Status:** `APPROVED INTERNAL ARCHITECTURE / LOGICAL METADATA ONLY`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Planning policy remains:** [ADR-0032](../adr/0032-sim-02-engine-owned-3d-physics-and-collider-publication.md) `PROPOSED`. **Runtime physics claims:** none.

## 1. Purpose

Define a bounded, deterministic metadata layer for 3D bodies, collision shapes, broadphase layers, queries, constraints and integrations. It answers what a scene authored and requested, not how bodies are simulated, how contacts are solved or which backend is used.

## 2. Logical model

- **Body intent:** stable body identity, body type, pose/mass/damping intent and optional entity reference.
- **Collision shape intent:** sphere/box/capsule/convex/compound/mesh/heightfield descriptors with finite dimensions and material metadata.
- **Broadphase intent:** layer/mask/group descriptors and candidate-intent flags; no AABB execution.
- **Query intent:** ray/overlap/sweep/cast descriptors and bounded result limits; no execution.
- **Constraint intent:** constraint kind, anchors, axis, limits and motor descriptors.
- **Integration intent:** tick/profile, scene, streaming and authority references.
- **Diagnostics:** typed error plus source ID and index; outputs reset on failure.

## 3. Runtime non-goals

No solver, backend adapter, broadphase/narrowphase execution, contact manifold, event dispatch, ECS mutation, imported collision assets, GPU, I/O, cache or public ABI. Those remain future decisions under ADR-0032 and other module owners.

## 4. Ownership boundaries

- WORLD-01/02/03/04 own entity/scene/streaming/terrain identity.
- CORE-03/05/06 own scheduling, numeric math and fixed tick.
- DATA-02..05 own assets, journal, cook and streaming data.
- GAME/NET own runtime authority.
- SIM-02 owns only logical 3D physics intent metadata.

## 5. Determinism and bounds

All plans are fixed-capacity, header-only, `noexcept` and allocation-free. Capacities are frozen in `-02`; validation and overload behavior must be deterministic across compilers. No clock, random source, file, network, audio, GPU, thread, RTTI hash or global state is allowed.

## 6. Planned slices

| Slice | Logical deliverable | Oracle |
|---|---|---|
| `-03` | rigid body metadata | BODY3-01 |
| `-04` | collision shape metadata | SHAPE3-01 |
| `-05` | broadphase layer metadata | BROAD3-01 |
| `-06` | query intent metadata | QUERY3-01 |
| `-07` | constraint metadata | CONSTRAINT3-01 |
| `-08` | integration metadata | INTEGRATION3-01 |
| `-09` | integrated qualification | QLF-S201..S204 |
| `-10` | closeout | evidence/audit |

`-02` must freeze exact types, capacities, error codes, allowlists and test fixtures before `-03` is activated.

## 7. Explicit non-goals

No solver, backend dependency, simulation, broadphase/narrowphase execution, collision suite, stability/stress benchmark, replay/snapshot, ECS mutation, query execution, event dispatch, scene/physics bridge, GPU, hardware measurement or public ABI. ADR-0032 remains the separate planning authority for those future runtime decisions.
