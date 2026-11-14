# NLE-EXEC-WO-AUD-01-001 — Audio Device & Mixer
**STATE:** BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS | **NOT EXECUTOR_READY** | Release class UNDECIDED | Risk TBD.
[Catalog](../../product/module-catalog.md) · [Registry](../implementation-registry.json) · [Zcode protocol](../../engineering/zcode-handoff.md).

## OBJECTIVE
Implement the first approved, verifiable necessary slice of Audio Device & Mixer in Stormline after all technical decisions are signed off; candidate coverage: Output multi-device, sample-rate, buses, voz virtualizada, streaming e limites.

## CONTEXT
Original 2D/2.5D/3D/web game engine, Windows/Linux/macOS Editor+exports, AI-native human/CLI/MCP parity and no public MVP. Candidate catalog is an approved *index*, not an executable plan.

## DEPENDENCIES
`CORE-01`, `CORE-03`. Dependents require full approved interfaces and checkpoint evidence.

## SCOPE
Output multi-device, sample-rate, buses, voz virtualizada, streaming e limites. This packet becomes a coding task **only when** specific interface/schema, files, methods, tests and a small NECESSARY increment have been authored and audited by the planner.

## OUT OF SCOPE
Unapproved architecture and tech selection, unrelated cleanup, speculative APIs, out-of-scope gameplay, subscriptions, external reviewer, CodeRabbit, forced/bypass merge and public release.

## FILES / SOURCES TO READ
Canonical priority: `docs/11-checkpoint.md`, `docs/10-decisions-ledger.md`/ADRs, `docs/03-scope.md`, `docs/09-definition-of-done.md`, `docs/04-architecture.md`, `docs/02-requirements.md`, then `AGENTS.md`, [catalog](../../product/module-catalog.md), module-specific approved spec **TBD**, actual source paths **TBD**.

## REQUIREMENTS
GOV-001..005, relevant CAP/NFR IDs and NLE-D013..018. Specific mapping and release class **TBD/UNAPPROVED**.

## ARCHITECTURE RULES
Typed/secure API, lifecycle/ownership, cross-platform/editor/runtime/server isolation, data migration/error handling, measurable performance; public authoring commands mapped to Editor/CLI/MCP without raw privileged internals.

## CONSTRAINTS
Zero mandatory paid CI, solo governance, no force-push, no credentials or unlicensed content. Do not code until all review gates pass.

## ACCEPTANCE CRITERIA
- [ ] Required tech ADR, license/security review, release scope, API and data model, exact files, OS matrix and risk APPROVED
- [ ] All dependencies APPROVED and merged; BASE SHA/critical SHA-256 fingerprints valid
- [ ] Candidate proof: **Testes de underruns, latência e custo por quantidade de vozes.**
- [ ] Required unit/integration/stress/failure/regression and platform tests passed (actual evidence)
- [ ] CPU/GPU/memory/latency benchmarks as applicable and Editor/CLI/MCP parity validated
- [ ] Docs, build, Evidence Bundle, pt-BR audit APPROVED, PR merge and checkpoint delta

## TESTS
Commands, fixtures, devices, hardware and quantitative thresholds **TBD BY PLANNER**. Current tests **NOT RUN**; no implementation exists.

## DELIVERABLES
Only files in approved work order, tests, interfaces, documentation, CI, PR, rollback/roll-forward and evidence.

## REVIEW FORMAT
Review pt-BR: APPROVED/CORRECTION REQUIRED/BLOCKED with SHA, tests, defects/severity, security/license, risk, diff and checkpoint delta.

## STOP CONDITION
BLOCKED on any TBD above, stale source, failed required test, HIGH/CRITICAL, unauthorized payment/change or pending predecessor. Corrections stay in same WO/PR.

## CONTEXT LOCK
BASE SHA and hashes: TBD when unlocked. Revalidate Checkpoint, Scope, DoD, Architecture and ADR fingerprints.

## EVIDENCE BUNDLE
Base/head SHA, changed files, exact commands and results, CI/build/lint/typecheck/security/perf, errors fixed, risks, diff and checkpoint delta **proposed**, not auto-promoted.

**A planning shell only; Zcode must not start code from this document.**
