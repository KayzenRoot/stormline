# NLE-PRPLAN-CORE-04-03 — Monotonic ClockSource evidence

**Status:** `IMPLEMENTATION / EXACT-HEAD CI PENDING`. **Base main:** `90c6377`. **Formal packet:** `NLE-PRPLAN-CORE-04-03`. **Risk:** `ELEVATED`. **Release class:** `INTERNAL_ONLY`. **Contract:** [core-04-timeline-v0](../contracts/core-04-timeline-v0.md). **WO:** [NLE-PRPLAN-CORE-04-03](../work-orders/NLE-PRPLAN-CORE-04-03.md).

## Scope

Exact allowlist implemented:

1. `src/stormline/core/time/time_types.hpp`
2. `src/stormline/core/time/clock_source.hpp`
3. `src/stormline/core/time/clock_source.cpp`
4. `tests/core/clock_source_tests.cpp`
5. `CMakeLists.txt` (additive CORE-04 target/tests)
6. `.github/workflows/core01-internal-headless.yml` (CORE-04 paths and TSan target)
7. `docs/evidence/NLE-PRPLAN-CORE-04-03.md`

No Timeline, SDL/QPC adapter, third-party timing library, dependency, public ABI or release.

## CLK matrix

| ID | Result | Evidence |
|---|---|---|
| CLK-01 basic monotonic | PASS | two `SteadyClockSource` samples non-negative and non-decreasing |
| CLK-02 fake injection | PASS | `ClockSource` interface accepts a fake sample of exactly 123,456,789 ns |
| CLK-03 typed errors | PASS | `ClockUnavailable`, `NonMonotonicSample`, `DurationOverflow` propagate unchanged |
| CLK-04 overflow/backward | PASS | `SteadyClockSource` checks backward epoch, negative conversion and duration overflow |
| CLK-05 defaults/lifetime | PASS | frozen `TimelineConfig`, `TickPlan`, `TimelineStats`, `ReplayScheduleHeader` defaults; construct/destruct safe |
| CLK-06 cross-platform | PASS | Linux, Linux ASan/UBSan, TSan, Windows MSVC and macOS AppleClang |

## Local evidence

- Windows 11 x64 / MSVC 19.44, Ninja Debug: CORE-04 clock **6/6 PASS**; full CTest **132/132 PASS**.
- WSL Ubuntu 24.04 / GCC 13.3: ASan/UBSan **6/6 PASS**; TSan **6/6 PASS**; no sanitizer report.
- `std::chrono::steady_clock` is used only inside `SteadyClockSource`; no SDL/QPC/platform type escapes.

## Contract fidelity

- `ClockSample` returns elapsed nanoseconds since an opaque process epoch or a typed error.
- Negative/backward samples are rejected; no simulated negative time.
- `time_types.hpp` freezes the shared enums/structs needed by the future Timeline contract.
- No implementation of `Timeline`, pause/step, debt, interpolation or replay is included.

## Security and rollback

No secret, network, filesystem, upload, paid service, dependency or global override. Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.

## Open risks

`SteadyClockSource` is a candidate adapter; real resolution/suspend behavior and native comparators remain future evidence. CORE-01 is not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03 `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; full Q4 `BLOCKED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

- `CORE-04-03` `EXECUTOR_READY` → `COMPLETED` with this code PR number.
- Manifest `CORE04_03_COMPLETED_REST_BLOCKED`: **709 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 31 `COMPLETED`, 8 approved gates**.
- `CORE-04-04` remains `PLANNED_BLOCKED`; selector denies every ID; registry byte-identical.

## Exact-head CI

Pending. This section will be updated only with real run IDs and conclusions after the code PR is opened.
