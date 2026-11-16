# GAME-03 — Game UI, Text & Localization | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#59](https://github.com/KayzenRoot/stormline/issues/59). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Widgets, layouts responsivos, foco, texto, fontes licenciadas, idiomas e HUD. | Formal predecessors: GFX-07 + TWO-01 | Catalog acceptance: UI gamepad/mouse, legibilidade, foco e internacionalização..
[Architecture](../architecture/game-03-ui-text-localization.md) · [Proposed ADR](../adr/0044-game-03-engine-owned-ui-semantic-tree.md) · [Original blocked code WO](../queue/work-orders/GAME-03.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-GAME-03-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-GAME-03-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-GAME-03-01 | BLOCKED |
| 3 | NLE-PRPLAN-GAME-03-03 | IMPLEMENTATION | Widgets | NLE-PRPLAN-GAME-03-02 | BLOCKED |
| 4 | NLE-PRPLAN-GAME-03-04 | IMPLEMENTATION | layouts responsivos | NLE-PRPLAN-GAME-03-03 | BLOCKED |
| 5 | NLE-PRPLAN-GAME-03-05 | IMPLEMENTATION | foco | NLE-PRPLAN-GAME-03-04 | BLOCKED |
| 6 | NLE-PRPLAN-GAME-03-06 | IMPLEMENTATION | texto | NLE-PRPLAN-GAME-03-05 | BLOCKED |
| 7 | NLE-PRPLAN-GAME-03-07 | IMPLEMENTATION | fontes licenciadas | NLE-PRPLAN-GAME-03-06 | BLOCKED |
| 8 | NLE-PRPLAN-GAME-03-08 | IMPLEMENTATION | idiomas | NLE-PRPLAN-GAME-03-07 | BLOCKED |
| 9 | NLE-PRPLAN-GAME-03-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-GAME-03-08 | BLOCKED |
| 10 | NLE-PRPLAN-GAME-03-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-GAME-03-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-GAME-03-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: GAME-03 predecessors GFX-07+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: UI gamepad/mouse, legibilidade, foco e internacionalização.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-03-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: GAME-03 predecessors GFX-07+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: UI gamepad/mouse, legibilidade, foco e internacionalização.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-03-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-03-03 / Widgets
OBJECTIVE / SCOPE: Widgets. CONTEXT: GAME-03 predecessors GFX-07+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: UI gamepad/mouse, legibilidade, foco e internacionalização.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Widgets with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-03-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-03-04 / layouts responsivos
OBJECTIVE / SCOPE: layouts responsivos. CONTEXT: GAME-03 predecessors GFX-07+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: UI gamepad/mouse, legibilidade, foco e internacionalização.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise layouts responsivos with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-03-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-03-05 / foco
OBJECTIVE / SCOPE: foco. CONTEXT: GAME-03 predecessors GFX-07+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: UI gamepad/mouse, legibilidade, foco e internacionalização.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise foco with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-03-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-03-06 / texto
OBJECTIVE / SCOPE: texto. CONTEXT: GAME-03 predecessors GFX-07+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: UI gamepad/mouse, legibilidade, foco e internacionalização.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise texto with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-03-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-03-07 / fontes licenciadas
OBJECTIVE / SCOPE: fontes licenciadas. CONTEXT: GAME-03 predecessors GFX-07+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: UI gamepad/mouse, legibilidade, foco e internacionalização.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise fontes licenciadas with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-03-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-03-08 / idiomas
OBJECTIVE / SCOPE: idiomas. CONTEXT: GAME-03 predecessors GFX-07+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: UI gamepad/mouse, legibilidade, foco e internacionalização.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise idiomas with valid/invalid fixtures, typed failures and input/contract/replay tests. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-03-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-03-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: GAME-03 predecessors GFX-07+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: UI gamepad/mouse, legibilidade, foco e internacionalização.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: UI gamepad/mouse, legibilidade, foco e internacionalização.. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-03-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GAME-03-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: GAME-03 predecessors GFX-07+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: UI gamepad/mouse, legibilidade, foco e internacionalização.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE input/contract/replay tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GAME-03-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
