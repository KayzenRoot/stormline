#include "stormline/core/internal/sdl_runtime.hpp"

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <cstddef>
#include <limits>
#include <thread>

namespace stormline::core::internal {
namespace {

bool on_owner_thread(const std::thread::id& owner) noexcept {
    return std::this_thread::get_id() == owner;
}

// SDL video has process-wide ownership. This state is private to the adapter,
// is only accessed on SDL's main thread, and outlives individual Runtime/Window
// objects. It is not an engine-wide service or a public singleton API.
struct ProcessState final {
    SdlRuntime* active{nullptr};
    std::size_t live_windows{0};
    bool deferred_quit{false};
    std::uint64_t generation{0};
};

ProcessState& process_state() noexcept {
    static ProcessState state;
    return state;
}

} // namespace

SdlRuntime::SdlRuntime() noexcept
    : owner_thread_(std::this_thread::get_id()) {
}

SdlRuntime::~SdlRuntime() noexcept {
    if (!initialized_ || !on_owner_thread(owner_thread_) || !SDL_IsMainThread()) {
        return;
    }
    auto& state = process_state();
    if (state.active != this) {
        return;
    }
    state.active = nullptr;
    initialized_ = false;
    if (state.live_windows == 0) {
        SDL_Quit();
    } else {
        // Do not SDL_Quit while a Window still owns SDL_Window*. A later
        // Window teardown completes quit; new runtimes are rejected meanwhile.
        state.deferred_quit = true;
    }
}

SdlError SdlRuntime::initialize() noexcept {
    try {
        if (!on_owner_thread(owner_thread_) || !SDL_IsMainThread()) {
            return SdlError::WrongThread;
        }
        if (initialized_) {
            return SdlError::AlreadyInitialized;
        }
        auto& state = process_state();
        if (state.active != nullptr || state.deferred_quit || state.live_windows != 0) {
            return SdlError::AlreadyInitialized;
        }

        SDL_SetMainReady();
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
            SDL_Quit();
            return SdlError::InitFailed;
        }

        state.active = this;
        initialized_ = true;
        return SdlError::None;
    } catch (...) {
        return SdlError::InternalFailure;
    }
}

SdlError SdlRuntime::shutdown() noexcept {
    try {
        if (!on_owner_thread(owner_thread_) || !SDL_IsMainThread()) {
            return SdlError::WrongThread;
        }
        if (!initialized_) {
            return SdlError::None;
        }
        auto& state = process_state();
        if (state.active != this || state.deferred_quit) {
            return SdlError::InternalFailure;
        }
        if (state.live_windows != 0) {
            return SdlError::WindowsActive;
        }

        SDL_Quit();
        state.active = nullptr;
        initialized_ = false;
        return SdlError::None;
    } catch (...) {
        return SdlError::InternalFailure;
    }
}

bool SdlRuntime::initialized() const noexcept {
    return initialized_;
}

bool SdlRuntime::owns_runtime() noexcept {
    const auto& state = process_state();
    return SDL_IsMainThread() && state.active != nullptr && !state.deferred_quit
           && SDL_WasInit(SDL_INIT_VIDEO) != 0;
}

std::uint64_t SdlRuntime::next_generation() noexcept {
    auto& state = process_state();
    if (!SDL_IsMainThread() || state.generation == std::numeric_limits<std::uint64_t>::max()) {
        return 0;
    }
    return ++state.generation;
}

bool SdlRuntime::window_created(std::uint64_t& surface, std::uint64_t& native) noexcept {
    if (!owns_runtime()) {
        return false;
    }
    const std::uint64_t new_surface = next_generation();
    const std::uint64_t new_native = next_generation();
    if (new_surface == 0 || new_native == 0
        || process_state().live_windows == std::numeric_limits<std::size_t>::max()) {
        return false;
    }
    ++process_state().live_windows;
    surface = new_surface;
    native = new_native;
    return true;
}

void SdlRuntime::window_destroyed() noexcept {
    if (!SDL_IsMainThread()) {
        return;
    }
    auto& state = process_state();
    if (state.live_windows == 0) {
        return;
    }
    --state.live_windows;
    if (state.live_windows == 0 && state.deferred_quit) {
        SDL_Quit();
        state.deferred_quit = false;
    }
}

SdlVersion linked_version() noexcept {
    try {
        const int version = SDL_GetVersion();
        return {
            SDL_VERSIONNUM_MAJOR(version),
            SDL_VERSIONNUM_MINOR(version),
            SDL_VERSIONNUM_MICRO(version)
        };
    } catch (...) {
        return {};
    }
}

} // namespace stormline::core::internal
