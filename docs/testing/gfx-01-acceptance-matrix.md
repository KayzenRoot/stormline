# GFX-01 — RHI Device, Resource and Backend Future Acceptance Matrix

**WO:** NLE-P00-WO-002-GFX-01 | **Issue:** #123 | **Current status:** SPECIFIED TESTS, **NONE EXECUTED**.
Risk LOW research docs; future ELEVATED GPU crash/device reset, native driver integrity, concurrency, shader source and memory lifetime.

| Test | Risk | Future exercise | Objective proof |
|---|---|---|---|
| RHI-001 | STANDARD | Windows x64 Vulkan adapter enumerate/device init/shutdown | real adapter/driver/SDK, success/failure logs, no invalid handles |
| RHI-002 | STANDARD | Windows x64 D3D12 alternate/fallback | declared tier/feature parity and error on unsupported backend |
| RHI-003 | STANDARD | Linux x64 Vulkan on Mesa and vendor GPUs | Wayland/X11 surface, formats, driver-info and clean shutdown |
| RHI-004 | STANDARD | Apple Silicon macOS native Metal | device init/surface/offscreen, verified Apple hardware not inferred from runner |
| RHI-005 | ELEVATED | Intel macOS Metal and MoltenVK feasibility; KosmicKrisp Apple Silicon optional | capability/feature, license and deprecation trade-off, unsupported path explicit |
| RHI-006 | STANDARD | browser WebGPU + HTTPS secure context | typed feature detection and browser support limits, no assumption Baseline |
| RHI-007 | STANDARD | unsupported browser WebGPU / WebGL2 fallback | explicit reduced quality capability, no silent engine parity |
| RHI-008 | STANDARD | native headless server NO_DEVICE mode | validate descriptors/requests without claiming GPU pixel output |
| RHI-009 | STANDARD | GPU offscreen native test with real adapter | pixel readback and reference orientation/color tolerance |
| RHI-010 | ELEVATED | create/release buffers/textures repeatedly with generation handles | no stale deref/leak, mapped ownership and deferred resource retire |
| RHI-011 | ELEVATED | free in-flight buffer before fence | correct deferred destruction or typed denial, no GPU UAF |
| RHI-012 | ELEVATED | device loss during upload/submit and reinit | old handles invalid; declared restart-required or verified new-generation recovery |
| RHI-013 | ELEVATED | repeated device loss, GPU reset, adapter hotplug | no infinite retry, deadlock, resource resurrection or stale cache |
| RHI-014 | STANDARD | surface resize/occluded/minimized/refresh/HDR unsupported | swapchain versioning/recreate, safe present and typed fallback |
| RHI-015 | ELEVATED | queue family ownership, compute/graphics/transfer submission | validation layers show no missing barrier/race and explicit unsupported feature |
| RHI-016 | ELEVATED | concurrent CPU resource creation/shutdown/callback race | threading contract, sanitizer logs where supported, reproducible results |
| RHI-017 | ELEVATED | invalid buffer length/alignment, texture dimension overflow | checked reject before driver/alloc, bounded error without OOM |
| RHI-018 | STANDARD | CORE-05 RH Y-up to Vulkan/Metal/D3D/SDL GPU clip | golden triangle/frontface/viewport/depth/readback, no inverted cull/UV |
| RHI-019 | STANDARD | 2D sprite transparency/sRGB/linear, layered 2.5D and basic 3D depth | golden images under native backends with per-driver tolerance |
| RHI-020 | STANDARD | disabled optional compute/ray tracing/bindless tier | fallback or explicit unsupported with no silent feature claim |
| RHI-021 | ELEVATED | shader/pipeline malformed/binary version mismatch from GFX-02 | error boundary protects GPU, scoped compile authority and safe diagnostics |
| RHI-022 | ELEVATED | memory pressure and large texture upload while rendering | bounded CPU/GPU alloc, VRAM monitoring, no uncontrolled stutter/oom |
| RHI-023 | STANDARD | p50/p95/p99 submit/encode/present, GPU timing/VRAM, low-end hardware | exact CPU/GPU/driver/OS/SDK/scenes and sample counts, unavailable timing flagged |
| RHI-024 | STANDARD | SDL_GPU vs native RHI vs Dawn/wgpu/bgfx A/B | same workloads/features, real pass/fail/license/build/latency vs complexity |
| RHI-025 | ELEVATED | MCP caller attempts native pointer, arbitrary shader/driver command | capability denial and no GPU side effects or disclosure |
| RHI-026 | ELEVATED | device-identifying telemetry/crash capture, error redaction | privacy defaults OFF, no secret/host path leakage |
| RHI-027 | STANDARD | license/SBOM exact tags for SDL3, Vulkan, Apple, Dawn/wgpu, bgfx | explicit shipped file license, transitive notices and OS SDK terms |
| RHI-028 | STANDARD | SCGF recovery/capability planner A/B | prove improvement vs standard feature query/generation handles or drop |

## Execution plan when code later authorized
1. Pin actual feature tiers, target minimum versions and compiler/SDK tags; all tests report input SHA/driver/runner and capability snapshot.
2. Stub/mock backend correctness tests for handle ownership, generation invalidation, memory/fence contracts, error taxonomy and descriptor validation. This does not prove real driver behavior.
3. Native platform smoke on actual Windows/Linux/macOS Apple Silicon: device, offscreen and native presentation; optional Mac Intel matrix to be decided, Web browser separate and HTTPS required.
4. Validate graphics and synchronization against native APIs/tools (Vulkan validation layers, D3D12 debug layer, Xcode Metal capture, RenderDoc where supported), with flagged unavailable tests.
5. Golden image fixtures original and rights-cleared, compare tolerance envelopes for color-space, depth, alpha and orientation. No exact cross-GPU bitwise pixel claim.
6. Device lost/driver reset injection and window resize, hotplug, multiple windows and abrupt shutdown; distinguish recoverable from restart-required, never leave stale resource valid.
7. Benchmarks p50/p95/p99 CPU and GPU (if supported), frame-time variance, peak VRAM/RSS, startup init, adapter selection cost, submit count, throughput and energy if measurable, modest GPUs. No ungrounded FPS estimate.
8. Security: native GPU/OS boundaries, fuzz descriptors, invalid bindings, shader validation (GFX-02), extension enumeration, redaction and MCP authorization.
9. License/SBOM and provenance: exact shipped compiled files, no unsupported/paid SDK artifact, vendor notice compliance, pin format versions and disclosed feature support.
10. Public free GitHub docs CI currently checks documents only; no native CI, C++ build, sanitizer/fuzzer, real GPU driver or hardware-run report has been executed in this research.

**RHI-001..028 ALL NOT EXECUTED.** Evidence requirements are future obligations, not existing feature delivery.
