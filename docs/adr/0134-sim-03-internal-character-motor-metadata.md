# ADR-0134 — Internal logical character motor metadata

**Status: APPROVED for bounded internal logical metadata only.** **Date:** 2026-11-24. **Module:** `SIM-03` — Character Controller & Movement. **Issue:** #48. **Keeps planning-only:** [ADR-0033](0033-sim-03-authoritative-character-motor-policy.md), which remains `PROPOSED / NOT APPROVED FOR CODE`.

## Context

SIM-03 must eventually provide engine-owned kinematic/dynamic character controllers, locomotion, input response and decoupled camera consumers for 2D and 3D. The full problem includes contact-gated movement against SIM-01/SIM-02, fixed-tick authority, deterministic replay, input buffering, moving platforms, production gameplay tuning and native/Web/headless stress qualification. Those runtime capabilities are not qualified and must not be claimed.

The module's formal predecessors, SIM-01 and SIM-02, have completed their internal sequences and are available as capability sources. Their status is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.

## Decision

Approve a bounded internal sequence that produces **logical character motor metadata only** under `src/stormline/character/`:

1. Controller profile metadata: dimension, kinematic/dynamic mode, capsule/box extents, up axis, ground/step/slope policy flags; no movement execution.
2. Locomotion metadata: walk/run/air speed, acceleration, jump/dash intent descriptors and tick-based grace/buffer windows; no simulation.
3. Input response metadata: bounded action/axis descriptors and tick-indexed buffering intent; no device polling.
4. Decoupled camera metadata: follow/look descriptors, damping and independence flags; no camera update.
5. Integrated deterministic validation, failure-recovery and bounded-overload qualification.

The sequence must not implement a motor, sweeper, contact query, solver, input device layer, camera transform, animation root motion, ECS mutation or network prediction. SIM-01/02 own collision metadata and future physics runtime; CORE-03/04/06 own jobs/tick/scheduling; WORLD-01/02 own entities/scenes; GAME/NET own input authority and prediction.

## Ownership and boundaries

| Concern | Authority | SIM-03 may produce |
|---|---|---|
| Entity identity/lifecycle | WORLD-01 | optional entity references |
| Scene/prefab source | WORLD-02 | opaque source references |
| 2D/3D collision metadata | SIM-01/02 | controller profile intent only |
| Fixed tick and scheduler | CORE-04/06 | tick-window descriptors |
| Jobs and budgets | CORE-03 | none; descriptors only |
| Input devices | CORE-01/editor/platform | action/axis intent |
| Camera rendering | GFX/editor | decoupled camera intent only |
| Animation/root motion | SIM-04 | motion request descriptors |
| Runtime authority | GAME/NET | proposals; owners decide |

## Risk and release class

- Planning risk: `LOW` for documentation and logical metadata.
- Future runtime character-motor risk: `ELEVATED`, explicitly out of scope for this sequence.
- Release class: `INTERNAL_ONLY`. No public ABI, release, hardware, performance, gameplay-feel or production-readiness claim.

## Rejected alternatives

- Exposing a Jolt `CharacterVirtual`/Box2D mover/other backend type as the contract; rejected because backend choice, license/SBOM and ABI are unqualified.
- Implementing a bespoke sweeper or contact pipeline; rejected because SIM-01/02 runtime and determinism obligations are unexecuted.
- Polling devices or updating cameras inside the motor; rejected because input and presentation authority belong to other modules.
- Claiming gameplay feel or replay determinism; rejected because player testing and numeric-profile evidence do not exist.
- Approving ADR-0033 wholesale for engine code; rejected because its proof obligations are not executed.

## Consequences

- Slice `-02` must freeze an exact header-only logical API, allowlist and test oracles before any code.
- Each implementation slice requires its own G6 activation gate.
- The module can close as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; it cannot claim movement quality, collision-gated locomotion, replay, security or performance readiness.
- Any future runtime character-motor implementation requires a new owner-approved decision that resolves ADR-0033's proof obligations.
