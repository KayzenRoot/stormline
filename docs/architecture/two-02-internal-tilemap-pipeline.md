# TWO-02 internal tilemap and streaming metadata pipeline (INTERNAL_ONLY)

**Status:** `PROPOSED LOGICAL ARCHITECTURE / NO RENDERER / NO STREAMING I/O / NO PHYSICS`. **ADR:** [ADR-0124](../adr/0124-two-02-internal-tilemap-pipeline.md). **Governance:** [two-02-governance-v0](../contracts/two-02-governance-v0.md). **Queue:** `NLE-PRPLAN-TWO-02-01`.

## 1. Purpose

Describe the bounded logical model TWO-02 will implement before any tile renderer, map persistence, chunk streaming or physics integration. It validates tilemap metadata, derives deterministic plans and reports typed fallback/degradation reasons. It does not draw a tile, read a file or run a collision solver.

## 2. Modules and boundaries

- **TWO-02** owns logical grid/chunk math, tile cells, collision-authoring metadata, parallax and streaming plans.
- **TWO-01** owns Canvas sprite/layer rendering; **DATA-04/05** own durable authoring/cook; **GFX** owns GPU; **PHYS/WORLD** own collision truth and entities.
- No dependency is added to a renderer, file format, codec, cache, physics engine, navigation system or hardware driver.

## 3. Logical model

### 3.1 Grid and chunk math

- Map/layer IDs/revisions nonzero; tile size and chunk dimensions positive.
- Signed 64-bit cell coordinates with checked bounds and mathematical floor division; local coordinates in `[0,chunk_dimension)`.
- Negative cells must not use truncating division; overflow fails closed.

### 3.2 Tile cells

- Tile ID/revision, signed cell coordinates and layer reference.
- Flip/rotate flags validated against orthogonal orientation; empty sentinel explicit.
- No tile instance or draw is produced.

### 3.3 Collision authoring metadata

- Tile-local rectangle/segment shapes with finite vertices, positive extents and safe flags.
- Solidity/one-way policy metadata only; no contact, solver or activation receipt.
- Physics owns authoritative collision truth.

### 3.4 Parallax

- Per-axis finite factors, camera reference and repeat policy.
- No scroll transform or render execution.

### 3.5 Streaming plan

- Visible/prefetch rings, hysteresis, priority, job/byte budgets and typed chunk states.
- Bounded requested/ready/failed counts with exact receipts; no I/O, cache or async job.

## 4. Determinism and failure

- All plans are pure functions of validated inputs; stable IDs and declared order determine output.
- Errors are typed and fail closed; partial plans are not emitted.
- Stale revisions, out-of-bounds cells and budget exhaustion select declared safe paths.
- No allocation, exception, file, network, GPU, thread or global state in the internal implementation.

## 5. Test strategy

- Unit oracles for grid/chunk math, tile cells, collision-authoring shapes, parallax and streaming plans.
- Integrated qualification QLF-T201..T204: valid pipeline, deterministic repeat, failure recovery and 10,000 bounded attempts.
- Native CI on Linux/ASan/UBSan/TSan/Windows/macOS; no renderer, filesystem, physics or visual assertion.

## 6. Explicit non-goals

- No tile renderer, GPU buffer, texture, shader, batch or draw.
- No map save/reopen, chunk codec, cache, filesystem or streaming I/O.
- No Tiled/LDtk import or parser.
- No collision solver, physics activation, navigation or gameplay authority.
- No terrain autotiling, procedural generation or animation.
- No hardware, memory, 60 FPS or visual qualification.
- No public ABI, release or production readiness.

## 7. Failure and stop conditions

Stop on stale source, attempted renderer/GPU/import/physics selection, unbounded world/chunk/streaming, failed tests, HIGH/CRITICAL findings or any release/ABI claim.
