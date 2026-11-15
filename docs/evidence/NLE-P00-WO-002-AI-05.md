# Evidence Bundle — NLE-P00-WO-002-AI-05 / MCP Context Resources & Templates

**2026-11-15 | P00 RESEARCH DOCUMENTATION ONLY | [research issue #297](https://github.com/KayzenRoot/stormline/issues/297) | future code [#79](https://github.com/KayzenRoot/stormline/issues/79) OPEN/BLOCKED | BASE `ec1a8efc89de6e90d53f7b56fd31bc874335a2ff`.** No engine code, MCP context service, source semantic index or host conformance exists.

## 1. Source Check / Context Lock
- Requested git HEAD and live `refs/heads/main` both `ec1a8efc89de6e90d53f7b56fd31bc874335a2ff`, zero open PRs before research branch; AI-05 catalog_order **61/80**, dependencies **AI-02 + AI-04 only**, acceptance **"Agente descobre estrutura sem copiar repositório inteiro."** Code #79 OPEN/BLOCKED.
- Registry baseline: **80 modules, 60/80 research documented, 20 pending; 80/80 future code packets BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**, 0 executor_ready, 0 approved_adr, all release_class=UNDECIDED, engine_implemented=false.
- AI-02 and AI-04 research integrated but ADR-0061/0063 PROPOSED; future code #76/#78 blocked. AI-05 ADR-0064 remains PROPOSED. NLE-D009 license OPEN, NLE-D015 AI-native MCP owner-directed; no new formal edge.
- Canonical hierarchy, checkpoint, Decisions Ledger, Scope, DoD, Architecture, Requirements, AGENTS, module catalog, MCP architecture contract, registry, AI-05 future Work Order and AI-02/04 architecture/contracts/ADRs were read before changes.
- Context Lock source Git **blob OIDs (SHA-1, not standalone SHA-256)** documented with exact paths in research [Work Order](../work-orders/NLE-P00-WO-002-AI-05.md) and research issue #297. Critical source drift after base => STALE; no new source assumptions without fresh readback.

## 2. Technical research primary findings
- Official MCP **2026-07-28** modern protocol: stateless requests, per-request metadata and server/discover. AI-04 already owns JSON-RPC, wire version/transport and compatibility; AI-05 must not implement another MCP server.
- [Resources specification](https://modelcontextprotocol.io/specification/2026-07-28/server/resources): resources/list, resources/read, resources/templates/list, pagination, listChanged and opt-in resource updates; resources are application-controlled and URIs identify source context.
- [Prompts specification](https://modelcontextprotocol.io/specification/2026-07-28/server/prompts): prompts are user-selected, not model-controlled actions; examples and source text remain untrusted. [Python SDK prompts](https://py.sdk.modelcontextprotocol.io/servers/prompts/) and [TypeScript prompts](https://ts.sdk.modelcontextprotocol.io/v2/servers/prompts) clarify named string arguments and safe missing/unknown handling.
- [Completion](https://modelcontextprotocol.io/specification/2026-07-28/server/utilities/completion): completion/complete is optional for prompt and URI-template parameters; max 100 suggestions, prevent disclosure through suggestion values/total.
- [MCP 2026 release](https://blog.modelcontextprotocol.io/posts/2026-07-28/): cache hints ttlMs and cacheScope for eligible read/list results, including private per-auth response. Safe candidate defaults ttlMs=0/cacheScope=private for project/private content.
- [RFC 6570](https://www.rfc-editor.org/rfc/rfc6570): URI template language permits reserved-character expansion; AI-05 proposes a deliberately restricted typed-ID-only subset to eliminate unbounded arbitrary paths.
- AI-02 [architecture](../architecture/ai-02-project-semantic-index.md) and [API](../contracts/ai-02-semantic-index-api.md) already own derived index generation, authoritatively committed source revisions, provenance, permission-filtered search, context packs and cursor policy; AI-05 should compose only, not create second database.
- Rights/PII and revocation are critical: already delivered client plaintext cannot be remotely deleted; server-side revocation blocks new requests and cache/cursor/subscription access. Source citations must use owner IDs/digests, not a model-generated claim or raw paths.
- Potential libraries (uriparser, Mustache-family, ICU, SDK renderer) remain unselected. Exact tags, license/SPDX/NOTICE/SBOM/CVEs, test-file license distinctions, redistribution rights and multi-OS evidence require separate owner approval.

## 3. Scope: exactly eight NEW Markdown artifacts
1. [Architecture](../architecture/ai-05-context-resources-templates.md)
2. [ADR-0064 PROPOSED](../adr/0064-ai-05-authorized-context-projections.md)
3. [Technology / security / license matrix](../research/ai-05-context-technology-license-security-matrix.md)
4. [Typed resource/citation/recipe API](../contracts/ai-05-context-resource-api.md)
5. [128 FUTURE acceptance tests](../testing/ai-05-acceptance-matrix.md)
6. [Minimal context benchmark protocol](../research/ai-05-context-benchmark-protocol.md)
7. [Work Order](../work-orders/NLE-P00-WO-002-AI-05.md)
8. This Evidence Bundle.

Research PR changes these eight new Markdown only: no registry, checkpoint, backlog, CI, code, SDK, dependency lock or runtime config change.

## 4. Evidence status and limits
- **Exactly 128 distinct `A05-T001..A05-T128`** future scenarios are specified in eight groups of 16; **FUTURE/NOT EXECUTED, 0 run/0 PASS/0 FAIL**. Exact ID count/order to be verified with programmatic readback of PR HEAD.
- No MCP resource provider, URI parser, Context Capsule composer, prompt interpreter, AI-02 index, AI-04 transport, source-ACL engine, host integration, engine binary, repo-copy benchmark, or conformance test implemented or executed.
- No SDK, external library, model provider, license, code release class or benchmark threshold approved.
- Documentation CI can prove links/source hierarchy, DAG/queue and block status only, not real MCP integration/security performance.
- **Research PR/CI/audit/squash/readback: PENDING until observed**. Any future green status must carry exact commit SHA/run/job and objective pt-BR audit reference.

## 5. Proposed independent checkpoint delta (NOT PROMOTED in this research PR)
After exact-HEAD research Docs Validation **SUCCESS**, independent objective pt-BR documentary **APPROVED**, normal squash and main/readback:
- Open separate checkpoint PR from verified research merge SHA.
- Modify exactly **five** existing files: `docs/11-checkpoint.md`, `docs/08-backlog.md`, `docs/queue/implementation-registry.json`, `docs/work-orders/NLE-P00-WO-002-AI-05.md` and `docs/evidence/NLE-P00-WO-002-AI-05.md`.
- Sole semantic registry mutation: AI-05 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`; all other 79 entries, dependencies, release class, approved_adr, executor_ready, risk and code status remain untouched.
- **Target only after own CI/audit/squash/readback:** **61/80 research documented (76.25%), 19 pending, engine_implemented=false, 80/80 code WOs BLOCKED, executor_ready=0, approved_adr=0, all 80 release_class=UNDECIDED**.
- Close research issue #297 only after factual readback, leave future implementation #79 OPEN/BLOCKED. Historical closeout, if following project pattern, is another four-Markdown PR with own CI/audit/squash/readback before starting next module.

## 6. Risks, rollback, and audit oracles
- **Research risk LOW** for doc edits; code implementation risk **ELEVATED/HIGH_ASSURANCE** for privileged cross-project source export, auth, copyright, privacy, path traversal and arbitrary network/file access.
- Threats: hidden ACL existence/count/autocomplete leakage, prompt poisoning, nested URI expansion, SSRF, stale source/ACL, forged cursor, cache cross-tenant key, leaked licensed/private excerpts, unsigned source citations, unbounded context and false token savings.
- No known HIGH/CRITICAL defect is *claimed to be resolved* by documentation; implementation must prove separately. If a documentary HIGH/CRITICAL violation is found, same PR Correction Delta.
- Rollback of research docs = normal revert PR after audit; no source migration or data deletion. Any checkpoint mutation must be independently audited before becoming canonical.
- Testable future acceptance: no full-project automatic read, no unauthorized bytes/existence leak, no prompt-driven command, correct source revision/citation, explicit partial source coverage, bounded bytes and honest token estimates.

## Research PR #298 verified; independent checkpoint candidate
- [Pesquisa PR #298](https://github.com/KayzenRoot/stormline/pull/298) BASE `ec1a8efc89de6e90d53f7b56fd31bc874335a2ff`, HEAD final `d7758024494a5edf1d32b9e90f4594f6fe151e21`, oito novos Markdown e nenhum código/CI/registry/checkpoint/backlog. [Docs Validation #43771301324](https://github.com/KayzenRoot/stormline/actions/runs/43771301324) SUCCESS job #132987586852 (Source Pack/links, DAG, 80 WO registry, blocked Zcode selector), [auditoria em pt-BR #6902678036](https://github.com/KayzenRoot/stormline/pull/298#issuecomment-6902678036) APPROVED documental. Squash normal, main/readback `0df89955dcaf5ce9dada4900fe8deca6acfeaa85`, research issue [#297](https://github.com/KayzenRoot/stormline/issues/297) ainda OPEN até checkpoint; futuro código [#79](https://github.com/KayzenRoot/stormline/issues/79) OPEN/BLOCKED.
- Eight new Markdown, 128 unique A05 FUTURE tests, ADR-0064 PROPOSED. **Estado após checkpoint auditado:** **61/80 pesquisas documentadas (76,25%), 19 pendentes; ZERO engine**, 80/80 WOs de implementação `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`; ADR-0064 PROPOSED; NLE-D009 OPEN; A05-T001..A05-T128 FUTURE/NOT EXECUTED. Nenhum contexto MCP, SDK, host test, parser, autorização ou benchmark implementado.
- Checkpoint BASE `0df89955dcaf5ce9dada4900fe8deca6acfeaa85`; only five files, sole AI-05 status transition. Own CI/audit/squash/readback pending before research issue #297 closure; code #79 OPEN/BLOCKED.

## Independent checkpoint #299 and research closeout factual evidence
- [Research PR #298](https://github.com/KayzenRoot/stormline/pull/298): BASE `ec1a8efc89de6e90d53f7b56fd31bc874335a2ff`, final HEAD `d7758024494a5edf1d32b9e90f4594f6fe151e21`, **exactly 8 new Markdown**. [Docs Validation #43771301324](https://github.com/KayzenRoot/stormline/actions/runs/43771301324) SUCCESS, job #132987586852; [objective pt-BR audit #6902681484](https://github.com/KayzenRoot/stormline/pull/298#issuecomment-6902681484) APPROVED documentary only. Normal squash/main readback `0df89955dcaf5ce9dada4900fe8deca6acfeaa85`.
- [Independent checkpoint #299](https://github.com/KayzenRoot/stormline/pull/299): BASE `0df89955dcaf5ce9dada4900fe8deca6acfeaa85`, final HEAD `40f744d083122dc60808733b8d752921677f60f5`, **exactly 5 modified files**; sole registry semantic transition AI-05 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`. [Docs Validation #43771516761](https://github.com/KayzenRoot/stormline/actions/runs/43771516761) SUCCESS job #132988243234; [audit #6902704817](https://github.com/KayzenRoot/stormline/pull/299#issuecomment-6902704817) APPROVED documentary. Squash/main readback `4a2280959871b84c5b3b2b292daaa250d21481e0`; [readback note #6902712670](https://github.com/KayzenRoot/stormline/pull/299#issuecomment-6902712670).
- [Research issue #297](https://github.com/KayzenRoot/stormline/issues/297) **CLOSED after checkpoint proof**. Future code [#79](https://github.com/KayzenRoot/stormline/issues/79) OPEN/BLOCKED. Registry after checkpoint: **61/80 researches documented (76.25%), 19 pending, zero engine**; all 80/80 implementation WOs BLOCKED, executor_ready=0, approved_adr=0, all release_class=UNDECIDED. ADR-0064 remains **PROPOSED** and NLE-D009 license OPEN; exactly 128 A05 FUTURE/NOT EXECUTED tests, no runtime, hosted service, index, conformance, host certification or benchmark.
- Next research by registry: **AI-06 Agent Security & Authorization**, catalog order **62/80**, formal dependencies **AI-04 + AI-01**, code [#80](https://github.com/KayzenRoot/stormline/issues/80) OPEN/BLOCKED. Separate fresh Source Check required; no implementation authorized. Historical closeout PR modifies **only four Markdown**, with own CI/audit/squash/readback required before proceeding.
