# ADR-0101 — CORE-02 integrated memory qualification slice

**Status:** `OWNER_DIRECTION_CAPABILITY_BASED_L1 / TECHNICAL_SLICE_PROPOSED / CONDITIONAL_ON_AUDIT_AND_MERGE`. **Subordinate to ADR-0004, which remains `PROPOSED`; does not approve thresholds, release, G3 globally or a public memory guarantee.**

**Date:** 2026-11-19 | **WO:** `NLE-PRPLAN-CORE-02-09` | **Parent:** `NLE-PRPLAN-CORE-02-01` | **Issue:** #19.

## Context and authority

CORE-02-03..08 delivered ownership, system allocator baseline, monotonic arena, soft/hard budget, explicit leak tokens and opt-in telemetry. The planned packet `-09` is integrated qualification of the approved internal scope. The owner authorized CORE-02-08/-09/-10 sequentially, each behind its individual gate.

This slice is **test-only**. It exercises the existing primitives together under deterministic load, stress, overflow/recovery and size churn, with report-only timing. It does not add production APIs, thresholds, allocator selection, global interception, export or release qualification.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, `module_completion_claimed=false`; no window/input/DPI/IME/hotplug/soak product capability used.

## Bounded technical decision

- New test executable `core02_memory_qualification_tests.cpp` with modes:
  - QLF-01 integrated deterministic workload over `SystemMemoryResource`, `MemoryBlock`, `MonotonicArena`, `MemoryBudget`, `LeakTracker` and `MemoryTelemetry`;
  - QLF-02 stress: 10,000 mixed iterations with final counter/drain invariants;
  - QLF-03 recovery: arena OOM→reset→reuse, budget hard rejection→release→reuse, leak capacity→release→reuse, telemetry underflow non-mutation;
  - QLF-04 size-churn: varied block sizes/alignments with release patterns; no fragmentation estimator is claimed;
  - QLF-05 report-only benchmark of the integrated loop.
- Assertions use deterministic counters/state, not timing. Timing is printed and never gates CI.
- No threshold for p95, RSS, fragmentation or allocation rate is established; no claim of leak-free beyond observable counters.
- Linux ASan/UBSan retained; existing CTests preserved.

## Alternatives rejected

- **Performance thresholds now:** rejected; no owner-ratified hardware/tier/threshold exists.
- **Fragmentation metric:** rejected for this slice; requires a defined estimator and calibrated methodology.
- **Global allocator interception or OS RSS scanning:** rejected; outside approved scope and security model.
- **New allocator comparison:** rejected; the system baseline is the only approved allocator.
- **Production code changes:** rejected; the slice qualifies existing behavior only.

## Proof and consequence

- G4/G5 bounded eligibility after gate Docs Validation, pt-BR audit and merge; G6 activation separate.
- Code proof: QLF-01..QLF-05, 10,000-iteration stress, recovery paths, size churn, report-only timing, existing 105/104 CTests, Linux ASan/UBSan.
- Physical hardware, OS RSS/VRAM, p95/RSS thresholds, fragmentation metrics, 32 scenarios, release and module completion remain `NOT_QUALIFIED`.
- ADR-0004 `PROPOSED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 WOs `BLOCKED`; `engine_implemented=false`.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the qualification test/CMake/evidence restores the previous state; no production-code, G2, registry or license change.
