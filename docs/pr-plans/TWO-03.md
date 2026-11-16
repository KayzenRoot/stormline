# TWO-03 — 2D Animation & Sequencing | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#39](https://github.com/KayzenRoot/stormline/issues/39). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Flipbooks, bones 2D, blend, cutscenes e timelines. | Formal predecessors: TWO-01 | Catalog acceptance: Timeline reproduzível e exportada com sincronismo áudio..
[Architecture](../architecture/two-03-animation-sequencing.md) · [Proposed ADR](../adr/0024-two-03-deterministic-animation-sequencing-policy.md) · [Original blocked code WO](../queue/work-orders/TWO-03.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-TWO-03-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-TWO-03-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-TWO-03-01 | BLOCKED |
| 3 | NLE-PRPLAN-TWO-03-03 | IMPLEMENTATION | Flipbooks | NLE-PRPLAN-TWO-03-02 | BLOCKED |
| 4 | NLE-PRPLAN-TWO-03-04 | IMPLEMENTATION | bones 2D | NLE-PRPLAN-TWO-03-03 | BLOCKED |
| 5 | NLE-PRPLAN-TWO-03-05 | IMPLEMENTATION | blend | NLE-PRPLAN-TWO-03-04 | BLOCKED |
| 6 | NLE-PRPLAN-TWO-03-06 | IMPLEMENTATION | cutscenes | NLE-PRPLAN-TWO-03-05 | BLOCKED |
| 7 | NLE-PRPLAN-TWO-03-07 | IMPLEMENTATION | timelines | NLE-PRPLAN-TWO-03-06 | BLOCKED |
| 8 | NLE-PRPLAN-TWO-03-08 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-TWO-03-07 | BLOCKED |
| 9 | NLE-PRPLAN-TWO-03-09 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-TWO-03-08 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-TWO-03-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: TWO-03 predecessors TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Timeline reproduzível e exportada com sincronismo áudio.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-03-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: TWO-03 predecessors TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Timeline reproduzível e exportada com sincronismo áudio.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-03-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-03-03 / Flipbooks
OBJECTIVE / SCOPE: Flipbooks. CONTEXT: TWO-03 predecessors TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Timeline reproduzível e exportada com sincronismo áudio.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Flipbooks with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-03-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-03-04 / bones 2D
OBJECTIVE / SCOPE: bones 2D. CONTEXT: TWO-03 predecessors TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Timeline reproduzível e exportada com sincronismo áudio.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise bones 2D with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-03-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-03-05 / blend
OBJECTIVE / SCOPE: blend. CONTEXT: TWO-03 predecessors TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Timeline reproduzível e exportada com sincronismo áudio.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise blend with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-03-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-03-06 / cutscenes
OBJECTIVE / SCOPE: cutscenes. CONTEXT: TWO-03 predecessors TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Timeline reproduzível e exportada com sincronismo áudio.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise cutscenes with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-03-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-03-07 / timelines
OBJECTIVE / SCOPE: timelines. CONTEXT: TWO-03 predecessors TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Timeline reproduzível e exportada com sincronismo áudio.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise timelines with valid/invalid fixtures, typed failures and pixel/DPI/2D save-reopen tests. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-03-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-03-08 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: TWO-03 predecessors TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Timeline reproduzível e exportada com sincronismo áudio.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Timeline reproduzível e exportada com sincronismo áudio.. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-03-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-TWO-03-09 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: TWO-03 predecessors TWO-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Timeline reproduzível e exportada com sincronismo áudio.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE pixel/DPI/2D save-reopen tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-TWO-03-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
