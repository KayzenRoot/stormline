# ADR-0104 — CORE-02 isolated allocator benchmark harness

**Status:** `OWNER_RATIFIED_Q2_BOUNDED_HARNESS / REPORT_ONLY / NO ALLOCATOR SELECTION / NO PRODUCTION INTEGRATION`. **Subordinate to ADR-0004 (planning direction only) and the owner ratification Q1/Q2/Q3/Q4/Q7 of 2026-11-19.**

**Date:** 2026-11-19 | **WO:** `NLE-CORE02-ALLOC-001` | **Parent:** CORE-02 | **Issue:** #19.

## Context and authority

The owner ratified Q1=A (ADR-0004 planning direction), Q2=B (baseline remains default; isolated harness for mimalloc 3.x and rpmalloc), Q3=A (`REPORT_ONLY`), Q4=B (physical matrix G1-M04/M05), Q7=A (NLE-D009 OPEN). This ADR defines only the controlled harness authorized by Q2.

## Bounded technical decision

- Add an **optional, non-default** benchmark executable `stormline_core02_allocator_bench` behind `STORMLINE_CORE02_ALLOC_BENCH=OFF`.
- Pin third-party sources by commit:
  - mimalloc `v3.7.0` / `1ed67b5156a763441d2ec3c20221a7b3cd866129` (MIT);
  - rpmalloc `2.0.1` / `beef233c176b235587c0145f765e4316e5ca60d1` (MIT).
- Build both with global override disabled (`MI_OVERRIDE=OFF`, `ENABLE_OVERRIDE=0`); the harness calls explicit APIs only.
- Compare baseline (`malloc/free`, `operator new/delete`, `std::pmr::new_delete_resource`, `SystemMemoryResource`) against mimalloc and rpmalloc for fixed sizes, aligned allocations and 1/4-thread workloads.
- The harness validates non-null/aligned allocations and read/write integrity; timing is report-only and never a PASS/FAIL threshold.
- No production code, global override, public API, third-party type in an engine contract, allocator default, release or physical qualification is added.

## Alternatives rejected

- **Global override or process-wide replacement:** rejected by Q2 and ADR-0004.
- **Selecting mimalloc/rpmalloc now:** rejected; no physical matrix, thresholds or license release decision.
- **Benchmark inside the default test suite:** rejected; third-party builds stay opt-in and isolated.
- **Vendoring unverified source:** rejected; commits/licenses/notices are pinned and audited.
- **Using CI timings as physical evidence:** rejected by Q4.

## Proof and consequence

- Harness correctness on all enabled platforms; existing tests unaffected when option is OFF.
- CI report-only runs on Linux, Windows and macOS; no performance PASS or allocator winner.
- Physical Q4 execution requires owner-provided machines and remains `NOT_RUN` until executed.
- ADR-0004 still planning-only; NLE-D009 OPEN; G3 NOT_CLEARED; CORE-02 NOT_QUALIFIED; no CORE-03 impact.

## Rollback

Unmerge/close branch or revert PR; delete the optional target/FetchContent/benchmark. Production behavior and defaults are unchanged because the option is OFF and no engine code calls the third-party allocators.
