# Evidence Bundle — NLE-P00-WO-002-TWO-04 Hybrid Research

**Status:** RESEARCH PR OPEN; INITIAL EXACT-HEAD CI SUCCESS, FINAL HEAD REVALIDATION/AUDIT PENDING | Research issue #156 | Future coding issue #40 OPEN/BLOCKED.  
**BASE main:** 73f4826354724ce72a037411eba3dc86174638c3; research branch docs/NLE-P00-WO-002-TWO-04-hybrid-composition-research. No 2.5D engine, GPU compositing, real cutscene/art assets or benchmark produced.

## Context/Source Check
- Git canonical read: Checkpoint > Decisions Ledger/approved ADR > Scope > DoD > Architecture > Requirements > AGENTS, catalog, registry and blocked future packet TWO-04. TWO-03 research PR #154 and checkpoint PR #155 integrated. All 80 future code WOs BLOCKED/executor_ready=false, prerequisite TWO-01/GFX-04 C++ not implemented.
- Primary source research: Godot 4.6 CanvasItem Y/Z-sorting, SubViewport color render targets and HDR2D; Unity 6 custom 2D sorting of 3D with documented depth-post loss in Sort-as-2D mode, W3C WebGPU depth formats and usage restrictions, Khronos glTF 2.0 right-handed +Y-up meters, McGuire/Bavoil JCGT weighted blended OIT approximation. These are public specifications/reference behavior, NOT integrated software/source/asset rights. No external materials installed.
- Design: typed 3 composition modes (shared depth world vs ordered Canvas overlay vs subview), explicit ortho/perspective 2Dpx-to-3Dm bridge, masks/alpha/depth, GFX-03 resource graph, GFX-05/06 lit normals/shadows, GFX-07 HDR/temporal and native UI, subview depth-loss warning, WebGL2 CPU+Canvas fallback, versioned Editor/CLI/MCP transactions and SDOI optional prove-or-drop.

## Canonical source Git object fingerprints at BASE (Git SHA-1 OIDs, NOT raw file SHA-256)
- `docs/11-checkpoint.md`: `3001e09027d9f8e4db833aa37393948c39424d69`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `45e7e0b98a97996685668905b6634cea97344528`
- `docs/queue/work-orders/TWO-04.md`: `b3b51196f3f9b1d274a8e1d902213684d434cc0c`
These are Git object fingerprints observed before research changes, not SHA-256 of raw file bytes. Before any future code, actual byte-level SHA-256 and fresh approved Context Lock are required.

## Research PR source inventory and truthfulness
- Expected 11 docs-only research files: 8 new (architecture, technology/license matrix, ADR-0025, API, tests, benchmark, WO, EB) and 3 existing Architecture/Backlog/blocked #40 packet references. **NO checkpoint or implementation-registry change in initial research PR**.
- [Research PR #157](https://github.com/KayzenRoot/stormline/pull/157): initial HEAD `be5b5dfd67ad31a5584f4adaf43a807187d3f1f2`, [Docs Validation run #43633144894](https://github.com/KayzenRoot/stormline/actions/runs/43633144894) **SUCCESS on initial exact HEAD**; initial Socket Security Project Report SUCCESS. This Evidence edit changes HEAD and requires a NEW final-exact-HEAD CI before objective audit and merge.
- Objective pt-BR audit and merge SHA/readback: **PENDING**.
- All **109 future tests NOT EXECUTED**. No CPU/3D sprite math implementation, GPU screenshots, real HDR mode, native/Web device, full frame p95/p99, source license SBOM, shadows, physics or 60FPS data. No claim Stormline is better than existing engines.
- Risk LOW docs, future ELEVATED GPU buffer/alpha/depth precision/viewport life cycle and untrusted scene authoring. All release/ABI targets undecided, ADR-0025 PROPOSED.

## Proposed Checkpoint Delta, NOT APPLIED
Only after exact-head CI+objective audit APPROVED and research merge, open separate same-WO checkpoint PR changing ONLY TWO-04.research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED. Update checkpoint/backlog/research WO/evidence with verified receipts, preserve 80 future implementation statuses BLOCKED, 0 executor_ready, approved_adr=null, release class UNDECIDED, coding issue #40 OPEN. Require independent exact-final-HEAD CI and audit before closing #156 / starting WORLD-01 research.
