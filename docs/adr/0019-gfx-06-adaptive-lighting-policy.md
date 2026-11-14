# ADR-0019 — Portable Hybrid Lighting, Stable Shadows and Responsive GI

**Status:** PROPOSED / NOT APPROVED FOR ENGINE CODE  
**Date:** 2026-11-14 | **Research #138** | **WO:** NLE-P00-WO-002-GFX-06 | **Future code #34 BLOCKED**.

## Problem
The owner prioritizes cinematic light, reactive ARPG effects, premium shadows and efficiency better than Unreal/GGG where future comparable proof exists. Enforcing one hardware RT pipeline would exclude low-end, browser and some macOS paths. Incorrect cache invalidation may give glossy but temporally wrong lighting and severe shadow artifacts.

## Proposed decisions
1. GFX-06 owns light semantics, dynamic lighting and shadow/GI/reflection/volumetric policies only. GFX-01 backends, GFX-02 shaders, GFX-03 RenderGraph/VRAM/fences, GFX-04 casters/LOD, GFX-05 BRDF/alpha, GFX-07 output/tone map and DATA-02/04/05 IDs/scene/cook remain authoritative.
2. **Correct, portable baseline**: checked photometric units, bounded direct light, stable CSM/PCF and local shadow maps, IBL/probes/baked lighting fallback, per-device/scene error receipts, first-class 2D/2.5D. Never assume native GPU or HDR in headless.
3. **Optional capability-driven premium tiers**: clustered compute, PCSS/contact shadows, Virtual Shadow Map paged cache, DDGI/SDF/SSR/SSGI, Brixelizer GI for supported native backends and hardware RT shadows/reflections where valid; no simultaneous all-feature promise.
4. Explicitly separate **paged Virtual Shadow Maps** vs **Variance Shadow Maps**. Missing page/caster, cache pressure, deflector/light move, camera/LOD/origin/device changes => invalidation & coarse correct fallback; never corrupt alias or silently conceal animated occluder.
5. **Radiance Cascades** as research priority for 2D and screen-space ARPG GI based on GGG talks, with instant light-source response test. 3D/world-space scaling is optional EXPERIMENTAL with actual proof requirement and rights-respecting independent research; published code not assumed permissively licensed.
6. Preserve light freshness: camera cuts, new/missing emissive effects, skinned meshes, new occluders, material revision, device loss or invalid history reset denoising/cache confidence instead of persisting ghosts.
7. **Vendor gate:** AMD Brixelizer GI MIT candidate after source/tag/SBOM audit. NVIDIA RTXDI/RTXGI SDK governed by proprietary NVIDIA RTX terms, not MIT; no download/integration/copy without legal, architectural and owner authorization. Public ReSTIR paper is a reference only.
8. W3C WebGPU and WebGL2 degraded routes cannot assume Vulkan/DXR/Metal ray tracing equivalence. Explicit feature targets and test fixtures.
9. Scene light edit via safe Editor/CLI/MCP semantic commands with project scope, revision conflict detection, bounded authoring and durable DATA-04 journal. No arbitrary native GPU/driver/host filesystem/shader operation.
10. **SLRG optional hypothesis**: quality/confidence-aware budget distribution between direct/shadows/GI/fog. Not novel or superior until reproducible comparison; PROVE-OR-DROP.
11. **No implementation approval:** all 80 code WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS` and `executor_ready=false`, release class UNDECIDED. Future #34 requires approved 1.0 release scope, exact versions/licenses/files/ABI, implemented dependencies, named hardware and visual thresholds, SHA-256 Context Lock and objective audit.

## Rejected defaults
Clone Unreal or PoE2 shader/code/assets; mandatory RTX/RTXDI/RTXGI; unbounded light/shadow count; WebGPU hardware RT assumption; only-baked lighting for dynamic games; silent no-fallback SSR/SSGI; constant temporal reuse after scene change; blanket “better than X” benchmark claim.

## Evidence gates (NOT EXECUTED)
Photometry/color, light culling overflow, CSM stability, soft shadows/alpha, page exhaustion and stale history, CPU/GPU fenced resources, GI light leaking and offscreen misses, Radiance Cascades 2D/3D hypothesis, Windows/Linux/macOS/Web, 2D/2.5D/3D, low-end, security and licensing, real CPU/GPU/VRAM p50/p95/p99, same-scene competitor protocol, 0 known HIGH/CRITICAL before code.

See [architecture](../architecture/gfx-06-lighting-shadows.md), [tech matrix](../research/gfx-06-lighting-technology-matrix.md), [API](../contracts/gfx-06-lighting-api.md), [future tests](../testing/gfx-06-acceptance-matrix.md), [benchmark protocol](../research/gfx-06-competitive-benchmark-protocol.md).
