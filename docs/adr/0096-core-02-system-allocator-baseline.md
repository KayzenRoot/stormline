# ADR-0096 — CORE-02 system allocator baseline and comparative harness

**Status:** `OWNER_DIRECTION_CAPABILITY_BASED_L1 / TECHNICAL_SLICE_PROPOSED / CONDITIONAL_ON_AUDIT_AND_MERGE`. **Subordinate to ADR-0004, which remains `PROPOSED`; does not approve an allocator selection, a release class or G3 globally.**

**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-02-04` | **Parent:** `NLE-PRPLAN-CORE-02-01` | **Issue:** #19.

## Context and authority

CORE-02-03 delivered the internal `MemoryBlock` ownership primitive. The next planned packet `-04` is allocators. ADR-0004 proposes a `std::pmr` resource interface with the OS/C++ system allocator as the reproducible baseline, no global override in the first step, and third-party candidates (mimalloc/rpmalloc) only after measured comparison.

This ADR authorizes a **system allocator baseline** and a **report-only** comparative harness. It does not select mimalloc/rpmalloc, does not replace global `new/delete`, does not adopt a performance budget and does not claim a speedup.

## Capability admission

The formal dependency `CORE-01` remains. The packet is admitted only through the completed capabilities already used by CORE-02-03:

- `CORE01_HEADLESS_BUILD_AND_TEST` (`-03`), `CORE01_PORTABLE_PATHS` (`-06`), `CORE01_SDL3_BUILD_BASELINE` (`-07`), `CORE01_NATIVE_CI_MATRIX` (`-08`).

This does **not** claim CORE-01 complete and does not use window/input/DPI/IME/hotplug/soak capabilities. The admission expires at packet closeout.

## Bounded technical decision

- New internal `SystemMemoryResource final : public std::pmr::memory_resource`:
  - uses `::operator new`/`::operator delete` with `std::align_val_t` for over-aligned allocations and ordinary new/delete otherwise;
  - zero-byte requests allocate one byte and deallocate with the same effective size;
  - `do_is_equal` is identity-based; no global state, no counters, no override;
  - can be injected into the existing `MemoryBlock`; a null resource still resolves to `std::pmr::new_delete_resource()`.
- Report-only benchmark/test harness compares `SystemMemoryResource`, `std::pmr::new_delete_resource`, `::operator new/delete` and `malloc/free` over deterministic sizes/alignments; it asserts only correctness, never timing.
- Tests: basic allocation/alignment/read-write, block ownership integration, over-alignment 1..4096, 10,000-cycle lifetime, cross-thread release, report-only benchmark.
- No third-party dependency, no global allocator override, no arena/budget/leak/telemetry, no public ABI.

## Alternatives rejected

- **Adopt mimalloc/rpmalloc now:** rejected; no pinned release/security review/benchmark evidence, and ADR-0004 requires comparison before selection.
- **Replace global `new/delete`:** rejected; unsafe at plugin/CRT boundaries and outside the first step.
- **Benchmark with a performance PASS:** rejected; no approved hardware/threshold and CI is noisy.
- **Use only `new_delete_resource`:** rejected; a separate system resource gives an explicit baseline and tests aligned new/delete semantics without changing global state.
- **Arena/pool first:** rejected; allocator baseline is the next necessary prerequisite.

## Proof and consequence

- G4/G5 bounded eligibility after gate Docs Validation, pt-BR audit and merge; G6 activation separate.
- Code proof: `SYS-01..SYS-06`, Linux/Windows/macOS, Linux ASan/UBSan, report-only benchmark output, existing 67 CTests regression.
- No third-party selection or performance verdict. ADR-0004 remains `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false`.
- Physical/hardware allocator benchmarks, plugin ABI, RSS/fragmentation budgets and release remain `NOT_QUALIFIED`.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the system-resource target/tests/benchmark and evidence restores the previous state; no G2, registry or license change is part of this ADR.
