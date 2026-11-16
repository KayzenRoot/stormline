# TWO-01 — 2D Renderer & Canvas | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#37](https://github.com/KayzenRoot/stormline/issues/37). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Sprites, atlases, layers, câmera, pixel snapping, lights, shadows e batching. | Formal predecessors: GFX-01 + DATA-03 | Catalog acceptance: Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts..
[Architecture](../architecture/two-01-renderer-canvas.md) · [Proposed ADR](../adr/0022-two-01-native-2d-renderer-policy.md) · [Original blocked code WO](../queue/work-orders/TWO-01.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-TWO-01-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-TWO-01-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-TWO-01-01 | BLOCKED |
| 3 | NLE-PRPLAN-TWO-01-03 | IMPLEMENTATION | Sprites | NLE-PRPLAN-TWO-01-02 | BLOCKED |
| 4 | NLE-PRPLAN-TWO-01-04 | IMPLEMENTATION | atlases | NLE-PRPLAN-TWO-01-03 | BLOCKED |
| 5 | NLE-PRPLAN-TWO-01-05 | IMPLEMENTATION | layers | NLE-PRPLAN-TWO-01-04 | BLOCKED |
| 6 | NLE-PRPLAN-TWO-01-06 | IMPLEMENTATION | câmera | NLE-PRPLAN-TWO-01-05 | BLOCKED |
| 7 | NLE-PRPLAN-TWO-01-07 | IMPLEMENTATION | pixel snapping | NLE-PRPLAN-TWO-01-06 | BLOCKED |
| 8 | NLE-PRPLAN-TWO-01-08 | IMPLEMENTATION | lights | NLE-PRPLAN-TWO-01-07 | BLOCKED |
| 9 | NLE-PRPLAN-TWO-01-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-TWO-01-08 | BLOCKED |
| 10 | NLE-PRPLAN-TWO-01-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-TWO-01-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-TWO-01-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: TWO-01 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-01-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: TWO-01 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-01-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-01-03 / Sprites
OBJECTIVE / SCOPE: Sprites. CONTEXT: TWO-01 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Sprites with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-01-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-01-04 / atlases
OBJECTIVE / SCOPE: atlases. CONTEXT: TWO-01 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise atlases with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-01-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-01-05 / layers
OBJECTIVE / SCOPE: layers. CONTEXT: TWO-01 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise layers with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-01-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-01-06 / câmera
OBJECTIVE / SCOPE: câmera. CONTEXT: TWO-01 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise câmera with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-01-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-01-07 / pixel snapping
OBJECTIVE / SCOPE: pixel snapping. CONTEXT: TWO-01 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise pixel snapping with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-01-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-01-08 / lights
OBJECTIVE / SCOPE: lights. CONTEXT: TWO-01 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise lights with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-01-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-01-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: TWO-01 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts.. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-01-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-01-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: TWO-01 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-01-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
