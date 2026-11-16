# TWO-02 — Tilemaps & 2D Worlds | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#38](https://github.com/KayzenRoot/stormline/issues/38). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Grades, tiles, collision shapes, parallax e streaming de mapas 2D. | Formal predecessors: TWO-01 + DATA-04 | Catalog acceptance: Editor pode salvar/reabrir mapas; streaming e colisão correspondentes..
[Architecture](../architecture/two-02-tilemaps-worlds.md) · [Proposed ADR](../adr/0023-two-02-sparse-chunk-tilemap-policy.md) · [Original blocked code WO](../queue/work-orders/TWO-02.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-TWO-02-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-TWO-02-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-TWO-02-01 | BLOCKED |
| 3 | NLE-PRPLAN-TWO-02-03 | IMPLEMENTATION | Grades | NLE-PRPLAN-TWO-02-02 | BLOCKED |
| 4 | NLE-PRPLAN-TWO-02-04 | IMPLEMENTATION | tiles | NLE-PRPLAN-TWO-02-03 | BLOCKED |
| 5 | NLE-PRPLAN-TWO-02-05 | IMPLEMENTATION | collision shapes | NLE-PRPLAN-TWO-02-04 | BLOCKED |
| 6 | NLE-PRPLAN-TWO-02-06 | IMPLEMENTATION | parallax | NLE-PRPLAN-TWO-02-05 | BLOCKED |
| 7 | NLE-PRPLAN-TWO-02-07 | IMPLEMENTATION | streaming de mapas 2D | NLE-PRPLAN-TWO-02-06 | BLOCKED |
| 8 | NLE-PRPLAN-TWO-02-08 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-TWO-02-07 | BLOCKED |
| 9 | NLE-PRPLAN-TWO-02-09 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-TWO-02-08 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-TWO-02-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: TWO-02 predecessors TWO-01+DATA-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor pode salvar/reabrir mapas; streaming e colisão correspondentes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-02-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: TWO-02 predecessors TWO-01+DATA-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor pode salvar/reabrir mapas; streaming e colisão correspondentes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-02-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-02-03 / Grades
OBJECTIVE / SCOPE: Grades. CONTEXT: TWO-02 predecessors TWO-01+DATA-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor pode salvar/reabrir mapas; streaming e colisão correspondentes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Grades with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-02-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-02-04 / tiles
OBJECTIVE / SCOPE: tiles. CONTEXT: TWO-02 predecessors TWO-01+DATA-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor pode salvar/reabrir mapas; streaming e colisão correspondentes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise tiles with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-02-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-02-05 / collision shapes
OBJECTIVE / SCOPE: collision shapes. CONTEXT: TWO-02 predecessors TWO-01+DATA-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor pode salvar/reabrir mapas; streaming e colisão correspondentes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise collision shapes with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-02-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-02-06 / parallax
OBJECTIVE / SCOPE: parallax. CONTEXT: TWO-02 predecessors TWO-01+DATA-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor pode salvar/reabrir mapas; streaming e colisão correspondentes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise parallax with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-02-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-02-07 / streaming de mapas 2D
OBJECTIVE / SCOPE: streaming de mapas 2D. CONTEXT: TWO-02 predecessors TWO-01+DATA-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor pode salvar/reabrir mapas; streaming e colisão correspondentes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise streaming de mapas 2D with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-02-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-02-08 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: TWO-02 predecessors TWO-01+DATA-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor pode salvar/reabrir mapas; streaming e colisão correspondentes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Editor pode salvar/reabrir mapas; streaming e colisão correspondentes.. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-02-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-02-09 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: TWO-02 predecessors TWO-01+DATA-04. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor pode salvar/reabrir mapas; streaming e colisão correspondentes.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-02-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
