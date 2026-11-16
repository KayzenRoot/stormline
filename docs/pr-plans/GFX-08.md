# GFX-08 — VFX & Particle Graph | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#36](https://github.com/KayzenRoot/stormline/issues/36). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: CPU/GPU particles, ribbons, trails, transparência, volumétricos, pooling e budgets. | Formal predecessors: GFX-03 + GFX-05 | Catalog acceptance: Stress de efeitos ao estilo ARPG com frametimes, VRAM e qualidade comparável..
[Architecture](../architecture/gfx-08-vfx-particle-graph.md) · [Proposed ADR](../adr/0021-gfx-08-vfx-graph-particle-policy.md) · [Original blocked code WO](../queue/work-orders/GFX-08.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-GFX-08-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-GFX-08-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-GFX-08-01 | BLOCKED |
| 3 | NLE-PRPLAN-GFX-08-03 | IMPLEMENTATION | CPU/GPU particles | NLE-PRPLAN-GFX-08-02 | BLOCKED |
| 4 | NLE-PRPLAN-GFX-08-04 | IMPLEMENTATION | ribbons | NLE-PRPLAN-GFX-08-03 | BLOCKED |
| 5 | NLE-PRPLAN-GFX-08-05 | IMPLEMENTATION | trails | NLE-PRPLAN-GFX-08-04 | BLOCKED |
| 6 | NLE-PRPLAN-GFX-08-06 | IMPLEMENTATION | transparência | NLE-PRPLAN-GFX-08-05 | BLOCKED |
| 7 | NLE-PRPLAN-GFX-08-07 | IMPLEMENTATION | volumétricos | NLE-PRPLAN-GFX-08-06 | BLOCKED |
| 8 | NLE-PRPLAN-GFX-08-08 | IMPLEMENTATION | pooling | NLE-PRPLAN-GFX-08-07 | BLOCKED |
| 9 | NLE-PRPLAN-GFX-08-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-GFX-08-08 | BLOCKED |
| 10 | NLE-PRPLAN-GFX-08-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-GFX-08-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-GFX-08-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: GFX-08 predecessors GFX-03+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Stress de efeitos ao estilo ARPG com frametimes, VRAM e qualidade comparável.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-08-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: GFX-08 predecessors GFX-03+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Stress de efeitos ao estilo ARPG com frametimes, VRAM e qualidade comparável.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-08-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-08-03 / CPU/GPU particles
OBJECTIVE / SCOPE: CPU/GPU particles. CONTEXT: GFX-08 predecessors GFX-03+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Stress de efeitos ao estilo ARPG com frametimes, VRAM e qualidade comparável.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise CPU/GPU particles with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-08-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-08-04 / ribbons
OBJECTIVE / SCOPE: ribbons. CONTEXT: GFX-08 predecessors GFX-03+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Stress de efeitos ao estilo ARPG com frametimes, VRAM e qualidade comparável.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise ribbons with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-08-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-08-05 / trails
OBJECTIVE / SCOPE: trails. CONTEXT: GFX-08 predecessors GFX-03+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Stress de efeitos ao estilo ARPG com frametimes, VRAM e qualidade comparável.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise trails with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-08-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-08-06 / transparência
OBJECTIVE / SCOPE: transparência. CONTEXT: GFX-08 predecessors GFX-03+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Stress de efeitos ao estilo ARPG com frametimes, VRAM e qualidade comparável.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise transparência with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-08-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-08-07 / volumétricos
OBJECTIVE / SCOPE: volumétricos. CONTEXT: GFX-08 predecessors GFX-03+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Stress de efeitos ao estilo ARPG com frametimes, VRAM e qualidade comparável.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise volumétricos with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-08-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-08-08 / pooling
OBJECTIVE / SCOPE: pooling. CONTEXT: GFX-08 predecessors GFX-03+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Stress de efeitos ao estilo ARPG com frametimes, VRAM e qualidade comparável.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise pooling with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-08-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-08-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: GFX-08 predecessors GFX-03+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Stress de efeitos ao estilo ARPG com frametimes, VRAM e qualidade comparável.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Stress de efeitos ao estilo ARPG com frametimes, VRAM e qualidade comparável.. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-08-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-08-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: GFX-08 predecessors GFX-03+GFX-05. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Stress de efeitos ao estilo ARPG com frametimes, VRAM e qualidade comparável.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-08-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
