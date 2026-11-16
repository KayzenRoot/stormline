# EDIT-01 — Editor Shell & Workspace | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#68](https://github.com/KayzenRoot/stormline/issues/68). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Docking, workspaces, shortcut profiles, undo host, project manager e acessibilidade. | Formal predecessors: CORE-01 | Catalog acceptance: Workspace salva/reabre, UI de múltiplos monitores com erros recuperáveis..
[Architecture](../architecture/edit-01-editor-shell-workspace.md) · [Proposed ADR](../adr/0053-edit-01-toolkit-neutral-editor-shell.md) · [Original blocked code WO](../queue/work-orders/EDIT-01.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-EDIT-01-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-EDIT-01-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-EDIT-01-01 | BLOCKED |
| 3 | NLE-PRPLAN-EDIT-01-03 | IMPLEMENTATION | Docking | NLE-PRPLAN-EDIT-01-02 | BLOCKED |
| 4 | NLE-PRPLAN-EDIT-01-04 | IMPLEMENTATION | workspaces | NLE-PRPLAN-EDIT-01-03 | BLOCKED |
| 5 | NLE-PRPLAN-EDIT-01-05 | IMPLEMENTATION | shortcut profiles | NLE-PRPLAN-EDIT-01-04 | BLOCKED |
| 6 | NLE-PRPLAN-EDIT-01-06 | IMPLEMENTATION | undo host | NLE-PRPLAN-EDIT-01-05 | BLOCKED |
| 7 | NLE-PRPLAN-EDIT-01-07 | IMPLEMENTATION | project manager | NLE-PRPLAN-EDIT-01-06 | BLOCKED |
| 8 | NLE-PRPLAN-EDIT-01-08 | IMPLEMENTATION | acessibilidade | NLE-PRPLAN-EDIT-01-07 | BLOCKED |
| 9 | NLE-PRPLAN-EDIT-01-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-EDIT-01-08 | BLOCKED |
| 10 | NLE-PRPLAN-EDIT-01-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-EDIT-01-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-EDIT-01-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: EDIT-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Workspace salva/reabre, UI de múltiplos monitores com erros recuperáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-01-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: EDIT-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Workspace salva/reabre, UI de múltiplos monitores com erros recuperáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-01-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-01-03 / Docking
OBJECTIVE / SCOPE: Docking. CONTEXT: EDIT-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Workspace salva/reabre, UI de múltiplos monitores com erros recuperáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Docking with valid/invalid fixtures, typed failures and undo/reopen/a11y/visual tests. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-01-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-01-04 / workspaces
OBJECTIVE / SCOPE: workspaces. CONTEXT: EDIT-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Workspace salva/reabre, UI de múltiplos monitores com erros recuperáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise workspaces with valid/invalid fixtures, typed failures and undo/reopen/a11y/visual tests. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-01-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-01-05 / shortcut profiles
OBJECTIVE / SCOPE: shortcut profiles. CONTEXT: EDIT-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Workspace salva/reabre, UI de múltiplos monitores com erros recuperáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise shortcut profiles with valid/invalid fixtures, typed failures and undo/reopen/a11y/visual tests. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-01-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-01-06 / undo host
OBJECTIVE / SCOPE: undo host. CONTEXT: EDIT-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Workspace salva/reabre, UI de múltiplos monitores com erros recuperáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise undo host with valid/invalid fixtures, typed failures and undo/reopen/a11y/visual tests. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-01-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-01-07 / project manager
OBJECTIVE / SCOPE: project manager. CONTEXT: EDIT-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Workspace salva/reabre, UI de múltiplos monitores com erros recuperáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise project manager with valid/invalid fixtures, typed failures and undo/reopen/a11y/visual tests. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-01-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-01-08 / acessibilidade
OBJECTIVE / SCOPE: acessibilidade. CONTEXT: EDIT-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Workspace salva/reabre, UI de múltiplos monitores com erros recuperáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise acessibilidade with valid/invalid fixtures, typed failures and undo/reopen/a11y/visual tests. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-01-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-01-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: EDIT-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Workspace salva/reabre, UI de múltiplos monitores com erros recuperáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Workspace salva/reabre, UI de múltiplos monitores com erros recuperáveis.. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-01-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-01-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: EDIT-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Workspace salva/reabre, UI de múltiplos monitores com erros recuperáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-01-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
