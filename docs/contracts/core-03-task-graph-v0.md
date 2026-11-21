# CORE-03 INTERNAL_ONLY Task Graph & Executor Contract v0 (NLE-PRPLAN-CORE-03-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `dcb2cbd7739d44d09f432621d2dbd0acdef14cb1`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md), [ADR-0005](../adr/0005-core-03-jobs-concurrency.md). **WO:** [NLE-PRPLAN-CORE-03-02](../work-orders/NLE-PRPLAN-CORE-03-02.md).

## Objective

Define the first internal CORE-03 contract: a bounded fixed-capacity task graph and executor with explicit priorities, dependencies, cancellation scopes, fences, work budget, deterministic commit order, typed errors and diagnostics. No implementation, dependency, public ABI or release is authorized by this contract.

## Admission and boundaries

- Formal `CORE-02` dependency remains; admission is limited to completed `CORE-02-03..09` capabilities under NLE-D022/D2. CORE-02 module completion is **not** claimed.
- CORE-01 owns OS threads/lifecycle; CORE-02 owns memory domains; CORE-04 owns time/tick; CORE-06 owns instrumentation; GFX-03 owns GPU submission; AUD-01 owns real-time audio. CORE-03 must not create cycles into those owners.
- No third-party scheduler type appears in the contract. Taskflow/enkiTS/oneTBB remain benchmark candidates only; SFAS is not started.

## Internal API (logical, exact names)

```cpp
namespace stormline::core::jobs {

enum class JobPriority : std::uint8_t { Background, Normal, High, FrameCritical };
enum class JobAffinity : std::uint8_t { AnyWorker, MainThread };
enum class CancellationStatus : std::uint8_t { Active, Requested };

enum class JobError : std::uint8_t {
    None,
    InvalidCapacity,
    InvalidTask,
    InvalidGraph,
    CycleDetected,
    DependencyFailed,
    Cancelled,
    QueueFull,
    ResourceExhausted,
    DeadlineMissed,
    AffinityViolation,
    DeadlockRisk,
    WrongThread,
    NotInitialized,
    ShuttingDown,
    InternalFailure
};

enum class ExecutorState : std::uint8_t { Uninitialized, Running, Draining, Stopped, Failed };

struct TaskId { std::uint32_t value{0}; };
struct JobHandle { std::uint64_t value{0}; };
struct CancellationScope { std::uint64_t value{0}; };
struct JobFence { std::uint64_t value{0}; };

struct WorkBudget {
    std::uint32_t max_workers{1};
    std::uint32_t max_tasks{256};
    std::uint64_t frame_budget_ns{0};   // 0 = report-only, no hard deadline
    std::uint32_t background_quota{0}; // reserved non-frame workers
};

struct ExecutorStats {
    std::uint64_t submitted{0};
    std::uint64_t completed{0};
    std::uint64_t cancelled{0};
    std::uint64_t failed{0};
    std::uint64_t queue_depth{0};
    std::uint64_t peak_queue_depth{0};
    std::uint64_t busy_ns{0};
    std::uint64_t idle_ns{0};
};

using JobFunction = void (*)(void* context);
using CommitFunction = void (*)(void* context);

class TaskGraph final {
public:
    static constexpr std::uint32_t capacity = 256;
    explicit TaskGraph(std::uint32_t tasks) noexcept;

    [[nodiscard]] JobError add_task(TaskId id, JobPriority priority, JobAffinity affinity,
                                    CancellationScope scope, JobFunction function,
                                    void* context) noexcept;
    [[nodiscard]] JobError add_dependency(TaskId before, TaskId after) noexcept;
    [[nodiscard]] JobError add_commit(std::uint32_t order, TaskId task,
                                      CommitFunction function, void* context) noexcept;
    [[nodiscard]] JobError finalize() noexcept;
    [[nodiscard]] bool valid() const noexcept;
};

class JobExecutor final {
public:
    static constexpr std::uint32_t max_workers = 32;
    JobExecutor() noexcept;
    ~JobExecutor() noexcept;

    JobExecutor(const JobExecutor&) = delete;
    JobExecutor& operator=(const JobExecutor&) = delete;
    JobExecutor(JobExecutor&&) = delete;
    JobExecutor& operator=(JobExecutor&&) = delete;

    [[nodiscard]] JobError start(WorkBudget budget) noexcept;
    [[nodiscard]] JobError submit(const TaskGraph& graph, JobFence& fence) noexcept;
    [[nodiscard]] JobError request_cancel(CancellationScope scope) noexcept;
    [[nodiscard]] JobError wait(JobFence fence) noexcept;       // owner thread only
    [[nodiscard]] JobError drain() noexcept;                     // owner thread only
    [[nodiscard]] JobError stop() noexcept;                      // idempotent
    [[nodiscard]] ExecutorState state() const noexcept;
    [[nodiscard]] ExecutorStats stats() const noexcept;
    void pump_main_thread() noexcept;                            // owner thread only
};

}  // namespace stormline::core::jobs
```

No implementation is provided by this contract. Signatures may be refined only by an audited contract correction before `CORE-03-03`.

## Semantics

- **Capacity:** graph capacity 256 and executor workers 1..32; zero/invalid values return `InvalidCapacity`; no dynamic graph growth.
- **Task identity:** `TaskId` must be nonzero and unique within a graph; duplicates/invalid IDs return `InvalidTask`.
- **Dependencies:** edges must reference graph tasks and form a DAG. `finalize()` detects cycles (`CycleDetected`); dependency failure marks dependents `DependencyFailed` and does not run them.
- **Priority:** `FrameCritical` > `High` > `Normal` > `Background` when ready tasks compete; ties are deterministic by `TaskId`. Priority is not a hard real-time guarantee.
- **Affinity:** `MainThread` tasks never run on workers; `pump_main_thread()` executes them on the owner thread. Waiting on a fence from a worker returns `DeadlockRisk`; only the owner thread may `wait`.
- **Cancellation:** `request_cancel(scope)` sets a cooperative flag; pending tasks in scope return `Cancelled` without running; running tasks observe the scope through their context. New submissions after shutdown return `ShuttingDown`.
- **Commit order:** commit callbacks execute in ascending `order` after their task completes and dependencies are satisfied; duplicate order values are rejected. Parallel task execution must not reorder externally visible commits when a commit order is declared.
- **Budget/backpressure:** `max_tasks` and worker capacity bound the queue; overflow returns `QueueFull` without mutation. `background_quota` reserves workers for non-frame work; `frame_budget_ns` is report-only in v0 (0 means no deadline claim).
- **Lifecycle:** `Uninitialized -> Running -> Draining -> Stopped`; failures enter `Failed`; `stop()` is idempotent and drains/cancels according to policy. Destruction while running performs bounded cancellation/join, never detaches threads.
- **Errors:** no exception crosses the API; all failures are typed; wrong-thread use returns `WrongThread`.
- **Diagnostics:** `ExecutorStats` counters are monotonic snapshots; no pointer addresses, unbounded logs or third-party tracing.

## Test oracles (future CORE-03-03)

| ID | Scenario | Oracle |
|---|---|---|
| JOB-01 | basic graph | independent tasks complete once; stats submitted/completed balanced |
| JOB-02 | dependency order | `after` never starts before `before`; commit order deterministic |
| JOB-03 | cycle/invalid graph | cycle, duplicate ID, dangling edge return typed errors without execution |
| JOB-04 | priority/fairness | ready tasks dispatch by priority and TaskId tie-break under a controlled pump |
| JOB-05 | cancellation | pending scope tasks cancelled; running tasks observe request; no new work after shutdown |
| JOB-06 | affinity/deadlock | MainThread tasks only on owner; worker wait rejected with `DeadlockRisk` |
| JOB-07 | backpressure | queue overflow returns `QueueFull`; stats/state unchanged |
| JOB-08 | shutdown/lifetime | stop idempotent; no detached threads; destruction drains |
| JOB-09 | determinism/stress | repeated graph runs produce identical commit order; race/TSan/ASan/UBSan clean |
| JOB-10 | benchmark/report-only | enqueue-to-commit latency and throughput printed; no threshold |

## Exact implementation allowlist for future packet -03

1. `src/stormline/core/jobs/task_graph.hpp`
2. `src/stormline/core/jobs/task_graph.cpp`
3. `src/stormline/core/jobs/job_executor.hpp`
4. `src/stormline/core/jobs/job_executor.cpp`
5. `tests/core/job_executor_tests.cpp`
6. `CMakeLists.txt` (additive CORE-03 target/tests)
7. `.github/workflows/core01-internal-headless.yml` (additive CORE-03-03 filters)
8. `docs/evidence/NLE-PRPLAN-CORE-03-03.md`

`CORE-03-03` remains `PLANNED_BLOCKED`; its implementation requires a separate G6 activation, exact audit, TSan/race/deadlock proof and owner authorization.

## Stop / rollback / security

Stop on stale source, missing D2 admission, technology/third-party type in the API, code outside allowlist, dynamic graph growth, worker fence wait, unbounded queue, release/ABI overclaim, HIGH/CRITICAL. Unmerged: close branch; after merge: normal revert PR. No manifest/registry/G3/license change is authorized by this contract beyond the `-02` approval.
