# CORE-04 INTERNAL_ONLY Timeline Contract v0 (NLE-PRPLAN-CORE-04-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `7fb0949`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md), [ADR-0006](../adr/0006-core-04-time-policy.md) planning-only. **WO:** [NLE-PRPLAN-CORE-04-02](../work-orders/NLE-PRPLAN-CORE-04-02.md).

## Objective

Define the first internal CORE-04 contract: an injectable monotonic clock source and a bounded rational fixed-step timeline with pause, single-step, interpolation phase, debt policy, typed errors and report-only diagnostics. No implementation, dependency, public ABI or release is authorized by this contract.

## Admission and boundaries

- Formal `CORE-01` dependency remains; admission is limited to completed `CORE-01-03/-06/-07/-08/-12/-13` capabilities under ADR-0107/ADR-0086. CORE-01 module completion is **not** claimed.
- CORE-04 owns measured elapsed time, tick timeline, pause/step, time scale, debt policy, interpolation phase and diagnostics.
- CORE-01 owns OS time acquisition; CORE-03 consumes tick IDs but does not create them; CORE-06 owns instrumentation; SIM/GFX/NET/AUD boundaries unchanged.
- No third-party timing library, SDL type or platform API appears in the contract.

## Internal API (logical, exact names)

```cpp
namespace stormline::core::time {

enum class TimeError : std::uint8_t {
    None,
    InvalidConfig,
    InvalidTransition,
    WrongThread,
    NotInitialized,
    AlreadyInitialized,
    ClockUnavailable,
    NonMonotonicSample,
    DurationOverflow,
    TickOverflow,
    DebtLimitExceeded,
    ReplayIncompatible,
    InternalFailure
};

enum class TimelineState : std::uint8_t {
    Uninitialized,
    Running,
    Paused,
    Stopped,
    Failed
};

enum class DebtPolicy : std::uint8_t {
    DropExcess,
    Carry
};

struct TickId { std::uint64_t value{0}; };
struct Rational { std::int64_t numerator{0}; std::int64_t denominator{1}; };

struct ClockSample {
    std::int64_t elapsed_ns{0};
    TimeError error{TimeError::None};
};

class ClockSource {
public:
    virtual ~ClockSource() = default;
    virtual ClockSample sample() noexcept = 0;
};

class SteadyClockSource final : public ClockSource {
public:
    SteadyClockSource() noexcept;
    ClockSample sample() noexcept override;
private:
    // opaque steady epoch and last checked sample
};

struct TimelineConfig {
    std::uint32_t tick_rate_numerator{60};
    std::uint32_t tick_rate_denominator{1};
    std::uint32_t max_catch_up_ticks{4};
    std::uint64_t max_frame_delta_ns{250'000'000};
    std::uint64_t max_debt_ns{1'000'000'000};
    Rational time_scale{1, 1};
    DebtPolicy debt_policy{DebtPolicy::DropExcess};
};

struct TickPlan {
    std::uint32_t tick_count{0};
    TickId first_tick{};
    Rational fixed_step{1, 60};
    double interpolation_alpha{0.0};
    std::uint64_t dropped_ns{0};
    bool clamped{false};
};

struct TimelineStats {
    std::uint64_t pumps{0};
    std::uint64_t ticks_emitted{0};
    std::uint64_t dropped_ns{0};
    std::uint64_t debt_ns{0};
    std::uint64_t clock_errors{0};
    std::uint64_t rejected_pumps{0};
    double last_alpha{0.0};
};

struct ReplayScheduleHeader {
    std::uint32_t schema_version{1};
    std::uint32_t tick_rate_numerator{60};
    std::uint32_t tick_rate_denominator{1};
    std::uint64_t initial_tick{0};
    std::uint64_t build_fingerprint{0};
};

class Timeline final {
public:
    Timeline() noexcept;
    ~Timeline() noexcept;
    Timeline(const Timeline&) = delete;
    Timeline& operator=(const Timeline&) = delete;
    Timeline(Timeline&&) = delete;
    Timeline& operator=(Timeline&&) = delete;

    [[nodiscard]] TimeError start(ClockSource* source, TimelineConfig config) noexcept;
    [[nodiscard]] TimeError pump(TickPlan& plan) noexcept;          // owner thread
    [[nodiscard]] TimeError pump_elapsed(std::int64_t elapsed_ns,
                                         TickPlan& plan) noexcept;  // owner thread, tests/replay
    [[nodiscard]] TimeError pause() noexcept;
    [[nodiscard]] TimeError resume() noexcept;
    [[nodiscard]] TimeError step_once(TickPlan& plan) noexcept;     // paused only
    [[nodiscard]] TimeError stop() noexcept;                        // idempotent
    [[nodiscard]] TimelineState state() const noexcept;
    [[nodiscard]] TimelineStats stats() const noexcept;
    [[nodiscard]] TickId current_tick() const noexcept;
};

}  // namespace stormline::core::time
```

No implementation is provided. Signatures may be refined only by an audited contract correction before `CORE-04-03`.

## Semantics

- **Lifecycle:** `Uninitialized -> Running <-> Paused -> Stopped`; source invariant failure enters `Failed`. `start` only from `Uninitialized`; `stop` is idempotent; restart is rejected. Owner thread is the `start` caller; owner-only methods return `WrongThread` elsewhere.
- **Config:** tick rate numerator/denominator > 0; `max_catch_up_ticks` 1..64; `max_frame_delta_ns` > 0; `max_debt_ns` > 0; time scale positive rational. Invalid values return `InvalidConfig` without state change.
- **Clock:** monotonic elapsed nanoseconds since an opaque process epoch. Null source, `ClockUnavailable`, backward/duplicate samples and overflow return typed errors; source failures move the timeline to `Failed`.
- **Fixed step:** exact rational period `tick_rate_denominator / tick_rate_numerator` seconds. Use checked integer arithmetic with carried remainder; never accumulate floating-point `dt`. `TickId` starts at 0 and increments by one per emitted tick; overflow returns `TickOverflow`.
- **Pump:** running pump samples (or accepts injected elapsed), applies rational time scale, clamps to `max_frame_delta_ns` with `plan.clamped=true`, and emits at most `max_catch_up_ticks`. Paused pump emits zero ticks and does not accumulate background elapsed.
- **Debt:** excess beyond catch-up follows `DropExcess` (record `dropped_ns` and stats) or `Carry` (bounded by `max_debt_ns`; exceeding returns `DebtLimitExceeded`). Authoritative headless must use `Carry` or equivalent and must not silently discard ticks.
- **Interpolation:** `interpolation_alpha` is the remaining fraction of a tick after emitted ticks, in `[0,1)`; it is derived only from admitted elapsed, never wall-clock UTC or presentation timestamps.
- **Pause/step:** pause while running; resume while paused; `step_once` emits exactly one tick while remaining paused and never accumulates background time.
- **Determinism envelope:** same admitted elapsed/input schedule and config yields the same `TickId` sequence and rational fixed step. This is not a bit-exact physics, multi-thread numerical, compiler floating-point or cross-platform replay guarantee.
- **Replay header:** `ReplayScheduleHeader` records schema, tick rate, initial tick and build fingerprint; mismatch returns `ReplayIncompatible` rather than asserting cross-machine determinism.
- **Diagnostics:** stats are monotonic counters/snapshot; no pointers, thread IDs, unbounded logs or third-party tracing.
- **Errors:** no exception crosses the API.

## Test oracles (future CORE-04-03/-04)

| ID | Scenario | Oracle |
|---|---|---|
| TICK-01 | start/config/thread | null source, zero/negative rate, bad catch-up/debt/scale → `InvalidConfig`; non-owner → `WrongThread` |
| TICK-02 | clock anomalies | backward/duplicate/overflow/unavailable → typed error and `Failed`; no simulated negative time |
| TICK-03 | FPS partitions | 60 s at 30/60/144 FPS → exactly 3,600 60-Hz ticks; alpha in `[0,1)` |
| TICK-04 | long-run rational | 24 h at 60 Hz → exactly 5,184,000 ticks; no nanosecond drift |
| TICK-05 | pause | paused pump emits zero ticks and no debt; resume has no burst |
| TICK-06 | single-step | one tick exactly, state remains Paused |
| TICK-07 | catch-up/drop | bounded tick count; every dropped duration recorded |
| TICK-08 | debt carry | bounded debt; exceeding `max_debt_ns` returns `DebtLimitExceeded` |
| TICK-09 | time scale | 2× and 0.5× rational scale produce exact expected tick counts |
| TICK-10 | overflow | tick counter near max and duration overflow → typed errors, no wrap |
| TICK-11 | lifecycle | stop idempotent; restart rejected; destructor safe; no detached work |
| TICK-12 | determinism/replay | same elapsed partition → identical tick sequence; replay header mismatch rejected |

## Implementation allowlists

### `CORE-04-03` (real time / ClockSource)

1. `src/stormline/core/time/time_types.hpp`
2. `src/stormline/core/time/clock_source.hpp`
3. `src/stormline/core/time/clock_source.cpp`
4. `tests/core/clock_source_tests.cpp`
5. `CMakeLists.txt` (additive CORE-04 target/tests)
6. `.github/workflows/core01-internal-headless.yml` (additive CORE-04 filters)
7. `docs/evidence/NLE-PRPLAN-CORE-04-03.md`

### `CORE-04-04` (timeline/fixed tick, interpolation, pause, step, replay header)

1. `src/stormline/core/time/timeline.hpp`
2. `src/stormline/core/time/timeline.cpp`
3. `tests/core/timeline_tests.cpp`
4. `CMakeLists.txt` (additive CORE-04 target/tests)
5. `.github/workflows/core01-internal-headless.yml` (additive CORE-04 filters)
6. `docs/evidence/NLE-PRPLAN-CORE-04-04.md`

`CORE-04-05`..`-08` may be closed only as satisfied by `CORE-04-04` with audited TICK-05..TICK-12 evidence; any new API/file requires an audited contract correction. `CORE-04-09` qualification and `-10` closeout require separate G6 packets.

## Stop / rollback / security

Stop on stale source, missing admission, third-party timing type, float-only accumulation, unbounded catch-up, silent authoritative tick loss, public ABI/release claim, HIGH/CRITICAL. Unmerged: close the branch; after merge: normal revert PR, never force push.

No implementation is authorized by this contract. `CORE-04-03` requires its own G6 activation.
