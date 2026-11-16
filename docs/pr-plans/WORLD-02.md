# WORLD-02 — Scene & Prefab Hierarchy | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#42](https://github.com/KayzenRoot/stormline/issues/42). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Árvore/graph, composição, prefab variants, instancing e transformações. | Formal predecessors: WORLD-01 + DATA-02 | Catalog acceptance: Alterações em prefabs propagam de forma controlada, com undo/redo..
[Architecture](../architecture/world-02-scene-prefab-hierarchy.md) · [Proposed ADR](../adr/0027-world-02-prefab-override-rebase-policy.md) · [Original blocked code WO](../queue/work-orders/WORLD-02.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-WORLD-02-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-WORLD-02-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-WORLD-02-01 | BLOCKED |
| 3 | NLE-PRPLAN-WORLD-02-03 | IMPLEMENTATION | Árvore/graph | NLE-PRPLAN-WORLD-02-02 | BLOCKED |
| 4 | NLE-PRPLAN-WORLD-02-04 | IMPLEMENTATION | composição | NLE-PRPLAN-WORLD-02-03 | BLOCKED |
| 5 | NLE-PRPLAN-WORLD-02-05 | IMPLEMENTATION | prefab variants | NLE-PRPLAN-WORLD-02-04 | BLOCKED |
| 6 | NLE-PRPLAN-WORLD-02-06 | IMPLEMENTATION | instancing | NLE-PRPLAN-WORLD-02-05 | BLOCKED |
| 7 | NLE-PRPLAN-WORLD-02-07 | IMPLEMENTATION | transformações | NLE-PRPLAN-WORLD-02-06 | BLOCKED |
| 8 | NLE-PRPLAN-WORLD-02-08 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-WORLD-02-07 | BLOCKED |
| 9 | NLE-PRPLAN-WORLD-02-09 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-WORLD-02-08 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-WORLD-02-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: WORLD-02 predecessors WORLD-01+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Alterações em prefabs propagam de forma controlada, com undo/redo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-02-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: WORLD-02 predecessors WORLD-01+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Alterações em prefabs propagam de forma controlada, com undo/redo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-02-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-02-03 / Árvore/graph
OBJECTIVE / SCOPE: Árvore/graph. CONTEXT: WORLD-02 predecessors WORLD-01+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Alterações em prefabs propagam de forma controlada, com undo/redo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Árvore/graph with valid/invalid fixtures, typed failures and entity identity/source preservation/soak tests. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-02-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-02-04 / composição
OBJECTIVE / SCOPE: composição. CONTEXT: WORLD-02 predecessors WORLD-01+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Alterações em prefabs propagam de forma controlada, com undo/redo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise composição with valid/invalid fixtures, typed failures and entity identity/source preservation/soak tests. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-02-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-02-05 / prefab variants
OBJECTIVE / SCOPE: prefab variants. CONTEXT: WORLD-02 predecessors WORLD-01+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Alterações em prefabs propagam de forma controlada, com undo/redo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise prefab variants with valid/invalid fixtures, typed failures and entity identity/source preservation/soak tests. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-02-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-02-06 / instancing
OBJECTIVE / SCOPE: instancing. CONTEXT: WORLD-02 predecessors WORLD-01+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Alterações em prefabs propagam de forma controlada, com undo/redo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise instancing with valid/invalid fixtures, typed failures and entity identity/source preservation/soak tests. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-02-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-02-07 / transformações
OBJECTIVE / SCOPE: transformações. CONTEXT: WORLD-02 predecessors WORLD-01+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Alterações em prefabs propagam de forma controlada, com undo/redo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise transformações with valid/invalid fixtures, typed failures and entity identity/source preservation/soak tests. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-02-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-02-08 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: WORLD-02 predecessors WORLD-01+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Alterações em prefabs propagam de forma controlada, com undo/redo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Alterações em prefabs propagam de forma controlada, com undo/redo.. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-02-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-02-09 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: WORLD-02 predecessors WORLD-01+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Alterações em prefabs propagam de forma controlada, com undo/redo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-02-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
