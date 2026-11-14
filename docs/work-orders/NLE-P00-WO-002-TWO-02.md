# Research Work Order — NLE-P00-WO-002-TWO-02

**Research issue #150 | Future implementation #38 OPEN/BLOCKED** | 2026-11-14  
**State:** RESEARCH IN PROGRESS, DOCS ONLY | **ADR-0023:** PROPOSED | **BASE main:** 11beaafb5122a29fdeb8a45aa01e4f90c1a6517a (TWO-01 research #147, PRs #148/#149 integrated).  
**Risk:** LOW docs; future ELEVATED persistence, malicious compressed source maps, collision cutover, GPU/physics consistency.

## OBJECTIVE
Prepare original first-class Tilemaps & 2D Worlds semantics with signed64 sparse world chunks, deterministic terrain/edit/save/reopen, bounded camera streaming, parallax and physics-authoritative collision correspondence, Windows/Linux/macOS/Web fallbacks and real future benchmarking. Zcode should code approved frozen contracts, not invent backend APIs/file formats.

## CONTEXT
P00 only. Owner approved 80 future implementation packets as planning inventory but all BLOCKED; no engine built. TWO-01 research is documented but mandatory TWO-01 and DATA-04 CODE are absent; research issue #150 distinct from future code issue #38. Full 2D/2.5D/3D/Web, AI native Editor/CLI/MCP, no public MVP, free public CI and solo objective audit remain directions.

## SCOPE
- Stable Map/Level/Layer/Tileset/TileId/Cell/Chunk schema, signed64 global cells and checked negative floor division, rebased local GPU view, sparse infinite/finite worlds, orthogonal baseline and conditional ISO/staggered/hex grids.
- DATA-04 source/journal/save/reopen/undo+redo and DATA-05 chunk cook/stream/prefetch/cancel/evict, GFX-03 fences and TWO-01 Canvas batching, data security, layer/parallax.
- Deterministic bounded Wang/4/8-neighbor autotile and dirty-neighbor repair, sprite/animation future TWO-03 reference, future collision shape metadata and PHYS revision acknowledgement before gameplay interaction.
- External Tiled TMX/JSON source and LDtk JSON integration research, distinct Tiled GPL editor versus BSD-2 libtiled and LDtk MIT, owned imported art rights, no arbitrary script/file fetch or decompression bombs.
- ADR-0023 PROPOSED, architecture, license matrix, typed API, **93 future NOT EXECUTED cases**, benchmark protocol and optional SWSP prove-or-drop, research WO/Evidence/3 additive index links. Research PR -> audit/squash -> separate checkpoint reconciliation PR on same WO.

## OUT OF SCOPE
No C++/shader/runtime, map asset or external tool installed, third-party games/art/GPL editor code copied, physics engine or pathfinding, network gameplay, animated tiles/timeline TWO-03 or hybrid TWO-04, expensive/premium dependencies, CodeRabbit, required external reviewer, bypass/force push, no 60FPS or world scale guarantee.

## FILES / SOURCES TO READ
Canonical hierarchy: docs/11-checkpoint.md > docs/10-decisions-ledger.md/approved ADRs > docs/03-scope.md > docs/09-definition-of-done.md > docs/04-architecture.md > docs/02-requirements.md. Then AGENTS.md, docs/product/module-catalog.md, docs/queue/implementation-registry.json, docs/queue/work-orders/TWO-02.md, TWO-01 API, DATA-02/03/04/05, GFX-03/05/07 and WORLD/PHYS interface research. Also public official Tiled/LDtk/Godot spec+license sources in the matrix and baseline Git/PR/issue. Exact future code paths TBD upon approval, not guessed.

## REQUIREMENTS
GOV-001..005; CAP-001/004/005/007/008/009/010/011/012/013/014/016; NFR-001..005 and NLE-D013..020 where relevant. Catalog: future editor map save/reopen and streamed tile/collision correspondence. Numeric thresholds, chunk cap, exact hardware, source formats and release class UNDECIDED.

## ARCHITECTURE RULES
DATA-04 owns durable source/journal, DATA-05 owns cooker/cache/async IO, DATA-03 owns hostile import, TWO-01 Canvas renders, GFX-03 GPU allocation/fences, PHYS owns collision contacts and acknowledgment, TWO-03 tile animation and TWO-04 hybrid depth later. No duplicate GPU resource/physical engine/asset store. Mathematically correct floor negative coordinates and visual readiness separate from physics-safe activation.

## CONSTRAINTS
Documentation-only LOW, no code/SDK/data tests claimed, CI at zero paid cost; all 80 code WOs remain BLOCKED and executor_ready=false; #38 open, ADR-0023 PROPOSED, no merge bypass.

## ACCEPTANCE CRITERIA
- [ ] 64-bit global chunks, negative floor and source/cooked schema, stable tile identity and layer/projection contracts.
- [ ] DATA-04 transaction/save/reopen, DATA-05 bounded streaming/cancellation/corrupt states and collision revision cutover with PHYS owner, WebGL2 CPU path, Canvas alpha/order and GFX-03 fences.
- [ ] Safe Tiled/LDtk import, TMX four top GID flags, hex rotation, LDtk external .ldtkl paths, licensing editor GPL vs libtiled BSD2 vs LDtk MIT, own art rights.
- [ ] 93 future NOT RUN cases, reproducible world benchmark and SWSP optional prove-or-drop; no false 60FPS or big-world measurement.
- [ ] 11 docs-only research files, final exact-HEAD docs-validation and objective pt-BR audit without HIGH/CRITICAL, normal squash merge/main readback.
- [ ] Separate same-WO checkpoint PR, only TWO-02 research_status changed, 80 future code packets still BLOCKED, #38 code open and ADR PROPOSED, TWO-03 next only when complete.

## TESTS
Only free GitHub Docs Validation on exact final HEAD for P00 docs. If checkout exists: python3 scripts/validate_docs.py, python3 scripts/validate_module_catalog.py, python3 scripts/validate_wo_registry.py; python3 scripts/select_wo.py TWO-02 expected refusal while code blocked. All 93 unit/integration/graphics/security/benchmark tests FUTURE NOT EXECUTED.

## DELIVERABLES
8 research docs (architecture, matrix, ADR, typed API, test matrix, benchmark plan, this Work Order, Evidence Bundle), 3 additive architecture/backlog/blocked packet links, issue #150, research PR/audit and separate same-WO checkpoint PR. No engine software.

## REVIEW FORMAT
Pt-BR objective audit: BASE/HEAD SHA, scoped file diff, exact GitHub CI and security checks, architecture/source license/DoD/evidence truth, residual risks, proposed Checkpoint Delta, verdict APPROVED / CORRECTION REQUIRED / BLOCKED.

## STOP CONDITION
Stale source or failed CI, improper license, unexpected code/asset, false benchmark or HIGH/CRITICAL defect blocks; fix same WO/PR only before merge, do not advance TWO-03. No force push, bypass, paid CI or mandatory reviewer.

## CONTEXT LOCK
BASE main 11beaafb5122a29fdeb8a45aa01e4f90c1a6517a; Git blob SHA is NOT raw file SHA-256. Runtime activation needs actual SHA-256, exact files/ABI, owner-approved DoD and integrated dependencies.
