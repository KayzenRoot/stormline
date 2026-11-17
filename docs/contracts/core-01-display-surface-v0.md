# CORE-01 INTERNAL_ONLY Display and Surface Contract v0 (NLE-PRPLAN-CORE-01-10)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NOT EXTERNAL ABI`. **Base:** `7e42b48f19272498c732d75f2051704f5b82311f`. **ADR:** [ADR-0089](../adr/0089-core-01-display-surface-slice.md). **WO:** [NLE-PRPLAN-CORE-01-10](../work-orders/NLE-PRPLAN-CORE-01-10.md).

## Objective and bounded scope

Provide the first real CORE-01 display/surface metadata path: enumerate displays, report bounds/usable bounds/content scale, query a window's display/scale/logical/pixel metrics, and invalidate a borrowed surface generation after a successful resize or an observed display/pixel-size change.

Out of scope: renderer/swapchain/GPU/VRAM, physical hotplug/display-removal certification, IME, text editing, fullscreen, HDR, clipboard, drag-and-drop, gameplay mapping, public ABI, packaging/release.

## Dependency and build profile

- SDL3 3.4.20, commit `f00dc919ca35b9756316e86c4777392de442f9b2`, zlib, static `SDL3::SDL3-static`, build-time `FetchContent`; existing `-07`/`-08`/`-09` baseline.
- `SdlRuntime` must be initialized on the same owner thread and outlive display/window objects. Display enumeration requires `SDL_WasInit(SDL_INIT_VIDEO) != 0`.
- Tests use `SDL_VIDEODRIVER=dummy` on all platforms; real X11/Win32/Cocoa window tests remain in the existing window suite. Physical multi-monitor/hotplug/DPI changes are **NOT_QUALIFIED**.
- Linux/macOS/Windows standard public runners; Linux ASan/UBSan. No package installation, paid runner, secret or runtime download.

## Internal API (exact names)

### `display.hpp`

```cpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <thread>

namespace stormline::core::internal {

struct DisplayInfo final {
    std::uint32_t id{0};
    bool primary{false};
    int x{0};
    int y{0};
    int width{0};
    int height{0};
    int usable_x{0};
    int usable_y{0};
    int usable_width{0};
    int usable_height{0};
    float content_scale{1.0F};
};

enum class DisplayError : std::uint8_t {
    None,
    VideoNotInitialized,
    WrongThread,
    NoDisplays,
    BufferTooSmall,
    InvalidArgument,
    QueryFailed,
    InternalFailure
};

class DisplayService final {
public:
    DisplayService() noexcept;
    ~DisplayService() noexcept = default;

    DisplayService(const DisplayService&) = delete;
    DisplayService& operator=(const DisplayService&) = delete;
    DisplayService(DisplayService&&) = delete;
    DisplayService& operator=(DisplayService&&) = delete;

    [[nodiscard]] DisplayError enumerate(DisplayInfo* out, std::size_t capacity,
                                         std::size_t& count) noexcept;
    [[nodiscard]] DisplayError primary(DisplayInfo& out) noexcept;

private:
    std::thread::id owner_thread_;
};

}  // namespace stormline::core::internal
```

### Additive `window.hpp` surface API

`WindowError` gains `SurfaceQueryFailed` after `InternalFailure` (existing values unchanged). The following types/methods are added without changing existing methods:

```cpp
struct SurfaceMetrics final {
    std::uint32_t display_id{0};
    float display_scale{1.0F};
    int logical_width{0};
    int logical_height{0};
    int pixel_width{0};
    int pixel_height{0};
    std::uint64_t generation{1};
};

[[nodiscard]] WindowError query_surface(SurfaceMetrics& out) noexcept;
[[nodiscard]] bool surface_valid(std::uint64_t generation) const noexcept;
```

Headers include only C++ standard headers; no SDL/platform/third-party type.

## Semantics

### `DisplayService::enumerate(out, capacity, count)`

1. Wrong owner thread → `WrongThread`; no SDL call.
2. `SDL_WasInit(SDL_INIT_VIDEO) == 0` → `VideoNotInitialized`.
3. `out == nullptr && capacity != 0` → `InvalidArgument`; `count` unchanged.
4. Query `SDL_GetDisplays`. Null/zero → `NoDisplays`, `count = 0`.
5. If total displays exceed `capacity` → `BufferTooSmall`, `count = total`, no partial write.
6. For each display, query bounds, usable bounds and content scale; a failed bounds query → `QueryFailed` with `count` unchanged and no partial contract claim.
7. Fill `DisplayInfo` values; `primary` is true only for `SDL_GetPrimaryDisplay()`; `content_scale` is the SDL content scale (positive); free the SDL-owned display array.
8. Success → `None`, `count = total`.

### `DisplayService::primary(out)`

- Wrong thread → `WrongThread`; video not initialized → `VideoNotInitialized`; no primary/display → `NoDisplays`; bounds/scale failure → `QueryFailed`.
- Fills exactly one `DisplayInfo` with `primary = true`.

### `Window::query_surface(out)`

1. Wrong owner thread → `WrongThread`; no window → `NotCreated`.
2. Query `SDL_GetDisplayForWindow`, `SDL_GetWindowDisplayScale`, `SDL_GetWindowSize` and `SDL_GetWindowSizeInPixels`.
3. Any query failure or non-positive logical/pixel size → `SurfaceQueryFailed`; `out` unchanged.
4. If the display ID or pixel size changed from the cached value, increment the surface generation before returning. A successful `resize` also increments the generation.
5. Fill `SurfaceMetrics`; return `None`.

### `Window::surface_valid(generation)`

- Returns false if no window or `generation == 0`.
- Returns true only when the supplied generation equals the current surface generation.
- Does not query SDL or mutate state.

### Failure and lifetime behavior

- No exception crosses the API; unexpected exceptions → `InternalFailure`/`SurfaceQueryFailed` as applicable.
- No global mutable state, singleton or hidden thread.
- `SdlRuntime` must outlive `DisplayService` and `Window`; destroying a window does not destroy displays.
- `DisplayInfo` has no strings or pointers; no caller owns SDL memory.
- Physical display addition/removal, real DPI/hotplug events, renderer surfaces and VRAM ownership remain **NOT_QUALIFIED**.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| DPY-01 | display enumeration | at least one display; exactly one primary; positive bounds; usable bounds within bounds; positive content scale |
| DPY-02 | primary query | primary result matches the enumerated primary display |
| DPY-03 | buffer/argument errors | null+capacity → `InvalidArgument`; capacity smaller than total → `BufferTooSmall`, `count=total`, no partial write; zero capacity behaves the same |
| DPY-04 | runtime/thread errors | no video runtime → `VideoNotInitialized`; worker enumerate/primary → `WrongThread` |
| DPY-05 | surface metrics | created window has display ID, positive scale, logical 640x480, positive pixel size; generation >= 1 |
| DPY-06 | resize invalidation | capture generation; resize; old generation invalid; new query has greater generation and is valid |
| DPY-07 | surface errors | query before create/after destroy → `NotCreated`; worker query → `WrongThread` |
| DPY-08 | stability/lifetime/regression | repeated query without change keeps generation; 100 resize/query cycles monotonic; existing 40 CTests pass on Linux, Linux ASan/UBSan, Windows and macOS |

Physical hotplug, multi-monitor movement, real DPI transitions and display removal are **NOT_QUALIFIED**; the query path re-reads display/pixel state but is not a physical hotplug PASS.

## Exact implementation allowlist for packet -10

1. `src/stormline/core/internal/display.hpp`
2. `src/stormline/core/internal/display.cpp`
3. `src/stormline/core/internal/window.hpp` (additive surface API)
4. `src/stormline/core/internal/window.cpp` (additive surface generation/query)
5. `tests/core/display_tests.cpp`
6. `CMakeLists.txt` (additive display target/tests only)
7. `.github/workflows/core01-internal-headless.yml` (additive CORE-01-10 path filters only)
8. `docs/evidence/NLE-PRPLAN-CORE-01-10.md`

`docs/work-orders/NLE-PRPLAN-CORE-01-10.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, gate not merged, selector blocked, existing test regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, SDL type in a header, physical hotplug/DPI overclaim, renderer/GPU/ABI/release claim, or another packet/module unlock.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- No secret, paid runner/service, upload, runtime download or package installation. SDL3 zlib notice remains preserved for future distribution; `NLE-D009 OPEN`; no release.
- Risk `STANDARD`, release `INTERNAL_ONLY`. ADR-0003/0075 `PROPOSED`; ADR-0089 bounded; G3 global `NOT_CLEARED`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -10 remains blocked until then.**
