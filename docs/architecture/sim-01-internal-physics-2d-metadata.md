# SIM-01 — Internal logical 2D physics metadata

**Status:** `APPROVED INTERNAL ARCHITECTURE / LOGICAL METADATA ONLY`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Planning policy remains:** [ADR-0031](../adr/0031-sim-01-physics-2d-fixedstep-backend-policy.md) `PROPOSED`. **Runtime physics claims:** none.

## 1. Purpose

Define a bounded, deterministic metadata layer for 2D bodies, collision shapes, queries, joints, triggers and collision masks. It answers what a scene authored and requested, not how bodies are simulated, how contacts are solved or which backend is used.

## 2. Logical model

- **Body intent:** stable body identity, body type, pose/damping intent and optional entity reference.
- **Collision shape intent:** shape kind, finite dimensions, density and material metadata.
- **Query intent:** ray/overlap/cast descriptors and bounded result limits; no execution.
- **Joint intent:** joint kind, anchors, limits and break-policy descriptors.
- **Trigger intent:** sensor descriptors and event-enablement metadata.
- **Mask intent:** category/mask/group descriptors and symmetric collision checks.
- **Diagnostics:** typed error plus source ID and index; outputs reset on failure.

## 3. Runtime non-goals

No solver, backend adapter, broadphase, narrowphase, contact manifold, event dispatch, ECS mutation, imported collision assets, GPU, I/O, cache or public ABI. Those remain future decisions under ADR-0031 and other module owners.

## 4. Ownership boundaries

- WORLD-01/02 own entity/scene identity; TWO-01/02/04 own canvas/tilemap/2.5D.
- CORE-05/06 own numeric math and fixed tick; WORLD-03 owns streaming.
- DATA-02..05 own assets, journal, cook and streaming data.
- GAME/NET own runtime authority.
- SIM-01 owns only logical 2D physics intent metadata.

## 5. Determinism and bounds

All plans are fixed-capacity, header-only, `noexcept` and allocation-free. Capacities are frozen in `-02`; validation and overload behavior must be deterministic across compilers. No clock, random source, file, network, audio, GPU, thread, RTTI hash or global state is allowed.

## 6. Planned slices

| Slice | Logical deliverable | Oracle |
|---|---|---|
| `-03` | rigid body metadata | BODY-01 |
| `-04` | collision shape metadata | COL-01 |
| `-05` | query intent metadata | QRY-01 |
| `-06` | joint metadata | JNT-01 |
| `-07` | trigger/sensor metadata | TRG-01 |
| `-08` | collision mask metadata | MSK-01 |
| `-09` | integrated qualification | QLF-S101..S104 |
| `-10` | closeout | evidence/audit |

`-02` must freeze exact types, capacities, error codes, allowlists and test fixtures before `-03` is activated.

## 7. Explicit non-goals

No solver, backend dependency, simulation, collision suite, stability/stress benchmark, replay/snapshot, ECS mutation, query execution, event dispatch, tilemap/physics bridge, GPU, hardware measurement or public ABI. ADR-0031 remains the separate planning authority for those future runtime decisions.
