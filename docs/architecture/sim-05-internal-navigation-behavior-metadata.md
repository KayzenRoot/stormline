# SIM-05 — Internal logical navigation and behavior metadata

**Status:** `APPROVED INTERNAL ARCHITECTURE / LOGICAL METADATA ONLY`. **ADR:** [ADR-0136](../adr/0136-sim-05-internal-navigation-behavior-metadata.md). **Planning policy remains:** [ADR-0035](../adr/0035-sim-05-engine-owned-navigation-and-behavior-authority.md) `PROPOSED`. **Runtime navigation claims:** none.

## 1. Purpose

Define a bounded, deterministic metadata layer for navmesh regions, steering, behavior trees/statecharts and NPC perception. It answers what an author configured, not how paths are built, agents are steered, decisions execute or senses are polled.

## 2. Logical model

- **Navmesh intent:** tile/cell references, area tags, traversal cost and flags.
- **Steering intent:** behavior kinds, weights, radii and priorities.
- **Behavior intent:** node kinds, children counts, transitions and blackboard keys.
- **Perception intent:** sensor kinds, radii, cones, intervals and layer references.
- **Diagnostics:** typed error plus source ID and index; outputs reset on failure.

## 3. Runtime non-goals

No Recast/Detour, tile build, path query, steering execution, behavior graph runtime, perception polling, physics query, ECS mutation, character motion, GPU, I/O or public ABI. Those remain future decisions under ADR-0035 and other module owners.

## 4. Ownership boundaries

- WORLD-03 owns cells/streaming; SIM-02 owns collision/physics.
- SIM-03 owns character motion; CORE-03/04/06 own jobs and tick.
- DATA owns assets; GAME/NET own runtime authority.
- SIM-05 owns only logical navigation/behavior intent metadata.

## 5. Determinism and bounds

All plans are fixed-capacity, header-only, `noexcept` and allocation-free. Capacities are frozen in `-02`; validation and overload behavior must be deterministic across compilers. No clock, random source, file, network, audio, GPU, thread, RTTI hash or global state is allowed.

## 6. Planned slices

| Slice | Logical deliverable | Oracle |
|---|---|---|
| `-03` | navmesh region metadata | NAV-01 |
| `-04` | steering metadata | STEER-01 |
| `-05` | behavior tree/statechart metadata | BT-01 |
| `-06` | NPC perception metadata | PERC-01 |
| `-07` | integrated qualification | QLF-S501..S504 |
| `-08` | closeout | evidence/audit |

`-02` must freeze exact types, capacities, error codes, allowlists and test fixtures before `-03` is activated.

## 7. Explicit non-goals

No navmesh build, pathfinding, steering, behavior execution, perception polling, replay, ECS mutation, GPU, hardware measurement or public ABI. ADR-0035 remains the separate planning authority for those future runtime decisions.
