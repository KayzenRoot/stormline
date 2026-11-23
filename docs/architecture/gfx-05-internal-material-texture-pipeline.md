# GFX-05 internal logical material and texture pipeline

**Status:** `GOVERNANCE-SCOPED / NOT IMPLEMENTED / NO NATIVE GPU`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Parent research:** [gfx-05-materials-textures-pbr](gfx-05-materials-textures-pbr.md), planning only.

## Purpose

Define the first executable GFX-05 slice without selecting a texture codec, image decoder or GPU renderer. The pipeline validates material parameters, texture/mip metadata, virtual page requests, sampler profiles, decal ordering and transparency budgets.

## Hard boundaries

- No Vulkan/D3D12/Metal/WebGPU, KTX2/Basis, image decoder, shader compiler or GPU allocator.
- No image bytes, decode/encode, GPU upload, BRDF evaluation, pixel output or rendering.
- No command buffer, submission, timing or hardware measurement.
- No public ABI, release, performance or security certification.

## Logical model

- **PBR material:** bounded base color/metallic/roughness/occlusion/emissive/normal/alpha parameters with finite range checks.
- **Texture metadata:** dimensions, levels, format, color space and usage; no pixels.
- **Mips:** expected level count and logical sizes derived from dimensions, bounded and checked.
- **Virtual texture:** page grid, resident pages and deterministic request planning under a page budget; no hardware sparse residency.
- **Sampler:** filter/address/LOD/anisotropy/compare profile validated against logical limits.
- **Decals:** bounded layer/priority/opacity descriptors and deterministic ordering.
- **Transparency:** alpha/blend states, deterministic back-to-front sort and overdraw count budget.

## Determinism

- Tables preserve declaration order unless an explicit stable sort key is defined.
- Page/decal/transparent outputs sort by stable integer keys, with IDs as tie-breaks.
- Float validation rejects NaN/Inf; no unordered iteration determines output.

## Failure model

Typed errors cover duplicate/unknown IDs, capacity, non-finite/out-of-range parameters, invalid mip/format/sampler, page/decal/transparency budget and stale generation. Unknown or unsupported input fails closed.
