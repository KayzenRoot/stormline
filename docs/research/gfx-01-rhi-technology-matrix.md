# GFX-01 — Native/Web Rendering Hardware Interface Technology Matrix

**WO:** NLE-P00-WO-002-GFX-01 | **Issue:** #123 | **State:** PROPOSED / DOCS ONLY.
**No GPU SDK, library, backend or shader compiler has been installed or benchmarked.**

| Candidate | License / authoritative source | Potential capability | Main risk / gate |
|---|---|---|---|
| **Stormline-owned C++20 thin RHI** | Engine code license still OPEN | native API control and stable public contracts | three native backends maintenance/security/recovery cost, versioning and cross-platform testing |
| **Vulkan 1.x** | [Khronos Vulkan spec](https://registry.khronos.org/vulkan/) and headers/loader license require exact audit | explicit graphics/compute/synchronization on supported Windows/Linux | device/driver extensions and portability subset; min Vulkan version only after GPU matrix |
| **D3D12** | [Microsoft D3D12 docs](https://learn.microsoft.com/en-us/windows/win32/direct3d12/direct3d-12-graphics) SDK terms to review | native Windows API and feature tiers | Windows SDK/driver/compiler, cross-platform duplicate adapter and portability |
| **Metal** | [Apple Metal](https://developer.apple.com/metal/) OS SDK license to review | preferred direct macOS API candidate Apple Silicon | Objective-C++ bridging and GPU families, Intel support/version minimum |
| **KosmicKrisp / Vulkan-on-Metal** | [Khronos porting page](https://www.vulkan.org/porting), [Mesa project](https://gitlab.freedesktop.org/mesa/mesa), exact source/license TBD | Vulkan translation candidate for Apple Silicon | Khronos recommendation is recent; validate maturity, license, platform GPU/feature gaps before distribution |
| **MoltenVK** | [official repo/notice](https://github.com/KhronosGroup/MoltenVK) exact tag/third parties TBD | Vulkan-on-Metal compatibility, Intel macOS route | **Khronos deprecation/community-maintained**; Apple Silicon should not depend on it by assumption |
| **SDL3 GPU** | [SDL3 docs](https://wiki.libsdl.org/SDL3/CategoryGPU); [SDL zlib license](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt) | Vulkan/D3D12/Metal portable device/resource API, sample parity | documented broad hardware target rather than bleeding edge features, shader formats and feature ceiling; no automatic WebGPU backend |
| **Dawn Native / Tint** | [Dawn README](https://github.com/google/dawn/blob/main/README.md) BSD-3-Clause primary; [LICENSE](https://github.com/google/dawn/blob/main/LICENSE) mixed/file-level notices | WebGPU C++/C native implementation and WGSL compiler candidate | dependency and build footprint, shader feature/API compatibility, platform parity, bundled code licenses |
| **wgpu-native** | [Cargo license MIT OR Apache-2.0](https://github.com/gfx-rs/wgpu-native/blob/trunk/Cargo.toml), [wgpu repo](https://github.com/gfx-rs/wgpu) | WebGPU native C API backed by Rust implementations | Rust toolchain and static/dynamic ABI, version/feature mismatch with browser and C++ target, transitive licenses |
| **bgfx** | [official BSD-2 docs](https://bkaradzic.github.io/bgfx/overview.html) | permissive cross-platform renderer, Vulkan/D3D/Metal/WebGL/WebGPU native variants | larger renderer abstraction vs RHI separation, extension APIs, build/licensing and performance proof |
| **Browser WebGPU** | [MDN WebGPU](https://developer.mozilla.org/en-US/docs/Web/API/WebGPU_API), [W3C spec](https://www.w3.org/TR/webgpu/) | modern browser device API | **not Baseline universal**; HTTPS secure context, feature limits, adapter loss, browsers/GPU flags; PLAT-03 owns |
| **Browser WebGL2** | [Khronos WebGL](https://registry.khronos.org/webgl/specs/latest/2.0/) | candidate limited-function browser fallback | missing compute/advanced texture/pipeline support; explicit degradation, never fake WebGPU parity |
| **GPU validation / tracing** | [RenderDoc](https://renderdoc.org/) (license & compatibility TBD), Xcode GPU capture, Vulkan validation layers | analyze correctness, draw calls and device errors | driver and runner availability, overhead/privacy; not automatically installed in public CI |
| **SCGF original research hypothesis** | project-native research, no implementation | typed capability negotiations and recovery receipts | compare to baseline feature flags+generation handles; prove-or-drop |

## Critical 2026 finding: Vulkan-on-Metal transition
The [Khronos porting guidance](https://www.vulkan.org/porting) now explicitly says MoltenVK is **deprecated and community maintained**, directs Apple Silicon users toward **KosmicKrisp**, and retains MoltenVK as the recommended route for Intel Macs/iOS. Do not write project specs assuming MoltenVK is Khronos' long-term universal official answer or that KosmicKrisp has already passed Stormline tests. A **native Metal** baseline remains the safer candidate architecture to benchmark independently of Vulkan translation. This is an upstream guidance snapshot, not a proven Stormline backend.

## Suggested evaluation sequence (no selected winner)
1. Prototype equivalent feature-tier BASE operations with **SDL3 GPU** portability reference and an **owned thin RHI** layered against Vulkan+Metal(+D3D12) mocks or actual adapters only during future authorized coding. Compare complexity and completeness.
2. Determine which advanced features are truly NECESSARY for release-1.0 vs IMPORTANT/FUTURE. Only benchmark necessary hardware features and actual 2D/3D workloads with validated artifacts. Do not make ray tracing, mesh shaders or bindless mandatory without evidence.
3. Evaluate native WebGPU via Dawn and wgpu-native if a single C ABI simplifies platform/backend maintenance; test native and browser WebGPU feature sets separately rather than equating them.
4. Compare bgfx as an existing alternative, avoid adopting whole renderer if it breaks Stormline's own GFX-02/03 public contract ownership.
5. Pin SDL/GPU-native/validation/shader compiler versions, exact license and third-party notices, Apple/macOS ABI/driver and Windows/Linux/Web matrix **before** implementation. Apple Silicon Metal tests mandatory; Intel coverage undecided.
6. Keep C++20 application/platform layer from CORE-01 separate from graphics backend. Web browser loader and GPU permission/secure-context policy belong PLAT-03.
7. SCGF prove-or-drop vs basic queries/restoration recipes and hardware profile caching, measured device loss/restart behavior.

## Proposed weighted scorecard, no measurements yet
- Correctness, resource/sync/device loss handling 25%
- Feature-tiers and native/Web portability including macOS 25%
- CPU/GPU/VRAM performance on modest hardware 20%
- Stable C++20 ABI/complexity/security 15%
- License/build/CI/community upkeep 10%
- Editor/headless tools integration 5%

Do not give library winner or fake numeric scores without comparable executable fixture sets, hardware drivers, versions and traces. Proposed candidates are neither dependencies nor approved code.

## Official research sources checked November 2026
- https://www.vulkan.org/porting
- https://github.com/KhronosGroup/MoltenVK
- https://wiki.libsdl.org/SDL3/CategoryGPU
- https://wiki.libsdl.org/SDL3/SDL_CreateGPUDevice
- https://github.com/google/dawn/blob/main/README.md
- https://github.com/google/dawn/blob/main/LICENSE
- https://github.com/gfx-rs/wgpu-native/blob/trunk/Cargo.toml
- https://bkaradzic.github.io/bgfx/overview.html
- https://developer.mozilla.org/en-US/docs/Web/API/WebGPU_API

**Research only**: no adapter selected, benchmark executed, RHI code or GPU driver tested.
