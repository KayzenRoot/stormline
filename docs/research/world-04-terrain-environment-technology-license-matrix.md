# WORLD-04 — Terrain/Environment Technology, GPU Feature and License Matrix

**Research #168 | NLE-P00-WO-002-WORLD-04 | ADR-0029 PROPOSED.** Nothing below has been integrated, benchmarked or licensed as a Stormline dependency.

| Technology / method | Proposed status and subsystem owner | Strength vs cost / safety / target limits | Rights/actual gate |
|---|---|---|---|
| Authored heightfield tile source with stable patch IDs/layers and explicit cave mesh topology | **NECESSARY**, WORLD-04 source + DATA-04 persistence | authorable/regenerable, tile borders/precision/height limitations; overhang needs mesh | original contract, external elevation/map copyright separate |
| Tile/quadtree patch mesh LOD with edge stitching/skirts and geomorph | **NECESSARY baseline candidate**, GFX-04 geometry driven by WORLD-04 | predictable GPU WebGL2 fallback, more CPU mesh/state than clipmap in some workloads | original algorithm, measured seam and error |
| GPU geometry clipmaps (NVIDIA GPU Gems 2) | **IMPORTANT optional candidate**, GFX-04 | nested rings, toroidal height update; needs vertex texture/data residency and crack-proof transitions, benchmark historical not current | published algorithm reference, **not** right to copy arbitrary source/figures |
| Hardware tessellation / mesh shaders / compute tile generation | **FUTURE feature-gated**, GFX-01/02/04 | quality potential, platform fragmentation and shader complexity, WebGL2 not guaranteed | native backend and legal shader source approval |
| meshoptimizer mesh simplification/cluster processing | **OPTIONAL GFX-04/DATA-05 adapter** | CPU offline mesh and cluster LOD, some experimental APIs not stable | **MIT**, pin exact version, notices, SBOM, actual target builds |
| Terrain3D for Godot | **REFERENCE ONLY** | open MIT heightmap editor, practical brush/splat/tooling reference but Godot GDExtension ownership not Stormline API | **MIT** upstream plugin, no copied addon/assets |
| Multichannel splatmaps and triplanar PBR | **NECESSARY source**, GFX-05 material | normalized weights/zero sum, slope/texture seams and normals; textures budget | original source + asset texture media rights |
| Virtual texturing / sparse tiled textures | **OPTIONAL future GFX-05/GFX-03** | streaming residency and page fault complexity, feature gates, browser fallback | not duplicated in WORLD-04 |
| Vegetation instance placement + wind visual profiles | **NECESSARY WORLD-04 authored data**, GFX-04/05/06 final | huge instance/overdraw/shadow costs, collision separate, growth procedural WORLD-05 | author-owned licensed mesh/foliage texture packs |
| Gerstner-style or heightmap water surface visual | **IMPORTANT portable baseline**, GFX-05/07 shading | approximate water with controllable CPU sample if PHYS needs it; not a fluid solver | original implementation / academic public formula; no FFT library adopted |
| Spectral FFT ocean / volumetric clouds | **FUTURE GPU optional** | quality/precision/VRAM/compute and WebGL2 fallback, cross-service ownership | library choice independent, FFTW licensing not assumed permissive |
| Bruneton precomputed atmospheric scattering | **OPTIONAL GFX-06/07 adapter** | physically motivated LUT with GPU memory/time tradeoffs, optional analytic sky | **BSD** upstream source license, pin exact rev, notice/3rd-party review |
| Godot 4.6 Environment/fog/sky & occlusion | **REFERENCE ONLY** | explicit HDR, fog/volumetric rendering tier and occlusion tradeoffs; does not prove feature equivalence | Godot core **MIT**, no editor assets imported |
| Unreal Landscape/Nanite/Foliage/Water system | **REFERENCE ONLY** | powerful authoring/terrain GPU design but assets and runtime under proprietary Epic terms | no engine source/assets copied |
| Khronos glTF EXT_mesh_gpu_instancing | **OPTIONAL import/export contract** DATA-03/GFX-04 | public extension reference for repeated mesh placement; not scene/biome semantic format | open technical spec; no distribution rights to vendor 3D models |
| SABE visual biome budget planner | **OPTIONAL PROVE-OR-DROP** | coordinated LOD may help but p99/cache/incorrect cull risk | original hypothesis, no novelty/performance claim |

## Decisions NOT taken
- The **GPU Gems 2** article published in 2005 reports very high performance on historic datasets/hardware. This is a research reference, **not measured Stormline FPS**, and its figures/code may have separate use rights.
- **Terrain3D** (Godot plugin) and **meshoptimizer** explicitly use MIT upstream, and **Bruneton atmospheric scattering** repo describes BSD; check exact pinned tag/tree plus all dependencies and notice/credits before integrating any selected code. Their APIs, coordinates, shaders and assets are not Stormline's own licensed fixtures.
- Godot 4.6 environmental classes demonstrate volumetric fog/HDR/fog options that differ by backend, not universal support. Unreal engine landscape and water docs are proprietary technology references; may not copy Unreal project assets, texture sets, sample landscapes or engine code.
- FFTW is not preapproved as a permissive dependency merely because FFT methods are common; if an FFT implementation is needed, independent licensing/SBOM and owner approval are required. No “free reference” confers copyright rights to third-party shaders/meshes/photogrammetry, maps or texture materials.
- Caves, cliffs, winding rivers and vegetation interact with WORLD-03 cells and PHYS colliders but WORLD-04 must not duplicate their authorities. Heightfield topology limits explicitly retained. Generated content lives WORLD-05; ground/biome artist edits in DATA-04 layered source win according to approved precedence.
- Required function on browsers is **feature-gated reduced** rendering: compute/mesh shader, GPU tessellation, 3D texture/float filter and volumetric fog are not guaranteed by WebGL2; absence must return explicit quality receipt/fallback rather than crash or false visual parity.
- Freeze source/license rights, scene image/mesh asset provenance and exact version, capability probes, GPU/CPU/memory benchmarks and user-visible credits before adoption. No library/SDK/vendor art installed by this research.

## Public first-party/primary sources, research only
- NVIDIA GPU Gems 2 terrain geometry clipmaps chapter (historical performance is not Stormline's): https://developer.nvidia.com/gpugems/gpugems2/part-i-geometric-complexity/chapter-2-terrain-rendering-using-gpu-based-geometry
- Terrain3D Godot plugin **MIT** source license: https://github.com/TokisanGames/Terrain3D/blob/main/LICENSE.txt
- meshoptimizer **MIT** library license and feature maturity: https://github.com/zeux/meshoptimizer/blob/master/LICENSE.md
- Bruneton precomputed atmospheric scattering implementation **BSD**: https://github.com/ebruneton/precomputed_atmospheric_scattering
- Godot 4.6 sky, fog, volumetric and post owner reference: https://docs.godotengine.org/en/4.6/classes/class_environment.html
- Godot 4.6 occlusion and level-of-detail practices: https://docs.godotengine.org/en/4.6/tutorials/3d/occlusion_culling.html
- Unreal Landscape technical design and authoring reference, proprietary Epic terms: https://dev.epicgames.com/documentation/en-us/unreal-engine/landscape-outdoor-terrain
- Khronos glTF EXT_mesh_gpu_instancing public extension reference (asset rights independent): https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Vendor/EXT_mesh_gpu_instancing/README.md
- WebGPU specification capability/texture/compute restrictions: https://www.w3.org/TR/webgpu/
