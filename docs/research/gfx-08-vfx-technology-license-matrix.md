# GFX-08 — VFX Technology, Platform and License Matrix

**Research issue #144** | **NLE-P00-WO-002-GFX-08** | **PROPOSED only**. Libraries, shaders, assets and exact package versions are NOT installed, frozen or production-certified.

| Candidate | Class | Portability and caveats | License/distribution gate | Future validation |
|---|---|---|---|---|
| Self-owned typed VFX node graph | NECESSARY proposal | stable schema/ports/cycles/quotas, GFX-02 shader bridge | independent original design | fuzz and deterministic CPU evaluation |
| CPU bounded particle simulation | NECESSARY baseline | C++ core/CPU, WebGL2 and headless; no GPU needed | original code, no SDK | fixed-step/PRNG/cancel/LOD |
| GPU SoA compute emitters | IMPORTANT conditional | Vulkan/DX12/Metal/WebGPU feature/limits; WebGL2 excluded | own shaders via GFX-02 | compute cost, busy GPU, GPU fallback |
| GPU alive compaction and prefix-sum | IMPORTANT conditional | buffer/atomic/overflow/alias and per-backend shader features | own algorithm, references reviewed | no write OOB or bad dispatch |
| Ribbon/trail tessellation | NECESSARY visual candidates | screen-space vs world length cap, camera turns, Web fallback | original design | fast ARPG trail continuity |
| Sprite/flipbook/mesh particles | NECESSARY | GFX-05 textures/materials, GFX-04 mesh bounds | authored texture rights and DATA-05 cook | 2D/2.5D/3D art and alpha |
| AMD FidelityFX Parallel Sort | OPTIONAL native accelerator | DX12/Vulkan GPUOpen, HLSL SM6 wave features; Metal/Web not automatic | MIT technique, transitive notice/version/SBOM gate | sort overhead vs CPU small/large |
| Stable CPU depth sorting | BASELINE for bounded blend | WebGL2/Metal/native, O(n log n) or stable bucket | own code | translucent correctness/overdraw |
| Weighted blended OIT | OPTIONAL approximation | blend formats and layer interactions, fails thick/refraction | independent mathematical implementation | golden crossing trails/alpha |
| Depth-soft particles | IMPORTANT visual | scene depth must match projection reversed-Z/alpha | own post visual path | no depth halos/near-plane |
| Volumetric stamps + GFX-06 fog | IMPORTANT optional | density emitter only, lighting owned GFX-06 | own stamp format | no fog GPU memory overrun |
| OpenVDB/NanoVDB research | OPTIONAL offline asset interchange | source/cook/codec size and Web/Metal runtime not universal | OpenVDB upstream Apache-2.0, actual included components/deps/codec separately | sparse assets vs sprites |
| Effekseer effect authoring/runtime | OPTIONAL interoperability, not mandatory engine | runtime backends Vulkan/Metal/WebGL and tool distribution vary | MIT core; DirectX/Vulkan backend runtime licenses/transitive glslang/DirectX; effects CC0 samples check | import/export translation and license audit |
| Epic Unreal Niagara | COMPARATIVE REFERENCE only | UE graph/data interfaces, GPU simulation and commercial engine coupling | Epic proprietary engine rights; no code/assets copying | ARPG emitter scalability per-instance costs |
| Godot GPUParticles/CPUParticles | COMPARATIVE REFERENCE only | GPU/CPU path and UI graph differences, no parity guarantee | Godot MIT but actual third-party assets separate | low-end correctness and trails |
| GPU indirect draw | OPTIONAL | capabilities, GFX-03 memory/fences/visibility, not guaranteed WebGL2 | own shader/pipeline | culling vs CPU overhead |
| Visual-only collision depth/SDF | IMPORTANT optional | camera/offscreen and stale depth, not gameplay collision truth | GFX-04 owns geometry sampling, no PHY duplicate | avoid false authoritative hit |
| GPU particle-to-light requests | IMPORTANT integration | GFX-06 scarce light/volumetric budgets, low-end emissive fallback | no third-party core | explosion flashes vs frame budget |
| Camera reactive masks / motion vectors | IMPORTANT integration | GFX-07 temporal history/alpha emitter and shader motion | GFX-07 post owner | no ghost spells or blurred UI |
| SVAG governor | OPTIONAL PROVE-OR-DROP | adaptation overhead/flicker/readability, no novelty claim | hypothesis original, prior art review | quality-cost Pareto vs fixed LOD |

## Key cautions
- **AMD Parallel Sort** is MIT and described for DX12/Vulkan Shader Model 6, RDNA-focused. The GPUOpen FidelityFX 1.1.4 page refers to older SDK v1 source; modern AMD FSR SDK 2.4 signed DLL model is a **different product/version**, not automatic Parallel Sort dependency. Do not claim Metal/WebGPU drop-in.
- **Effekseer runtime MIT** with backend/tool third-party components: its own documentation identifies separate Vulkan/DirectX licensing dependencies (e.g. glslang/DirectX Tool Kit). Version and license of integrated binaries and effect content must be verified before any code. Its authored effect file is not the canonical Stormline graph unless import translation is approved.
- **OpenVDB upstream Apache-2.0**, but libraries, included components, codecs, image assets and optional GPU NanoVDB integration have own transitive gates; VDB volumetric **not mandatory** at runtime, especially on Web. DATA-03/05 own hostile format parsing and cooking.
- **Unreal Niagara** is Epic's native proprietary engine technology; public benchmarking docs are reference, not permission to lift Niagara engine code or Unreal example content. Godot MIT engine code still needs exact feature and asset provenance.
- “GPU particles faster” is a workload-specific hypothesis: CPU can win for tiny bursts or GPU-bound devices. **Visual GPU collision must NEVER be server-authoritative gameplay physics**.
- OIT is approximate and screen-space masks/sort can be expensive; high particle count is not equal high visual quality. Overdraw, actual opacity and HDR ghosting may dominate.
- **WebGL2** cannot run modern compute shaders; WebGPU requires adapter storage/compute limits and WGSL implementation; Metal backend is a separate compiler/capability proof from Vulkan/HLSL.
- No software licenses, redistribution rights, package versions, hardware performance nor code are approved by adding a row to this matrix.

## Primary references and upstream licensing evidence
- Epic Niagara scalability and GPU/CPU budget caveats: https://dev.epicgames.com/documentation/en-us/unreal-engine/scalability-and-best-practices-for-niagara
- Godot stable GPU/CPU particles (independent reference): https://docs.godotengine.org/en/stable/tutorials/3d/particles/index.html
- Godot GPUParticles3D trails and restart semantics: https://docs.godotengine.org/en/stable/classes/class_gpuparticles3d.html
- Effekseer MIT runtime code: https://github.com/effekseer/Effekseer/blob/master/LICENSE
- Effekseer Tool runtime/backend license notices: https://effekseer.github.io/Help_Tool/en/overview.html
- Effekseer platform and source compatibility: https://github.com/effekseer/Effekseer
- AMD GPUOpen FidelityFX Parallel Sort (MIT DX12/Vulkan): https://gpuopen.com/fidelityfx-parallel-sort/
- AMD FidelityFX Parallel Sort documentation: https://gpuopen.com/manuals/fidelityfx_sdk/techniques/parallel-sort/
- OpenVDB Apache-2.0 current upstream LICENSE: https://github.com/AcademySoftwareFoundation/openvdb/blob/master/LICENSE
- W3C WebGPU GPU compute/capability standard: https://www.w3.org/TR/webgpu/
