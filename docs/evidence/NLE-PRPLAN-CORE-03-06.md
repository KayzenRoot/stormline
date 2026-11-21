# NLE-PRPLAN-CORE-03-06 — Affinity slice satisfaction evidence

**Status:** `SATISFIED BY CORE-03-03 / NO NEW CODE`. **Base main:** `c26a95999a88cb1e0869a1257cd486e00505d165`. **Formal packet:** `NLE-PRPLAN-CORE-03-06`. **Risk:** `ELEVATED` inherited. **Release class:** `INTERNAL_ONLY`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **Contract:** [core-03-task-graph-v0](../contracts/core-03-task-graph-v0.md). **WO:** [NLE-PRPLAN-CORE-03-06](../work-orders/NLE-PRPLAN-CORE-03-06.md).

## Scope traceability

| Packet requirement | Evidence |
|---|---|
| MainThread tasks never run on workers | JOB-06 records the main task thread and asserts it equals the owner |
| Worker tasks stay off the owner lane | JOB-06 records the worker thread and asserts it differs from the owner |
| Worker `wait` rejected | JOB-06 task calls `wait` and receives `DeadlockRisk` |
| Non-owner `wait` rejected | JOB-06 external thread receives `WrongThread` |
| Wrong-thread pump is a no-op | JOB-06 calls `pump_main_thread` from another thread; the main task remains pending until owner pump |
| Lifecycle/stress | JOB-01 and JOB-09 cover submit/wait/stop and repeated runs |
| Cross-platform | Linux, Linux ASan/UBSan, TSan, Windows MSVC and macOS AppleClang CI |

## Exact evidence

- Implementation PR #508, head `d22a2d7`, squash merge `3a697f6869f7081d9a05089d84ab6021c6e6a550`.
- Native CI [44959327194](https://github.com/KayzenRoot/stormline/actions/runs/44959327194): Linux **120/120**, Linux ASan/UBSan **120/120**, TSan **10/10**, Windows **121/121**, macOS **119/119**.
- `core03_job06_affinity` PASS on every native target.
- Audit [APPROVED](https://github.com/KayzenRoot/stormline/pull/508#issuecomment-7070569794).

## Manifest effect

- `CORE-03-06` `PLANNED_BLOCKED` → `COMPLETED` with this closeout PR.
- Root `CORE03_06_COMPLETED_REST_BLOCKED`: **716 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 26 `COMPLETED`, 6 approved gates**.
- `CORE-03-07`..`-10` remain `PLANNED_BLOCKED`; selector denies every ID; registry byte-identical.
- CORE-02 remains `NOT_QUALIFIED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; no allocator, technology, ABI or release.

## Security and rollback

Documentary only. No secret, upload, paid service, dependency or runtime change. Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.

## Open risks

OS affinity masks, CPU pinning, NUMA, heterogeneous cores, GPU/audio affinity and hard real-time guarantees remain future scope. Full Q4 remains `BLOCKED`.

## Proposed checkpoint delta

`CORE-03-06` completed as satisfied; `CORE-03-07` (“cancelamento”) is the next blocked packet and requires its own satisfaction/G6 decision.
