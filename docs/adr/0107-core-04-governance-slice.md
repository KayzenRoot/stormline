# ADR-0107 — CORE-04 governance and bounded planning direction

**Status:** `OWNER-RATIFIED_BOUNDED_PLANNING_ONLY / NO CODE AUTHORIZED`. **Subordinate to ADR-0006 (ratified only as planning direction) and ADR-0086 (capability admission). Does not declare CORE-01 complete, approve implementation, public ABI, release, G3 or license.**

**Date:** 2026-11-21 | **WO:** `NLE-PRPLAN-CORE-04-01` | **Parent:** CORE-04 | **Issue:** #21.

## Context

CORE-03 closed its internal sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. CORE-04 (`Time & Simulation Clock`) has research, an architecture document and ADR-0006 `PROPOSED`; no executable code exists. Its formal dependency `CORE-01` is not a qualified module, but several CORE-01 capabilities are completed and merged. The owner instructed continuation on 2026-11-21 after the CORE-03 closeout.

## Decision

- **A:** ADR-0006 is ratified only as planning direction for CORE-04: injectable monotonic `ClockSource`, integer/rational fixed step with carried remainder, no float-only accumulated simulation time, no new third-party timing SDK.
- **B:** documentary artifacts are `LOW`; future runtime implementation is `ELEVATED`; first internal slices are `INTERNAL_ONLY`. No public release.
- **C:** capability admission for CORE-04 preparation uses completed CORE-01 capabilities; CORE-01 module completion is **not** claimed and its formal dependency remains recorded.
- **D:** the determinism envelope is limited to logical `TickId` sequence and rational fixed `dt` for the same admitted elapsed/input schedule and configuration. Bit-exact physics, multi-thread numerical results, compiler floating point and cross-platform/network replay are **not** guaranteed by CORE-04.
- **E:** initial test fixtures are 60 Hz, 4 catch-up ticks per offline pump and a 250 ms stall diagnostic; these are test/diagnostic candidates, not production promises or frozen defaults.
- **F:** CORE-04 must not own OS time acquisition, graphics refresh, audio callbacks, physics substeps or netcode clocks; those remain with CORE-01, GFX-07, AUD-01, SIM-01/02 and NET-02/03/04.

## Required before code

1. `CORE-04-02` contract audited with exact logical API, error model, rational arithmetic, files and tests.
2. Individual `CORE-04-03` G6 activation and explicit owner authorization.
3. Fake-clock tests for 30/60/144 FPS partitions, 24 h rational arithmetic, pause/step/suspend/backward-time, overflow and debt policies.
4. MSVC/GCC/Clang/AppleClang CI; no HIGH/CRITICAL.
5. CORE-01/CORE-02/CORE-03 statuses remain truthful; no allocator/technology/public ABI/release change.

## Consequence

- `CORE-04-01` may be prepared as `APPROVED_GOVERNANCE`; `CORE-04-02`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 remains not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03 `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
- G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; engine not released.
- This ADR does not make any implementation packet `EXECUTOR_READY` by itself.
