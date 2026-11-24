# ADR-0128 — Internal logical scene/prefab metadata pipeline

**Status: APPROVED for bounded internal logical metadata only.** **Date:** 2026-11-24. **Module:** `WORLD-02` — Scene & Prefab Hierarchy. **Issue:** #42. **Keeps planning-only:** [ADR-0027](0027-world-02-prefab-override-rebase-policy.md), which remains `PROPOSED / NOT APPROVED FOR CODE`.

## Context

WORLD-02 must eventually provide reusable scene graphs, nested prefabs, variants, instancing and controlled override propagation with undo/redo. The full problem includes durable asset identity, three-way rebase, transform math, transactions and persistence. Those runtime capabilities are not yet qualified and must not be claimed by documentation.

The module's formal predecessors, WORLD-01 and DATA-02, have completed their internal sequences and are available as capability sources. Their status is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.

## Decision

Approve a bounded internal sequence that produces **logical scene/prefab metadata only** under `src/stormline/scene/`:

1. Scene hierarchy forest metadata (stable node IDs, single parent, cycle/depth rejection, ordered siblings).
2. Prefab composition metadata (nested source references, bounded depths, composition layers).
3. Prefab variant/override metadata (field-level overrides, mismatch detection, rebase receipts).
4. Instance expansion metadata (bounded fan-out and expansion counts; no runtime entity creation).
5. Transform intent metadata (finite local TRS values, reparent mode intent; no matrix composition).

The sequence must not create a runtime scene graph, ECS storage, prefab serializer, asset database, three-way merge engine, undo journal, transform solver, spatial index, physics authority or editor UI. DATA-02/04 remain authoritative for assets, source revisions and journal; WORLD-01 remains authoritative for entity/component metadata.

## Ownership and boundaries

| Concern | Authority | WORLD-02 may produce |
|---|---|---|
| Entity/component metadata | WORLD-01 | opaque references and hierarchy intents |
| Asset identity/provenance | DATA-02 | opaque prefab/scene references |
| Persistence, CAS, undo/redo | DATA-04 | change-set and rebase intent metadata |
| Import/cooked assets | DATA-03/05 | opaque references and readiness status |
| Transform math | CORE-05 | finite TRS intent; no matrix composition |
| Spatial index/streaming | WORLD-03 | none |
| Physics/gameplay/network | SIM/PHYS/GAME/NET | typed transform intents only |
| Rendering/editor UI | GFX/EDIT/UI | none |

## Risk and release class

- Planning risk: `LOW` for documentation and logical metadata.
- Future runtime graph/prefab risk: `ELEVATED`, explicitly out of scope for this sequence.
- Release class: `INTERNAL_ONLY`. No public ABI, release, hardware, performance, security or production-readiness claim.

## Rejected alternatives

- Implementing prefab expansion or override rebase at runtime; rejected because ADR-0027's proof obligations are not executed.
- Treating names/paths as identity; rejected because renames/reparents would break references.
- Serializing runtime entity handles; rejected because persistent and transient identity differ.
- Approving ADR-0027 wholesale for engine code; rejected because its runtime proof obligations are not executed.

## Consequences

- Slice `-02` must freeze an exact header-only logical API, allowlist and test oracles before any code.
- Each implementation slice requires its own G6 activation gate.
- The module can close as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; it cannot claim scene/prefab runtime readiness.
- Any future runtime scene/prefab implementation requires a new owner-approved decision that resolves ADR-0027's proof obligations.
