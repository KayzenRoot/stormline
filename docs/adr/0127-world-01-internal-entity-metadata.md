# ADR-0127 — Internal logical entity/component metadata pipeline

**Status: APPROVED for bounded internal logical metadata only.** **Date:** 2026-11-24. **Module:** `WORLD-01` — Entity Component Model. **Issue:** #41. **Keeps planning-only:** [ADR-0026](0026-world-01-entity-identity-storage-policy.md), which remains `PROPOSED / NOT APPROVED FOR ENGINE CODE`.

## Context

WORLD-01 must eventually provide safe entity identity, typed components, lifecycle, queries and schema reflection across editor, headless and gameplay. The full problem includes memory ownership, concurrency, serialization, storage layout and server authority. Those runtime capabilities are not yet qualified and must not be claimed by documentation.

The module's formal predecessors, CORE-05 and DATA-04, have completed their internal sequences and are available as capability sources. Their status is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.

## Decision

Approve a bounded internal sequence that produces **logical entity/component metadata only** under `src/stormline/world/`:

1. Generational entity handle intent metadata (slot, generation, world epoch, validity).
2. Component type identity/schema intent metadata (stable type IDs, versions, bounded fields).
3. Entity lifecycle transition intent metadata (create/destroy states, tombstones, idempotent receipts).
4. Query intent metadata over required/excluded component type IDs.
5. Component reflection field metadata (names, kinds, bounds) without runtime reflection.

The sequence must not create an ECS storage engine, archetype/sparse-set container, allocator, job system, serialization codec, scene hierarchy, spatial index, physics authority or public ABI. DATA-04 owns persistence/undo; WORLD-02 owns hierarchy; DATA-02 owns stable source identity.

## Ownership and boundaries

| Concern | Authority | WORLD-01 may produce |
|---|---|---|
| Stable persistent GUIDs, assets | DATA-02/DATA-04 | opaque references and resolution status |
| Scene persistence, journal, CAS | DATA-04 | lifecycle and schema intents |
| Hierarchy, prefabs, transforms | WORLD-02 | component IDs only; no parent index |
| Spatial index, streaming | WORLD-03 | none |
| Memory, jobs, math | CORE-01/02/03/05 | bounded metadata only |
| Physics, gameplay, network authority | SIM/PHYS/GAME/NET | component IDs and typed intent |
| GPU, Canvas, animation, hybrid | GFX/TWO | none |

## Risk and release class

- Planning risk: `LOW` for documentation and logical metadata.
- Future runtime ECS risk: `ELEVATED`, explicitly out of scope for this sequence.
- Release class: `INTERNAL_ONLY`. No public ABI, release, hardware, performance, security or production-readiness claim.

## Rejected alternatives

- Implementing archetype/sparse-set storage in this sequence; rejected because storage policy remains an open benchmark decision.
- Using compiler `typeid` hashes as persistent component identity; rejected because it is not stable across compilers.
- Serializing raw slot/generation handles; rejected because persistent and runtime identity differ.
- Approving ADR-0026 wholesale for engine code; rejected because its runtime proof obligations are not executed.

## Consequences

- Slice `-02` must freeze an exact header-only logical API, allowlist and test oracles before any code.
- Each implementation slice requires its own G6 activation gate.
- The module can close as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; it cannot claim ECS runtime readiness.
- Any future runtime ECS requires a new owner-approved decision that resolves ADR-0026's proof obligations.
