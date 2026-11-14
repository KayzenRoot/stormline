# ADR-0014 — GFX-01 Portable RHI and Capability-Driven Backends

**Status:** PROPOSED / NOT APPROVED FOR IMPLEMENTATION  
**Date:** 2026-11-14 | **Research WO:** NLE-P00-WO-002-GFX-01 | **Issue:** #123 | **Code issue:** #29 BLOCKED

## Problem
Stormline targets 2D/2.5D/3D high-quality graphics plus Web and native Windows/Linux/macOS. A GPU hardware abstraction must deliver correct resource lifetime, robust device loss, API-neutral capabilities, stable shader/asset boundaries and good frame-time scaling without handcuffing future graphics innovation to lowest-common-denominator or committing to three heavy backends before evidence.

## Proposed policy
1. Define a **Stormline-owned, narrow, versioned C++20 RHI contract**, independent from public Vulkan/Metal/D3D12/SDL GPU vendor types and carrying explicit GPU feature/capability descriptors. This is a design contract, **not** approval to code three native backends.
2. Research **Vulkan** on Windows/Linux, **Metal native** on macOS, **D3D12** as a Windows candidate/fallback, with SDL3 GPU and bgfx as comparison baselines. No final stack winner without A/B tests.
3. Record modern Vulkan-on-Metal transition: Khronos states MoltenVK deprecated/community-maintained; recommends KosmicKrisp on Apple Silicon, MoltenVK on Intel Mac. Evaluate translation only as conditional adapter, not the macOS prerequisite.
4. Study Dawn/wgpu-native as optional native WebGPU C-compatible backends and browser WebGPU separately. No assumption WebGPU is universally available or offers native Vulkan feature parity; WebGL2 is explicit degraded candidate under PLAT-03.
5. Capability query returns individual supported features/numeric limits plus derived tiers; never infer from OS/GPU marketing name. Missing required feature fails clearly; optional advanced path may be disabled with measured fallback.
6. Require opaque resource handles with device-generation and ownership; enforce checked buffer/texture descriptors, correct queue/fence/hazard contracts, retirement and staged upload; no stale handle reuse across device loss.
7. Device loss may be recoverable through explicit re-probe and generation rehydration **or** fail with restart-required. Don't promise universal recovery, especially after driver reset or GPU removal.
8. CORE-05 owns world-coordinate convention; GFX-01 normalizes API clip-space/depth/winding/texture origin as an explicit tested transform. SDL GPU documented NDC conventions do not silently change the world coordinate policy.
9. GFX-02 owns shader/pipeline compilation variants, GFX-03 owns render graph/resource budget and hazard planning; GFX-01 exposes primitive submission and capability only. No huge multi-feature renderer inside RHI.
10. Editor/CLI/MCP can inspect adapters/capabilities, invoke scoped diagnostic preview, never native driver commands, arbitrary shader code, compiler flags or exposed GPU pointer. Redacted telemetry opt-in only.
11. SCGF capability-aware recovery receipts are **prove-or-drop** against simple generation handles/query and rehydrate baseline, not a required proprietary subsystem.

## Alternatives and trade-offs
- Vulkan-only including all macOS machines: conditional translation maintenance/portability gaps; reject as unproven default.
- SDL_GPU for all future AAA features: excellent base parity candidate, yet documented feature ceiling; compare against target tiers.
- Immediately write all native backends: maintenance and testing explosion, unjustified until selected mandatory feature set and hardware matrix.
- Adopt bgfx wholesale: potentially simpler but may overlap GFX-02/03 and constrain native extension control; only if A/B justifies.
- WebGPU native/browser identical contract: browser and runtime features/availability differ; explicit tier negotiation.
- Silent GPU fallback or lost-resource reuse: reject data corruption and wrong results.
- Expose raw native GPU API to AI tools: reject privileged execution boundary.

## Deliberately unresolved
Engine source license, pinned API/SDK tags, native and Web target minimum versions, Intel macOS 1.0 support, device-lost recovery guarantees, feature tier 1.0 class, exact shader dialect/compiler, GPU memory budgets/VRAM allocator (GFX-03), backend source files/CI/hardware and test tolerance thresholds.

## Future proof obligations
Exact Vulkan/Metal/D3D12/SDL GPU/Dawn/wgpu/backends licenses and SBOM, feature conformance, weak GPU target profiling, Windows/Linux/macOS Apple Silicon native smoke, optional Intel and WebGPU/WebGL2 browser, golden 2D/2.5D/3D pixels and NDC transforms, resource lifetime/driver lost/resize/fence/multithreading tests, sanitizer/validation and GPU counters, genuine p50/p95/p99 CPU/GPU latency. Approved Scope/DoD/release class, predecessor implementation CORE-01/02 merged and fresh SHA-256 Context Lock before issue #29 is unlocked.

Research ADR status does not change all 80 code WOs, including #29: **BLOCKED**.

References: [architecture](../architecture/gfx-01-graphics-rhi.md), [matrix](../research/gfx-01-rhi-technology-matrix.md), [contracts](../contracts/gfx-01-rhi-api.md), [future tests](../testing/gfx-01-acceptance-matrix.md).
