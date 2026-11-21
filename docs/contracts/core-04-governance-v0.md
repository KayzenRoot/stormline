# CORE-04 INTERNAL_ONLY Governance Contract v0 (NLE-PRPLAN-CORE-04-01)

**Status:** `GOVERNANCE PROPOSAL / NO CODE AUTHORIZED`. **Base:** `6747eb9fd6949c177e293ed2d754661929f16451`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md), [ADR-0006](../adr/0006-core-04-time-policy.md) planning-only. **WO:** [NLE-PRPLAN-CORE-04-01](../work-orders/NLE-PRPLAN-CORE-04-01.md).

## Objective

Define the bounded governance envelope for CORE-04 (`Time & Simulation Clock`): ownership, risk/release, permitted planning direction, capability admission and gates before any contract or code.

## Ownership boundaries

- CORE-01 owns OS lifecycle, monotonic time acquisition, suspend/resume signals and platform adaptation.
- CORE-04 owns measured elapsed time, tick timeline, pause/step, time scaling, overrun/debt policy, interpolation phase and diagnostics.
- CORE-03 consumes tick IDs for job ordering but does not create or alter them.
- CORE-06 owns observability; SIM-01/02 physics/numerical determinism; GFX-07 presentation; NET-02/03/04 network clocks/rollback; AUD-01 real-time audio.

## Bounded planning direction

- Injectable `ClockSource` based on C++20 `std::chrono::steady_clock`; fake clock for tests.
- Integer/rational fixed step with carried remainder; no float-only accumulated simulation time and no new third-party timing SDK.
- Typed lifecycle: Uninitialized -> Running <-> Paused -> Stopped, with single-step and typed source/overflow/transition errors.
- Determinism envelope limited to logical `TickId` sequence and rational `dt` for the same admitted elapsed/input schedule and configuration.
- Explicit debt/clamp policy; offline may drop with events; authoritative headless must not silently discard ticks.
- Initial fixtures 60 Hz, 4 catch-up ticks offline, 250 ms stall diagnostic; not production promises.

## Capability admission

Formal dependency `CORE-01` remains. Admission is limited to completed CORE-01 capabilities:

| Capability | Completed packet |
|---|---|
| `CORE01_HEADLESS_BUILD_AND_TEST` | `NLE-PRPLAN-CORE-01-03` |
| `CORE01_PORTABLE_PATHS` | `NLE-PRPLAN-CORE-01-06` |
| `CORE01_SDL3_BUILD_BASELINE` | `NLE-PRPLAN-CORE-01-07` |
| `CORE01_NATIVE_CI_MATRIX` | `NLE-PRPLAN-CORE-01-08` |
| `CORE01_LIFECYCLE_REQUESTS` | `NLE-PRPLAN-CORE-01-12` |
| `CORE01_CAPABILITY_GRAPH` | `NLE-PRPLAN-CORE-01-13` |

`module_completion_claimed=false`. Window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release are not used.

## Gates before code

1. `CORE-04-02` contract with exact logical API, error model, rational arithmetic, files and tests.
2. Individual `CORE-04-03` G6 activation and explicit owner authorization.
3. Fake-clock 30/60/144 FPS, 24 h rational, pause/step/suspend/backward-time, overflow and debt tests.
4. MSVC/GCC/Clang/AppleClang CI; TSan/ASan/UBSan as applicable; no HIGH/CRITICAL.
5. No allocator, third-party timing SDK, public ABI, release or license change.

## Stop / rollback / security

Stop on stale source, missing admission, technology/dependency change, public ABI/release claim, floating accumulation, unbounded catch-up, silent tick loss, HIGH/CRITICAL. Unmerged: close the branch; after merge: normal revert PR, never force push.

No implementation packet becomes `EXECUTOR_READY` by this contract. `CORE-04-02`..`-10` remain `PLANNED_BLOCKED`.
