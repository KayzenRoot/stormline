# ADR-0132 — Internal logical 2D physics metadata pipeline

**Status: APPROVED for bounded internal logical metadata only.** **Date:** 2026-11-24. **Module:** `SIM-01` — Physics 2D. **Issue:** #46. **Keeps planning-only:** [ADR-0031](0031-sim-01-physics-2d-fixedstep-backend-policy.md), which remains `PROPOSED / NOT APPROVED FOR ENGINE CODE`.

## Context

SIM-01 must eventually provide engine-owned 2D rigid bodies, collision, queries, joints, triggers and collision masks, with a replaceable solver backend and a fixed-tick authority. The full problem includes a real solver, broadphase/narrowphase, deterministic replay, imported collision shapes, ECS lifecycle, tile/scene bridges and native/Web/headless stress qualification. Those runtime capabilities are not qualified and must not be claimed.

The module's formal predecessors, WORLD-01 and TWO-01, have completed their internal sequences and are available as capability sources. Their status is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.

## Decision

Approve a bounded internal sequence that produces **logical 2D physics metadata only** under `src/stormline/physics2d/`:

1. Body descriptor metadata: body type, pose intent, mass/damping flags and identity fields; no simulation.
2. Collision shape metadata: shape kinds, finite dimensions, material/density descriptors and filters; no broadphase or narrowphase.
3. Query intent metadata: ray/overlap/cast request descriptors and bounded result limits; no query execution.
4. Joint metadata: joint kinds, anchors, limits and break-policy descriptors; no constraint solver.
5. Trigger/sensor metadata: sensor descriptors, enablement and event-intent flags; no event dispatch.
6. Collision mask metadata: category/mask/group descriptors and symmetric-policy checks; no contact generation.
7. Integrated deterministic validation, failure-recovery and bounded-overload qualification.

The sequence must not implement a physics solver, adopt Box2D/Chipmunk/Rapier, execute queries, generate contacts, dispatch events, mutate ECS state, read assets or publish collision data. CORE-03/05/06 own scheduling/numeric/fixed tick; WORLD-01/02 own entities/scenes; TWO-01/02/04 own canvas/tilemaps/2.5D composition; WORLD-03 owns streaming; DATA-02/03/04/05 own assets/journal/cook; GAME/NET own runtime authority.

## Ownership and boundaries

| Concern | Authority | SIM-01 may produce |
|---|---|---|
| Entity identity/lifecycle | WORLD-01 | optional entity references |
| Scene/prefab source | WORLD-02 | opaque source references |
| Canvas, tilemap, 2.5D layers | TWO-01/02/04 | collision-shape intent only |
| Fixed tick, scheduler | CORE-06 | tick-intent descriptors |
| Coordinate math | CORE-05 | checked physical-scale metadata |
| Streaming cells/readiness | WORLD-03 | collider publish intent only |
| Assets, import, journal, cook | DATA-02..05 | asset references and revisions |
| Solver, contacts, queries | SIM-01 future backend | descriptors only; no execution |
| Runtime authority | GAME/NET/PHYS | proposals; owners decide |

## Risk and release class

- Planning risk: `LOW` for documentation and logical metadata.
- Future runtime physics risk: `ELEVATED`, explicitly out of scope for this sequence.
- Release class: `INTERNAL_ONLY`. No public ABI, release, hardware, performance, security or production-readiness claim.

## Rejected alternatives

- Adopting Box2D/Chipmunk/Rapier in this sequence; rejected because backend choice, license/SBOM, build and determinism proof are not executed.
- Implementing a bespoke solver; rejected because numerical stability and replay obligations are unqualified.
- Executing queries or dispatching contacts; rejected because events, handles and owner barriers require the runtime design from ADR-0031.
- Mutating ECS from physics callbacks; rejected because WORLD-01 lifecycle authority and deterministic command queues are not implemented.
- Approving ADR-0031 wholesale for engine code; rejected because its proof obligations are not executed.

## Consequences

- Slice `-02` must freeze an exact header-only logical API, allowlist and test oracles before any code.
- Each implementation slice requires its own G6 activation gate.
- The module can close as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; it cannot claim collision suites, determinism, stability or stress readiness.
- Any future runtime physics implementation requires a new owner-approved decision that resolves ADR-0031's proof obligations.
