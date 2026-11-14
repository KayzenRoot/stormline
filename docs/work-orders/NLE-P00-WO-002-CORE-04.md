# Work Order — NLE-P00-WO-002-CORE-04

**Risk:** LOW (documentation); future clock runtime STANDARD/ELEVATED with physics/server integration.  
**State:** RESEARCH IN PROGRESS / ADR-0006 PROPOSED / NO ENGINE CODE. **Issue:** #99.  
**Baseline main:** 90eaf1b7cef148dfd168e3fa1ac8f7e9be603216 (after PR #98).

## OBJECTIVE
Research and specify CORE-04 Time & Simulation Clock choices, cross-platform fixed-step scheduling, determinism envelope and evidence-driven tests before Zcode receives any coding Work Order.

## CONTEXT
The 80-module catalog is approved as an index, all 80 implementation packets/issues #18–#97 are BLOCKED, and CORE-01/02/03 research completed as documents only. This is a research child of NLE-P00-WO-002. It does not activate implementation issue #21.

## SCOPE
- Research monotonic clocks and rational/fixed-step accumulator, clock injection, interpolation, time scaling and pause/single-step.
- Specify offline vs authoritative overload/debt behavior, replay/event ordering and typed failures.
- Define API contract boundaries with CORE-01, CORE-03, CORE-06, SIM, GFX, NET, AI, and OS/headless test plan.
- Deliver architecture blueprint, research matrix, ADR-0006 PROPOSED, scoped Source Pack references, a CI-verified docs PR, objective audit and Evidence Bundle.

## OUT OF SCOPE
No engine C++, stdlib wrappers implemented, SDK/runtime release, physics/network code, lockstep claim, asset content, binaries, native benchmarking, paid tools, code execution on issue #21, unrelated cleanup or mandatory external reviewer.

## FILES / SOURCES TO READ
Read docs/11-checkpoint.md > docs/10-decisions-ledger.md and approved ADRs > docs/03-scope.md > docs/09-definition-of-done.md > docs/04-architecture.md > docs/02-requirements.md > docs/product/module-catalog.md > docs/architecture/core-01-platform-lifecycle.md > docs/architecture/core-03-concurrency-jobs.md > docs/queue/work-orders/CORE-04.md > AGENTS.md; use official references in research matrix. Inspect Git HEAD/PRs first.

## REQUIREMENTS
GOV-001..005; CAP-009 performance and CAP-010 extensibility, relevant simulation requirements/NFR-001..005; NLE-D013..020. Preserve Windows/Linux/macOS/native + headless support and 2D/2.5D/3D/web roadmap, with no public MVP.

## ARCHITECTURE RULES
Clock acquisition from CORE-01 only; CORE-04 owns TickId/rational timeline; CORE-03 consumes tick barriers; graphics/audio never own sim time. No third-party API in engine public contract. Never claim numeric cross-platform physics determinism based only on fixed ticks. Freeze dependent module ownership.

## CONSTRAINTS
Zero-cost public CI; no engine implementation, secret, paid package, CodeRabbit, external approval, bypass, force-push or premature issue status promotion. Approved prior ADRs and Source Pack dominate speculative alternatives.

## ACCEPTANCE CRITERIA
- [ ] Clock candidates, portable semantics, source links, licenses/packaging implications and reasons documented.
- [ ] Typed conceptual contracts for monotonic ClockSource, integer/rational TickId/timeline, errors, pause, one-step, replay scope, overload/clamp/dropped time diagnostics and interpolation.
- [ ] 60Hz fixture, 30/60/144 FPS partition invariance, 24h/5,184,000 tick drift check, overflow, backwards time, sleep, pause and server overload scenarios specified.
- [ ] Cross-module DAG and OS/headless/Web limitations documented; deterministic scheduling explicitly distinguished from deterministic physics.
- [ ] ADR-0006 explicitly PROPOSED and implementation #21 remains BLOCKED.
- [ ] GitHub Actions docs-validation passes on exact HEAD; no code or unintended artifacts; objective audit in pt-BR and scoped Evidence Bundle.
- [ ] Checkpoint delta ONLY after approval/merge, with main readback; no premature next module.

## TESTS
Current Work Order: python3 scripts/validate_docs.py; python3 scripts/validate_module_catalog.py; python3 scripts/validate_wo_registry.py; python3 scripts/select_wo.py CORE-04 (must refuse execution); GitHub Actions docs-validation exact PR HEAD. Planned runtime tests are specifications only, not executed.

## DELIVERABLES
docs/architecture/core-04-time-simulation.md, docs/research/core-04-technology-matrix.md, docs/adr/0006-core-04-time-policy.md, this Work Order, relevant docs/04-architecture.md and docs/08-backlog.md links, Evidence Bundle with test/CI/SHAs and proposed Checkpoint Delta; branch and PR.

## REVIEW FORMAT
Brazilian Portuguese; check Scope, source precedence, interface boundaries, portability, security/licensing, exact base/head, paths, CI run, errors, risks and verdict APPROVED/CORRECTION REQUIRED/BLOCKED. No independent human reviewer requirement.

## STOP CONDITION
STALE canonical source or main, failing check, unsupported precision claims, contradictory determinism/overrun policy, unapproved dependencies or costs, HIGH/CRITICAL defect, any code in docs-only diff; no next increment until audit and checkpoint reconciliation.

## CONTEXT LOCK
Base SHA: 90eaf1b7cef148dfd168e3fa1ac8f7e9be603216. Critical file fingerprints and HEAD to be included in audit Evidence Bundle. Revalidate if checkpoint, Scope, Architecture, DoD or ADR changes.

## EVIDENCE BUNDLE
Document actual PR head/base, CI commands and run IDs, changed files, checks and limitations, licensing, risks, corrections and proposed Checkpoint Delta. No native tests are claimed in this P00 research.
