# GFX-04 — Geometry, Occlusion, Instancing and LOD Technology Matrix

**WO:** NLE-P00-WO-002-GFX-04 | **Issue:** #132 | **Status:** PROPOSED DOCS ONLY.
No geometry tool, GPU renderer, shaders, codec, library or benchmark selected, installed or run.

| Technology / approach | Upstream and license evidence | Use candidate | Main risk / decision gate |
|---|---|---|---|
| **Stormline owned geometry visibility contract** | Engine source license OPEN | stable geometry identity, cull/LOD/proxy semantics and error contracts | custom complexity, GPU/CPU parity and visual correctness |
| **meshoptimizer (C/C++)** | [Official project](https://github.com/zeux/meshoptimizer), [MIT LICENSE](https://github.com/zeux/meshoptimizer/blob/master/LICENSE.md) | mesh/vertex/index optimization, simplification, meshlet generation/bounds, compression; candidate DATA-05 cooking transform | exact tag, API stability, SIMD/Web decoding/cross-platform target & fidelity; no runtime GPU visibility by itself |
| **meshoptimizer clusterlod.h** | [meshoptimizer release notes](https://github.com/zeux/meshoptimizer/releases), verify exact shipped header/license | optional cluster-hierarchy HLOD/continuous detail baseline | compare to simpler discrete LODs, cracks/silhouettes/material seams, build cost; verify current tag and release date |
| **gltfpack** | [meshoptimizer gltfpack](https://meshoptimizer.org/gltf/), MIT core with dependent codec/tool notices to audit | offline glTF optimize and target compression recipe reference | output may discard unknown/custom extensions; never ingest and rewrite imported authored source without preview |
| **EXT_meshopt_compression** | [Khronos glTF ratified vendor extension](https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Vendor/EXT_meshopt_compression/README.md) | compressed glTF bufferView format, import/export | correct version/fallback payload and memory/bounds validation; cannot equate compression to GPU stream placement |
| **EXT_mesh_gpu_instancing** | [Khronos ratified](https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Vendor/EXT_mesh_gpu_instancing/README.md) | efficient instance transforms in glTF import | custom attributes and per-instance state preserved, doesn't replace engine's runtime instancing |
| **KHR_meshopt_compression candidate** | meshoptimizer mentions **draft**, [glTF registry](https://github.com/KhronosGroup/glTF/blob/main/extensions/README.md) is authority | possible future standard payload if ratified & supported | do not claim ratified or enable export by default until extension registry confirms |
| **CPU frustum + spatial BVH/octree** | original algorithm implementation (license not intrinsic); test against deterministic reference | universal conservative fallback, modest GPUs and Web | big scene CPU cull cost, dynamic bounds refit and origin-rebase precision |
| **GPU compute/indirect + Hi-Z pyramid** | GPU API shader path needs GFX-01/02 support, [D3D12 indirect](https://learn.microsoft.com/en-us/windows/win32/direct3d12/indirect-drawing) | scalable instance/meshlet culling candidate | stale depth false-negative, occlusion reprojection, GPU barriers, visible-list overflow, format/feature limits |
| **Vulkan VK_EXT_mesh_shader** | [Khronos feature](https://docs.vulkan.org/features/latest/features/proposals/VK_EXT_mesh_shader.html) | optional mesh/task shader cull/draw path | device extension+compiler feature support, not universal macOS/WebGPU; fallback vertex/index required |
| **D3D12 Mesh Shaders** | [Microsoft reference](https://learn.microsoft.com/en-us/windows/win32/direct3d12/mesh-shaders) | optional amplification/meshlet on Windows feature devices | shader model/OS/hardware tier and platform parity, not mandatory |
| **Native Apple Metal mesh/object shader features** | [Apple Metal](https://developer.apple.com/metal/), availability differs by GPU family | optional Apple GPU-driven path on supported devices | must query/validate actual Metal feature family and shader toolchain; no universal Vulkan feature mapping |
| **WebGPU/WebGL2 runtime path** | [W3C WebGPU](https://www.w3.org/TR/webgpu/), [Khronos WebGL2](https://registry.khronos.org/webgl/specs/latest/2.0/) | browser vertex/index+instancing baseline, optional indirect and compute | WebGPU limits/availability and memory opacity; no assumed portable mesh/task shader or unrestricted indirect |
| **Unreal Nanite** | [Epic documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/nanite-virtualized-geometry-in-unreal-engine), Epic proprietary tool/engine content | conceptual comparison: hierarchical clusters, fine streaming & screen-space error | DO NOT copy proprietary code/assets or assert equivalent Stormline functionality; foliage and aggregate occlusion deficiencies documented |
| **Impostors/alpha foliage/HLOD alternatives** | original implementation from stable documented algorithms + authored assets rights | trees/grass/foliage LOD with fewer triangles and bounded bandwidth | alpha overdraw, transparency/wind animations, popping, shadow and collision mismatch |
| **SVCG visibility confidence research** | new original hypothesis, NO IMPLEMENTATION | bounded temporal conservative prefetch/LOD hysteresis | prove-or-drop against simple CPU+LOD+Hi-Z, never cull uncertainty as invisible |

## Research conclusions (not final stack selection)
1. Prefer **conservative CPU frustum + static LOD** as future baseline to prove correctness first; prioritize meshoptimizer MIT for offline geometry recipes **after license, version and CPU/ABI proof**. GPU-driven Hi-Z/meshlets are optional optimization tiers, not the only path.
2. Geometry virtualisation is a distinct costly architecture, not automatic adoption of Nanite. Fine meshlet hierarchies need error metrics, residency, cracks stitching, material/deformation and CPU/GPU telemetry. Require A/B against simpler HLOD with original assets.
3. Preserve DATA-05's immutable chunk cooking and streaming API instead of creating a new asset pipeline in GFX-04; don't conflate source AssetId, derived geometry chunk checksum and GPU address.
4. For vegetation and alpha-cutout, treat perforated/aggregate materials as poor conservative occluders unless special validated technique. The [Epic technical docs](https://dev.epicgames.com/documentation/unreal-engine/nanite-technical-details) illustrate why large triangle counts and overdraw may persist for foliage. Fallback impostors and instancing should be measured.
5. For WebGPU and Apple Metal, query feature/limits at runtime. Advanced mesh shader paths require hardware/driver/compiler and fallback matrix proof, never promise ubiquitous equivalent stages.

## Suggested scorecard (UNMEASURED)
- Visible-geometry correctness, no false negatives & rights fidelity: 30%
- Low-end/native/Web portability and degraded fallback: 20%
- p50/p95/p99 CPU-GPU/VRAM/IO on large scenes: 20%
- Build/cook/stream workflow integration and memory safety: 15%
- Pinned licensing/toolchain and maintenance: 10%
- Innovation capacity without unnecessary new subsystem: 5%
Hard veto for missing visible geometry, unsafe indirect buffer, unsupported export, unverifiable source rights and dependency license violations.

## Official sources visited 2026-11-14
https://github.com/zeux/meshoptimizer
https://meshoptimizer.org/
https://github.com/zeux/meshoptimizer/releases
https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Vendor/EXT_meshopt_compression/README.md
https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Vendor/EXT_mesh_gpu_instancing/README.md
https://github.com/KhronosGroup/glTF/blob/main/extensions/README.md
https://docs.vulkan.org/features/latest/features/proposals/VK_EXT_mesh_shader.html
https://dev.epicgames.com/documentation/en-us/unreal-engine/nanite-virtualized-geometry-in-unreal-engine

No performance gain, version lock, compiler, target SDK or successful platform feature has been demonstrated.
