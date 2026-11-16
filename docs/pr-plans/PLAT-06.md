# PLAT-06 — macOS Desktop Target (Apple Silicon + Intel compatibility) | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#87](https://github.com/KayzenRoot/stormline/issues/87). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Cocoa/Objective-C++ bridge, native window lifecycle, Metal presentation surface, packaging, architecture ABI, GPU capability/fallback and OS version matrix. Apple Silicon mandatory; Intel coverage to be decided by ADR for 1.0. | Formal predecessors: CORE-01 + GFX-01 + GAME-01 | Catalog acceptance: Editor and exported 2D/2.5D/3D game open/build/close on a macOS test matrix, with platform-native graphics checks and recoverable errors..
[Architecture](../architecture/plat-06-macos-desktop-target.md) · [Proposed ADR](../adr/0072-plat-06-macos-apple-silicon-compatibility-policy.md) · [Original blocked code WO](../queue/work-orders/PLAT-06.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-PLAT-06-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-PLAT-06-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-PLAT-06-01 | BLOCKED |
| 3 | NLE-PRPLAN-PLAT-06-03 | IMPLEMENTATION | Cocoa/Objective-C++ bridge | NLE-PRPLAN-PLAT-06-02 | BLOCKED |
| 4 | NLE-PRPLAN-PLAT-06-04 | IMPLEMENTATION | native window lifecycle | NLE-PRPLAN-PLAT-06-03 | BLOCKED |
| 5 | NLE-PRPLAN-PLAT-06-05 | IMPLEMENTATION | Metal presentation surface | NLE-PRPLAN-PLAT-06-04 | BLOCKED |
| 6 | NLE-PRPLAN-PLAT-06-06 | IMPLEMENTATION | packaging | NLE-PRPLAN-PLAT-06-05 | BLOCKED |
| 7 | NLE-PRPLAN-PLAT-06-07 | IMPLEMENTATION | architecture ABI | NLE-PRPLAN-PLAT-06-06 | BLOCKED |
| 8 | NLE-PRPLAN-PLAT-06-08 | IMPLEMENTATION | GPU capability/fallback | NLE-PRPLAN-PLAT-06-07 | BLOCKED |
| 9 | NLE-PRPLAN-PLAT-06-09 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-PLAT-06-08 | BLOCKED |
| 10 | NLE-PRPLAN-PLAT-06-10 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-PLAT-06-09 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-PLAT-06-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: PLAT-06 predecessors CORE-01+GFX-01+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor and exported 2D/2.5D/3D game open/build/close on a macOS test matrix, with platform-native graphics checks and recoverable errors.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE real OS/arch/GPU/hardware tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-PLAT-06-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: PLAT-06 predecessors CORE-01+GFX-01+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor and exported 2D/2.5D/3D game open/build/close on a macOS test matrix, with platform-native graphics checks and recoverable errors.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE real OS/arch/GPU/hardware tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-PLAT-06-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-PLAT-06-03 / Cocoa/Objective-C++ bridge
OBJECTIVE / SCOPE: Cocoa/Objective-C++ bridge. CONTEXT: PLAT-06 predecessors CORE-01+GFX-01+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor and exported 2D/2.5D/3D game open/build/close on a macOS test matrix, with platform-native graphics checks and recoverable errors.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Cocoa/Objective-C++ bridge with valid/invalid fixtures, typed failures and real OS/arch/GPU/hardware tests. TESTS: FUTURE real OS/arch/GPU/hardware tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-PLAT-06-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-PLAT-06-04 / native window lifecycle
OBJECTIVE / SCOPE: native window lifecycle. CONTEXT: PLAT-06 predecessors CORE-01+GFX-01+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor and exported 2D/2.5D/3D game open/build/close on a macOS test matrix, with platform-native graphics checks and recoverable errors.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise native window lifecycle with valid/invalid fixtures, typed failures and real OS/arch/GPU/hardware tests. TESTS: FUTURE real OS/arch/GPU/hardware tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-PLAT-06-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-PLAT-06-05 / Metal presentation surface
OBJECTIVE / SCOPE: Metal presentation surface. CONTEXT: PLAT-06 predecessors CORE-01+GFX-01+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor and exported 2D/2.5D/3D game open/build/close on a macOS test matrix, with platform-native graphics checks and recoverable errors.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise Metal presentation surface with valid/invalid fixtures, typed failures and real OS/arch/GPU/hardware tests. TESTS: FUTURE real OS/arch/GPU/hardware tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-PLAT-06-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-PLAT-06-06 / packaging
OBJECTIVE / SCOPE: packaging. CONTEXT: PLAT-06 predecessors CORE-01+GFX-01+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor and exported 2D/2.5D/3D game open/build/close on a macOS test matrix, with platform-native graphics checks and recoverable errors.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise packaging with valid/invalid fixtures, typed failures and real OS/arch/GPU/hardware tests. TESTS: FUTURE real OS/arch/GPU/hardware tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-PLAT-06-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-PLAT-06-07 / architecture ABI
OBJECTIVE / SCOPE: architecture ABI. CONTEXT: PLAT-06 predecessors CORE-01+GFX-01+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor and exported 2D/2.5D/3D game open/build/close on a macOS test matrix, with platform-native graphics checks and recoverable errors.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise architecture ABI with valid/invalid fixtures, typed failures and real OS/arch/GPU/hardware tests. TESTS: FUTURE real OS/arch/GPU/hardware tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-PLAT-06-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-PLAT-06-08 / GPU capability/fallback
OBJECTIVE / SCOPE: GPU capability/fallback. CONTEXT: PLAT-06 predecessors CORE-01+GFX-01+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor and exported 2D/2.5D/3D game open/build/close on a macOS test matrix, with platform-native graphics checks and recoverable errors.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Exercise GPU capability/fallback with valid/invalid fixtures, typed failures and real OS/arch/GPU/hardware tests. TESTS: FUTURE real OS/arch/GPU/hardware tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-PLAT-06-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-PLAT-06-09 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: PLAT-06 predecessors CORE-01+GFX-01+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor and exported 2D/2.5D/3D game open/build/close on a macOS test matrix, with platform-native graphics checks and recoverable errors.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Editor and exported 2D/2.5D/3D game open/build/close on a macOS test matrix, with platform-native graphics checks and recoverable errors.. TESTS: FUTURE real OS/arch/GPU/hardware tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-PLAT-06-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-PLAT-06-10 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: PLAT-06 predecessors CORE-01+GFX-01+GAME-01. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Editor and exported 2D/2.5D/3D game open/build/close on a macOS test matrix, with platform-native graphics checks and recoverable errors.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE real OS/arch/GPU/hardware tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-PLAT-06-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
