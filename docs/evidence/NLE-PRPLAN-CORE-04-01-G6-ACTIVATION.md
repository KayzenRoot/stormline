# NLE-PRPLAN-CORE-04-01 — G6 governance activation

**Status:** `G6 GOVERNANCE PROPOSAL / NO CODE AUTHORIZED / CORE-01 CAPABILITY ADMISSION`. **Base main:** `6747eb9fd6949c177e293ed2d754661929f16451`. **Formal packet:** `NLE-PRPLAN-CORE-04-01`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md). **Contract:** [core-04-governance-v0](../contracts/core-04-governance-v0.md). **WO:** [NLE-PRPLAN-CORE-04-01](../work-orders/NLE-PRPLAN-CORE-04-01.md).

## Authorization

The owner instructed continuation on 2026-11-21 after the CORE-03 sequence closeout. This gate activates only `CORE-04-01` governance after Docs Validation and pt-BR audit. It does not activate `CORE-04-02`, write clock code, select a timing library, approve release/ABI or declare CORE-01 complete.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- Window runtime, input, DPI, IME, hotplug, sleep/resume soak, renderer, GPU, audio, network, public ABI and release are not required or used.

## Governance scope

- ADR-0006 ratified only as planning direction: injectable monotonic `ClockSource`, integer/rational fixed step with carried remainder, no float-only accumulation, no new third-party timing SDK.
- Risk `LOW` documentary / `ELEVATED` implementation; release `INTERNAL_ONLY`.
- Determinism envelope only `TickId` sequence and rational `dt`; no bit-exact physics/network/cross-platform claim.
- Explicit debt/clamp policy; offline may drop with events; authoritative headless never silently drops ticks.
- Initial fixtures 60 Hz, 4 catch-up ticks offline, 250 ms stall diagnostic; not production promises.

## Gate state after merge

- Manifest root `CORE04_01_APPROVED_GOVERNANCE_ONLY`: **711 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 30 `COMPLETED`, 7 approved gates**.
- `CORE-04-01` becomes `APPROVED_GOVERNANCE`; `CORE-04-02`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, governance review, selector denial, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this governance gate.
