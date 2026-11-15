# Evidence Bundle — NLE-P00-WO-002-AI-04 MCP Server & Protocol Adapter P00 Research

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #293 | NLE-P00-WO-002-AI-04 | code #78 OPEN/BLOCKED | BASE 0cdcef6ae19ba1105667404ed5749ad5155fef0f.** 59/80 researches documented, 21 pending, zero engine, all 80 implementation packets BLOCKED. Formal dependency AI-03 ONLY; ADR-0062 PROPOSED; NLE-D009 OPEN; NLE-D015 OWNER-DIRECTED.

## 1. Source Check verified at base
- Main 0cdcef6ae19ba1105667404ed5749ad5155fef0f equals user-provided HEAD; zero open PRs.
- AI-04 catalog order 60/80, formal dependency AI-03 only, future code issue #78 OPEN/BLOCKED.
- Registry: 80 modules; 59 research documented, 21 pending; 80/80 code WOs BLOCKED, executor_ready=false, approved_adr=null, release_class=UNDECIDED; engine_implemented=false.
- NLE-D015 OWNER-DIRECTED model-neutral MCP; NLE-D009 engine license OPEN; AI-03 ADR-0062 PROPOSED; AI-01 ADR-0060 PROPOSED.
- Context Lock OIDs (Git blob SHA-1, not byte SHA-256) are recorded in Work Order and research issue. Source files include hierarchy, checkpoint, Ledger, Scope, DoD, Architecture, Requirements, AGENTS, catalog, AI/MCP contract, registry, AI-04 future WO and AI-03 architecture/API/ADR.

## 2. External research findings (2026-11-15)
- MCP 2026-07-28 is the latest dated spec found. It introduces stateless requests, mandatory server/discover, per-request metadata, MRTR, subscriptions/listen and revised Streamable HTTP.
- 2026 Streamable HTTP is POST-only with no protocol sessions, GET stream or Last-Event-ID; 2025-11-25 is separate legacy handshake/session era.
- Modern HTTP requires protocol header/body consistency, method/name mirror headers, Origin validation and authentication. Local services bind loopback; remote access is explicit.
- OAuth resource-server path: RFC 9728 Protected Resource Metadata, RFC 8414/OIDC discovery, resource/audience validation and least privilege. Never token passthrough. CIMD is current client-registration direction; DCR is deprecated fallback.
- Tools use AI-03 projections and route to AI-01 owner. Annotations are untrusted; structuredContent must match outputSchema. Resources carry cache TTL/scope; prompts are user-controlled.
- Tasks is optional; requires per-request client capability, durable owner job, high-entropy IDs and authorization on every operation. No tasks/list. Current Python SDK v2 roadmap says Tasks extension not implemented; TypeScript has separate official Tasks package.
- TypeScript SDK v2 and Python SDK v2 are official Tier 1 candidates with different runtime/license/Tasks trade-offs. No candidate selected; exact tags and SBOM required.
- Official conformance suite distinguishes modern stateless 2026 and legacy handshake-era 2025. No suite executed in P00.

## 3. Exactly eight NEW Markdown artifacts
1. [Architecture](../architecture/ai-04-mcp-server-protocol-adapter.md)
2. [ADR-0063 PROPOSED](../adr/0063-ai-04-stateless-mcp-adapter.md)
3. [Technology/license/security matrix](../research/ai-04-mcp-technology-license-security-matrix.md)
4. [Typed contracts](../contracts/ai-04-mcp-server-contracts.md)
5. [128 future tests](../testing/ai-04-acceptance-matrix.md)
6. [Benchmark protocol](../research/ai-04-mcp-benchmark-protocol.md)
7. [Research WO](../work-orders/NLE-P00-WO-002-AI-04.md)
8. This Evidence Bundle

## 4. Test and implementation truth
A04-T001..A04-T128 are exactly 128 unique FUTURE / NOT EXECUTED scenarios; 0 executed, 0 passed, 0 failed. No MCP server, SDK, listener, OAuth provider, tool handler, resource/prompt provider, task runtime, conformance test, host integration or benchmark has been implemented or executed. Literature research is not product conformance; no Codex/Claude release certified. P00 Docs Validation/PR/CI/audit/readback remain pending until observed.

## 5. Proposed independent checkpoint delta — NOT promoted
After exact-final-HEAD research CI SUCCESS, objective pt-BR audit APPROVED, normal squash and main readback, create a separate checkpoint PR changing exactly five files: checkpoint, backlog, registry, this research WO and this Evidence. Sole registry semantic transition: AI-04 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED. Target after independent checkpoint CI/audit/squash/readback: **60/80 researched (75%), 20 pending, zero engine**; all 80 code WOs BLOCKED, executor_ready=0, approved_adr=0, release_class=UNDECIDED, engine_implemented=false. Research #293 closes only after factual readback; code #78 remains OPEN/BLOCKED. Historical closeout, if used, is separate four-Markdown PR with own gates.

## 6. Risks
Protocol-era mismatch/downgrade, token audience/issuer/scope bypass, token passthrough, DNS rebinding, Origin/CORS weakness, prompt/tool injection, cross-project tool/resource/task/cursor/cache leakage, legacy state contaminating stateless path, non-durable task handles, duplicate mutation retry, SDK/license mismatch and incomplete conformance. No code, SDK, endpoint, registry, auth provider, host integration or implementation unlock is authorized by this research WO.

## Research PR #294 — factual verification
- Research PR #294 BASE 0cdcef6ae19ba1105667404ed5749ad5155fef0f, final HEAD f20faa864dc09405e7f594aaa537c5f4ad4acd3d, exactly eight new Markdown. Docs Validation #43768221750 SUCCESS job #132978032826 at exact HEAD; Source Pack/links, module DAG, registry and blocked selector all SUCCESS. Objective pt-BR audit #6902255307 APPROVED documentary only. Normal squash merged; main readback b679395f544019eb8564fe7928d8185f548a9bf5. PR diff: eight new Markdown, zero code/registry/checkpoint/CI changes. 128 ordered unique A04 IDs, all FUTURE/NOT EXECUTED. No runtime or benchmark claims.
- Independent checkpoint PR BASE b679395f544019eb8564fe7928d8185f548a9bf5, five files, sole AI-04 research_status transition. **Após checkpoint auditado**: 60/80 pesquisas documentadas (75%), 20/80 pendentes, ZERO engine; 80/80 implementation WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null, release_class=UNDECIDED. ADR-0063 PROPOSED, NLE-D009 OPEN, 128 A04 tests FUTURE/NOT EXECUTED, zero runtime/host/conformance/benchmark execution. Own CI/audit/squash/main readback pending; research #293 remains open until proof.

## Independent checkpoint #295 and main readback VERIFIED
- [Research PR #294](https://github.com/KayzenRoot/stormline/pull/294) BASE `0cdcef6ae19ba1105667404ed5749ad5155fef0f`, HEAD final `f20faa864dc09405e7f594aaa537c5f4ad4acd3d`, oito novos Markdown. [Docs Validation #43768221750](https://github.com/KayzenRoot/stormline/actions/runs/43768221750) SUCCESS job #132978032826; [auditoria pt-BR #6902255307](https://github.com/KayzenRoot/stormline/pull/294#issuecomment-6902255307) APPROVED documental; squash normal/main readback `b679395f544019eb8564fe7928d8185f548a9bf5`.
- [Checkpoint PR #295](https://github.com/KayzenRoot/stormline/pull/295) BASE `b679395f544019eb8564fe7928d8185f548a9bf5`, HEAD final `0bd9680b5c42237e519a3020fbb1caea25aa5382`, exatos cinco arquivos. Registry diff prova **única** transição AI-04 `research_status=RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`. [Docs Validation #43768391556](https://github.com/KayzenRoot/stormline/actions/runs/43768391556) SUCCESS job #132978555327; [auditoria #6902275741](https://github.com/KayzenRoot/stormline/pull/295#issuecomment-6902275741) APPROVED documental. Squash normal e main readback `59b199dd3b0d2d64ed69e38cc26d6cde1b01c508`, PR merged.
- [Pesquisa #293](https://github.com/KayzenRoot/stormline/issues/293) CLOSED após o readback; implementação [#78](https://github.com/KayzenRoot/stormline/issues/78) OPEN/BLOCKED. Estado canônico: **60/80 pesquisas (75%), 20 pendentes, zero engine**, 80/80 code WOs BLOCKED, executor_ready=0, approved_adr=0, release_class=UNDECIDED, engine_implemented=false. ADR-0063 PROPOSED; 128 A04 FUTURE/NOT EXECUTED; nenhum servidor/SDK/auth provider/host conformance/benchmark implementado ou executado.
- Próximo módulo confirmado por registry: **AI-05 MCP Context Resources & Templates**, catalog order **61/80**, dependências formais **AI-02 + AI-04**. Nenhuma implementação liberada. Este closeout histórico altera apenas quatro Markdown e tem CI/auditoria/squash/readback próprios.

