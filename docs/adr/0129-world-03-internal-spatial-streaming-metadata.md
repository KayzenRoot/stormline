# ADR-0129 — Internal logical spatial index and streaming metadata pipeline

**Status: APPROVED for bounded internal logical metadata only.** **Date:** 2026-11-24. **Module:** `WORLD-03` — Spatial Index & World Streaming. **Issue:** #43. **Keeps planning-only:** [ADR-0028](0028-world-03-budgeted-spatial-streaming-policy.md), which remains `PROPOSED / NOT APPROVED FOR ENGINE CODE`.

## Context

WORLD-03 must eventually provide coarse spatial cells, interest queries, a coordinated spatial origin and asynchronous world streaming without main-thread stalls beyond an approved budget. The full problem includes I/O, decoding, threading, memory pressure, physics/network coordination and real traversal benchmarks. Those runtime capabilities are not yet qualified and must not be claimed by documentation.

The module's formal predecessors, WORLD-02 and DATA-05, have completed their internal sequences and are available as capability sources. Their status is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.

## Decision

Approve a bounded internal sequence that produces **logical spatial/streaming metadata only** under `src/stormline/spatial/`:

1. Signed cell-coordinate and cell-key intent metadata with checked arithmetic and negative-coordinate floor behavior.
2. Interest-query metadata (bounded bounds union, priorities, roles, completeness status).
3. Spatial origin epoch request metadata (old/new origin, epoch, owner acknowledgement fields).
4. Streaming plan metadata (cell request states, priorities, budgets and cancellation generations; no async execution).

The sequence must not create an asynchronous task system, file/network I/O, decoder, cache, GPU resource, physics broadphase, network replication, renderer or public ABI. DATA-05 owns I/O/decode/cache; CORE owns scheduling; WORLD-02 owns scene source; PHYS/NET own runtime authority.

## Ownership and boundaries

| Concern | Authority | WORLD-03 may produce |
|---|---|---|
| Scene/prefab source | WORLD-02 | opaque cell references and source revisions |
| I/O, decode, cache | DATA-05 | bounded request/priority metadata |
| Scheduling, threads, fixed tick | CORE-03/06 | intent and cancellation generation only |
| Entity lifecycle | WORLD-01 | cell/residency references only |
| Physics, AI, gameplay authority | PHYS/AI/GAME | interest pins and priority intents |
| Network replication | NET | interest proposals; NET decides visibility |
| Rendering, GPU residency | GFX-03/04 | none |
| Coordinate math | CORE-05 | checked cell/origin intent; no transforms |

## Risk and release class

- Planning risk: `LOW` for documentation and logical metadata.
- Future runtime streaming risk: `ELEVATED`, explicitly out of scope for this sequence.
- Release class: `INTERNAL_ONLY`. No public ABI, release, hardware, performance, security or production-readiness claim.

## Rejected alternatives

- Implementing asynchronous streaming or I/O in this sequence; rejected because DATA-05/CORE own it and ADR-0028's proof obligations are not executed.
- Treating render origin as durable cell identity; rejected because cell keys and GUIDs must survive rebasing.
- Camera-only loading; rejected because simulation-critical content requires explicit pins and owner priorities.
- Approving ADR-0028 wholesale for engine code; rejected because its runtime proof obligations are not executed.

## Consequences

- Slice `-02` must freeze an exact header-only logical API, allowlist and test oracles before any code.
- Each implementation slice requires its own G6 activation gate.
- The module can close as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; it cannot claim streaming or traversal performance readiness.
- Any future runtime streaming implementation requires a new owner-approved decision that resolves ADR-0028's proof obligations.
