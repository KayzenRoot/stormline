# NLE-P00-WO-002-BIZ-01 — Commercial Licensing & Compliance: Research Work Order

**2026-11-16 · P00 DOCUMENTARY RESEARCH ONLY · [research #362](https://github.com/KayzenRoot/stormline/issues/362) OPEN until independently validated checkpoint · [future coding #95](https://github.com/KayzenRoot/stormline/issues/95) OPEN/BLOCKED.** BASE main 81aded1f42dffd9a7f36f0c3fd30a3168db15344, 77/80 catalog, QA-05 sole formal dependency and ADR-0079 PROPOSED. Baseline 76/80 research documented, 4 pending, all 80/80 coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, 0 ready, 0 approved ADR, releases UNDECIDED, engine_implemented=false; source license NLE-D009 OPEN.

**Risk LOW documentary, future legal/release and privacy HIGH_ASSURANCE for consequential actions.** Qualified counsel not replaced by automated scan. No purchase, release or legal instrument approved.

## OBJECTIVE
Investigate original engine/source/runtime license strategy, open-source vs source-available vs proprietary, paid/royalty-free/royalty models, personal and commercial use, sublicensing, creator asset/IP carve-out, patents/trademarks, OSS/transitive SPDX/NOTICE, fonts/shaders/SDK/source offers, AI generated output/provenance, global LGPD/GDPR/privacy/telemetry, accessibility, app distribution/consumer terms, export control, risk/cost and reproducible legal rights evidence; propose ADR-0080 and 128 tests without ratification.

## CONTEXT / SOURCE CHECK
Use source priority Checkpoint > Decisions Ledger/approved ADR > Scope > DoD > Architecture > Requirements > other references. Observed main 81aded1f42dffd9a7f36f0c3fd30a3168db15344, public docs-only repository, 0 open PR at source check; official repo README says license PENDING, no engine code, alpha, export or SDK. Catalog BIZ-01 77/80 formal **QA-05 ONLY**; predecessor [ADR-0079](../adr/0079-qa-05-platform-compatibility-qualification-policy.md) PROPOSED and [QA-05 evidence API](../contracts/qa-05-qualification-evidence-api.md) conceptual; NLE-D009 source license OPEN, NLE-D010 trademark clearance OPEN, D013 no public MVP, D014 planned 2D/2.5D/3D/Web, D017 native desktop Windows/Linux/macOS, D018 safe documentary autonomy, D019/020 blocked 80 queue. No third-party engine code released, no rights audit of binaries possible.

## CONTEXT LOCK
Source commit 81aded1f42dffd9a7f36f0c3fd30a3168db15344. Git object SHAs are SHA-1 BLOB IDs, **not SHA256 of raw bytes**. Future Zcode must compute real SHA-256 content fingerprints before implementation, rebuild lock when canonical sources change:
- AGENTS.md; docs/00-source-hierarchy.md; docs/11-checkpoint.md; docs/10-decisions-ledger.md; docs/03-scope.md; docs/09-definition-of-done.md; docs/04-architecture.md; docs/02-requirements.md; docs/product/module-catalog.md
- docs/queue/implementation-registry.json; docs/queue/work-orders/BIZ-01.md; docs/queue/work-orders/QA-05.md
- docs/adr/0079-qa-05-platform-compatibility-qualification-policy.md; docs/contracts/qa-05-qualification-evidence-api.md; .github/workflows/docs.yml
- Fingerprints from observed Git blobs to be maintained as evidence; if main SHA/Scope/DoD/approved ADR changes => **STALE**, rebase and re-audit.

## SCOPE — NECESSARY (exactly EIGHT NEW Markdown files)
1. [Architecture](../architecture/biz-01-commercial-licensing-compliance.md)
2. [ADR-0080 PROPOSED](../adr/0080-biz-01-rights-compliance-policy.md)
3. [2026 legal/license/SPDX/privacy/global matrix](../research/biz-01-licensing-rights-regulatory-matrix.md)
4. [Typed semantic rights/privacy evidence API](../contracts/biz-01-license-compliance-evidence-api.md)
5. [128 FUTURE B01 acceptance cases](../testing/biz-01-acceptance-matrix.md)
6. [Future rights/compliance audit protocol](../research/biz-01-rights-compliance-audit-protocol.md)
7. This research Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-BIZ-01.md)

Research PR adds only these 8 Markdown, no prior Source Pack/checkpoint/backlog/registry/code/CI/license changes. **After research APPROVED**, independently audit checkpoint PR (five modified files, sole semantic BIZ-01 research_status delta), close research issue only after readback, then final factual historical PR with four modified docs.

## OUT OF SCOPE
No public LICENSE, EULA, royalty rate/scheme activation, legal contract, privacy policy live publication, trademark application, patent opinion, signed DPA, actual code scanner, games, C++, SDK, shader/font upload, vendor account, telemetry, personal data processing, payments, stores, MSI/DMG/AppImage, software release, build, deploy, attorney expense, refactor, dependency edits or external review requirement. Do not unlock implementation issue #95 or any other coding packet.

## FILES/SOURCES TO READ
Canonical sources/context lock and prior [QA-05 architecture](../architecture/qa-05-compatibility-release-qualification.md), its [ADR](../adr/0079-qa-05-platform-compatibility-qualification-policy.md), [API](../contracts/qa-05-qualification-evidence-api.md), current [BIZ-01 blocked future WO](../queue/work-orders/BIZ-01.md); official [OSI](https://opensource.org/osd), [SPDX](https://spdx.org/licenses/), [FSF GPL FAQ](https://www.gnu.org/licenses/gpl-faq.html), [OFL](https://openfontlicense.org/ofl-faq/), [ORT](https://github.com/oss-review-toolkit/ort), [ANPD](https://www.gov.br/anpd/pt-br/assuntos/assuntos-internacionais/transferencia-internacional-de-dados), [GDPR](https://eur-lex.europa.eu/eli/reg/2016/679/oj/eng/), [W3C WCAG](https://www.w3.org/TR/wcag/), [Creative Commons](https://creativecommons.org/share-your-work/cclicenses/). Recheck actual upstream versions and jurisdictional rules when executing.

## REQUIREMENTS
Catalog acceptance: "Licença aprovada e publicável, direitos de dependências/assets auditados" is **future product acceptance**, not satisfied by P00. Preserve GOV-001..005, no MVP, owner rights; privacy/consent, creator content and manifest obligations must be explicit. Risks unknown -> BLOCKED, no fake legal approval.

## ARCHITECTURE RULES
Versioned rights graph and creator-asset separation, upstream SPDX with OR/AND/WITH, artifact-level file and transitive closure, explicit NOTICE/source offer, account for static/dynamic code and SDK/font/content exceptions. Local-first telemetry off until lawful basis and opt-in when required; no user assets in public CI/AI. QA-05-only formal predecessor; other PLAT-05/QA-04/DATA/AI modules integration/transitive contracts. Editor/CLI/MCP view/propose only; privilege to ratify legal grant belongs owner/counsel.

## CONSTRAINTS
R$0 routine docs CI, no CodeRabbit, no mandatory outside human code reviewer, no force-push/bypass, no unapproved fees, no new product license from proposal; legal counsel advice required before real commercial launch. Risk LOW planning, HIGH_ASSURANCE future contract/publication/payment/personal data processing.

## ACCEPTANCE CRITERIA
- [ ] Exactly 8 new Markdown, ADR-0080 PROPOSED, formal QA-05 only and no approved license/royalties.
- [ ] All 128 B01-T001..B01-T128 unique FUTURE/NOT EXECUTED, no PASS.
- [ ] Detailed legal tech/research/source references, coherent API and legal gates, creator IP/embedded runtime separation.
- [ ] Git exact-head Docs Validation SUCCESS, 80 blocked registry still unchanged.
- [ ] Evidence SHA/diff/results, pt-BR audit APPROVED without HIGH/CRITICAL, normal squash and main readback.
- [ ] Separate checkpoint CI/audit/squash/readback, only BIZ-01 registry research_status delta; future code remains BLOCKED.
- [ ] History closeout later four Markdown only; no fictitious legal certification or source license decision.

## TESTS
Current executable checks: GitHub Docs Validation from .github/workflows/docs.yml validates canonical links/catalog/DAG/80 WO registry/selector BLOCKED. All 128 B01 tests future and NOT EXECUTED. No native compile/legal auditor or paid SaaS used.

## DELIVERABLES
Eight research docs in tracked branch/PR, direct primary source links, 128 planned test oracles, R$0 constraints, evidence/diff, proposed checkpoint delta, objective pt-BR review, eventual separate checkpoint/history PRs.

## REVIEW FORMAT
Português brasileiro: APPROVED / CORRECTION REQUIRED / BLOCKED; exact SHA, scope/diff, issue, tests/CI real proof, legal and privacy rights concerns, HIGH/CRITICAL, costs/risks, checkpoint proposal and explicit NO license ratification.

## STOP CONDITION
STOP for source STALE, failed CI, rights or privacy defect HIGH/CRITICAL, unapproved irreversible license/royalty, generated secrets/PII, unauthorized scope/expense, unverified dependencies or attempt to unblock implementation.

## CHECKPOINT DELTA (PROPOSAL ONLY)
After research merge and readback, modify checkpoint, backlog, registry, future BIZ-01 WO and evidence in independent PR; **sole semantic registry change BIZ-01 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED**. Other 79 full module records and root fields unchanged. Target 77/80 researched, 3 pending, 80/80 coding BLOCKED, 0 ready/approved ADR, release classes UNDECIDED, engine=false, source license OPEN. QA-05 PROPOSED. No self-promotion by executor.
