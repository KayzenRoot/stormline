# CORE-01 INTERNAL_ONLY SDL3 Runtime Contract v0 (NLE-PRPLAN-CORE-01-07)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NOT EXTERNAL ABI`. **Base:** `80a6fdafb2cc0f1f923af83367f21e9260e53323`. **Bounded ADR:** [ADR-0084](../adr/0084-core-01-sdl3-runtime-slice.md). **WO:** [NLE-PRPLAN-CORE-01-07](../work-orders/NLE-PRPLAN-CORE-01-07.md).

## Objective and bounded scope

Provide the first real SDL3 integration: a small internal runtime that initializes and shuts down the SDL video/events subsystem on the owner (main) thread, with typed errors, no SDL types in the internal header, and no window, input loop, renderer, GPU, audio, network, public ABI or release.

Out of scope: `SDL_CreateWindow`, window lifecycle, input/event pumping, HiDPI/IME/hotplug, renderer/RHI, audio devices, gamepad, filesystem/VFS, dialogs, clipboard, message boxes, public C ABI/plugin surface, SDL types in any engine header, real display-driver qualification, packaging and distribution.

## Dependency pin and build profile

- Official SDL3 `release-3.4.20`, commit `f00dc919ca35b9756316e86c4777392de442f9b2`, zlib license.
- CMake `FetchContent` from `https://github.com/libsdl-org/SDL.git` at the full commit, **build time only**; no system install, no vendor copy, no runtime download, no package manager, no paid service.
- Static link target `SDL3::SDL3-static`; `SDL_SHARED=OFF`, `SDL_STATIC=ON`, `SDL_TEST_LIBRARY=OFF`, `SDL_TESTS=OFF`, `SDL_EXAMPLES=OFF`, `SDL_INSTALL=OFF`.
- This slice disables audio/joystick/haptic/HIDAPI/sensor/power/camera and X11/Wayland/KMSDRM; the dummy video driver is used in CI. Real window drivers are deferred to `-08`/PLAT and are **NOT_QUALIFIED** here.
- SDL3 headers are included only by `sdl_runtime.cpp`; the internal header and test translation unit must not see SDL include directories.

## Internal API (exact names)

Namespace `stormline::core::internal`, no symbol/ABI stability guarantee:

```cpp
#include <cstdint>

enum class SdlError : std::uint8_t {
    None,
    AlreadyInitialized,
    WrongThread,
    InitFailed,
    InternalFailure
};

struct SdlVersion final {
    int major{0};
    int minor{0};
    int patch{0};
};

class SdlRuntime final {
public:
    SdlRuntime() noexcept;
    ~SdlRuntime() noexcept;

    SdlRuntime(const SdlRuntime&) = delete;
    SdlRuntime& operator=(const SdlRuntime&) = delete;
    SdlRuntime(SdlRuntime&&) = delete;
    SdlRuntime& operator=(SdlRuntime&&) = delete;

    [[nodiscard]] SdlError initialize() noexcept;
    [[nodiscard]] SdlError shutdown() noexcept;
    [[nodiscard]] bool initialized() const noexcept;
};

[[nodiscard]] SdlVersion linked_version() noexcept;
```

The header includes no SDL header, type, macro or handle.

## Semantics

### Constructor / destructor

- The constructor records `std::this_thread::get_id()` as the owner thread and leaves the runtime uninitialized.
- The destructor is no-throw. If initialized and called on the owner thread, it calls `SDL_Quit()`. If called on another thread, it does not call SDL (that is a programming error; the process must not use SDL from a foreign thread). The contract requires destruction on the owner thread in tests and normal use.
- One active `SdlRuntime` per process; sequential create/init/quit/destroy cycles are allowed. Concurrent instances are unsupported.

### `initialize()`

1. If called from a thread other than the owner: `WrongThread`, no SDL call.
2. If already initialized: `AlreadyInitialized`, no second `SDL_Init`.
3. Call `SDL_SetMainReady()`, then `SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)`.
4. On failure: call `SDL_Quit()` to clean partial state, remain uninitialized, return `InitFailed`.
5. On success: mark initialized, return `None`.

No window is created. No input is pumped. No renderer/audio/network API is called.

### `shutdown()`

1. If called from a non-owner thread: `WrongThread`, no SDL call.
2. If not initialized: `None` (idempotent).
3. Otherwise call `SDL_Quit()`, mark uninitialized, return `None`.

### `linked_version()`

Calls `SDL_GetVersion` and returns the three integers. CI must observe `3.4.20`; a different linked version is a gate failure, not a silent pass.

### Failure and thread behavior

- No C++ exception crosses the boundary; all three member functions and `linked_version` are `noexcept`. Any unexpected caught exception returns `InternalFailure`.
- No global mutable adapter state, no singleton, no hidden thread, no callback, no ambient network/telemetry.
- SDL error strings are not exposed in the header; typed errors are the contract. (A future diagnostic slice may add a bounded copyable message.)
- Tests use the dummy video driver via `SDL_VIDEODRIVER=dummy`; the invalid-driver test overrides it to a non-existent driver and restores the previous value.

## Test oracles (future implementation)

| ID | Scenario | Oracle |
|---|---|---|
| SDL-01 | 20 init/shutdown cycles on the owner thread with dummy video | every init `None`, every shutdown `None`, `initialized()` false at rest |
| SDL-02 | duplicate init, repeated shutdown | second init `AlreadyInitialized`; repeated shutdown `None`; no double `SDL_Quit` |
| SDL-03 | init/shutdown from a worker thread | `WrongThread`; no SDL initialization from the worker; owner can still init |
| SDL-04 | invalid `SDL_VIDEODRIVER` | `InitFailed`; adapter uninitialized; restore env and a fresh init succeeds |
| SDL-05 | linked version | `3.4.20`, major 3, minor 4, patch 20 |
| SDL-06 | header isolation | test TU includes only the internal header and compiles without SDL include dirs |
| SDL-07 | scope isolation | source contains no window/input/renderer/audio/network call; only SetMainReady/Init/Quit/GetVersion |
| SDL-08 | regression | all existing 12 CORE-01 CTests still pass on Linux, Windows and macOS |

Sanitizers run on Linux when the preinstalled toolchain supports them. Real display/window and physical-driver proof is **NOT_QUALIFIED** in this slice.

## Exact implementation allowlist for packet -07

1. `src/stormline/core/internal/sdl_runtime.hpp`
2. `src/stormline/core/internal/sdl_runtime.cpp`
3. `tests/core/sdl_runtime_tests.cpp`
4. `CMakeLists.txt` (add pinned FetchContent, SDL library/target and CTests; existing targets preserved)
5. `.github/workflows/core01-internal-headless.yml` (timeout increase only, if required by the SDL3 build)
6. `docs/evidence/NLE-PRPLAN-CORE-01-07.md`

`docs/work-orders/NLE-PRPLAN-CORE-01-07.md` is created by the gate and not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, missing gate, failed existing tests, failed SDL3 fetch/build, unexpected dependency/license, HIGH/CRITICAL, real-window overclaim or any out-of-allowlist change.
- Unmerged: close the branch; `main` untouched. After a future merge: normal revert PR, never force push.
- SDL3 is zlib-licensed; its notice must be preserved in any future distribution. Stormline engine license `NLE-D009` remains `OPEN`; no redistribution, package or release.
- Risk `STANDARD`, release `INTERNAL_ONLY` only for this slice. ADR-0003/0075 remain `PROPOSED`; G3 global remains `NOT_CLEARED`.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -07 remains blocked until then.**
