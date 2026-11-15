# NLE-P00-WO-002-AI-05 — MCP Context Resources & Templates P00 Research Work Order

**2026-11-15 | RESEARCH ONLY / NOT IMPLEMENTED | [research issue #297](https://github.com/KayzenRoot/stormline/issues/297) | [future code #79](https://github.com/KayzenRoot/stormline/issues/79) OPEN/BLOCKED | BASE `ec1a8efc89de6e90d53f7b56fd31bc874335a2ff`.** Catalog order **61/80**. Formal dependencies **AI-02 + AI-04 only**, both documentary/ADR PROPOSED; AI-02 code #76 and AI-04 code #78 BLOCKED. 60/80 researched at baseline, 20 pending, zero engine; all 80 implementation WOs BLOCKED.

## OBJECTIVE
Research, architect and specify a versioned, rights-aware **read-only** MCP context provider delivering compact project/scene/asset/script/schema/document resource catalogs, RFC6570 typed resource templates, source-cited Context Capsules, user-selected prompts/recipes, optional argument completion, pagination/caching/freshness and explicit partial coverage. Provide 128 FUTURE tests and reproducible benchmark proving an agent can discover structure **without copying the repository**. No implementation.

## CONTEXT / SOURCE CHECK
- Canonical source hierarchy: checkpoint > Decisions Ledger and approved ADRs > Scope > DoD > Architecture > Requirements > remaining sources. Main exactly `ec1a8efc89de6e90d53f7b56fd31bc874335a2ff` at entry, with zero open PRs; AI-05 research_status RESEARCH_PENDING and code #79 OPEN/BLOCKED.
- AI-02 ADR-0061 (source-backed, rebuildable project index) and AI-04 ADR-0063 (MCP stateless protocol adapter) both PROPOSED; no engine/index/server runtime exists. AI-01, DATA-02, AI-03, DATA-04, WORLD-02, GAME-02 are transitive/integration owners, not additional formal dependencies.
- NLE-D015 OWNER-DIRECTED model-neutral AI-native MCP, NLE-D009 engine license OPEN. NLE-D003 documentary-before-code, NLE-D005 zero-cost CI and no CodeRabbit, NLE-D018 delegated routine documentation with controls.

## CONTEXT LOCK / REQUIRED FINGERPRINTS
Git **blob object IDs (SHA-1, not SHA-256 of working-tree bytes)** taken from BASE:
- `AGENTS.md`: `3e57b719f8651407879ebb641707a048773ea4c2`.
- `docs/00-source-hierarchy.md`: `58a377bc76cafdd3377d733d4f30ef53661bb034`.
- `docs/11-checkpoint.md`: `220ac506b0124dd74a927040f8e7f4029c0264ab`.
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`.
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`.
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`.
- `docs/04-architecture.md`: `df62574cb3956c3ac9881631a4cf66be4e1abff1`.
- `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`.
- `docs/product/module-catalog.md`: `18d69bca439831d65982cb0f8acbca1dbaa2eee9`.
- `docs/product/ai-mcp-contract.md`: `161183078034162ca458212e65a47cd17a112394`.
- `docs/queue/implementation-registry.json`: `d7021bf3d4ec1b16204cf593811f8ca257cbbeb0`.
- `docs/queue/work-orders/AI-05.md`: `943e142ecc3309d0586ac6f2499892354647329c`.
- `docs/architecture/ai-02-project-semantic-index.md`: `c87575cb33f3a652421a8f62555a9a7d027f6139`; `docs/contracts/ai-02-semantic-index-api.md`: `c1b21f066c59119a98b86d847f2db9ded6109b9b`; `docs/adr/0061-ai-02-rebuildable-authorized-semantic-index.md`: `fcdf7d00424c6d154b0cbd4be8e9db9a55d2c3e3`.
- `docs/architecture/ai-04-mcp-server-protocol-adapter.md`: `3c1cef611c99c8e7c297ad5ea3a92228b953d443`; `docs/contracts/ai-04-mcp-server-contracts.md`: `098d9bc2346743000445af3631a1bb700e2b7027`; `docs/adr/0063-ai-04-stateless-mcp-adapter.md`: `9e60bfede7052823b7b7906554673f6e2fdf25ce`.
Before write/PR/checkpoint compare relevant base/head and critical sources; any approved decision, Scope, DoD or Architecture drift => **STALE**, stop and recompile.

## SCOPE — exactly eight NEW Markdown documents
1. [Architecture](../architecture/ai-05-context-resources-templates.md)
2. [ADR-0064 PROPOSED](../adr/0064-ai-05-authorized-context-projections.md)
3. [Technology, license, risk and alternatives matrix](../research/ai-05-context-technology-license-security-matrix.md)
4. [Typed resources/templates/prompt/citation contracts](../contracts/ai-05-context-resource-api.md)
5. [Exactly 128 FUTURE tests](../testing/ai-05-acceptance-matrix.md)
6. [Reproducible benchmark protocol](../research/ai-05-context-benchmark-protocol.md)
7. This Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-AI-05.md)

Research PR changes exactly these eight NEW Markdown files, **no registry/checkpoint/backlog/CI/SDK/code edits**. Independent checkpoint PR after successful research audit changes only checkpoint, backlog, registry (one status), this research WO and Evidence; historical closeout if established uses four Markdown, each independently gated.

## OUT OF SCOPE
Any C++/TypeScript/Python runtime, SDK install, MCP endpoint, context index implementation, database, source content upload, arbitrary file/http fetch, vector store/embeddings, LLM/cloud summarization, run prompts as tools, auth issuer, schema parser, privilege widening, editor UI, import/export commands, proprietary assets, third-party IP distribution, benchmark claims, public 1.0, license choice, paid CI, CodeRabbit, mandatory external reviewer, force push/bypass or wholesale cleanup.

## FILES / SOURCES TO READ
All canonical sources listed in Context Lock, plus AI-02 and AI-04 research documents/128 test matrices, future AI-05 code WO, all relevant preceding ADRs. External: official MCP 2026-07-28 resources/prompts/completion/versioning/cache/subscriptions, RFC6570 URI Templates, SDK exact-version docs and security/authorization best practices, license notices for any candidate URI/template library.

## REQUIREMENTS
GOV-001..005; CAP-010, CAP-013, CAP-014, CAP-016; NFR-002..005; NLE-D015 and owner P00 first. Catalog AI-05 acceptance **"Agente descobre estrutura sem copiar repositório inteiro."** Provenance and rights, owner-scoped ACL, source revision, explicit partial coverage, bounded context and deterministic pagination/byte budgeting are acceptance obligations. Preserve AI-02's search/source truth, AI-04's MCP wire ownership and AI-01's source command authority.

## ARCHITECTURE RULES
- Exactly two formal dependencies AI-02 and AI-04. No circular new edge to AI-01/DATA-02/AI-03 or downstream AI-06.
- Resources/list/read/templates/list use AI-04 wire. AI-05 is a provider port consuming AI-02 bounded owner citations, not a second search/index engine.
- Progressive discovery -> choose resource -> read revision-pinned bounded Context Capsule -> next page only if requested.
- Opaque typed stormline:// URIs, allowlisted RFC6570 subset; no raw path, arbitrary URL or reserved expansion.
- Auth before list/count/completion, again on hydration and every page; cursor bound to principal, project, grant/policy, index generation, query, sort, expiry.
- MCP 2026 modern cache ttlMs=0/private default for sensitive contexts; cached host data already disclosed cannot be remotely deleted.
- Prompts are user-controlled, no implicit command dispatch; user input/source text untrusted. Optional completion max 100 visible values, no hidden counts.
- Versioned source citations, rights/license markers, explicit stale/partial/unsupported outcomes, UTF-8 byte-based hard caps, approximate token estimates only.
- No SDK/license/technology adopted; NLE-D009 engine code license OPEN; all 80 WOs BLOCKED.

## CONSTRAINTS / RISK
Documentation-only risk LOW. Future cross-project access and privileged token/auth/rights distribution **ELEVATED / HIGH_ASSURANCE**. No invented conformance, user approvals, benchmark, deployed endpoint, SDK license or production functionality. No nonessential feature expansion. Existing P00 source hierarchy and queued future code WO remain canonical.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight new Markdown, valid relative links, unchanged registry/checkpoint/backlog/code in research PR.
- [ ] ADR-0064 remains PROPOSED and formal deps exactly AI-02 + AI-04; none of 80 implementation WOs unlocked.
- [ ] Security covers ACL before list/count/hydration/completion, RFC6570 URI injection/SSRF, cache revocation, prompt poisoning, rights/PII, stale owner revisions, provenance and exact citation.
- [ ] 128 unique ordered IDs `A05-T001..A05-T128`, all FUTURE/NOT EXECUTED with independent acceptance oracle and reproducible benchmark.
- [ ] Exact-HEAD Docs Validation SUCCESS with Source Pack/local links, module DAG, queue registry and blocked Zcode selector.
- [ ] Independent pt-BR objective audit APPROVED, no known HIGH/CRITICAL in the scoped doc work; normal squash and main readback.
- [ ] Independent checkpoint PR changes exactly five files; *sole* registry semantic transition AI-05 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED, preserving every other field and all code blocks.
- [ ] Checkpoint CI/audit/squash/readback confirms **61/80 documented (76.25%), 19 pending, engine false, 80/80 coding WOs BLOCKED, executor_ready=0, approved_adr=null, release_class=UNDECIDED**.
- [ ] Close research #297 only after factual readback; future code #79 remains OPEN/BLOCKED. If historical closeout needed, four-Markdown PR has its own gates/readback before AI-06.

## TESTS
P00 docs: repo scripts for source/local links, module taxonomy/DAG, implementation registry and selector must reject BLOCKED WOs; exact GitHub Docs Validation on final PR HEAD. Future MCP: official version-pinned resources/list/read, templates/list, prompts/list/get, optional completion/complete/subscriptions/listen, selected Codex/Claude host matrix, 128 A05 tests, rights/ACL/URI fuzz and min-context benchmarks. None of future code/runtime/conformance tests are executed in P00.

## DELIVERABLES
Eight research Markdown, ADR-0064 PROPOSED, typed contracts, security/license matrix, 128 future tests, benchmark plan, research issue/PR, Evidence Bundle; independent CI/audit/readback/checkpoint and optional factual closeout. No SDK installation, engine code or release.

## REVIEW FORMAT
Português brasileiro, verdict APPROVED/CORRECTION REQUIRED/BLOCKED; base/head SHA and exact file list; CI run/job/steps, 128 unique ID audit, formal DAG, architecture/security/rights/licensing, risks, checkpoint delta and factual main/registry readback. Don't claim completed without evidence.

## STOP CONDITION
Wrong baseline or drift, conflicting approved source, invalid docs links, missing test IDs, unapproved SDK/license, hidden owner permissions, path traversal/SSRF design, unbounded context, invented tests/perf, CI failure, HIGH/CRITICAL, unexpected code change or any code WO unlock. No AI-06 research until AI-05 checkpointhistory validated.
