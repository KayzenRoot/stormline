# CORE-02 — Memory & Allocators | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#19](https://github.com/KayzenRoot/stormline/issues/19). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Ownership, alocadores, arenas, budgets, leak tracking e telemetria de memória. | Formal predecessors: CORE-01 | Catalog acceptance: Comparar allocators e detectar vazamentos em carga reproduzível..
[Architecture](../architecture/core-02-memory-allocators.md) · [Proposed ADR](../adr/0004-core-02-memory-policy.md) · [Original blocked code WO](../queue/work-orders/CORE-02.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-CORE-02-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-CORE-02-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-CORE-02-01 | BLOCKED |
| 3 | NLE-PRPLAN-CORE-02-03 | IMPLEMENTATION | Ownership | NLE-PRPLAN-CORE-02-02 | BLOCKED |
| 4 | NLE-PRPLAN-CORE-02-04 | IMPLEMENTATION | alocadores | NLE-PRPLAN-CORE-02-03 | BLOCKED |
| 5 | NLE-PRPLAN-CORE-02-05 | IMPLEMENTATION | arenas | NLE-PRPLAN-CORE-02-04 | BLOCKED |
| 6 | NLE-PRPLAN-CORE-02-06 | IMPLEMENTATION | budgets | NLE-PRPLAN-CORE-02-05 | BLOCKED |
| 7 | NLE-PRPLAN-CORE-02-07 | IMPLEMENTATION | leak tracking | NLE-PRPLAN-CORE-02-06 | BLOCKED |
| 8 | NLE-PRPLAN-CORE-02-08 | IMPLEMENTATION | telemetria de memória | NLE-PRPLAN-CORE-02-07 | BLOCKED |
| 9 | NLE-PRPLAN-CORE-02-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-CORE-02-08 | BLOCKED |
| 10 | NLE-PRPLAN-CORE-02-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-CORE-02-09 | BLOCKED |

The table above is the historical all-blocked map. The owner-approved capability-based gate [PR #440](https://github.com/KayzenRoot/stormline/pull/440) activated only `NLE-PRPLAN-CORE-02-03`; [PR #441](https://github.com/KayzenRoot/stormline/pull/441) merged the ownership slice as `ab12abd…`. `CORE-02-03` is now `COMPLETED`; `CORE-02-01/-02` are approved gate entries; every other CORE-02 packet remains `PLANNED_BLOCKED`. This does not approve ADR-0004, complete CORE-02 or authorize `-04`.

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-CORE-02-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: CORE-02 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Comparar allocators e detectar vazamentos em carga reproduzível.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-02-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: CORE-02 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Comparar allocators e detectar vazamentos em carga reproduzível.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-02-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-02-03 / Ownership
OBJECTIVE / SCOPE: Ownership. CONTEXT: CORE-02 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Comparar allocators e detectar vazamentos em carga reproduzível.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Ownership with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-02-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-02-04 / alocadores
OBJECTIVE / SCOPE: alocadores. CONTEXT: CORE-02 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Comparar allocators e detectar vazamentos em carga reproduzível.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise alocadores with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-02-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-02-05 / arenas
OBJECTIVE / SCOPE: arenas. CONTEXT: CORE-02 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Comparar allocators e detectar vazamentos em carga reproduzível.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise arenas with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-02-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-02-06 / budgets
OBJECTIVE / SCOPE: budgets. CONTEXT: CORE-02 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Comparar allocators e detectar vazamentos em carga reproduzível.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise budgets with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-02-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-02-07 / leak tracking
OBJECTIVE / SCOPE: leak tracking. CONTEXT: CORE-02 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Comparar allocators e detectar vazamentos em carga reproduzível.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise leak tracking with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-02-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-02-08 / telemetria de memória
OBJECTIVE / SCOPE: telemetria de memória. CONTEXT: CORE-02 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Comparar allocators e detectar vazamentos em carga reproduzível.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise telemetria de memória with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-02-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-02-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: CORE-02 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Comparar allocators e detectar vazamentos em carga reproduzível.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Comparar allocators e detectar vazamentos em carga reproduzível.. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-02-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-02-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: CORE-02 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Comparar allocators e detectar vazamentos em carga reproduzível.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-02-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
