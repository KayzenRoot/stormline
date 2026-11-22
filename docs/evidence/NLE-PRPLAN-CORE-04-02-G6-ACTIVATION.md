# NLE-PRPLAN-CORE-04-02 — G6 contract activation

**Status:** `G6 CONTRACT PROPOSAL / NO CODE AUTHORIZED / CORE-01 CAPABILITY ADMISSION`. **Base main:** `7fb0949`. **Formal packet:** `NLE-PRPLAN-CORE-04-02`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md). **Contract:** [core-04-timeline-v0](../contracts/core-04-timeline-v0.md). **WO:** [NLE-PRPLAN-CORE-04-02](../work-orders/NLE-PRPLAN-CORE-04-02.md).

## Authorization

The owner instructed continuation on 2026-11-21. CORE-04-01 governance is `APPROVED_GOVERNANCE`; this gate prepares only the `CORE-04-02` contract after Docs Validation and pt-BR audit. It does not activate `CORE-04-03`, write clock code, select a timing library, approve release/ABI or declare CORE-01 complete.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Contract scope

- Injectable `ClockSource`/`SteadyClockSource`, rational `TickId`/`Rational`, `TimelineConfig`, `TickPlan`, `TimelineStats`, `ReplayScheduleHeader` and `Timeline`.
- Exact rational fixed step with carried remainder; no float accumulation; no third-party timing type.
- Pause, resume, single-step, interpolation alpha, debt/clamp policy, typed errors and lifecycle.
- TICK-01..TICK-12 oracles and exact `CORE-04-03`/`-04` allowlists.
- No implementation, dependency, public ABI or release.

## Gate state after merge

- Manifest root `CORE04_02_APPROVED_CONTRACT_ONLY`: **710 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 30 `COMPLETED`, 8 approved gates**.
- `CORE-04-02` becomes `APPROVED_CONTRACT`; `CORE-04-03`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, contract review, selector denial, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this contract gate.
