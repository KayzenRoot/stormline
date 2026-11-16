# NLE-EXEC-WO-BIZ-02-001 — SDK, Plugins & Developer Experience

**Status:** BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS | **Release class:** UNDECIDED | **Risk:** TBD. Not ready for execution.

## OBJECTIVE
Implement the first necessary and independently testable increment for SDK, Plugins & Developer Experience, only after the planner approves technology, contracts, measurable DoD, file paths and dependency evidence.

## CONTEXT
Stormline is an original AI-native 2D/2.5D/3D/Web game engine with Windows/Linux/macOS Editor + exported games. No public MVP; engine code not started. This packet derives from approved candidate module `BIZ-02` but is NOT approved code scope.

## DEPENDENCIES
`GAME-02`, `AI-01`. All blocking dependencies must have approved interfaces and merged evidence.

## SCOPE
Candidate capability: API versionada, extensões, samples, docs técnicas e portabilidade.
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
- [ ] Catalog verification: Plugin/sample compatível com API publicada, teste de atualização.
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
Module BIZ-02, base/head and SHA-256 source fingerprints: TBD AT ACTIVATION. Rebase if Checkpoint/Scope/DoD/Architecture/approved ADR changes.

## EVIDENCE BUNDLE
Record actual base/head SHA, files/diffs, commands/test results, lint/typecheck/build/security/benchmarks when applicable, fixes, risks, rollback and proposed Checkpoint Delta.

**Not authorized for coding.** Future module research and an objective audit must promote this packet to EXECUTOR_READY.

## P00 BIZ-02 Research Checkpoint (2026-11-16) — STILL NOT EXECUTOR_READY
- [Research #366](https://github.com/KayzenRoot/stormline/issues/366), [PR #367](https://github.com/KayzenRoot/stormline/pull/367) with exactly 8 docs and 128 FUTURE `B02-T001..B02-T128`; ADR-0081 [PROPOSED](../../adr/0081-biz-02-sdk-plugin-abi-policy.md), [SDK/plugin API](../../contracts/biz-02-sdk-plugin-api.md), [technical matrix](../../research/biz-02-sdk-plugin-technology-security-license-matrix.md). Exact-head [Docs Validation #43845155975](https://github.com/KayzenRoot/stormline/actions/runs/43845155975), job #133223354776 SUCCESS; [objective pt-BR audit](https://github.com/KayzenRoot/stormline/pull/367#issuecomment-6913320019) APPROVED **only documentary**. Normal squash and `main` readback at `29ca0fa90215e13b09135d2330357354a35aba85`.
- **Formal GAME-02 + AI-01 ONLY**; their ADR-0043/0060 and BIZ-02 ADR-0081 are all PROPOSED. Engine license NLE-D009 OPEN, no permission to ship SDK, plugins, sample or engine runtime, no ABI frozen, no real code or sandbox. Upcoming independent checkpoint may set `research_status=RESEARCH_DOCUMENTED_ADR_PROPOSED`, **not `approved_adr` or `executor_ready`**.
- Current implementation packet `NLE-EXEC-WO-BIZ-02-001` and issue [#96](https://github.com/KayzenRoot/stormline/issues/96) remain **BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS / OPEN**, risk UNCLASSIFIED, release class UNDECIDED, context_lock_sha null, approved_adr null, executor_ready=false. 80/80 coding packets remain blocked. Zcode preflight still denies coding until owner-approved exact source/API/ABI/runtime/rights/contracts/real test hardware, DoD/release class and fresh fingerprints. No PASS for future 128 scenarios.
