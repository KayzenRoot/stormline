#include "stormline/core/internal/sdl_runtime.hpp"

#if defined(SDL_h_)
#error "SDL header/type leaked through the internal sdl_runtime header"
#endif

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <thread>

namespace {

using stormline::core::internal::SdlError;
using stormline::core::internal::SdlRuntime;
using stormline::core::internal::SdlVersion;
using stormline::core::internal::linked_version;

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

bool set_env(const char* name, const char* value) {
#if defined(_WIN32)
    return _putenv_s(name, value) == 0;
#else
    return ::setenv(name, value, 1) == 0;
#endif
}

bool unset_env(const char* name) {
#if defined(_WIN32)
    return _putenv_s(name, "") == 0;
#else
    return ::unsetenv(name) == 0;
#endif
}

bool read_env(const char* name, std::string& value) {
#if defined(_WIN32)
    char* buffer = nullptr;
    std::size_t length = 0;
    if (_dupenv_s(&buffer, &length, name) != 0) {
        return false;
    }
    const bool present = buffer != nullptr;
    if (present) {
        value = buffer;
    }
    std::free(buffer);
    return present;
#else
    const char* raw = std::getenv(name);
    if (raw == nullptr) {
        return false;
    }
    value = raw;
    return true;
#endif
}

bool run_basic() {
    begin_case();
    SdlRuntime runtime;
    expect(!runtime.initialized(), "fresh runtime is uninitialized");

    expect(runtime.initialize() == SdlError::None, "initialize succeeds");
    expect(runtime.initialized(), "runtime reports initialized");
    expect(runtime.initialize() == SdlError::AlreadyInitialized, "duplicate initialize rejected");
    {
        SdlRuntime second;
        const SdlError duplicate = second.initialize();
        expect(duplicate == SdlError::AlreadyInitialized, "second runtime must not own global SDL state");
        if (duplicate == SdlError::None) {
            expect(second.shutdown() == SdlError::None, "baseline duplicate cleaned before continuing");
        }
    }
    expect(runtime.shutdown() == SdlError::None, "shutdown succeeds");
    expect(!runtime.initialized(), "runtime reports uninitialized");
    expect(runtime.shutdown() == SdlError::None, "repeated shutdown is idempotent");

    for (int cycle = 0; cycle < 20; ++cycle) {
        expect(runtime.initialize() == SdlError::None, "cycle initialize");
        expect(runtime.initialized(), "cycle initialized");
        expect(runtime.shutdown() == SdlError::None, "cycle shutdown");
        expect(!runtime.initialized(), "cycle uninitialized");
    }
    return finish_case();
}

bool run_wrong_thread() {
    begin_case();
    SdlRuntime runtime;
    SdlError worker_init = SdlError::None;
    std::thread initializer([&runtime, &worker_init] {
        worker_init = runtime.initialize();
    });
    initializer.join();
    expect(worker_init == SdlError::WrongThread, "worker initialize rejected");
    expect(!runtime.initialized(), "worker initialize leaves runtime uninitialized");

    expect(runtime.initialize() == SdlError::None, "owner initialize succeeds");
    SdlError worker_stop = SdlError::None;
    std::thread stopper([&runtime, &worker_stop] {
        worker_stop = runtime.shutdown();
    });
    stopper.join();
    expect(worker_stop == SdlError::WrongThread, "worker shutdown rejected");
    SdlError background_owner = SdlError::None;
    std::thread background([&background_owner] {
        SdlRuntime wrong_owner;
        background_owner = wrong_owner.initialize();
        if (background_owner == SdlError::None) {
            (void)wrong_owner.shutdown();
        }
    });
    background.join();
    expect(background_owner == SdlError::WrongThread,
           "runtime constructed off SDL main thread cannot initialize video");
    expect(runtime.initialized(), "worker shutdown leaves runtime initialized");
    expect(runtime.shutdown() == SdlError::None, "owner shutdown succeeds");
    return finish_case();
}

bool run_init_failure() {
    begin_case();
    std::string saved;
    const bool had_previous = read_env("SDL_VIDEODRIVER", saved);

    SdlRuntime runtime;
    expect(set_env("SDL_VIDEODRIVER", "stormline_invalid_driver"), "invalid driver env set");
    expect(runtime.initialize() == SdlError::InitFailed, "invalid driver fails init");
    expect(!runtime.initialized(), "failed init leaves runtime uninitialized");

    if (had_previous) {
        expect(set_env("SDL_VIDEODRIVER", saved.c_str()), "previous driver restored");
    } else {
        expect(unset_env("SDL_VIDEODRIVER"), "previous driver unset");
    }
    expect(runtime.initialize() == SdlError::None, "init recovers after driver restore");
    expect(runtime.shutdown() == SdlError::None, "recovery shutdown");
    return finish_case();
}

bool run_destructor() {
    begin_case();
    {
        SdlRuntime runtime;
        expect(runtime.initialize() == SdlError::None, "destructor case initialize");
    }
    SdlRuntime runtime;
    expect(runtime.initialize() == SdlError::None, "init after destructor QUIT");
    expect(runtime.shutdown() == SdlError::None, "shutdown after destructor");
    return finish_case();
}

bool run_version() {
    begin_case();
    const SdlVersion version = linked_version();
    expect(version.major == 3, "SDL major is 3");
    expect(version.minor == 4, "SDL minor is 4");
    expect(version.patch == 20, "SDL patch is 20");
    return finish_case();
}

bool run_header() {
    begin_case();
    expect(true, "header isolation compile-time check");
    return finish_case();
}

} // namespace

int main(int argc, char** argv) {
    const std::string_view mode = argc > 1 ? std::string_view(argv[1]) : std::string_view("all");

    try {
        bool ok = true;
        if (mode == "all" || mode == "basic") {
            ok = run_basic() && ok;
        }
        if (mode == "all" || mode == "wrong_thread") {
            ok = run_wrong_thread() && ok;
        }
        if (mode == "all" || mode == "init_failure") {
            ok = run_init_failure() && ok;
        }
        if (mode == "all" || mode == "destructor") {
            ok = run_destructor() && ok;
        }
        if (mode == "all" || mode == "version") {
            ok = run_version() && ok;
        }
        if (mode == "all" || mode == "header") {
            ok = run_header() && ok;
        }

        if (mode != "all" && mode != "basic" && mode != "wrong_thread" && mode != "init_failure"
            && mode != "destructor" && mode != "version" && mode != "header") {
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
