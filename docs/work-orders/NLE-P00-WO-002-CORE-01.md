# Work Order — NLE-P00-WO-002-CORE-01

**Parent program:** NLE-P00-WO-002 (technology/licensing research for all modules, iterated one module at a time)  
**Module:** CORE-01 Platform & Lifecycle  
**GitHub issue:** #6  
**Risk classification:** LOW for this documentation-only execution; future C++ implementation STANDARD or ELEVATED depending on OS/security changes  
**Context Lock baseline SHA:** c5ef59c13e65db2a79a04d420cdfc9a9c10768d6  
**Status:** PLANNING / AWAITING OBJECTIVE AUDIT

## OBJECTIVE
Produce researched technology recommendations and functional/architectural contracts for CORE-01 that enable Windows, Linux and macOS Editor + exported games, while protecting headless server and Web target boundaries.

## CONTEXT
The 80-module catalog was accepted as candidate index in PR #5 and its checkpoint reconciled in PR #7. NLE-D017 mandates the three desktop OS. NLE-D018 allows routine technical planning without repetitive approval requests but does not bypass tests, payment approval or destructive-action restrictions. No engine runtime code exists.

## SCOPE
- Document technology matrix and rationale, licenses and alternatives.
- Formalize CORE-01 architecture contracts, event/capability schemas, failure modes, OS thread and headless behavior.
- Proposed ADR-0003, platform CI matrix and experiments/benchmark plan.
- Link issue #6 and update backlog (same module, no adjacent work).

## OUT OF SCOPE
Do **not** implement C++, build an engine, download SDK, install paid services, change CI for non-existent code, choose a final renderer backend, build an editor, open other module WOs or merge unverified PRs. No logo, asset or game code.

## FILES / SOURCES TO READ
Checkpoint > Decisions Ledger/ADRs > Scope > DoD > Architecture > Requirements > module catalog > AGENTS and issue #6 > SDL, CMake, Apple and GitHub official documentation.

## REQUIREMENTS
NLE-D002 (original specialist-library engine); NLE-D017 (Windows/Linux/macOS editor + exports), NLE-D018 (delegated routine planning), GOV-001..005, CAP-016 (platforms), NFR-001/002/003/005. Preserve no-MVP and free/solo governance.

## ARCHITECTURE RULES
No platform specific types in public gameplay/MCP APIs; renderer API not selected in Core; headless server has no GUI/GPU requirement; interface contracts versioned and testable; avoid duplicate abstractions without proof. Keep no-op overhead measured.

## CONSTRAINTS
Public GitHub repository with no mandatory paid CI, CodeRabbit or external human reviewers. No bypass, no force-push, no speculative proof of superiority or hardware compatibility. No Apple enrollment or other expenditure.

## ACCEPTANCE CRITERIA
- [ ] Stable CORE-01 interfaces and lifecycle state machine defined.
- [ ] C++20/23, SDL3, native bridges, CMake/Ninja and compilers evaluated with alternatives, license and constraints.
- [ ] Apple Silicon and Mac Intel decision clearly separated; Web handled in PLAT-03.
- [ ] Real macOS/Windows/Linux target matrix and headless requirements specified.
- [ ] SAPL innovation hypothesis includes baseline, metric, stop rule and no invented results.
- [ ] ADR-0003 clearly PROPOSED and future proof obligations defined.
- [ ] Docs validator succeeds; GitHub Actions docs-validation passes on fixed HEAD; diff contains only scoped documentation.
- [ ] Review in pt-BR; Evidence Bundle with base/head, CI, risks and checkpoint delta.
- [ ] Do not initiate CORE-02 until this WO is audited/merged/reconciled.

## TESTS
Execute existing docs-validation and module-DAG validation; inspect links and ADR references; compare changed-file diff and canonical states. **Future software tests** are specified but NOT executed.

## DELIVERABLES
`docs/architecture/core-01-platform-lifecycle.md`, `docs/research/core-01-platform-technology-matrix.md`, `docs/adr/0003-core-01-platform-technology.md`, this WO, issue #6 update, Evidence Bundle and post-merge checkpoint reconciliation.

## REVIEW FORMAT
Português brasileiro; verdict APPROVED / CORRECTION REQUIRED / BLOCKED; evidence for each criterion, severity and remediation. No external reviewer required.

## STOP CONDITION
STALE baseline or requirements, missing license evidence, accidental implementation, unsupported platform promise, paying for Apple/account, broken CI, known HIGH/CRITICAL problem, or requirement beyond this Work Order.

## CONTEXT LOCK
Do not update files if main differs from the verified baseline. After docs merge, propose new checkpoint with explicit main SHA. Technical choices stay PROPOSED pending implementation conformance and platform tests.
