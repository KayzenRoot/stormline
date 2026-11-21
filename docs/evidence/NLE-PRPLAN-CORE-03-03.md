# NLE-PRPLAN-CORE-03-03 — Task graph & executor implementation evidence

**Status:** `IMPLEMENTATION / EXACT-HEAD CI PENDING`. **Base main:** `6cd1e9c3962bdbd71e9fded54787842203440e95`. **Formal packet:** `NLE-PRPLAN-CORE-03-03`. **Risk:** `ELEVATED`. **Release class:** `INTERNAL_ONLY`. **Contract:** [core-03-task-graph-v0](../contracts/core-03-task-graph-v0.md). **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **WO:** [NLE-PRPLAN-CORE-03-03](../work-orders/NLE-PRPLAN-CORE-03-03.md).

## Scope

Exact allowlist implemented:

1. `src/stormline/core/jobs/task_graph.hpp`
2. `src/stormline/core/jobs/task_graph.cpp`
3. `src/stormline/core/jobs/job_executor.hpp`
4. `src/stormline/core/jobs/job_executor.cpp`
5. `tests/core/job_executor_tests.cpp`
6. `CMakeLists.txt` (additive CORE-03 target/tests and TSan option)
7. `.github/workflows/core01-internal-headless.yml` (additive CORE-03 paths and TSan job)
8. `docs/evidence/NLE-PRPLAN-CORE-03-03.md` (this file)

No dependency, third-party scheduler type, public ABI, release, allocator selection, registry, G2 or license change.

## Contract implementation

- `TaskGraph`: fixed 256-task storage, nonzero unique task IDs, validated priority/affinity, dependency edges, duplicate/self/dangling rejection, Kahn cycle detection in `finalize()`, ascending commit records with duplicate-order rejection, no dynamic graph growth.
- `JobExecutor`: 1..32 joined workers, bounded queue, priority plus TaskId tie-break, MainThread tasks only through `pump_main_thread()`, cooperative cancellation scopes, per-job fences, fixed job slots with generation validation, deterministic commit lane, report-only stats, `wait`/`drain` owner-only, worker/commit/main-task `wait` rejected with `DeadlockRisk`, idempotent `stop()`, no detached threads.
- Commit callbacks execute serially in ascending `order`; the commit-lane mutex is acquired blocking so a finishing worker or waiting owner cannot miss a newly ready commit. Jobs are pruned from queues when complete so `queue_depth` reflects live work.
- `stop()` waits for running tasks, serializes with the commit lane, cancels pending work, finalizes every job and joins all workers.
- Errors are typed; no exception crosses the API. Task/commit exceptions are contained and fail the job.

## JOB-01..JOB-10 oracles

| ID | Scenario | Result |
|---|---|---|
| JOB-01 | Basic graph, independent tasks, stats balance | PASS |
| JOB-02 | Dependency order and deterministic commit order | PASS |
| JOB-03 | Cycle, duplicate ID/edge/commit order, dangling edge, capacity, add-after-finalize | PASS |
| JOB-04 | Priority and TaskId dispatch; background-worker reservation | PASS |
| JOB-05 | Cancellation scope isolation and pending-task cancellation | PASS |
| JOB-06 | MainThread affinity, non-owner wait, worker wait deadlock, pump ownership | PASS |
| JOB-07 | QueueFull without mutation, invalid budget and pre-start errors | PASS |
| JOB-08 | Drain, idempotent stop, restart denial, worker stop denial, destructor join | PASS |
| JOB-09 | 20 deterministic 64-task/64-commit runs, 10 concurrent jobs, stress | PASS |
| JOB-10 | Report-only throughput/latency printout, no threshold | PASS |

## Local evidence

- Windows 11 x64 / MSVC 19.44 (VS 2022 BuildTools), Ninja Debug: `core03_*` **10/10 PASS**; full CTest **121/121 PASS**. One earlier full-suite run hit the pre-existing timing-sensitive `core02_q4_helper_failclosed` PowerShell case; it passed standalone 8/8 and on the next full run. No CORE-03 failure.
- WSL Ubuntu 24.04 / GCC 13.3.0, `-fsanitize=address,undefined -O1`: JOB-01..JOB-10 **10/10 PASS**, no ASan/UBSan report.
- WSL Ubuntu 24.04 / GCC 13.3.0, `-fsanitize=thread -O1` with `setarch -R`: JOB-01..JOB-10 **10/10 PASS**, no TSan report.
- WSL Ubuntu 24.04 / GCC 13.3.0, `-O2 -Wall -Wextra -Wpedantic -Werror`: build clean; JOB-09 repeated **2000/2000 PASS** with no timeout.
- `JOB10_BENCH` samples (report-only, not thresholds): approximately 15k–50k tasks/s depending on sanitizer/host.

## Errors and corrections

1. The first commit sequencer did not advance `next_commit` when selecting a ready commit, so the same commit was selected forever and JOB-02/09/10 timed out. Corrected by incrementing the per-job cursor before executing the serialized callback.
2. `run_ready_commits` used `try_lock`; a waiter could observe a task completion, fail to acquire the commit lane, sleep, and miss the release with no further notification. Corrected by acquiring the commit lane blocking; JOB-09 then passed 2000/2000 optimized repetitions.
3. Queue items for cancelled/failed jobs were inert but still counted in `queue_depth` until popped. Added completion-time pruning of finished-job items.
4. `stop()` could leave a job with completed tasks but pending commits non-terminal. Added commit-lane serialization in `stop()` and explicit terminal finalization before join.

## Security and architecture

- CORE-02 remains `NOT_QUALIFIED`; D2 admission uses only completed `CORE-02-03..09` capabilities; formal dependency remains recorded.
- No third-party scheduler, no network, no filesystem, no secret, no upload, no paid service, no global allocator override.
- CORE-03 uses only C++20 standard library facilities; CORE-01/02/04/06/GFX-03/AUD-01 boundaries are unchanged.
- `INTERNAL_ONLY`; no public ABI, release, license or performance claim.

## Rollback

Unmerged: close the branch/PR; `main` untouched. After merge: normal revert PR; never force push or rewrite history.

## Open risks

- Maximum 256 outstanding job slots and 256 cancelled scope IDs are implementation bounds, not qualified limits.
- `frame_budget_ns` remains report-only and is not used as a deadline.
- No allocator selection, physical Q4 matrix, CORE-02 completion, release or public ABI is claimed.
- Full Q4 remains `BLOCKED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

- `CORE-03-03` `EXECUTOR_READY` -> `COMPLETED` with this code PR number.
- Manifest `CORE03_03_COMPLETED_REST_BLOCKED`: **719 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 23 `COMPLETED`, 6 approved gates**.
- `CORE-03-04`..`-10` remain `PLANNED_BLOCKED`; selector then denies every ID; registry byte-identical; CORE-02 remains `NOT_QUALIFIED`.

## Exact-head CI

Pending. This section will be updated only with real run IDs and conclusions after the code PR is opened.
