# ADR-0004 — CORE-02 Memory Strategy

**Date:** 2026-11-14 | **Status:** PROPOSED FOR IMPLEMENTATION VALIDATION  
**Work Order:** NLE-P00-WO-002-CORE-02 | **Issue:** #10

## Problem
Stormline requires ambitious graphics, VFX density and worlds while keeping frame-time tail latency, memory footprint and OOM behavior acceptable on modest Windows/Linux/macOS hardware. The engine needs a stable memory policy for many modules and plugins without betting the entire application on a bespoke allocator.

## Proposed decision
1. Use a **C++20 `std::pmr`-compatible resource interface** for explicitly opted-in engine allocations, with allocation domain/lifetime and owner contracts.
2. Keep OS/C++ system allocators as reproducible baseline and fallback. Do not override global allocation during the first implementation step.
3. Trial **mimalloc 3.x** and **rpmalloc** in a controlled benchmark harness with real Stormline workloads before selecting a default.
4. For per-frame/job allocations, evaluate bounded linear/monotonic scratch arenas with lifetime fences; specialized pools for VFX/network/streaming only when measured.
5. Research a small proprietary **Stormline Memory Fabric (SMF)** for hierarchical budgets, pressure response and optional allocation journal, not a wholesale reinvention of malloc.
6. Use Tracy/sanitizers/natively supported profiling for reproducible diagnostics; disable or bound overhead in shipping configurations.
7. Host/plugin boundaries must own allocations explicitly; GPU VRAM belongs to GFX-03, asset lifetime/streaming policy belongs to DATA-05/WORLD-03.
8. Document Windows x64, Linux x64 and macOS arm64 tests and Intel feasibility, with strict OOM, wrong-thread, lifetime and security checks.

## Alternatives evaluated
- **Only system malloc:** simplest baseline but may not meet high VFX/streaming tail latency; use as control, not prematurely rejected.
- **Set mimalloc globally everywhere:** easy benchmarking but possibly unsafe at plugin/CRT boundaries; reject as first step.
- **rpmalloc always:** thread-focused but may incur platform-specific memory reservation overhead; trial, not frozen.
- **Full proprietary general allocator:** unnecessary engineering burden without evidence; reject initially.
- **Only arenas:** cannot handle unpredictable lifetime/interactive authoring and plugins; restrict to scoped allocations.

## Proof obligations before final approval
- Pin exact versions/licenses and security advisories.
- Benchmark representative workloads on approved Windows/Linux/macOS machines; p50/p95/p99, RSS, fragmentation, retained/committed memory and memory pressure.
- Test UAF, double-free, leaks, OOM, over-alignment, cross-thread frees and sanitizer combinations.
- Demonstrate proper plugin/SDK ABI and audio real-time constraints.
- Prove low-RAM tiers meet approved budgets; reject innovation if overhead outweighs benefit.
- Objective audit and Evidence Bundle without HIGH/CRITICAL blockers.

## Consequences and open decisions
No allocator selection or speedup is proven by this ADR. In future implementation, early, explicit `std::pmr` and targeted arenas have a relatively low coupling cost; global replacement requires stronger proof. The choice of release default allocator, SMF admission, minimum OS/version and memory tiers remains OPEN.

## Status semantics
The research document and decision **may be approved as planning**. The technology is not integrated, performance is not verified and implementation requires its own Work Order.
