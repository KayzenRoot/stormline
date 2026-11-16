# SIM-03 — Character Controller & Movement | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#48](https://github.com/KayzenRoot/stormline/issues/48). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Kinematic/dynamic controllers 2D/3D, locomoção, input response e câmera desacoplada. | Formal predecessors: SIM-01 + SIM-02 | Catalog acceptance: Golden replay de movimento e variação de FPS..
[Architecture](../architecture/sim-03-character-controller-movement.md) · [Proposed ADR](../adr/0033-sim-03-authoritative-character-motor-policy.md) · [Original blocked code WO](../queue/work-orders/SIM-03.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-SIM-03-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-SIM-03-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-SIM-03-01 | BLOCKED |
| 3 | NLE-PRPLAN-SIM-03-03 | IMPLEMENTATION | Kinematic/dynamic controllers 2D/3D | NLE-PRPLAN-SIM-03-02 | BLOCKED |
| 4 | NLE-PRPLAN-SIM-03-04 | IMPLEMENTATION | locomoção | NLE-PRPLAN-SIM-03-03 | BLOCKED |
| 5 | NLE-PRPLAN-SIM-03-05 | IMPLEMENTATION | input response | NLE-PRPLAN-SIM-03-04 | BLOCKED |
| 6 | NLE-PRPLAN-SIM-03-06 | IMPLEMENTATION | câmera desacoplada | NLE-PRPLAN-SIM-03-05 | BLOCKED |
| 7 | NLE-PRPLAN-SIM-03-07 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-SIM-03-06 | BLOCKED |
| 8 | NLE-PRPLAN-SIM-03-08 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-SIM-03-07 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-SIM-03-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: SIM-03 predecessors SIM-01+SIM-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Golden replay de movimento e variação de FPS.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-03-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: SIM-03 predecessors SIM-01+SIM-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Golden replay de movimento e variação de FPS.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-03-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-03-03 / Kinematic/dynamic controllers 2D/3D
OBJECTIVE / SCOPE: Kinematic/dynamic controllers 2D/3D. CONTEXT: SIM-03 predecessors SIM-01+SIM-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Golden replay de movimento e variação de FPS.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Kinematic/dynamic controllers 2D/3D with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-03-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-03-04 / locomoção
OBJECTIVE / SCOPE: locomoção. CONTEXT: SIM-03 predecessors SIM-01+SIM-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Golden replay de movimento e variação de FPS.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise locomoção with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-03-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-03-05 / input response
OBJECTIVE / SCOPE: input response. CONTEXT: SIM-03 predecessors SIM-01+SIM-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Golden replay de movimento e variação de FPS.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise input response with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-03-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-03-06 / câmera desacoplada
OBJECTIVE / SCOPE: câmera desacoplada. CONTEXT: SIM-03 predecessors SIM-01+SIM-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Golden replay de movimento e variação de FPS.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise câmera desacoplada with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-03-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-03-07 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: SIM-03 predecessors SIM-01+SIM-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Golden replay de movimento e variação de FPS.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Golden replay de movimento e variação de FPS.. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-03-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-03-08 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: SIM-03 predecessors SIM-01+SIM-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Golden replay de movimento e variação de FPS.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-03-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
