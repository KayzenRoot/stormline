# ADR-0097 — CORE-02 monotonic arena slice

**Status:** `OWNER_DIRECTION_CAPABILITY_BASED_L1 / TECHNICAL_SLICE_PROPOSED / CONDITIONAL_ON_AUDIT_AND_MERGE`. **Subordinate to ADR-0004, which remains `PROPOSED`; does not approve an allocator selection, release class or G3 globally.**

**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-02-05` | **Parent:** `NLE-PRPLAN-CORE-02-01` | **Issue:** #19.

## Context and authority

CORE-02-03 delivered ownership and CORE-02-04 the system allocator baseline. The next planned packet `-05` is arenas. ADR-0004 proposes bounded linear/monotonic scratch arenas with lifetime fences; CORE-04 owns frame/tick boundaries, so this slice is the arena primitive only: one backing block, bump allocation, explicit reset and high-water accounting.

## Capability admission

Formal dependency `CORE-01` remains. Admitted only via completed `CORE-01-03/-06/-07/-08` capabilities, with `module_completion_claimed=false`; no window/input/DPI/IME/hotplug/soak capability used. Admission expires at packet closeout.

## Bounded technical decision

- New internal `ArenaError`, `ArenaSlice`, `MonotonicArena`:
  - one `MemoryBlock` backing allocation from an explicit `std::pmr::memory_resource*` (null → system baseline);
  - configurable capacity and backing alignment (default 64), requested slice alignment must not exceed it;
  - bump allocation with alignment padding, no per-slice free;
  - `reset()` rewinds to offset 0, preserves the high-water mark;
  - owner-thread allocate/reset; typed errors; no exceptions across the API;
  - queries: capacity, used, remaining, high-water, valid.
- No pools, budgets, leak tracking, telemetry, frame/job reset barriers, global override, third-party dependency or public ABI.
- Integration tests use `MemoryBlock`, a counting PMR resource and cross-platform CTest.

## Alternatives rejected

- **General-purpose allocator in the arena:** rejected; arenas are monotonic scratch storage, not malloc replacement.
- **Per-slice free:** rejected; it would turn the arena into a general heap and add fragmentation/ownership complexity.
- **Global/static arena:** rejected; explicit instance/lifetime only.
- **Unbounded arena:** rejected; fixed capacity and typed overflow are the contract.
- **Frame/job barrier ownership:** rejected; CORE-04 owns tick boundaries; this slice only exposes reset.

## Proof and consequence

- G4/G5 bounded eligibility after gate Docs Validation, pt-BR audit and merge; G6 activation separate.
- Code proof: ARN-01..ARN-06, alignment, overflow/reset, high-water, wrong-thread, 1000 cycles, counting resource, existing 73 CTests regression, Linux ASan/UBSan.
- Frame/job integration, thread-local/scratch lifecycle, budgets, leak tracking and telemetry remain `NOT_QUALIFIED`.
- ADR-0004 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false`.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the arena target/tests/evidence restores the previous state; no G2, registry or license change.
