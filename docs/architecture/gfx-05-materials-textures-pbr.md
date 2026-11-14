# GFX-05 — Material Semantics, Portable PBR and Bounded Texture Residency

**Research WO:** NLE-P00-WO-002-GFX-05 | **Research:** #135 | **Future implementation:** #33 BLOCKED  
**State:** RESEARCH PROPOSED, DOCS ONLY | **Context Lock base:** `ace3355583dd1f83d2d483081184d665fa2229fa`  
**Risk:** LOW research; future ELEVATED (untrusted image/texture data, native GPU resources, renderer fidelity and device-loss recovery).

## Mission and hard ownership
Provide physically based **and stylized** material appearance on 2D/2.5D/3D native/Web, with reproducible authored semantics, perceptually reasonable quality tiers and explicitly bounded texture residency. GFX-05 defines shading/math, material parameters, texture semantic usage, alpha/decal behavior and fallback decisions. It is not a shader compiler, an asset importer, a GPU allocator or a whole lighting engine.

- **DATA-01/02:** scoped VFS, permanent MaterialAssetId / TextureAssetId, revision/provenance/rights and dependency links; digests and GPU descriptors never replace permanent IDs.
- **DATA-03:** validate source image/texture/color profiles and glTF material import, reimport receipts, per-subasset stability and user override conflicts. GFX-05 never parses untrusted files directly through privileged host paths.
- **DATA-04:** authored serializable material/scene references and version migrations. **DATA-05:** per-target immutable cooked texture, mip/codec manifests, integrity, fetching, patch/rollback and scheduling of source chunks.
- **GFX-01:** native RHI capability snapshots, formats, sampler limits, device generation and physical texture handles. **GFX-02:** shader language, reflection, variants/layout and compiled artifacts; GFX-05 provides semantic MaterialFeatureSet/parameters, not its own compiler, cache or runtime shader evaluator.
- **GFX-03:** actual GPU upload, barriers, fences, VRAM residency and transient resources. GFX-05 proposes texture sampling quality and residency requests/receipts; never allocates VRAM independently.
- **GFX-04:** visibility/LOD, uv/tangent/material section compatibility; alpha-tested foliage cannot become a solid depth occluder merely because it has a texture. **GFX-06:** direct/indirect lighting, shadows/reflections/probes, **GFX-07:** exposure and tone mapping. GFX-05 BRDF model cannot fabricate light sources or auto-approve HDR output.
- **TWO-01/04:** sprite/unlit/lit style and layered hybrid semantics; **EDIT-05:** node editor UI; **PLAT-03:** Web runtime/fallback. **CORE-02/03/06:** quotas, scheduling, diagnostics, privacy. Headless server tests use CPU evaluation and metadata, not imagined GPU output.

## Core material representation
Use immutable `MaterialDefinitionV1` (extends GFX-02 shared compiler-facing contract, not a duplicate) and `MaterialInstanceV1` with dynamic overrides. Parameter edit is runtime uniform/data update; only a change of explicitly static feature shape triggers GFX-02 variant planning. Permanent references use DATA-02 IDs and expected revisions; preserve last-good runtime generation during failed reload.

- **Physical core:** glTF 2.0 metallic-roughness model; linear-light microfacet BRDF, GGX/Trowbridge-Reitz NDF, Smith masking-shadowing, Fresnel Schlick approximation where validated, energy conservation under layered lobes. Authoring baseColor/emissive in sRGB semantics and scalar metallic/roughness/occlusion/normal data in **linear** semantics; convert exactly once at texture sampling/input, not double-decode.
- **Surface inputs:** baseColor, metallic/roughness, normals/tangents (validated handedness and green-channel conventions), emissive, occlusion, opacity and material flags; explicit defaults and out-of-range finite validation. No silently clamped NaN/Inf; non-unit normals handled with tested normalization/fallback.
- **Portable extensions:** evaluate glTF KHR_materials_clearcoat, sheen, ior, specular, transmission, volume, iridescence, anisotropy, emissive_strength and variants. Each has own versioned feature and target capability gate. Required unsupported extension => typed rejection or importer-approved explicit lossy alternative, never silent physical equivalence. Extension statuses must be verified at exact source revision before implementation.
- **Stylized/2D:** unlit/sprite, vertex color, cutout, toon ramp and controlled layered shading as **separate** explicit models. Physically plausible is not mandatory for authored stylization.
- **Custom material graphs:** semantic graph nodes are versioned/deterministic; GFX-02 owns actual compilation, EDIT-05 visual authoring. No executable arbitrary code, scripts or raw backend shader flags from graph/MCP. MaterialX is optional import/export interoperability, never mandatory runtime nor guarantee of equal native/Web look.

## Textures: source, cooking, target and sampling
1. Import verified source and metadata through DATA-03. Retain color profile, alpha mode, orientation, swizzle, normal tangent convention, dimensions/depth/layers, provenance and rights. Reject ambiguous ICC/colorspace requiring decisions; no RGB gamma applied to alpha, roughness or normals.
2. Use DATA-05 target-specific immutable cook recipe. **Preferred distribution candidate:** KTX2 + Basis Universal ETC1S (distribution ratio) or UASTC (quality) with explicit per-target transcoding; compare BCn (desktop where supported), ASTC (commonly Apple/mobile where supported), ETC2 (many Web/mobile targets), and uncompressed fallback. Choose based on actual GFX-01 adapter/browser format support, feature flags, alpha/HDR requirements and measured quality/cost, not OS names.
3. Always validate KTX2 header/DFD/level index, decompression size, image count, dimensions, mip offsets, alignment, slice pitch and format compatibility before allocation. Bound total bytes, CPU/GPU memory, time, decoder recursion and work queue. Malformed streams never reach native driver unchecked; sandbox third-party converters/importers.
4. Standard mips for 2D/color and environment textures with color-correct filtering and normal-vector renormalization; alpha cutout coverage preservation across mips; tangent-space normal filtering avoids specular aliasing using validated roughness compensation as an optional tuned path.
5. Sampler is explicit: clamp/wrap/mirror, min/mag/mip filtering, LOD bias/range, anisotropy requested vs clamped supported max, comparison modes only where semantically legal. Non-mipmap/minification failures and edge seams require golden tests; avoid infinite anisotropy or unsupported format filtering.
6. Texture residency keys include target cooked artifact, material-revision, RHI device generation, format and mip range. GFX-05 requests desired mip state via DATA-05 and GFX-03; **confirmed completion fences** gate activation. Last-good coarse mip or typed missing-texture policy is retained; do not expose freed GPU handles after device loss.
7. Optional sparse/virtual textures only under proven budgets and platform features. A **software-managed page/atlas** fallback may be compared against standard mips; hardware sparse residency is never assumed on Metal/WebGPU/WebGL2. Avoid page table update races, feedback overflows, thrashing, mip seams and feedback based on stale camera/device generation.

## Alpha, decals and overdraw
- Distinguish **OPAQUE**, **MASK/cutout**, **BLEND/coverage compositing** and **transmission/refraction**. Alpha alone is not equivalent to optical transmission. Import glTF alpha modes with explicitly documented cutoff and semantics. Correct depth writes and ordering, blend premultiplication, alpha-to-coverage capability constraints, MSAA compatibility and GFX-04 foliage occlusion classification.
- Transparent path: correct conservative reference via depth-aware sorted draws; weighted blended OIT is an optional approximation tested against reference (order/energy and alpha color) with explicit quality flag. No guarantee of perfect order-independent transparency for multilayer refraction.
- Decals: versioned projection/surface compatibility, priority/overlap, normal blending, mip and depth interactions. Choose mesh/projected versus deferred DBuffer-like path by actual backend; disallow unbounded decal stacks and G-buffer changes without GFX-03/GFX-06 integration contracts.
- Complexity classification: baseline opaque/mask plus measured overdraw; advanced layered coatings, transmission, parallax, decals and virtual texturing are gated by cost + release class. No invented numeric FPS, VRAM or quality threshold.

## Cross-target capability strategy
| Tier | Example fallback contract | Unproven advanced capabilities |
|---|---|---|
| CPU/headless | inspect/evaluate finite parameters, validate texture manifests, deterministic golden metadata | no GPU image proof |
| WebGL2 reduced | metallic-roughness/unlit, ordinary mip/sampler, ordered alpha blend and fallback texture formats supported by browser | no guaranteed compute/sparse/OIT |
| WebGPU browser | validated WGSL feature/layout/resource limits, portable mips, samplers, bounded texture uploads | no universal sparse hardware/format entitlement |
| Windows Vulkan/D3D12; Linux Vulkan | same semantic core with actual supported BCn/ASTC/ETC2 targets per adapter | no guaranteed compression, bindless or hardware sparse |
| macOS Apple Silicon Metal | target Metal formats/samplers and validated shader generated/maintained path | no assumed DX/Vulkan extension parity |

Feature detection is per adapter/device generation, not by marketing GPU family. WebGL2 is degraded feature tier, not pixel-identical proof of desktop path. Exact minimum GPUs, OS/browser/driver versions, shader model, residency budgets and artifact formats remain OPEN until approved target matrix and real benchmarks.

## Safe AI-native Editor/CLI/MCP operations
Read-only: `InspectMaterial`, `InspectTextureProfile`, `PreviewMaterialVariant`, `PreviewTextureCook`, `PreviewMaterialCost`, `GetMaterialValidation`, bounded redacted `GetResidencyReceipt`. Explicitly capability-gated authored mutations: `StageMaterialEdit`, `ValidateMaterialEdit`, `CommitMaterialEdit` with expected DATA-02 revision, human-owner policy, audit, quotas and rollback. Reject raw shader/driver/native handles, arbitrary URI, process execution, unscoped filesystem or auto-publish third-party assets. Preview is not GPU test.

## Original R&D: STAM (Stormline Texture Adaptation Model)
Optional **prove-or-drop**, not an invented performance breakthrough: use measured screen-space projected texel demand, task priorities and texture-dependency graph to propose mip-selection residency plan against fixed-mip/standard streaming baseline. Must never starve last-good mip, exceed budgets or bypass GPU fences; cannot silently change visual fidelity/artist intent. Require actual p50/p95/p99 frametimes, peak VRAM, upload bandwidth, LOD shimmer/seams, perceptual quality on named devices, reproducible datasets. Drop if no safe net advantage; do not make AI/ML or cloud a dependency.

## Implementation gates (not achieved)
- Pin exact dependency revisions/tags with SBOM, per-file licensing, known vulnerabilities; **KTX-Software includes optional non-open-source ETC decoder** and must be disabled/excluded via audited configuration or separately approved distribution terms. MaterialX Apache-2.0 and Basis Universal Apache-2.0 core do not exempt their transitive files from inspection.
- Approve precise canonical material schema, asset migrations, costs/thresholds, OS/GPU/browser fixture matrix, selected target codecs, required/proposed features, release scope and context fingerprints. Validate real color science/PBR against reference renderer, golden assets with explicit content licenses.
- Complete GFX-02 and DATA-03 implemented/approved dependencies before activating #33. Future code/tests, GPU screenshots, native builds, fuzzing, profiling and runtime deployments remain **NOT DONE**.

## Primary references (candidate specifications, not dependencies installed)
- Khronos glTF 2.0: https://www.khronos.org/gltf/ and https://www.khronos.org/gltf/pbr
- Khronos KHR_texture_basisu: https://github.com/KhronosGroup/glTF/tree/main/extensions/2.0/Khronos/KHR_texture_basisu
- Khronos KTX developer guide: https://github.com/KhronosGroup/3D-Formats-Guidelines/blob/main/KTXDeveloperGuide.md
- Khronos KTX software licensing: https://github.com/KhronosGroup/KTX-Software/blob/main/LICENSE.md
- Binomial Basis Universal: https://github.com/BinomialLLC/basis_universal
- ASWF MaterialX https://materialx.org/ and https://github.com/AcademySoftwareFoundation/MaterialX
- Khronos render-fidelity reference: https://github.khronos.org/glTF-Render-Fidelity/
