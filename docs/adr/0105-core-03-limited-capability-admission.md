# ADR-0105 — CORE-03 limited capability admission (owner-ratified, contract only)

**Status:** `OWNER_RATIFIED_BOUNDED_CAPABILITY_ADMISSION / CONTRACT_ONLY / NO CODE AUTHORIZED`. **Subordinate to ADR-0005 (planning direction only) and ADR-0086. Does not declare CORE-02 module completion, approve implementation, release, G3, license or thresholds.**

**Date:** 2026-11-21 | **WO:** `NLE-PRPLAN-CORE-03-02` (future contract) | **Parent:** CORE-03 | **Issue:** #20.

## Context

CORE-02 completed its internal packet sequence (`-03`..`-10`) but remains `NOT_QUALIFIED` as a module. CORE-03-01 governance is `APPROVED_GOVERNANCE` only. The owner ratified A+B+C+D2 on 2026-11-21: ADR-0005 planning direction, risk/release proposals, benchmark-only candidate program, and a limited capability admission based on completed CORE-02-03..09.

## Decision

- **A:** ADR-0005 is ratified only as planning direction for the CORE-03 contract and candidate benchmark. No scheduler technology, API, dependency, release or code is selected.
- **B:** documentary artifacts are `LOW`; future concurrency implementation is proposed `ELEVATED`; first internal slices are proposed `INTERNAL_ONLY`. No public release.
- **C:** benchmark baseline C++20 `std::jthread`/fixed pool + Taskflow 4.x + enkiTS; oneTBB conditional; SFAS research not started. No candidate enters default/public API/product without benchmark, licenses/advisories and separate ratification.
- **D2:** limited capability admission for the first internal CORE-03 slice uses completed `CORE-02-03..09` capabilities; CORE-02 module completion is **not** claimed and the formal dependency remains recorded. This admission authorizes only preparing the `CORE-03-02` contract, not code.

## Required before code

1. `CORE-03-02` contract audited with exact API/error model/files/tests.
2. `CORE-03-03` individual G6 activation and explicit owner authorization.
3. Benchmark/technology evidence per C; TSan/race/deadlock/cancellation/overload plan.
4. No HIGH/CRITICAL known; CORE-02 status remains truthful.
5. No allocator/default/release/ABI/license change.

## Consequence

- CORE-03-01 stays governance-only; `CORE-03-02` may be prepared as the next documentary contract packet; `-03`..`-10` remain `PLANNED_BLOCKED`.
- CORE-02 remains `NOT_QUALIFIED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`.
- This ADR does not make any packet `EXECUTOR_READY` by itself.
