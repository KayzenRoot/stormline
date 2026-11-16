# NLE-P00-WO-002-AI-08 — AI Authoring Workflows P00 Research Work Order

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | [research #309](https://github.com/KayzenRoot/stormline/issues/309) | NLE-P00-WO-002-AI-08 | [future code #82](https://github.com/KayzenRoot/stormline/issues/82) OPEN/BLOCKED | BASE `55250c21f834067524014bdb70eedcdddbf6949e`.** Formal deps AI-05 + AI-07 only; ADR-0067 PROPOSED; 63/80 research at baseline; 80/80 future code packets BLOCKED; engine false, NLE-D009 license OPEN.

**Research [#309](https://github.com/KayzenRoot/stormline/issues/309) OPEN**, catalog order **64/80**, formal dependencies **AI-05 + AI-07 ONLY**, both research-only with ADRs 0064/0066 PROPOSED; future code [#82](https://github.com/KayzenRoot/stormline/issues/82) OPEN/BLOCKED. P00 documentation LOW; later privileged autonomous authoring/target export HIGH_ASSURANCE.

## OBJECTIVE
Research and specify model-neutral, declarative, versioned, bounded, source-proven authoring recipes for complete 2D/3D scenes, material/shader, VFX, audio, gameplay script/behavior, localized UI, repair and export, using AI-05 authorized context and AI-07 owner-backed transactional Changesets. Catalog acceptance **"Cenários completos gerados por tool calls com zero edição manual obrigatória."** Require owner-verified source/target fixture outcomes without human scene edits, while never bypassing actual human consent for high-risk actions.

## CONTEXT / SOURCE CHECK
Canonical precedence: approved checkpoint > Decisions Ledger/ADRs > Scope > DoD > Architecture > Requirements > remaining. Live requested Git HEAD `55250c21f834067524014bdb70eedcdddbf6949e` matches main, zero open PRs before research branch. Registry 80 modules, **63/80 research documented, 17 pending, 80/80 future implementation WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=null, release_class=UNDECIDED for all, engine_implemented=false**. AI-08 research_status RESEARCH_PENDING, future code issue #82 OPEN/BLOCKED. NLE-D009 engine license OPEN, NLE-D015 AI-native owner-directed, D018 routine documentary delegation, D019 prepare blocked WOs before code.

## CONTEXT LOCK (Git blob SHA-1 OIDs, NOT raw SHA-256)
- `AGENTS.md` `3e57b719f8651407879ebb641707a048773ea4c2`; `docs/00-source-hierarchy.md` `58a377bc76cafdd3377d733d4f30ef53661bb034`; `docs/11-checkpoint.md` `b58ba0cf740702762a79da30606c15f2c091d16b`; `docs/10-decisions-ledger.md` `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`.
- `docs/03-scope.md` `4ef605c74632ece080b2650e37dd83a415b63310`; `docs/09-definition-of-done.md` `160b3054db9ea1961308934b401488b838d24c3e`; `docs/04-architecture.md` `df62574cb3956c3ac9881631a4cf66be4e1abff1`; `docs/02-requirements.md` `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`.
- `docs/product/module-catalog.md` `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; `docs/product/ai-mcp-contract.md` `161183078034162ca458212e65a47cd17a112394`; `docs/queue/implementation-registry.json` `bec09b791505177b766f4a729e04ae3da0a4837c`; `docs/queue/work-orders/AI-08.md` `fe61846e2b886d9d9267f49b2f498f209adada8e`.
- `docs/architecture/ai-05-context-resources-templates.md` `b2e9d32630de4796dc0488ac0cf8b4e316757ba0`; `docs/contracts/ai-05-context-resource-api.md` `6b99214ca71503c83fa1782faa17e97f2c0a5cee`; `docs/adr/0064-ai-05-authorized-context-projections.md` `00fa3b9d0ae929cd3bd2cbde0f57c600dc7909cf`.
- `docs/architecture/ai-07-transactional-planning-undo.md` `0d4b601b080fa61ff704fa85c0dde18661ae8ddf`; `docs/contracts/ai-07-changeset-transaction-api.md` `918c10982477a1220c9880d989f36fae80702426`; `docs/adr/0066-ai-07-recoverable-owner-changesets.md` `b222e576d8d0db1867984f1cbd3817dd32520481`.
Drift in checkpoint, approved decision, Scope, DoD, Architecture or critical fingerprint => **STALE**; stop and rebase/recompile before merge.

## SCOPE: precisely eight NEW Markdown
1. [Architecture](../architecture/ai-08-authoring-workflows.md)
2. [ADR-0067 PROPOSED](../adr/0067-ai-08-declarative-owner-authoring-recipes.md)
3. [Technology/licensing/security matrix](../research/ai-08-workflow-technology-license-threat-matrix.md)
4. [Typed workflow/recipe/receipt API](../contracts/ai-08-authoring-workflow-api.md)
5. [Exactly 128 future scenarios](../testing/ai-08-acceptance-matrix.md)
6. [Benchmark protocol](../research/ai-08-authoring-benchmark-protocol.md)
7. This Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-AI-08.md)

Research PR changes eight new Markdown only, no checkpoint, backlog, registry, GitHub CI, lockfile, SDK, engine code, permissions or source files.

## OUT OF SCOPE
AI-08 runtime, LLM or cloud provider SDK, engine binaries, direct file writes, arbitrary script execution, prompt automation that bypasses consent, unlicensed media, generated proprietary game art/music, actual scene/shader/VFX/audio/scripts/gameplay code, imported or exported playable games, benchmarks, host certification, paid services, source material redistribution, release class approval, 80 packet unlock, force push, history rewrite, CodeRabbit or mandatory external reviewer.

## FILES / SOURCES TO READ
Canonical Source Pack and OIDs above, AI-05/AI-07 architecture/API/ADRs, future AI-08 code WO, AI-01/04/06 ownership boundaries, DATA-02/03/04/05 source and cooker, WORLD-02, GFX-07, VFX, AUDIO, GAME-02/03, EDIT-04 public owner API drafts as integration references. External: official MCP 2026-07-28, Tasks extension and Python SDK support status, OpenUSD layer composition and licenses, glTF 2.0 + extensions, MaterialX nodes, OpenTimelineIO media refs, OWASP Agentic 2026 and exact dependency license gates.

## REQUIREMENTS
GOV-001..005, CAP-010/013/014/016 as applicable, NFR-002..005 and NLE-D015/D017/D018/D019. Model-neutral, typed owner semantic parity for Editor/CLI/MCP; no manual editing in *supported* end-to-end fixture; trusted user consent remains mandatory where risk; quality/cook/source proof never invented.

## ARCHITECTURE RULES
- Formal deps **AI-05 + AI-07 only**, no circular new edge or sneaky direct implementation dependency. AI-05 context read-only and owner-revision scoped; AI-07 only source mutation/transaction/undo via AI-01+AI-06 transitive owner.
- Recipe DAG versioned and deterministic typed parameters, explicit owner module/CommandId schema and target capabilities, no untrusted dynamic eval, shell/network/process or raw file access.
- Classify mandatory vs optional step and unsupported owner; no silent missing shader, VFX, audio, gameplay, UI, target export nor false COMPLETE.
- Source context pins provenance, rights and current grant; out-of-scope resource/PII/external licensed asset forbidden. Revalidate AI-06 at owner effect; consent one-use tied to exact plan and source revision.
- Actual source receipt and owner open/digest required after apply; cook/export/derived/compiled targets have **separate evidence**; AI-07 partial/irreversible guarantee preserved.
- MCP 2026-07-28 optional Tasks extension *only if negotiated and SDK support proven*; MRTR input is not consent. No deprecated sampling as baseline.
- Baseline deterministic static recipe works offline without paid model. LLM/image/audio nondeterminism marked and actual output bytes/rights pinned.
- Target accessibility, Unicode/RTL, security, license/notice, perf and test gates specified but no claims of certified implementation.
- ADR-0067 stays PROPOSED, NLE-D009 OPEN, 80/80 implementation WOs BLOCKED, zero ready/approved, engine_implemented=false.

## CONSTRAINTS / RISK
Documentation-only LOW. Future engine authoring/export involving privileged code and external services HIGH_ASSURANCE. Zero real tests/build/deploy, no benchmark winners/targets or host certifications claimed. No known HIGH/CRITICAL advancement or paid dependencies.

## ACCEPTANCE CRITERIA
- [ ] Eight NEW Markdown exact, valid links/Source Pack, no registry/checkpoint/backlog/source/CI modifications in research PR.
- [ ] ADR-0067 PROPOSED and formal AI-05 + AI-07 only, no decisions overwritten.
- [ ] Threat/license matrix and typed contracts cover complete 2D/3D/material/VFX/audio/script/UI/export workflows, optional task support, owner source/cook and consent.
- [ ] 128 unique ordered A08-T001..A08-T128 FUTURE/NOT EXECUTED, eight groups of sixteen with independent source/OS/target oracles.
- [ ] Benchmark reproducible and does not fabricate numerical performance or engine capability.
- [ ] Exact HEAD Docs Validation SUCCESS; objective pt-BR audit APPROVED, normal squash/main readback, zero HIGH/CRITICAL doc defect.
- [ ] Separate five-file checkpoint PR modifies only checkpoint/backlog/registry/research WO/Evidence and only AI-08 research_status from RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED in registry. Own CI/audit/squash/readback.
- [ ] Checkpoint target **64/80 research documented (80%), 16 pending, engine false, all 80 implementation WOs BLOCKED, zero ready, zero approved ADR, release class 80/80 UNDECIDED**.
- [ ] Research issue #309 CLOSED only after factual checkpoint, future code #82 OPEN/BLOCKED, historical four-Markdown closeout own CI/audit/squash/readback before AI-09.

## TESTS
P00: GitHub Docs Validation exact HEAD, Source Pack/local link checker, taxonomy/DAG 80 modules, registry validator and blocked Zcode selector (e.g. CORE-01). **NOT EXECUTED** future: real 128 A08 tests, owner shader/script, host conformance, 2D/3D/export demos, security/benchmark/compat tests.

## DELIVERABLES
Eight research Markdown, ADR-0067 PROPOSED, typed contracts, threat/license matrix, 128 tests future, benchmark protocol, research PR/CI/audit/squash/readback, separate checkpoint PR with same gates and historical closeout, factual Evidence. No execution code.

## REVIEW FORMAT
Pt-BR verdict APPROVED / CORRECTION REQUIRED / BLOCKED, BASE/HEAD SHA, exact diff/8 files, test uniqueness, CI run/job/steps, owner AI-05/07 boundaries, privacy, security, rights/licenses, no runtime claims, benchmark, Checkpoint Delta proposed, independent PR audits and main readback.

## STOP CONDITION
STALE context, unexpected approved source change, wrong DAG, malformed links/tests, privacy or out-of-scope authority, library adopted silently, unsupported feature marked complete, consent bypass, misleading generated media copyright/perf, CI failure, HIGH/CRITICAL, unlocked code packet, false claim or missing readback. Do not start AI-09 while AI-08 unresolved.
