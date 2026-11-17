# NLE-PRPLAN-CORE-01-12 — G6 activation (lifecycle request state machine)

**Status:** `G6 PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `df551006982868e616d867c7daaa3fc5a7c51ee8`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-12`. **ADR:** [ADR-0091](../adr/0091-core-01-lifecycle-request-state-machine.md). **Contract:** [core-01-lifecycle-requests-v0](../contracts/core-01-lifecycle-requests-v0.md). **WO:** [NLE-PRPLAN-CORE-01-12](../work-orders/NLE-PRPLAN-CORE-01-12.md).

## Owner authorization

The owner authorized continuing and unlocking what is necessary on 2026-11-17 (`autorizo tudo que for preciso continue`). C01-D07 (explicit lifecycle state machine, typed errors, recoverable/idempotent cleanup) is an owner-ratified bounded direction. This gate activates **only** `NLE-PRPLAN-CORE-01-12` after exact-head Docs Validation, objective pt-BR audit and squash/readback.

It does not approve ADR-0003/0075 globally, clear G3, authorize OS signal handlers, forced process kill, persistence/save, renderer device-loss recovery, public ABI/release, or another packet/module.

## Predecessors

`-03` headless host PR #428; `-04`/`-05` reconciled; `-06` paths PR #432; `-07` SDL3 runtime PR #435; `-08` window lifecycle PR #438; `-09` event queue PR #444; `-10` display/surface PR #447; `-11` native bridge PR #450. All `COMPLETED`; no predecessor reopened. CORE-02-03 ownership is also `COMPLETED` via PR #441 and unaffected.

## Bounded technical slice

- `LifecycleState`, `LifecycleError`, `LifecycleController`; owner-thread typed transitions.
- Running → SuspendPending → Suspended → ResumePending → Running; running/suspended → ShutdownPending → Terminated; explicit forced `request_terminate`.
- `observe(InputEvent)` maps Quit/WindowCloseRequested to shutdown; other events ignored.
- `should_continue`/`state`; invalid transitions leave state unchanged and return typed errors.
- No OS signal handler, sleep hook, process kill, persistence/save, renderer teardown, public ABI or release.
- Exact code allowlist: `lifecycle.hpp`, `lifecycle.cpp`, `tests/core/lifecycle_tests.cpp`, additive `CMakeLists.txt`, additive workflow filters, `docs/evidence/NLE-PRPLAN-CORE-01-12.md`.

## Gate state after merge (expected, not yet promoted)

- Manifest root `CORE01_12_READY_PREDECESSORS_COMPLETED`: **733 `PLANNED_BLOCKED`, 10 `COMPLETED` (CORE-01 -03..-11 + CORE-02-03), 4 approved gate entries, 1 `EXECUTOR_READY` (`CORE-01-12`)**.
- `select_packet.py NLE-PRPLAN-CORE-01-12` → exit 0; every other ID, including `-13` and `CORE-02-04`, exit 2.
- 80/80 module WOs remain `BLOCKED`; registry unchanged; ADR-0003/0075 `PROPOSED`; ADR-0091 bounded; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; `engine_implemented=false` at module/product level.

## Proof obligations for the code PR

LCY-01..LCY-06: normal suspend/resume; shutdown from all allowed states; observed quit/close; invalid transitions and terminated repeats; wrong-thread; 100 recovery cycles and existing 53 CTests regression. Real Linux, Linux ASan/UBSan, Windows and macOS; no SDL in header; no OS signal/termination/persistence/ABI/release claim; exact-head Docs Validation and pt-BR audit.

No code or native PASS is claimed by this gate.

## Security and rollback

No dependency, package installation, secret, upload, paid service or runtime download. Unmerged: close the gate branch; `main` untouched. After merge: normal revert PR, never force push. SDL3 zlib notice remains preserved for future distribution; `NLE-D009 OPEN`; no release.
