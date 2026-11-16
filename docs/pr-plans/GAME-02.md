# GAME-02 — Gameplay Scripting & API | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#58](https://github.com/KayzenRoot/stormline/issues/58). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Scripting visual/textual a decidir, bindings, sandbox, hot reload e APIs estáveis. | Formal predecessors: WORLD-01 + CORE-03 | Catalog acceptance: Modificar regras sem recompilar Core e com limites de segurança..
[Architecture](../architecture/game-02-gameplay-scripting-api.md) · [Proposed ADR](../adr/0043-game-02-engine-owned-capability-script-host.md) · [Original blocked code WO](../queue/work-orders/GAME-02.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-GAME-02-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-GAME-02-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-GAME-02-01 | BLOCKED |
| 3 | NLE-PRPLAN-GAME-02-03 | IMPLEMENTATION | Scripting visual/textual a decidir | NLE-PRPLAN-GAME-02-02 | BLOCKED |
| 4 | NLE-PRPLAN-GAME-02-04 | IMPLEMENTATION | bindings | NLE-PRPLAN-GAME-02-03 | BLOCKED |
| 5 | NLE-PRPLAN-GAME-02-05 | IMPLEMENTATION | sandbox | NLE-PRPLAN-GAME-02-04 | BLOCKED |
| 6 | NLE-PRPLAN-GAME-02-06 | IMPLEMENTATION | hot reload | NLE-PRPLAN-GAME-02-05 | BLOCKED |
| 7 | NLE-PRPLAN-GAME-02-07 | IMPLEMENTATION | APIs estáveis | NLE-PRPLAN-GAME-02-06 | BLOCKED |
| 8 | NLE-PRPLAN-GAME-02-08 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-GAME-02-07 | BLOCKED |
| 9 | NLE-PRPLAN-GAME-02-09 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-GAME-02-08 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-GAME-02-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: GAME-02 predecessors WORLD-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Modificar regras sem recompilar Core e com limites de segurança.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-02-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: GAME-02 predecessors WORLD-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Modificar regras sem recompilar Core e com limites de segurança.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-02-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-02-03 / Scripting visual/textual a decidir
OBJECTIVE / SCOPE: Scripting visual/textual a decidir. CONTEXT: GAME-02 predecessors WORLD-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Modificar regras sem recompilar Core e com limites de segurança.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Scripting visual/textual a decidir with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-02-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-02-04 / bindings
OBJECTIVE / SCOPE: bindings. CONTEXT: GAME-02 predecessors WORLD-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Modificar regras sem recompilar Core e com limites de segurança.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise bindings with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-02-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-02-05 / sandbox
OBJECTIVE / SCOPE: sandbox. CONTEXT: GAME-02 predecessors WORLD-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Modificar regras sem recompilar Core e com limites de segurança.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise sandbox with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-02-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-02-06 / hot reload
OBJECTIVE / SCOPE: hot reload. CONTEXT: GAME-02 predecessors WORLD-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Modificar regras sem recompilar Core e com limites de segurança.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise hot reload with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-02-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-02-07 / APIs estáveis
OBJECTIVE / SCOPE: APIs estáveis. CONTEXT: GAME-02 predecessors WORLD-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Modificar regras sem recompilar Core e com limites de segurança.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise APIs estáveis with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-02-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-02-08 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: GAME-02 predecessors WORLD-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Modificar regras sem recompilar Core e com limites de segurança.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Modificar regras sem recompilar Core e com limites de segurança.. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-02-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-02-09 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: GAME-02 predecessors WORLD-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Modificar regras sem recompilar Core e com limites de segurança.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-02-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
