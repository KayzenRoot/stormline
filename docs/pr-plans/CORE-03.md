# CORE-03 — Jobs & Concurrency | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#20](https://github.com/KayzenRoot/stormline/issues/20). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Agendador de tarefas, prioridades, dependências, afinidade, cancelamento, isolamento de dados. | Formal predecessors: CORE-02 | Catalog acceptance: Teste de determinismo aplicável e stress sem data races..
[Architecture](../architecture/core-03-concurrency-jobs.md) · [Proposed ADR](../adr/0005-core-03-jobs-concurrency.md) · [Original blocked code WO](../queue/work-orders/CORE-03.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-CORE-03-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-CORE-03-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-CORE-03-01 | BLOCKED |
| 3 | NLE-PRPLAN-CORE-03-03 | IMPLEMENTATION | Agendador de tarefas | NLE-PRPLAN-CORE-03-02 | BLOCKED |
| 4 | NLE-PRPLAN-CORE-03-04 | IMPLEMENTATION | prioridades | NLE-PRPLAN-CORE-03-03 | BLOCKED |
| 5 | NLE-PRPLAN-CORE-03-05 | IMPLEMENTATION | dependências | NLE-PRPLAN-CORE-03-04 | BLOCKED |
| 6 | NLE-PRPLAN-CORE-03-06 | IMPLEMENTATION | afinidade | NLE-PRPLAN-CORE-03-05 | BLOCKED |
| 7 | NLE-PRPLAN-CORE-03-07 | IMPLEMENTATION | cancelamento | NLE-PRPLAN-CORE-03-06 | BLOCKED |
| 8 | NLE-PRPLAN-CORE-03-08 | IMPLEMENTATION | isolamento de dados | NLE-PRPLAN-CORE-03-07 | BLOCKED |
| 9 | NLE-PRPLAN-CORE-03-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-CORE-03-08 | BLOCKED |
| 10 | NLE-PRPLAN-CORE-03-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-CORE-03-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-CORE-03-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: CORE-03 predecessors CORE-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Teste de determinismo aplicável e stress sem data races.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-03-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: CORE-03 predecessors CORE-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Teste de determinismo aplicável e stress sem data races.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-03-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-03-03 / Agendador de tarefas
OBJECTIVE / SCOPE: Agendador de tarefas. CONTEXT: CORE-03 predecessors CORE-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Teste de determinismo aplicável e stress sem data races.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Agendador de tarefas with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-03-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-03-04 / prioridades
OBJECTIVE / SCOPE: prioridades. CONTEXT: CORE-03 predecessors CORE-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Teste de determinismo aplicável e stress sem data races.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise prioridades with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-03-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-03-05 / dependências
OBJECTIVE / SCOPE: dependências. CONTEXT: CORE-03 predecessors CORE-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Teste de determinismo aplicável e stress sem data races.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise dependências with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-03-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-03-06 / afinidade
OBJECTIVE / SCOPE: afinidade. CONTEXT: CORE-03 predecessors CORE-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Teste de determinismo aplicável e stress sem data races.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise afinidade with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-03-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-03-07 / cancelamento
OBJECTIVE / SCOPE: cancelamento. CONTEXT: CORE-03 predecessors CORE-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Teste de determinismo aplicável e stress sem data races.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise cancelamento with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-03-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-03-08 / isolamento de dados
OBJECTIVE / SCOPE: isolamento de dados. CONTEXT: CORE-03 predecessors CORE-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Teste de determinismo aplicável e stress sem data races.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise isolamento de dados with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-03-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-03-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: CORE-03 predecessors CORE-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Teste de determinismo aplicável e stress sem data races.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Teste de determinismo aplicável e stress sem data races.. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-03-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-03-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: CORE-03 predecessors CORE-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Teste de determinismo aplicável e stress sem data races.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-03-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
