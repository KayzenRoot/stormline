# WORLD-05 — Internal logical procedural generation metadata

**Status:** `APPROVED INTERNAL ARCHITECTURE / LOGICAL METADATA ONLY`. **ADR:** [ADR-0131](../adr/0131-world-05-internal-procedural-generation-metadata.md). **Planning policy remains:** [ADR-0030](../adr/0030-world-05-versioned-deterministic-nondestructive-generation.md) `PROPOSED`. **Runtime generation claims:** none.

## 1. Purpose

Define a bounded, deterministic metadata layer for seeds, generator graph topology, rules, biome classification, geometry recipes and content generators. It answers what recipe a project authored and how its parts relate, not how a graph is evaluated, how noise is computed or how artifacts are produced.

## 2. Logical model

- **Seed intent:** master seed halves, domain labels and derivation-version metadata; no random stream.
- **Graph intent:** stable graph/node/edge identities, typed ports, acyclic topology, depth and fan-out bounds.
- **Rule intent:** bounded condition codes, weights and precedence; no rule evaluation.
- **Biome intent:** stable zone IDs, weights, palette references and priority.
- **Geometry recipe intent:** bounded primitive/source descriptors, units and revisions; no mesh output.
- **Content generator intent:** stable generator IDs, output categories, caps and provenance links; no artifacts.
- **Diagnostics:** typed error plus source ID and index; outputs reset on failure.

## 3. Runtime non-goals

No graph interpreter, RNG/noise implementation, WFC solver, asset import, cache/cook, source or scene writes, GPU preview, artifact publication, editor UI, I/O or public ABI. Those remain future decisions under ADR-0030 and other module owners.

## 4. Ownership boundaries

- WORLD-04 owns authored terrain/environment intent; DATA-02/03 own assets/import.
- DATA-04/05 own persistence/journal/cook; WORLD-03 owns streaming cells.
- CORE-05/06 own numeric infrastructure and jobs; GFX-01..08 own rendering.
- PHYS/GAME/NET own simulation and authority.
- WORLD-05 owns only logical generation metadata.

## 5. Determinism and bounds

All plans are fixed-capacity, header-only, `noexcept` and allocation-free. Capacities are frozen in `-02`; validation and overload behavior must be deterministic across compilers. No clock, random source, file, network, audio, GPU, thread, RTTI hash or global state is allowed.

## 6. Planned slices

| Slice | Logical deliverable | Oracle |
|---|---|---|
| `-03` | seed/domain metadata | SEED-01 |
| `-04` | generator graph topology metadata | GRAPH-01 |
| `-05` | rule metadata | RULE-01 |
| `-06` | biome classification metadata | BIOME-01 |
| `-07` | geometry recipe metadata | GEO-01 |
| `-08` | content generator metadata | GEN-01 |
| `-09` | integrated qualification | QLF-W501..W504 |
| `-10` | closeout | evidence/audit |

`-02` must freeze exact types, capacities, error codes, allowlists and test fixtures before `-03` is activated.

## 7. Explicit non-goals

No graph evaluation, seed stream, noise, WFC, asset I/O, cook/cache, scene/source write, mesh generation, GPU preview, benchmark, hardware measurement or public ABI. ADR-0030 remains the separate planning authority for those future runtime decisions.
