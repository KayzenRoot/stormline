# CORE-02 — Memory, Allocators & Budgeting: Technical Architecture v0.1

**Work Order:** NLE-P00-WO-002-CORE-02 | **Issue:** #10 | **Parent:** NLE-P00-WO-002  
**Status:** PROPOSED / NOT IMPLEMENTED | **Date:** 2026-11-14  
**Baseline main:** 98738969c970c2f04cfaa35c84da86ab41688744

## 1. Objective
Design predictable, safe, measurable, low-overhead memory behavior for a proprietary 2D/2.5D/3D engine with unusually ambitious renderer, VFX, streaming, audio and AI-driven editor workflows, including **low-end PCs**. Scope includes Windows, Linux, macOS, and headless server processes; browser target has a separate memory model. Low frame-time variance matters as much as average allocation throughput.

No allocation library is currently selected, downloaded, integrated or benchmarked. A well-optimized engine does not automatically become fast by swapping malloc; application data layout and avoiding hot-path allocations often dominate results.

## 2. Memory taxonomy and ownership

| Domain | Lifetime | Candidate strategy | Rules and examples |
|---|---|---|---|
| **Bootstrap** | Engine initialization | System allocation + fixed bootstrap arena | Minimal independent allocation to avoid allocator initialization cycle |
| **General** | Variable | std::pmr resource over system/mimalloc/rpmalloc candidate | Safe default; ownership and release interface explicit |
| **Frame scratch** | One frame/tick phase | Linear/monotonic arena with reset barrier | Avoid per-object frees; reset only after all readers/jobs complete |
| **Job scratch** | Task duration | Thread-local or scoped scratch arena | Job lifetime and cross-thread task migration handled explicitly |
| **Scene persistent** | Scene/prefab session | Region/pools + tracked ownership | Scene unload must release references; no dangling shared asset owners |
| **Asset streaming** | Cache/reimport lifecycle | Pool with backpressure, reserved buffer strategy | Prevent spikes when loading textures, mesh, scripts, music |
| **VFX transient** | Short-lived particle batches | Packed SoA/pool, chunk reuse | Avoid general heap per particle; performance proof under intense ARPG test |
| **Audio real-time** | Callback | Preallocated fixed-capacity buffers | No blocking allocation or logging in real-time audio callback |
| **Network messages** | Tick/batch | Reuse/ring buffers with size limits | Bound buffers against attacker/peer abuse |
| **Plugin/SDK boundary** | Host/plugin lifetime | Explicit allocate/free ABI pairs or host-owned opaque handles | Never free through a different CRT/heap than allocator owner |
| **GPU VRAM** | RHI graph/asset lifecycle | GFX-03 budget abstraction only | GPU allocator implementation is out of CORE-02 |

### Typed logical interfaces (not code)
- `MemoryDomainId { persistent, frame, job, streaming, vfx, audio_rt, network, editor, plugin, ... }`.
- `AllocationRequest { bytes, alignment, domain, actor, lifetime_hint, failure_policy }`.
- `AllocationResult { handle_or_ptr, usable_size?, owner_allocator, diagnostic_token }` (the final native API will differ).
- `MemoryBudget { soft_limit, hard_limit, current, peak, committed, resident, policy, asset_reclaim_hooks }`.
- `MemorySnapshot { build_sha, timestamp, domain, reserved, committed, resident, live_bytes, allocation_rate, peak, fragmentation_estimate, sampling_config }`.

**Ownership contract:** every allocation has exactly one releaser and valid lifetime; avoid leaking allocator implementation into external public SDK ABI. Mapped files, aligned allocations, resources crossing C/C++ boundaries and third-party allocators require explicit ownership metadata. Engine API may expose stable handles rather than raw pointer when projects/plugins can outlive the allocation.

**Alignment:** define one normative alignment rule and validate vector/SIMD/graphics upload alignment per platform. Avoid assuming allocator default 16-byte alignment suffices for all future GPU/CPU structures.

## 3. Candidate allocation stack

### C++20 standard facilities
- `std::pmr::memory_resource` supplies a runtime polymorphic allocation interface for opted-in containers, with `monotonic_buffer_resource` and synchronized/unsynchronized pool resources.
- Prefer explicit resource injection and bounded lifetime, not changing the process-global default by accident.
- Danger: `std::pmr` does not make existing game objects automatically safe, and resource lifetime mismatches can cause use-after-free.

### General-purpose allocator candidates
- **Baseline:** system `malloc/free` and C++ `new/delete` on each OS. No third-party dependency and provides a necessary control case.
- **mimalloc 3.x (MIT):** primary candidate for a fast, robust general allocator with heap features and security variants. As of 2026-11-14, upstream lists v3.6.1 (Oct 30, 2026) as recommended. Use the exact pinned release and its license/security advisories at implementation; published upstream numbers are **not** Stormline benchmark results.
- **rpmalloc (Unlicense OR MIT):** alternative designed around per-thread heaps and cross-thread deferred free. Evaluate wakeup/lifetime memory reuse and Windows memory reservation consequences.
- **jemalloc or other allocators:** comparison candidates if evidence demonstrates they meet scope better; do not introduce an entire third-party ecosystem without need.
- **No unverified universal winner:** the workload can change recommendations dramatically. Keep pluggable backend in test harness and a very small production abstraction only after measurement.

### Profiling and sanitizers
- **Tracy profiler (BSD-3-Clause)** as candidate for allocation tracing, CPU zones and frame-time correlation; measure capture overhead.
- AddressSanitizer/UBSan/ThreadSanitizer (where toolchain supports) to detect UAF, overflow, races and undefined behavior; coverage and cross-platform restrictions documented.
- Native tools (e.g., Windows memory diagnostics, Linux perf/heaptrack, macOS Instruments) as applicable, with source/binary distribution rights checked.
- In profiling modes, include allocation call-site sampling; in shipping builds, telemetry is opt-in, bounded and privacy-preserving.

Official references:
- https://en.cppreference.com/cpp/header/memory_resource
- https://github.com/microsoft/mimalloc
- https://github.com/microsoft/mimalloc/blob/main3/LICENSE
- https://github.com/mjansson/rpmalloc
- https://github.com/wolfpld/tracy
- https://github.com/wolfpld/tracy/blob/master/LICENSE

## 4. Proposed in-house innovation: Stormline Memory Fabric (SMF)

**SMF is a research hypothesis**, not proof of unprecedented technology. It would combine:
1. **Budget Graph:** hierarchical domain budgets tagged by subsystem, scene, job and asset ownership. Soft/hard watermarks and confidence-aware memory pressure.
2. **Frame Allocation Policy:** detect known hot paths and propose preallocation, arenas, object pooling and SoA layout, not magic runtime allocation switching.
3. **Adaptive Reclaim Coordinator:** under pressure, ask assets/streaming caches to reduce *optional* residency before risking critical gameplay state; explicit priority and bounded cancellation.
4. **Temporal Allocation Journal:** optional sampling of alloc/free events alongside frame/tick IDs to correlate p95/p99 spikes and infer leak/fragmentation suspects.
5. **Deterministic Budget Tests:** import/reimport cycles, dense VFX scene, low-RAM profile and memory pressure replay from recorded demands.
6. **Cross-platform Capability Hooks:** take memory-pressure signals from CORE-01 where the OS supplies them; no full process memory scanner by default.
7. **AI-visible Diagnostics:** provide read-only, scoped memory summaries via CLI/MCP capabilities (AI-09) without leaking pointer addresses, system paths or process secrets.

### Keep/reject rule
SMF must **demonstrate** reduced frame stalls/peak RSS or materially improved deterministic OOM recovery at equal visual quality and workload, without unacceptable CPU overhead or complexity. Otherwise revert to a simpler `std::pmr` plus proven general allocator and targeted pools.

## 5. Failure semantics and recovery

- **Soft pressure:** emit bounded pressure event and ask optional caches to shrink; don't deallocate a resource still used by GPU or jobs.
- **Hard budget exceeded:** return typed failure without corrupting scene state. Transactional asset imports must roll back or leave previous valid asset intact.
- **True OS OOM:** allocate no new reporting buffers; use bounded error path, preallocated emergency record if justified and clean termination when recovery impossible.
- **Headless server:** memory budgets isolated from GPU/editor and no graphics runtime required; reserve for network protocol validation and connections.
- **Real-time callback:** if required buffer unavailable, return silence/degraded audio safely rather than allocating inside the real-time thread.
- **Streaming:** cancellation must remove partial caches, release reservations and preserve metadata integrity.
- **Memory fragmentation:** track both allocated live and committed/resident memory; never report low live bytes as proof of low RSS.
- **Plugin boundaries:** no freeing memory on different heap/CRT, no memory_resource pointer exported across incompatible ABI without a specified contract.

## 6. Cross-platform requirements

| Platform | Minimum research paths | Tests and unknowns |
|---|---|---|
| Windows x64 | VirtualAlloc-backed heap behavior, MSVC ABI, memory pressure and working set | CRT ownership, reserved/committed memory, allocator override safety, Windows minimum version |
| Linux x64 | mmap, glibc/alternative libc, page reclaim and multithreading | OOM killer behavior, cgroup limits, glibc compatibility, transparent huge pages optional |
| macOS Apple Silicon | VM/malloc zones, Apple Clang, arm64 page size/ABI, unified memory pressure | Native test, system memory pressure events, allocator interaction with Objective-C/Swift runtimes |
| macOS Intel | Compatibility research as NLE-D017 pending platform ADR | ABI and unsupported/old OS lifetime, deprecation risk |
| Web | Distinct memory/WASM limitations in PLAT-03 | No claim that native global allocator replacement maps to browser target |

No mandatory paid tool or Apple Developer enrollment for research. Heavy GPU VRAM accounting belongs to GFX-03; share budget interfaces without pretending RAM and VRAM are interchangeable (notably unified memory systems).

## 7. Test and benchmark plan (future executable WO)

For each platform and every candidate:
- **Microbenchmark** allocation size distributions (16 B to multi-MiB), 1-64 threads as supported, temporal allocation spikes, producer-consumer cross-thread frees, aligned allocations, fragmentation and reset.
- **Representative workloads**: 2D tilemap load, high-VFX ARPG scene, 3D terrain stream, editor reimport of 10k small files, server multiplayer state, audio callbacks.
- **Metrics**: allocation count per frame, total alloc/free CPU time, tail latency p50/p95/p99, working set/RSS, reserved vs committed, peak memory, retained cache, cache hit rate, major/minor page faults, fragmentation and frame-time stutter.
- **Memory tiers**: low RAM, memory pressure injected (where safe), frequent unload/reload and zero-extra-alloc hot-path acceptance. Define actual hardware, drivers, scene revisions and thresholds in future test ADRs.
- **Fuzz/security**: incorrect sizes/alignment, double/free/mismatched API, UAF with sanitizers, hard budget, cancellation and race conditions.
- **A/B**: system allocator vs mimalloc vs rpmalloc vs selected pools/SMF at same workload. Compare equal measured visual and gameplay quality. Check overhead when tracing disabled.
- **Reproducibility**: build SHA, allocator version/flags, compiler, OS, CPU/RAM, benchmark scene, random seed, thermal state and result artifacts.

No numerical improvements are claimed here; only a plan.

## 8. Interfaces and dependencies

- CORE-01 gives OS memory/capability signals and native page allocation bridge where needed.
- CORE-03 Jobs owns scheduling and thread-pool lifetime; CORE-02 provides thread-local scoped allocations with explicit task lifetime, no task scheduler.
- CORE-04 governs frame and tick boundaries, so scratch arena reset must wait for safe epoch/fence from readers, jobs and GPU (where relevant).
- CORE-06 owns telemetry infrastructure. CORE-02 emits trace/counters, but doesn't build its own profiler GUI.
- DATA-05/ WORLD-03 manage asset residency and streaming decisions; CORE-02 only reports pressure and budget.
- GFX-03 owns VRAM/resource allocators and GPU fences, not CORE-02.
- AUD-01 forbids dynamic allocations on real-time callbacks unless a safely documented exception.

## 9. Security, licensing, adoption controls

- Vendoring exact source requires license and provenance audit (mimalloc MIT, rpmalloc Unlicense/MIT, Tracy BSD-3-Clause candidates), version pinning and vulnerability checks.
- Avoid process-global allocator override in early versions; first prototype should use explicitly allocated test arenas and comparators to avoid OS/runtime interference.
- Default to memory safety checks and failure-injection test suite; allocator performance is not a security guarantee.
- High/critical memory corruption, leak affecting state/data integrity, or unbounded OOM is blocker for later implementation.
- Only approved software WOs may add dependencies and compile code. This Work Order is research only.

## 10. Acceptance status

| Acceptance obligation | Current status |
|---|---|
| Memory lifetimes, domains and owners described | DOCUMENTED |
| Cross-platform and headless requirements | DOCUMENTED |
| Comparators, tools, licenses and alternatives | PROPOSED |
| Proprietary SMF proof plan | PROPOSED / NOT VALIDATED |
| Microbenchmark and real-world A/B | NOT EXECUTED |
| Software integrated into engine | NOT STARTED |
| Final implementation technology | ADR PROPOSED only |
