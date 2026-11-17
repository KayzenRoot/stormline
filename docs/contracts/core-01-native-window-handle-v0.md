# CORE-01 INTERNAL_ONLY Native Window Handle Contract v0 (NLE-PRPLAN-CORE-01-11)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NOT EXTERNAL ABI`. **Base:** `44b37d4b6e67314e7317257707a3064bd69c6830`. **ADR:** [ADR-0090](../adr/0090-core-01-native-window-handle-bridge.md). **WO:** [NLE-PRPLAN-CORE-01-11](../work-orders/NLE-PRPLAN-CORE-01-11.md).

## Objective and bounded scope

Provide an internal opaque bridge to the native window handle already owned by SDL: identify the active window system, obtain a non-owning handle token (kind/value/generation), and validate that token against the live window. No direct Win32/Cocoa/Wayland/X11 implementation, renderer surface/VRAM, clipboard, drag-and-drop, IME, hotplug, permissions or public ABI.

## Dependency and build profile

- SDL3 3.4.20, commit `f00dc919ca35b9756316e86c4777392de442f9b2`, zlib, static `SDL3::SDL3-static`, build-time `FetchContent`; existing `-07`..`-10` baseline.
- `SdlRuntime` must be initialized on the same owner thread and outlive `Window`.
- Native window tests run with `SDL_VIDEODRIVER=x11` (Linux/Xvfb), `windows` (Windows), `cocoa` (macOS); dummy-driver test expects `NativeHandleUnavailable`.
- Physical OS permission/sandbox, multi-window, renderer/GPU and public plugin ABI remain **NOT_QUALIFIED**.

## Internal API (exact names)

### `native_bridge.hpp`

```cpp
#pragma once

#include <cstdint>

namespace stormline::core::internal {

enum class NativeWindowSystem : std::uint8_t {
    Unknown,
    X11,
    Wayland,
    Win32,
    Cocoa
};

enum class NativeHandleKind : std::uint8_t {
    None,
    X11Window,
    WaylandSurface,
    Win32Hwnd,
    CocoaWindow
};

struct NativeWindowHandle final {
    NativeHandleKind kind{NativeHandleKind::None};
    std::uint64_t value{0};
    std::uint64_t generation{0};
};

[[nodiscard]] NativeWindowSystem current_native_window_system() noexcept;

}  // namespace stormline::core::internal
```

### Additive `window.hpp` bridge API

`WindowError` gains `NativeHandleUnavailable` after `SurfaceQueryFailed` (existing values unchanged). The following methods are added:

```cpp
[[nodiscard]] WindowError query_native_handle(NativeWindowHandle& out) noexcept;
[[nodiscard]] bool native_handle_valid(const NativeWindowHandle& handle) const noexcept;
```

Headers include only C++ standard headers; no SDL/platform/third-party type.

## Semantics

### `current_native_window_system()`

- Returns `X11`, `Wayland`, `Win32` or `Cocoa` for the active SDL video driver.
- Returns `Unknown` when SDL is not initialized, the driver is `dummy`/`offscreen`, or the driver is unrecognized.
- Does not query a window and does not allocate.

### `Window::query_native_handle(out)`

1. Wrong owner thread → `WrongThread`; no window → `NotCreated`.
2. Obtain `SDL_GetWindowProperties`; failure/zero properties → `NativeHandleUnavailable`.
3. Check in this order and return the first present, non-zero property:
   - `SDL_PROP_WINDOW_WIN32_HWND_POINTER` → `Win32Hwnd`;
   - `SDL_PROP_WINDOW_COCOA_WINDOW_POINTER` → `CocoaWindow`;
   - `SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER` → `WaylandSurface`;
   - `SDL_PROP_WINDOW_X11_WINDOW_NUMBER` → `X11Window`.
4. No matching property → `NativeHandleUnavailable`.
5. Fill `kind`, `value` (opaque numeric handle) and `generation`; return `None`.
6. The handle is **non-owning**: the caller must not free, close or reinterpret-own it; SDL/the window/OS retain ownership.

### `Window::native_handle_valid(handle)`

- Returns false for `kind == None`, `value == 0` or `generation == 0`.
- Returns false if the window is not alive.
- Returns true only if the token generation equals the window's native-handle generation.
- Does not query SDL or mutate state.

### Lifetime and failure behavior

- The native-handle generation is set when the window is created and invalidated by destroy. It does not change on resize.
- No exception crosses the boundary; unexpected exceptions → `InternalFailure`.
- No global mutable state, singleton or hidden thread.
- `SdlRuntime` must outlive `Window`; destroying the window invalidates all native-handle tokens.
- The bridge exposes no direct OS permission, sandbox bypass, renderer surface or VRAM ownership.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| NBI-01 | active window system | X11/Win32/Cocoa on native drivers; dummy/offscreen → `Unknown` |
| NBI-02 | native handle | created window with native driver returns non-zero kind/value/generation; kind matches the active system |
| NBI-03 | dummy/unavailable | dummy window → `NativeHandleUnavailable`; no ownership claim |
| NBI-04 | wrong thread/errors | worker query → `WrongThread`; query before create/after destroy → `NotCreated` |
| NBI-05 | destroy invalidation | token valid before destroy, invalid after; stale generation rejected |
| NBI-06 | lifetime/regression | 50 create/query/destroy cycles; existing 47 CTests pass on Linux, Linux ASan/UBSan, Windows and macOS |

Physical OS permission/sandbox, multiple native windows, renderer surface/VRAM, IME/hotplug and public ABI remain **NOT_QUALIFIED**.

## Exact implementation allowlist for packet -11

1. `src/stormline/core/internal/native_bridge.hpp`
2. `src/stormline/core/internal/native_bridge.cpp`
3. `src/stormline/core/internal/window.hpp` (additive native-handle API)
4. `src/stormline/core/internal/window.cpp` (additive native-handle query/validity)
5. `tests/core/native_bridge_tests.cpp`
6. `CMakeLists.txt` (additive native-bridge target/tests only)
7. `.github/workflows/core01-internal-headless.yml` (additive CORE-01-11 path filters only)
8. `docs/evidence/NLE-PRPLAN-CORE-01-11.md`

`docs/work-orders/NLE-PRPLAN-CORE-01-11.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, gate not merged, selector blocked, existing test regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, SDL type in a header, handle ownership/double-free, physical-OS/ABI/release overclaim, or another packet/module unlock.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- No secret, paid runner/service, upload, runtime download or package installation. SDL3 zlib notice remains preserved for future distribution; `NLE-D009 OPEN`; no release.
- Risk `STANDARD`, release `INTERNAL_ONLY`. ADR-0003/0075 `PROPOSED`; ADR-0090 bounded; G3 global `NOT_CLEARED`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -11 remains blocked until then.**
