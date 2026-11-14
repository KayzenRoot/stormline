# ADR-0021 — Typed, Bounded Hybrid CPU/GPU VFX and Particle Graph

**Status:** PROPOSED / NOT APPROVED FOR ENGINE CODE  
**Date:** 2026-11-14 | **WO NLE-P00-WO-002-GFX-08** | **Research #144** | **Future implementation #36 BLOCKED**.

## Context
Owner wants AAA-grade ARPG VFX, cinematic explosions and many simultaneous magical effects with innovative visual performance across Windows/Linux/macOS/Web and genuine 2D/2.5D. Always-on high-count GPU effects can exhaust VRAM/overdraw, break WebGL2 or imply unsafe GPU simulation as gameplay authority. Reusing unlicensed code/assets is not an option.

## Proposed decisions
1. **Engine-owned typed effect asset graph with bounded DAG** and project-scoped DATA-02 AssetId/revision; DATA-03 import, DATA-04 durable authoring, DATA-05 cook, GFX-02 compiler, GFX-03 GPU resource graph are authoritative. No duplicate shader compiler/VRAM manager/asset DB and no arbitrary user shader injection.
2. **CPU bounded reference + optional GPU compute SoA runtime** chosen by verified device capability and real GPU/CPU p50/p95/p99 costs; 2D/2.5D and WebGL2 always have a conservative CPU simulation + sprite/ribbon fallback. Hybrid GPU effects are never gameplay-authoritative.
3. All spawn/lifetime/graph subemit/field/update/draw/sort costs have explicit finite caps, recursion/dependency validation, checked integer sizes, cancellation and fence-safe pool reuse. Unknown events must not form unbounded graph feedback or arbitrary code.
4. **Visual types** sprite/flipbook, mesh, ribbon, trail, sparks, decal-linked effects, volumetric density stamps and optional fog/cloud-like structures. GFX-06 **owns** actual dynamic light/volumetric scattering and sets light budgets; GFX-05 PBR/alpha/texture, GFX-07 HDR/reactive/AA.
5. **Transparency correctness**: conventional CPU/optional GPU sort; GPUOpen AMD Parallel Sort MIT DX12/Vulkan candidate but not universal. Weighted OIT is approximate, alpha, refraction/depth and overdraw have explicit supported/unsupported material matrix. No universal correct OIT claim.
6. Strict **VFX budget and degradation receipts** for effect salience, distance/area, overdraw, CPU/GPU compute, VRAM, trail complexity and GFX-06 lights. Preserve gameplay telegraph visibility without changing gameplay rules; low-end emits fewer cosmetic sparks rather than removing important indicators.
7. **Effekseer** optional import/interop study, MIT runtime but separate DirectX/Vulkan/tool dependencies and content rights verified. **OpenVDB** Apache-2.0 candidate for offline sparse volume cooking only until actual codec/shader/per-platform proof. Unreal Niagara/Godot references, not copied code or assets.
8. GFX-03 fence-safe RenderGraph, device generation and streaming cancellation; GFX-07 reactive history masks and UI, reduced-motion and flash sensitivity. Never keep stale GPU buffers through driver/device loss.
9. **SVAG** optional salience/budget work governor PROVE-OR-DROP against fixed quality tiers and simple distance/area LOD. Never claim novelty or measured win without prior art and reproducible benchmark evidence.
10. Same Editor/CLI/MCP allowlisted `Stage -> Validate -> Commit` semantic graph commands with revision CAS, scoped permissions/quotas, DATA-04 journal and rollback, redacted/provenance budget receipts. No unapproved binary/plugin install, OS commands, arbitrary shader/URL/fs or private art scraping.
11. **No execution authorization.** All 80 implementation WOs remain `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`; #36 stays open, release-class UNDECIDED. Before coding need owner-approved 1.0 Scope/DoD and exact artifacts/ABI/versions/license/SBOM, implemented+audited GFX-03/05 dependencies, GFX-06/07 integration, hardware targets and budget oracles, SHA-256 Context Lock and objective audit.

## Considered alternatives (rejected as mandatory)
- GPU-only runtime, every particle generates a light, arbitrary shader code stored in graph, unbounded fluid simulation for all, universal NanoVDB, port proprietary Niagara shaders, assume Effekseer tool/backend licenses all MIT, sorting for all additive effects, trust GPU visual collisions for player hits, render 4K transparency without overdraw limits.

## Future evidence, NOT EXECUTED
Golden graph/CPU simulation/PRNG, corrupted and recursive graphs, CPU/GPU visual tolerance and particle replays, 2D/2.5D/3D portability, native Win/Linux/macOS & WebGPU/WebGL2, alpha/trail/volumetric/HDR ghost, GPU device loss/pool caps, fuzz imports and license receipts, per-effect and scene p50/p95/p99 CPU/GPU/VRAM vs independent Unreal/GGG-style ARPG fixture. See [architecture](../architecture/gfx-08-vfx-particle-graph.md), [technology matrix](../research/gfx-08-vfx-technology-license-matrix.md), [API](../contracts/gfx-08-vfx-api.md), [tests](../testing/gfx-08-acceptance-matrix.md), [benchmark](../research/gfx-08-vfx-performance-benchmark-protocol.md).
