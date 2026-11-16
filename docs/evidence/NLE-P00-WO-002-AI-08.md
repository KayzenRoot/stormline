# Evidence Bundle — NLE-P00-WO-002-AI-08 AI Authoring Workflows Research

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | [research #309](https://github.com/KayzenRoot/stormline/issues/309) | NLE-P00-WO-002-AI-08 | [future code #82](https://github.com/KayzenRoot/stormline/issues/82) OPEN/BLOCKED | BASE `55250c21f834067524014bdb70eedcdddbf6949e`.** Formal deps AI-05 + AI-07 only; ADR-0067 PROPOSED; 63/80 research at baseline; 80/80 future code packets BLOCKED; engine false, NLE-D009 license OPEN.

## 1. Source Check & Context Lock
- Live main exact requested HEAD `55250c21f834067524014bdb70eedcdddbf6949e`, zero open PRs prior to creating research issue/branch. Source hierarchy/Checkpoint/Decisions Ledger/Scope/DoD/Architecture/Requirements/AGENTS/catalog and MCP contract, future AI-08 blocked WO, AI-05/07 architecture+API+ADR reviewed with precedence.
- Registry baseline 80 modules, **63/80 research documented, 17 pending**, AI-08 research_status RESEARCH_PENDING with deps AI-05 + AI-07, **80/80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**, executor_ready=0, approved_adr=0, release_class=UNDECIDED, engine_implemented=false, code [#82](https://github.com/KayzenRoot/stormline/issues/82) OPEN/BLOCKED.
- Full Context Lock Git **blob SHA-1 OIDs (not raw file SHA-256)** with critical path mapping in [research Work Order](../work-orders/NLE-P00-WO-002-AI-08.md) and issue #309. Any substantive approved-source drift => STALE, stop/rebase.
- NLE-D015 owner-directed AI-native MCP, NLE-D017 desktop OS, D018 delegated docs with CI/audit, NLE-D019 blocked queue. NLE-D009 engine license OPEN. AI-05 ADR-0064 and AI-07 ADR-0066 PROPOSED, predecessors not implemented.

## 2. Research findings (external primary sources, NOT implementation proof)
- [MCP 2026-07-28](https://modelcontextprotocol.io/specification/2026-07-28) and [2026 release](https://blog.modelcontextprotocol.io/posts/2026-07-28/): user-consent, stateless, MRTR and optional Tasks, with deprecated Sampling/Roots/Logging not recommended defaults. AI-04 wire still authoritative transitive owner.
- [MCP Tasks SDK docs](https://csharp.sdk.modelcontextprotocol.io/v2/concepts/tasks/tasks.html) and [Python SDK migration](https://py.sdk.modelcontextprotocol.io/migration/): extension **optional** and exact SDK support differs; no automatic assumption of background task ability.
- [OpenUSD](https://github.com/PixarAnimationStudios/OpenUSD/blob/dev/docs/intro.rst) layering/variant/scene composition is promising interchange, not native source authority. [OpenUSD LICENSE.txt](https://github.com/PixarAnimationStudios/OpenUSD/blob/dev/LICENSE.txt) contains **Tomorrow Open Source Technology License 1.0** (different trademark term from Apache-2.0) and bundled third-party notices; exact tag required.
- [Khronos glTF 2.0](https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html): mesh/material/animation and `extensionsRequired` must be feature-checked; not game physics/script/UI representation. [MaterialX](https://github.com/AcademySoftwareFoundation/MaterialX/blob/main/documents/Specification/MaterialX.Specification.md) typed shader nodes, repository [Apache-2.0](https://github.com/AcademySoftwareFoundation/MaterialX/blob/main/LICENSE) at root; target compile still separate. [OpenTimelineIO](https://github.com/AcademySoftwareFoundation/OpenTimelineIO/blob/main/docs/index.rst) references media externally and does not embed audio/video.
- [OWASP Agentic 2026](https://genai.owasp.org/resource/owasp-top-10-for-agentic-applications-for-2026/): prompt-injection goal hijack, tool/permission abuse and multi-agent/cross-context contamination require typed owner operations, not model safety claims.
- Proposed architecture: declarative versioned authoring recipe DAG; AI-05 bounded owner-cited resources; AI-07 preview/consent/source commit/readback; mandatory vs optional owner capability truth, provenance/licensing, target/cook/quality checks, reproducible offline recipes. Cloud LLM/asset generation optional and not proven deterministic. No decision overrides approved.

## 3. Exactly eight NEW research Markdown
1. [Architecture](../architecture/ai-08-authoring-workflows.md)
2. [ADR-0067 PROPOSED](../adr/0067-ai-08-declarative-owner-authoring-recipes.md)
3. [Tech/license/security](../research/ai-08-workflow-technology-license-threat-matrix.md)
4. [Typed workflow/recipe API](../contracts/ai-08-authoring-workflow-api.md)
5. [128 unique A08 future tests](../testing/ai-08-acceptance-matrix.md)
6. [Benchmark protocol](../research/ai-08-authoring-benchmark-protocol.md)
7. [Research Work Order](../work-orders/NLE-P00-WO-002-AI-08.md)
8. This Evidence Bundle.

**Research PR:** precisely eight new Markdown, no code/CI/registry/backlog/checkpoint modification.

## 4. Factual limits
- Exactly **128 unique A08-T001..A08-T128** future scenarios, eight groups of 16; all **FUTURE / NOT EXECUTED**, zero PASS/FAIL, zero engine, no shader/material/VFX/audio/script/scene/export runtime or real host test.
- No full 2D/3D game generated; no editor, compilation, build, package, sampled model, SDK Tasks, benchmark or security test actually run.
- Even a supported future "zero manual edit" fixture still requires **trusted human consent** where policy says so; no unsafe self-approval or private asset import.
- Runtime license, model provider, recipe engine, SDK, material library, owner schemas and target capabilities all **UNDECIDED**. CI/audit/merge values PENDING until observed in downstream checkpoint.

## 5. Proposed independent checkpoint delta (NOT PROMOTED in research)
After research PR exact HEAD Docs Validation SUCCESS, pt-BR objective documentary audit APPROVED, squash and main readback:
- Open independent five-file checkpoint from verified main. Exactly `docs/11-checkpoint.md`, `docs/08-backlog.md`, `docs/queue/implementation-registry.json`, this WO and this Evidence. **Sole registry semantic mutation: AI-08 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`**.
- All other 79 registry module entries and ALL future work_order_status, dependency, risk, release_class, approved_adr, executor_ready and engine_implemented fields unchanged.
- **Target 64/80 documented (80%), 16 pending, all 80 future coding WOs BLOCKED, zero ready/approved/engine; ADR-0067 PROPOSED, 128 tests FUTURE/NOT EXECUTED**.
- Independent exact-head CI/audit/squash/main readback before closing research issue #309. Future code #82 stays OPEN/BLOCKED. Historical closeout four Markdown files, own CI/audit/squash/main readback before AI-09.

## 6. Risks and rollback
- P00 documentation LOW; future workflow orchestration creating source, interpreting scripts, importing copyrighted content or exporting externally **HIGH_ASSURANCE**. Threats: prompt-to-tool hijack, source rights, cross-project references, unbounded graph, missing owner capabilities, stale context/consent, false COMPLETE, leaked source or token, unlicensed media/voices, target incompatibility, incorrect rollback of external effects.
- No HIGH/CRITICAL actual runtime vulnerabilities claimed addressed. Only documentary planning/audit can approve this increment; functional+tested+deploy+validated future DoD remains UNSATISFIED.
- Rollback research docs via audited ordinary revert PR, no source migrations or assets touched in P00.

## Research PR #310 factual evidence and proposed independent checkpoint
- [Research PR #310](https://github.com/KayzenRoot/stormline/pull/310) BASE `55250c21f834067524014bdb70eedcdddbf6949e`, final HEAD `34f4b656d38c279eab7d3b2950fd8ebf0e2f64f4`, exactly eight NEW Markdown; [Docs Validation #43777724415](https://github.com/KayzenRoot/stormline/actions/runs/43777724415) SUCCESS at exact HEAD, job #133007734877 (Source Pack/links, 80-module DAG, registry, blocked Zcode selector); [objective pt-BR audit #6903567652](https://github.com/KayzenRoot/stormline/pull/310#issuecomment-6903567652) APPROVED documentary only; normal squash/main readback `ec5a710d083528a14eab169cf4daa835f03d9361`. Research [#309](https://github.com/KayzenRoot/stormline/issues/309) remains OPEN until independent checkpoint; future code [#82](https://github.com/KayzenRoot/stormline/issues/82) OPEN/BLOCKED.
- Eight new Markdown, 128 A08 future tests, ADR-0067 PROPOSED. **Post-checkpoint target pending own CI/audit/readback:** 64/80 research documented (80%), 16 pending, engine_implemented=false; **80/80 implementation WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**, executor_ready=0, approved_adr=0, release_class=UNDECIDED all; ADR-0067 PROPOSED, NLE-D009 OPEN, A08-T001..A08-T128 FUTURE/NOT EXECUTED. No runtime/owner/host/cook/SDK or benchmark proof. Checkpoint BASE `ec5a710d083528a14eab169cf4daa835f03d9361`, exactly five files, sole AI-08 status promotion in registry. Own CI/audit/squash/main readback pending; no runtime/host/benchmark proof.
