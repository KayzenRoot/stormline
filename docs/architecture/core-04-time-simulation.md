# CORE-04 — Time & Simulation Clock Architecture v0.1

**Work Order:** NLE-P00-WO-002-CORE-04 | **Issue:** #99 | **Status:** RESEARCH PROPOSED / NOT IMPLEMENTED | **Risk:** LOW (docs); ELEVATED for future runtime integration.

## Mission and boundaries
CORE-04 is the authoritative source of **simulation tick scheduling**, not the operating-system wall-clock and not the graphics refresh cycle. Target: original 2D/2.5D/3D/web-capable Stormline with native Windows/Linux/macOS runtime, standalone headless server, editor and replay test harness. A constant simulation step must be isolated from variable presentation frames.

Ownership:
- **CORE-01**: OS lifecycle, monotonic time acquisition, suspend/resume signals and platform adaptation.
- **CORE-04**: measured elapsed time, tick timeline, pause/single-step, time scaling, overrun/debt policy, interpolation phase and diagnostic counters.
- **CORE-03**: jobs, worker scheduling and deterministic logical commit barriers; it consumes tick IDs but does not create or alter them.
- **CORE-06**: observability, trace/event counters. No implicit telemetry allocation on realtime audio paths.
- **SIM-01/SIM-02**: physics solver substeps and numerical determinism (outside CORE-04).
- **NET-02/03/04**: authority, netcode clocks, network rollback (outside CORE-04).
- **GFX-07**: presentation and temporal visual reconstruction; consumes interpolation alpha but cannot advance sim time.
- **GAME/EDIT/AI**: request validated pause/single-step only through authorized public commands, never direct mutable clock internals.

## Proposed implementation-independent typed contracts
| Contract | Public responsibility | Required error behavior |
|---|---|---|
| ClockSource | sample monotonic elapsed duration since an opaque process epoch; permit fake clock injection | negative/backward jump, unavailable source and overflow reported, not treated as simulated negative time |
| ClockSample | signed/checked integer duration with explicit unit; no UTC/system timezone value | reject non-monotonic and nonsensical conversions |
| TimelineConfig | rational tick frequency (numerator/denominator), max steps/pump, time-scale ratio, debt policy, version | reject zero/negative periods, invalid ratios, overflow-prone bounds |
| TickId | unsigned 64-bit, monotonically increasing logical simulation tick per timeline epoch | reject counter rollover, no ID reuse within an epoch |
| TickPlan | zero or more ordered TickId updates, fixed dt as rational, simulation epoch, interpolation alpha | immutable output; never carry OS-thread ids or native pointers |
| TimelineControl | pause, resume, one-step, explicit reset/rebase with permission | invalid transition has typed result, no silent clock skip |
| TimeDebtEvent | observed elapsed, admitted elapsed, deferred/dropped duration, policy, reason | every deliberate drop or clamp recorded; no unbounded event growth |
| ReplayScheduleHeader | schema version, timestep rational, initial tick, seed/source ID mapping contract, build/physics compatibility fingerprint | reject mismatch rather than assert cross-machine deterministic replay |

Interface boundaries are **conceptual** and names are not an approved C++ ABI. No external library types escape public engine APIs.

## Monotonic time and precision
Prefer C++20 std::chrono::steady_clock as an implementation candidate; inject a test double. Treat SDL3 SDL_GetTicksNS/SDL_GetPerformanceCounter and native Win32 QPC as comparator/diagnostic fallback only after benchmark and platform research. Do **not** use system_clock, NTP, timezone, UTC or presentation timestamps as a simulation timebase. Source sampling must check negative deltas and overflow, use explicit integer conversions and keep an elapsed-remainder when conversion loses precision. A wall clock may move independently of the logical tick counter.

Use checked integer/rational representation for the fixed step: exact rational period (e.g. 1/60 seconds) cannot be represented by a single integral nanosecond value, so repeatedly adding 16,666,666 ns creates drift. Preferred design carries a remainder or a scaled integer accumulator; never accumulate float dt indefinitely. Avoid nonportable 128-bit arithmetic assumptions on MSVC; plan a proved overflow-safe implementation.

## Pump algorithm (proposed semantics)
1. Sample ClockSource (or receive explicit injected elapsed duration in tests). Reject source anomalies through a typed outcome.
2. Compute admitted elapsed via selected time scaling with rational remainder. If paused, **do not** accumulate background elapsed; a single-step command produces exactly one fixed tick and leaves pause active.
3. Increment integer accumulator; generate no more than the configured max ticks per pump. Every generated update has the same rational simulation delta and strictly increasing TickId.
4. Record any unsimulated remainder as explicit time debt. For offline mode, allow a configurable bounded debt policy; if time is discarded, emit a specific event with amount and reason. For authoritative headless server mode, **never silently drop authoritative ticks**: surface overload and escalate to server cadence/resync policies.
5. Emit bounded interpolation alpha in [0, 1), derived only from remaining admitted fraction (not from wall-clock UTC). Presentation interpolates snapshots without mutating the authoritative state.
6. Commit simulation jobs from CORE-03 in a defined logical order before publishing the next state. Dependency edges stay one way; CORE-04 must not block on arbitrary graphics/audio APIs.

**Default candidate for test fixtures:** 60 ticks/s; 4 catch-up ticks per presentation pump in offline mode, 250 ms candidate stall reporting threshold. These are **not approved performance promises**, not universal production defaults and must be stress-tested on real low-end and macOS hardware. 30/120 Hz and explicit headless policies remain configurable candidates.

## Determinism contract (strictly bounded)
CORE-04 can guarantee the **sequence of logical tick IDs and fixed rational dt for the same admitted elapsed/input schedule and configuration**, regardless of render FPS. It CANNOT by itself guarantee bit-exact 2D/3D physics, multi-thread numerical results, random streams, compiler floating point or network replay across Windows/Linux/macOS. Full replay needs versioned stable input ordering, deterministic/random seed domains, snapshot/state hashing, side-effect boundaries and physics/network policies decided by downstream modules.

Replay event order candidate: TickId -> producer/source stable ID -> within-source sequence. Same authored input stream with different presentation frame partitions must produce the same committed tick sequence when admission/debt decisions match. A frame with forced wall-delta clamp is NOT equivalent to identical raw wall elapsed without the clamp: log clamp events in replay metadata.

## Lifecycle and error model
States: UNINITIALIZED -> RUNNING <-> PAUSED -> STOPPED, with explicit SINGLE_STEP while paused and ERROR where a clock/source invariant fails. Sleep/resume behavior is explicit (rebase after suspend or carry bounded debt per mode). Typed error candidates: CLOCK_UNAVAILABLE, NON_MONOTONIC_SAMPLE, DURATION_OVERFLOW, INVALID_STEP_RATIO, INVALID_TIME_SCALE, TICK_OVERFLOW, INVALID_TRANSITION, DEBT_LIMIT_EXCEEDED, REPLAY_INCOMPATIBLE. No exceptions across C ABI; no busy spin or unbounded catch-up.

## Acceptance tests to implement later (NOT RUN)
- FakeClock injected patterns: simulated 60 seconds partitioned as 30/60/144 FPS produce exactly **3,600 60-Hz ticks** if no debt is dropped; presentation alpha stays [0,1).
- Long-run rational arithmetic: 24 h of 60-Hz logical time yields exactly **5,184,000 ticks** in a fast-forward harness; no 16,666,666-ns drift. All calculations must be checked for overflow.
- Freeze/unfreeze: paused time advances zero ticks; step once increments exactly one; no burst on resume.
- Delta anomaly: backward clock, duplicate timestamp, near-overflow counter, suspend 10 minutes, max catch-up and rejected config produce typed outcomes with no hidden tick loss.
- Deterministic scheduling: identical admitted elapsed and ordered injected inputs => identical tick IDs/state-hash envelope across same binary; cross-platform hash parity is an **additional** downstream integration gate, not implied.
- Server overload: no silently discarded authoritative ticks; report debt and explicit policy. Compare CPU p50/p95/p99 cost and max resident memory under fake clock 2/4/8-core stress when implementation exists.
- Compiler/OS matrix: MSVC x64 Win, GCC/Clang x64 Linux, Apple Clang arm64 macOS; Intel support feasibility explicit; headless build and sandboxed Web timing evaluated separately.

## Architecture gates
Approved ADR/contract, dependency implementations, resource budgets, error handling, compiler matrix, licensing/security review and tests must exist before converting implementation issue #21 out of BLOCKED. Research provides no engine code, benchmark or compilation evidence.

## References
- https://en.cppreference.com/w/cpp/chrono/steady_clock
- https://learn.microsoft.com/en-us/windows/win32/sysinfo/acquiring-high-resolution-time-stamps
- https://wiki.libsdl.org/SDL3/SDL_GetTicksNS
- https://www.gafferongames.com/post/fix_your_timestep/
- https://docs.unity.com/en-us/engine/6000.3/manual/scripting/managing-time-and-frame-rate/fixed-updates
- https://box2d.org/documentation/md_simulation.html
