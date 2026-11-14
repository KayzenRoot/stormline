# ADR-0017 — GFX-04 Conservative Visibility, Scalable LOD and Verified Mesh Streaming

**Status:** PROPOSED / NOT APPROVED FOR ENGINE CODE  
**Date:** 2026-11-14 | **Research WO:** NLE-P00-WO-002-GFX-04 | **Issue:** #132 | **Future implementation:** #32 BLOCKED.

## Problem
Large and detailed Stormline worlds require efficient geometry draws, instancing, selection of detail and bounded streaming. Aggressive occlusion and meshlet logic can accidentally remove required objects, while fully virtualized geometry is a massive implementation and maintenance undertaking. Browser WebGPU and Apple Silicon do not universally provide native Vulkan mesh shaders, and foliage/animation/transparent geometry make simple cull rules unsound.

## Proposed policy
1. **Preserve authored geometry identity** via DATA-02 AssetId, imported source rights via DATA-03 and DATA-05 derived immutable target geometry cook/chunks. GFX-04 selects visibility and LOD and requests chunks, but does NOT introduce new authoritative asset store, scene serialization or patcher.
2. **Conservative visibility first:** CPU frustum/spatial bounds + discrete LOD as baseline for every target. Unknown displacement, stale occlusion, malformed bounds or camera discontinuity must **prefer visible** (or explicit typed missing-content), never silently cull visible objects.
3. **Feature-tier-driven GPU acceleration:** compute/indirect drawing, meshlet bounds and Hi-Z depth-pyramid occlusion only if GFX-01/GFX-02/GFX-03 capabilities, shaders and barriers validated; Vulkan VK_EXT_mesh_shader and D3D12 mesh shaders are OPTIONAL advanced paths. Metal and Web use actual supported features, never implicit Vulkan mesh/task parity.
4. **Instancing** uses stable instance IDs and transforms/camera precision, with material/visibility compatibility; grouping must not merge instances with distinct rights, animation, draw state, picking or interaction semantics.
5. **LOD/HLOD contracts** include measured screen-space error, hysteresis, authored UV/normal/material/animation preservation, neighborhood crack control, dynamic/interactive object exclusions and explicit coarse fallback. No fabricated pixel-perfect quality. Aggregate alpha vegetation requires special classification and overdraw benchmarks.
6. **Occlusion safety:** Hi-Z uses valid complete depth, correct reversed-Z and camera epoch, conservative coverage and temporal invalidation; transparent/alpha-cutout foliage cannot become trusted solid occluder by default. Debuggable visibility receipt for every object/cluster with reason.
7. **Streaming:** permanent/coarse fallback (or documented missing-content response) retained while higher LOD unavailable; DATA-05 owns verified immutable chunk IO/recovery, GFX-03 owns GPU upload/residency and completion fences. Source hash is not publisher authentication. Limit IO, RAM, VRAM and per-frame upload.
8. **Library evaluation:** meshoptimizer MIT is a strong offline candidate for simplification/meshlets/locality and compressed glTF, with tagged license/source SBOM and experimental API review. Ratified EXT_meshopt_compression and EXT_mesh_gpu_instancing are exchange specs, not runtime implementation. Investigate clusterlod.h as a candidate and check exact release; no unapproved copyright/proprietary Nanite code or assets.
9. **Editor/CLI/MCP semantic operations:** inspect geometry/instances, LOD and visibility, preview stream plan, validate quality/hysteresis; no raw draw buffers, native GPU pointer, unbounded classifier, imported local path leak, arbitrary shader/host command or cross-project data access via agent.
10. **SVCG visibility continuity optimization** is research PROVE-OR-DROP vs conservative CPU+LOD+Hi-Z reference, no mandatory ML, no automatic LOD/occlusion suppression, hard correctness gate before performance.
11. **No code authorization** from this ADR or docs merge; future #32 requires approved release Scope/DoD/class, exact source files/versions, GFX-03/DATA-05 implemented and accepted, actual hardware/browser tests, complete security/licensing and fresh SHA-256 Context Lock.

## Alternatives/trade-offs
- Clone Nanite immediately: proprietary/legal/engineering constraints; inappropriate as automatic NECESSARY or performance promise. Public concepts may inspire independent research, but never copy engine source/assets.
- Mesh shader only: excludes devices and browsers; rejects no-fallback mandatory path.
- Occlude every depth-overlapped or alpha-cutout object: high false negative/pop-in; reject.
- Aggressive simplify foliage/interactive/animated geometry with static bounds: violates authored fidelity and movement; reject absent separate validated envelopes and proxy.
- Render everything in large scenes: correct reference for occlusion tests but expensive, useful as an oracle for debugging.
- Fully automatic ML visibility: unnecessary complexity and unsafe correctness claims; SVCG optional only with prove-or-drop.
- Ignore missing streamed LOD: causes holes; mandatory explicit coarse fallback or typed failure.
- Let GFX-04 own VRAM allocator and bundle patcher: duplicates GFX-03/DATA-05 and causes inconsistent life cycles.

## Deliberately unresolved
Min GPU/OS/browser feature tiers and Apple Intel policy, meshoptimizer exact tag/experimental API, `clusterlod.h` pin/licensing, source geometry formats/precision, proxy quality thresholds, screen-space error formula details, HLOD update/migration, foliage/occlusion classification, CPU vs GPU split, Web GPU compute and safe indirect caps, VRAM/IO budget numbers, release class and benchmark fixtures.

## Required future evidence before activating #32
- Deterministic offline simplification/cluster build with originals and rights-cleared fixtures; geometry ABI/provenance/decoder bounds, UV/normal/skin and displacement fidelity, cracks and silhouettes.
- CPU reference versus GPU culling oracle scenes with 0 false negatives under camera jumps/teleport/origin rebase/reversed-Z, animated/transparent vegetation and cyclic/invalid HLOD hierarchy.
- Real Windows Vulkan/D3D12, Linux Vulkan, macOS Apple Silicon Metal, WebGPU browser and WebGL2 reduced, optional mesh/task shader feature query and complete native fallback proof.
- Stream/patch failure, missing chunk, last-good LOD, DATA-05 auth vs integrity, bounded RAM/IO/VRAM/upload, device loss and GFX-03 fences; shader material reflection seams.
- Actual p50/p95/p99 CPU/GPU timings, draw/triangle/bandwidth/VRAM, visible error, frame-time spikes and streaming quality using named devices/driver/CI, plus SVCG baseline comparison.
- License/tag/SBOM plus proprietary content rights, secure MCP quotas and diagnostics, no unapproved paid runtime. Approved Scope/DoD/release class/ADR, dependencies **code** integrated, Context Lock SHA-256. Never equate documentary CI with a functional engine.

See [architecture](../architecture/gfx-04-geometry-visibility-lod.md), [matrix](../research/gfx-04-geometry-technology-matrix.md), [contract](../contracts/gfx-04-geometry-api.md), [future tests](../testing/gfx-04-acceptance-matrix.md).
