# Evidence Bundle — NLE-P00-WO-002-GFX-04

**Date:** 2026-11-14 | **Research issue:** #132 | **Future code issue:** #32 BLOCKED  
**State:** RESEARCH DOCS UNDER FINAL AUDIT. No C++ geometry, meshoptimizer runtime, GPU visibility, shader, HLOD tool, benchmark or deployment.
**BASE main:** `563f5dff168a688f5d03d959685024dd374de4c9`; **research branch:** `docs/NLE-P00-WO-002-GFX-04-geometry-research`. LOW doc risk; future ELEVATED incorrect visibility, GPU memory, geometry content rights and streaming.

## Canonical Context Lock: live GitHub blob fingerprints
These are **Git object blob hashes, NOT SHA-256 file content hashes**. Before actual source implementation, calculate fresh SHA-256 and rebase if any critical approved source changed:
- `docs/11-checkpoint.md`: `46e799f886282f477c4e6fa62e30a378b433260d`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `15fbb0163e0da4936270aba1a97458bf5ef60dbd`
- `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/queue/work-orders/GFX-04.md`: `05404642ba908e053c52203dce8293b4bfdb96db`
- `docs/queue/implementation-registry.json`: `7cad24c62be63f226dce3b5a458122fe0f575da3`
- `docs/architecture/gfx-03-render-graph-gpu-memory.md`: `64995e61950a257cda7309e4c1341a82f498ed19`
- `docs/architecture/data-05-cooking-streaming-bundles.md`: `0e77be93e7d0fa2404acd297b98c1ef4545cb948`
- `AGENTS.md`: `3e57b719f8651407879ebb641707a048773ea4c2`

## Documentation authored (not implemented)
- Proposed Conservative CPU frustum/spatial LOD baseline with optional Hi-Z/compute/indirect/Vulkan/D3D mesh shader advanced paths and Web/macOS degraded options; no false-negative visibility and unknown bound => visible.
- Mesh/HLOD/instance typed contracts, source AssetId+authored rights preserved, screen-space error/hysteresis, animated material/double-sided/alpha foliage and silhouette seam checks.
- DATA-05 verified immutable chunk streaming and resident coarse proxy; GFX-03 owns VRAM/fence, GFX-01/02 own GPU/shaders; no parallel packer, allocator or GPU memory store.
- meshoptimizer C/C++ MIT candidate with exact tag and experimental feature gates, glTF EXT meshopt compression and GPU instancing ratified, gltfpack tool caveats; Nanite comparison without copyrighted engine content copying. ADR-0017 PROPOSED.
- 36 future GEO-001..036 scenarios including real hardware platform, low-end, WebGPU/WebGL2, high-geometry CPU/GPU/VRAM/IO/popping reference, streaming error, meshlet fuzz, source rights and MCP semantic permissions.
- SVCG optional prove-or-drop with hard correctness before perf, no innovation performance claims.

## Observed checks / evidence (populate with exact GitHub results only)
- First research HEAD `8565e7bb7506dbf5ff2643eea8f2b8ff0875fa0d` passed [Docs Validation #43614101059](https://github.com/KayzenRoot/stormline/actions/runs/43614101059) **SUCCESS** (Source Pack links, catalog 80 modules/DAG, registry, blocked selector); after this evidence update exact new HEAD CI required.
- [Research PR #133](https://github.com/KayzenRoot/stormline/pull/133) initial scope audit: 10 documentation files under `docs/`, +399 / 0 deleted; no C++/SDK/compiled mesh, GPU test, workflow change or apparent secret. Registry readback shows 80/80 BLOCKED and zero executor_ready; implementation issue #32 remains PLANNING/BLOCKED. Final pt-BR audit and exact HEAD: PENDING.
- Native/real GEO-001..036, shader build, C++ compiler, meshoptimizer codec, GPU culling, Windows/Linux/macOS/Web browser, fuzz, benchmark frame-time p95/p99 and VRAM: **NOT RUN**.
- Research squash merge readback, separate same-WO checkpoint PR: PENDING.

## Risks/unfinished selection gates
No library/toolchain pinned or installed. Any third-party modeled scenes/copyrighted Epic assets prohibited unless authorized rights. UI/editor commands are semantic only; unbounded GPU count, private scene/asset data and GPU driver internals remain an ELEVATED boundary for future code. Both GFX-03 and DATA-05 **code** dependencies not integrated. All 80 implementation tickets BLOCKED and none executor_ready.

## Proposed Checkpoint Delta (not yet audited or merged)
After research PR docs CI success, objective audit and normal squash merge with readback, promote only GFX-04.research_status=RESEARCH_DOCUMENTED_ADR_PROPOSED via separate audited docs-only PR. ADR-0017 stays PROPOSED; future #32 and all 80 work orders remain BLOCKED/executor_ready=false. Then next eligible GFX-05 research.
