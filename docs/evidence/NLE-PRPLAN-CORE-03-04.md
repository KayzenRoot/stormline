# NLE-PRPLAN-CORE-03-04 — Priorities slice satisfaction evidence

**Status:** `SATISFIED BY CORE-03-03 / OWNER DECISION RECORDED / NO NEW CODE`. **Base main:** `386fa7faba3912d697dbdd404a0b2619df8779c0`. **Formal packet:** `NLE-PRPLAN-CORE-03-04`. **Risk:** `ELEVATED` inherited. **Release class:** `INTERNAL_ONLY`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **Contract:** [core-03-task-graph-v0](../contracts/core-03-task-graph-v0.md). **WO:** [NLE-PRPLAN-CORE-03-04](../work-orders/NLE-PRPLAN-CORE-03-04.md).

## Owner decision

On 2026-11-21 the owner declared the priorities slice satisfied and instructed continuation: “satisfeito continue”. This closes only `CORE-03-04`. It does not authorize priority aging, fairness weights, deadline scheduling, starvation metrics, priority inheritance, new dependencies, release or public ABI.

## Scope traceability

| Packet requirement | Evidence |
|---|---|
| FrameCritical > High > Normal > Background dispatch | JOB-04 exercises the exact expected order `{7,8,5,6,3,4,1,2}` with one worker and a controlled pump |
| Deterministic tie-break | JOB-04 uses TaskId ascending within the same priority |
| Background reservation | JOB-04 blocks both frame workers and proves the reserved background worker runs a Background task |
| Invalid priority is typed | JOB-03 rejects `static_cast<JobPriority>(9)` with `InvalidTask`; no execution |
| State/lifetime interaction | JOB-01/02/08/09 cover lifecycle, dependency, drain/stop and repeated runs |
| Cross-platform unit execution | Exact-head CI: Linux, Linux ASan/UBSan, TSan, Windows MSVC and macOS AppleClang |
| No hard real-time claim | Priority remains a dispatch preference; no deadline or latency threshold is asserted |

## Exact evidence

- Implementation PR #508, head `d22a2d7`, squash merge `3a697f6869f7081d9a05089d84ab6021c6e6a550`.
- Native CI [44959327194](https://github.com/KayzenRoot/stormline/actions/runs/44959327194): Linux **120/120**, Linux ASan/UBSan **120/120**, TSan **10/10**, Windows **121/121**, macOS **119/119**.
- `core03_job04_priority` PASS on every native target; `core03_job03_invalid` PASS on every native target.
- Audit [APPROVED](https://github.com/KayzenRoot/stormline/pull/508#issuecomment-7070569794).
- No new code, test, dependency or workflow bytes are changed by this packet.

## Manifest effect

- `CORE-03-04` `PLANNED_BLOCKED` → `COMPLETED` with this closeout PR.
- Root `CORE03_04_COMPLETED_REST_BLOCKED`: **718 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 24 `COMPLETED`, 6 approved gates**.
- `CORE-03-05`..`-10` remain `PLANNED_BLOCKED`; selector denies every ID; registry byte-identical.
- CORE-02 remains `NOT_QUALIFIED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; no allocator, technology, ABI or release.

## Security and rollback

Documentary only. No secret, upload, paid service, dependency or runtime change. Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.

## Open risks

Priority aging/fairness weights, starvation accounting, hard deadlines and priority inheritance remain future scope if the owner requests them. Full Q4 remains `BLOCKED`; no performance threshold or real-time guarantee is claimed.

## Proposed checkpoint delta

`CORE-03-04` completed as satisfied; `CORE-03-05` (“dependências”) remains the next blocked packet and requires its own satisfaction/G6 decision.
