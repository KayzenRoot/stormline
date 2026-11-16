# NLE-P00-WO-002-BIZ-03 — Release, Installer & Lifecycle Research Work Order

**P00 DOCUMENTARY ONLY | 2026-11-16 | [issue #370](https://github.com/KayzenRoot/stormline/issues/370) | future coding [#97](https://github.com/KayzenRoot/stormline/issues/97) OPEN/BLOCKED.** Main BASE `3d2ad393ab4b70460e7d5cb46f82e03d2f5c9935`. BIZ-03 registry `catalog_order=79` (zero-based last of 80), formal dependencies **PLAT-05 + BIZ-01 + QA-04 ONLY**, ADR-0074/0080/0078 PROPOSED. Baseline 78/80 researched, 2 pending **BIZ-03 + CORE-04**, 80/80 code WOs BLOCKED, executor_ready=0, approved_adr=0, release classes UNDECIDED, engine_implemented=false, engine NLE-D009 source license OPEN, no public MVP.

## OBJECTIVE
Source-checked, officially researched secure native Windows/Linux/macOS release/installer lifecycle and Web publication where applicable, signing/notarization and OS store rules, cryptographically authenticated full/delta updates, channel staging, rollback and crash recovery, app vs creator project/save schema migrations, source and license rights, supply-chain attestation/SBOM, shipped SDK/runtime/sample rights, opt-in crash reports, privacy/a11y, min supported OS/CPU/GPU, R$0 CI, independent QA/hardware, incident maintenance with 128 FUTURE tests; NO software released.

## SOURCE CHECK / CONTEXT LOCK
GitHub main at `3d2ad393ab4b70460e7d5cb46f82e03d2f5c9935`, 80 registry records, 78 research documented, 2 pending CORE-04 and BIZ-03, all 80 future coding blocked, no open PR at start. Checked canonical order checkpoint > Decisions Ledger/approved ADR > Scope > DoD > Architecture > Requirements > other. Critical Git blob SHA-1 object IDs **NOT raw SHA-256** (future coding executor must compute actual SHA-256 before implementing and rebase STALE if any critical source changes):
- `docs/11-checkpoint.md` `69c607cba61527f22b14b216a887bb18bda1e1e2`
- `docs/10-decisions-ledger.md` `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md` `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md` `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md` `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- `docs/02-requirements.md` `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/product/module-catalog.md` `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- `docs/queue/implementation-registry.json` `bae495233c8c92ebb8765adcc76674b4aa29d76e`
- `docs/queue/work-orders/BIZ-03.md` `c2b8a33c637c7110d1095b467ea074e9524e0115`
- `docs/adr/0074-plat-05-reproducible-export-release-policy.md` `b9ad6bbfc9cd4434d83167f03c73e50307aedfea`
- `docs/adr/0080-biz-01-rights-compliance-policy.md` `64fc3e985e9b977d84950f6d0a2ab4e95bd79431`
- `docs/adr/0078-qa-04-security-gates-fuzz-sbom-provenance-policy.md` `beca4a5e542339ad510873ba2ade379271b5794f`
- `docs/contracts/plat-05-export-release-api.md` `764713955d50ca963db76ffc9a7281aba9bb6259`
- `docs/contracts/qa-04-security-evidence-api.md` `acb0c73412a9743577da3bfd1b0011f5328888e5`
- `AGENTS.md` `3e57b719f8651407879ebb641707a048773ea4c2`
- `.github/workflows/docs.yml` `cbbaf5731de75f1de4bdf8cad6489e6d73681d71`

## SCOPE — eight NEW Markdown only in research PR
1. [Proposed architecture](../architecture/biz-03-release-installer-lifecycle.md)
2. [ADR-0082 PROPOSED](../adr/0082-biz-03-release-update-trust-policy.md)
3. [Primary upstream official technology and license matrix](../research/biz-03-installer-updater-security-licenses-matrix.md)
4. [Typed lifecycle versioned contracts](../contracts/biz-03-release-lifecycle-api.md)
5. [128 unique future tests B03-T001..B03-T128](../testing/biz-03-acceptance-matrix.md)
6. [Failure/benchmark protocol](../research/biz-03-release-fault-injection-benchmark-protocol.md)
7. This research Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-BIZ-03.md)

No existing file edits for research PR; no code, binaries, git workflow, Source Pack/checkpoint/registry/ADR older/CI/licenses. Independent five-file checkpoint only AFTER research CI/audit/squash/readback. Then close research issue, independently audit four-Markdown historical PR.

## OUT OF SCOPE
Actual installer or release distribution, Windows/macOS certificate acquisition, Apple Developer fee, notarization signing, CDN/storage, changing license/terms/sales, third-party private SDKs, package downloads, building native engine/GPU, real game samples or save migration, telemetry collection, user data, server/network service, exploit reproduction, real fuzz/penetration scan, changing any of 80 blocked future code packets to ready, CodeRabbit, paid CI, forced push/destructive Git, public MVP, extra formal DAG edges, project-wide cleanup.

## FILES / SOURCES
Above Context Lock and linked [PLAT-05 release API](../contracts/plat-05-export-release-api.md), [QA-04 evidence API](../contracts/qa-04-security-evidence-api.md), [BIZ-01 rights architecture](../architecture/biz-01-commercial-licensing-compliance.md); Apple notarization/Developer ID, Microsoft Store MSIX vs MSI/EXE, The Update Framework, SLSA v1.2, GitHub artifact attestations, SBOM, Sparkle and OS package manager documentation with pinned future versions/licenses.

## REQUIREMENTS
Catalog BIZ-03 acceptance exactly **Instalar/exportar/atualizar/reverter em ambientes-alvo sem intervenção de dev.** Governance GOV-001..005; NLE-D009 OPEN, D013 full 1.0 no MVP, D014 2D/2.5D/3D/Web, D015 gated AI/MCP, D017 native Windows/Linux/macOS, D018 solo documentary integrations but no paid/irreversible, D019/020 all future WOs blocked. Distinguish app release vs creator rights/SDK and all transitive runtime licenses.

## ARCHITECTURE RULES
BIZ-03 publishes/channel-manages **PLAT-05 immutable exports**, consumes **BIZ-01 rights/licensing approval** and **QA-04 independently verified security/provenance**. Never duplicate PLAT-05 cooking, DATA migration ownership or security bypass. TUF-style threshold signed feed anti-rollback/freeze/mixmatch, full digest after delta, OS package manager signing, rollback app separated from save/project migrations with explicit backup/consent. Crash telemetry disabled by default. Public release prohibited until all complete v1.0 DoD gates and owner approval.

## CONSTRAINTS
No code/tool/library dependency added, no unverified OS/hardware compatibility, no self-approval. Docs CI must green at exact-head before audit, then normal squash with readback. No new paid service, CodeRabbit, forced push, branch protection bypass, unexpected private data/secrets. Treat future privileged updaters/keys/data loss as HIGH_ASSURANCE.

## ACCEPTANCE CRITERIA
- [ ] Exactly 8 NEW Markdown, ADR-0082 PROPOSED, formal PLAT-05+BIZ-01+QA-04 ONLY, 128 unique tests FUTURE/NOT EXECUTED zero PASS.
- [ ] Primary-source technology, signing requirements, legal NLE-D009 OPEN, TUF updater security, immutable release channel and supply chain, migration/rollback data integrity, privacy/a11y and R$0 hardware limits, no exaggerated claims.
- [ ] Exact research PR CI Docs Validation all existing four checks SUCCESS; objective pt-BR audit no HIGH/CRITICAL, normal squash and main readback.
- [ ] Independent 5 MODIFIED checkpoint (checkpoint/backlog/registry/blocked BIZ-03 code WO/Evidence) with **SOLE semantic registry BIZ-03 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED**; other 79 records/root untouched, 79/80 researched and CORE-04 pending.
- [ ] Independent checkpoint CI/audit/squash/main readback, then close research #370; code #97 stays OPEN/BLOCKED and all 80 coding WOs blocked.
- [ ] Separate 4 MODIFIED historical closure (checkpoint/backlog/blocked BIZ-03 code WO/Evidence) with own CI/audit/squash/main readback. Never claim full 80/80 research while CORE-04 registry is still pending.

## TESTS
Current P00 Docs Validation `python3 scripts/validate_docs.py`, `python3 scripts/validate_module_catalog.py`, `python3 scripts/validate_wo_registry.py`, and negative `python3 scripts/select_wo.py BIZ-03` (future coding BLOCKED), verified via GitHub Actions; no actual compiler/signer/installer/OS/browser support tests. Exactly 128 `B03-T001..B03-T128` future cases not run; neither proof of release correctness nor legal clearance.

## DELIVERABLES
Research issue, 8 Markdown with source locked references, proposed ADR and typed contracts, 128 future test matrix, benchmark and audit plan, Evidence; PR research+CI+pt-BR APPROVED audit+squash+readback, independent checkpoint 5 modified and historical 4 modified each audited/read back, next module suggestion CORE-04 research-status reconciliation.

## REVIEW FORMAT
Português brasileiro verdict APPROVED / CORRECTION REQUIRED / BLOCKED, exact base/head/diff/CI run/job, docs links and DAG validation, future tests count/status, security/ownership/licensing/OS platform review, code issue status, checkpoint delta, stop conditions and reproducible readback.

## STOP CONDITION
STALE checkpoint/Scope/DoD/approved ADR, extra formal dependency, unapproved rights/account/expense/auto-publication/telemetry, unsafe signed update/downloader, data loss, missing real QA/OS platform for product release, failed CI, any known HIGH/CRITICAL, attempt to activate Zcode or drifted registry. Research approval never flips code ready.

## CHECKPOINT DELTA PROPOSED, NOT SELF-APPROVED
After research observed merger: checkpoint/backlog/registry/future blocked WO/Evidence, only BIZ-03 `research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, count **79/80** researches, remaining **CORE-04** pending (already a historical proposed ADR-0006 and research PR #100, but status pending, requiring SOURCE CHECK and reconciliation rather than blind duplicate research), 80/80 code WOs blocked, zero ready/approved ADR, engine false, license OPEN. Catalog order zero-based 0..79; BIZ-03 catalog_order=79, not a "79th of 80" in human ordinal.
