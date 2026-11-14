# GFX-04 — Geometry, Conservative Visibility, Instancing and Hierarchical LOD

**Research WO:** NLE-P00-WO-002-GFX-04 | **Issue:** #132 | **Future code:** #32 BLOCKED  
**Status:** RESEARCH PROPOSED / NO ENGINE | **BASE main:** 563f5dff168a688f5d03d959685024dd374de4c9  
**Risk:** LOW current docs; future ELEVATED for missing geometry, unsafe GPU indirect commands, scene integrity, streaming and driver faults.

## Objective
Design an original, reusable **visibility and geometry-detail system** for Stormline 2D/2.5D/3D and native/Web platforms. Support huge scenes as a **measured research goal**, not a promised unlimited triangle count or Nanite reproduction. Preserve geometry/mesh source and authored object identity while transforming it into safe, feature-tier-specific renderable representations with predictable quality, non-visible-object rejection, streaming, instancing and graceful fallback for lower-end GPUs.

## Correct architectural ownership and dependencies
- **GFX-03** owns frame Render Graph ordering, CPU/GPU synchronization, transient heap residency plan, barriers and GPU-safe retirement. GFX-04 contributes culling, depth-pyramid, indirect-draw and geometry pass declarations plus persistent mesh usage/lifetime hints. **GFX-04 does not implement a second render graph or GPU allocator.**
- **DATA-05** owns reproducible immutable target cooking, versioned bundles, verified chunk-level streaming and last-good patch recovery. GFX-04 defines mesh/cluster/HLOD cook recipes and prioritizes streamed geometry by camera/visibility, then consumes verified chunk receipts; **no private packfile/CDN or patch system**.
- **DATA-02** owns stable AssetIds/revisions, **DATA-03** owns import/source rights, and **DATA-04** owns scene references. Visibility/LOD decisions never rewrite authored identity/geometry; generated cluster keys are derived immutable content references, not replacement AssetIds.
- **GFX-01** owns feature query, device/driver generation, vertex/index/indirect buffers and texture capability; mesh/task shaders are **optional capabilities**, not a cross-platform contract requirement. **GFX-02** supplies validated shader/material reflection and resource bindings.
- **CORE-05** owns world-space units, handedness, transforms and precision. Camera transforms and bounds must use its conventions with origin rebasing/floating origin and per-backend clip NDC conversion. **CORE-03** owns bounded CPU visibility jobs; **CORE-02** manages CPU scratch budgets.
- **GFX-05** owns material/illumination/PBR, TWO owns 2D sprites and 2.5D composition, future world/foliage modules own vegetation placement and physical simulation. GFX-04 handles mesh instancing and conservative visibility for these clients, not complete terrain, animation, vegetation physics or material shading.
- **PLAT-03** owns Web browser support/availability and disabled feature tiers; offscreen GPU vs CPU-only headless diagnostics must remain clearly distinguished.

## Proposed hybrid visibility pipeline
```text
DATA-02 MeshAssetId and DATA-03 import/source rights
 -> DATA-05 target CookRecipe (meshoptimizer simplification, meshlets, quantization candidates)
 -> immutable MeshLODManifest / spatial cluster hierarchy / geometry chunks
 -> camera + GFX-01 capabilities + GFX-03 graph epoch + budgets
 -> CPU coarse frustum/distance bounds and scene hierarchy
 -> optional GPU depth hierarchy / conservative occlusion with safe previous depth
 -> choose LOD/HLOD (screen-space error + hysteresis + residency + quality contract)
 -> batch compatible instance groups; optional GPU indirect/meshlet path
 -> request missing geometry chunks via DATA-05 (bounded IO/CPU/VRAM)
 -> choose verified resident LOD or last-good coarse proxy, no invisible hole
 -> emit typed GFX-03 cull/depth/transfer/draw pass declarations and usage/fences
 -> actual GPU rendering and safe retirement/reuse by GFX-01/GFX-03
```

### Levels of GPU capability and honest fallback
1. **Base tier:** CPU frustum/distance culling, coarse BVH/spatial index, classical vertex+index draws and instancing where supported; static LODs, correct solid geometry and guaranteed coarse fallback; WebGL2/low-end and Metal supported by actual measured feature query. Conservative visibility with **no occlusion if uncertain**.
2. **Compute tier:** optional compute-based instance/meshlet visibility and indirect command generation; Hi-Z depth-pyramid for conservative occlusion, bounded draw/dispatch counts, synchronization and zero-initialized counters via GFX-03; no generic claim all GPU formats/capabilities allow this.
3. **Advanced tier:** optional Vulkan VK_EXT_mesh_shader task/mesh path, D3D12 Mesh Shaders and native equivalents **only if explicitly supported by device and compiler targets**. Apple Metal and browser WebGPU do not inherit Vulkan shader API stages by default. Vertex/index/indirect fallback remains part of conformance.
4. **Virtual geometry R&D:** hierarchical cluster page streaming and adaptive screen-space error selection. This is not automatically v1.0 NECESSARY, not a copy of Unreal Nanite, and needs license/legal review before adopting conceptual architecture beyond public principles.

### Culling correctness: false negatives are worse than overdraw
- Coarse **frustum** tests use conservative bounding spheres/AABBs/OBBs with correct transform, nonuniform/negative scale, animated/morph/skinned/WPO displacement envelopes, camera jitter, stereo/VR if later supported and origin rebasing; invalid/unknown bounds mean **visible**, not culled.
- Backface/cone meshlet culling permitted only for provably suitable closed/one-sided geometry and material; double-sided/foliage, winding flips or deformation invalidate naive cones.
- **Occlusion/Hi-Z** is conditional. Depth hierarchy must correspond to a known camera/viewport, full occluder history and correct depth convention (reversed-Z or ordinary). Transparent, alpha-masked and small perforated surfaces are **not trusted opaque occluders by default**. Use conservative bounds and bias, coverage confidence, counter evidence, reject stale pyramid.
- **Temporal coherence:** avoid popping/disappearing when camera moves rapidly, teleports, changes FOV, origin rebases, scene edits, resize, depth convention or device generation. Invalidate/rebuild depth history; uncertain result forces draw/stream coarse proxy. Hysteresis stabilizes LOD and occlusion decisions, but must not hide newly visible required geometry.
- **GPU-driven indirect:** bounded, validated instance/draw/meshlet counts, robust buffer range, indirect index validation, queue/barrier safety, per-frame generation, shader feature checks. No CPU visible-count assumption as authority on GPU completion.

### LOD, HLOD and cracks
- Define `GeometricErrorMetricV1` and `ProjectedErrorV1`: world-space simplification error, camera projection, viewport pixel density and camera-to-bounds min distance. Screen-space error, hysteresis and target cap are requested quality policies, not a fixed guarantee of pixel-perfect geometry on all hardware.
- Preserve authored normals/tangents/UV seams, material boundaries, vertex colors, bone weights/morph targets, collision and silhouette features according to explicit fidelity/rights constraints; geometry error metrics alone are not enough for foliage/transparency.
- HLOD combines **eligible** nearby scene assets into clusters/proxies without losing Data-02 original AssetIds/scene edits, material/shader legality or object picking. Animated/skinned instances, destructible/interactive or dynamically modified components may require explicit exclusion or dynamic refit and never automatically baked to static proxy.
- **Geometric seams/cracks** between mesh/LOD generations and neighboring clusters need deterministic stitching/skirt or conservative overlap strategies, with visual/golden tests; avoid claims of seamless transitions without hardware tests.
- Quantization and compressed mesh streams are **derived artifacts** and must state error envelope, target ABI/version, endian/precision and decoder bounds; exact original source remains outside derived artifacts in owner-controlled storage.
- Vegetation uses vegetation-specific categories: aggregate/non-opaque alpha cutout, double-sided leaves, thin branches and seasonal animations; common cluster simplification and occlusion can increase overdraw or create vanishing canopy. Require A/B testing of billboards/impostors, coarse instances and meshlet approaches.

### Mesh streaming and residency
`MeshLODManifestV1` maps source AssetId/revision to cluster hierarchy and target capability. `GeometryChunkRefV1` references DATA-05 immutable verified chunks, codec flags and content digest; hashed bytes do not prove author/publisher identity. Bundle generation and rights manifests remain DATA-05.
- A `VisibilityPlanV1` may request missing chunk priorities by screen-space value, camera motion, latency estimates and residency tier. **DATA-05** owns actual IO/network/cache and verification, **GFX-03** owns GPU allocation/upload fences, **GFX-04** owns "what is visible and which proxy is acceptable".
- Preserve **root/coarsest LOD residency** when entering visible region so streaming failure cannot create a silent hole. For critical geometry with no proxy, return typed missing-content / block render for that object, with explicit diagnostic; do not silently drop collision/quest objects.
- CPU, IO, GPU upload, VRAM, chunk count and concurrent request budgets; cancellation/re-prioritization for rapid camera motion and scene revisions; avoid starvation of near/important objects by speculative far prefetch.
- Last-good geometry persists across failed patch and device generation changes until safe retirement; invalid/poisoned chunk is quarantined, not decoded on GPU as trusted vertex/index source.

## Technology research and current upstream reality
- [meshoptimizer](https://github.com/zeux/meshoptimizer) C/C++ **MIT** provides index/vertex locality optimization, quantization, simplification, meshlets and bounds, compression; its experimental API list can change. `clusterlod.h` (alongside meshoptimizer) is a research candidate for hierarchical clustering; exact source release and license, algorithm quality and legal provenance must be verified at code selection. Never assume a release note means it is pinned.
- Ratified glTF extensions [EXT_meshopt_compression](https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Vendor/EXT_meshopt_compression/README.md) and [EXT_mesh_gpu_instancing](https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Vendor/EXT_mesh_gpu_instancing/README.md) define exchange semantics; don't confuse glTF buffer compression with GPU visibility scheduler. `KHR_meshopt_compression` may be a draft in some toolchains and **requires current registry confirmation**, not assumed ratified.
- [VK_EXT_mesh_shader](https://docs.vulkan.org/features/latest/features/proposals/VK_EXT_mesh_shader.html) is capability-gated, not baseline; modern GPU technologies do not remove the need for backwards compatible vertex/index draws. Browser WebGPU optional indirect draw and feature limits need explicit validation.
- Unreal [Nanite documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/nanite-virtualized-geometry-in-unreal-engine) is **comparative research** only: hierarchical clusters, demand streaming, screen-space selection. It documents restrictions and costs of perforated foliage/aggregate geometry, so Stormline must not claim equivalent behavior or copy Unreal proprietary files.

## Editor, CLI and MCP
Expose semantic `geometry.asset.inspect`, `geometry.lod.preview`, `geometry.visibility.inspect`, `geometry.stream.plan`, `geometry.quality.validate`, `geometry.diagnostics.snapshot` with capability-scoped, bounded, project-relative and redacted output. Any recipe edit or derived cook must use approved DATA-03/05 authoring actions with revision locks and quotas. No raw driver draw command, arbitrary GPU buffer address, mesh decoder memory pointer, shell invocation or external URL from LLM. Visibility recording must not silently leak scene layout/private geometry.

## Original R&D: Stormline Visibility Continuity Graph (SVCG)
**Prove-or-drop only.** Propose bounded confidence scores for camera-path occluder history, deformation envelopes and resident LOD hysteresis. Against baseline CPU frustum + fixed LOD + optional deterministic Hi-Z, measure missed visible objects (must be zero for correctness), frame-time p95/p99, VRAM, CPU cull cost, draw/triangle counts, stream bytes, pop-in and complexity. Must not add ML/model dependencies or replace conservative safety checks; discard when no reproducible benefit.

## Future implementation gates
Before #32: GFX-03 and DATA-05 predecessor **code** implemented and objectively audited/merged, GFX-01/02 stable RHI/reflection contracts, CORE-05 coordinate policy, approved technology/SDK versions, exact meshoptimizer release and license/SBOM, real target GPU/OS/browser matrix, rights-cleared 2D/2.5D/3D/foliage fixtures, actual low-end and high-end perf budgets, security/fuzz/stream/cross-frame proof, source paths and CI commands, approved ADR-0017/Scope/DoD/release class and **fresh SHA-256 Context Lock**. This research does **not** unlock code.

See [matrix](../research/gfx-04-geometry-technology-matrix.md), [ADR-0017](../adr/0017-gfx-04-visibility-geometry-policy.md), [API](../contracts/gfx-04-geometry-api.md), [future tests](../testing/gfx-04-acceptance-matrix.md).
