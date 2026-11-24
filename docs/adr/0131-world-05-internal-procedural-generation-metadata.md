# ADR-0131 — Internal logical procedural generation metadata pipeline

**Status: APPROVED for bounded internal logical metadata only.** **Date:** 2026-11-24. **Module:** `WORLD-05` — Procedural Generation Framework. **Issue:** #45. **Keeps planning-only:** [ADR-0030](0030-world-05-versioned-deterministic-nondestructive-generation.md), which remains `PROPOSED / NOT APPROVED FOR ENGINE CODE`.

## Context

WORLD-05 must eventually provide deterministic, versioned and non-destructive procedural generation: seeds, generator graphs, rules, biome classification, geometry recipes and content generators. The full problem includes graph evaluation, canonical numeric profiles, noise libraries, WFC-style solvers, GPU previews, source overlays and real cross-platform golden vectors. Those runtime capabilities are not qualified and must not be claimed.

The module's formal predecessors, WORLD-04 and DATA-03, have completed their internal sequences and are available as capability sources. Their status is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.

## Decision

Approve a bounded internal sequence that produces **logical procedural-generation metadata only** under `src/stormline/procedural/`:

1. Seed and domain-derivation metadata with explicit nonzero domains and recipe identity fields; no RNG execution.
2. Generator graph topology metadata: stable node/edge identities, typed ports, acyclicity, depth and fan-out bounds; no evaluation.
3. Rule metadata: bounded condition/weight descriptors and precedence; no rule engine.
4. Biome classification metadata: stable zones, weights and palette references; no solver.
5. Geometry recipe metadata: bounded primitive/source descriptors and revisions; no mesh generation.
6. Content generator metadata: stable generator IDs, output categories, caps and provenance links; no artifact production.
7. Integrated deterministic validation, failure-recovery and bounded-overload qualification.

The sequence must not execute graphs, generate noise, run WFC, read assets, write scene/source data, allocate GPU resources or publish artifacts. WORLD-04 owns authored terrain/environment intent; DATA-02/03 own assets/import; DATA-04/05 own persistence/cook; WORLD-03 owns cells/streaming; CORE-05/06 own numeric and job infrastructure; GFX/PHYS/GAME/NET own runtime output and authority.

## Ownership and boundaries

| Concern | Authority | WORLD-05 may produce |
|---|---|---|
| Authored terrain/environment | WORLD-04 | recipe references and generator intents |
| Asset identity/import | DATA-02/03 | asset references and hashes placeholders |
| Persistence, journal, undo | DATA-04 | transaction metadata only |
| Cook/cache/streaming | DATA-05/WORLD-03 | recipe/scope descriptors |
| Numeric/coordinate math | CORE-05 | explicit profiles and bounds |
| Jobs, tick, cancellation | CORE-06 | budget intents only |
| Rendering, geometry, GPU | GFX-01..08 | recipe metadata only |
| Physics, gameplay, network authority | PHYS/GAME/NET | proposals; owners decide |
| Editor/CLI/MCP | EDIT | metadata inspection; no execution |

## Risk and release class

- Planning risk: `LOW` for documentation and logical metadata.
- Future runtime generation risk: `ELEVATED`, explicitly out of scope for this sequence.
- Release class: `INTERNAL_ONLY`. No public ABI, release, hardware, performance, security or production-readiness claim.

## Rejected alternatives

- Executing generator graphs in this sequence; rejected because evaluation, memory/time caps and canonical numeric profiles are unqualified.
- Embedding a noise library or WFC solver; rejected because licenses, golden vectors and cross-platform determinism are not proven.
- Writing generated artifacts into scenes or assets; rejected because DATA-04/05 and authoring owners hold that authority.
- Treating seeds alone as determinism identity; rejected because graph/algorithm/schema/asset versions are part of the recipe.
- Approving ADR-0030 wholesale for engine code; rejected because its proof obligations are not executed.

## Consequences

- Slice `-02` must freeze an exact header-only logical API, allowlist and test oracles before any code.
- Each implementation slice requires its own G6 activation gate.
- The module can close as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; it cannot claim generation, determinism across platforms or non-destructive regeneration readiness.
- Any future runtime procedural implementation requires a new owner-approved decision that resolves ADR-0030's proof obligations.
