# GFX-08 internal VFX graph and effect metadata pipeline (INTERNAL_ONLY)

**Status:** `PROPOSED LOGICAL ARCHITECTURE / NO GPU / NO PARTICLE SIMULATION / NO VISUAL QUALIFICATION`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Governance:** [gfx-08-governance-v0](../contracts/gfx-08-governance-v0.md). **Queue:** `NLE-PRPLAN-GFX-08-01`.

## 1. Purpose

Describe the bounded logical model GFX-08 will implement before any particle runtime, compute, sorting, volumetric renderer or visual work. It validates VFX graph/effect metadata, derives deterministic plans and reports typed fallback/degradation reasons. It does not simulate or render a particle.

## 2. Modules and boundaries

- **GFX-08** owns logical VFX graph shape, emitter/spawn budgets, ribbon/trail plans, blend policy, density-stamp metadata and pool/quality budgets.
- **GFX-01** owns device capabilities and presentation; **GFX-02** shader compilation; **GFX-03** render graph/resources/fences; **GFX-04** visibility/depth/velocity semantics.
- **GFX-05** owns materials, alpha and textures; **GFX-06** owns lights, GI and volumetric scattering; **GFX-07** owns HDR/post/reconstruction.
- **DATA-02/03/04/05** own asset identity, import, durable authoring and cook receipts.

No dependency is added to a native graphics API, compute backend, particle SDK, volume codec, sorting library, asset plugin or hardware driver.

## 3. Logical model

### 3.1 Graph and nodes

- Stable graph/node IDs and revisions, allowlisted node kinds and typed ports, bounded node/edge counts.
- Acyclic validation rejects self/duplicate edges, foreign node references and cycles.
- Unknown node kinds, missing required ports and type mismatches fail closed.
- No graph is interpreted, compiled, uploaded or executed.

### 3.2 Emitter and spawn budget

- Emitter ID/revision, rate/burst, lifetime, seed and simulation-policy metadata.
- Spawn counts use checked arithmetic and explicit per-tick caps; overflow fails closed.
- Negative/non-finite rates, zero lifetime and stale graph revisions are rejected.
- No PRNG stream, particle state, substep or compaction is created.

### 3.3 Ribbon plan

- Source references, sample count, segment/vertex caps, width and join metadata.
- Degenerate or non-monotonic sample input, zero length and cap overflow fail closed.
- No spline, tessellation, strip or vertex buffer is produced.

### 3.4 Trail plan

- Ordered sample ages, segment cap, vertex budget, rollover and width metadata.
- Duplicate/out-of-order samples and non-finite age/width are rejected.
- No trail history, buffer or geometry exists.

### 3.5 Transparency/blend policy

- GFX-05 material ID/revision, blend mode, depth test/write policy, premultiplied-alpha and sort/OIT declaration.
- Unsupported blend/depth combinations and unknown material generations fail closed.
- Weighted OIT remains explicitly approximate; no sorting or pixel composition runs.

### 3.6 Volumetric density stamp

- Bounded density/extinction, density scale, region and time metadata for a GFX-06-owned fog/scattering path.
- Non-finite/negative density or zero extents fail closed.
- GFX-06 owns scattering, shadowing, froxel storage and rendering; GFX-08 authors density intent only.

### 3.7 Pool and quality budget

- Fixed pool capacity/generation metadata and per-tier caps for particles, ribbons, trails, overdraw, sorts and light requests.
- Admission returns requested/actual counts and typed degradation reasons without allocating a pool.
- Stale generations and exhausted capacity fail closed or degrade deterministically as declared.

## 4. Determinism and failure

- All plans are pure functions of validated inputs; stable IDs and declared order determine output.
- Errors are typed and fail closed; partial plans are not emitted.
- Stale graph revisions, pool generations and device epochs select a declared safe path rather than reusing stale metadata.
- No allocation, exception, file, network, thread or global state in the internal implementation.

## 5. Test strategy

- Unit oracles for graph shape, emitter/spawn, ribbon, trail, blend, density stamp and pool/budget.
- Integrated qualification QLF-G801..G804: valid pipeline, deterministic repeat, failure recovery and 10,000 bounded attempts.
- Native CI on Linux/ASan/UBSan/TSan/Windows/macOS; no simulation, GPU or visual assertion.

## 6. Explicit non-goals

- No particle simulation or rendering, compute shader, storage buffer or GPU sort.
- No OIT, volumetric ray march, froxel grid, VDB decoder or flipbook playback.
- No Effekseer/OpenVDB/AMD Parallel Sort/SVAG integration.
- No GPU, driver, VRAM, frame-time, visual or hardware qualification.
- No public ABI, release or production readiness.

## 7. Failure and stop conditions

Stop on stale source, attempted native GPU/compute/sort/SDK selection, gameplay-authority leakage, unbounded graph/spawn/geometry, failed tests, HIGH/CRITICAL findings or any release/ABI claim.
