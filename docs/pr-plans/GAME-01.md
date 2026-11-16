# GAME-01 — Input & Control Mapping | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#56](https://github.com/KayzenRoot/stormline/issues/56). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Keyboard/mouse/gamepad/touch, remapping, múltiplos dispositivos, acessibilidade. | Formal predecessors: CORE-01 | Catalog acceptance: Mapeamentos consistentes entre editor, runtime e exports..
[Architecture](../architecture/game-01-input-control-mapping.md) · [Proposed ADR](../adr/0042-game-01-engine-owned-input-actions.md) · [Original blocked code WO](../queue/work-orders/GAME-01.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-GAME-01-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-GAME-01-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-GAME-01-01 | BLOCKED |
| 3 | NLE-PRPLAN-GAME-01-03 | IMPLEMENTATION | Keyboard/mouse/gamepad/touch | NLE-PRPLAN-GAME-01-02 | BLOCKED |
| 4 | NLE-PRPLAN-GAME-01-04 | IMPLEMENTATION | remapping | NLE-PRPLAN-GAME-01-03 | BLOCKED |
| 5 | NLE-PRPLAN-GAME-01-05 | IMPLEMENTATION | múltiplos dispositivos | NLE-PRPLAN-GAME-01-04 | BLOCKED |
| 6 | NLE-PRPLAN-GAME-01-06 | IMPLEMENTATION | acessibilidade | NLE-PRPLAN-GAME-01-05 | BLOCKED |
| 7 | NLE-PRPLAN-GAME-01-07 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-GAME-01-06 | BLOCKED |
| 8 | NLE-PRPLAN-GAME-01-08 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-GAME-01-07 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-GAME-01-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: GAME-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Mapeamentos consistentes entre editor, runtime e exports.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-01-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: GAME-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Mapeamentos consistentes entre editor, runtime e exports.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-01-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-01-03 / Keyboard/mouse/gamepad/touch
OBJECTIVE / SCOPE: Keyboard/mouse/gamepad/touch. CONTEXT: GAME-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Mapeamentos consistentes entre editor, runtime e exports.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Keyboard/mouse/gamepad/touch with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-01-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-01-04 / remapping
OBJECTIVE / SCOPE: remapping. CONTEXT: GAME-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Mapeamentos consistentes entre editor, runtime e exports.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise remapping with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-01-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-01-05 / múltiplos dispositivos
OBJECTIVE / SCOPE: múltiplos dispositivos. CONTEXT: GAME-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Mapeamentos consistentes entre editor, runtime e exports.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise múltiplos dispositivos with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-01-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-01-06 / acessibilidade
OBJECTIVE / SCOPE: acessibilidade. CONTEXT: GAME-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Mapeamentos consistentes entre editor, runtime e exports.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise acessibilidade with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-01-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-01-07 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: GAME-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Mapeamentos consistentes entre editor, runtime e exports.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Mapeamentos consistentes entre editor, runtime e exports.. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-01-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-01-08 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: GAME-01 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Mapeamentos consistentes entre editor, runtime e exports.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-01-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
