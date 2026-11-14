# GFX-06 — Stormline Adaptive Lighting & Shadows

**Research:** #138 | **WO:** NLE-P00-WO-002-GFX-06 | **Future implementation:** #34 BLOCKED | **State:** PROPOSED DOCS ONLY  
**Context Lock BASE main:** `59f044b9ac34411bbdd2f0170549bb4a9c78465e`. **No GPU implementation, visuals or benchmarks exist.**

## 1. Mission: beauty, immediate response and bounded GPU cost
Stormline must aim for compelling physical and stylized lighting, stable soft shadows, realistic indirect diffuse/color bleed, reflections and fog, including demanding ARPG combat with many lights. Design for native Windows/Linux/macOS, WebGPU with explicit feature gates and reduced WebGL2. Competitive superiority vs Unreal or GGG is a future *test hypothesis*, never claimed as current fact.

## 2. Ownership (no duplicate engine services)
| Owner | Responsibilities / integration |
|---|---|
| CORE-04/05/06 | time, precision/floating origin, units and diagnostics |
| DATA-02/03/04/05 | durable LightId and provenance; light/probe source imports; authored scene schema; cooked/baked probes, streamed bundles and verified receipts |
| GFX-01 | device/backend feature snapshots and generation; Vulkan/D3D12/Metal/Web GPU support |
| GFX-02 | shader compilation/reflection/layout/variants, no new lighting shader compiler |
| GFX-03 | RenderGraph passes, barriers, GPU allocations/fences/history lifetime/VRAM pressure, no GFX-06 VRAM allocator |
| GFX-04 | visibility/LOD, bounded shadow casters, off-screen casters, morph/skeletal/alpha foliage and origin shifts |
| GFX-05 | PBR BRDF, energy conservation, normals, material alpha; GFX-06 integrates incident light, not BRDF definition |
| GFX-07/GFX-08 | exposure/tone mapping/color/upscale and VFX/particles; GFX-06 supplies linear HDR radiance and bounded emissive-light contribution |
| TWO/WORLD/EDIT/AI | 2D and hybrid layers; scene components; editor UI and versioned semantic command kernel |

CPU/headless reference validates math and typed requests, never masquerades as GPU output. Aesthetic lighting never becomes an authority for gameplay security or visibility.

## 3. Authoring/photometry contract
- `DIRECTIONAL`, `POINT`, `SPOT`, `AREA_RECT`, `ENVIRONMENT`, `STYLIZED_2D` with stable LightId, revision, world transform, finite positive/light-valid color, orientation/radius, channel/receiver mask, shadow cast policy, source size and mobility/epoch.
- Proposed explicit photometric units: directional illuminance **lux**, punctual luminous intensity **candela**, area **luminance cd/m²** where relevant. Linear working-color-space and exposure boundary must align GFX-05/GFX-07; no mysterious untyped `intensity=1000`.
- Inverse-square falloff with bounded near-source regularization and validated spot angular profile, documented nonphysical stylization override. Invalid NaN/Inf, negative power/attenuation, illegal transforms, excessive light count and zero-radius divergence return typed errors.
- Light cookies/IES and baked HDR environments are opt-in DATA-03 imports with explicit source rights, no arbitrary host/network path or executable graph.

## 4. Efficient direct illumination
- Reference CPU/forward path: directional + bounded local lights, correct PBR response with deterministic golden numerical fixtures. Modern hardware candidate **Forward+/clustered** tiles and depth slices; feature detection and actual cost decide which wins at target density.
- Cluster light lists built with checked counts/prefix-sums, explicit overflow/backpressure; no silently disappearing relevant lights. Consider pass splitting, adaptive light influence/resolution and published `LightingQualityReceipt` for approximations.
- Many small ARPG spell lights should preserve immediate create/destroy response and readable action. Dynamic budget scheduler is optional; never let performance heuristics remove vital authored light without a documented authoring policy.
- Batching does not reinterpret GFX-05 material features, light channels, GFX-04 occluders or change world IDs.

## 5. Shadows: four progressive strategies
**S0 portable correctness reference:** stable cascade shadow maps (CSM) + local spot/point shadow atlas/cubemap + PCF; explicit shadow bias/receiver-plane bias, texel-snap, cascade split blend/hysteresis, reversed-Z and near/far depth conventions. Compare silhouette against reference, avoid acne, peter-panning, seam popping. Alpha cutout and animated foliage remain correctly classified.

**S1 bounded softness:** PCSS/penumbra, contact shadow as *supplement* (screen-space misses offscreen), normal/geometry dependent filter and local shadows. Variance/EVSM filtering is **different** from Virtual Shadow Maps, and light leaking must be measured. Preserve correct coarse baseline when unsupported.

**S2 optional Virtual Shadow Maps:** a page/clipmap-based shadow system, NOT "variance shadow map". Determine page need from projected demand and GFX-04 caster info; GFX-03 owns physical pool/VRAM/fence/read-write. On moving lights, morph/skinning/WPO, alpha, foliage, LOD or streamed chunk change, camera cut/teleport, origin rebase, depth format/shader revision or page churn, invalidate affected entries and rebuild. Unknown/incomplete page -> valid coarse shadow, explicit quality loss or typed error, **never page corruption or stale shadows**. Cache static and dynamic layers only after measurable advantage.

**S3 optional hardware ray shadows:** Vulkan KHR ray_query/AS, D3D12 DXR support, Metal AS/intersection capability only when verified per GPU; GFX-04 supplies accurate acceleration geometry. Alpha and skinned objects require proven support or explicit fallback; no WebGPU/WebGL2 standard RT assumption. Ray budget, denoise stability and cost must be measured.

## 6. Global illumination, reflections, probes
- **Baseline:** IBL/environment and verified authored probes/lightmaps (DATA-05 baked only for compatible scene generation), no fictional fully dynamic bounced-light fidelity. Explicit response/error for missing/stale bake. Lightmaps can work on modest hardware.
- **Dynamic GI candidate paths:** screen-space SSGI plus offscreen probes, DDGI/visibility-aware irradiance probes, moving/repositioned probes to reduce light leaks, SDF/voxel sparse distance caches; AMD FidelityFX Brixelizer GI is promising for DX12/Vulkan compute without HW RT but not automatically Metal/Web compatible. Static-only geometry representations cannot blindly receive rapidly changing skinned occluders.
- **Radiance Cascades:** priority R&D due GGG. Analyze 2D/screen-space method for 2D and 2.5D, penumbra hypothesis and cascade spatial/angular resolution tradeoff, immediate dynamic-light response without reliance on temporal history. For **3D full-world**, describe as EXPERIMENTAL; no extrapolation of cost/quality from 2D, test offscreen occluders, depth discontinuity, memory, resolution, animated emitters and camera perspective. Study literature/public talk; no proprietary PoE2 shaders/art/code copied.
- **High-end:** optional hybrid RT GI/RTX reflections under confirmed capability; stochastic ReSTIR reservoir ideas considered as papers. NVIDIA RTXDI/RTXGI SDK **not MIT**, do not vendor or assume commercially redistributable absent legal review. RTXGI v2 NRC/SHaRC is not identical to old RTXGI DDGI.
- **Reflections:** environment/probes as robust base, optional SSR where geometry visible, explicit offscreen/probe fallback, optional ray-traced mirror/glossy when hardware and materials permit. GFX-05 transmission/alpha and GFX-07 HDR tone mapping remain separate; do not promise perfect refractive multilayer SSR.
- **Validity:** direct/indirect diffuse/indirect specular separate receipts; avoid treating scene-screen-only features as physically correct offscreen global coverage.

## 7. Volumetrics, atmosphere, 2D/2.5D
- Nonnegative absorption/scattering, bounded fog density and phase approximation, froxel/low-res volumetric integrator optional; simpler analytic fog WebGL2 fallback. Shadowed fog and participating lights require independent VRAM/compute/temporal budgets.
- GFX-08 owns particles; GFX-06 consumes capped emissive-light requests, cannot spawn unbounded area lights from every spark.
- 2D baseline: lit sprites, normal maps and polygon/cell occlusion, parallax layering and fixed-cost fallback. 2D Radiance Cascades candidate; 2.5D projected lighting only when layer depth/shadow interaction is explicitly authored. This is a real workflow, not an accidental special case of 3D.

## 8. History, frame and scene invalidation
Versioned `LightingHistoryKeyV1`: project/scene, camera/projection/resolution, viewport render scale, frame/origin epoch, lights/casters/material revisions, shader layout, technique/quality, GFX-01 device generation and GFX-03 completion/ownership. Camera cuts, FOV change, teleports, new emissive spell, destroyed lamp, skinned object change, viewport resize, device loss and hot reload invalidate incompatible history. Reject stale GPU handle; preserve fallback rather than ghosted/incorrect lighting. Temporal denoiser with explicit confidence, reactive mask and bounded disocclusion recovery; no invented “zero artifacts” guarantee.

## 9. Platform quality tiers and budgets
| Tier | Correct baseline | Conditional premium |
|---|---|---|
| headless CPU | units, shadow projection, analytic light reference, provenance and budgets | no GPU comparison |
| WebGL2 | small bounded lights, CSM/local PCF where available, IBL/probes, analytic fog | no required compute, RT or paged shadows |
| WebGPU | per-adapter feature/limits; compute clustered option, shadow/probes/SSR if proven | no native WebGPU RT assumed |
| Win Vulkan/DX12, Linux Vulkan | direct + stable CSM, probes/IBL | validated RT queries, virtual pages, Brixelizer GI native |
| macOS Apple Silicon Metal | Metal-native depth/compute/IBL/probe/CSM fallback | feature-probed Metal intersection/RT, no Vulkan parity claims |

`LightingQualityBudget`: GPU/CPU target (explicit unknown/estimated sources), VRAM/UMA headroom, ray samples/probes, local light count, shadow pages/atlas, fog steps/history, cache update pressure. Lower resolution/features only through defined visible quality receipt; no fake numbers on browser. Dynamic strategy candidates require objective quality and p50/p95/p99 measurement on named devices.

## 10. Stormline Lighting Response Governor (SLRG) — research only
Hypothesis: a budget arbiter can allocate work between light clustering, shadow invalidations, GI/probe updates and fog using view significance, motion and confidence without increasing unacceptable flicker or latency. Baselines: plain cluster+CSM+probes; fixed budget; Radiance Cascades 2D; hybrid compute option. Test adversarial dynamic scene, not just curated stills. PROVE-OR-DROP when performance, stability, costs or portability lose. Do **not** call invention or outperformance proven.

## 11. Secure authoring
Editor/CLI/MCP call one command kernel with `InspectLighting`, `PreviewLightBudget`, `PreviewShadowPlan`, `GetLightingReceipt`; scoped, revision-checked `Stage/Validate/CommitLightEdit` under explicit capability and durable DATA-04 scene journal. No direct GPU pointers, shader injection, file system scans, network fetch, unbounded bakes or proprietary content leak. Preview is not visual GPU benchmark.

## Required gates before code
Owner-approved release classes/DoD, exact API and C++ paths, GFX-03 + GFX-05 dependency code integrated, shader layout and authored light identity, supported platform/OS/compiler, GPU fixtures/licenses, p95/p99 and visual tolerances, risk evidence, fresh SHA-256 Context Lock. All currently **MISSING**. Future #34 remains BLOCKED. Refer to the test matrix and benchmark protocol.

## Primary research sources
- Epic Lumen (dynamic GI, surface cache, hardware/software RT): https://dev.epicgames.com/documentation/unreal-engine/lumen-global-illumination-and-reflections-in-unreal-engine
- Epic Virtual Shadow Maps (paged shadows; moving caster invalidation, pool pressure): https://dev.epicgames.com/documentation/en-us/unreal-engine/virtual-shadow-maps-in-unreal-engine
- GGG official *Rendering Path of Exile 2*, Alexander Sannikov (2023): https://www.youtube.com/watch?v=TrHHTQqmAaM
- Sannikov Radiance Cascades working-paper source (not a commercial license): https://github.com/Raikiri/RadianceCascadesPaper
- GGG 2026 ExileCon *The Engine of Path of Exile* (official live recording): https://www.youtube.com/live/8CEAhCzm
- AMD FidelityFX Brixelizer/GI (D3D12 and Vulkan SDK): https://gpuopen.com/fidelityfx-brixelizer/
- AMD FidelityFX SDK terms: https://gpuopen.com/manuals/fidelityfx_sdk/getting-started/
- Vulkan RT extension/AS/ray-query documentation: https://docs.vulkan.org/guide/latest/extensions/ray_tracing.html
- DX12 hardware raytracing tier: https://learn.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_feature_data_d3d12_options5
- Metal acceleration structures: https://developer.apple.com/documentation/metal/ray-tracing-with-acceleration-structures
- W3C WebGPU published feature registry: https://www.w3.org/TR/webgpu/
- NVIDIA RTXDI actual SDK LICENSE (NOT MIT): https://github.com/NVIDIA-RTX/RTXDI/blob/main/LICENSE.txt
- NVIDIA RTXGI v2 (NRC/SHaRC distinct from DDGI v1): https://github.com/NVIDIA-RTX/RTXGI
- ReSTIR 2020 technical paper landing: https://research.nvidia.com/publication/2020-07_spatiotemporal-reservoir-resampling-real-time-ray-tracing-dynamic-direct
