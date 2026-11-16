# SIM-01 — Physics 2D | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#46](https://github.com/KayzenRoot/stormline/issues/46). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Corpos rígidos 2D, colisão, queries, joints, triggers e máscaras. | Formal predecessors: WORLD-01 + TWO-01 | Catalog acceptance: Suite 2D de colisão, estabilidade e stress..
[Architecture](../architecture/sim-01-physics-2d.md) · [Proposed ADR](../adr/0031-sim-01-physics-2d-fixedstep-backend-policy.md) · [Original blocked code WO](../queue/work-orders/SIM-01.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-SIM-01-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-SIM-01-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-SIM-01-01 | BLOCKED |
| 3 | NLE-PRPLAN-SIM-01-03 | IMPLEMENTATION | Corpos rígidos 2D | NLE-PRPLAN-SIM-01-02 | BLOCKED |
| 4 | NLE-PRPLAN-SIM-01-04 | IMPLEMENTATION | colisão | NLE-PRPLAN-SIM-01-03 | BLOCKED |
| 5 | NLE-PRPLAN-SIM-01-05 | IMPLEMENTATION | queries | NLE-PRPLAN-SIM-01-04 | BLOCKED |
| 6 | NLE-PRPLAN-SIM-01-06 | IMPLEMENTATION | joints | NLE-PRPLAN-SIM-01-05 | BLOCKED |
| 7 | NLE-PRPLAN-SIM-01-07 | IMPLEMENTATION | triggers | NLE-PRPLAN-SIM-01-06 | BLOCKED |
| 8 | NLE-PRPLAN-SIM-01-08 | IMPLEMENTATION | máscaras | NLE-PRPLAN-SIM-01-07 | BLOCKED |
| 9 | NLE-PRPLAN-SIM-01-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-SIM-01-08 | BLOCKED |
| 10 | NLE-PRPLAN-SIM-01-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-SIM-01-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-SIM-01-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: SIM-01 predecessors WORLD-01+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Suite 2D de colisão, estabilidade e stress.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-01-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: SIM-01 predecessors WORLD-01+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Suite 2D de colisão, estabilidade e stress.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-01-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-01-03 / Corpos rígidos 2D
OBJECTIVE / SCOPE: Corpos rígidos 2D. CONTEXT: SIM-01 predecessors WORLD-01+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Suite 2D de colisão, estabilidade e stress.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Corpos rígidos 2D with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-01-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-01-04 / colisão
OBJECTIVE / SCOPE: colisão. CONTEXT: SIM-01 predecessors WORLD-01+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Suite 2D de colisão, estabilidade e stress.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise colisão with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-01-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-01-05 / queries
OBJECTIVE / SCOPE: queries. CONTEXT: SIM-01 predecessors WORLD-01+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Suite 2D de colisão, estabilidade e stress.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise queries with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-01-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-01-06 / joints
OBJECTIVE / SCOPE: joints. CONTEXT: SIM-01 predecessors WORLD-01+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Suite 2D de colisão, estabilidade e stress.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise joints with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-01-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-01-07 / triggers
OBJECTIVE / SCOPE: triggers. CONTEXT: SIM-01 predecessors WORLD-01+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Suite 2D de colisão, estabilidade e stress.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise triggers with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-01-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-01-08 / máscaras
OBJECTIVE / SCOPE: máscaras. CONTEXT: SIM-01 predecessors WORLD-01+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Suite 2D de colisão, estabilidade e stress.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise máscaras with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-01-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-01-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: SIM-01 predecessors WORLD-01+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Suite 2D de colisão, estabilidade e stress.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Suite 2D de colisão, estabilidade e stress.. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-01-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-01-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: SIM-01 predecessors WORLD-01+TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Suite 2D de colisão, estabilidade e stress.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-01-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
