# NLE-P00-WO-002-AI-06 — Agent Security & Authorization P00 Research Work Order

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #301 | NLE-P00-WO-002-AI-06 | future code #80 OPEN/BLOCKED | BASE 886f8c8687c4c79a18a3cb3b7e82a26a054eb656.** Formal deps AI-04 + AI-01 ONLY; 61/80 research at baseline, all 80 future code WOs BLOCKED; ADR-0065 PROPOSED; NLE-D009 OPEN.

**Research issue [#301](https://github.com/KayzenRoot/stormline/issues/301) OPEN**, catalog order **62/80** and future code [#80](https://github.com/KayzenRoot/stormline/issues/80) OPEN/BLOCKED. Formal dependencies AI-04 + AI-01 ONLY, both ADRs PROPOSED and code BLOCKED; AI-07 future integration is not a direct predecessor.

## OBJECTIVE
Research and specify capability-based authorization, verified agent identity/delegation, project/workspace scope, deny-overrides owner policy, one-use consent, grant revocation, OS sandbox and redacted audit across MCP and semantic command owners, without implementing runtime or approving technologies. Meet catalog oracle **"Agente não pode modificar arquivos/projetos fora do escopo."** with strong future proof obligations: independent owner/OS state, 128 negative/positive tests and reproducible benchmark.

## CONTEXT / SOURCE CHECK
Precedence: checkpoint > Decisions Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > remaining. Live main BASE `886f8c8687c4c79a18a3cb3b7e82a26a054eb656`, zero open PR before issue/branch, 61/80 research documented (76.25%), 19 pending, engine_implemented=false, all 80 implementation WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, zero executor_ready, approved_adr=null, all release_class UNDECIDED. AI-06 research_status RESEARCH_PENDING, future code #80 OPEN/BLOCKED. NLE-D015 owner-directed AI-native, NLE-D009 engine license OPEN, NLE-D018 documentary delegation only.

## CONTEXT LOCK (Git blob SHA-1 OIDs, NOT working-tree SHA-256)
- `docs/00-source-hierarchy.md` `58a377bc76cafdd3377d733d4f30ef53661bb034`, `docs/11-checkpoint.md` `df3dd83c0072e5383579a6209b14b8709b334fdd`, `docs/10-decisions-ledger.md` `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`.
- `docs/03-scope.md` `4ef605c74632ece080b2650e37dd83a415b63310`, `docs/09-definition-of-done.md` `160b3054db9ea1961308934b401488b838d24c3e`, `docs/04-architecture.md` `df62574cb3956c3ac9881631a4cf66be4e1abff1`, `docs/02-requirements.md` `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`.
- `AGENTS.md` `3e57b719f8651407879ebb641707a048773ea4c2`; `docs/product/module-catalog.md` `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; `docs/product/ai-mcp-contract.md` `161183078034162ca458212e65a47cd17a112394`.
- `docs/queue/implementation-registry.json` `b3ad68c1b04d422a4f1a83cfb9fec6379c6ad08d`, `docs/queue/work-orders/AI-06.md` `df5bb8671fad459e9ca6c0ef7b0061f26d37fe26`.
- `docs/architecture/ai-01-headless-command-kernel.md` `b9c3495de91e38b80c679db6ffc980f31dd76170`; `docs/contracts/ai-01-command-kernel-api.md` `ca0803152773395ac8f2868126d8cf2446fa4062`; `docs/adr/0060-ai-01-shared-semantic-command-kernel.md` `bf0b04c0e0539f081c3f4804daf0b5645db7bc57`.
- `docs/architecture/ai-04-mcp-server-protocol-adapter.md` `3c1cef611c99c8e7c297ad5ea3a92228b953d443`; `docs/contracts/ai-04-mcp-server-contracts.md` `098d9bc2346743000445af3631a1bb700e2b7027`; `docs/adr/0063-ai-04-stateless-mcp-adapter.md` `9e60bfede7052823b7b7906554673f6e2fdf25ce`.
Preflight on each new PR and checkpoint: Git HEAD and critical source object fingerprints. Unexpected change to checkpoint, approved decision, Scope, DoD or Architecture => **STALE**, stop and rebase.

## SCOPE — EXACTLY EIGHT NEW MARKDOWN
1. [AI-06 architecture](../architecture/ai-06-agent-security-authorization.md)
2. [ADR-0065 PROPOSED](../adr/0065-ai-06-agent-grant-consent-policy.md)
3. [Policy technology/license/security matrix](../research/ai-06-auth-technology-license-threat-matrix.md)
4. [Typed policy and authorization API](../contracts/ai-06-authorization-api.md)
5. [Exactly 128 A06 FUTURE tests](../testing/ai-06-acceptance-matrix.md)
6. [Benchmark protocol](../research/ai-06-security-benchmark-protocol.md)
7. This research Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-AI-06.md)

Research PR: exactly these eight NEW Markdown, no code/CI/registry/backlog/checkpoint changes.

## OUT OF SCOPE
Policy runtime, OAuth identity provider/auth server, bearer token, vault credential, operating system sandbox execution, actual agent launcher, native engine edits, service/network listener, model provider, prompt interpretation engine, AI-01 or AI-04 changes, AI-07 transaction code, privileged file/network/shell access, production credentials, external reviewer, paid CI, unapproved open source license, automatic retroactive rollback, CodeRabbit, force push or branch protection bypass.

## FILES / SOURCES TO READ
Canonical source files and object OIDs above; AI-01 command API/ADR, AI-04 transport API/ADR, future AI-06 blocked WO, AI-03 capability introspection and AI-05 context integration only for boundaries, local audit/test policies. Primary external MCP 2026 Authorization/Security Best Practices, OWASP Agentic Top 10 2026, Cedar/OPA docs and licenses, Windows AppContainer, macOS App Sandbox, Linux Landlock and Wasmtime/WASI documentation; exact versions/license review before future adoption.

## REQUIREMENTS
GOV-001..005, CAP-010/013/014/016 and NFR-002..005 as applicable; product NLE-D015/018. Catalog AI-06 must prove **no modification of files/projects outside scope**. P00 risk LOW documentary; future privileged agent authorization/identity/sandbox **HIGH_ASSURANCE**. License NLE-D009 remains OPEN.

## ARCHITECTURE RULES
- Formal deps **AI-04 + AI-01 only**; AI-04 authenticates transport, AI-01 owns CommandId/typed owner dispatch/commit, AI-06 only policy grants/consent/audit.
- Deny by default, explicit deny overrides, attenuated delegation and monotonic revocation; no implicit trust in model/tool annotation/clientInfo or chat confirmation.
- HTTP verified issuer/audience/resource/scopes with no token passthrough; local stdio independently verifies OS peer and workspace selection. Per-request identity even with modern MCP statelessness.
- Owner PEP rechecks grants/source revision/approval at actual commit, not just AI-06 policy ALLOW.
- Trusted UI one-use plan-and-revision-bound consent for destructive, exporting and irreversible operations; MRTR text is not approval.
- OS sandbox defense in depth for untrusted code; unavailable mandatory confinement blocks launch, never silently runs unsandboxed.
- No raw path/host shell or network access; canonical ProjectId/AssetId/OS handles, anti-TOCTOU, symlink, junction and UNC tests.
- Redacted/tamper-evident audit as future candidate, no secret exposure or false guarantees.
- Cedar/OPA/custom policy decision and sandbox runtime remain **candidates only**, exact version/license/SBOM/CVE/benchmark owner gate.
- No code/ADR adoption or implementation WO unlock; all 80 remain BLOCKED, executor_ready=false, approved_adr=null, release class UNDECIDED.

## CONSTRAINTS
No invented security controls/test executions/latency/host certification. Audit changes against Source Pack and DoD. No use of external reviewer/service or expenses. No HIGH/CRITICAL advancement. Engine remains NOT IMPLEMENTED.

## ACCEPTANCE CRITERIA
- [ ] Exactly 8 NEW Markdown, no unrelated code, registry, checkpoint or CI changes in research PR.
- [ ] ADR-0065 PROPOSED; formal deps AI-04+AI-01; future code #80 OPEN/BLOCKED.
- [ ] Research covers identities, scoped grant issue/attenuation/revoke, consent and trusted UI, owner PEP, MCP OAuth/stdi0, sandbox Windows/Linux/macOS/WASM, prompt injection, audit and licensing.
- [ ] Exactly 128 unique A06-T001..A06-T128 FUTURE/NOT EXECUTED, 8 groups of 16 and independently measurable negative OS/owner oracles.
- [ ] Benchmark protocol without invented thresholds.
- [ ] Exact HEAD Docs Validation SUCCESS; objective pt-BR audit APPROVED with no HIGH/CRITICAL; normal squash and main readback.
- [ ] Independent five-file checkpoint PR changes ONLY checkpoint, backlog, registry, research WO and Evidence. Sole registry AI-06 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED; own CI/audit/squash/readback. Target **62/80 researched (77.5%), 18 pending, 80/80 implementation WOs BLOCKED, zero engine**.
- [ ] Close research issue #301 only after checkpoint readback, leave future code #80 OPEN/BLOCKED. Historical closeout four Markdown with own gates before AI-07.

## TESTS
P00: python3 scripts/validate_docs.py, python3 scripts/validate_module_catalog.py, python3 scripts/validate_wo_registry.py, selector CORE-01 rejection exit 2 via python3 scripts/select_wo.py CORE-01 --json, verified GitHub Docs Validation exact PR HEAD and underlying jobs. Future A06 tests and official MCP conformance NOT EXECUTED; future OS security and policy library benchmarks NOT EXECUTED.

## DELIVERABLES
Eight research docs + issue, ADR-0065 PROPOSED, 128 future tests, benchmark, Evidence Bundle, PR/CI/audit/readback, independent checkpoint PR and factual closeout. None authorizes code.

## REVIEW FORMAT
Pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED with base/head, scope diff, exact files and 128 IDs, CI run/job/steps, dependency/permissions/consent/sandbox/security threats, license/risks, checkpoint delta, merge commit and main/registry readback.

## STOP CONDITION
STALE source, wrong DAG or approved decision, invalid local links, unverified license/runtime, missing future tests, policy model fail-open, missing high-risk consent, unsafe path escape, unauthorized scope, CI failure, HIGH/CRITICAL, false implementation claim or unlocked code packet. Do not start AI-07 until AI-06 is factually closed.

## Research PR #302: exact-head CI, audit, squash and main readback verified
- [Research PR #302](https://github.com/KayzenRoot/stormline/pull/302) BASE `886f8c8687c4c79a18a3cb3b7e82a26a054eb656`, final HEAD `e3a4b601ac8675beb81420d900121fff09a6b190`, exactly eight NEW Markdown, no code/CI/registry/checkpoint/backlog. [Docs Validation #43774594592](https://github.com/KayzenRoot/stormline/actions/runs/43774594592) SUCCESS job #132997880558 (Source Pack/local links, 80-module DAG, registry, blocked Zcode selector); [objective pt-BR audit #6903130775](https://github.com/KayzenRoot/stormline/pull/302#issuecomment-6903130775) APPROVED DOCUMEN­TARY ONLY; normal squash/main/readback `c4ddd6d8c42ce250e043423457de17f2567a0e0a`. Research issue [#301](https://github.com/KayzenRoot/stormline/issues/301) remains OPEN pending independent checkpoint; future code [#80](https://github.com/KayzenRoot/stormline/issues/80) OPEN/BLOCKED.
- 128 A06 FUTURE/NOT EXECUTED. **Após checkpoint auditado (proposta até CI/readback): 62/80 pesquisas documentadas (77,5%), 18 pendentes, zero engine, todos 80/80 WOs de código BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class=UNDECIDED.** ADR-0065 PROPOSED, NLE-D009 OPEN, exactly 128 A06 tests FUTURE/NOT EXECUTED, 0 native security tests and no OS sandbox/identity/consent service implemented. Independent checkpoint changes five files only and only AI-06 research_status within registry. Own CI/audit/squash/readback PENDING; research #301 OPEN until checkpoint proof, code #80 OPEN/BLOCKED.

## Checkpoint #303 factual main readback VERIFIED; closeout history
- [Research PR #302](https://github.com/KayzenRoot/stormline/pull/302) BASE `886f8c8687c4c79a18a3cb3b7e82a26a054eb656`, HEAD `e3a4b601ac8675beb81420d900121fff09a6b190`, exactly eight new Markdown. [Docs Validation #43774594592](https://github.com/KayzenRoot/stormline/actions/runs/43774594592) SUCCESS job #132997880558, [pt-BR audit #6903130775](https://github.com/KayzenRoot/stormline/pull/302#issuecomment-6903130775) APPROVED documentary only, normal squash/main `c4ddd6d8c42ce250e043423457de17f2567a0e0a`.
- [Checkpoint PR #303](https://github.com/KayzenRoot/stormline/pull/303) BASE `c4ddd6d8c42ce250e043423457de17f2567a0e0a`, HEAD `48d26f0c5a6a9c59a4574e6887a7b9a77a8d69d0`, exactly five modified files; **sole registry AI-06 research_status** RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED. [Docs Validation #43774777952](https://github.com/KayzenRoot/stormline/actions/runs/43774777952) SUCCESS job #132998493352, [pt-BR audit #6903151592](https://github.com/KayzenRoot/stormline/pull/303#issuecomment-6903151592) APPROVED documentary; normal squash/main `9b74803b6a2123d703f07237ad759f047aa96feb`, [factual readback #6903156503](https://github.com/KayzenRoot/stormline/pull/303#issuecomment-6903156503).
- [Research issue #301](https://github.com/KayzenRoot/stormline/issues/301) CLOSED after checkpoint proof; [future code #80](https://github.com/KayzenRoot/stormline/issues/80) OPEN/BLOCKED. Registry **62/80 researched (77.5%), 18 pending, zero engine, all 80/80 coding WOs BLOCKED, 0 executor_ready, 0 approved_adr, all release_class=UNDECIDED**. ADR-0065 PROPOSED; NLE-D009 OPEN, all 128 A06 tests FUTURE/NOT EXECUTED. No granted identity, policy evaluator, trusted consent, OS sandbox, security test, host conformance or benchmark implemented.
- Next catalog research **AI-07 Transactional Planning & Undo**, order **63/80**, formal dependencies **AI-01 + AI-06**. This historical closeout changes only four Markdown, no registry or code, and requires own Docs CI/audit/squash/main readback before next module.

