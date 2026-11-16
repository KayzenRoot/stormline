# NLE-EXEC-WO-BIZ-01-001 — Commercial Licensing & Compliance

**Status:** BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS | **Release class:** UNDECIDED | **Risk:** TBD. Not ready for execution.

## OBJECTIVE
Implement the first necessary and independently testable increment for Commercial Licensing & Compliance, only after the planner approves technology, contracts, measurable DoD, file paths and dependency evidence.

## CONTEXT
Stormline is an original AI-native 2D/2.5D/3D/Web game engine with Windows/Linux/macOS Editor + exported games. No public MVP; engine code not started. This packet derives from approved candidate module `BIZ-01` but is NOT approved code scope.

## DEPENDENCIES
`QA-05`. All blocking dependencies must have approved interfaces and merged evidence.

## SCOPE
Candidate capability: Política de licença, royalties ou não, third-party notices, IP, privacy, acessibilidade.
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
- [ ] Catalog verification: Licença aprovada e publicável, direitos de dependências/assets auditados.
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
Module BIZ-01, base/head and SHA-256 source fingerprints: TBD AT ACTIVATION. Rebase if Checkpoint/Scope/DoD/Architecture/approved ADR changes.

## EVIDENCE BUNDLE
Record actual base/head SHA, files/diffs, commands/test results, lint/typecheck/build/security/benchmarks when applicable, fixes, risks, rollback and proposed Checkpoint Delta.

**Not authorized for coding.** Future module research and an objective audit must promote this packet to EXECUTOR_READY.

## P00 Research Checkpoint (2026-11-16; **STILL BLOCKED FOR CODE**)
- Research [#362](https://github.com/KayzenRoot/stormline/issues/362), [PR #363](https://github.com/KayzenRoot/stormline/pull/363) integrated by normal squash in main `c9e5acc96884f2e1b0c292278c82348581d334ed`. Eight research docs, [ADR-0080 PROPOSED](../../adr/0080-biz-01-rights-compliance-policy.md), [rights API](../../contracts/biz-01-license-compliance-evidence-api.md), [128 future tests B01](../../testing/biz-01-acceptance-matrix.md), no actual legal or engine acceptance. [CI #43841571657](https://github.com/KayzenRoot/stormline/actions/runs/43841571657) SUCCESS documentary, [auditoria pt-BR](https://github.com/KayzenRoot/stormline/pull/363#issuecomment-6912825571) APPROVED documentary.
- **ONLY formal DAG dependency QA-05**, predecessor ADR-0079 PROPOSED; engine source license NLE-D009 OPEN and trademark NLE-D010 OPEN, no EULA, royalty decision or sublicensing permission. Creator IP distinct from included runtime/third-party content; legal expert and owner clearances required before release.
- Registry status research may be documented by independent checkpoint, but **work_order_status remains BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**, release_class UNDECIDED, approved_adr null, executor_ready false, context_lock_sha null and risk UNCLASSIFIED. None of the 128 tests executed. Do not let Zcode start without actual engine artifacts, fully approved licenses, QA-05 qualification evidence, exact source fingerprints, code implementation WO/audit and owner gates.
