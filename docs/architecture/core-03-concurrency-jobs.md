# CORE-03 — Jobs, Task Graph & Concurrency Architecture v0.1

**WO:** NLE-P00-WO-002-CORE-03 | **Issue:** #13 | **Risk:** LOW for this planning artifact; STANDARD/ELEVATED for subsequent native implementation.  
**Base SHA:** `b76e7fd9992dcc012c212e8afe3d2836d9776c63` | **Status:** RESEARCH PROPOSED / NOT IMPLEMENTED.

## Mission
Design a fast, predictable, portable execution layer for high-quality 2D, 2.5D and 3D worlds, asset loading, physics, animation, AI, rendering preparation and editor processing across Windows, Linux and macOS. Target **low-core-count PCs** as deliberately as 16+ core machines. Optimize p95/p99 frame time, fairness and correct dependency order before peak jobs/second.

## Boundaries and ownership
- CORE-01 controls OS threads, platform capability hints and lifecycle.
- CORE-02 owns allocation domains, scratch arenas and lifetime fences.
- CORE-03 owns work submission, scheduling, dependency resolution, cancellation, queueing and worker lifetime.
- CORE-04 defines clock/tick and synchronization boundaries; CORE-03 **must not** own simulation time or cause an architecture cycle.
- CORE-06 provides instrumentation; CORE-03 emits bounded tracing events.
- GFX-03 owns GPU command submission and fences. Jobs may produce CPU-side rendering data but cannot make arbitrary GPU calls.
- AUD-01 owns real-time callbacks. The audio callback is never blocked by CORE-03 queues or allocates unpredictable memory.
- AI/MCP modules receive **read-only, scoped diagnostics** and controlled build/test jobs, never arbitrary system worker privileges.

## Candidate public contracts (logical schemas only)

| Contract | Fields / responsibility | Error and safety obligations |
|---|---|---|
| `TaskId` | stable within job graph/revision, ownership domain | no reuse while in-flight |
| `JobRequest` | task kind, group, priority, estimated cost, deadline hint, cancellation scope, resource reads/writes | reject invalid graph/resource policy |
| `JobHandle` | scoped result, diagnostic ID, completion state | no dangling native pointers outside lifetime |
| `TaskGraph` | nodes/edges and dependency DAG; typed execution phases | reject cycles, preserve barriers |
| `JobFence` | completion and group barriers with explicit lifetime | avoid waiting on a fence from its own worker |
| `WorkBudget` | max active workers, frame/tick budget, fairness weights, background quotas | graceful overload and starvation accounting |
| `ExecutorStats` | enqueue-to-start latency, queue depth, busy/idle, completed/cancelled, steals, tail latency | aggregation/redaction rather than unbounded telemetry |

### Scheduling classes
- **Frame critical:** bounded work tied to an approved frame phase; failure to meet budget is diagnosable.
- **Simulation deterministic:** task data may be parallel, but externally observable state commits in a defined deterministic order.
- **Streaming/background:** asset IO, shader prepare, editor scanning, import jobs; bounded concurrency to protect gameplay.
- **Main thread / OS affinity:** explicit ownership for window events and platform APIs that require it.
- **GPU preparation:** CPU work may parallelize command-recording preparation; submission rules belong to GFX-03.
- **Real-time audio:** **not** a general job class. RT callback must avoid locks, blocking waits and dynamic allocation.

## Lifecycle
`UNINITIALIZED -> STARTING -> IDLE/RUNNING -> DRAINING/CANCELLING -> STOPPED` with `FAILED` for recoverable and unrecoverable events. Shutdown requests cancellations, rejects new jobs, drains according to policy and releases resources only after owner/fence completion. Graph destruction while work is active must be rejected or await a bounded safe point.

Failure model: `CANCELLED`, `DEPENDENCY_FAILED`, `RESOURCE_EXHAUSTED`, `DEADLINE_MISSED`, `CYCLE_FOUND`, `AFFINITY_VIOLATION`, `DEADLOCK_RISK`, `WORKER_SHUTDOWN`, `UNKNOWN_ERROR`. Native exceptions cannot cross a C ABI or worker boundary without controlled translation.

## Technology candidates

| Technology | How it works | Recommended disposition |
|---|---|---|
| C++20 `std::jthread` + `std::stop_token` | automatic join and cooperative stop request for threads, **not** a ready-made task graph | foundational lifecycle candidate |
| **Taskflow 4.x**, MIT | header-only task DAG executor, dynamic subflows and parallel operators; work-stealing scheduler | preferred graph-level evaluation baseline |
| **enkiTS**, zlib | lightweight task scheduler for data-parallel tasks with C/C++ integration | preferred fine-grained engine-workload comparator |
| **oneTBB**, Apache-2.0 | mature task-based parallelism and flow graph ecosystem | third comparator when dependency/ABI footprint justified |
| **Stormline Frame-Aware Scheduler (SFAS)** | research candidate for budget-aware queues, deterministic commit lanes and trace-driven profiling | prototype only after baseline studies |
| **Tracy**, BSD-3-Clause | CPU zones/locks/allocation event correlation | opt-in candidate profiling; avoid runtime requirement |

Taskflow v4 documentation identifies C++20 compiler requirements and Windows/Linux/macOS support. enkiTS requires C++11+ and has permissive zlib terms; oneTBB uses Apache-2.0. Exact released tags, notices and vulnerability reviews must be pinned **before** vendoring. Sources: https://taskflow.github.io/taskflow/index.html , https://github.com/dougbinks/enkiTS , https://github.com/uxlfoundation/oneTBB , https://en.cppreference.com/cpp/thread/jthread .

## Proprietary innovation proposal: SFAS
Stormline's **Frame-Aware Scheduler** may combine:
1. Task graphs carrying frame/tick owner and estimated cost, with **optional** budget-aware priority.
2. A **critical-path visualization** and queue waiting-time attribution integrated with CORE-06 profiler.
3. Bounded background imports/streaming that respect frame-critical work, especially on 2-core CPUs.
4. Deterministic phase barriers: parallel computations may be nondeterministic in execution order, but deterministic commit order is explicit where games require it.
5. Thermal/power-aware backoff only from reliable CORE-01 signals; absent signals become UNKNOWN, never fabricated.
6. Cancellation propagation and error containment for editor hot-reload, project closure and asset migration.

This is **not a demonstrated novel algorithm**. The research is worthwhile only if it beats a small taskflow/enkiTS-backed solution or improves correctness/diagnostics with acceptable overhead. Do not write a proprietary scheduler to create a branding claim.

## Anti-patterns to prohibit
- `std::async` per game object/particle, thread per task, or busy polling every frame.
- Unbounded job creation and queue growth without backpressure.
- Locking audio callback from the general scheduler or running OS window API on arbitrary worker threads.
- Hidden nondeterministic updates to authoritative gameplay state.
- Cross-thread free of scratch arena after an unsafe reset.
- GPU submission from workers without proper RHI contracts/fences.
- Loading the full job graph into MCP context rather than pagination/aggregates.
- More worker threads than effective CPU capacity as an untested default.

## Cross-platform matrix
| Test | Windows | Linux | macOS |
|---|---|---|---|
| Build & compile | MSVC/clang-cl x64 | Clang/GCC x64 | Apple Clang arm64; Intel feasibility |
| Thread lifecycle | start/cancel/shutdown | same, include cgroup/affinity | same, sleep/wake and Apple performance/efficiency core policies |
| Workload | 2/4/8/16 cores where available | 2/4/8/16 cores | Apple Silicon performance/efficiency heterogeneity |
| Diagnostics | Tracy/ETW option | Tracy/perf option | Tracy/Instruments option |
| Safety | TSAN when supported, ASAN/UBSAN and stress | TSAN/ASAN/UBSAN | supported sanitizer set and native tools |

OS and CPU matrices are **planned tests**, not proof compiled code exists.

## Future reproducible benchmark plan
Establish simple serial, C++20 fixed-pool, Taskflow, enkiTS, oneTBB and SFAS candidates in **isolated benchmark harness** on equal workloads:
- 10k trivial tasks with varying granularity; 100–10k medium/heavy tasks; dynamic DAG changes.
- Mixed 2D tilemap updates, 3D animation/physics broadphase, asset loading, shader compilation, VFX/particles and audio running independently.
- 2-core modest PC: frame critical latency vs background task pressure; 4-core budget and high-core scaling.
- p50/p95/p99 task latency, queue waiting, steals/idle, CPU frame time, RSS/allocations, power if measurable, task/second.
- Deadlocks/races, graph cycles, cancellation storms, task fault injection, exhaustion, main-thread violations, headless server.
- Replay scene with same seed, compare **logical game state**, rather than promise deterministic thread execution.
- Record SHA, OS, CPU, compiler, flags, dependency version, workload seed, sample sizes, baseline noise and trace. No invented speedup or target FPS.

## Approval gates
A documented design is not a working scheduler. ADR-0005 remains PROPOSED until benchmarks/ABI/safety evidence and future implementation WO. A subsequent architecture/implementation plan must specify exact file paths and APIs once the repo has real code. **Do not begin CORE-04 until this research is audited and checkpoint reconciled.**

