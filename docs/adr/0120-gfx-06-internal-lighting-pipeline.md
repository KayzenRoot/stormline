# ADR-0120 — Bounded internal lighting, shadow, GI, probe, reflection and volumetric planning

**Status:** `APPROVED FOR INTERNAL LOGICAL PIPELINE ONLY` — owner-authorized continuation, 2026-11-23. **Supersedes for internal implementation:** none. **Keeps:** [ADR-0019](0019-gfx-06-adaptive-lighting-policy.md) as planning-only context.

## Context

GFX-03 and GFX-05 completed internal sequences as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. GFX-06 research, ADR-0019, architecture and API semantics exist, but no native GPU, shadow map, ray tracing, GI, probe bake, reflection or volumetric implementation is authorized. The repository needs a bounded, testable logical layer before any backend work.

## Decision

Ratify a first GFX-06 internal pipeline that validates and plans lighting metadata only:

1. **Light definitions and validation.** Stable IDs, revisions, declared types (directional, point, spot, area rectangle, environment, stylized 2D), finite color/intensity/orientation/radius/range, nonnegative attenuation, bounded counts and typed errors.
2. **Shadow planning.** Logical cascade splits, local shadow request metadata, atlas/page occupancy proposals, bias/filter profiles, generation/invalidation epochs and coarse fallback flags. No shadow map is created, sampled or rendered.
3. **GI planning.** Explicit baked/IBL/probe modes and fallback; missing or stale bake fails closed or degrades to a declared lower mode. Dynamic GI and ray tracing remain out of scope.
4. **Probe volumes.** Bounded logical probe definitions, cell placement, validity/provenance and leak-risk metadata. No bake, relocation, GPU upload or sampling.
5. **Reflection planning.** Probe/environment base plus optional SSR metadata and an explicit offscreen fallback reason. No SSR pass, ray query or material shader is executed.
6. **Volumetric planning.** Finite nonnegative density/extinction/scattering/phase metadata, analytic/froxel tier selection and bounded per-frame budgets. No froxel buffer, shadowed fog or particle system exists.

## Non-decisions

- No Vulkan/D3D12/Metal/WebGPU selection, GPU allocator, command buffer, descriptor, fence or swapchain.
- No shader compiler, shader bytecode, pipeline state, binding layout or GPU resource.
- No real CSM, virtual shadow map, PCF/PCSS, ray-traced shadow, DDGI, SSGI, probe bake, SSR, volumetric froxel or renderer.
- No visual golden, driver matrix, hardware tier, p50/p95/p99, performance, power, thermal or production claim.
- No public ABI, wire schema, release class beyond `INTERNAL_ONLY`, or engine license decision.

## Ownership

- GFX-03 owns render-graph passes, barriers, resources and fences.
- GFX-04 owns casters, visibility, LOD and stream revisions.
- GFX-05 owns BRDF/material alpha and texture semantics.
- GFX-07 owns exposure, tone mapping, color output and upscaling.
- DATA-02/04/05 own durable IDs, authored scene data, cooked bakes and streaming receipts.
- GFX-06 owns only the logical lighting plan and its typed failure/fallback metadata.

## Consequences

- The internal layer can be tested deterministically on every CI platform without a GPU.
- Later backend work still requires a new owner-approved contract and slice; this ADR is not a hardware or visual qualification.
- Any future shadow map, GI, probe bake, reflection or volumetric implementation must preserve these logical boundaries and document invalidation/fallback.

## Evidence gates

Contract `GFX-06-02`, six implementation slices, qualification `-09`, closeout `-10`, exact-head native CI, pt-BR audit. Stop on stale source, native GPU/codec/ray-tracing selection, released ABI or HIGH/CRITICAL.
