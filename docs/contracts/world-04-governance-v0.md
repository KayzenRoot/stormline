# WORLD-04 governance contract v0 — internal logical terrain/environment metadata

**Status:** `APPROVED GOVERNANCE / INTERNAL_ONLY / NO TERRAIN OR ENVIRONMENT RUNTIME`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Architecture:** [world-04-internal-terrain-environment-metadata](../architecture/world-04-internal-terrain-environment-metadata.md). **Planning-only policy:** [ADR-0029](../adr/0029-world-04-authored-terrain-environment-visual-ownership.md) remains `PROPOSED`.

## 1. Scope

This contract governs the internal WORLD-04 sequence: logical terrain patch metadata, splat/material layer descriptors, vegetation placement metadata, water body metadata, sky/environment profiles and weather visual intents. It does not authorize heightfield storage, mesh generation, terrain/water rendering, GPU LOD, texture residency, vegetation instancing, physics colliders, weather simulation, editor UI or public ABI.

## 2. Invariants

1. **GOV-001 Fail closed:** invalid identities, coordinates, weights, ranges, ticks or budgets produce a typed error and zeroed output; no silent fallback.
2. **GOV-002 Single authority:** WORLD-02/03 own scene and spatial intent, GFX-04..08 own rendering, DATA-04/05 own persistence/cook/streaming, PHYS/GAME/NET own simulation and truth, CORE-05 owns math.
3. **GOV-003 Identity separation:** durable terrain/patch/vegetation identities are independent of render origin, LOD level and runtime epochs.
4. **GOV-004 Determinism:** fixed-capacity plans, stable ordering where required, no allocation, exception, file, network, audio, GPU, clock, thread or global state.
5. **GOV-005 No runtime claim:** no heightfield/mesh storage, mesh generation, rendering, simulation, collision, texture residency or benchmark.
6. **GOV-006 Diagnostics:** every error carries a typed code, source ID and bounded index; output plans are reset before validation.
7. **GOV-007 Traceability:** one stable Work Order ID across issue, branch, PR, evidence and corrections; exact allowlists per slice.

## 3. Planned API areas (frozen only in `-02`)

- Terrain patch intent: stable patch ID, signed tile coordinates, LOD, neighbor refs, revision.
- Splat layer intent: bounded normalized channel weights, material asset refs, precedence.
- Vegetation intent: stable group/instance IDs, prototype refs, density bounds, collider declaration.
- Water intent: body ID/class, finite region and shore metadata, visual wave parameters.
- Sky intent: time-of-day, finite directions and ranges, quality tier.
- Weather intent: source tick/revision, finite precipitation/wind intensities, target systems.
- Common diagnostic and capacity types under `src/stormline/terrain/`.

Exact type names, capacities, error enums and allowlists are frozen by `WORLD-04-02` before implementation. No code may be created from this governance contract alone.

## 4. Slice oracles

| ID | Scenario | Oracle |
|---|---|---|
| TER-01 | terrain patches | stable IDs, signed tiles, LOD, neighbors, revision |
| SPL-01 | splat layers | normalized finite weights, precedence, material refs |
| VEG-01 | vegetation | unique instances/groups, density bounds, collider intent |
| WAT-01 | water | body classes, finite region/shore, wave ranges |
| SKY-01 | sky profiles | time/direction/range limits, quality tier |
| CLI-01 | weather | source tick/revision, finite intensities, target systems |
| QLF-W401 | integrated | terrain -> splat -> vegetation -> water -> sky -> weather |
| QLF-W402 | deterministic repeat | identical plans/counts |
| QLF-W403 | failure recovery | typed error followed by valid operation |
| QLF-W404 | bounded overload | 10,000 attempts keep caps |

## 5. Out of scope

Heightfield/mesh storage, mesh generation, terrain/water rendering, GPU geometry/LOD, texture residency, vegetation instancing, atmosphere/weather simulation, physics/network coordination, editor, audio, export, performance, ABI, release and production readiness.

## 6. Qualification statement

Passing internal CI qualification is not physical, OS, security, soak, rendering, simulation, traversal or performance qualification. WORLD-04 may close only as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
