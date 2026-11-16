# CORE-01 — Platform & Lifecycle | proposed future PRs
SOURCE bc11813de9e8eb2bc7ffd4c2941b7b8653a23701 | Existing blocked issue [#18](https://github.com/KayzenRoot/stormline/issues/18). RESEARCH DONE, ADR PROPOSED, implementation not authorized, release/risk UNDECIDED, engine license OPEN.
Scope: Inicialização, sistema operacional, janelas, eventos, paths, ciclo de vida e interfaces portáveis. | Formal predecessors: NONE | Catalog acceptance: Inicializar e desligar headless e com janela, sem leaks detectáveis..
[Architecture](../architecture/core-01-platform-lifecycle.md) · [Proposed ADR](../adr/0003-core-01-platform-technology.md) · [Original blocked code WO](../queue/work-orders/CORE-01.md)
## Candidate packets (not GitHub PR numbers)
| # | Stable packet | Kind | Bounded scope | Prior | Status |
|---:|---|---|---|---|---|
| 1 | NLE-PRPLAN-CORE-01-01 | GOVERNANCE | Explicit owner ADR, Scope/DoD, release and risk gates | Gates G1-G3 | BLOCKED |
| 2 | NLE-PRPLAN-CORE-01-02 | CONTRACT | Typed API/ABI, exact files and executable test contract | NLE-PRPLAN-CORE-01-01 | BLOCKED |
| 3 | NLE-PRPLAN-CORE-01-03 | IMPLEMENTATION | Toolchain and CPU-only headless harness | NLE-PRPLAN-CORE-01-02 | BLOCKED |
| 4 | NLE-PRPLAN-CORE-01-04 | IMPLEMENTATION | Typed HostConfig, states and errors | NLE-PRPLAN-CORE-01-03 | BLOCKED |
| 5 | NLE-PRPLAN-CORE-01-05 | IMPLEMENTATION | Partial init teardown and resource ownership | NLE-PRPLAN-CORE-01-04 | BLOCKED |
| 6 | NLE-PRPLAN-CORE-01-06 | IMPLEMENTATION | Portable process paths | NLE-PRPLAN-CORE-01-05 | BLOCKED |
| 7 | NLE-PRPLAN-CORE-01-07 | IMPLEMENTATION | Approved SDL3 thin adapter | NLE-PRPLAN-CORE-01-06 | BLOCKED |
| 8 | NLE-PRPLAN-CORE-01-08 | IMPLEMENTATION | Native window lifecycle | NLE-PRPLAN-CORE-01-07 | BLOCKED |
| 9 | NLE-PRPLAN-CORE-01-09 | IMPLEMENTATION | Input/event queue and replay | NLE-PRPLAN-CORE-01-08 | BLOCKED |
| 10 | NLE-PRPLAN-CORE-01-10 | IMPLEMENTATION | Multi-monitor, DPI and surface validity | NLE-PRPLAN-CORE-01-09 | BLOCKED |
| 11 | NLE-PRPLAN-CORE-01-11 | IMPLEMENTATION | Platform-specific OS bridges | NLE-PRPLAN-CORE-01-10 | BLOCKED |
| 12 | NLE-PRPLAN-CORE-01-12 | IMPLEMENTATION | Sleep/resume/shutdown requests | NLE-PRPLAN-CORE-01-11 | BLOCKED |
| 13 | NLE-PRPLAN-CORE-01-13 | IMPLEMENTATION | Capability graph comparative proof | NLE-PRPLAN-CORE-01-12 | BLOCKED |
| 14 | NLE-PRPLAN-CORE-01-14 | IMPLEMENTATION | Native multi-OS soak qualification | NLE-PRPLAN-CORE-01-13 | BLOCKED |
| 15 | NLE-PRPLAN-CORE-01-15 | QUALIFICATION | Integrated functionality, real OS/security/soak qualification | NLE-PRPLAN-CORE-01-14 | BLOCKED |
| 16 | NLE-PRPLAN-CORE-01-16 | CLOSEOUT | Evidence, review, recovery and checkpoint | NLE-PRPLAN-CORE-01-15 | BLOCKED |

## Packet pre-briefs (NOT executable)
### NLE-PRPLAN-CORE-01-01 / Explicit owner ADR, Scope/DoD, release and risk gates
OBJECTIVE / SCOPE: Explicit owner ADR, Scope/DoD, release and risk gates. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Owner ratification required; nothing approved by planning. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: owner technical gates; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-02 / Typed API/ABI, exact files and executable test contract
OBJECTIVE / SCOPE: Typed API/ABI, exact files and executable test contract. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Concrete interface, error model, test oracles, source SHA256 after owner signoff. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-01; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-03 / Toolchain and CPU-only headless harness
OBJECTIVE / SCOPE: Toolchain and CPU-only headless harness. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Boot/quit on an approved compiler without graphics/audio/display. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-02; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-04 / Typed HostConfig, states and errors
OBJECTIVE / SCOPE: Typed HostConfig, states and errors. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Reject wrong transitions and duplicate init without side effects. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-03; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-05 / Partial init teardown and resource ownership
OBJECTIVE / SCOPE: Partial init teardown and resource ownership. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Injected faults leave no leaked resources on repeated start/stop. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-04; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-06 / Portable process paths
OBJECTIVE / SCOPE: Portable process paths. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Unicode, access denial and directory traversal produce typed errors. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-05; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-07 / Approved SDL3 thin adapter
OBJECTIVE / SCOPE: Approved SDL3 thin adapter. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Main-thread init/quit and no SDL types leaking into engine public ABI. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-06; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-08 / Native window lifecycle
OBJECTIVE / SCOPE: Native window lifecycle. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Create/resize/focus/destroy with verified handle lifetime. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-07; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-09 / Input/event queue and replay
OBJECTIVE / SCOPE: Input/event queue and replay. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Sequence/timestamp order and overflow behavior tested. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-08; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-10 / Multi-monitor, DPI and surface validity
OBJECTIVE / SCOPE: Multi-monitor, DPI and surface validity. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Resize/hotplug invalidates borrowed surface safely. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-09; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-11 / Platform-specific OS bridges
OBJECTIVE / SCOPE: Platform-specific OS bridges. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Conditional Win32/Cocoa/Linux behavior isolated with real target tests. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-10; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-12 / Sleep/resume/shutdown requests
OBJECTIVE / SCOPE: Sleep/resume/shutdown requests. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Suspend/terminate interruptions recover without corruption. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-11; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-13 / Capability graph comparative proof
OBJECTIVE / SCOPE: Capability graph comparative proof. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Unknown vs unsupported and SAPL overhead vs thin SDL3 measured. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-12; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-14 / Native multi-OS soak qualification
OBJECTIVE / SCOPE: Native multi-OS soak qualification. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Windows/Linux/macOS headless+window builds, sanitizers and stress. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-13; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-15 / Integrated functionality, real OS/security/soak qualification
OBJECTIVE / SCOPE: Integrated functionality, real OS/security/soak qualification. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Inicializar e desligar headless e com janela, sem leaks detectáveis.. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-14; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

### NLE-PRPLAN-CORE-01-16 / Evidence, review, recovery and checkpoint
OBJECTIVE / SCOPE: Evidence, review, recovery and checkpoint. CONTEXT: CORE-01 predecessors none. OUT OF SCOPE: unapproved stack, new module edges, public release and unrelated work.
FILES/SOURCES: Source Pack, module ADR/architecture/blocked WO, actual source after approval. REQUIREMENTS: Inicializar e desligar headless e com janela, sem leaks detectáveis.. ARCHITECTURE: typed errors, clear ownership, fail-closed policy.
ACCEPTANCE: Real tests pass; no HIGH/CRITICAL; pt-BR audit and squash/readback. TESTS: FUTURE state/lifetime/cross-platform unit tests, never run in this plan. DEPENDENCIES: NLE-PRPLAN-CORE-01-15; for code also all formal predecessor modules merged.
DELIVERABLES/REVIEW: future full 13-field Work Order, exact files, CI, Evidence and pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED. STOP: stale Context Lock, missing approved ADR/risk/DoD/release class, HIGH/CRITICAL or failed test. CURRENT: PLANNED_BLOCKED; GitHub code PR NOT OPENED.

Completion requires all actual approved code PRs, real cross-target tests, rights/security proof, independent audit and checkpoint. These counts may change after owner ADR ratification.
[All 80 plans](index.md) · [Manifest](manifest.json) · [Gate policy](../engineering/p00-technical-approval-gates.md).
