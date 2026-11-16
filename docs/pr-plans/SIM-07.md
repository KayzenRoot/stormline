# SIM-07 — Vehicles & Flight Dynamics | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#57](https://github.com/KayzenRoot/stormline/issues/57). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Wheeled/tracked vehicles, suspension, boats, rotor/wing flight dynamics, control interfaces, audiovisual hooks and networked simulation. | Formal predecessors: SIM-02 + SIM-03 + GAME-01 | Catalog acceptance: Original drivable tank, truck and aircraft/rotorcraft reference tests with reproducible physics and network timing..
[Architecture](../architecture/sim-07-vehicles-flight-dynamics.md) · [Proposed ADR](../adr/0037-sim-07-single-authority-vehicle-flight-dynamics.md) · [Original blocked code WO](../queue/work-orders/SIM-07.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-SIM-07-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-SIM-07-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-SIM-07-01 | BLOCKED |
| 3 | NLE-PRPLAN-SIM-07-03 | IMPLEMENTATION | Wheeled/tracked vehicles | NLE-PRPLAN-SIM-07-02 | BLOCKED |
| 4 | NLE-PRPLAN-SIM-07-04 | IMPLEMENTATION | suspension | NLE-PRPLAN-SIM-07-03 | BLOCKED |
| 5 | NLE-PRPLAN-SIM-07-05 | IMPLEMENTATION | boats | NLE-PRPLAN-SIM-07-04 | BLOCKED |
| 6 | NLE-PRPLAN-SIM-07-06 | IMPLEMENTATION | rotor/wing flight dynamics | NLE-PRPLAN-SIM-07-05 | BLOCKED |
| 7 | NLE-PRPLAN-SIM-07-07 | IMPLEMENTATION | control interfaces | NLE-PRPLAN-SIM-07-06 | BLOCKED |
| 8 | NLE-PRPLAN-SIM-07-08 | IMPLEMENTATION | audiovisual hooks | NLE-PRPLAN-SIM-07-07 | BLOCKED |
| 9 | NLE-PRPLAN-SIM-07-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-SIM-07-08 | BLOCKED |
| 10 | NLE-PRPLAN-SIM-07-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-SIM-07-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-SIM-07-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: SIM-07 predecessors SIM-02+SIM-03+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Original drivable tank, truck and aircraft/rotorcraft reference tests with reproducible physics and network timing.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-07-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: SIM-07 predecessors SIM-02+SIM-03+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Original drivable tank, truck and aircraft/rotorcraft reference tests with reproducible physics and network timing.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-07-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-07-03 / Wheeled/tracked vehicles
OBJECTIVE / SCOPE: Wheeled/tracked vehicles. CONTEXT: SIM-07 predecessors SIM-02+SIM-03+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Original drivable tank, truck and aircraft/rotorcraft reference tests with reproducible physics and network timing.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Wheeled/tracked vehicles with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-07-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-07-04 / suspension
OBJECTIVE / SCOPE: suspension. CONTEXT: SIM-07 predecessors SIM-02+SIM-03+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Original drivable tank, truck and aircraft/rotorcraft reference tests with reproducible physics and network timing.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise suspension with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-07-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-07-05 / boats
OBJECTIVE / SCOPE: boats. CONTEXT: SIM-07 predecessors SIM-02+SIM-03+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Original drivable tank, truck and aircraft/rotorcraft reference tests with reproducible physics and network timing.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise boats with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-07-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-07-06 / rotor/wing flight dynamics
OBJECTIVE / SCOPE: rotor/wing flight dynamics. CONTEXT: SIM-07 predecessors SIM-02+SIM-03+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Original drivable tank, truck and aircraft/rotorcraft reference tests with reproducible physics and network timing.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise rotor/wing flight dynamics with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-07-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-07-07 / control interfaces
OBJECTIVE / SCOPE: control interfaces. CONTEXT: SIM-07 predecessors SIM-02+SIM-03+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Original drivable tank, truck and aircraft/rotorcraft reference tests with reproducible physics and network timing.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise control interfaces with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-07-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-07-08 / audiovisual hooks
OBJECTIVE / SCOPE: audiovisual hooks. CONTEXT: SIM-07 predecessors SIM-02+SIM-03+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Original drivable tank, truck and aircraft/rotorcraft reference tests with reproducible physics and network timing.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise audiovisual hooks with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-07-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-07-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: SIM-07 predecessors SIM-02+SIM-03+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Original drivable tank, truck and aircraft/rotorcraft reference tests with reproducible physics and network timing.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Original drivable tank, truck and aircraft/rotorcraft reference tests with reproducible physics and network timing.. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-07-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-07-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: SIM-07 predecessors SIM-02+SIM-03+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Original drivable tank, truck and aircraft/rotorcraft reference tests with reproducible physics and network timing.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-07-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
