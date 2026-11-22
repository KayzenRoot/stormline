# NLE-PRPLAN-CORE-04-03 — G6 ClockSource activation

**Status:** `G6 IMPLEMENTATION PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `67bbdfdcded5c2172c3773794fd45a85759082a8`. **Formal packet:** `NLE-PRPLAN-CORE-04-03`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md). **Contract:** [core-04-timeline-v0](../contracts/core-04-timeline-v0.md). **WO:** [NLE-PRPLAN-CORE-04-03](../work-orders/NLE-PRPLAN-CORE-04-03.md).

## Authorization

The owner instructed continuation on 2026-11-21. CORE-04-01/02 are approved; this gate activates only `CORE-04-03` after Docs Validation and pt-BR audit. It does not activate `CORE-04-04`, implement Timeline, select a timing SDK, approve release/ABI or declare CORE-01 complete.

## CORE-01 capability admission

Same bounded set as CORE-04-01/02: `-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests, `-13` capability graph; `module_completion_claimed=false`.

## Bounded technical slice

- `time_types.hpp` with shared typed enums/structs.
- `ClockSource`/`SteadyClockSource` over `std::chrono::steady_clock`; checked monotonic elapsed nanoseconds.
- CLK-01..CLK-06 tests; additive CMake/workflow; evidence.
- No Timeline, SDL/native adapter, dependency, public ABI or release.

## Gate state after merge

- Manifest root `CORE04_03_READY_L1_CAPABILITY_OVERLAY`: **709 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 30 `COMPLETED`, 8 approved gates**.
- `CORE-04-03` becomes `EXECUTOR_READY`; `CORE-04-04`..`-10` remain `PLANNED_BLOCKED`.
- Selector allows only `NLE-PRPLAN-CORE-04-03`; every other ID exits 2; registry byte-identical.

## Proof obligations

CLK-01..06; Linux/ASan/TSan/Windows/macOS; exact-head CI; no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
