#include "stormline/core/internal/window.hpp"
#include "stormline/core/internal/sdl_runtime.hpp"

#if defined(SDL_h_)
#error "SDL header/type leaked through the internal window header"
#endif

#include <cstdio>
#include <exception>
#include <iostream>
#include <string_view>
#include <thread>

namespace {

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

void note(const char* description) {
    std::printf("NOT_QUALIFIED: %s\n", description);
}

void begin_case() {
    failures = 0;
}

bool finish_case() {
    return failures == 0;
}

bool initialize_runtime(SdlRuntime& runtime, const char* description) {
    if (runtime.initialize() == SdlError::None) {
        return true;
    }
#if defined(__APPLE__)
    note("cocoa video driver unavailable on this runner");
    return false;
#else
    expect(false, description);
    return false;
#endif
}

bool create_window(Window& window, const WindowConfig& config, const char* description) {
    const WindowError error = window.create(config);
    if (error == WindowError::None) {
        return true;
    }
#if defined(__APPLE__)
    note("cocoa window creation unavailable on this runner");
    return false;
#else
    expect(false, description);
    return false;
#endif
}

bool run_basic() {
    begin_case();
    SdlRuntime runtime;
    if (!initialize_runtime(runtime, "runtime initialize")) {
        return finish_case();
    }

    Window window;
    expect(!window.valid(), "fresh window is invalid");
    const WindowConfig config{};
    if (!create_window(window, config, "window create")) {
        expect(runtime.shutdown() == SdlError::None, "runtime shutdown after create failure");
        return finish_case();
    }
    expect(window.valid(), "window is valid after create");
    expect(window.create(config) == WindowError::AlreadyCreated, "duplicate create rejected");
    expect(window.resize(800, 600) == WindowError::None, "resize succeeds");
    expect(window.show() == WindowError::None, "show succeeds");
    expect(window.focus() == WindowError::None, "focus request succeeds");
    expect(window.destroy() == WindowError::None, "destroy succeeds");
    expect(!window.valid(), "window invalid after destroy");
    expect(window.destroy() == WindowError::None, "repeated destroy is idempotent");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown succeeds");
    return finish_case();
}

bool run_invalid() {
    begin_case();
    Window window;
    expect(window.resize(10, 10) == WindowError::NotCreated, "resize before create rejected");
    expect(window.show() == WindowError::NotCreated, "show before create rejected");
    expect(window.focus() == WindowError::NotCreated, "focus before create rejected");
    expect(window.destroy() == WindowError::None, "destroy before create is idempotent");

    SdlRuntime runtime;
    if (!initialize_runtime(runtime, "runtime initialize for invalid test")) {
        return finish_case();
    }

    WindowConfig bad{};
    bad.width = 0;
    bad.height = 480;
    expect(window.create(bad) == WindowError::InvalidSize, "zero width rejected");
    bad.width = 640;
    bad.height = 0;
    expect(window.create(bad) == WindowError::InvalidSize, "zero height rejected");

    const WindowConfig good{};
    if (!create_window(window, good, "valid create after invalid attempts")) {
        expect(runtime.shutdown() == SdlError::None, "runtime shutdown after invalid create failure");
        return finish_case();
    }
    expect(window.resize(0, 600) == WindowError::InvalidSize, "zero resize width rejected");
    expect(window.resize(800, -1) == WindowError::InvalidSize, "negative resize height rejected");
    expect(window.destroy() == WindowError::None, "destroy after invalid resize");
    if (!create_window(window, good, "recreate after destroy")) {
        expect(runtime.shutdown() == SdlError::None, "runtime shutdown after recreate failure");
        return finish_case();
    }
    expect(window.destroy() == WindowError::None, "destroy recreated window");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown");
    return finish_case();
}

bool run_wrong_thread() {
    begin_case();
    SdlRuntime runtime;
    if (!initialize_runtime(runtime, "runtime initialize for wrong-thread test")) {
        return finish_case();
    }

    Window window;
    WindowError worker_create = WindowError::None;
    std::thread creator([&window, &worker_create] {
        worker_create = window.create(WindowConfig{});
    });
    creator.join();
    expect(worker_create == WindowError::WrongThread, "worker create rejected");
    expect(!window.valid(), "worker create leaves window invalid");

    if (!create_window(window, WindowConfig{}, "owner create after worker rejection")) {
        expect(runtime.shutdown() == SdlError::None, "runtime shutdown after owner create failure");
        return finish_case();
    }
    WindowError worker_destroy = WindowError::None;
    std::thread destroyer([&window, &worker_destroy] {
        worker_destroy = window.destroy();
    });
    destroyer.join();
    expect(worker_destroy == WindowError::WrongThread, "worker destroy rejected");
    expect(window.valid(), "worker destroy leaves window valid");
    expect(window.destroy() == WindowError::None, "owner destroy succeeds");
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown");
    return finish_case();
}

bool run_not_initialized() {
    begin_case();
    Window window;
    expect(window.create(WindowConfig{}) == WindowError::VideoNotInitialized,
           "create without SDL video initialization rejected");
    expect(!window.valid(), "window invalid without video initialization");
    expect(window.destroy() == WindowError::None, "destroy without window is idempotent");
    return finish_case();
}

bool run_lifetime() {
    begin_case();
    SdlRuntime runtime;
    if (!initialize_runtime(runtime, "runtime initialize for lifetime test")) {
        return finish_case();
    }

    Window window;
    for (int cycle = 0; cycle < 50; ++cycle) {
        WindowConfig config{};
        config.width = 640 + cycle;
        config.height = 480 + cycle;
        if (!create_window(window, config, "cycle window create")) {
            expect(runtime.shutdown() == SdlError::None, "runtime shutdown after cycle create failure");
            return finish_case();
        }
        expect(window.valid(), "cycle window valid");
        expect(window.show() == WindowError::None, "cycle show");
        expect(window.resize(800 + cycle, 600 + cycle) == WindowError::None, "cycle resize");
        expect(window.focus() == WindowError::None, "cycle focus request");
        expect(window.destroy() == WindowError::None, "cycle destroy");
        expect(!window.valid(), "cycle window invalid after destroy");
    }
    expect(runtime.shutdown() == SdlError::None, "runtime shutdown after cycles");
    return finish_case();
}

} // namespace

int main(int argc, char** argv) {
    const std::string_view mode = argc > 1 ? std::string_view(argv[1]) : std::string_view("all");

    try {
        bool ok = true;
        if (mode == "all" || mode == "not_initialized") {
            ok = run_not_initialized() && ok;
        }
        if (mode == "all" || mode == "basic") {
            ok = run_basic() && ok;
        }
        if (mode == "all" || mode == "invalid") {
            ok = run_invalid() && ok;
        }
        if (mode == "all" || mode == "wrong_thread") {
            ok = run_wrong_thread() && ok;
        }
        if (mode == "all" || mode == "lifetime") {
            ok = run_lifetime() && ok;
        }

        if (mode != "all" && mode != "basic" && mode != "invalid" && mode != "wrong_thread"
            && mode != "not_initialized" && mode != "lifetime") {
            std::cerr << "Unknown test mode: " << mode << '\n';
            return 2;
        }

        if (ok) {
            std::cout << "PASS: " << mode << '\n';
            return 0;
        }
        std::cerr << "FAIL: " << mode << '\n';
        return 1;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: uncaught exception: " << error.what() << '\n';
        return 1;
    }
}
