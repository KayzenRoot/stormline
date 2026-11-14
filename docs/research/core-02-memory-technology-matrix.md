# CORE-02 — Memory Allocator Technology Decision Matrix
Work Order: NLE-P00-WO-002-CORE-02 | **Status: PROPOSED RESEARCH**

## Evaluation criteria
No unmeasured numerical score. Suggested evidence-weighted dimensions:
- Tail allocation latency and frame-time impact (25%).
- Working set/RSS, fragmentation and low-memory behavior (25%).
- Memory safety, debug observability and correct failure semantics (20%).
- Windows/Linux/macOS portability and ABI/toolchain fit (15%).
- Commercial license, maintenance and security updates (10%).
- Complexity and integration burden (5%).

Weights themselves are planning preferences and may need owner/benchmark review.

## Candidate table

| Technology | Mechanism | Strength/fit | Limitations and status |
|---|---|---|---|
| **C++20 `std::pmr`** | polymorphic resources, monotonic and pool allocators | Baseline abstraction for resource injection and lifetimes | Not a complete global allocator; implementation/library ABI to test; preferred |
| **System malloc / `new`** | OS toolchain allocator | Control baseline, no dependency | May incur contention/fragmentation in specific patterns; only real benchmarks decide |
| **mimalloc 3.x** | general allocator with multiple heaps and security options | Preferred trial candidate, MIT, cross-OS support; upstream v3.6.1 in Oct 2026 | A/B results on Stormline scenes absent; allocator override/secure flags might change metrics and runtime behavior |
| **rpmalloc** | per-thread heaps, page spans, deferred cross-thread free | Strong alternative for jobs and long-lived/short-lived mixed allocation, Unlicense OR MIT | Thread ownership, OS reservations and memory behavior must be checked |
| **jemalloc** | mature general allocator, heap profiling and arena controls | Optional broader comparison if needed | Version/license/Windows support and complexity not yet vetted |
| **Tracy** | allocation, frame, timing profiling | Research instrumentation candidate, BSD-3-Clause | Profiler overhead, release opt-in and platform build conditions |
| **Sanitizers** | ASan/UBSan/TSan where supported | Catch memory defects and races | Supported combinations differ by OS/toolchain, not all simultaneously |
| **Custom arenas & pools** | lifetime-scoped bump/pool/slab allocations | Useful for frame scratch/VFX/streaming when measured | Fragmentation, resets, wrong-lifetime UAF, duplicated complexity |
| **SMF innovation candidate** | budgets, pressure events, journal, domain adaptive reclaim | Research differentiator if it reduces stalls or protects low-end memory | Must beat simple solutions on measured scenes; no proof today |

## Decision guidance
- Adopt **`std::pmr` design as preferred public C++20 memory resource pattern** (subject to future ABI tests).
- Keep default system allocator as benchmark baseline and fallback.
- Benchmark **mimalloc 3.x** and **rpmalloc** as general allocator candidates; no permanent global override yet.
- Use **Tracy** and sanitizers for development evidence, not as required released runtime dependencies without review.
- Investigate custom **frame/job arenas and memory budgets** before inventing a wholesale general allocator.
- Preserve identical workload, quality settings, compiler flags and exact library revisions in comparisons.

## Latest-source notes (2026-11-14)
mimalloc README identifies v3.6.1 (2026-10-30) as recommended, MIT. Its own published performance claims are upstream claims, **not Stormline-measured**. rpmalloc repository declares Unlicense OR MIT and Windows/Linux/macOS support. Tracy declares BSD-3-Clause and allocation tracing; C++ std::pmr is available since C++17 (compatible with planned C++20). Recheck versions, advisories and license notices before embedding.

### Primary references
- https://en.cppreference.com/cpp/header/memory_resource
- https://github.com/microsoft/mimalloc
- https://github.com/microsoft/mimalloc/blob/main3/LICENSE
- https://github.com/mjansson/rpmalloc
- https://github.com/wolfpld/tracy
- https://github.com/wolfpld/tracy/blob/master/LICENSE

## HOLD/REJECT
- Hold numerical performance commitments until real memory benchmarks.
- Reject process-global allocator override as the first implementation action.
- Hold customized allocator as product differentiator until measured evidence.
- Reject treating GPU VRAM as system RAM without explicit GFX-03 interface.
- Reject extra paid profiling/CI or mandatory external reviewer.
