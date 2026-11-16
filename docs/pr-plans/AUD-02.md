# AUD-02 — Spatial Audio & Acoustic World | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#53](https://github.com/KayzenRoot/stormline/issues/53). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: HRTF/opções de spatialization, atenuação, oclusão, reverberação e salas. | Formal predecessors: AUD-01 + WORLD-02 | Catalog acceptance: Cenário de posições/obstáculos com áudio validado e custos medidos..
[Architecture](../architecture/aud-02-spatial-audio-acoustic-world.md) · [Proposed ADR](../adr/0039-aud-02-engine-owned-acoustics-and-binaural-authority.md) · [Original blocked code WO](../queue/work-orders/AUD-02.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-AUD-02-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-AUD-02-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-AUD-02-01 | BLOCKED |
| 3 | NLE-PRPLAN-AUD-02-03 | IMPLEMENTATION | HRTF/opções de spatialization | NLE-PRPLAN-AUD-02-02 | BLOCKED |
| 4 | NLE-PRPLAN-AUD-02-04 | IMPLEMENTATION | atenuação | NLE-PRPLAN-AUD-02-03 | BLOCKED |
| 5 | NLE-PRPLAN-AUD-02-05 | IMPLEMENTATION | oclusão | NLE-PRPLAN-AUD-02-04 | BLOCKED |
| 6 | NLE-PRPLAN-AUD-02-06 | IMPLEMENTATION | reverberação | NLE-PRPLAN-AUD-02-05 | BLOCKED |
| 7 | NLE-PRPLAN-AUD-02-07 | IMPLEMENTATION | salas | NLE-PRPLAN-AUD-02-06 | BLOCKED |
| 8 | NLE-PRPLAN-AUD-02-08 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-AUD-02-07 | BLOCKED |
| 9 | NLE-PRPLAN-AUD-02-09 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-AUD-02-08 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-AUD-02-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: AUD-02 predecessors AUD-01+WORLD-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenário de posições/obstáculos com áudio validado e custos medidos.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-02-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: AUD-02 predecessors AUD-01+WORLD-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenário de posições/obstáculos com áudio validado e custos medidos.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-02-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-02-03 / HRTF/opções de spatialization
OBJECTIVE / SCOPE: HRTF/opções de spatialization. CONTEXT: AUD-02 predecessors AUD-01+WORLD-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenário de posições/obstáculos com áudio validado e custos medidos.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise HRTF/opções de spatialization with valid/invalid fixtures, typed failures and audio xrun/latency/device tests. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-02-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-02-04 / atenuação
OBJECTIVE / SCOPE: atenuação. CONTEXT: AUD-02 predecessors AUD-01+WORLD-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenário de posições/obstáculos com áudio validado e custos medidos.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise atenuação with valid/invalid fixtures, typed failures and audio xrun/latency/device tests. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-02-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-02-05 / oclusão
OBJECTIVE / SCOPE: oclusão. CONTEXT: AUD-02 predecessors AUD-01+WORLD-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenário de posições/obstáculos com áudio validado e custos medidos.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise oclusão with valid/invalid fixtures, typed failures and audio xrun/latency/device tests. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-02-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-02-06 / reverberação
OBJECTIVE / SCOPE: reverberação. CONTEXT: AUD-02 predecessors AUD-01+WORLD-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenário de posições/obstáculos com áudio validado e custos medidos.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise reverberação with valid/invalid fixtures, typed failures and audio xrun/latency/device tests. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-02-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-02-07 / salas
OBJECTIVE / SCOPE: salas. CONTEXT: AUD-02 predecessors AUD-01+WORLD-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenário de posições/obstáculos com áudio validado e custos medidos.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise salas with valid/invalid fixtures, typed failures and audio xrun/latency/device tests. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-02-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-02-08 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: AUD-02 predecessors AUD-01+WORLD-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenário de posições/obstáculos com áudio validado e custos medidos.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Cenário de posições/obstáculos com áudio validado e custos medidos.. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-02-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-02-09 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: AUD-02 predecessors AUD-01+WORLD-02. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenário de posições/obstáculos com áudio validado e custos medidos.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-02-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
