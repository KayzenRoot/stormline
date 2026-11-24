# WORLD-05 governance contract v0 — internal logical procedural generation metadata

**Status:** `APPROVED GOVERNANCE / INTERNAL_ONLY / NO GENERATION RUNTIME`. **ADR:** [ADR-0131](../adr/0131-world-05-internal-procedural-generation-metadata.md). **Architecture:** [world-05-internal-procedural-generation-metadata](../architecture/world-05-internal-procedural-generation-metadata.md). **Planning-only policy:** [ADR-0030](../adr/0030-world-05-versioned-deterministic-nondestructive-generation.md) remains `PROPOSED`.

## 1. Scope

This contract governs the internal WORLD-05 sequence: logical seed/domain metadata, generator graph topology, rule descriptors, biome classification, geometry recipes and content generator metadata. It does not authorize graph evaluation, RNG/noise, WFC solvers, asset I/O, cook/cache, artifact publication, editor UI or public ABI.

## 2. Invariants

1. **GOV-001 Fail closed:** invalid identities, seeds, ports, weights, references or budgets produce a typed error and zeroed output; no silent fallback.
2. **GOV-002 Single authority:** WORLD-04 owns authored environment intent, DATA-02/03 assets/import, DATA-04/05 persistence/cook, WORLD-03 streaming, CORE-05/06 numeric/jobs, GFX/PHYS/GAME/NET runtime authority.
3. **GOV-003 Recipe identity separation:** seed metadata is not the full determinism identity; graph/algorithm/schema/asset versions are separate required fields.
4. **GOV-004 Determinism:** fixed-capacity plans, stable ordering where required, no allocation, exception, file, network, audio, GPU, clock, thread or global state.
5. **GOV-005 No runtime claim:** no graph execution, noise, WFC, artifact production, cache, source write, GPU preview or benchmark.
6. **GOV-006 Diagnostics:** every error carries a typed code, source ID and bounded index; output plans are reset before validation.
7. **GOV-007 Traceability:** one stable Work Order ID across issue, branch, PR, evidence and corrections; exact allowlists per slice.

## 3. Planned API areas (frozen only in `-02`)

- Seed intent: master seed halves, domain labels, derivation version.
- Graph intent: stable graph/node/edge IDs, typed ports, acyclicity, depth/fan-out limits.
- Rule intent: condition codes, weights, precedence.
- Biome intent: zone IDs, weights, palette references, priority.
- Geometry intent: primitive/source descriptors, units, revision.
- Content generator intent: generator IDs, output categories, caps, provenance links.
- Common diagnostic and capacity types under `src/stormline/procedural/`.

Exact type names, capacities, error enums and allowlists are frozen by `WORLD-05-02` before implementation. No code may be created from this governance contract alone.

## 4. Slice oracles

| ID | Scenario | Oracle |
|---|---|---|
| SEED-01 | seeds/domains | nonzero halves, allowlisted domains, derivation version |
| GRAPH-01 | graph topology | unique node/edge IDs, ports, acyclicity, depth/fan-out |
| RULE-01 | rules | condition/weight ranges, precedence, uniqueness |
| BIOME-01 | biomes | unique zones, weight ranges, palette refs, priority |
| GEO-01 | geometry recipes | primitive/source descriptors, units, revisions |
| GEN-01 | content generators | unique generator IDs, output categories, caps |
| QLF-W501 | integrated | seed -> graph -> rule -> biome -> geometry -> generator |
| QLF-W502 | deterministic repeat | identical plans/counts |
| QLF-W503 | failure recovery | typed error followed by valid operation |
| QLF-W504 | bounded overload | 10,000 attempts keep caps |

## 5. Out of scope

Graph evaluation, RNG/noise implementations, WFC/constraint solvers, asset import, cache/cook, source/scene writes, mesh generation, GPU preview, editor, audio, export, performance, ABI, release and production readiness.

## 6. Qualification statement

Passing internal CI qualification is not deterministic cross-platform generation, golden-vector, non-destructive regeneration, security, soak or performance qualification. WORLD-05 may close only as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
