# CORE-01 INTERNAL_ONLY Lifecycle Request Contract v0 (NLE-PRPLAN-CORE-01-12)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NOT EXTERNAL ABI`. **Base:** `df551006982868e616d867c7daaa3fc5a7c51ee8`. **ADR:** [ADR-0091](../adr/0091-core-01-lifecycle-request-state-machine.md). **WO:** [NLE-PRPLAN-CORE-01-12](../work-orders/NLE-PRPLAN-CORE-01-12.md).

## Objective and bounded scope

Provide an owner-thread lifecycle request state machine for suspend/resume/shutdown/terminate, with typed transitions and host-event observation of quit/window-close requests. No OS signal handlers, sleep hooks, forced process kill, persistence/save, renderer teardown, public ABI or release.

## Dependency and build profile

- C++20 standard library only; no SDL/platform header in this contract or header.
- Consumes the existing `InputEvent` from `event_queue.hpp` for `Quit`/`WindowCloseRequested`.
- Tests run on Linux, Linux ASan/UBSan, Windows and macOS; no display/OS suspend required.
- Physical OS sleep/resume/termination and persistence remain **NOT_QUALIFIED**.

## Internal API (exact names)

```cpp
#pragma once

#include "stormline/core/internal/event_queue.hpp"

#include <cstdint>
#include <thread>

namespace stormline::core::internal {

enum class LifecycleState : std::uint8_t {
    Running,
    SuspendPending,
    Suspended,
    ResumePending,
    ShutdownPending,
    Terminated
};

enum class LifecycleError : std::uint8_t {
    None,
    WrongThread,
    InvalidTransition,
    AlreadyTerminated,
    InternalFailure
};

class LifecycleController final {
public:
    LifecycleController() noexcept;
    ~LifecycleController() noexcept = default;

    LifecycleController(const LifecycleController&) = delete;
    LifecycleController& operator=(const LifecycleController&) = delete;
    LifecycleController(LifecycleController&&) = delete;
    LifecycleController& operator=(LifecycleController&&) = delete;

    [[nodiscard]] LifecycleError request_suspend() noexcept;
    [[nodiscard]] LifecycleError acknowledge_suspend() noexcept;
    [[nodiscard]] LifecycleError request_resume() noexcept;
    [[nodiscard]] LifecycleError acknowledge_resume() noexcept;
    [[nodiscard]] LifecycleError request_shutdown() noexcept;
    [[nodiscard]] LifecycleError acknowledge_shutdown() noexcept;
    [[nodiscard]] LifecycleError request_terminate() noexcept;
    [[nodiscard]] LifecycleError observe(const InputEvent& event) noexcept;

    [[nodiscard]] LifecycleState state() const noexcept;
    [[nodiscard]] bool should_continue() const noexcept;

private:
    LifecycleState state_{LifecycleState::Running};
    std::thread::id owner_thread_;
};

}  // namespace stormline::core::internal
```

The header includes only C++ standard headers plus the existing internal event-queue header; no SDL/platform type.

## Transition table

| Call | Current | Result | Error |
|---|---|---|---|
| `request_suspend` | `Running` | `SuspendPending` | `None` |
| `request_suspend` | any other | unchanged | `InvalidTransition` |
| `acknowledge_suspend` | `SuspendPending` | `Suspended` | `None` |
| `acknowledge_suspend` | any other | unchanged | `InvalidTransition` |
| `request_resume` | `Suspended` | `ResumePending` | `None` |
| `request_resume` | any other | unchanged | `InvalidTransition` |
| `acknowledge_resume` | `ResumePending` | `Running` | `None` |
| `acknowledge_resume` | any other | unchanged | `InvalidTransition` |
| `request_shutdown` | `Running`, `SuspendPending`, `Suspended`, `ResumePending` | `ShutdownPending` | `None` |
| `request_shutdown` | `ShutdownPending` | unchanged | `None` (idempotent) |
| `request_shutdown` | `Terminated` | unchanged | `AlreadyTerminated` |
| `acknowledge_shutdown` | `ShutdownPending` | `Terminated` | `None` |
| `acknowledge_shutdown` | `Terminated` | unchanged | `AlreadyTerminated` |
| `acknowledge_shutdown` | any other | unchanged | `InvalidTransition` |
| `request_terminate` | any not `Terminated` | `Terminated` | `None` |
| `request_terminate` | `Terminated` | unchanged | `AlreadyTerminated` |

### `observe(event)`

- Wrong owner thread → `WrongThread`.
- `InputEventType::Quit` or `WindowCloseRequested` → calls the `request_shutdown` transition; returns its result.
- Any other event type → `None`, state unchanged.
- Does not own/poll the event queue; the caller supplies already-normalized events.

### Queries and lifetime

- `state()` returns the current state; no SDL call, no mutation.
- `should_continue()` returns false for `ShutdownPending` and `Terminated`; true otherwise.
- All mutating operations are owner-thread only and `noexcept`; no exception crosses the boundary.
- The controller owns no OS resources; the destructor performs no forced transition.
- No global state, singleton, signal handler or hidden thread.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| LCY-01 | normal suspend/resume | Running → SuspendPending → Suspended → ResumePending → Running; `should_continue` true |
| LCY-02 | shutdown | request from Running/SuspendPending/Suspended/ResumePending → ShutdownPending; acknowledge → Terminated; `should_continue` false |
| LCY-03 | observed host events | Quit/WindowCloseRequested → ShutdownPending; KeyDown ignored; state unchanged |
| LCY-04 | invalid transitions | resume/acknowledge in wrong state → `InvalidTransition`; state unchanged; terminated repeats → `AlreadyTerminated` |
| LCY-05 | wrong thread | all mutating calls from worker → `WrongThread`; state unchanged |
| LCY-06 | recovery/lifetime/regression | 100 suspend/resume cycles, then shutdown; existing 53 CTests pass on Linux, Linux ASan/UBSan, Windows and macOS |

Physical OS suspend/resume/termination, forced process kill, persistence/save, renderer device-loss recovery and public ABI remain **NOT_QUALIFIED**.

## Exact implementation allowlist for packet -12

1. `src/stormline/core/internal/lifecycle.hpp`
2. `src/stormline/core/internal/lifecycle.cpp`
3. `tests/core/lifecycle_tests.cpp`
4. `CMakeLists.txt` (additive lifecycle target/tests only)
5. `.github/workflows/core01-internal-headless.yml` (additive CORE-01-12 path filters only)
6. `docs/evidence/NLE-PRPLAN-CORE-01-12.md`

`docs/work-orders/NLE-PRPLAN-CORE-01-12.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, gate not merged, selector blocked, existing test regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, OS signal/termination/persistence/ABI/release overclaim, or another packet/module unlock.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- No secret, paid runner/service, upload, runtime download or package installation. SDL3 zlib notice remains preserved for future distribution; `NLE-D009 OPEN`; no release.
- Risk `STANDARD`, release `INTERNAL_ONLY`. ADR-0003/0075 `PROPOSED`; ADR-0091 bounded; G3 global `NOT_CLEARED`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -12 remains blocked until then.**
