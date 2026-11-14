# GFX-01 — Portable Graphics RHI, Capability Tiers and Device Recovery

**Research WO:** NLE-P00-WO-002-GFX-01 | **Issue:** #123 | **Future code:** #29 BLOCKED  
**Status:** RESEARCH PROPOSED / NOT IMPLEMENTED | **Context Lock main:** 36f08368be2c1d1cdd8aa7bd553f4fed7d610d56  
**Risk:** LOW for docs, ELEVATED for future native GPU/driver, synchronization, lifetime and device-loss recovery.

## Mission
Plan a Stormline-owned, versioned Render Hardware Interface (RHI) that isolates GPU device selection, queues, resources, command encoding, synchronization and presentation from 2D/2.5D/3D gameplay, a multi-window Editor and future Web/browser backends. Keep high-end effects possible through explicit feature tiers without making exotic GPU features mandatory on modest hardware. Do **not** prematurely select or implement any backend.

## Responsibility and dependency graph
- **CORE-01** owns OS lifecycle, native windows/surfaces, event delivery, display and adapters; GFX-01 receives typed platform surface handles, not arbitrary OS paths or exposed Cocoa/Win32 internals.
- **CORE-02** owns CPU allocator, memory budgets and ownership conventions. GFX-01 reports device heap constraints, GPU allocation pressure and resource residency counters; complex VRAM pooling/alias/transient algorithms belong GFX-03.
- **CORE-03** later coordinates CPU jobs; RHI explicitly describes thread-safe operations, submission ownership, fence wait/cancel; no implicit parallel command encoding.
- **CORE-05** owns world-space units, handedness and precision. RHI declares normalized GPU NDC/depth/viewport/texture conventions and backend conversion without changing world data.
- **CORE-06** supplies redacted diagnostics, context IDs, counters and trace; GPU timestamp support optional/capability-gated; driver information can be privacy-sensitive.
- **DATA-05** supplies cooked texture/geometry/scene variants compatible with device capabilities; never assume every Windows, Linux or macOS GPU supports identical BC/ASTC/ETC/compression or shader formats.
- **GFX-02** owns shader source languages, compilation, reflection, variants and pipeline binaries; GFX-01 exposes typed pipeline creation/compatibility and error reporting only.
- **GFX-03** owns render graph scheduling, hazard inference, transient resource reuse and VRAM residency; GFX-01 exports low-level barriers/queue submission primitives, not another authoritative graph.
- **GFX-04+**, **TWO**, **EDITOR** and **PLAT-01/02/03/06** consume stable RHI capability contracts; 2D vs 3D is not a separate device ABI.

## Backend research direction, not a decision
Research candidate **thin Stormline C++20 RHI with isolated backends**:
1. **Vulkan** on supported Windows/Linux devices as an explicit GPU API candidate (choose exact API level only after hardware coverage).
2. **Direct3D 12** as a native Windows alternative/fallback where warranted, not mandatory duplicate implementation without tests.
3. **Metal** as a native macOS baseline; avoid requiring Vulkan translation for Apple Silicon. Vulkan-on-Metal remains an opt-in compatibility research track: Khronos now states MoltenVK is deprecated/community-maintained, recommends KosmicKrisp for Apple Silicon and MoltenVK for Intel Macs. This requires revalidation with actual drivers, license/SBOM and hardware, and can change.
4. **WebGPU browser** as a separate PLAT-03 adapter, with secure-context availability and WebGL2 degraded fallback to be scoped. Desktop WebGPU-compatible **Dawn** or **wgpu-native** may be evaluated as a common RHI backend, but their runtime, shader, C ABI and feature restrictions must be measured.
5. **SDL3 GPU API** as a low-complexity cross-platform comparison implementation (Vulkan/D3D12/Metal). SDL documentation explicitly says it targets a broadly compatible feature set, not cutting-edge hardware features. Evaluate whether it meets Stormline tier 0/1, and whether native extensions can remain isolated. Do not confuse SDL platform/window CORE-01 with selecting SDL GPU backend.
6. **bgfx** BSD-2-Clause as API-agnostic reference, not automatically adopted. Compare integration/API extension constraints and exact renderer scope.

No chosen winning library or deployed SDK. A native RHI may create high maintenance cost; choose the least complex option demonstrated to satisfy explicit GFX tiers and 1.0 acceptance.

## Logical RHI service boundaries
```text
Platform CORE-01 + device capability discovery
          |
    GpuAdapter enumerate + choose [policy/OS/user-specified]
          |
    GpuDevice [feature tier, budgets, error callbacks, generation]
          |
    Queue + Resource descriptors + Command encoder + Sync primitives
          |
    Surface/swapchain | Offscreen target | Headless validate-only mode
          |
   GFX-02 shader/pipeline <- GFX-03 resource/pass scheduler
          |
   TWO/GFX render clients + Editor viewports + DATA-05 cooked assets
```

### Lifecycle state machine
`UNINITIALIZED -> ADAPTER_DISCOVERED -> INITIALIZING -> READY -> SUSPENDED/LOST -> RECOVERY_PREPARED -> RECREATING -> READY | FAILED -> DISPOSED`.
A device-lost event invalidates all **generation-tagged** resource handles and in-flight fences, blocks unsafe submissions, stops uploads and invalidates caches requiring re-creation. Restoration reuses immutable DATA-05 assets and CPU-side descriptors only after capability re-probe; every resource needs explicit rehydration semantics. Not all drivers/backends can recover from a device loss in-process: supported response may be an actionable `RESTART_REQUIRED` rather than a false recovery promise. Repeated loss, OOM, suspend, monitor hotplug and window resize must not hang shutdown.

### Ownership and resource safety
- Expose opaque typed `GpuDeviceId`, `GpuBufferHandle`, `GpuTextureHandle`, `CommandListHandle`, `FenceHandle` with **generation counters** and checked lifetime, not raw backend pointers publicly.
- `BufferDescV1` and `TextureDescV1` include usage, size/alignment, format/strides/sample count, mip/layer, writable/cpu mapping, origin/transfer, initial state; validate before GPU allocation and against device limits.
- Ownership of mapped memory and queue submissions explicit; cannot release resources with live GPU references until fences or deferred-retirement protocol say safe. Never recycle a stale descriptor handle into another device generation.
- Sync must model queue family, read/write hazards, stages, pipeline barriers and CPU/GPU fence boundaries without hiding mandatory correctness checks. Async compute/transfer/mesh/ray tracing are optional feature tiers only.
- Core resource/command APIs must permit small testable operations before full render graph exists. Don't build GFX-03 alias tracking inside GFX-01.
- HDR/sRGB/P3 surface color handling, presentation latency and swapchain state versioned and feature-gated; no claim of default HDR support.

### Feature tier policy (proposed categories, not release classes)
- **Tier Base:** simple 2D sprites, basic 3D buffers/textures, depth, linear/sRGB sampled resources, standard rasterization, present/offscreen and CPU fallback/diagnostics if GPU missing.
- **Tier Compute:** storage buffers, compute queues/pipelines where supported, async uploads and richer material capability **only after feature query**.
- **Tier Advanced:** bindless/descriptors, indirect GPU-driven rendering, mesh/task shaders, ray tracing, sparse/virtual textures, variable rate shading, multiview/HDR. Each individually checked, no single forced "AAA" tier or assumed universal hardware.
- Host RHI advertises independent `supported_features` + numeric limits rather than OS-name-based global bit; feature tiers are derived, not the only truth. Renderer chooses fallback or refuses unsupported technique with typed diagnostic.

### Coordinate and clip-space contracts
Define Stormline canonical clip-space convention and explicit per-backend transforms, test Y flip, depth [0,1] vs [-1,1], front-face winding/culling, projection reverse-Z, texture vertical origin and framebuffer readback orientation. The CORE-05 world-space RH Y-up policy is a separate proposal and must not be silently mutated by SDL GPU's documented left-handed NDC convention. Keep color transfer and premultiplied alpha in the data contract; visual golden tests necessary.

### Headless and CI
Differentiate `NO_DEVICE_HEADLESS` validation-only (never claims a pixel rendered), native **offscreen GPU rendering** when a real/virtual device exists, and Web browser canvas. GitHub docs CI does not prove GPU hardware, Apple Silicon or graphics driver behavior. Use hardware machines when available, note public runner limitations. Unknown adapter/driver state should yield typed error, not pretend a GPU is present.

## Security, privacy and supply chain
- Treat shaders, SPIR-V/DXIL/MSL binaries, textures and external GPU data as untrusted until DATA-03/05 and GFX-02 validation; a GPU driver is a privileged boundary. Bound sizes/allocations, shader work and compile timeout; validate buffer ranges, uniform layout, integer multiplication and resource aliases.
- GPU validation layers do not replace application authorization, fuzzing or hostile-source gating. Device extensions/driver flags must not be chosen by MCP clients.
- Editor/CLI/MCP parity is **semantic inspection** (`rhi.adapters.list`, `rhi.capabilities.inspect`, `rhi.device.health`, `rhi.diagnostics.snapshot`) and authorized harmless preview tests. No exposed arbitrary native handles, code injection, direct driver calls, arbitrary shader compilation or unsigned plugin load through MCP.
- Metadata minimization for GPU vendor/device IDs, logs and crash traces; upload opt-in only. Third party license/SBOM by exact tag, compiled files and transitive sources; SDL3/zlib, bgfx BSD, wgpu MIT/Apache, Dawn BSD with per-file notices require audit.
- GPU driver/toolchain versions, platform SDKs, validation layers and shader compiler dependencies vary; exact tested versions required before implementation and distribution.

## Research hypothesis: Stormline Capability-Aware GPU Fabric (SCGF)
Potential owned capability negotiation and recovery planner using GPU feature fingerprints and versioned rehydration receipts. **Prove-or-drop** against ordinary typed feature queries, generation handles and deterministic restore ordering. Do not duplicate GFX-03 resource graph, claim superior latency or force ML. Measure recovery success, time-to-device-ready, VRAM overhead and correctness under mock device loss.

## Future proof gates
GFX-01 implementation #29 requires selected backend architecture, pinned API/SDK/library versions, licensing/SBOM, exact ABI and source paths, tier policy and quality/perf budget, win/linux/macOS Apple Silicon hardware+driver and Web feature matrix, actual CI commands/harness, CORE-01/02 implemented/approved predecessor contracts, SHA-256 Context Lock, and owner-approved ADR/Scope/DoD/release class. This document alone **does not** unblock code.

See [technology matrix](../research/gfx-01-rhi-technology-matrix.md), [ADR-0014](../adr/0014-gfx-01-rhi-backends.md), [semantic API](../contracts/gfx-01-rhi-api.md), [future tests](../testing/gfx-01-acceptance-matrix.md).
