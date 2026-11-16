# NET-02 — Authoritative Dedicated Server | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#63](https://github.com/KayzenRoot/stormline/issues/63). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Loop headless, simulação no servidor, validation commands e deployment local. | Formal predecessors: NET-01 + WORLD-01 + CORE-04 | Catalog acceptance: Servidor executa sem GPU e rejeita estado cliente arbitrário..
[Architecture](../architecture/net-02-authoritative-dedicated-server.md) · [Proposed ADR](../adr/0048-net-02-authoritative-headless-server-tick-command-gateway.md) · [Original blocked code WO](../queue/work-orders/NET-02.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-NET-02-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-NET-02-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-NET-02-01 | BLOCKED |
| 3 | NLE-PRPLAN-NET-02-03 | IMPLEMENTATION | Loop headless | NLE-PRPLAN-NET-02-02 | BLOCKED |
| 4 | NLE-PRPLAN-NET-02-04 | IMPLEMENTATION | simulação no servidor | NLE-PRPLAN-NET-02-03 | BLOCKED |
| 5 | NLE-PRPLAN-NET-02-05 | IMPLEMENTATION | validation commands | NLE-PRPLAN-NET-02-04 | BLOCKED |
| 6 | NLE-PRPLAN-NET-02-06 | IMPLEMENTATION | deployment local | NLE-PRPLAN-NET-02-05 | BLOCKED |
| 7 | NLE-PRPLAN-NET-02-07 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-NET-02-06 | BLOCKED |
| 8 | NLE-PRPLAN-NET-02-08 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-NET-02-07 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-NET-02-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: NET-02 predecessors NET-01+WORLD-01+CORE-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Servidor executa sem GPU e rejeita estado cliente arbitrário.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-NET-02-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: NET-02 predecessors NET-01+WORLD-01+CORE-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Servidor executa sem GPU e rejeita estado cliente arbitrário.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: NLE-PRPLAN-NET-02-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-NET-02-03 / Loop headless
OBJECTIVE / SCOPE: Loop headless. CONTEXT: NET-02 predecessors NET-01+WORLD-01+CORE-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Servidor executa sem GPU e rejeita estado cliente arbitrário.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Loop headless with valid/invalid fixtures, typed failures and jitter/loss/abuse validation. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: NLE-PRPLAN-NET-02-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-NET-02-04 / simulação no servidor
OBJECTIVE / SCOPE: simulação no servidor. CONTEXT: NET-02 predecessors NET-01+WORLD-01+CORE-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Servidor executa sem GPU e rejeita estado cliente arbitrário.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise simulação no servidor with valid/invalid fixtures, typed failures and jitter/loss/abuse validation. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: NLE-PRPLAN-NET-02-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-NET-02-05 / validation commands
OBJECTIVE / SCOPE: validation commands. CONTEXT: NET-02 predecessors NET-01+WORLD-01+CORE-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Servidor executa sem GPU e rejeita estado cliente arbitrário.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise validation commands with valid/invalid fixtures, typed failures and jitter/loss/abuse validation. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: NLE-PRPLAN-NET-02-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-NET-02-06 / deployment local
OBJECTIVE / SCOPE: deployment local. CONTEXT: NET-02 predecessors NET-01+WORLD-01+CORE-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Servidor executa sem GPU e rejeita estado cliente arbitrário.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise deployment local with valid/invalid fixtures, typed failures and jitter/loss/abuse validation. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: NLE-PRPLAN-NET-02-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-NET-02-07 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: NET-02 predecessors NET-01+WORLD-01+CORE-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Servidor executa sem GPU e rejeita estado cliente arbitrário.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Servidor executa sem GPU e rejeita estado cliente arbitrário.. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: NLE-PRPLAN-NET-02-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-NET-02-08 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: NET-02 predecessors NET-01+WORLD-01+CORE-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Servidor executa sem GPU e rejeita estado cliente arbitrário.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE jitter/loss/abuse validation, never run in this plan. DEPENDENCIES: NLE-PRPLAN-NET-02-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
