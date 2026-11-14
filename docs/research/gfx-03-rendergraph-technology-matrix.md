# GFX-03 — Render Graph, Synchronization & VRAM Technology Matrix

**WO:** NLE-P00-WO-002-GFX-03 | **Issue:** #129 | **Status:** PROPOSED / RESEARCH DOCUMENTS ONLY  
No allocator/vendor SDK/renderer, GPU driver or benchmark currently installed/tested as part of this research.

| Candidate | License / authoritative source | Role to evaluate | Risks and decision gates |
|---|---|---|---|
| **Owned declarative DAG compiler** | Stormline code license OPEN | stable pass/resource semantics, validation, dependency edges, optimal scheduling bounded by correctness | write from scratch only narrow graph IR; graph cycles, alias/fence proof burden, backend adapters |
| **Vulkan Synchronization2** | Khronos Vulkan specification, exact loader/headers licenses TBD | stage/access2 barrier plan, queue-family transitions and validation layers | feature/API/version gate and correct submit ownership; overbarriering can destroy performance |
| **Vulkan Memory Allocator (VMA)** | [GPUOpen VulkanMemoryAllocator](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator), **MIT** | Vulkan suballocations, pools, virtual allocation, budget statistics | verify exact tag/SBOM, alignment/memory-type, allocation multithreading and physical budget trust; not a render graph |
| **D3D12 legacy barriers** | [Microsoft D3D12 barriers](https://learn.microsoft.com/en-us/windows/win32/direct3d12/using-resource-barriers-to-synchronize-resource-states-in-direct3d-12), SDK terms | transitions, aliasing and UAV barriers baseline on supported Windows | explicit state/race, barrier inside render pass constraints; test debug layer |
| **D3D12 enhanced barriers** | [Microsoft enhanced barriers](https://learn.microsoft.com/en-us/windows-hardware/drivers/display/enhanced-barriers), SDK terms | independent sync/layout/cache control, finer alias | availability is conditional, NOT guaranteed by Windows label; fallback legacy resource barriers |
| **D3D12 Memory Allocator (D3D12MA)** | [GPUOpen D3D12MemoryAllocator](https://github.com/GPUOpen-LibrariesAndSDKs/D3D12MemoryAllocator), **MIT** | pools, placed-resource alias and budget stats, virtual allocation | exact tag is required: top-level GPUOpen product page and current header can show different releases; don't pin from search alone |
| **Metal MTLHeap / MTLFence / MTLEvent** | [Apple Metal heaps](https://developer.apple.com/documentation/metal/memory-heaps), SDK terms | Apple Silicon/Metal native heap allocation and alias/fence synchronization | Apple warns default MTLHeap hazard-tracking mode may be untracked; aliasing without fence/event is undefined/corrupting |
| **Metal resource alias safety** | [Apple makeAliasable](https://developer.apple.com/documentation/metal/mtlresource/makealiasable%28%29), SDK terms | reuse transient memory after completion | cannot reuse after marking aliased until done; need device/OS API-specific test, never assume safety |
| **Browser WebGPU usage scopes** | [W3C WebGPU specification](https://www.w3.org/TR/webgpu/) | validated render/compute pass usages and implicit resource synchronization | different from explicit Vulkan/D3D API; illegal within-pass read/write and queue barriers must reject or split passes |
| **CPU graph plan + CPU-only headless mock** | project-owned | deterministic topo/cycle/hazard/alias checker before GPU | mock cannot prove driver rendering or real GPU timing; no false headless VRAM measurement |
| **Render graph references: Filament/bgfx** | [Filament project](https://github.com/google/filament) and [bgfx](https://github.com/bkaradzic/bgfx), LICENSE exact tag review | study graph lifetimes and render scheduling trade-offs | don't copy whole renderer or conflate pass graph with shaders/GFX-05 material algorithms |
| **SAFG (project research hypothesis)** | NOT IMPLEMENTED | optional critical-path/VRAM pressure policy | prove-or-drop against deterministic DAG, conservative non-alias/single-queue and measured alias baseline |

## Explicit scoring priorities (PROPOSED, not scored)
1. **Correctness and hazard rejection** 30%; illegal resource order, alias or GPU lifetime is a hard fail irrespective of frame-rate.
2. **Platform/native/browser feature parity with safe fallback** 20%.
3. **VRAM/RAM and p95/p99 frame time on weak hardware** 20%.
4. **Auditable contracts, diagnostics and testability** 15%.
5. **Licensing/SBOM/SDK maintenance** 10%.
6. **R&D innovation opportunity without uncontrolled complexity** 5%.

No numeric benchmark results or production winner. Do not auto-select VMA+D3D12MA just because MIT; ELEVATED GPU memory/race validation and exact backend stack decisions precede code.

## Platform proof requirements
- Windows D3D12 legacy AND enhanced-when-supported, Vulkan with synchronization validation; Linux Mesa/vendor Vulkan; macOS Apple Silicon native Metal (heap hazard and alias), optional Intel matrix; browser WebGPU fallback policy and usage scopes. Backend win must account for actual device/capability tier, OS and driver, not label.
- WebGPU usage scope is a validation concept, not native barrier API; memory budget and driver heap details often opaque. Avoid claiming physical VRAM budget accuracy from browser.
- Discrete GPU vs unified memory on Apple/low-power PCs changes accounting; driver budget availability can be unknown. Need `KNOWN/ESTIMATED/UNKNOWN` and conservative fallback.
- Multi-frame-in-flight plus async compute means naive pass-interval overlap can hide true GPU in-flight overlap; fence completion proof required.
- Shared cache/texture streaming from DATA-05 and GPU resident resources from GFX-01/03 are different ownership, and GPU heap aliasing must never delete underlying authored source.

## External sources reviewed (14 November 2026)
- https://docs.vulkan.org/guide/latest/synchronization.html
- https://docs.vulkan.org/spec/latest/chapters/synchronization.html
- https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator
- https://github.com/GPUOpen-LibrariesAndSDKs/D3D12MemoryAllocator
- https://learn.microsoft.com/en-us/windows-hardware/drivers/display/enhanced-barriers
- https://learn.microsoft.com/en-us/windows/win32/direct3d12/using-resource-barriers-to-synchronize-resource-states-in-direct3d-12
- https://developer.apple.com/documentation/metal/memory-heaps
- https://developer.apple.com/documentation/metal/mtlresource/makealiasable%28%29
- https://www.w3.org/TR/webgpu/

**None of these technologies has been installed, tested, vendored or approved as an engine dependency.**
