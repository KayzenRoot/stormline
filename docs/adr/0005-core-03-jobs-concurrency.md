# ADR-0005 — Job Scheduling and Concurrency Baseline

**Status:** PROPOSED; NOT APPROVED FOR IMPLEMENTATION  
**Date:** 2026-11-14 | **Work Order:** NLE-P00-WO-002-CORE-03 | **Issue:** #13

## Context
The engine must drive demanding 3D worlds while maintaining consistent frame times on low-core CPUs, without unstable task order, deadlock or starvation. It must run natively on Windows, Linux and macOS and in headless server mode. CORE-01 and CORE-02 research is documented, but neither module is implemented or benchmarked.

## Proposed choice
- Use C++20 `std::jthread`/cooperative stop primitive for managed workers.
- Prototype candidate task graph using **Taskflow v4.x** and compare to **enkiTS**; include baseline serial/fixed pool and optionally oneTBB, not a prematurely bespoke scheduler.
- Public CORE-03 API must be versioned and own `TaskGraph, JobHandle, CancellationScope, JobFence, ExecutorStats` contracts, hiding third-party types from engine/public SDK.
- Streaming/background work must have quotas so frame-critical work retains capacity on 2–4-core targets.
- Determinism is about observable simulation state/commit order where required, not fixed thread scheduling order.
- Proprietary Stormline Frame-Aware Scheduler is R&D only, with a prove-or-drop rule against simpler implementations.
- Profiling, cancellation, main-thread affinity, audio real-time separation and GPU submission boundary are mandatory design obligations.

## Alternatives
Single-thread only: deterministic baseline but lacks scalability. Custom native work-stealing executor immediately: avoid complexity without need. oneTBB as universal dependency: hold until packaging and performance justify. Taskflow or enkiTS as final: neither selected without per-platform benchmark.

## Proof before technology promotion
Exact dependency versions and notices; multi-OS compiler checks; benchmark across low-core and multicore machines; race/deadlock/cancel/overload tests; memory budget and frame-time p95/p99; no new HIGH/CRITICAL; rollback path. Use free public CI and test real machines for performance (CI hosted runner is not a hardware performance guarantee).

## Result
This ADR and the architecture specification can be APPROVED as **planning artifacts only** after audit. No implementation authorization, compatibility claim, release target or proven proprietary invention arises from a docs PR.

