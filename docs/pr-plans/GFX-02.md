# GFX-02 — Shader & Material Compilation | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#30](https://github.com/KayzenRoot/stormline/issues/30). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Linguagem/pipeline de shaders, reflexão, variantes, cache, compilação incremental. | Formal predecessors: GFX-01 + DATA-03 | Catalog acceptance: Build determinístico, diagnóstico por arquivo/linha, variantes estáveis..
[Architecture](../architecture/gfx-02-shader-material-compilation.md) · [Proposed ADR](../adr/0015-gfx-02-shader-compilation-policy.md) · [Original blocked code WO](../queue/work-orders/GFX-02.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-GFX-02-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-GFX-02-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-GFX-02-01 | BLOCKED |
| 3 | NLE-PRPLAN-GFX-02-03 | IMPLEMENTATION | Linguagem/pipeline de shaders | NLE-PRPLAN-GFX-02-02 | BLOCKED |
| 4 | NLE-PRPLAN-GFX-02-04 | IMPLEMENTATION | reflexão | NLE-PRPLAN-GFX-02-03 | BLOCKED |
| 5 | NLE-PRPLAN-GFX-02-05 | IMPLEMENTATION | variantes | NLE-PRPLAN-GFX-02-04 | BLOCKED |
| 6 | NLE-PRPLAN-GFX-02-06 | IMPLEMENTATION | cache | NLE-PRPLAN-GFX-02-05 | BLOCKED |
| 7 | NLE-PRPLAN-GFX-02-07 | IMPLEMENTATION | compilação incremental | NLE-PRPLAN-GFX-02-06 | BLOCKED |
| 8 | NLE-PRPLAN-GFX-02-08 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-GFX-02-07 | BLOCKED |
| 9 | NLE-PRPLAN-GFX-02-09 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-GFX-02-08 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-GFX-02-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: GFX-02 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Build determinístico, diagnóstico por arquivo/linha, variantes estáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-02-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: GFX-02 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Build determinístico, diagnóstico por arquivo/linha, variantes estáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-02-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-02-03 / Linguagem/pipeline de shaders
OBJECTIVE / SCOPE: Linguagem/pipeline de shaders. CONTEXT: GFX-02 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Build determinístico, diagnóstico por arquivo/linha, variantes estáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Linguagem/pipeline de shaders with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-02-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-02-04 / reflexão
OBJECTIVE / SCOPE: reflexão. CONTEXT: GFX-02 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Build determinístico, diagnóstico por arquivo/linha, variantes estáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise reflexão with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-02-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-02-05 / variantes
OBJECTIVE / SCOPE: variantes. CONTEXT: GFX-02 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Build determinístico, diagnóstico por arquivo/linha, variantes estáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise variantes with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-02-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-02-06 / cache
OBJECTIVE / SCOPE: cache. CONTEXT: GFX-02 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Build determinístico, diagnóstico por arquivo/linha, variantes estáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise cache with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-02-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-02-07 / compilação incremental
OBJECTIVE / SCOPE: compilação incremental. CONTEXT: GFX-02 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Build determinístico, diagnóstico por arquivo/linha, variantes estáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise compilação incremental with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-02-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-02-08 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: GFX-02 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Build determinístico, diagnóstico por arquivo/linha, variantes estáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Build determinístico, diagnóstico por arquivo/linha, variantes estáveis.. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-02-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-02-09 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: GFX-02 predecessors GFX-01+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Build determinístico, diagnóstico por arquivo/linha, variantes estáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-02-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
