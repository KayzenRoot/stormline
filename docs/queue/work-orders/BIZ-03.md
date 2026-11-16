# NLE-EXEC-WO-BIZ-03-001 — Release, Installer & Lifecycle

**Status:** BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS | **Release class:** UNDECIDED | **Risk:** TBD. Not ready for execution.

## OBJECTIVE
Implement the first necessary and independently testable increment for Release, Installer & Lifecycle, only after the planner approves technology, contracts, measurable DoD, file paths and dependency evidence.

## CONTEXT
Stormline is an original AI-native 2D/2.5D/3D/Web game engine with Windows/Linux/macOS Editor + exported games. No public MVP; engine code not started. This packet derives from approved candidate module `BIZ-03` but is NOT approved code scope.

## DEPENDENCIES
`PLAT-05`, `BIZ-01`, `QA-04`. All blocking dependencies must have approved interfaces and merged evidence.

## SCOPE
Candidate capability: Installer/updates, samples originais, crash reports opt-in, rollback e suporte de manutenção.
Exact implementation slice and requirements, public APIs, data model, files and constraints: **TBD BY PLANNER AFTER TECHNICAL ADR**.

## OUT OF SCOPE
Unapproved features or architecture, related-module code, unsanctioned imports, broad cleanup, paid CI, CodeRabbit, mandatory external human reviewer, bypass/force push and public unfinished release.

## FILES / SOURCES TO READ
Checkpoint, Decisions Ledger/approved ADRs, Scope, Definition of Done, Architecture, Requirements, AGENTS, module catalog, approved per-module technical specification and actual target source files (TBD). Respect canonical priority and read only relevant context.

## REQUIREMENTS
GOV-001..005, relevant CAP/NFR entries, NLE-D013..018; complete requirement-to-test mapping TBD before activation.

## ARCHITECTURE RULES
Preserve native core/editor/server isolation and explicit ownership. Typed contracts, validation, error handling, data/version migration, platform performance tiers, security. Public authoring operations should be available through controlled Editor/CLI/MCP; no unsafe internals exposed.

## CONSTRAINTS
No unverified stack or invented results; free public CI; no CodeRabbit, paid subscription, force push or bypass. Zcode cannot choose product architecture, legal license, 1.0 release class or definitive benchmarks.

## ACCEPTANCE CRITERIA
- [ ] Owner-approved ADR/technology versions/licenses, exact interfaces/data contracts, release class, risk, Scope and DoD
- [ ] Dependency status APPROVED / MERGED; fresh base SHA and fingerprints
- [ ] Catalog verification: Instalar/exportar/atualizar/reverter em ambientes-alvo sem intervenção de dev.
- [ ] Functional, unit, integration, failure, security and regression tests passed
- [ ] Cross-target compatibility, performance budgets and Editor/CLI/MCP coverage tested where applicable
- [ ] Docs/evidence/rollback; pt-BR audit APPROVED, no HIGH/CRITICAL; squash merge and checkpoint

## TESTS
Exact commands, CI, fixture data, hardware/tier metrics, load and expected outcomes **TBD BY PLANNER**. No build/tests have been run for this module.

## DELIVERABLES
Scoped native code after authorization, tests, API docs, reproducible build, PR, evidence bundle, risks and proposed Checkpoint Delta.

## REVIEW FORMAT
Português brasileiro; verdict APPROVED/CORRECTION REQUIRED/BLOCKED, base/head SHA, commands/results, security/architecture/license, defect severity and checkpoint proposal.

## STOP CONDITION
BLOCKED if any TBD remains, predecessor unapproved, sources STALE, paid/unlicensed action, failing test, data loss, security HIGH/CRITICAL or unauthorized scope.

## CONTEXT LOCK
Module BIZ-03, base/head and SHA-256 source fingerprints: TBD AT ACTIVATION. Rebase if Checkpoint/Scope/DoD/Architecture/approved ADR changes.

## EVIDENCE BUNDLE
Record actual base/head SHA, files/diffs, commands/test results, lint/typecheck/build/security/benchmarks when applicable, fixes, risks, rollback and proposed Checkpoint Delta.

**Not authorized for coding.** Future module research and an objective audit must promote this packet to EXECUTOR_READY.

## BIZ-03 P00 research checkpoint (2026-11-16) — CODING STILL BLOCKED
- [Research #370](https://github.com/KayzenRoot/stormline/issues/370), [PR #371](https://github.com/KayzenRoot/stormline/pull/371) exactly eight new research docs: [ADR-0082 PROPOSED](../../adr/0082-biz-03-release-update-trust-policy.md), [typed lifecycle contract](../../contracts/biz-03-release-lifecycle-api.md), [original tech matrix](../../research/biz-03-installer-updater-security-licenses-matrix.md) and [128 B03 FUTURE tests](../../testing/biz-03-acceptance-matrix.md). [Docs Validation #43848200892](https://github.com/KayzenRoot/stormline/actions/runs/43848200892) **SUCCESS** job #133233677478, [audit pt-BR](https://github.com/KayzenRoot/stormline/pull/371#issuecomment-6913747938) APPROVED only documentary, normal squash/main readback `afccb5872603b845b449a43b48f3d2fab206e1c9`.
- **FORMAL dependencies PLAT-05 + BIZ-01 + QA-04 ONLY**, ADR-0074/0080/0078/0082 PROPOSED, NLE-D009 source LICENSE OPEN. No owner-approved source license, SDK/runtime redistribution, signing/notary, OS package, TUF verified feed, data migration or hardware/security proof. All 128 B03-T001..128 remain FUTURE/NOT_EXECUTED, zero PASS.
- Checkpoint may move **BIZ-03 research_status ONLY** to RESEARCH_DOCUMENTED_ADR_PROPOSED. This is **NOT** owner approval of code: existing `NLE-EXEC-WO-BIZ-03-001` **work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`, `risk=UNCLASSIFIED`, `context_lock_sha=null`, issue [#97](https://github.com/KayzenRoot/stormline/issues/97) OPEN/BLOCKED. 80/80 code WOs blocked. Future Zcode executor needs actual source fingerprints, approved release class/DoD, PLAT-05/BIZ-01/QA-04 authorities, verified legal+security+OS proof and isolated installation rollback tests. Research #370 closes only AFTER checkpoint readback. CORE-04 registry research pending and historic ADR-0006/PR #100 should be source-reconciled next; do not assert 80/80 researched.
