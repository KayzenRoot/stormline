# ADR-0136 — Internal logical navigation and behavior metadata

**Status: APPROVED for bounded internal logical metadata only.** **Date:** 2026-11-24. **Module:** `SIM-05` — Navigation & Behavior. **Issue:** #50. **Keeps planning-only:** [ADR-0035](0035-sim-05-engine-owned-navigation-and-behavior-authority.md), which remains `PROPOSED / NOT APPROVED FOR ENGINE CODE`.

## Context

SIM-05 must eventually provide navmesh tiles, path queries, steering, behavior trees/statecharts and NPC perception over streamed worlds. The full problem includes Recast/Detour adoption, tile residency gates against WORLD-03, physics queries against SIM-02, character motion against SIM-03, deterministic tick behavior and native/Web/headless stress qualification. Those runtime capabilities are not qualified and must not be claimed.

The module's formal predecessors, WORLD-03 and SIM-02, have completed their internal sequences and are available as capability sources. Their status is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.

## Decision

Approve a bounded internal sequence that produces **logical navigation and behavior metadata only** under `src/stormline/navigation/`:

1. Navmesh region metadata: tile/cell references, area tags, traversal cost and flags; no build or query execution.
2. Steering metadata: steering behavior kinds, weights, radii and priority descriptors; no steering execution.
3. Behavior tree/statechart metadata: node kinds, child references, transitions and blackboard keys; no graph execution.
4. NPC perception metadata: sensor kinds, radii, cones, intervals and layer references; no sensing.
5. Integrated deterministic validation, failure-recovery and bounded-overload qualification.

The sequence must not implement Recast/Detour, pathfinding, steering, behavior execution, perception polling, ECS mutation, physics queries, character motion or network authority. WORLD-03 owns cells/streaming; SIM-02 owns physics; SIM-03 owns character motion; CORE-03/04/06 own jobs/tick; DATA owns assets; GAME/NET own runtime authority.

## Ownership and boundaries

| Concern | Authority | SIM-05 may produce |
|---|---|---|
| Cells, residency, leases | WORLD-03 | cell/tile references only |
| Collision and physics queries | SIM-02 | opaque collider references |
| Character motion | SIM-03 | motion request descriptors |
| Jobs, tick, scheduling | CORE-03/04/06 | interval/tick-window descriptors |
| Scene and entity identity | WORLD-01/02 | optional entity references |
| Runtime authority | GAME/NET | proposals; owners decide |

## Risk and release class

- Planning risk: `LOW` for documentation and logical metadata.
- Future runtime navigation/AI risk: `ELEVATED`, explicitly out of scope for this sequence.
- Release class: `INTERNAL_ONLY`. No public ABI, release, hardware, performance, pathfinding-quality or production-readiness claim.

## Rejected alternatives

- Adopting Recast/Detour/BehaviorTree.CPP in this sequence; rejected because backend choice, license/SBOM and determinism proof are not executed.
- Building a bespoke navmesh generator or pathfinder; rejected because tiling, residency and replay obligations are unqualified.
- Executing steering/behavior graphs in this sequence; rejected because tick authority and bounded budgets are not implemented.
- Sensing from physics or scene state directly; rejected because SIM-02/WORLD ownership and event barriers are unresolved.
- Approving ADR-0035 wholesale for engine code; rejected because its proof obligations are not executed.

## Consequences

- Slice `-02` must freeze an exact header-only logical API, allowlist and test oracles before any code.
- Each implementation slice requires its own G6 activation gate.
- The module can close as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; it cannot claim pathfinding, crowd, behavior or perception readiness.
- Any future runtime navigation implementation requires a new owner-approved decision that resolves ADR-0035's proof obligations.
