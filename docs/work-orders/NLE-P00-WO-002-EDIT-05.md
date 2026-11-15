# NLE-P00-WO-002-EDIT-05 — Visual Shader & Material Graph P00 Documentary Research Work Order

**2026-11-15 | Research [#268](https://github.com/KayzenRoot/stormline/issues/268) | catalog_order=54 | future implementation [#72](https://github.com/KayzenRoot/stormline/issues/72) OPEN/BLOCKED.** BASE main `7034fdce1d1d0220b349e8b333dc67cc6d19c515`. Baseline 53/80 research documented, 27 pending, zero engine; all 80/80 implementation WOs BLOCKED. Formal dependencies **EDIT-02 + GFX-05**, both documented/ADR PROPOSED, not implemented. Risk LOW for docs; future shader compiler/driver/import/preview ELEVATED. Privileged arbitrary native node/plugin execution is OUT OF SCOPE and would require a separate HIGH_ASSURANCE decision.

## OBJECTIVE
Research a professional toolkit-neutral Visual Shader & Material Graph authoring system: typed node canvas, ports/links, node palette/search, graph navigation, subgraphs/groups, parameter inspector, material preview, GFX-02 compile/reflection/diagnostics, GFX-05 material semantics, dynamic/static parameters and bounded variants, target compatibility, validated shader/material export, accessible buttons/commands, secure import/clipboard/compiler, licenses, tests and benchmarks. **No engine code or dependency adoption.**

## CONTEXT
Source Pack precedence is checkpoint > Decisions Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > remaining docs. Research #268, future code #72. Verified main SHA `7034fdce1d1d0220b349e8b333dc67cc6d19c515`; no open PRs. Registry is 80 modules, 53 documented/27 pending; EDIT-05 RESEARCH_PENDING, dependencies EDIT-02/GFX-05, code BLOCKED, risk UNCLASSIFIED, release UNDECIDED. Formal predecessors have research docs but no implementation: EDIT-02 #69 and GFX-05 #33 remain OPEN/BLOCKED. GFX-02 #30 is integration owner for compilation/graph semantics and remains OPEN/BLOCKED; no extra formal DAG edge. GFX-05 code itself requires GFX-02 and DATA-03 actual evidence. All 80 code packets remain blocked.

## SCOPE — exactly eight NEW Markdown files
1. [Architecture](../architecture/edit-05-visual-shader-material-graph.md)
2. [ADR-0057 PROPOSED](../adr/0057-edit-05-semantic-graph-authoring-and-preview.md)
3. [Technology/license/security/interoperability matrix](../research/edit-05-visual-shader-technology-license-matrix.md)
4. [Typed semantic API and button/command contract](../contracts/edit-05-visual-shader-api.md)
5. [Exactly 128 E05-T001..E05-T128 FUTURE tests](../testing/edit-05-acceptance-matrix.md)
6. [Benchmark/fault protocol](../research/edit-05-visual-shader-benchmark-protocol.md)
7. This Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-EDIT-05.md)

Research PR adds exactly these eight files. No checkpoint/backlog/registry/CI/source-code/SDK changes in research PR. After exact-final-HEAD Docs Validation and objective pt-BR audit, normal squash merge and main/contract readback, create an **independent five-file checkpoint PR**: checkpoint, backlog, registry (SOLE EDIT-05 research_status), this WO and Evidence. Target 54/80 documented (67.5%), 26 pending, zero engine, all 80 coding WOs blocked. After checkpoint CI/audit/squash/readback, close research #268; code #72 stays OPEN/BLOCKED. A separate four-Markdown historical closeout may follow with its own gates. Do not begin EDIT-06 until this closeout is objectively read back.

## OUT OF SCOPE
C++/Rust/TypeScript editor or graph engine; actual graph schema/compiler/IR or shader language; Vulkan/Metal/WebGPU pipeline, GPU preview, render code, PBR implementation, asset importer/cooker, dependency/toolkit install, MaterialX runtime adoption, custom executable nodes/plugins/scripts, arbitrary source editor, remote/cloud compilation, collaboration, AI auto-commit, image generation, third-party proprietary content, paid CI, CodeRabbit, external human reviewer requirement, release class/license approval, performance/accessibility claims, engine deployment/public MVP. No registry unblock, bypass or force-push.

## FILES / SOURCES TO READ
Canonical order: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/EDIT-05.md`. Formal deps: EDIT-02 architecture/API/ADR-0054 and GFX-05 architecture/matrix/API/ADR-0018. Integration sources: EDIT-01 architecture/API/ADR-0053; GFX-02 architecture/API/ADR-0015; DATA-02/03/04/05, GFX-01/03/06/07, EDIT-07, QA-04, AI/MCP contracts. External official sources in matrix: MaterialX 1.39/1.39.5, Khronos glTF/PBR/extensions, Slang, DXC/SPIR-V tools, W3C WGSL/WebGPU, ImNodes, xyflow, Godot VisualShaders and Unreal static parameter docs.

## REQUIREMENTS
GOV-001..005; CAP-001, CAP-008, CAP-009, CAP-010, CAP-011, CAP-012, CAP-013, CAP-014, CAP-016; NFR-001..005; NLE-D013..020. Catalog acceptance: **Visualizar e exportar shader/material validado.** This requires real future editor, compile/preview and validated export evidence; document-only CI is not that proof. No release 1.0 class, engine source license NLE-D009, compiler/toolkit or numeric budget is approved.

## ARCHITECTURE RULES
EDIT-05 owns graph-editor UX/commands/presentation state only. EDIT-01 shared shell/button/keyboard/accessibility registry; EDIT-02 project scope; GFX-02 canonical graph semantics/compiler/reflection/variants/cache; GFX-05 material/PBR/texture semantics; DATA-02/03/04/05 asset identity/import/persistence/cook; GFX-01/03 RHI/device/fence/render resources; GFX-06/07 light/color; EDIT-07 preview/debug; QA-04 security. No new formal DAG edge beyond EDIT-02/GFX-05. Graph is bounded typed DAG, no recursive graph or arbitrary code. All source writes through owner preview/stage/validate/CAS; compile preview is isolated and cancellable; last-good retained; target loss explicit. All toolbar buttons use stable EDIT-01 EditorCommandIdV1 and same permission checks across UI/CLI/MCP.

## CONSTRAINTS
Research-only risk LOW. All source fingerprints in Evidence are Git blob object SHAs, **not byte SHA-256**; re-fetch critical files before mutation. Checkpoint/Scope/DoD/Architecture/approved ADR drift => Context Lock STALE and recompile. No false claims about Slang target parity, MaterialX support, UI library license, graph runtime, benchmark or editor. Exact toolkit/compiler/schema/license versions and quotas remain open. All 80 code WOs remain BLOCKED.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight NEW Markdown deliverables, scoped diff only.
- [ ] ADR-0057 PROPOSED; GFX-02/GFX-05/EDIT-02 ownership boundaries preserved and no DAG inflation.
- [ ] Buttons and graph commands defined through EDIT-01 stable command registry with accessible labels/states/disabled reasons, focus/IME and GUI/CLI/MCP parity.
- [ ] Typed graph node/port/edge, DAG/subgraph/version, layout/semantic digest separation, compiler receipt, material preview, variants and validated export contracts specified.
- [ ] MaterialX/glTF interoperability and target compiler limitations/licensing/security documented accurately.
- [ ] Exactly 128 unique E05 tests all FUTURE/NOT EXECUTED; reproducible benchmark/fault protocol with thresholds TBD.
- [ ] Research PR exact-final-HEAD Docs Validation SUCCESS, actual 8-file diff, objective pt-BR audit APPROVED with no HIGH/CRITICAL, normal squash and main/API readback.
- [ ] Separate checkpoint PR changes exactly five files and only EDIT-05.research_status; its own exact-head CI/audit/squash/readback. All 80 code WOs remain BLOCKED.
- [ ] Optional historical closeout has own four-file diff, CI/audit/squash/readback; research #268 closes only after checkpoint factual readback, code #72 remains OPEN/BLOCKED.

## TESTS
Document CI: `python3 scripts/validate_docs.py`, module catalog/DAG and registry validators through existing GitHub Actions Docs Validation. Verify exactly eight new files and 128 unique IDs. CI must be on exact final PR HEAD and selector must reject all blocked packets. Do not claim local tests ran unless actual checkout/commands available. Future runtime matrix in [128 tests](../testing/edit-05-acceptance-matrix.md) and [benchmark/fault protocol](../research/edit-05-visual-shader-benchmark-protocol.md); all NOT EXECUTED.

## DELIVERABLES
Eight Markdown docs, research issue/branch/PR, exact base/head/diff, CI run evidence, pt-BR audit, risks and proposed checkpoint delta. No source code or compiled shader artifact.

## REVIEW FORMAT
Português brasileiro: APPROVED / CORRECTION REQUIRED / BLOCKED; exact base/head; eight file paths; 128 IDs/count; CI run and steps; ownership/DAG/license/security/accessibility audit; no HIGH/CRITICAL; observed fixes; checkpoint delta; stop condition. Corrections remain in this WO/PR.

## STOP CONDITION
Stop on stale canonical sources, unexpected file diff, DAG inflation, owner authority duplication, license misstatement, compiler/toolkit selection presented as approved, arbitrary code path, unsupported target promise, CI failure, test count mismatch, known HIGH/CRITICAL, or any attempt to unlock code #72 or another packet.

## CONTEXT LOCK — planning baseline
Verified main BASE `7034fdce1d1d0220b349e8b333dc67cc6d19c515`. Critical Git blob fingerprints at Source Check (Git object SHA-1, **not byte SHA-256**):
- checkpoint `cf9a609a882fe8deefcd46f0cc55c55f7818d880`
- Decisions Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- Scope `4ef605c74632ece080b2650e37dd83a415b63310`
- DoD `160b3054db9ea1961308934b401488b838d24c3e`
- Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- Module catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- implementation registry `b2e079bc87f0656c7e08125eb995a35b5db7ce9b`
- AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`
- EDIT-05 blocked packet `f11f565d97ea106aaab2b2624f45540a2870c5d9`
- EDIT-02 architecture/API/ADR `48c7ab698950d48e761b56f1f05dbd56b4ea8d9e` / `d2ce33b3d52f9a73bbf7de51af80ab800ce4e720` / `ae328eeb6ee5a07b58f2235102d2114fe7ea1213`
- GFX-05 architecture/matrix/API/ADR `d35e343843ab77fea26f2ae53d1aa6723dc7ccf4` / `4aec41eca42c5a7b88b0603245d2b896aa2013c5` / `42c15e9a1d7ff97765a24c1539869cba066110c3` / `7b447206b40869f2f38ae6a13252ca4186e6c0a1`
- GFX-02 architecture/API/ADR `dbc2822aa6d6890b93e60fc095d94bf5d78e6f6b` / `2e7e14f5f598d25229582683ea4a9d0d531e8580` / `b26e90e9f0fa4c45a22a8aa920bc2680c0e61c88`
- EDIT-01 architecture/API/ADR `d8eb653afb1734746775cd4133462976140bcd7c` / `e2c713c6666f0521f44b1d0920b1a696391844d7` / `6cc58d33531a5bd761fe0d61a4d11cf4329b2fb5`

Refresh these from the actual branch before writes; if any source changes, mark lock STALE and rebase/re-audit.

## EVIDENCE BUNDLE
See [Evidence](../evidence/NLE-P00-WO-002-EDIT-05.md); record only observed Git SHA, file diff, exact-head CI, audit, merge and readback. No inferred test/benchmark success.
