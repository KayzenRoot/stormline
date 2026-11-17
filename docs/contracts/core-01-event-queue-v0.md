# CORE-01 INTERNAL_ONLY Event Queue Contract v0 (NLE-PRPLAN-CORE-01-09)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NOT EXTERNAL ABI`. **Base:** `27cd592ec235a63def60f04757ac27700babd334`. **ADR:** [ADR-0088](../adr/0088-core-01-event-queue-slice.md). **WO:** [NLE-PRPLAN-CORE-01-09](../work-orders/NLE-PRPLAN-CORE-01-09.md).

## Objective and bounded scope

Provide the first real CORE-01 host-event path: normalize selected SDL3 events into internal values, enqueue them in a fixed-capacity queue with monotonic sequence/timestamp order, surface overflow, and replay captured events deterministically.

Out of scope: gameplay input mapping/action bindings, gamepad/joystick, text input/IME, DPI, hotplug, fullscreen, clipboard, drag-and-drop, blocking event loop, frame/tick scheduling, physical-device certification, public ABI, packaging/release.

## Dependency and build profile

- SDL3 3.4.20, commit `f00dc919ca35b9756316e86c4777392de442f9b2`, zlib, static `SDL3::SDL3-static`, build-time `FetchContent`; the existing SDL3 runtime/window baseline from `-07`/`-08`.
- `SdlRuntime` must be initialized on the same owner thread and outlive `EventQueue`. `poll()` requires `SDL_WasInit(SDL_INIT_EVENTS) != 0`.
- Event tests use `SDL_VIDEODRIVER=dummy` and inject synthetic events with `SDL_PushEvent`; no physical keyboard/mouse/gamepad is required or claimed.
- Linux/macOS/Windows standard public runners; Linux ASan/UBSan. No package installation, paid runner, secret or runtime download.

## Internal API (exact names)

Namespace `stormline::core::internal`, header `stormline/core/internal/event_queue.hpp`, no symbol/ABI stability guarantee:

```cpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <thread>

namespace stormline::core::internal {

enum class InputEventType : std::uint8_t {
    None,
    Quit,
    KeyDown,
    KeyUp,
    MouseMotion,
    MouseButtonDown,
    MouseButtonUp,
    WindowResized,
    WindowFocusGained,
    WindowFocusLost,
    WindowCloseRequested
};

enum class EventError : std::uint8_t {
    None,
    Empty,
    Full,
    Overflow,
    WrongThread,
    RuntimeNotInitialized,
    InvalidReplay,
    InternalFailure
};

struct InputEvent final {
    InputEventType type{InputEventType::None};
    std::uint64_t sequence{0};
    std::uint64_t timestamp_ns{0};
    std::uint32_t window_id{0};
    std::int32_t keycode{0};
    std::int32_t scancode{0};
    std::uint16_t modifiers{0};
    std::uint32_t mouse_state{0};
    std::uint8_t button{0};
    std::uint8_t clicks{0};
    float x{0.0F};
    float y{0.0F};
    float xrel{0.0F};
    float yrel{0.0F};
    int width{0};
    int height{0};
};

class EventQueue final {
public:
    static constexpr std::size_t capacity = 256;

    EventQueue() noexcept;
    ~EventQueue() noexcept = default;

    EventQueue(const EventQueue&) = delete;
    EventQueue& operator=(const EventQueue&) = delete;
    EventQueue(EventQueue&&) = delete;
    EventQueue& operator=(EventQueue&&) = delete;

    [[nodiscard]] EventError poll() noexcept;
    [[nodiscard]] EventError replay(const InputEvent* events, std::size_t count) noexcept;
    [[nodiscard]] EventError pop(InputEvent& out) noexcept;
    [[nodiscard]] EventError clear() noexcept;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] std::uint64_t next_sequence() const noexcept;

private:
    void push_back(const InputEvent& event) noexcept;

    std::array<InputEvent, capacity> events_{};
    std::size_t head_{0};
    std::size_t tail_{0};
    std::size_t size_{0};
    std::uint64_t next_sequence_{1};
    std::thread::id owner_thread_;
};

}  // namespace stormline::core::internal
```

The header includes only C++ standard headers. It must not include SDL, platform headers or any third-party header.

## Semantics

### `poll()`

1. Wrong owner thread → `WrongThread`; no SDL call.
2. `SDL_WasInit(SDL_INIT_EVENTS) == 0` → `RuntimeNotInitialized`.
3. Queue already full (`size() == capacity`) → `Overflow` **before** consuming any SDL event.
4. Otherwise call `SDL_PollEvent` until it returns false or the queue becomes full, normalizing only:
   - `SDL_EVENT_QUIT` → `Quit`
   - `SDL_EVENT_KEY_DOWN`/`SDL_EVENT_KEY_UP` → `KeyDown`/`KeyUp` with window ID, keycode, scancode, modifiers
   - `SDL_EVENT_MOUSE_MOTION` → `MouseMotion` with window ID, mouse state, x/y, xrel/yrel
   - `SDL_EVENT_MOUSE_BUTTON_DOWN`/`SDL_EVENT_MOUSE_BUTTON_UP` → `MouseButtonDown`/`MouseButtonUp` with window ID, button, clicks, x/y
   - `SDL_EVENT_WINDOW_RESIZED` → `WindowResized` with window ID, width/height from `data1`/`data2`
   - `SDL_EVENT_WINDOW_FOCUS_GAINED`/`SDL_EVENT_WINDOW_FOCUS_LOST` → corresponding type and window ID
   - `SDL_EVENT_WINDOW_CLOSE_REQUESTED` → `WindowCloseRequested` and window ID
5. Unhandled SDL event types are consumed and skipped; they do not enter the queue.
6. Each queued event gets `sequence = next_sequence_++`; `timestamp_ns` is the SDL event timestamp.
7. If the queue becomes full during the drain, remaining SDL events stay in SDL's queue and the call returns `None`; the next `poll()` returns `Overflow` until the caller pops. No queued event is dropped.
8. No exception crosses the API; unexpected exceptions return `InternalFailure`.

### `replay(events, count)`

- Wrong owner thread → `WrongThread`.
- `count == 0` → `None` (a null pointer is allowed when count is zero).
- `events == nullptr && count != 0` → `InvalidReplay`.
- `count > capacity - size()` → `Full`; no mutation.
- The complete input is validated before mutation:
  - every `type != None`;
  - `sequence > tail sequence` when the queue is non-empty, otherwise `sequence > 0`;
  - each following sequence is strictly greater than the previous;
  - `timestamp_ns` is non-decreasing against the queue tail and within the replay.
- On success, events are appended with their original `sequence` and `timestamp_ns`; `next_sequence()` becomes at least `last.sequence + 1`.
- On any validation failure → `InvalidReplay`; the queue is unchanged (atomic replay).
- No SDL call and no allocation.

### `pop(out)`

- Wrong owner thread → `WrongThread`.
- Empty → `Empty`; `out` unchanged.
- Otherwise copies the front event to `out`, clears the slot, advances the head and returns `None`.

### `clear()` and queries

- `clear()`: wrong thread → `WrongThread`; otherwise drops all queued events, zeroes the slots and returns `None`. It does **not** reset `next_sequence_` or SDL's queue.
- `size()`, `empty()`, `next_sequence()` report the internal queue only; they do not pump SDL or consume events.
- The queue is not thread-safe for concurrent access; all mutating calls and queries must be serialized by the caller, with mutation restricted to the owner thread.

### Failure and lifetime behavior

- No exception crosses the boundary.
- No global mutable state, singleton, SDL event filter, hidden thread or blocking loop.
- `SdlRuntime` must outlive `EventQueue`; destroying the queue does not call `SDL_Quit` or flush SDL events.
- Tests run one mode per CTest process and flush SDL events at test start.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| EVT-01 | live normalization of quit/key/mouse/window events | all nine mapped types appear with the expected fields |
| EVT-02 | sequence/timestamp order | strictly increasing sequences; non-decreasing timestamps; exact replay preservation |
| EVT-03 | overflow | full queue → `Overflow` before SDL consumption; no queued event lost; drain then poll recovers |
| EVT-04 | replay success | order/sequence/timestamp preserved; `next_sequence` advances; no SDL required |
| EVT-05 | replay rejection | null+count, `None` type, non-monotonic sequence/timestamp, too many events → typed error and unchanged queue |
| EVT-06 | wrong thread | poll/replay/pop/clear → `WrongThread`; queue and SDL queue unchanged |
| EVT-07 | runtime/empty/clear | poll without events subsystem → `RuntimeNotInitialized`; empty pop → `Empty`; clear → empty and sequence preserved |
| EVT-08 | 1000-cycle lifetime/regression | replay/pop 1000 cycles without growth; existing 32 CTests still pass on Linux, Linux ASan/UBSan, Windows and macOS |

Synthetic SDL events prove normalization, ordering, overflow and replay semantics. Physical keyboard/mouse/gamepad, IME, DPI, hotplug, text editing and gameplay mapping remain **NOT_QUALIFIED**.

## Exact implementation allowlist for packet -09

1. `src/stormline/core/internal/event_queue.hpp`
2. `src/stormline/core/internal/event_queue.cpp`
3. `tests/core/event_queue_tests.cpp`
4. `CMakeLists.txt` (additive event-queue target/tests only)
5. `.github/workflows/core01-internal-headless.yml` (additive CORE-01-09 path filters only)
6. `docs/evidence/NLE-PRPLAN-CORE-01-09.md`

`docs/work-orders/NLE-PRPLAN-CORE-01-09.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, gate not merged, selector blocked, existing test regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, SDL type in the header, silent event drop, physical-input/gamepad/IME/DPI/hotplug overclaim, public ABI/release or another packet/module unlock.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- No secret, paid runner/service, upload, runtime download or package installation. SDL3 zlib notice remains preserved for future distribution; `NLE-D009 OPEN`; no release.
- Risk `STANDARD`, release `INTERNAL_ONLY`. ADR-0003/0075 `PROPOSED`; ADR-0088 bounded; G3 global `NOT_CLEARED`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -09 remains blocked until then.**
