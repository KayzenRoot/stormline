# AUD-01 — Audio Device & Mixer | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#52](https://github.com/KayzenRoot/stormline/issues/52). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Output multi-device, sample-rate, buses, voz virtualizada, streaming e limites. | Formal predecessors: CORE-01 + CORE-03 | Catalog acceptance: Testes de underruns, latência e custo por quantidade de vozes..
[Architecture](../architecture/aud-01-audio-device-mixer.md) · [Proposed ADR](../adr/0038-aud-01-real-time-audio-mixer-and-device-authority.md) · [Original blocked code WO](../queue/work-orders/AUD-01.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-AUD-01-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-AUD-01-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-AUD-01-01 | BLOCKED |
| 3 | NLE-PRPLAN-AUD-01-03 | IMPLEMENTATION | Output multi-device | NLE-PRPLAN-AUD-01-02 | BLOCKED |
| 4 | NLE-PRPLAN-AUD-01-04 | IMPLEMENTATION | sample-rate | NLE-PRPLAN-AUD-01-03 | BLOCKED |
| 5 | NLE-PRPLAN-AUD-01-05 | IMPLEMENTATION | buses | NLE-PRPLAN-AUD-01-04 | BLOCKED |
| 6 | NLE-PRPLAN-AUD-01-06 | IMPLEMENTATION | voz virtualizada | NLE-PRPLAN-AUD-01-05 | BLOCKED |
| 7 | NLE-PRPLAN-AUD-01-07 | IMPLEMENTATION | streaming | NLE-PRPLAN-AUD-01-06 | BLOCKED |
| 8 | NLE-PRPLAN-AUD-01-08 | IMPLEMENTATION | limites | NLE-PRPLAN-AUD-01-07 | BLOCKED |
| 9 | NLE-PRPLAN-AUD-01-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-AUD-01-08 | BLOCKED |
| 10 | NLE-PRPLAN-AUD-01-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-AUD-01-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-AUD-01-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: AUD-01 predecessors CORE-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de underruns, latência e custo por quantidade de vozes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-01-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: AUD-01 predecessors CORE-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de underruns, latência e custo por quantidade de vozes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-01-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-01-03 / Output multi-device
OBJECTIVE / SCOPE: Output multi-device. CONTEXT: AUD-01 predecessors CORE-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de underruns, latência e custo por quantidade de vozes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Output multi-device with valid/invalid fixtures, typed failures and audio xrun/latency/device tests. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-01-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-01-04 / sample-rate
OBJECTIVE / SCOPE: sample-rate. CONTEXT: AUD-01 predecessors CORE-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de underruns, latência e custo por quantidade de vozes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise sample-rate with valid/invalid fixtures, typed failures and audio xrun/latency/device tests. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-01-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-01-05 / buses
OBJECTIVE / SCOPE: buses. CONTEXT: AUD-01 predecessors CORE-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de underruns, latência e custo por quantidade de vozes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise buses with valid/invalid fixtures, typed failures and audio xrun/latency/device tests. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-01-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-01-06 / voz virtualizada
OBJECTIVE / SCOPE: voz virtualizada. CONTEXT: AUD-01 predecessors CORE-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de underruns, latência e custo por quantidade de vozes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise voz virtualizada with valid/invalid fixtures, typed failures and audio xrun/latency/device tests. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-01-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-01-07 / streaming
OBJECTIVE / SCOPE: streaming. CONTEXT: AUD-01 predecessors CORE-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de underruns, latência e custo por quantidade de vozes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise streaming with valid/invalid fixtures, typed failures and audio xrun/latency/device tests. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-01-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-01-08 / limites
OBJECTIVE / SCOPE: limites. CONTEXT: AUD-01 predecessors CORE-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de underruns, latência e custo por quantidade de vozes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise limites with valid/invalid fixtures, typed failures and audio xrun/latency/device tests. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-01-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-01-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: AUD-01 predecessors CORE-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de underruns, latência e custo por quantidade de vozes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Testes de underruns, latência e custo por quantidade de vozes.. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-01-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-AUD-01-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: AUD-01 predecessors CORE-01+CORE-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de underruns, latência e custo por quantidade de vozes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE audio xrun/latency/device tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-AUD-01-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
