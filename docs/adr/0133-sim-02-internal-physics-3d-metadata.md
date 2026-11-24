# ADR-0133 — Internal logical 3D physics metadata pipeline

**Status: APPROVED for bounded internal logical metadata only.** **Date:** 2026-11-24. **Module:** `SIM-02` — Physics 3D. **Issue:** #47. **Keeps planning-only:** [ADR-0032](0032-sim-02-engine-owned-3d-physics-and-collider-publication.md), which remains `PROPOSED / NOT APPROVED FOR ENGINE CODE`.

## Context

SIM-02 must eventually provide engine-owned 3D rigid bodies, collision shapes, broadphase, queries, constraints and integrations, with a replaceable solver backend and a fixed-tick authority. The full problem includes a real solver, broadphase/narrowphase, deterministic replay, imported collision meshes and heightfields, ECS lifecycle, scene/streaming bridges and native/Web/headless stress qualification. Those runtime capabilities are not qualified and must not be claimed.

The module's formal predecessors, WORLD-02 and CORE-03, have completed their internal sequences and are available as capability sources. Their status is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.

## Decision

Approve a bounded internal sequence that produces **logical 3D physics metadata only** under `src/stormline/physics3d/`:

1. Body descriptor metadata: body type, pose intent, mass/damping flags and identity fields; no simulation.
2. Collision shape metadata: sphere/box/capsule/convex/compound/mesh/heightfield descriptors, finite dimensions and material metadata; no narrowphase.
3. Broadphase layer metadata: layer/mask/group descriptors and candidate-intent flags; no AABB tree, sweep or candidate execution.
4. Query intent metadata: ray/overlap/sweep/shape-cast descriptors and bounded result limits; no query execution.
5. Constraint metadata: constraint kinds, anchors, axes, limits and motor descriptors; no constraint solver.
6. Integration metadata: tick/profile, scene, streaming and authority references; no ECS mutation and no runtime bridge.
7. Integrated deterministic validation, failure-recovery and bounded-overload qualification.

The sequence must not implement a physics solver, adopt Jolt/PhysX/Bullet/Rapier, execute queries, generate contacts, run broadphase, dispatch events, mutate ECS state, read assets or publish collision data. CORE-03/05/06 own scheduling/numeric/fixed tick; WORLD-01/02/03/04 own entities/scenes/streaming/terrain; DATA-02..05 own assets/journal/cook; GAME/NET own runtime authority.

## Ownership and boundaries

| Concern | Authority | SIM-02 may produce |
|---|---|---|
| Entity identity/lifecycle | WORLD-01 | optional entity references |
| Scene/prefab source | WORLD-02 | opaque source references |
| Spatial cells/streaming | WORLD-03 | collider publish intent only |
| Terrain/heightfield source | WORLD-04 | heightfield collider references |
| Jobs, priorities, cancellation | CORE-03 | job-intent descriptors |
| Coordinate math, precision | CORE-05 | checked physical-scale metadata |
| Fixed tick, scheduler | CORE-06 | tick-intent descriptors |
| Assets, import, journal, cook | DATA-02..05 | asset references and revisions |
| Solver, contacts, queries | SIM-02 future backend | descriptors only; no execution |
| Runtime authority | GAME/NET/PHYS | proposals; owners decide |

## Risk and release class

- Planning risk: `LOW` for documentation and logical metadata.
- Future runtime physics risk: `ELEVATED`, explicitly out of scope for this sequence.
- Release class: `INTERNAL_ONLY`. No public ABI, release, hardware, performance, security or production-readiness claim.

## Rejected alternatives

- Adopting Jolt/PhysX/Bullet/Rapier in this sequence; rejected because backend choice, license/SBOM, build and determinism proof are not executed.
- Implementing a bespoke 3D solver; rejected because numerical stability and replay obligations are unqualified.
- Running broadphase or queries; rejected because spatial execution, handles and owner barriers require the runtime design from ADR-0032.
- Mutating ECS from physics callbacks; rejected because WORLD-01 lifecycle authority and deterministic command queues are not implemented.
- Approving ADR-0032 wholesale for engine code; rejected because its proof obligations are not executed.

## Consequences

- Slice `-02` must freeze an exact header-only logical API, allowlist and test oracles before any code.
- Each implementation slice requires its own G6 activation gate.
- The module can close as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; it cannot claim collision suites, determinism, stability or stress readiness.
- Any future runtime 3D physics implementation requires a new owner-approved decision that resolves ADR-0032's proof obligations.
