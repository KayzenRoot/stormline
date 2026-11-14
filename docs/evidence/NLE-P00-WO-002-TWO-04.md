# Evidence Bundle — NLE-P00-WO-002-TWO-04 Hybrid Research

**Status:** DRAFT, RESEARCH PR/CI/AUDIT PENDING | Research issue #156 | Future coding issue #40 OPEN/BLOCKED.  
**BASE main:** 73f4826354724ce72a037411eba3dc86174638c3; research branch docs/NLE-P00-WO-002-TWO-04-hybrid-composition-research. No 2.5D engine, GPU compositing, real cutscene/art assets or benchmark produced.

## Context/Source Check
- Git canonical read: Checkpoint > Decisions Ledger/approved ADR > Scope > DoD > Architecture > Requirements > AGENTS, catalog, registry and blocked future packet TWO-04. TWO-03 research PR #154 and checkpoint PR #155 integrated. All 80 future code WOs BLOCKED/executor_ready=false, prerequisite TWO-01/GFX-04 C++ not implemented.
- Primary source research: Godot 4.6 CanvasItem Y/Z-sorting, SubViewport color render targets and HDR2D; Unity 6 custom 2D sorting of 3D with documented depth-post loss in Sort-as-2D mode, W3C WebGPU depth formats and usage restrictions, Khronos glTF 2.0 right-handed +Y-up meters, McGuire/Bavoil JCGT weighted blended OIT approximation. These are public specifications/reference behavior, NOT integrated software/source/asset rights. No external materials installed.
- Design: typed 3 composition modes (shared depth world vs ordered Canvas overlay vs subview), explicit ortho/perspective 2Dpx-to-3Dm bridge, masks/alpha/depth, GFX-03 resource graph, GFX-05/06 lit normals/shadows, GFX-07 HDR/temporal and native UI, subview depth-loss warning, WebGL2 CPU+Canvas fallback, versioned Editor/CLI/MCP transactions and SDOI optional prove-or-drop.

## Research PR source inventory and truthfulness
- Expected 11 docs-only research files: 8 new (architecture, technology/license matrix, ADR-0025, API, tests, benchmark, WO, EB) and 3 existing Architecture/Backlog/blocked #40 packet references. **NO checkpoint or implementation-registry change in initial research PR**.
- Research PR number, exact HEAD CI and security checks: **PENDING**.
- Objective pt-BR audit and merge SHA/readback: **PENDING**.
- All **109 future tests NOT EXECUTED**. No CPU/3D sprite math implementation, GPU screenshots, real HDR mode, native/Web device, full frame p95/p99, source license SBOM, shadows, physics or 60FPS data. No claim Stormline is better than existing engines.
- Risk LOW docs, future ELEVATED GPU buffer/alpha/depth precision/viewport life cycle and untrusted scene authoring. All release/ABI targets undecided, ADR-0025 PROPOSED.

## Proposed Checkpoint Delta, NOT APPLIED
Only after exact-head CI+objective audit APPROVED and research merge, open separate same-WO checkpoint PR changing ONLY TWO-04.research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED. Update checkpoint/backlog/research WO/evidence with verified receipts, preserve 80 future implementation statuses BLOCKED, 0 executor_ready, approved_adr=null, release class UNDECIDED, coding issue #40 OPEN. Require independent exact-final-HEAD CI and audit before closing #156 / starting WORLD-01 research.
