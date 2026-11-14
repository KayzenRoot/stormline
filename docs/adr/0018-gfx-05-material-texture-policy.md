# ADR-0018 — GFX-05 Physically Based Materials and Portable Texture Quality

**Status:** PROPOSED / NOT APPROVED FOR ENGINE CODE  
**Date:** 2026-11-14 | **WO:** NLE-P00-WO-002-GFX-05 | **Research:** #135 | **Future implementation:** #33 BLOCKED

## Problem
Advanced shading and high-density textures must produce consistent visual authoring across desktop and Web without shader explosion, driver-unsafe codecs, overdraw spikes, texture residency stalls, false color-space conversions or platform feature assumptions. Treating material graph, asset import, shader compiler and VRAM manager as one subsystem would duplicate earlier modules and make rollback and GPU device-loss unsafe.

## Proposed policy, not implementation approval
1. **Semantic ownership:** GFX-05 defines PBR/material model/alpha/decal/mip usage and typed quality policy. Existing GFX-02 `MaterialDefinitionV1` and `MaterialInstanceV1` remain canonical compiler-facing types, extended by versioned GFX-05 semantic structs, not recreated. DATA-02 permanent IDs, DATA-03 source validation, DATA-05 cook/stream, GFX-01 capability/handles, GFX-03 allocations/fences and GFX-06 lighting remain authorities.
2. **PBR baseline:** glTF metallic-roughness with correct linear light, energy-aware GGX/Smith/Fresnel math and explicit sRGB treatment. Portable glTF extensions gated per feature. Stylized, unlit and 2D material domains are first-class, not fake metallic-roughness.
3. **Texture distribution:** KTX2/Basis Universal ETC1S/UASTC is **preferred research candidate**, not mandatory installed dependency. Validate target format via GFX-01 capability and DATA-05 target cook receipts; choose supported BCn/ASTC/ETC2 or bounded RGBA fallback. Original source, profile, alpha/data semantics and material rights preserved.
4. **Legal gate:** KTX-Software has mixed licenses and optional non-open-source ETC decoder (`etcdec`); require per-file SPDX/REUSE and exclude `LIBKTX_FEATURE_ETC_UNPACK` or obtain explicitly approved legal distribution path. Basis Universal/MaterialX Apache-2.0 NOTICE and transitives checked; exact pinned tags before code.
5. **Explicit alpha:** OPAQUE, MASK, BLEND and optical transmission are distinct; sorting/transmittance/normal blend/decal priority must have reference test and overdraw budget. Alpha foliage is **not** trusted solid occluder (GFX-04). OIT and layered advanced effects are optional with quality-loss receipts.
6. **Bounded residency:** material requests preferred mip/fidelity; actual DATA-05 retrieval and GFX-03 uploads/fences own state. Device generation and last-good fallback mandatory; non-resident texture and malformed mips yield typed errors or intentional coarse fallback, not stale handle access.
7. **Platform tiers:** Windows Vulkan/D3D12, Linux Vulkan, macOS Metal, WebGPU and reduced WebGL2 get semantically equivalent supported profile, not promised pixel identity. No universal native sparse residency, BCn/ASTC/ETC2 or Metal/WGSL shader generation claim.
8. **Material graph interoperability:** MaterialX 1.39.x optional for import/export; GFX-02 owns actual compilation/variants, EDIT-05 UI. Limit static switches and bounded graph cycles/nodes. Typed safe Editor/CLI/MCP inspection and staged revision-checked edits only.
9. **Golden quality and provenance:** named rights-cleared fixtures + render reference, linear/high-dynamic-range correctness, normal/tangent behavior, mip stability, alpha coverage, overdraw, device-loss and streaming faults; measured p50/p95/p99/peak memory on specified machines. CI docs never certifies real renderer.
10. **STAM innovation** (adaptive texture demand across priorities) remains optional PROVE-OR-DROP. It cannot starve guaranteed mip, bypass a fence, hide content or claim ML superiority; measure against straightforward bounded ordinary mip streaming.
11. **No code authorization:** future #33 depends on implemented/accepted GFX-02 and DATA-03, Scope/DoD release decision, exact tags/licenses, source paths, shader ABI, target capabilities, budgets, fixtures, golden thresholds, security evidence, Context Lock SHA-256 and explicit activation. 80 coding WOs stay BLOCKED with `executor_ready=false`.

## Alternatives evaluated
- **Make MaterialX the mandatory runtime:** premature third-party coupling; its existence is not proof of renderer-native/Web output parity.
- **Use only ordinary uncompressed textures:** useful conservative fallback, too expensive at large resolutions; needs budget checks.
- **Assume hardware sparse/virtual texturing universally:** violates Metal/Web/low-end portability; reject as requirement.
- **Always choose maximum compressed codec:** quality, licensing and format support differ per GPU; reject.
- **Approximate all transparency with alpha blending:** not equivalent to physical transmission or multilayer refraction; reject.
- **Unlimited material static switches or arbitrary graph code:** variant explosion and untrusted execution; reject.
- **Separate GFX-05 own compiler/VRAM/asset database:** violates GFX-02/03/DATA-02/03/05 boundaries; reject.

## Required future evidence
Exact versions/rights/SBOM, golden fidelity baselines, sanitizer/fuzz malformed textures/graph, Windows/Linux/macOS real GPU plus WebGPU/WebGL2 browsers, alpha/decals/refractive ordering, shader reflection/pipeline tests, mip/normal/color numerical correctness, GPU device-loss, deterministic cook, bounded memory and low-end performance.

See [architecture](../architecture/gfx-05-materials-textures-pbr.md), [matrix](../research/gfx-05-material-technology-matrix.md), [semantic API](../contracts/gfx-05-material-texture-api.md) and [future tests](../testing/gfx-05-acceptance-matrix.md).
