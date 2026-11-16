# WORLD-04 — Terrain & Environment | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#44](https://github.com/KayzenRoot/stormline/issues/44). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Terrenos, splatmaps, vegetação, água, céu, clima e editorabilidade. | Formal predecessors: WORLD-03 + GFX-04 | Catalog acceptance: Benchmark de travessia e render de biomas 3D originais..
[Architecture](../architecture/world-04-terrain-environment.md) · [Proposed ADR](../adr/0029-world-04-authored-terrain-environment-visual-ownership.md) · [Original blocked code WO](../queue/work-orders/WORLD-04.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-WORLD-04-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-WORLD-04-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-WORLD-04-01 | BLOCKED |
| 3 | NLE-PRPLAN-WORLD-04-03 | IMPLEMENTATION | Terrenos | NLE-PRPLAN-WORLD-04-02 | BLOCKED |
| 4 | NLE-PRPLAN-WORLD-04-04 | IMPLEMENTATION | splatmaps | NLE-PRPLAN-WORLD-04-03 | BLOCKED |
| 5 | NLE-PRPLAN-WORLD-04-05 | IMPLEMENTATION | vegetação | NLE-PRPLAN-WORLD-04-04 | BLOCKED |
| 6 | NLE-PRPLAN-WORLD-04-06 | IMPLEMENTATION | água | NLE-PRPLAN-WORLD-04-05 | BLOCKED |
| 7 | NLE-PRPLAN-WORLD-04-07 | IMPLEMENTATION | céu | NLE-PRPLAN-WORLD-04-06 | BLOCKED |
| 8 | NLE-PRPLAN-WORLD-04-08 | IMPLEMENTATION | clima | NLE-PRPLAN-WORLD-04-07 | BLOCKED |
| 9 | NLE-PRPLAN-WORLD-04-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-WORLD-04-08 | BLOCKED |
| 10 | NLE-PRPLAN-WORLD-04-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-WORLD-04-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-WORLD-04-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: WORLD-04 predecessors WORLD-03+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Benchmark de travessia e render de biomas 3D originais.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-04-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: WORLD-04 predecessors WORLD-03+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Benchmark de travessia e render de biomas 3D originais.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-04-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-04-03 / Terrenos
OBJECTIVE / SCOPE: Terrenos. CONTEXT: WORLD-04 predecessors WORLD-03+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Benchmark de travessia e render de biomas 3D originais.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Terrenos with valid/invalid fixtures, typed failures and entity identity/source preservation/soak tests. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-04-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-04-04 / splatmaps
OBJECTIVE / SCOPE: splatmaps. CONTEXT: WORLD-04 predecessors WORLD-03+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Benchmark de travessia e render de biomas 3D originais.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise splatmaps with valid/invalid fixtures, typed failures and entity identity/source preservation/soak tests. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-04-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-04-05 / vegetação
OBJECTIVE / SCOPE: vegetação. CONTEXT: WORLD-04 predecessors WORLD-03+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Benchmark de travessia e render de biomas 3D originais.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise vegetação with valid/invalid fixtures, typed failures and entity identity/source preservation/soak tests. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-04-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-04-06 / água
OBJECTIVE / SCOPE: água. CONTEXT: WORLD-04 predecessors WORLD-03+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Benchmark de travessia e render de biomas 3D originais.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise água with valid/invalid fixtures, typed failures and entity identity/source preservation/soak tests. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-04-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-04-07 / céu
OBJECTIVE / SCOPE: céu. CONTEXT: WORLD-04 predecessors WORLD-03+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Benchmark de travessia e render de biomas 3D originais.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise céu with valid/invalid fixtures, typed failures and entity identity/source preservation/soak tests. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-04-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-04-08 / clima
OBJECTIVE / SCOPE: clima. CONTEXT: WORLD-04 predecessors WORLD-03+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Benchmark de travessia e render de biomas 3D originais.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise clima with valid/invalid fixtures, typed failures and entity identity/source preservation/soak tests. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-04-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-04-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: WORLD-04 predecessors WORLD-03+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Benchmark de travessia e render de biomas 3D originais.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Benchmark de travessia e render de biomas 3D originais.. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-04-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-WORLD-04-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: WORLD-04 predecessors WORLD-03+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Benchmark de travessia e render de biomas 3D originais.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE entity identity/source preservation/soak tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-WORLD-04-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
