# CORE-01 INTERNAL_ONLY Window Lifecycle Contract v0 (NLE-PRPLAN-CORE-01-08)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NOT EXTERNAL ABI`. **Base:** `b54f19c252fda9c06a7d7289a853bd4cf957cf53`. **ADR:** [ADR-0085](../adr/0085-core-01-window-lifecycle-slice.md). **WO:** [NLE-PRPLAN-CORE-01-08](../work-orders/NLE-PRPLAN-CORE-01-08.md).

## Objective and bounded scope

Provide the first real window lifecycle: create, resize, show, raise/focus request and destroy a window through SDL3 on the owner/main thread, with typed errors, no SDL types in the internal header and verified handle lifetime. No renderer, GPU, audio, input pumping, IME/DPI/hotplug, public ABI, packaging or release.

Out of scope: renderer/swapchain, GPU/Vulkan/Metal/OpenGL, audio, event pump/replay (`-09`), multi-monitor/DPI (`-10`), OS-specific bridges (`-11`), sleep/resume (`-12`), public C ABI/plugin/SDK, physical display/driver certification.

## Dependency and build profile

- SDL3 3.4.20, commit `f00dc919ca35b9756316e86c4777392de442f9b2`, zlib, static `SDL3::SDL3-static`, build-time `FetchContent`.
- X11 and Wayland video drivers built on Linux; Win32 on Windows; Cocoa on macOS. Render/GPU/Vulkan/Metal/OpenGL/GLES/D3D and audio remain OFF; `SDL_KMSDRM=OFF`.
- **Linux CI installation (owner-authorized, R$0):** exact packages:
  `libx11-dev`, `libxext-dev`, `libxrandr-dev`, `libxcursor-dev`, `libxfixes-dev`, `libxi-dev`, `libxss-dev`, `libxtst-dev`, `libxinerama-dev`, `libxrender-dev`, `libxkbcommon-dev`, `libxkbcommon-x11-dev`, `libwayland-dev`, `libdecor-0-dev`, `wayland-protocols`, `libdbus-1-dev`, `libibus-1.0-dev`, `libthai-dev`, `libfribidi-dev`, `libgl1-mesa-dev`, `libegl1-mesa-dev`, `libgles2-mesa-dev`, `xvfb`, `x11-utils`, `openbox`.
- Linux runtime: `Xvfb :99 -screen 0 1280x720x24`, `openbox --sm-disable`, `DISPLAY=:99`, `SDL_VIDEODRIVER=x11`.
- Windows: `SDL_VIDEODRIVER=windows`, no installation.
- macOS: `SDL_VIDEODRIVER=cocoa`; if the hosted runner has no usable window server, real window cases are `NOT_QUALIFIED` with explicit evidence, never a false PASS.
- Wayland: built but **runtime NOT_QUALIFIED** (no compositor in CI).

## Internal API (exact names)

Namespace `stormline::core::internal`, no symbol/ABI stability guarantee:

```cpp
#include <cstdint>
#include <memory>
#include <thread>

struct WindowConfig final {
    int width{640};
    int height{480};
};

enum class WindowError : std::uint8_t {
    None,
    AlreadyCreated,
    NotCreated,
    InvalidSize,
    VideoNotInitialized,
    WrongThread,
    CreateFailed,
    ResizeFailed,
    ShowFailed,
    FocusFailed,
    AllocationFailed,
    InternalFailure
};

class Window final {
public:
    Window() noexcept;
    ~Window() noexcept;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    [[nodiscard]] WindowError create(const WindowConfig& config) noexcept;
    [[nodiscard]] WindowError destroy() noexcept;
    [[nodiscard]] WindowError resize(int width, int height) noexcept;
    [[nodiscard]] WindowError show() noexcept;
    [[nodiscard]] WindowError focus() noexcept;
    [[nodiscard]] bool valid() const noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
    std::thread::id owner_thread_;
};
```

The header includes no SDL header, type, macro or handle.

## Semantics

### Constructor / destructor

- Records the owner thread. The destructor is no-throw; if a window is still alive and the destructor runs on the owner thread, it calls `SDL_DestroyWindow`. On a wrong thread it does not call SDL (programming error; process must not use SDL from a foreign thread).
- A `SdlRuntime` must be initialized on the same owner thread and must outlive the `Window`. The window does not own the runtime.

### `create(config)`

1. Wrong thread → `WrongThread`, no SDL call.
2. Already created → `AlreadyCreated`.
3. `width <= 0 || height <= 0` → `InvalidSize`.
4. `SDL_WasInit(SDL_INIT_VIDEO) == 0` → `VideoNotInitialized`.
5. `SDL_CreateWindow("Stormline", width, height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE)`; null → `CreateFailed`.
6. Allocate the private implementation without exceptions; on allocation failure destroy the SDL window and return `AllocationFailed`.
7. Success → hidden, resizable window; `valid()` true.

### `destroy()`

- Wrong thread → `WrongThread`.
- No window → `None` (idempotent).
- Otherwise `SDL_DestroyWindow`, clear the implementation, return `None`.

### `resize(width, height)`

- Wrong thread → `WrongThread`; no window → `NotCreated`; non-positive → `InvalidSize`.
- `SDL_SetWindowSize` false → `ResizeFailed`; success → `None`.

### `show()`

- Wrong thread → `WrongThread`; no window → `NotCreated`; `SDL_ShowWindow` false → `ShowFailed`; success → `None`.

### `focus()`

- Wrong thread → `WrongThread`; no window → `NotCreated`; `SDL_RaiseWindow` false → `FocusFailed`; success → `None`.
- This is a raise/focus **request**; the compositor may decide actual keyboard focus. Real focus semantics are `NOT_QUALIFIED`.

### Failure and thread behavior

- No C++ exception crosses the boundary; all methods and `valid()` are `noexcept`; unexpected caught exceptions return `InternalFailure`.
- No global mutable adapter state, singleton, hidden window or ambient authority.
- Tests run one mode per CTest process; `VideoNotInitialized` is tested before any `SdlRuntime` initialization in that process.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| WIN-01 | create/resize/show/focus/destroy | every step `None`; `valid()` true then false; no crash |
| WIN-02 | duplicate create and repeated destroy | second create `AlreadyCreated`; repeated destroy `None` |
| WIN-03 | invalid sizes | zero/negative create/resize → `InvalidSize`; state unchanged |
| WIN-04 | operations before create | resize/show/focus/destroy → `NotCreated`/`None` as contracted |
| WIN-05 | wrong-thread create/destroy | `WrongThread`; owner state unchanged |
| WIN-06 | video runtime not initialized | create → `VideoNotInitialized` |
| WIN-07 | 50 lifecycle cycles | each cycle create/show/resize/focus/destroy succeeds; no lingering valid handle |
| WIN-08 | regression | existing 18 CTests still pass on Linux, Windows and macOS |

Real X11 is exercised under Xvfb/openbox; Win32 on the Windows runner; Cocoa on macOS when a window server exists. Wayland and physical display/DPI/IME/hotplug remain **NOT_QUALIFIED**.

## Exact implementation allowlist for packet -08

1. `src/stormline/core/internal/window.hpp`
2. `src/stormline/core/internal/window.cpp`
3. `tests/core/window_tests.cpp`
4. `CMakeLists.txt` (add window target/tests and enable X11/Wayland video build)
5. `.github/workflows/core01-internal-headless.yml` (exact Linux install, Xvfb/openbox, window test env)
6. `docs/evidence/NLE-PRPLAN-CORE-01-08.md`

`docs/work-orders/NLE-PRPLAN-CORE-01-08.md` is created by the gate and not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, missing gate, package install failure, SDL3 build/fetch mismatch, existing test regression, CI red, HIGH/CRITICAL, unsafe write, real-window overclaim or out-of-allowlist change.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- Only Ubuntu packages from the official repositories; no paid runner/service, secret, upload or runtime download. SDL3 zlib notice preserved for future distribution; `NLE-D009 OPEN`; no release.
- Risk `STANDARD`, release `INTERNAL_ONLY` only. ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; 80 module WOs `BLOCKED`.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -08 remains blocked until then.**
