# SIM-04 — Skeletal Animation & Motion | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#49](https://github.com/KayzenRoot/stormline/issues/49). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Retargeting, blend trees, IK, ragdoll, compressão, sync e root motion. | Formal predecessors: SIM-03 + DATA-03 | Catalog acceptance: Animação de locomotion/combat com transições coerentes e custo medido..
[Architecture](../architecture/sim-04-skeletal-animation-motion.md) · [Proposed ADR](../adr/0034-sim-04-animation-authority-retarget-ik-and-ragdoll.md) · [Original blocked code WO](../queue/work-orders/SIM-04.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-SIM-04-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-SIM-04-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-SIM-04-01 | BLOCKED |
| 3 | NLE-PRPLAN-SIM-04-03 | IMPLEMENTATION | Retargeting | NLE-PRPLAN-SIM-04-02 | BLOCKED |
| 4 | NLE-PRPLAN-SIM-04-04 | IMPLEMENTATION | blend trees | NLE-PRPLAN-SIM-04-03 | BLOCKED |
| 5 | NLE-PRPLAN-SIM-04-05 | IMPLEMENTATION | IK | NLE-PRPLAN-SIM-04-04 | BLOCKED |
| 6 | NLE-PRPLAN-SIM-04-06 | IMPLEMENTATION | ragdoll | NLE-PRPLAN-SIM-04-05 | BLOCKED |
| 7 | NLE-PRPLAN-SIM-04-07 | IMPLEMENTATION | compressão | NLE-PRPLAN-SIM-04-06 | BLOCKED |
| 8 | NLE-PRPLAN-SIM-04-08 | IMPLEMENTATION | sync | NLE-PRPLAN-SIM-04-07 | BLOCKED |
| 9 | NLE-PRPLAN-SIM-04-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-SIM-04-08 | BLOCKED |
| 10 | NLE-PRPLAN-SIM-04-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-SIM-04-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-SIM-04-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: SIM-04 predecessors SIM-03+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Animação de locomotion/combat com transições coerentes e custo medido.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-04-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: SIM-04 predecessors SIM-03+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Animação de locomotion/combat com transições coerentes e custo medido.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-04-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-04-03 / Retargeting
OBJECTIVE / SCOPE: Retargeting. CONTEXT: SIM-04 predecessors SIM-03+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Animação de locomotion/combat com transições coerentes e custo medido.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Retargeting with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-04-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-04-04 / blend trees
OBJECTIVE / SCOPE: blend trees. CONTEXT: SIM-04 predecessors SIM-03+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Animação de locomotion/combat com transições coerentes e custo medido.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise blend trees with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-04-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-04-05 / IK
OBJECTIVE / SCOPE: IK. CONTEXT: SIM-04 predecessors SIM-03+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Animação de locomotion/combat com transições coerentes e custo medido.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise IK with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-04-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-04-06 / ragdoll
OBJECTIVE / SCOPE: ragdoll. CONTEXT: SIM-04 predecessors SIM-03+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Animação de locomotion/combat com transições coerentes e custo medido.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise ragdoll with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-04-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-04-07 / compressão
OBJECTIVE / SCOPE: compressão. CONTEXT: SIM-04 predecessors SIM-03+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Animação de locomotion/combat com transições coerentes e custo medido.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise compressão with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-04-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-04-08 / sync
OBJECTIVE / SCOPE: sync. CONTEXT: SIM-04 predecessors SIM-03+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Animação de locomotion/combat com transições coerentes e custo medido.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise sync with valid/invalid fixtures, typed failures and fixed-tick replay/numerical stress tests. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-04-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-04-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: SIM-04 predecessors SIM-03+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Animação de locomotion/combat com transições coerentes e custo medido.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Animação de locomotion/combat com transições coerentes e custo medido.. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-04-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-SIM-04-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: SIM-04 predecessors SIM-03+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Animação de locomotion/combat com transições coerentes e custo medido.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE fixed-tick replay/numerical stress tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-SIM-04-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
