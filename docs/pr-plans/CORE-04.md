# CORE-04 — Time & Simulation Clock | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#21](https://github.com/KayzenRoot/stormline/issues/21). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Tempo real, tick fixo, interpolação, pausa, stepping, replay determinístico onde exigido. | Formal predecessors: CORE-01 | Catalog acceptance: Reproduzir ticks consistentes com FPS variáveis..
[Architecture](../architecture/core-04-time-simulation.md) · [Proposed ADR](../adr/0006-core-04-time-policy.md) · [Original blocked code WO](../queue/work-orders/CORE-04.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-CORE-04-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-CORE-04-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-CORE-04-01 | BLOCKED |
| 3 | NLE-PRPLAN-CORE-04-03 | IMPLEMENTATION | Tempo real | NLE-PRPLAN-CORE-04-02 | BLOCKED |
| 4 | NLE-PRPLAN-CORE-04-04 | IMPLEMENTATION | tick fixo | NLE-PRPLAN-CORE-04-03 | BLOCKED |
| 5 | NLE-PRPLAN-CORE-04-05 | IMPLEMENTATION | interpolação | NLE-PRPLAN-CORE-04-04 | BLOCKED |
| 6 | NLE-PRPLAN-CORE-04-06 | IMPLEMENTATION | pausa | NLE-PRPLAN-CORE-04-05 | BLOCKED |
| 7 | NLE-PRPLAN-CORE-04-07 | IMPLEMENTATION | stepping | NLE-PRPLAN-CORE-04-06 | BLOCKED |
| 8 | NLE-PRPLAN-CORE-04-08 | IMPLEMENTATION | replay determinístico onde exigido | NLE-PRPLAN-CORE-04-07 | BLOCKED |
| 9 | NLE-PRPLAN-CORE-04-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-CORE-04-08 | BLOCKED |
| 10 | NLE-PRPLAN-CORE-04-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-CORE-04-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-CORE-04-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: CORE-04 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reproduzir ticks consistentes com FPS variáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-04-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: CORE-04 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reproduzir ticks consistentes com FPS variáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-04-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-04-03 / Tempo real
OBJECTIVE / SCOPE: Tempo real. CONTEXT: CORE-04 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reproduzir ticks consistentes com FPS variáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Tempo real with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-04-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-04-04 / tick fixo
OBJECTIVE / SCOPE: tick fixo. CONTEXT: CORE-04 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reproduzir ticks consistentes com FPS variáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise tick fixo with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-04-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-04-05 / interpolação
OBJECTIVE / SCOPE: interpolação. CONTEXT: CORE-04 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reproduzir ticks consistentes com FPS variáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise interpolação with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-04-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-04-06 / pausa
OBJECTIVE / SCOPE: pausa. CONTEXT: CORE-04 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reproduzir ticks consistentes com FPS variáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise pausa with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-04-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-04-07 / stepping
OBJECTIVE / SCOPE: stepping. CONTEXT: CORE-04 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reproduzir ticks consistentes com FPS variáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise stepping with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-04-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-04-08 / replay determinístico onde exigido
OBJECTIVE / SCOPE: replay determinístico onde exigido. CONTEXT: CORE-04 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reproduzir ticks consistentes com FPS variáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise replay determinístico onde exigido with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-04-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-04-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: CORE-04 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reproduzir ticks consistentes com FPS variáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Reproduzir ticks consistentes com FPS variáveis.. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-04-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-04-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: CORE-04 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reproduzir ticks consistentes com FPS variáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-04-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
