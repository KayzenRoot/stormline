# GFX-04 — Geometry, Occlusion & LOD | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#32](https://github.com/KayzenRoot/stormline/issues/32). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Instancing, culling, HLOD, mesh streaming, vegetação e geometry optimization. | Formal predecessors: GFX-03 + DATA-05 | Catalog acceptance: Grande cena com culling correto e evidência de custo..
[Architecture](../architecture/gfx-04-geometry-visibility-lod.md) · [Proposed ADR](../adr/0017-gfx-04-visibility-geometry-policy.md) · [Original blocked code WO](../queue/work-orders/GFX-04.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-GFX-04-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-GFX-04-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-GFX-04-01 | BLOCKED |
| 3 | NLE-PRPLAN-GFX-04-03 | IMPLEMENTATION | Instancing | NLE-PRPLAN-GFX-04-02 | BLOCKED |
| 4 | NLE-PRPLAN-GFX-04-04 | IMPLEMENTATION | culling | NLE-PRPLAN-GFX-04-03 | BLOCKED |
| 5 | NLE-PRPLAN-GFX-04-05 | IMPLEMENTATION | HLOD | NLE-PRPLAN-GFX-04-04 | BLOCKED |
| 6 | NLE-PRPLAN-GFX-04-06 | IMPLEMENTATION | mesh streaming | NLE-PRPLAN-GFX-04-05 | BLOCKED |
| 7 | NLE-PRPLAN-GFX-04-07 | IMPLEMENTATION | vegetação | NLE-PRPLAN-GFX-04-06 | BLOCKED |
| 8 | NLE-PRPLAN-GFX-04-08 | IMPLEMENTATION | geometry optimization | NLE-PRPLAN-GFX-04-07 | BLOCKED |
| 9 | NLE-PRPLAN-GFX-04-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-GFX-04-08 | BLOCKED |
| 10 | NLE-PRPLAN-GFX-04-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-GFX-04-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-GFX-04-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: GFX-04 predecessors GFX-03+DATA-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Grande cena com culling correto e evidência de custo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-04-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: GFX-04 predecessors GFX-03+DATA-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Grande cena com culling correto e evidência de custo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-04-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-04-03 / Instancing
OBJECTIVE / SCOPE: Instancing. CONTEXT: GFX-04 predecessors GFX-03+DATA-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Grande cena com culling correto e evidência de custo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Instancing with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-04-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-04-04 / culling
OBJECTIVE / SCOPE: culling. CONTEXT: GFX-04 predecessors GFX-03+DATA-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Grande cena com culling correto e evidência de custo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise culling with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-04-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-04-05 / HLOD
OBJECTIVE / SCOPE: HLOD. CONTEXT: GFX-04 predecessors GFX-03+DATA-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Grande cena com culling correto e evidência de custo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise HLOD with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-04-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-04-06 / mesh streaming
OBJECTIVE / SCOPE: mesh streaming. CONTEXT: GFX-04 predecessors GFX-03+DATA-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Grande cena com culling correto e evidência de custo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise mesh streaming with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-04-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-04-07 / vegetação
OBJECTIVE / SCOPE: vegetação. CONTEXT: GFX-04 predecessors GFX-03+DATA-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Grande cena com culling correto e evidência de custo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise vegetação with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-04-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-04-08 / geometry optimization
OBJECTIVE / SCOPE: geometry optimization. CONTEXT: GFX-04 predecessors GFX-03+DATA-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Grande cena com culling correto e evidência de custo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise geometry optimization with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-04-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-04-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: GFX-04 predecessors GFX-03+DATA-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Grande cena com culling correto e evidência de custo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Grande cena com culling correto e evidência de custo.. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-04-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-04-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: GFX-04 predecessors GFX-03+DATA-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Grande cena com culling correto e evidência de custo.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-04-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
