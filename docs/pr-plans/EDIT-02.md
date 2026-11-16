# EDIT-02 — Project Creation & Management | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#69](https://github.com/KayzenRoot/stormline/issues/69). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Wizard 2D/2.5D/3D/web, templates, schema upgrade e project validation. | Formal predecessors: EDIT-01 + DATA-01 | Catalog acceptance: Criar projetos de todos os modos com configurações corretas..
[Architecture](../architecture/edit-02-project-creation-management.md) · [Proposed ADR](../adr/0054-edit-02-transactional-project-descriptor.md) · [Original blocked code WO](../queue/work-orders/EDIT-02.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-EDIT-02-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-EDIT-02-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-EDIT-02-01 | BLOCKED |
| 3 | NLE-PRPLAN-EDIT-02-03 | IMPLEMENTATION | Wizard 2D/2.5D/3D/web | NLE-PRPLAN-EDIT-02-02 | BLOCKED |
| 4 | NLE-PRPLAN-EDIT-02-04 | IMPLEMENTATION | templates | NLE-PRPLAN-EDIT-02-03 | BLOCKED |
| 5 | NLE-PRPLAN-EDIT-02-05 | IMPLEMENTATION | schema upgrade | NLE-PRPLAN-EDIT-02-04 | BLOCKED |
| 6 | NLE-PRPLAN-EDIT-02-06 | IMPLEMENTATION | project validation | NLE-PRPLAN-EDIT-02-05 | BLOCKED |
| 7 | NLE-PRPLAN-EDIT-02-07 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-EDIT-02-06 | BLOCKED |
| 8 | NLE-PRPLAN-EDIT-02-08 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-EDIT-02-07 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-EDIT-02-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: EDIT-02 predecessors EDIT-01+DATA-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar projetos de todos os modos com configurações corretas.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-02-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: EDIT-02 predecessors EDIT-01+DATA-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar projetos de todos os modos com configurações corretas.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-02-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-02-03 / Wizard 2D/2.5D/3D/web
OBJECTIVE / SCOPE: Wizard 2D/2.5D/3D/web. CONTEXT: EDIT-02 predecessors EDIT-01+DATA-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar projetos de todos os modos com configurações corretas.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Wizard 2D/2.5D/3D/web with valid/invalid fixtures, typed failures and undo/reopen/a11y/visual tests. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-02-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-02-04 / templates
OBJECTIVE / SCOPE: templates. CONTEXT: EDIT-02 predecessors EDIT-01+DATA-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar projetos de todos os modos com configurações corretas.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise templates with valid/invalid fixtures, typed failures and undo/reopen/a11y/visual tests. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-02-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-02-05 / schema upgrade
OBJECTIVE / SCOPE: schema upgrade. CONTEXT: EDIT-02 predecessors EDIT-01+DATA-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar projetos de todos os modos com configurações corretas.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise schema upgrade with valid/invalid fixtures, typed failures and undo/reopen/a11y/visual tests. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-02-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-02-06 / project validation
OBJECTIVE / SCOPE: project validation. CONTEXT: EDIT-02 predecessors EDIT-01+DATA-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar projetos de todos os modos com configurações corretas.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise project validation with valid/invalid fixtures, typed failures and undo/reopen/a11y/visual tests. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-02-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-02-07 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: EDIT-02 predecessors EDIT-01+DATA-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar projetos de todos os modos com configurações corretas.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Criar projetos de todos os modos com configurações corretas.. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-02-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-02-08 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: EDIT-02 predecessors EDIT-01+DATA-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar projetos de todos os modos com configurações corretas.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-02-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
