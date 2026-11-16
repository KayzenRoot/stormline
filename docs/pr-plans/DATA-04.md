# DATA-04 — Serialization & Scene Format | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#27](https://github.com/KayzenRoot/stormline/issues/27). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Schemas versionados, representação declarativa, mudanças compatíveis e diffs semânticos. | Formal predecessors: CORE-05 + DATA-02 | Catalog acceptance: Round-trip equivalente; diff estruturado e migração testada..
[Architecture](../architecture/data-04-serialization-scene-format.md) · [Proposed ADR](../adr/0012-data-04-scene-schema-policy.md) · [Original blocked code WO](../queue/work-orders/DATA-04.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-DATA-04-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-DATA-04-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-DATA-04-01 | BLOCKED |
| 3 | NLE-PRPLAN-DATA-04-03 | IMPLEMENTATION | Schemas versionados | NLE-PRPLAN-DATA-04-02 | BLOCKED |
| 4 | NLE-PRPLAN-DATA-04-04 | IMPLEMENTATION | representação declarativa | NLE-PRPLAN-DATA-04-03 | BLOCKED |
| 5 | NLE-PRPLAN-DATA-04-05 | IMPLEMENTATION | mudanças compatíveis | NLE-PRPLAN-DATA-04-04 | BLOCKED |
| 6 | NLE-PRPLAN-DATA-04-06 | IMPLEMENTATION | diffs semânticos | NLE-PRPLAN-DATA-04-05 | BLOCKED |
| 7 | NLE-PRPLAN-DATA-04-07 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-DATA-04-06 | BLOCKED |
| 8 | NLE-PRPLAN-DATA-04-08 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-DATA-04-07 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-DATA-04-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: DATA-04 predecessors CORE-05+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Round-trip equivalente; diff estruturado e migração testada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-04-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: DATA-04 predecessors CORE-05+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Round-trip equivalente; diff estruturado e migração testada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-04-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-04-03 / Schemas versionados
OBJECTIVE / SCOPE: Schemas versionados. CONTEXT: DATA-04 predecessors CORE-05+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Round-trip equivalente; diff estruturado e migração testada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Schemas versionados with valid/invalid fixtures, typed failures and schema/roundtrip/corruption/rollback tests. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-04-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-04-04 / representação declarativa
OBJECTIVE / SCOPE: representação declarativa. CONTEXT: DATA-04 predecessors CORE-05+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Round-trip equivalente; diff estruturado e migração testada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise representação declarativa with valid/invalid fixtures, typed failures and schema/roundtrip/corruption/rollback tests. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-04-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-04-05 / mudanças compatíveis
OBJECTIVE / SCOPE: mudanças compatíveis. CONTEXT: DATA-04 predecessors CORE-05+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Round-trip equivalente; diff estruturado e migração testada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise mudanças compatíveis with valid/invalid fixtures, typed failures and schema/roundtrip/corruption/rollback tests. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-04-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-04-06 / diffs semânticos
OBJECTIVE / SCOPE: diffs semânticos. CONTEXT: DATA-04 predecessors CORE-05+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Round-trip equivalente; diff estruturado e migração testada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise diffs semânticos with valid/invalid fixtures, typed failures and schema/roundtrip/corruption/rollback tests. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-04-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-04-07 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: DATA-04 predecessors CORE-05+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Round-trip equivalente; diff estruturado e migração testada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Round-trip equivalente; diff estruturado e migração testada.. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-04-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-DATA-04-08 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: DATA-04 predecessors CORE-05+DATA-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Round-trip equivalente; diff estruturado e migração testada.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE schema/roundtrip/corruption/rollback tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-DATA-04-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
