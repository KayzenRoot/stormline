# GFX-05 — Materials, Texture Systems & PBR | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#33](https://github.com/KayzenRoot/stormline/issues/33). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Shading físico, textura virtual/opcional, mips, filtros, decals e transparência. | Formal predecessors: GFX-02 + DATA-03 | Catalog acceptance: Cenas golden de materiais e limites de overdraw..
[Architecture](../architecture/gfx-05-materials-textures-pbr.md) · [Proposed ADR](../adr/0018-gfx-05-material-texture-policy.md) · [Original blocked code WO](../queue/work-orders/GFX-05.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-GFX-05-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-GFX-05-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-GFX-05-01 | BLOCKED |
| 3 | NLE-PRPLAN-GFX-05-03 | IMPLEMENTATION | Shading físico | NLE-PRPLAN-GFX-05-02 | BLOCKED |
| 4 | NLE-PRPLAN-GFX-05-04 | IMPLEMENTATION | textura virtual/opcional | NLE-PRPLAN-GFX-05-03 | BLOCKED |
| 5 | NLE-PRPLAN-GFX-05-05 | IMPLEMENTATION | mips | NLE-PRPLAN-GFX-05-04 | BLOCKED |
| 6 | NLE-PRPLAN-GFX-05-06 | IMPLEMENTATION | filtros | NLE-PRPLAN-GFX-05-05 | BLOCKED |
| 7 | NLE-PRPLAN-GFX-05-07 | IMPLEMENTATION | decals | NLE-PRPLAN-GFX-05-06 | BLOCKED |
| 8 | NLE-PRPLAN-GFX-05-08 | IMPLEMENTATION | transparência | NLE-PRPLAN-GFX-05-07 | BLOCKED |
| 9 | NLE-PRPLAN-GFX-05-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-GFX-05-08 | BLOCKED |
| 10 | NLE-PRPLAN-GFX-05-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-GFX-05-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-GFX-05-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: GFX-05 predecessors GFX-02+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenas golden de materiais e limites de overdraw.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-05-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: GFX-05 predecessors GFX-02+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenas golden de materiais e limites de overdraw.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-05-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-05-03 / Shading físico
OBJECTIVE / SCOPE: Shading físico. CONTEXT: GFX-05 predecessors GFX-02+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenas golden de materiais e limites de overdraw.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Shading físico with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-05-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-05-04 / textura virtual/opcional
OBJECTIVE / SCOPE: textura virtual/opcional. CONTEXT: GFX-05 predecessors GFX-02+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenas golden de materiais e limites de overdraw.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise textura virtual/opcional with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-05-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-05-05 / mips
OBJECTIVE / SCOPE: mips. CONTEXT: GFX-05 predecessors GFX-02+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenas golden de materiais e limites de overdraw.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise mips with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-05-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-05-06 / filtros
OBJECTIVE / SCOPE: filtros. CONTEXT: GFX-05 predecessors GFX-02+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenas golden de materiais e limites de overdraw.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise filtros with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-05-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-05-07 / decals
OBJECTIVE / SCOPE: decals. CONTEXT: GFX-05 predecessors GFX-02+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenas golden de materiais e limites de overdraw.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise decals with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-05-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-05-08 / transparência
OBJECTIVE / SCOPE: transparência. CONTEXT: GFX-05 predecessors GFX-02+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenas golden de materiais e limites de overdraw.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise transparência with valid/invalid fixtures, typed failures and GPU validation/visual golden/driver tests. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-05-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-05-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: GFX-05 predecessors GFX-02+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenas golden de materiais e limites de overdraw.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Cenas golden de materiais e limites de overdraw.. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-05-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-GFX-05-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: GFX-05 predecessors GFX-02+DATA-03. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Cenas golden de materiais e limites de overdraw.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE GPU validation/visual golden/driver tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-GFX-05-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
