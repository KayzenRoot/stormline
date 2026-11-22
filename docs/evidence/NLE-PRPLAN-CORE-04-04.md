# NLE-PRPLAN-CORE-04-04 — Rational fixed-step Timeline evidence

**Status:** `IMPLEMENTATION / EXACT-HEAD CI GREEN / AUDIT PENDING`. **Base main:** `99e59b0`. **Head:** `b9144da96cc1cac67ebec6c615a2edfbf8330ae5`. **Formal packet:** `NLE-PRPLAN-CORE-04-04`. **Risk:** `ELEVATED`. **Release class:** `INTERNAL_ONLY`. **Contract:** [core-04-timeline-v0](../contracts/core-04-timeline-v0.md). **WO:** [NLE-PRPLAN-CORE-04-04](../work-orders/NLE-PRPLAN-CORE-04-04.md).

## Scope

Exact allowlist:

1. `src/stormline/core/time/timeline.hpp`
2. `src/stormline/core/time/timeline.cpp`
3. `tests/core/timeline_tests.cpp`
4. `CMakeLists.txt` (additive CORE-04 target/tests)
5. `.github/workflows/core01-internal-headless.yml` (CORE-04 TSan target/regex)
6. `docs/evidence/NLE-PRPLAN-CORE-04-04.md`

No third-party timing library, SDL/QPC adapter, public ABI or release.

## TICK matrix

| ID | Result | Evidence |
|---|---|---|
| TICK-03 FPS partitions | PASS | 60 s at 30/60/144 FPS → exactly 3,600 60-Hz ticks; alpha in `[0,1)` |
| TICK-04 long rational | PASS | 24 h at 60 Hz → exactly 5,184,000 ticks |
| TICK-05 pause | PASS | paused pump zero ticks and no debt; resume no burst; sampled-clock baseline discarded |
| TICK-06 single-step | PASS | exactly one tick, state remains Paused |
| TICK-07 catch-up/drop | PASS | 250 ms pump capped at 4 ticks; dropped duration recorded |
| TICK-08 debt carry | PASS | bounded debt drains over pumps; exceeding `max_debt_ns` returns `DebtLimitExceeded` |
| TICK-09 time scale | PASS | 2× → 60 ticks/0.5 s; 0.5× → 30 ticks/1 s |
| TICK-10 overflow/config | PASS | `start_at(max-1)` then two single steps → second `TickOverflow`; invalid config/null source/negative delta/`AlreadyInitialized` typed; no wrap |
| TICK-11 lifecycle | PASS | stop idempotent, restart rejected, wrong-thread pump/pause, destructor safe |
| TICK-12 determinism/replay | PASS | same admitted partition yields same 600-tick schedule; `replay_schedule_compatible` accepts exact/unknown fingerprint and rejects schema/rate/initial/fingerprint mismatch |

## Local evidence

- Windows 11 x64 / MSVC 19.44, Ninja Debug: CORE-04 timeline **11/11 PASS**; full CTest **143/143 PASS**.
- WSL Ubuntu 24.04 / GCC 13.3: ASan/UBSan **11/11 PASS**; TSan **11/11 PASS**; no sanitizer report.
- Exact rational arithmetic uses integer numerator/remainder; no floating-point simulation accumulation. `interpolation_alpha` is presentation-only.

## Contract fidelity

- `Timeline` lifecycle, owner-thread rule, pause/resume/step, clamp, DropExcess/Carry and typed errors.
- `pump` uses sampled absolute elapsed with a first-sample baseline; `pump_elapsed` accepts injected deltas for tests/replay.
- `resume` discards the next sampled delta so pause duration cannot burst.
- `start` rejects invalid config/null source; `stop` is idempotent; restart is rejected.
- No CORE-03 dependency, GPU/audio call or public ABI.

## Limitations / residual risk

- `start_at` carries an initial tick for replay/tests; it does not imply cross-machine deterministic physics or network replay.
- `replay_schedule_compatible` treats `build_fingerprint == 0` as unknown; it does not prove numerical determinism.
- Real suspend/resume, platform clock resolution and native comparators remain future evidence.

## Security and rollback

No secret, network, filesystem, upload, paid service, dependency or global override. Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.

## Proposed checkpoint delta

- `CORE-04-04` `EXECUTOR_READY` → `COMPLETED` with this code PR number.
- Manifest `CORE04_04_COMPLETED_REST_BLOCKED`: **708 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 32 `COMPLETED`, 8 approved gates**.
- `CORE-04-05` remains `PLANNED_BLOCKED`; selector denies every ID; registry byte-identical.

## Exact-head CI

Native run [44989284287](https://github.com/KayzenRoot/stormline/actions/runs/44989284287) on head `b9144da96cc1cac67ebec6c615a2edfbf8330ae5`: **SUCCESS**.

- Linux GCC: **141/141** CTest PASS, including 10 CORE-04 timeline tests.
- Linux ASan/UBSan: **141/141** PASS, no sanitizer failure.
- Linux TSan: **31/31** PASS (15 CORE-03 + 6 CORE-04 clock + 10 CORE-04 timeline), no TSan report.
- Windows MSVC: **142/142** PASS, including 10 CORE-04 timeline tests.
- macOS AppleClang: **140/140** PASS, including 10 CORE-04 timeline tests.
- Docs Validation [44989284391](https://github.com/KayzenRoot/stormline/actions/runs/44989284391): SUCCESS.
- SonarCloud and Socket Security: SUCCESS.
- Allocator benchmark matrix: 3/3 PASS (isolated, report-only; no allocator selected).

No native PASS is claimed beyond these exact-head run IDs. TICK-10 `TickOverflow` and TICK-12 `ReplayIncompatible` remain partial as documented above.
