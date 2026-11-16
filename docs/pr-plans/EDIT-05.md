# EDIT-05 — Visual Shader & Material Graph | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#72](https://github.com/KayzenRoot/stormline/issues/72). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Editor de materiais/nodes, shader preview, variant management. | Formal predecessors: EDIT-02 + GFX-05 | Catalog acceptance: Visualizar e exportar shader/material validado..
[Architecture](../architecture/edit-05-visual-shader-material-graph.md) · [Proposed ADR](../adr/0057-edit-05-semantic-graph-authoring-and-preview.md) · [Original blocked code WO](../queue/work-orders/EDIT-05.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-EDIT-05-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-EDIT-05-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-EDIT-05-01 | BLOCKED |
| 3 | NLE-PRPLAN-EDIT-05-03 | IMPLEMENTATION | Editor de materiais/nodes | NLE-PRPLAN-EDIT-05-02 | BLOCKED |
| 4 | NLE-PRPLAN-EDIT-05-04 | IMPLEMENTATION | shader preview | NLE-PRPLAN-EDIT-05-03 | BLOCKED |
| 5 | NLE-PRPLAN-EDIT-05-05 | IMPLEMENTATION | variant management | NLE-PRPLAN-EDIT-05-04 | BLOCKED |
| 6 | NLE-PRPLAN-EDIT-05-06 | IMPLEMENTATION | source/data compatibility | NLE-PRPLAN-EDIT-05-05 | BLOCKED |
| 7 | NLE-PRPLAN-EDIT-05-07 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-EDIT-05-06 | BLOCKED |
| 8 | NLE-PRPLAN-EDIT-05-08 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-EDIT-05-07 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-EDIT-05-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: EDIT-05 predecessors EDIT-02+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Visualizar e exportar shader/material validado.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-05-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: EDIT-05 predecessors EDIT-02+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Visualizar e exportar shader/material validado.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-05-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-05-03 / Editor de materiais/nodes
OBJECTIVE / SCOPE: Editor de materiais/nodes. CONTEXT: EDIT-05 predecessors EDIT-02+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Visualizar e exportar shader/material validado.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Editor de materiais/nodes with valid/invalid fixtures, typed failures and undo/reopen/a11y/visual tests. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-05-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-05-04 / shader preview
OBJECTIVE / SCOPE: shader preview. CONTEXT: EDIT-05 predecessors EDIT-02+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Visualizar e exportar shader/material validado.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise shader preview with valid/invalid fixtures, typed failures and undo/reopen/a11y/visual tests. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-05-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-05-05 / variant management
OBJECTIVE / SCOPE: variant management. CONTEXT: EDIT-05 predecessors EDIT-02+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Visualizar e exportar shader/material validado.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise variant management with valid/invalid fixtures, typed failures and undo/reopen/a11y/visual tests. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-05-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-05-06 / source/data compatibility
OBJECTIVE / SCOPE: source/data compatibility. CONTEXT: EDIT-05 predecessors EDIT-02+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Visualizar e exportar shader/material validado.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise source/data compatibility with valid/invalid fixtures, typed failures and undo/reopen/a11y/visual tests. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-05-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-05-07 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: EDIT-05 predecessors EDIT-02+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Visualizar e exportar shader/material validado.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Visualizar e exportar shader/material validado.. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-05-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-EDIT-05-08 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: EDIT-05 predecessors EDIT-02+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Visualizar e exportar shader/material validado.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE undo/reopen/a11y/visual tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-EDIT-05-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
