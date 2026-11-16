# GFX-07 — Camera, Color & Post-processing | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#35](https://github.com/KayzenRoot/stormline/issues/35). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Exposição, tone mapping, HDR quando disponível, antialiasing, motion blur opcional e upscale. | Formal predecessors: GFX-06 | Catalog acceptance: Testes de cor/estabilidade, compatibilidade e falhas de GPU..
[Architecture](../architecture/gfx-07-camera-color-postprocessing.md) · [Proposed ADR](../adr/0020-gfx-07-camera-color-reconstruction-policy.md) · [Original blocked code WO](../queue/work-orders/GFX-07.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-GFX-07-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-GFX-07-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-GFX-07-01 | BLOCKED |
| 3 | NLE-PRPLAN-GFX-07-03 | IMPLEMENTATION | Exposição | NLE-PRPLAN-GFX-07-02 | BLOCKED |
| 4 | NLE-PRPLAN-GFX-07-04 | IMPLEMENTATION | tone mapping | NLE-PRPLAN-GFX-07-03 | BLOCKED |
| 5 | NLE-PRPLAN-GFX-07-05 | IMPLEMENTATION | HDR quando disponível | NLE-PRPLAN-GFX-07-04 | BLOCKED |
| 6 | NLE-PRPLAN-GFX-07-06 | IMPLEMENTATION | antialiasing | NLE-PRPLAN-GFX-07-05 | BLOCKED |
| 7 | NLE-PRPLAN-GFX-07-07 | IMPLEMENTATION | motion blur opcional | NLE-PRPLAN-GFX-07-06 | BLOCKED |
| 8 | NLE-PRPLAN-GFX-07-08 | IMPLEMENTATION | upscale | NLE-PRPLAN-GFX-07-07 | BLOCKED |
| 9 | NLE-PRPLAN-GFX-07-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-GFX-07-08 | BLOCKED |
| 10 | NLE-PRPLAN-GFX-07-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-GFX-07-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-GFX-07-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: GFX-07 predecessors GFX-06. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de cor/estabilidade, compatibilidade e falhas de GPU.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-07-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: GFX-07 predecessors GFX-06. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de cor/estabilidade, compatibilidade e falhas de GPU.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-07-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-07-03 / Exposição
OBJECTIVE / SCOPE: Exposição. CONTEXT: GFX-07 predecessors GFX-06. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de cor/estabilidade, compatibilidade e falhas de GPU.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Exposição with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-07-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-07-04 / tone mapping
OBJECTIVE / SCOPE: tone mapping. CONTEXT: GFX-07 predecessors GFX-06. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de cor/estabilidade, compatibilidade e falhas de GPU.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise tone mapping with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-07-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-07-05 / HDR quando disponível
OBJECTIVE / SCOPE: HDR quando disponível. CONTEXT: GFX-07 predecessors GFX-06. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de cor/estabilidade, compatibilidade e falhas de GPU.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise HDR quando disponível with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-07-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-07-06 / antialiasing
OBJECTIVE / SCOPE: antialiasing. CONTEXT: GFX-07 predecessors GFX-06. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de cor/estabilidade, compatibilidade e falhas de GPU.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise antialiasing with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-07-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-07-07 / motion blur opcional
OBJECTIVE / SCOPE: motion blur opcional. CONTEXT: GFX-07 predecessors GFX-06. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de cor/estabilidade, compatibilidade e falhas de GPU.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise motion blur opcional with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-07-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-07-08 / upscale
OBJECTIVE / SCOPE: upscale. CONTEXT: GFX-07 predecessors GFX-06. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de cor/estabilidade, compatibilidade e falhas de GPU.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise upscale with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-07-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-07-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: GFX-07 predecessors GFX-06. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de cor/estabilidade, compatibilidade e falhas de GPU.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Testes de cor/estabilidade, compatibilidade e falhas de GPU.. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-07-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-07-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: GFX-07 predecessors GFX-06. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Testes de cor/estabilidade, compatibilidade e falhas de GPU.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-07-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
