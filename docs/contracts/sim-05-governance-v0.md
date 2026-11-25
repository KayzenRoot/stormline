# SIM-05 governance contract v0 — internal logical navigation and behavior metadata

**Status:** `APPROVED GOVERNANCE / INTERNAL_ONLY / NO NAVIGATION RUNTIME`. **ADR:** [ADR-0136](../adr/0136-sim-05-internal-navigation-behavior-metadata.md). **Architecture:** [sim-05-internal-navigation-behavior-metadata](../architecture/sim-05-internal-navigation-behavior-metadata.md). **Planning-only policy:** [ADR-0035](../adr/0035-sim-05-engine-owned-navigation-and-behavior-authority.md) remains `PROPOSED`.

## 1. Scope

This contract governs the internal SIM-05 sequence: navmesh region descriptors, steering descriptors, behavior tree/statechart descriptors and NPC perception descriptors. It does not authorize Recast/Detour, navmesh build, path queries, steering, behavior execution, perception polling, physics queries, ECS mutation, editor UI or public ABI.

## 2. Invariants

1. **GOV-001 Fail closed:** invalid tile/area references, node kinds, weights, radii, intervals or budgets produce a typed error and zeroed output; no silent fallback.
2. **GOV-002 Single authority:** WORLD-03 owns cells/streaming, SIM-02 owns physics, SIM-03 owns motion, CORE-03/04/06 own jobs/tick, DATA owns assets, GAME/NET own authority.
3. **GOV-003 Identity separation:** nav/steering/behavior metadata is not a runtime handle and never exposes backend types or raw pointers.
4. **GOV-004 Determinism:** fixed-capacity plans, stable ordering where required, no allocation, exception, file, network, audio, GPU, clock, thread or global state.
5. **GOV-005 No runtime claim:** no navmesh build, path query, steering, behavior execution, perception polling, physics query or benchmark.
6. **GOV-006 Diagnostics:** every error carries a typed code, source ID and bounded index; output plans are reset before validation.
7. **GOV-007 Traceability:** one stable Work Order ID across issue, branch, PR, evidence and corrections; exact allowlists per slice.

## 3. Planned API areas (frozen only in `-02`)

- Navmesh intent: tile/cell refs, area tags, traversal cost, flags.
- Steering intent: behavior kinds, weights, radii, priorities.
- Behavior intent: node kinds, children counts, transitions, blackboard keys.
- Perception intent: sensor kinds, radii, cones, intervals, layer refs.
- Common diagnostic and capacity types under `src/stormline/navigation/`.

Exact type names, capacities, error enums and allowlists are frozen by `SIM-05-02` before implementation. No code may be created from this governance contract alone.

## 4. Slice oracles

| ID | Scenario | Oracle |
|---|---|---|
| NAV-01 | navmesh | unique tile IDs, area refs, finite cost, flags |
| STEER-01 | steering | kind allowlist, weights/radii bounds |
| BT-01 | behavior | node kind allowlist, child counts, transitions |
| PERC-01 | perception | sensor kinds, radii/cones/intervals, layer refs |
| QLF-S501 | integrated | navmesh -> steering -> behavior -> perception |
| QLF-S502 | deterministic repeat | identical plans/counts |
| QLF-S503 | failure recovery | typed error followed by valid operation |
| QLF-S504 | bounded overload | 10,000 attempts keep caps |

## 5. Out of scope

Navmesh build, pathfinding, steering execution, behavior runtime, perception polling, physics queries, ECS mutation, replay/snapshot, editor, GPU, audio, export, performance, ABI, release and production readiness.

## 6. Qualification statement

Passing internal CI qualification is not the catalog's navigation/tile validity/agent decision suite, pathfinding quality, determinism, security, soak or performance qualification. SIM-05 may close only as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
