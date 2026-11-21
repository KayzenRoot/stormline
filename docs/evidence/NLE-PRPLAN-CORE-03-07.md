# NLE-PRPLAN-CORE-03-07 — Cancellation slice satisfaction evidence

**Status:** `SATISFIED BY CORE-03-03 / NO NEW CODE`. **Base main:** `1c016b318f55f29ff4539e235925bd466ea89087`. **Formal packet:** `NLE-PRPLAN-CORE-03-07`. **Risk:** `ELEVATED` inherited. **Release class:** `INTERNAL_ONLY`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **Contract:** [core-03-task-graph-v0](../contracts/core-03-task-graph-v0.md). **WO:** [NLE-PRPLAN-CORE-03-07](../work-orders/NLE-PRPLAN-CORE-03-07.md).

## Scope traceability

| Packet requirement | Evidence |
|---|---|
| Pending tasks in scope are cancelled without running | JOB-05 cancels scope 7 before pumping two MainThread tasks; neither function executes |
| Scope isolation | JOB-05 scope 8 task still executes; stats completed=1, cancelled=2 |
| Terminal job result | JOB-05 `wait` returns `Cancelled`; queue is pruned to depth 0 |
| Shutdown rejects new work | JOB-08 submit after stop returns `ShuttingDown`; stop is idempotent |
| No detached threads / bounded shutdown | JOB-08 destructor with submitted work joins; JOB-01/09 lifecycle/stress |
| Deadlock/wrong-thread safety | JOB-06 worker `wait` → `DeadlockRisk`; non-owner → `WrongThread` |
| Cross-platform | Linux, Linux ASan/UBSan, TSan, Windows MSVC and macOS AppleClang CI |

## Exact evidence

- Implementation PR #508, head `d22a2d7`, squash merge `3a697f6869f7081d9a05089d84ab6021c6e6a550`.
- Native CI [44959327194](https://github.com/KayzenRoot/stormline/actions/runs/44959327194): Linux **120/120**, Linux ASan/UBSan **120/120**, TSan **10/10**, Windows **121/121**, macOS **119/119**.
- `core03_job05_cancel`, `core03_job06_affinity`, `core03_job08_shutdown` PASS on every native target.
- Audit [APPROVED](https://github.com/KayzenRoot/stormline/pull/508#issuecomment-7070569794).

## Manifest effect

- `CORE-03-07` `PLANNED_BLOCKED` → `COMPLETED` with this closeout PR.
- Root `CORE03_07_COMPLETED_REST_BLOCKED`: **715 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 27 `COMPLETED`, 6 approved gates**.
- `CORE-03-08`..`-10` remain `PLANNED_BLOCKED`; selector denies every ID; registry byte-identical.
- CORE-02 remains `NOT_QUALIFIED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; no allocator, technology, ABI or release.

## Security and rollback

Documentary only. No secret, upload, paid service, dependency or runtime change. Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.

## Open risks

Forced termination, preemptive cancellation of blocking calls, cancellation-aware GPU/audio APIs and transactional rollback remain future scope. Full Q4 remains `BLOCKED`; no real-time guarantee is claimed.

## Proposed checkpoint delta

`CORE-03-07` completed as satisfied; `CORE-03-08` (“isolamento de dados”) is the next blocked packet and requires a scope/G6 decision because the frozen v0 contract does not define a data/resource isolation policy.
