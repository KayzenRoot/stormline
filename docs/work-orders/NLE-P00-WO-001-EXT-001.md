# NLE-P00-WO-001-EXT-001 — Professional Repository Presentation
**Risk:** LOW | **Type:** owner-requested extension to P00 documentation | **State:** track audit/merge in Checkpoint.

## OBJECTIVE
Transform Stormline's public GitHub entry into an accurate, polished, international, startup-grade presentation while retaining the owner-approved P00 scope and solo/free governance.

## CONTEXT
Approved P00 foundation via PR #1/#2, baseline main commit \`dcd6c81d092d629caf2f4f143bdd9377a262f87d\`. Engine implementation NOT STARTED. The owner expressly requested a highly professional README and repository hygiene as the first visible presentation task.

## SCOPE
Main English README with coherent professional sections; pt-BR summary; docs navigation; Changelog, Contribution, Conduct, Security and Support; versioning/repository policies; GitHub issue templates; minimal formatting controls; stronger P00 documentation validation; changelog and backlog update.

## OUT OF SCOPE
Engine/runtime implementation, logo/brand asset, paid services, CI for C++ code that does not exist, GitHub website, external human reviewers, proprietary third-party content, license selection, claiming benchmark or release, altering administrative settings without support.

## FILES / SOURCES TO READ
In order: docs/11-checkpoint.md, docs/10-decisions-ledger.md and ADRs, docs/03-scope.md, docs/09-definition-of-done.md, docs/04-architecture.md, docs/02-requirements.md, AGENTS.md, docs/brand/brand-foundation.md, docs/engineering/solo-governance.md, docs/engineering/free-ci.md, README.md, CI workflow and validator.

## REQUIREMENTS
GOV-001..005, BRAND-001/002 and NFR-001/005. Maintain explicit factual status and intellectual-property warnings.

## ARCHITECTURE RULES
Do not promote a technology candidate, unapproved logo or performance target. Keep editor/runtime/server conceptual. Documentation remains indexable, consistent and future-proof.

## CONSTRAINTS
R$0 mandatory CI; no CodeRabbit/external reviewer; no new runtime dependency or credential; do not bypass rules; public repo is not automatically open source.

## ACCEPTANCE CRITERIA
- English README presents vision, planned modules, architecture diagram, roadmap, honest current status, governance, CI, docs links and legal disclosures.
- pt-BR companion links back to English.
- Community docs and templates are navigable and contain no accidental claims of operational support.
- Versioning strategy distinguishes editorial versions vs actual tagged software releases.
- All internal Markdown links resolve and required repo presentation files exist.
- GitHub Actions docs-validation is green on exact HEAD before squash merge.
- Diff contains no engine code or secret, and has evidence/audit in pt-BR.

## TESTS
\`python3 scripts/validate_docs.py\`; real GitHub Actions docs-validation; diff check; docs status consistency review; check issue template metadata and pipeline references.

## DELIVERABLES
README, README.pt-BR, repo community and editorial standards, validation script changes, PR, Evidence Bundle with base/head SHA, audit and proposed Checkpoint Delta.

## REVIEW FORMAT
pt-BR: APPROVED, CORRECTION REQUIRED or BLOCKED, findings ordered by severity, actual commands/links and check evidence.

## STOP CONDITION
Out-of-scope implementation, missing license decision masquerading as license, false software claims, stale canonical sources, failing CI or HIGH/CRITICAL problem. Rework within same WO/PR.

## CONTEXT LOCK
Base SHA \`dcd6c81d092d629caf2f4f143bdd9377a262f87d\`. Read-only fingerprints should be collected and rechecked for checkpoint, Scope, DoD, Architecture and Ledger when tools support hashing.

## CHECKPOINT DELTA
Proposal only: after objective approval and merge, record repository presentation completed; enumerate inaccessible GitHub About/security/branch rules and brand asset/licensing as open. NLE-P00-WO-002 remains not started.
