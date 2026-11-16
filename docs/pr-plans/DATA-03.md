# DATA-03 — Import & Conversion Pipeline | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#26](https://github.com/KayzenRoot/stormline/issues/26). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Importadores 2D/3D, texturas, animações, áudio, validação e relatórios de origem. | Formal predecessors: DATA-02 | Catalog acceptance: Reimport idempotente sem perder edição derivada..
[Architecture](../architecture/data-03-import-conversion-pipeline.md) · [Proposed ADR](../adr/0011-data-03-import-policy.md) · [Original blocked code WO](../queue/work-orders/DATA-03.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-DATA-03-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-DATA-03-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-DATA-03-01 | BLOCKED |
| 3 | NLE-PRPLAN-DATA-03-03 | IMPLEMENTATION | Importadores 2D/3D | NLE-PRPLAN-DATA-03-02 | BLOCKED |
| 4 | NLE-PRPLAN-DATA-03-04 | IMPLEMENTATION | texturas | NLE-PRPLAN-DATA-03-03 | BLOCKED |
| 5 | NLE-PRPLAN-DATA-03-05 | IMPLEMENTATION | animações | NLE-PRPLAN-DATA-03-04 | BLOCKED |
| 6 | NLE-PRPLAN-DATA-03-06 | IMPLEMENTATION | áudio | NLE-PRPLAN-DATA-03-05 | BLOCKED |
| 7 | NLE-PRPLAN-DATA-03-07 | IMPLEMENTATION | validação | NLE-PRPLAN-DATA-03-06 | BLOCKED |
| 8 | NLE-PRPLAN-DATA-03-08 | IMPLEMENTATION | relatórios de origem | NLE-PRPLAN-DATA-03-07 | BLOCKED |
| 9 | NLE-PRPLAN-DATA-03-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-DATA-03-08 | BLOCKED |
| 10 | NLE-PRPLAN-DATA-03-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-DATA-03-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-DATA-03-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: DATA-03 predecessors DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reimport idempotente sem perder edição derivada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-03-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: DATA-03 predecessors DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reimport idempotente sem perder edição derivada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-03-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-03-03 / Importadores 2D/3D
OBJECTIVE / SCOPE: Importadores 2D/3D. CONTEXT: DATA-03 predecessors DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reimport idempotente sem perder edição derivada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Importadores 2D/3D with valid/invalid fixtures, typed failures and schema/roundtrip/corruption/rollback tests. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-03-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-03-04 / texturas
OBJECTIVE / SCOPE: texturas. CONTEXT: DATA-03 predecessors DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reimport idempotente sem perder edição derivada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise texturas with valid/invalid fixtures, typed failures and schema/roundtrip/corruption/rollback tests. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-03-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-03-05 / animações
OBJECTIVE / SCOPE: animações. CONTEXT: DATA-03 predecessors DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reimport idempotente sem perder edição derivada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise animações with valid/invalid fixtures, typed failures and schema/roundtrip/corruption/rollback tests. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-03-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-03-06 / áudio
OBJECTIVE / SCOPE: áudio. CONTEXT: DATA-03 predecessors DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reimport idempotente sem perder edição derivada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise áudio with valid/invalid fixtures, typed failures and schema/roundtrip/corruption/rollback tests. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-03-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-03-07 / validação
OBJECTIVE / SCOPE: validação. CONTEXT: DATA-03 predecessors DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reimport idempotente sem perder edição derivada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise validação with valid/invalid fixtures, typed failures and schema/roundtrip/corruption/rollback tests. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-03-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-03-08 / relatórios de origem
OBJECTIVE / SCOPE: relatórios de origem. CONTEXT: DATA-03 predecessors DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reimport idempotente sem perder edição derivada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise relatórios de origem with valid/invalid fixtures, typed failures and schema/roundtrip/corruption/rollback tests. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-03-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-03-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: DATA-03 predecessors DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reimport idempotente sem perder edição derivada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Reimport idempotente sem perder edição derivada.. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-03-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-03-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: DATA-03 predecessors DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Reimport idempotente sem perder edição derivada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-03-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
