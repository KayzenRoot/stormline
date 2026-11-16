# TWO-04 — 2.5D Hybrid Composition | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#40](https://github.com/KayzenRoot/stormline/issues/40). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Orthographic/perspective cameras, layers 2D/3D, sorting e efeitos híbridos. | Formal predecessors: TWO-01 + GFX-04 | Catalog acceptance: Projeto mistura sprites e mundo 3D preservando ordem/iluminação..
[Architecture](../architecture/two-04-hybrid-composition.md) · [Proposed ADR](../adr/0025-two-04-depth-order-hybrid-composition-policy.md) · [Original blocked code WO](../queue/work-orders/TWO-04.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-TWO-04-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-TWO-04-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-TWO-04-01 | BLOCKED |
| 3 | NLE-PRPLAN-TWO-04-03 | IMPLEMENTATION | Orthographic/perspective cameras | NLE-PRPLAN-TWO-04-02 | BLOCKED |
| 4 | NLE-PRPLAN-TWO-04-04 | IMPLEMENTATION | layers 2D/3D | NLE-PRPLAN-TWO-04-03 | BLOCKED |
| 5 | NLE-PRPLAN-TWO-04-05 | IMPLEMENTATION | sorting | NLE-PRPLAN-TWO-04-04 | BLOCKED |
| 6 | NLE-PRPLAN-TWO-04-06 | IMPLEMENTATION | efeitos híbridos | NLE-PRPLAN-TWO-04-05 | BLOCKED |
| 7 | NLE-PRPLAN-TWO-04-07 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-TWO-04-06 | BLOCKED |
| 8 | NLE-PRPLAN-TWO-04-08 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-TWO-04-07 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-TWO-04-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: TWO-04 predecessors TWO-01+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Projeto mistura sprites e mundo 3D preservando ordem/iluminação.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-04-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: TWO-04 predecessors TWO-01+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Projeto mistura sprites e mundo 3D preservando ordem/iluminação.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-04-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-04-03 / Orthographic/perspective cameras
OBJECTIVE / SCOPE: Orthographic/perspective cameras. CONTEXT: TWO-04 predecessors TWO-01+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Projeto mistura sprites e mundo 3D preservando ordem/iluminação.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Orthographic/perspective cameras with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-04-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-04-04 / layers 2D/3D
OBJECTIVE / SCOPE: layers 2D/3D. CONTEXT: TWO-04 predecessors TWO-01+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Projeto mistura sprites e mundo 3D preservando ordem/iluminação.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise layers 2D/3D with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-04-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-04-05 / sorting
OBJECTIVE / SCOPE: sorting. CONTEXT: TWO-04 predecessors TWO-01+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Projeto mistura sprites e mundo 3D preservando ordem/iluminação.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise sorting with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-04-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-04-06 / efeitos híbridos
OBJECTIVE / SCOPE: efeitos híbridos. CONTEXT: TWO-04 predecessors TWO-01+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Projeto mistura sprites e mundo 3D preservando ordem/iluminação.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise efeitos híbridos with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-04-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-04-07 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: TWO-04 predecessors TWO-01+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Projeto mistura sprites e mundo 3D preservando ordem/iluminação.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Projeto mistura sprites e mundo 3D preservando ordem/iluminação.. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-04-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-04-08 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: TWO-04 predecessors TWO-01+GFX-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Projeto mistura sprites e mundo 3D preservando ordem/iluminação.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-04-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
