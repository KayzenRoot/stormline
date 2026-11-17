#include "stormline/core/internal/native_bridge.hpp"
#include "stormline/core/internal/sdl_runtime.hpp"
#include "stormline/core/internal/window.hpp"

#if defined(SDL_h_)
#error "SDL header/type leaked through the CORE-01 native bridge/window headers"
#endif

#include <cstdint>
#include <cstdio>
#include <string_view>
#include <thread>

namespace {

using stormline::core::internal::current_native_window_system;
using stormline::core::internal::NativeHandleKind;
using stormline::core::internal::NativeWindowHandle;
using stormline::core::internal::NativeWindowSystem;
using stormline::core::internal::SdlError;
using stormline::core::internal::SdlRuntime;
using stormline::core::internal::Window;
using stormline::core::internal::WindowConfig;
using stormline::core::internal::WindowError;

int failures = 0;

void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}

void begin_case() {
    failures = 0;
}

bool finish_case() {
    return failures == 0;
}

#if defined(_WIN32)
constexpr NativeWindowSystem kExpectedSystem = NativeWindowSystem::Win32;
constexpr NativeHandleKind kExpectedKind = NativeHandleKind::Win32Hwnd;
#elif defined(__APPLE__)
constexpr NativeWindowSystem kExpectedSystem = NativeWindowSystem::Cocoa;
constexpr NativeHandleKind kExpectedKind = NativeHandleKind::CocoaWindow;
#else
constexpr NativeWindowSystem kExpectedSystem = NativeWindowSystem::X11;
constexpr NativeHandleKind kExpectedKind = NativeHandleKind::X11Window;
#endif

bool initialize_runtime(SdlRuntime& runtime) {
    if (runtime.initialize() == SdlError::None) {
        return true;
    }
#if defined(__APPLE__)
    std::printf("NOT_QUALIFIED: cocoa window server unavailable\n");
    return false;
#else
    expect(false, "runtime initialize succeeds");
    return false;
#endif
}

bool create_window(Window& window) {
    if (window.create(WindowConfig{}) == WindowError::None) {
        return true;
    }
#if defined(__APPLE__)
    std::printf("NOT_QUALIFIED: cocoa window creation unavailable\n");
    return false;
#else
    expect(false, "window create succeeds");
    return false;
#endif
}

bool run_system() {
    begin_case();
    SdlRuntime runtime;
    if (!initialize_runtime(runtime)) {
        return finish_case();
    }
    expect(current_native_window_system() == kExpectedSystem,
           "active native window system matches the platform driver");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_handle() {
    begin_case();
    SdlRuntime runtime;
    if (!initialize_runtime(runtime)) {
        return finish_case();
    }

    Window window;
    if (!create_window(window)) {
        expect(runtime.shutdown() == SdlError::None, "runtime shutdown after create failure");
        return finish_case();
    }

    NativeWindowHandle handle{};
    expect(window.query_native_handle(handle) == WindowError::None,
           "native handle query succeeds");
    expect(handle.kind == kExpectedKind, "native handle kind matches the platform");
    expect(handle.value != 0, "native handle value is non-zero");
    expect(handle.generation != 0, "native handle generation is non-zero");
    expect(window.native_handle_valid(handle), "current native handle is valid");

    expect(window.destroy() == WindowError::None, "window destroy succeeds");
    expect(!window.native_handle_valid(handle), "destroy invalidates the native handle");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_unavailable() {
    begin_case();
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "dummy runtime initialize succeeds");
    expect(current_native_window_system() == NativeWindowSystem::Unknown,
           "dummy driver reports an unknown native system");

    Window window;
    expect(window.create(WindowConfig{}) == WindowError::None, "dummy window create succeeds");
    NativeWindowHandle handle{};
    expect(window.query_native_handle(handle) == WindowError::NativeHandleUnavailable,
           "dummy window has no native handle");
    expect(!window.native_handle_valid(handle), "unavailable handle is not valid");
    expect(window.destroy() == WindowError::None, "dummy window destroy succeeds");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_errors() {
    begin_case();
    Window window;
    NativeWindowHandle handle{};
    expect(window.query_native_handle(handle) == WindowError::NotCreated,
           "native handle query before create is rejected");
    expect(!window.native_handle_valid(handle), "no native handle is valid without a window");

    SdlRuntime runtime;
    if (!initialize_runtime(runtime)) {
        return finish_case();
    }
    if (!create_window(window)) {
        expect(runtime.shutdown() == SdlError::None, "runtime shutdown after create failure");
        return finish_case();
    }
    expect(window.destroy() == WindowError::None, "window destroy succeeds");
    expect(window.query_native_handle(handle) == WindowError::NotCreated,
           "native handle query after destroy is rejected");
    expect(!window.native_handle_valid(handle), "destroyed window has no valid handle");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_wrong_thread() {
    begin_case();
    SdlRuntime runtime;
    if (!initialize_runtime(runtime)) {
        return finish_case();
    }
    Window window;
    if (!create_window(window)) {
        expect(runtime.shutdown() == SdlError::None, "runtime shutdown after create failure");
        return finish_case();
    }

    WindowError worker_query = WindowError::None;
    NativeWindowHandle worker_handle{};
    std::thread worker([&window, &worker_query, &worker_handle] {
        worker_query = window.query_native_handle(worker_handle);
    });
    worker.join();

    expect(worker_query == WindowError::WrongThread, "worker native handle query is rejected");
    expect(worker_handle.kind == NativeHandleKind::None, "worker query leaves the handle empty");
    expect(window.destroy() == WindowError::None, "window destroy succeeds");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_lifetime() {
    begin_case();
    SdlRuntime runtime;
    if (!initialize_runtime(runtime)) {
        return finish_case();
    }

    bool ok = true;
    for (int cycle = 0; cycle < 50 && ok; ++cycle) {
        Window window;
        ok = create_window(window);
        NativeWindowHandle handle{};
        ok = ok && window.query_native_handle(handle) == WindowError::None;
        ok = ok && handle.kind == kExpectedKind;
        ok = ok && handle.value != 0;
        ok = ok && handle.generation != 0;
        ok = ok && window.native_handle_valid(handle);
        ok = ok && window.destroy() == WindowError::None;
        ok = ok && !window.native_handle_valid(handle);
    }
    expect(ok, "50 native-handle create/query/destroy cycles succeed");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: %s <system|handle|unavailable|errors|wrong_thread|lifetime>\n",
                     argv[0]);
        return 2;
    }

    const std::string_view mode(argv[1]);
    if (mode == "system") {
        return run_system() ? 0 : 1;
    }
    if (mode == "handle") {
        return run_handle() ? 0 : 1;
    }
    if (mode == "unavailable") {
        return run_unavailable() ? 0 : 1;
    }
    if (mode == "errors") {
        return run_errors() ? 0 : 1;
    }
    if (mode == "wrong_thread") {
        return run_wrong_thread() ? 0 : 1;
    }
    if (mode == "lifetime") {
        return run_lifetime() ? 0 : 1;
    }

    std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return 2;
}
