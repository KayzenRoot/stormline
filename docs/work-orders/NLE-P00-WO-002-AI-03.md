# NLE-P00-WO-002-AI-03 — Capability Registry & Schemas P00 Documentary Research Work Order

**2026-11-15 | P00 RESEARCH ONLY, NOT IMPLEMENTED | [research #289](https://github.com/KayzenRoot/stormline/issues/289) | NLE-P00-WO-002-AI-03 | [future code #77](https://github.com/KayzenRoot/stormline/issues/77) OPEN/BLOCKED | BASE `1db368aa555f7a8eb2fa1a1eb3a38744a23ef6bb`.** 58/80 researched at baseline, 22 pending, zero engine, all 80 implementation packets BLOCKED. Formal dependency **AI-01 ONLY**; ADR-0060 PROPOSED and code #75 OPEN/BLOCKED. NLE-D009 engine license OPEN.

**Research #289**; catalog_order **59/80**; code issue **#77 OPEN/BLOCKED**; at base 58/80 documented (72.5%), 22 pending; zero engine, all 80 code work orders blocked. Formal dependency AI-01 only, ADR-0060 PROPOSED and code #75 OPEN/BLOCKED. Risk docs LOW; future metadata ACL/schema compile ELEVATED, privileged cross-project/remote/invocation HIGH_ASSURANCE separate approval.

## OBJECTIVE
Deep research and document Stormline-owned reflected registry for 100% independently inventoried **approved public authoring operations**, stable CommandId, Draft 2020-12 JSON Schema contracts, versions/deprecation, permission and target-aware discovery, errors, generation publication, UI/CLI/MCP mapping, security, tests and benchmark. Catalog oracle: **"100% das ações públicas de autoria enumeradas e rastreáveis."** No code.

## CONTEXT / SOURCE CHECK
Source precedence checkpoint > Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS > registry/catalog. Main base verified at `1db368aa555f7a8eb2fa1a1eb3a38744a23ef6bb` and no other open PR, stable independent module order 59. Registry 80 entries, 58 RESEARCH_DOCUMENTED_ADR_PROPOSED and 22 RESEARCH_PENDING; AI-03 RESEARCH_PENDING, work_order_status BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null, release_class=UNDECIDED, engine_implemented=false. AI-01 owns all command dispatch and authorization; ADR-0060 PROPOSED, implementation #75 BLOCKED. No registry/schema runtime exists, no license selected (NLE-D009 OPEN). Critical source Git blob object OIDs (Git SHA-1, **not computed SHA-256 bytes**) verified: checkpoint `a8d8c362bc5ac19d965c03f9e965806952b53704`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; registry/checkpoint must be re-read before any write. Mark STALE and stop on changed canonical controls.

## SCOPE — EXACTLY EIGHT NEW MARKDOWN
1. [AI-03 architecture](../architecture/ai-03-capability-registry-schemas.md).
2. [ADR-0062 PROPOSED](../adr/0062-ai-03-authorized-capability-reflection.md).
3. [Technology/license/security matrix](../research/ai-03-schema-technology-license-matrix.md).
4. [Typed API discovery/schema/compat contract](../contracts/ai-03-capability-registry-api.md).
5. [128 unique A03-T001..A03-T128 FUTURE tests](../testing/ai-03-acceptance-matrix.md).
6. [Reproducible benchmark protocol](../research/ai-03-capability-benchmark-protocol.md).
7. This research Work Order.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-AI-03.md).

Research PR changes ONLY these eight NEW Markdown; no registry/backlog/checkpoint/code/CI changes. After **exact-final-HEAD** Docs Validation SUCCESS and objective pt-BR APPROVED, normal squash merge and main readback, create **independent five-file checkpoint PR** updating checkpoint/backlog/registry (SOLE AI-03 `research_status=RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`)/this WO/Evidence. Target 59/80 research documented (73.75%), 21 pending, zero engine. Checkpoint PR independently CI/audit/squash/main readback before closing research #289. Optional independent four-Markdown historical closeout and readback. Do not advance before completion.

## OUT OF SCOPE
Any actual C++/editor/UI/CLI/MCP code, JSON Schema C++ library installation, code generation, owner handler registration, SDK, remote schema resolve, running tests/benchmarks, production docs deployment, changing AI-01 or related module APIs, release class/engine-license adoption, direct VFS/VM/OS access, unapproved capability activation, broad cleanup, CodeRabbit, paid CI, force push or security bypass. AI-03 #77 remains OPEN/BLOCKED; all other 79 future code packets unchanged.

## FILES / SOURCES TO READ
Canonical: `docs/00-source-hierarchy.md`, `docs/11-checkpoint.md`, `docs/10-decisions-ledger.md`, `docs/03-scope.md`, `docs/09-definition-of-done.md`, `docs/04-architecture.md`, `docs/02-requirements.md`, `AGENTS.md`, `docs/product/module-catalog.md`, `docs/product/ai-mcp-contract.md`, `docs/queue/implementation-registry.json`, `docs/queue/work-orders/AI-03.md`. AI-01: `docs/architecture/ai-01-headless-command-kernel.md`, `docs/contracts/ai-01-command-kernel-api.md`, `docs/adr/0060-ai-01-shared-semantic-command-kernel.md`; integrate EDIT-01 buttons, AI-02 read-only index, AI-04 MCP, AI-06 security as non-formal dependents. Primary external spec links in matrix.

## REQUIREMENTS
GOV-001..005, NLE-D013..020, CAP-008/010/011/012/013/014/016, NFR-001..005, source/owner privileges, 100% independent eligible public operation coverage, stable typed versioned descriptions with permission/side-effect/owner and errors. Enumerate blocked/unavailable targets without false claims. Future tests must map to acceptance, risk and platform.

## ARCHITECTURE RULES
Only formal AI-01 dependency. Registry derived from AI-01 owner descriptors, no other executor or authorization root. 2020-12 dialect/allowlisted bounded local refs, no arbitrary remote loads; separate schema syntax from permissions/business invariants; immutable atomic generation with prior-good; publication fails incomplete coverage; actor/project/policy-filtered discovery, revocation and owner-side revalidation; stable namespaced IDs/version/deprecation. MCP tools are AI-04 future projections; do not expose internals or auto-open network services. Release and license OPEN/PROPOSED remain unchanged.

## CONSTRAINTS
Documentation-only LOW. Git blob OIDs listed are not byte SHA-256. Recheck main/fingerprints/PRs before writes and again before independent checkpoint. Free standard GitHub CI only. Never call future tests passed; no invented benchmark numbers; no external reviewer mandatory. Any owner approval, implementation activation or irreversible setting change is out of authorization.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight new Markdown with correct relative links and no code/registry mutation in research PR.
- [ ] ADR-0062 explicitly PROPOSED; AI-01 formal DAG unchanged; all 80 code WOs BLOCKED.
- [ ] Complete catalog/API/schema, permission, compatibility, error, deprecation, reversible publication and primary source license matrix.
- [ ] 128 unique A03-T001..A03-T128 marked FUTURE/NOT EXECUTED (zero passed) with independent 100% coverage oracle.
- [ ] Exact HEAD Docs Validation and validators PASS; evidence of actual HEAD/diff/CI.
- [ ] Objective audit pt-BR APPROVED no HIGH/CRITICAL, squash, main readback.
- [ ] Separate checkpoint five-file PR with **sole AI-03 research status** delta; own exact HEAD CI/audit/squash/readback, research issue closed only after factual proof.
- [ ] If historical closeout required, 4-Markdown independent PR with its own gates before next module.

## TESTS
P00 `python3 scripts/validate_docs.py`; `python3 scripts/validate_module_catalog.py`; `python3 scripts/validate_wo_registry.py`; `python3 scripts/select_wo.py CORE-01 --json` must reject status 2; GitHub Actions Docs Validation exact HEAD. Native schema registry acceptance tests [A03-T001..128](../testing/ai-03-acceptance-matrix.md) FUTURE / NOT EXECUTED. Benchmark protocol only, zero measurements.

## DELIVERABLES
Eight research Markdown, proposed technology/security ADR, exact 128 future tests, reproducible benchmark, PR/evidence/audit/readback, independent checkpoint delta. No executor code activation.

## REVIEW FORMAT
pt-BR: verdict APPROVED/CORRECTION REQUIRED/BLOCKED; base/head, changed files, CI run/job/steps, test count/status, schema/compat/licensing/security, risks, proposed checkpoint delta and postmerge verification.

## STOP CONDITION
Stale source lock, wrong 80 DAG, unexpected files/third-party dependency, unapproved license/permission relaxation, incorrect required/covered denominator, missing test IDs, CI fail, unresolved HIGH/CRITICAL, false claims or implementation unblocked. No next increment during CORRECTION REQUIRED/BLOCKED.

## Research PR #290 — factual verified documentary result
- [PR de pesquisa #290](https://github.com/KayzenRoot/stormline/pull/290) BASE `1db368aa555f7a8eb2fa1a1eb3a38744a23ef6bb`, final HEAD `30d0ecd15c6cdb918a097913b9434b284fd3d50c`, oito novos Markdown e nenhum código/registry/checkpoint/CI; [Docs Validation #43762690154](https://github.com/KayzenRoot/stormline/actions/runs/43762690154) SUCCESS job #132960788029 em HEAD exato (Source Pack/links, DAG, registry, blocked selector); [auditoria pt-BR #6901497461](https://github.com/KayzenRoot/stormline/pull/290#issuecomment-6901497461) APPROVED documental; squash normal/main readback `980824e674be88c4941b6c4d7aa2368c4c4566e9`. exactly 128 future test IDs A03-T001..A03-T128 NOT EXECUTED. Research receipt does not adopt ADR or code. Independent checkpoint PR changes only checkpoint/backlog/registry/WO/Evidence, sole AI-03 research_status. **Após checkpoint auditado**: 59/80 pesquisas documentadas (73,75%), 21/80 pendentes, ZERO engine; 80/80 implementation WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null, release_class=UNDECIDED. ADR-0062 PROPOSED, NLE-D009 OPEN, todos os 128 testes A03 FUTURE/NOT EXECUTED, zero medição runtime. Checkpoint CI/audit/squash/main readback PENDING before issue #289 closure.

## Checkpoint #291 and historical closeout readback VERIFIED
- [Checkpoint PR #291](https://github.com/KayzenRoot/stormline/pull/291) BASE `980824e674be88c4941b6c4d7aa2368c4c4566e9`, HEAD final `bebe206678aac491fd40cffee7c1c37806ce0808`, exatos **5 arquivos modificados**; diff registry comprova **única** mudança AI-03 `research_status=RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`. [Docs Validation #43763148722](https://github.com/KayzenRoot/stormline/actions/runs/43763148722) SUCCESS job #132962210233 com Source Pack/links, DAG, registry e blocked selector PASS; [audit pt-BR #6901552400](https://github.com/KayzenRoot/stormline/pull/291#issuecomment-6901552400) APPROVED documentary only. Squash normal e main/readback `ee9ab999c097c24ec0ae4d3bc2cf9d9127a569ae` idênticos, [readback #6901560095](https://github.com/KayzenRoot/stormline/pull/291#issuecomment-6901560095).
- [Research #289](https://github.com/KayzenRoot/stormline/issues/289) CLOSED somente após prova; futuro código [#77](https://github.com/KayzenRoot/stormline/issues/77) OPEN/BLOCKED; AI-01 predecessor #75 OPEN/BLOCKED. **Estado canônico 59/80 pesquisas (73,75%), 21 pendentes, ZERO engine**, 80/80 implementation WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, executor_ready=false, approved_adr=null, release_class=UNDECIDED, ADR-0062 PROPOSED e NLE-D009 OPEN. Exatos 128 `A03-T001..128` FUTURE/NOT EXECUTED, sem implementação ou benchmark.
- Próxima pesquisa canônica **AI-04 MCP Server & Protocol Adapter**, ordem **60/80**, dependência formal **AI-03** exclusivamente. Nenhuma implementação autorizada. Este histórico de closeout altera **apenas quatro Markdown** (checkpoint/backlog/WO/Evidence) com CI/auditoria/squash/readback independentes antes do próximo Source Check.

