# ADR-0122 — Bounded internal VFX graph and effect metadata planning

**Status:** `APPROVED FOR INTERNAL LOGICAL PIPELINE ONLY` — owner-authorized continuation, 2026-11-23. **Keeps:** [ADR-0021](0021-gfx-08-vfx-graph-particle-policy.md) as planning-only context.

## Context

GFX-07 completed its internal sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. GFX-08 research, architecture and ADR-0021 exist, but no CPU/GPU particle simulation, compute, sorting, OIT, volumetric rendering, shader, renderer or hardware qualification is authorized. A fail-closed logical layer is required before any backend work.

## Decision

Ratify a first GFX-08 internal pipeline that validates and plans VFX metadata only:

1. **Graph shape.** Stable graph/node IDs and revisions, allowlisted node kinds and typed ports, acyclic edge validation, bounded node/edge counts and explicit rejection of unknown nodes, cycles, duplicate IDs and invalid references. No graph is interpreted, compiled or executed.
2. **Particle emitter/spawn budget.** Emitter and instance metadata with finite rate/burst/lifetime/seed fields, declared simulation policy and checked per-tick spawn caps. No particle is spawned, integrated or rendered.
3. **Ribbon plan.** Source references, sample count, segment/vertex caps and join/width metadata with checked arithmetic and degenerate-input rejection. No spline is tessellated or drawn.
4. **Trail plan.** Ordered samples, age/lifetime, segment/vertex budgets, rollover and invalid-segment rejection. No trail buffer or geometry exists.
5. **Transparency/blend policy.** Material-owned blend mode, depth policy, premultiplied-alpha flag and declared sort/OIT approximation metadata. No sort, OIT or pixel compositing executes.
6. **Volumetric density stamp.** Bounded density/extinction/region/time metadata compatible with GFX-06 ownership of scattering and fog grids. No volume is baked, sampled or rendered.
7. **Pooling/quality budget.** Fixed pool capacity, generation metadata and quality-tier caps for particles, ribbons, trails, overdraw and light requests, with typed degradation receipts. No pool allocation or GPU resource is created.
8. **Boundaries.** GFX-01 device capability, GFX-02 shaders, GFX-03 graph/resources/fences, GFX-04 visibility/depth, GFX-05 materials/alpha, GFX-06 lighting/volumetrics, GFX-07 HDR/post and DATA-02/03/04/05 identity/import/authoring/cook remain authoritative. GFX-08 owns only logical VFX graph and effect plans.

## Non-decisions

- No Vulkan/D3D12/Metal/WebGPU, compute pipeline, storage buffer, GPU allocator, RenderGraph pass or fence.
- No CPU or GPU particle simulation, PRNG stream, substep execution, compaction, sorting or collision approximation.
- No shader compilation/bytecode, arbitrary user shader, Effekseer runtime, OpenVDB/NanoVDB decoder, AMD Parallel Sort or SVAG governor.
- No ribbon/trail tessellation, sprite, mesh, flipbook, volumetric or particle draw.
- No visual golden, hardware, driver, VRAM, frame-time, latency or quality qualification.
- No public ABI, release class beyond `INTERNAL_ONLY`, engine license decision or production-readiness claim.

## Ownership

- GFX-08 owns logical VFX graph shape, emitter/spawn budgets, ribbon/trail plans, blend policy, density-stamp metadata and pool/quality budgets.
- It does not own devices, shaders, GPU resources, render passes, materials, lights, post-processing, durable assets or gameplay authority.
- Cosmetic VFX never becomes gameplay-authoritative; damage, collision and network state remain upstream.

## Consequences

- The layer is deterministic and testable on every CI platform without a GPU, shader compiler or asset codec.
- Any future particle simulation, GPU compute, sorting, OIT, volumetric rendering or visual comparison requires a new owner-approved contract/slice and platform evidence.
- ADR-0021 remains planning context; this ADR neither ratifies its GPU/Web/hardware decisions nor selects any vendor dependency.

## Evidence gates

Contract `GFX-08-02`, six implementation slices `-03`..`-08`, qualification `-09`, closeout `-10`, exact-head native CI and pt-BR audit. Stop on stale source, native GPU/compute/sort/SDK selection, released ABI or HIGH/CRITICAL.
