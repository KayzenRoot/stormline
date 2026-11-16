# NET-05 — Sessions & Lobby Interfaces | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#66](https://github.com/KayzenRoot/stormline/issues/66). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Match/session/lobby abstractions; integração com backend externo opcional. | Formal predecessors: NET-01 + NET-02 | Catalog acceptance: Criar/join/leave, reconexão e falhas previsíveis sem SaaS obrigatório..
[Architecture](../architecture/net-05-sessions-lobby-interfaces.md) · [Proposed ADR](../adr/0051-net-05-local-first-session-lobby-ticket-contracts.md) · [Original blocked code WO](../queue/work-orders/NET-05.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-NET-05-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-NET-05-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-NET-05-01 | BLOCKED |
| 3 | NLE-PRPLAN-NET-05-03 | IMPLEMENTATION | Match/session/lobby abstractions; integração com backend externo opcional | NLE-PRPLAN-NET-05-02 | BLOCKED |
| 4 | NLE-PRPLAN-NET-05-04 | IMPLEMENTATION | boundary adapters and integration | NLE-PRPLAN-NET-05-03 | BLOCKED |
| 5 | NLE-PRPLAN-NET-05-05 | IMPLEMENTATION | resource limits and resilience | NLE-PRPLAN-NET-05-04 | BLOCKED |
| 6 | NLE-PRPLAN-NET-05-06 | IMPLEMENTATION | source/data compatibility | NLE-PRPLAN-NET-05-05 | BLOCKED |
| 7 | NLE-PRPLAN-NET-05-07 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-NET-05-06 | BLOCKED |
| 8 | NLE-PRPLAN-NET-05-08 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-NET-05-07 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-NET-05-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: NET-05 predecessors NET-01+NET-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar/join/leave, reconexão e falhas previsíveis sem SaaS obrigatório.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-NET-05-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: NET-05 predecessors NET-01+NET-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar/join/leave, reconexão e falhas previsíveis sem SaaS obrigatório.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: NLE-PRPLAN-NET-05-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-NET-05-03 / Match/session/lobby abstractions; integração com backend externo opcional
OBJECTIVE / SCOPE: Match/session/lobby abstractions; integração com backend externo opcional. CONTEXT: NET-05 predecessors NET-01+NET-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar/join/leave, reconexão e falhas previsíveis sem SaaS obrigatório.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Match/session/lobby abstractions; integração com backend externo opcional with valid/invalid fixtures, typed failures and jitter/loss/abuse validation. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: NLE-PRPLAN-NET-05-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-NET-05-04 / boundary adapters and integration
OBJECTIVE / SCOPE: boundary adapters and integration. CONTEXT: NET-05 predecessors NET-01+NET-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar/join/leave, reconexão e falhas previsíveis sem SaaS obrigatório.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise boundary adapters and integration with valid/invalid fixtures, typed failures and jitter/loss/abuse validation. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: NLE-PRPLAN-NET-05-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-NET-05-05 / resource limits and resilience
OBJECTIVE / SCOPE: resource limits and resilience. CONTEXT: NET-05 predecessors NET-01+NET-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar/join/leave, reconexão e falhas previsíveis sem SaaS obrigatório.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise resource limits and resilience with valid/invalid fixtures, typed failures and jitter/loss/abuse validation. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: NLE-PRPLAN-NET-05-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-NET-05-06 / source/data compatibility
OBJECTIVE / SCOPE: source/data compatibility. CONTEXT: NET-05 predecessors NET-01+NET-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar/join/leave, reconexão e falhas previsíveis sem SaaS obrigatório.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise source/data compatibility with valid/invalid fixtures, typed failures and jitter/loss/abuse validation. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: NLE-PRPLAN-NET-05-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-NET-05-07 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: NET-05 predecessors NET-01+NET-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar/join/leave, reconexão e falhas previsíveis sem SaaS obrigatório.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Criar/join/leave, reconexão e falhas previsíveis sem SaaS obrigatório.. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: NLE-PRPLAN-NET-05-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-NET-05-08 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: NET-05 predecessors NET-01+NET-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Criar/join/leave, reconexão e falhas previsíveis sem SaaS obrigatório.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: NLE-PRPLAN-NET-05-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
