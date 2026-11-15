# Evidence Bundle — NLE-P00-WO-002-AI-06 Agent Security & Authorization P00 Research

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #301 | NLE-P00-WO-002-AI-06 | future code #80 OPEN/BLOCKED | BASE 886f8c8687c4c79a18a3cb3b7e82a26a054eb656.** Formal deps AI-04 + AI-01 ONLY; 61/80 research at baseline, all 80 future code WOs BLOCKED; ADR-0065 PROPOSED; NLE-D009 OPEN.

## 1. Verified Source Check
- Requested HEAD and live refs/heads/main match `886f8c8687c4c79a18a3cb3b7e82a26a054eb656` before work. Zero open PRs; future code [#80](https://github.com/KayzenRoot/stormline/issues/80) OPEN/BLOCKED.
- Registry: 80 modules, **61/80 research documented, 19 pending**, all **80/80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**, executor_ready=0, approved_adr=0, 80/80 release_class=UNDECIDED, engine_implemented=false.
- Catalog AI-06 order **62/80**, acceptance *"Agente não pode modificar arquivos/projetos fora do escopo."*, formal dependencies **AI-04 + AI-01 only**, predecessor ADR-0063/0060 PROPOSED and implementation blocked.
- Canonical hierarchy/Checkpoint/Decisions/Scope/DoD/Architecture/Requirements/AGENTS/catalog/MCP contract/AI-01 and AI-04 architectures/contracts/ADRs/future AI-06 WO read prior to research. Exact Git **blob SHA-1 object IDs (not raw SHA-256)** recorded in [research WO](../work-orders/NLE-P00-WO-002-AI-06.md) and issue #301. Recheck for STALE before PR/checkpoint.

## 2. Technical research evidence (not runtime test)
- Official [MCP 2026-07-28 authorization](https://modelcontextprotocol.io/specification/2026-07-28/basic/authorization) defines HTTP OAuth resource-server behavior, protected resource metadata and transport separation; stdio requires local security model. An OAuth token to MCP resource is **not** broad Stormline project access.
- Official [MCP security best practices](https://modelcontextprotocol.io/docs/2026-07-28/tutorials/security/security_best_practices) cover confused deputy, token passthrough, SSRF, state-handle and local server attacks.
- [MCP 2026 release notes](https://blog.modelcontextprotocol.io/posts/2026-07-28/) document stateless per-request metadata and MRTR, which cannot count as trusted approval.
- [OWASP Agentic Top 10 2026](https://genai.owasp.org/resource/owasp-top-10-for-agentic-applications-for-2026/) motivates the ASI01..ASI10 threat matrix and independent denial oracles.
- [Cedar](https://github.com/cedar-policy/cedar) (root Apache-2.0) and [OPA/Rego](https://www.openpolicyagent.org/docs) (root Apache-2.0) are **unselected** policy evaluator candidates. [Wasmtime](https://docs.wasmtime.dev/security.html), [Linux Landlock](https://docs.kernel.org/userspace-api/landlock.html), [macOS App Sandbox](https://developer.apple.com/documentation/security/app-sandbox/) and Windows AppContainer are OS/guest isolation **candidates**, not deployed protections.
- Proposed design: deny-overrides grants, user+agent+project+CommandId attenuating delegation, just-in-time AI-01 owner PEP, one-use consent receipt bound to owner plan/revision/args/target, policy epoch revoke, zero ambient credentials, OS sandbox defense in depth, scoped redacted audit.
- NLE-D009 engine license remains OPEN; no library/package versions, policy interpreter, sandbox, OAuth provider, key management, host SDK, execution or approval has been adopted.

## 3. Research artifacts: eight NEW Markdown
1. [Architecture](../architecture/ai-06-agent-security-authorization.md)
2. [ADR-0065 PROPOSED](../adr/0065-ai-06-agent-grant-consent-policy.md)
3. [Technology/license/security threats](../research/ai-06-auth-technology-license-threat-matrix.md)
4. [Authorization typed API](../contracts/ai-06-authorization-api.md)
5. [128 FUTURE tests](../testing/ai-06-acceptance-matrix.md)
6. [Benchmark protocol](../research/ai-06-security-benchmark-protocol.md)
7. [Research WO](../work-orders/NLE-P00-WO-002-AI-06.md)
8. This Evidence Bundle.

Research PR should change **exactly eight new Markdown**, no code/SDK/runtime/auth credentials, no workflow, registry, checkpoint or backlog.

## 4. Validation truth
- **A06-T001..A06-T128**: exactly 128 distinct, ordered FUTURE/NOT EXECUTED scenarios in 8 groups of 16. No executable tests written. Need verify IDs via PR readback.
- **0** MCP conformance runs, owner authorization test executions, OS sandbox runs, host interoperability tests, policy engine benchmarks, native builds or security certifications.
- Documentation CI may prove links/DAG/registry blocked status, **not** actual project data isolation or policy correctness. CI/run/job/audit/merge values are PENDING until observed and recorded in later checkpoint delta.
- Catalog scope is conceptual: no user app/agent can rely on these controls as if implemented.

## 5. Proposed independent checkpoint delta (NOT promoted by this research PR)
Only after exact-final-HEAD Docs Validation SUCCESS and objective pt-BR APPROVED documentary audit, normal squash and verified main/readback:
- **Separate checkpoint PR exactly five modified files:** `docs/11-checkpoint.md`, `docs/08-backlog.md`, `docs/queue/implementation-registry.json`, this research WO and Evidence.
- **Only registry semantic change:** AI-06 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED. Absolutely no dependency, other 79 module status, work_order_status, risk, release_class, executor_ready, approved_adr or engine_implemented change.
- Target **62/80 researched (77.5%), 18 pending, zero engine, 80/80 code WOs BLOCKED, 0 ready, 0 approved ADR, all release_class UNDECIDED**; code #80 remains OPEN/BLOCKED and AI-06 ADR-0065 remains PROPOSED.
- Checkpoint requires own exact-head CI, pt-BR objective audit, squash/readback. Close research issue #301 after factual proof only. Historical four-Markdown closeout with independent gates before next AI-07.

## 6. Risk review and rollback
Research-only risk LOW; later AI-06 code classification **HIGH_ASSURANCE** due to privileged authentication, consent, sandbox and destructive authorization. Unresolved: OS-specific isolation, token issuer/subject trust, grant signing, owner ACL race, policy engine selection and package/license compatibility, trustworthy approval UI, audit storage/retention/key management. Any HIGH/CRITICAL actual bypass must block code.
Rollback research docs via audited normal revert PR only; no project data/credentials are modified in P00. Do not treat "completed" or written policy as evidence of runtime protection.

## Research PR #302 factual checks and proposed independent checkpoint
- [Research PR #302](https://github.com/KayzenRoot/stormline/pull/302) BASE `886f8c8687c4c79a18a3cb3b7e82a26a054eb656`, final HEAD `e3a4b601ac8675beb81420d900121fff09a6b190`, exactly eight NEW Markdown, no code/CI/registry/checkpoint/backlog. [Docs Validation #43774594592](https://github.com/KayzenRoot/stormline/actions/runs/43774594592) SUCCESS job #132997880558 (Source Pack/local links, 80-module DAG, registry, blocked Zcode selector); [objective pt-BR audit #6903130775](https://github.com/KayzenRoot/stormline/pull/302#issuecomment-6903130775) APPROVED DOCUMEN­TARY ONLY; normal squash/main/readback `c4ddd6d8c42ce250e043423457de17f2567a0e0a`. Research issue [#301](https://github.com/KayzenRoot/stormline/issues/301) remains OPEN pending independent checkpoint; future code [#80](https://github.com/KayzenRoot/stormline/issues/80) OPEN/BLOCKED.
- Eight new Markdown, 128 future unique tests, no runtime/security benchmark. **Após checkpoint auditado (proposta até CI/readback): 62/80 pesquisas documentadas (77,5%), 18 pendentes, zero engine, todos 80/80 WOs de código BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class=UNDECIDED.** ADR-0065 PROPOSED, NLE-D009 OPEN, exactly 128 A06 tests FUTURE/NOT EXECUTED, 0 native security tests and no OS sandbox/identity/consent service implemented. This checkpoint BASE `c4ddd6d8c42ce250e043423457de17f2567a0e0a`: exactly five modified files, one AI-06 status promotion only. Own CI/audit/squash/readback PENDING; no code unlock.
