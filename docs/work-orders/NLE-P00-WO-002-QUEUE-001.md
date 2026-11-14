# Work Order — NLE-P00-WO-002-QUEUE-001

**Risk:** STANDARD documentation / mass issue preparation  
**Status:** APPROVED / MERGED as blocked Work Order preparation (PR #17); 80 issues created #18–97 after registry merge, issue mapping in audited follow-up.  
**Issue:** #16  
**Baseline main:** `3db4507ffa99896a799c0da7fe0be738fa4a4f4c`.

## OBJECTIVE
Prepare 80 traceable and deterministically verifiable future implementation Work Order packets, so Zcode executes only pre-approved scoped coding, not initial product design.

## CONTEXT
The original 80-module Stormline catalog was accepted as an index, but its technology choices and 1.0 release classes remain open. CORE-01/02/03 research documents and checkpoints were integrated. Owner explicitly requests the whole future WO/issue queue prepared before coding, with no premature execution.

## SCOPE
Registry JSON with all 80 module IDs and catalog dependencies, individual `NLE-EXEC-WO-<MODULE_ID>-001` drafts, shared packet template, Zcode handoff and deterministic stdlib validators/read-only selector; future issue staging and checkpoint reconciliation.

## OUT OF SCOPE
Engine C++/shader/editor/MCP Server implementation, release, unapproved architecture decisions, 80 simultaneous implementation branches, paid services, CodeRabbit, external reviewers, bypass/force push or false READY statuses.

## FILES / SOURCES TO READ
Checkpoint, Ledger/ADRs, Scope, DoD, Architecture, Requirements, AGENTS.md, approved module catalog, previously audited module studies, queue registry and Zcode handoff.

## REQUIREMENTS
GOV-001..005; CAP-001..016 as relevant; NFR-001..005; NLE-D013..018. Only *preparation* is authorized by owner's request.

## ARCHITECTURE RULES
Each module ID stable; dependency graph topological; no implementation without an approved per-module technology/API/DoD contract; no common engine core pollution; Editor/CLI/MCP parity and security; cross-platform requirements.

## CONSTRAINTS
Public repo zero-cost CI, solo governance, no CodeRabbit, no paid provider credentials, no action bypass or destructive behavior.

## ACCEPTANCE CRITERIA
- [ ] Exactly 80 unique provisional WO packets corresponding to the approved catalog; no dependency cycles or incorrect module names
- [ ] Each draft includes all mandatory Work Order headings, stable ID, candidate acceptance and explicit BLOCKED/NOT EXECUTOR_READY
- [ ] Runner-neutral, stdlib validators and read-only selector; CI docs-validation success with real HEAD
- [ ] One GitHub planning issue per module when safe, tracked without accidentally labeling coding complete or READY
- [ ] Issue dedup by stable ID; no duplicate releases/jobs across runs
- [ ] Documentation Zcode instructions and Source Pack consistency
- [ ] Evidence Bundle with base/head SHA, diff, tests, security/risks, checkpoint delta and pt-BR objective audit

## TESTS
`python3 scripts/validate_docs.py`, `python3 scripts/validate_module_catalog.py`, `python3 scripts/validate_wo_registry.py`, `python3 scripts/select_wo.py --list`; GitHub Actions docs-validation. Validate 80 file count and checked status. No C++ tests in this WO.

## DELIVERABLES
GitHub PR containing queue registry and packets, Zcode handoff, scripts, 80 planning-only tickets if connector supports, Evidence Bundle and audited checkpoint update.

## REVIEW FORMAT
pt-BR; APPPROVED / CORRECTION REQUIRED / BLOCKED, exact SHAs, tests, risk and limits. No external reviewer.

## STOP CONDITION
Any module marked ready without tech/spec/Context Lock, missing dependency, duplicated issue, incorrect source precedence, failing CI, code implementation or unapproved cost. Correction only within this WO/PR.

## CONTEXT LOCK
Base SHA `3db4507ffa99896a799c0da7fe0be738fa4a4f4c`. Fingerprints of sources can be captured via Git and checked against approved Source Pack; stale if checkpoint/ADR/Scope/DoD/Architecture changes.

## EVIDENCE BUNDLE
Source files and manifest, Git base/head, issue IDs, check outputs, CI links, risks, corrected errors and proposed checkpoint delta. No engine implemented or released.
