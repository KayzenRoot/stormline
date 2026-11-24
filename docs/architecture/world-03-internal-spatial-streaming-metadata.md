# WORLD-03 — Internal logical spatial/streaming metadata

**Status:** `APPROVED INTERNAL ARCHITECTURE / LOGICAL METADATA ONLY`. **ADR:** [ADR-0129](../adr/0129-world-03-internal-spatial-streaming-metadata.md). **Planning policy remains:** [ADR-0028](../adr/0028-world-03-budgeted-spatial-streaming-policy.md) `PROPOSED`. **Runtime streaming claims:** none.

## 1. Purpose

Define a bounded, deterministic metadata layer for cell coordinates, interest queries, spatial origin requests and streaming plans without executing I/O, decoding, threading or resource residency. It answers what cells and priorities a world requested, not how data is fetched, cached or committed.

## 2. Logical model

- **Cell coordinate intent:** signed global cell coordinates, checked floor division for negatives, cell keys and world identity.
- **Interest query intent:** bounded axis-aligned bounds, source role/priority, exact/approx mode, completeness status.
- **Origin epoch intent:** old/new origin candidate, epoch, and owner acknowledgement placeholders; no rebase execution.
- **Streaming plan intent:** cell request states, priority classes, bounded budget counts, request/cancellation generations; no async task or I/O.
- **Diagnostics:** typed error plus source ID and index; outputs reset on failure.

## 3. Runtime non-goals

No asynchronous task system, thread pool, file/network I/O, decompression, cache, GPU/VRAM lease, physics broadphase, network replication, scene expansion, renderer, editor UI or public ABI. Those remain future decisions under ADR-0028 and other module owners.

## 4. Ownership boundaries

- WORLD-02 owns scene/prefab source; WORLD-01 entity lifecycle.
- DATA-05 owns I/O/decode/cache; CORE-03/06 own scheduling and tick barriers.
- CORE-05 owns coordinate math; GFX-03/04 own GPU/render residency.
- PHYS/AI/GAME/NET own simulation, gameplay and replication authority.
- WORLD-03 owns only logical spatial/streaming intent metadata.

## 5. Determinism and bounds

All plans are fixed-capacity, header-only, `noexcept` and allocation-free. Capacities are frozen in `-02`; slicing and overload behavior must be deterministic across compilers. No clock, random source, file, network, audio, GPU, thread, RTTI hash or global state is allowed.

## 6. Planned slices

| Slice | Logical deliverable | Oracle |
|---|---|---|
| `-03` | cell coordinate/key metadata | CEL-01 |
| `-04` | interest query metadata | INT-01 |
| `-05` | spatial origin epoch metadata | ORG-01 |
| `-06` | streaming plan metadata | STR-01 |
| `-07` | integrated qualification | QLF-W301..W304 |
| `-08` | closeout | evidence/audit |

`-02` must freeze exact types, capacities, error codes, allowlists and test fixtures before `-03` is activated.

## 7. Explicit non-goals

No streaming execution, async work, I/O, decode, cache, memory pressure handling, origin rebase execution, spatial index queries, result sets, physics/network coordination, renderer, editor, benchmark, hardware measurement or public ABI. ADR-0028 remains the separate planning authority for those future runtime decisions.
