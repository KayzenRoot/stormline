# GFX-06 — Technology, Platform and Licensing Matrix

**Research #138 / WO NLE-P00-WO-002-GFX-06** | PROPOSED only, no libraries installed nor GPU benchmarks.

| Candidate | Class | Portability limits | Licensing boundary | Future proof |
|---|---|---|---|---|
| Own clustered/Forward+ direct lighting | Baseline candidate | portable CPU oracle, GPU compute per capability | independent design, no SDK | cluster overflow, per-light source priority |
| CSM/PCF shadow atlas | Baseline candidate | depth sampler/features and precision per backend | public algorithm; own implementation | stable cascade, alpha/deformed caster |
| PCSS/contact shadows | Optional quality | screen-space offscreen misses; GPU cost | algorithm reference only | softness vs acne, contact vs reference |
| Variance/EVSM shadow filters | Optional research | light bleeding, precision | own implementation | distinguish virtual-page shadows |
| Virtual Shadow Maps / page cache | Optional high tier | GPU pool, fence/fragmentation and invalidation; Web limited | Epic public concepts only, no copied code | page overflow and temporal artifacts |
| IBL + lightmaps/reflection probes | Baseline fallback | static/baked quality, DATA-05 verification | authored asset rights | offscreen, low-end fidelity |
| SSGI + SSR | Optional hybrid | screen-only misses, disocclusion | own algorithm | temporal ghost, mirror quality |
| DDGI/visibility probes | Optional GI | probe leaking/moving geometry cost | research licenses checked by exact repo | probe relocation & update |
| Radiance Cascades / GGG | Priority 2D & 2.5D research | 3D full-world unresolved, memory/occluders | Sannikov WIP article not code license | ARPG immediate response without temporal |
| AMD FidelityFX Brixelizer GI | Optional native GI | DX12/Vulkan compute SDK; Metal/Web not automatic | AMD SDK MIT claim; SBOM/tag required | vs probes and Radiance Cascades |
| Vulkan RT queries and AS | Optional high end | explicit KHR feature and driver | Khronos API, SDK legal check | skinned/alpha and AS lifetime |
| D3D12 DXR tier | Optional high end | Windows adapters only where feature reports | platform SDK terms | reflection and shadow cost |
| Apple Metal ray tracing | Optional high end | feature-probed Apple GPU/intersector | Apple SDK terms | native parity, no Vulkan assumption |
| WebGPU W3C | Required Web path | no standard native RT feature in published enum | W3C specification | compute/texture quotas, fallback |
| ReSTIR paper / NVIDIA RTXDI SDK | R&D papers only | RT and denoiser dependency | RTXDI LICENSE proprietary NVIDIA RTX terms, NOT MIT | license before any source usage |
| NVIDIA RTXGI v2 NRC/SHaRC | Watch only | NRC tensor, hardware/vendor/backend limits | RTX SDK proprietary terms; DDGI v1 separate | do not vendor |
| Volumetric froxel fog | Optional feature | CPU/GPU memory and temporal costs | own research | light shafts, extinction stability |
| SLRG budget policy | Optional PROVE-OR-DROP | depends on frame/quality measurements | original design hypothesis not novel claim | vs fixed budget and missing-light correctness |

## Critical distinctions
- **Virtual Shadow Maps** are *physical-page shadow caches* (Epic concept), NOT **Variance Shadow Maps** or Exponential Variance Shadow Maps (moment filters). Do not silently interchange them.
- GGG Radiance Cascades is an important comparator for screen-space/2D dynamic GI, not an automatic portable complete 3D solution or reusable proprietary code. WIP paper and videos carry their own publication terms.
- AMD FidelityFX Brixelizer/GI uses compute without hardware RT and documents D3D12/Vulkan integrations, but does not guarantee Mac/Browser support. Exact version and transitive license scan gate before use.
- NVIDIA RTXDI/RTXGI visible source code **not MIT**, governed by NVIDIA RTX SDK license with additional distribution terms. Research ideas allowed as literature; copying SDK not preapproved.
- W3C WebGPU feature registry does not define portable hardware ray tracing; WebGL2 has even stricter compute limitations. Explicit per-adapter feature probes instead of OS/marketing guesses.
- Version freeze is **future**; maintain version/commit/license/security/NOTICE/SBOM/target matrix with evidence. No vendor downloads, asset licenses, patents, proprietary engine binary extraction or shader reuse in P00.

## Primary research sources
- Epic Lumen (dynamic GI, surface cache, hardware/software RT): https://dev.epicgames.com/documentation/unreal-engine/lumen-global-illumination-and-reflections-in-unreal-engine
- Epic Virtual Shadow Maps (paged shadows; moving caster invalidation, pool pressure): https://dev.epicgames.com/documentation/en-us/unreal-engine/virtual-shadow-maps-in-unreal-engine
- GGG official *Rendering Path of Exile 2*, Alexander Sannikov (2023): https://www.youtube.com/watch?v=TrHHTQqmAaM
- Sannikov Radiance Cascades working-paper source (not a commercial license): https://github.com/Raikiri/RadianceCascadesPaper
- GGG 2026 ExileCon *The Engine of Path of Exile* (community recording index; official recording linked there when available): https://poe2page.com/poe2/guides/exilecon-2026/
- AMD FidelityFX Brixelizer/GI (D3D12 and Vulkan SDK): https://gpuopen.com/fidelityfx-brixelizer/
- AMD FidelityFX SDK terms: https://gpuopen.com/manuals/fidelityfx_sdk/getting-started/
- Vulkan RT extension/AS/ray-query documentation: https://docs.vulkan.org/guide/latest/extensions/ray_tracing.html
- DX12 hardware raytracing tier: https://learn.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_feature_data_d3d12_options5
- Metal acceleration structures: https://developer.apple.com/documentation/metal/ray-tracing-with-acceleration-structures
- W3C WebGPU published feature registry: https://www.w3.org/TR/webgpu/
- NVIDIA RTXDI actual SDK LICENSE (NOT MIT): https://github.com/NVIDIA-RTX/RTXDI/blob/main/LICENSE.txt
- NVIDIA RTXGI v2 (NRC/SHaRC distinct from DDGI v1): https://github.com/NVIDIA-RTX/RTXGI
- ReSTIR 2020 technical paper landing: https://research.nvidia.com/publication/2020-07_spatiotemporal-reservoir-resampling-real-time-ray-tracing-dynamic-direct
