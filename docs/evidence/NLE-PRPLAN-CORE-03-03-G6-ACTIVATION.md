# NLE-PRPLAN-CORE-03-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION PROPOSAL / OWNER-AUTHORIZED / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `38d73bd46fc66cc4f83294bcad44e7e310534013`. **Formal packet:** `NLE-PRPLAN-CORE-03-03`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **Contract:** [core-03-task-graph-v0](../contracts/core-03-task-graph-v0.md). **WO:** [NLE-PRPLAN-CORE-03-03](../work-orders/NLE-PRPLAN-CORE-03-03.md).

## Authorization

The owner explicitly authorized unblocking the continuation on 2026-11-21: “faça o que preciso pra desbloquear a continuação e continue ... autorizado”. This gate activates **only** `NLE-PRPLAN-CORE-03-03` after exact-head Docs Validation and pt-BR audit. It does not select Taskflow/enkiTS/oneTBB/SFAS, approve a public ABI or release, change the frozen contract, declare CORE-02 complete, or unlock `CORE-03-04`..`-10`.

## Preconditions

- `CORE-03-02` contract approved by PR #505 (`aa97b23`) and recorded by PR #506 (`38d73bd`).
- ADR-0105 D2 admission ratified in NLE-D022; formal dependency `CORE-02` remains recorded.
- Completed capabilities only: `CORE-02-03` ownership, `-04` system allocator baseline, `-05` arena, `-06` budget, `-07` leak tracking, `-08` telemetry, `-09` integrated qualification.
- CORE-02 is `NOT_QUALIFIED` as a module; no CORE-02 completion is claimed.

## D2 capability admission

| Capability | Completed packet |
|---|---|
| `CORE02_MEMORY_OWNERSHIP` | `NLE-PRPLAN-CORE-02-03` |
| `CORE02_SYSTEM_ALLOCATOR_BASELINE` | `NLE-PRPLAN-CORE-02-04` |
| `CORE02_MONOTONIC_ARENA` | `NLE-PRPLAN-CORE-02-05` |
| `CORE02_MEMORY_BUDGET` | `NLE-PRPLAN-CORE-02-06` |
| `CORE02_LEAK_TRACKING` | `NLE-PRPLAN-CORE-02-07` |
| `CORE02_MEMORY_TELEMETRY` | `NLE-PRPLAN-CORE-02-08` |
| `CORE02_INTEGRATED_QUALIFICATION` | `NLE-PRPLAN-CORE-02-09` |

Not required and not used: module completion, allocator selection, Q4 physical matrix, public ABI, release, renderer/GPU, audio, network. `module_completion_claimed=false`.

## Bounded technical slice

- `TaskGraph` and `JobExecutor` exactly as frozen by the contract; fixed 256-task graph and 1..32 workers.
- Priorities, dependencies, cycle detection, deterministic commit order, cancellation scopes, MainThread affinity, fences, bounded queue, typed errors and report-only stats.
- Exact allowlist: `src/stormline/core/jobs/task_graph.hpp`, `task_graph.cpp`, `job_executor.hpp`, `job_executor.cpp`, `tests/core/job_executor_tests.cpp`, additive `CMakeLists.txt`, additive CORE-03 filters/TSan job in `.github/workflows/core01-internal-headless.yml`, `docs/evidence/NLE-PRPLAN-CORE-03-03.md`.
- No third-party scheduler type, public ABI or release.

## Gate state after merge (expected, not yet promoted)

- Manifest root `CORE03_03_READY_L1_CAPABILITY_OVERLAY`: **719 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY` (`CORE-03-03`), 22 `COMPLETED`, 6 approved gates**.
- `CORE-03-03` becomes `EXECUTOR_READY` with `risk=ELEVATED`, `release_class=INTERNAL_ONLY`, ADR-0105 and this evidence; `CORE-03-04`..`-10` remain `PLANNED_BLOCKED`.
- Selector allows only `NLE-PRPLAN-CORE-03-03`; every other ID exits 2; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations for the code PR

- JOB-01 basic graph; JOB-02 dependency/commit order; JOB-03 invalid/cycle; JOB-04 priority/TaskId; JOB-05 cancellation; JOB-06 affinity/deadlock; JOB-07 backpressure; JOB-08 shutdown/lifetime; JOB-09 determinism/stress; JOB-10 report-only benchmark.
- Linux GCC, Linux ASan/UBSan, Linux TSan, Windows MSVC and macOS AppleClang exact-head CI.
- No race, deadlock, detached thread, leak, queue overrun, commit reordering or MainThread violation; no HIGH/CRITICAL.
- Docs Validation, pt-BR audit, file allowlist, `CORE-02 NOT_QUALIFIED`, no release/ABI/technology claim.

No code or native PASS is claimed by this gate.

## Security and rollback

No dependency, package installation, secret, upload, paid service or runtime download. Unmerged: close the gate branch; `main` untouched. After merge: normal revert PR, never force push. CORE-02 remains `NOT_QUALIFIED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; no release.
