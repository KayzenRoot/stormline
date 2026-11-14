# CORE-03 — Candidate Scheduler Technology Matrix

**Work Order:** NLE-P00-WO-002-CORE-03 | **Status:** PROPOSED / DOCS ONLY

## Comparative research matrix

| Candidate | Implementation mechanics | License | Pros | Limitations/risks | Gate |
|---|---|---|---|---|---|
| C++20 `std::jthread` / `stop_token` | Threads and cooperative cancellation, no task scheduling by default | ISO library/runtime terms | portable primitives | custom queues, starvation/dep handling required | compiler conformance Windows/Linux/macOS |
| Taskflow v4.x | header-only DAG and executor, work-stealing, subflows | MIT | natural task dependencies and visualization | task graph allocation/overhead needs measurement | DAG and frame latency benchmarks |
| enkiTS | work queues, tasksets, C/C++ API | zlib | game-oriented fine grained tasks | integration API differs from graph/command abstractions | microtask load, cross-thread lifetime tests |
| oneTBB | task scheduler, parallel algorithms, flow graph | Apache-2.0 | mature graph/parallel ecosystem | dependency size/ABI/runtime packaging cost | cross-platform binary/ABI, lifecycle, footprint |
| SFAS in-house | frame-aware budget/commit layer | Original proposal, not implemented | possible fixed-budget frame fairness and better diagnostics | risk of reinvention, complexity and maintenance | A/B vs Taskflow/enkiTS and simpler queue |
| Tracy | tracing and profiling | BSD-3-Clause candidate | inspect queue/frame stalls | overhead and build integration | opt-in trace correctness |

### Source verification
- Taskflow v4 compiler floor, MIT and OS support: https://taskflow.github.io/taskflow/index.html
- enkiTS README/license and required C++11: https://github.com/dougbinks/enkiTS
- oneTBB license: https://github.com/uxlfoundation/oneTBB/blob/master/LICENSE.txt
- C++20 cancellation: https://en.cppreference.com/cpp/thread/stop_token
- Tracy: https://github.com/wolfpld/tracy

## Weighted evaluation (proposed)
- Frame/tick tail latency and gameplay fairness **25%**.
- Deterministic logical result and error containment **20%**.
- CPU/core scaling and low-end 2-core operation **20%**.
- Memory, queue growth and allocation budget **15%**.
- Portability, license, maintenance and ABI **15%**.
- Ease of instrumentation and future editor integration **5%**.

Scores are **not filled** until workloads, hardware, versions and benchmark data exist. Source-provided performance figures cannot be presented as Stormline results.

## Dependencies
CORE-01, CORE-02, CORE-04 contractual simulation clock (future); GFX-03 GPU queue and AUD-01 callback are strictly isolated. Thread count must never assume maximum hardware concurrency is usable (container quotas, heterogeneous cores, background load).

## Preliminary recommendation
1. Default design language: **C++20**, `std::jthread` for owned worker lifetime.
2. **Taskflow** as first graph-based candidate and **enkiTS** as first compact game-oriented benchmark comparator.
3. oneTBB as an option when benchmarks and functionality merit packaging costs.
4. Proprietary SFAS only as conditional innovation with measurable ROI; never claim it exists today.
5. No technology selected for production and no code/library added.

