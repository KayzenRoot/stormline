# CORE-06 — Diagnostics & Observability | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#23](https://github.com/KayzenRoot/stormline/issues/23). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Logs, traces, contadores, crashes, profiling e telemetria local opt-in. | Formal predecessors: CORE-01 | Catalog acceptance: Captura reproduzível de CPU frame/jobs, falha e rastreabilidade por build..
[Architecture](../architecture/core-06-diagnostics-observability.md) · [Proposed ADR](../adr/0008-core-06-observability-policy.md) · [Original blocked code WO](../queue/work-orders/CORE-06.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-CORE-06-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-CORE-06-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-CORE-06-01 | BLOCKED |
| 3 | NLE-PRPLAN-CORE-06-03 | IMPLEMENTATION | Logs | NLE-PRPLAN-CORE-06-02 | BLOCKED |
| 4 | NLE-PRPLAN-CORE-06-04 | IMPLEMENTATION | traces | NLE-PRPLAN-CORE-06-03 | BLOCKED |
| 5 | NLE-PRPLAN-CORE-06-05 | IMPLEMENTATION | contadores | NLE-PRPLAN-CORE-06-04 | BLOCKED |
| 6 | NLE-PRPLAN-CORE-06-06 | IMPLEMENTATION | crashes | NLE-PRPLAN-CORE-06-05 | BLOCKED |
| 7 | NLE-PRPLAN-CORE-06-07 | IMPLEMENTATION | profiling | NLE-PRPLAN-CORE-06-06 | BLOCKED |
| 8 | NLE-PRPLAN-CORE-06-08 | IMPLEMENTATION | telemetria local opt-in | NLE-PRPLAN-CORE-06-07 | BLOCKED |
| 9 | NLE-PRPLAN-CORE-06-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-CORE-06-08 | BLOCKED |
| 10 | NLE-PRPLAN-CORE-06-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-CORE-06-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-CORE-06-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: CORE-06 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Captura reproduzível de CPU frame/jobs, falha e rastreabilidade por build.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-06-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: CORE-06 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Captura reproduzível de CPU frame/jobs, falha e rastreabilidade por build.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-06-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-06-03 / Logs
OBJECTIVE / SCOPE: Logs. CONTEXT: CORE-06 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Captura reproduzível de CPU frame/jobs, falha e rastreabilidade por build.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Logs with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-06-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-06-04 / traces
OBJECTIVE / SCOPE: traces. CONTEXT: CORE-06 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Captura reproduzível de CPU frame/jobs, falha e rastreabilidade por build.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise traces with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-06-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-06-05 / contadores
OBJECTIVE / SCOPE: contadores. CONTEXT: CORE-06 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Captura reproduzível de CPU frame/jobs, falha e rastreabilidade por build.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise contadores with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-06-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-06-06 / crashes
OBJECTIVE / SCOPE: crashes. CONTEXT: CORE-06 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Captura reproduzível de CPU frame/jobs, falha e rastreabilidade por build.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise crashes with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-06-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-06-07 / profiling
OBJECTIVE / SCOPE: profiling. CONTEXT: CORE-06 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Captura reproduzível de CPU frame/jobs, falha e rastreabilidade por build.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise profiling with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-06-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-06-08 / telemetria local opt-in
OBJECTIVE / SCOPE: telemetria local opt-in. CONTEXT: CORE-06 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Captura reproduzível de CPU frame/jobs, falha e rastreabilidade por build.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise telemetria local opt-in with valid/invalid fixtures, typed failures and state/lifetime/cross-platform unit tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-06-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-06-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: CORE-06 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Captura reproduzível de CPU frame/jobs, falha e rastreabilidade por build.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Captura reproduzível de CPU frame/jobs, falha e rastreabilidade por build.. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-06-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-06-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: CORE-06 predecessors CORE-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Captura reproduzível de CPU frame/jobs, falha e rastreabilidade por build.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-06-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
