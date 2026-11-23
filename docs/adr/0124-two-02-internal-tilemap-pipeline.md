# ADR-0124 — Bounded internal 2D tilemap, collision metadata and streaming planning

**Status:** `APPROVED FOR INTERNAL LOGICAL PIPELINE ONLY` — owner-authorized continuation, 2026-11-23. **Keeps:** [ADR-0023](0023-two-02-sparse-chunk-tilemap-policy.md) as planning-only context.

## Context

TWO-01 completed its internal sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. TWO-02 research, architecture and ADR-0023 exist, but no tilemap renderer, editor save/load, chunk file I/O, collision solver, physics activation, streaming runtime or hardware qualification is authorized. A fail-closed logical layer is required before any backend work.

## Decision

Ratify a first TWO-02 internal pipeline that validates and plans metadata only:

1. **Signed grid/chunk math.** Stable map/layer IDs/revisions, positive tile/chunk dimensions, signed 64-bit cell coordinates, checked bounds and mathematical floor division for negative cells; local chunk coordinates are returned. No GPU coordinate or upload exists.
2. **Tile cells.** Stable tile IDs, bounded layer/cell coordinates, flip/rotate flags validated against declared orientation, and explicit empty sentinel. No tile instance, sprite or draw is produced.
3. **Collision authoring metadata.** Bounded tile-local rectangles/segments, solidity/one-way flags and stable revisions. Physics remains authoritative; no contact, solver or activation receipt is produced.
4. **Parallax metadata.** Per-axis finite scroll factors, camera reference and repeat policy. No render transform or scroll is executed.
5. **Streaming plan.** Visible/prefetch rings, hysteresis, priority, job/byte budgets and typed chunk states (`Unloaded/Requested/Fetching/Cancelled/Failed/Ready`). No file, cache, async I/O or residency mutation occurs.
6. **Boundaries.** DATA-02/03/04/05 own identity/import/authoring/cook; TWO-01 owns Canvas/sprite rendering; GFX owns GPU resources; PHYS/WORLD own collision truth and entities. TWO-02 owns only logical map/collision-authoring/streaming plans.

## Non-decisions

- No tilemap renderer, GPU buffer, texture upload, shader, batch, draw or fence.
- No editor save/reopen, chunk codec/compression, filesystem/cache/streaming I/O or async job execution.
- No Tiled/LDtk import, parser, external format or GPL/BSD tool integration.
- No collision solver, contact, broadphase, physics activation receipt, navigation or gameplay authority.
- No terrain autotiling/Wang rules, procedural generation, parallax execution or animation.
- No visual golden, 60 FPS, hardware, driver, memory or performance qualification.
- No public ABI, release class beyond `INTERNAL_ONLY`, engine license decision or production-readiness claim.

## Ownership

- TWO-02 owns logical grid/chunk, tile cell, collision-authoring, parallax and streaming plans with typed failure metadata.
- It does not own renderers, GPU resources, assets, files, caches, physics, world entities, navigation or gameplay state.

## Consequences

- The layer is deterministic and testable on every CI platform without a GPU, filesystem or physics engine.
- Any future renderer, importer, persistence, streaming runtime or collision activation requires a new owner-approved contract/slice and platform evidence.
- ADR-0023 remains planning context; this ADR neither ratifies its Tiled/LDtk, GPU, editor or physics decisions nor selects any dependency.

## Evidence gates

Contract `TWO-02-02`, five implementation slices `-03`..`-07`, qualification `-08`, closeout `-09`, exact-head native CI and pt-BR audit. Stop on stale source, native GPU/render/import/physics selection, released ABI or HIGH/CRITICAL.
