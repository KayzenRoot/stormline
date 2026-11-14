# Research Work Order — NLE-P00-WO-002-WORLD-02

**Date 2026-11-14 | Research #162 | Future code issue #42 OPEN/BLOCKED**  
**Status:** APPROVED / MERGED FOR RESEARCH DOCS ONLY (PR #163) | **ADR-0027:** PROPOSED | **Context Lock BASE main:** 1871b4adc99eb82e79890af5e7a423d8db202daa (WORLD-01 research PR #160 + checkpoint PR #161 merged).
**Risk:** LOW docs, future ELEVATED persistent prefab source, schema migration, cross-project refs, rollback/synchronization, massive graph expansion.

## OBJECTIVE
Prepare a source-authoritative Scene & Prefab Hierarchy with stable node/asset/instance IDs, rooted instance trees and bounded prefab dependency DAGs, safe transforms, versioned nested variants, sparse field/structural overrides and deterministic **three-way base/ours/theirs** rebase. Reusable asset edits should propagate automatically only to unoverridden instance fields and safely conflict without loss; DATA-04 must own real undo/redo/commit/recovery. Zcode gets exact stable approved contracts once coding gates are met, not architecture choices.

## CONTEXT
Stormline P00 documentation-only, editor+headless, Windows/Linux/macOS/Web, 2D/2.5D/3D; AI-native Editor/CLI/MCP and no mandatory external paid tools/reviewers. Canonical registry at BASE: **23/80 research documented, 57 pending**, old CORE-04 research gap, **80 implementation WOs BLOCKED/executor_ready=false**, zero executable engine. WORLD-01 is researched but coding #41 and DATA-02 code are not integrated. WORLD-02 code issue #42 is a separate future work order, not authorized by this research.

## SCOPE
- Scene source node stable GUID/EntityGuid/InstanceId namespaces, authored parent forest/sibling order, separate prefab+variant nested dependency DAG with cycle/depth/fanout constraints and typed external ref readiness.
- CORE-05 affine transforms, KEEP_LOCAL vs KEEP_WORLD explicit representability with mirroring/shear/singular parents, large world origin and source vs runtime authority.
- Original prefab reusable base/variant/nested/link+override representation, stable field-level component schema keys, structural add/remove/reorder/tombstone and lossless 3-way base/ours/theirs merge with conflict receipts and controlled propagation.
- DATA-02 asset identity and rights, DATA-04 journal/undo/redo/save/reopen/CAS, DATA-05 cook/stream, WORLD-01 ECS deferred generation mapping, WORLD-03 spatial/stream, GFX/TWO/PHYS/NET owners separated. Source commit and runtime publish phases explicitly reconciled, not fictitiously atomic.
- Official reference research Godot PackedScene MIT, Unity 6 proprietary nested prefab/variant/override reference, OpenUSD composition with **Tomorrow Open Source Technology License 1.0** (NOT plain Apache-2.0) and transitive rights, O3DE core Apache-2.0 OR MIT with independent third party terms; no imported code/asset.
- Semantic Editor/CLI/MCP allowlisted authoring, static preview/permissions/quota and error receipts, **122 future NOT EXECUTED acceptance scenarios**, reproducible p95/p99 and SIOP optional PROVE-OR-DROP; architecture/matrix/ADR-0027/API/tests/benchmark/WO/Evidence + 3 additive existing docs.
- Research PR 11 docs only with exact-final-HEAD CI/audit/normal squash/main readback; independent **separate same-WO** checkpoint PR with only WORLD-02 research_status delta, checks/audit/merge/readback and research issue closure.

## OUT OF SCOPE
No C++/SDK/editor/asset import, actual scene instantiation, persistent file writer, prefab propagation, test harness, benchmark, real undo/redo, ABI, PHYS/GFX or WORLD-03 spatial engine. No forced cross-world network authority, mandatory USD/Godot/Unity/O3DE runtime, copied proprietary art/code, broad refactor, CORE-04 undocumented gap closure, paid CI/CodeRabbit/external reviewer requirement, force push/bypass, no WORLD-03 research before approved reconciled checkpoint.

## FILES / SOURCES TO READ
Source hierarchy `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md`, then AGENTS.md, docs/product/module-catalog.md, docs/queue/implementation-registry.json, docs/queue/work-orders/WORLD-02.md, WORLD-01 Entity API/ADR, DATA-02/03/04/05, CORE-05 transforms, TWO-01..04 and PHYS/NET interface ownership, public official upstream references in matrix. Inspect main tree/rules/issue before any writing. Exact future C++ files TBD and must be audited when implementation approved.

## REQUIREMENTS
GOV-001..005, CAP-004/008/009/010/011/012/013/014/016 and NFR-001..005, NLE-D013..020 where applicable. Future catalog acceptance: **prefab source edits propagate with undo/redo**; only proven by real runtime+DATA-04 tests, not documentation. Numerical scene fanout size, p95/p99 CPU/VRAM, native/Web target/ABI and 1.0 release class currently UNDECIDED.

## ARCHITECTURE RULES
WORLD-01 handles ECS EntityGuid/generational runtime Handle/components, WORLD-02 only source scene hierarchy/prefab composition and transform relation; CORE-05 owns math, DATA-02 source/asset IDs, DATA-04 canonical persistence and journal, DATA-05 cooker/cache, WORLD-03 streaming/spatial, GFX/TWO graphics, PHYS/NET gameplay. No second ECS/asset DB/writer/renderer. Structurally cycle-free and bounded, rights checked, no remote/scripts, no silently dropped overrides.

## CONSTRAINTS
Only docs now; all 80 code packets remain BLOCKED and zero executor-ready, ADR-0027 PROPOSED, coding #42 OPEN/BLOCKED. Predecessor WORLD-01 and DATA-02 code not built; historical CORE-04 research pending. No shipped compiler/SDK or numeric performance proof. Solo free GitHub Actions docs-validation and objective pt-BR review.

## ACCEPTANCE CRITERIA
- [ ] Source scene forest versus prefab dependency DAG, stable Node/Instance/Asset ID and ECS EntityGuid mapping, no cycles/stale names/cross-world leaks.
- [ ] Ortho/3D checked KEEP_LOCAL/KEEP_WORLD affine reparent and correct negative scale/shear/singular errors, no PHYS server unauthorized writes.
- [ ] Nested/variant precedence, stable field/structural override, three-way merge conflict and controlled base propagation without silent local data loss, author-authorized break-link, undo/redo after revisions/crash.
- [ ] DATA-04 source CAS/journal and separate WORLD-01 published runtime consistency, DATA-02/03/05 rights/import/cache owner boundaries, Editor/CLI/MCP permissions and quotas.
- [ ] Licensing exact OpenUSD TOST 1.0 vs Apache and transitive bundle, O3DE dual licensing/third-party, Godot MIT reference, Unity proprietary; no vendor code/assets installed.
- [ ] 122 tests explicitly FUTURE NOT EXECUTED and clean-room benchmark, SIOP prove-or-drop with correct full-rebuild oracle, no invented prefab perf/scale.
- [ ] 11 docs-only research files, exact final HEAD CI success and pt-BR audit no known HIGH/CRITICAL, normal squash/readback; separate same-WO checkpoint PR with only WORLD-02.research_status delta, all 80 coding WOs remain BLOCKED, #42 OPEN, ADR PROPOSED; next WORLD-03 only after checkpoint.

## TESTS
Only `docs-validation` in free GitHub Actions on exact final HEAD, plus Socket/SonarCloud when present. Local if checkout possible: `python3 scripts/validate_docs.py`, `python3 scripts/validate_module_catalog.py`, `python3 scripts/validate_wo_registry.py`, `python3 scripts/select_wo.py WORLD-02` expected refusal while code blocked. **All 122 runtime, undo, export, CPU, OS/Web, security and benchmark tests FUTURE NOT EXECUTED.**

## DELIVERABLES
8 new docs architecture, technology/license matrix, ADR-0027, semantic API, future acceptance cases, benchmark protocol, this WO, Evidence Bundle; 3 additive existing Architecture, Backlog and future coding packet links; research #162, docs PR and separate checkpoint PR with independent CI/audits. No executable assets.

## REVIEW FORMAT
Pt-BR objective verdict APPROVED/CORRECTION REQUIRED/BLOCKED, BASE/HEAD SHA+source fingerprints, changed files, CI exact-HEAD link, security/license/source/DoD findings, 122 NOT EXECUTED, risks, and proposed Checkpoint Delta. Correct same WO/PR; no advance with HIGH/CRITICAL.

## STOP CONDITION
Changed canonical source, incompatible rights, unsafe untrusted data graph, semantic overriding data loss, false software claim, unexpected C++/asset or failed CI => CORRECTION REQUIRED/BLOCKED in same WO, no WORLD-03 until checkpoint reconciled. No bypass, forced push, CodeRabbit, paid CI or mandatory external reviewer.

## CONTEXT LOCK
Research BASE 1871b4adc99eb82e79890af5e7a423d8db202daa. Git blob SHA is not raw byte SHA-256. Before any code, new approved Scope/DoD/ADR, exact target code files/ABI/rights, implemented WORLD-01+DATA-02 prerequisites, independent evidence and raw SHA-256 fingerprints mandatory.

## Verified research evidence and correction receipts
PR #163 research BASE main 1871b4adc99eb82e79890af5e7a423d8db202daa; initial HEAD 5c8fc2ce357f8ebef885f0dcb57a84199893f7f8 failed [Docs Validation #43635576110](https://github.com/KayzenRoot/stormline/actions/runs/43635576110) due 22 escaped Markdown backtick markers. Same WO/PR Correction Delta fixed 22 markers in this Work Order and added failure Evidence. Final audited HEAD 07045d868d96088c9897a78391fe92f2ef4fd1ca, [Docs Validation #43635712447](https://github.com/KayzenRoot/stormline/actions/runs/43635712447) SUCCESS exact HEAD, Socket Security/SonarCloud PASS, 11 docs-only files and objective pt-BR audit APPROVED no known HIGH/CRITICAL documentary defects. Normal squash main f278b46d6bf67f3751125e81af9e4346e7eced76. Checkpoint separate same-WO PR requires independent exact-HEAD CI/audit/readback. 122 future tests NOT EXECUTED, ADR-0027 PROPOSED and code #42 OPEN/BLOCKED.
