#include "stormline/core/internal/sdl_runtime.hpp"

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <thread>

namespace stormline::core::internal {
namespace {

bool on_owner_thread(const std::thread::id& owner) noexcept {
    return std::this_thread::get_id() == owner;
}

// SDL owns its process-wide video state. Query that native state rather than
// adding mutable global adapter state forbidden by the bounded SDL contract.
// NULL means an SDL query failure: fail closed, never call SDL_Quit.
bool windows_exist_or_query_failed() noexcept {
    int count = 0;
    SDL_Window** windows = SDL_GetWindows(&count);
    if (windows == nullptr) {
        return true;
    }
    SDL_free(windows);
    return count != 0;
}

} // namespace

SdlRuntime::SdlRuntime() noexcept
    : owner_thread_(std::this_thread::get_id()) {
}

SdlRuntime::~SdlRuntime() noexcept {
    if (!initialized_ || !on_owner_thread(owner_thread_) || !SDL_IsMainThread()) {
        return;
    }
    // The existing contract requires Window to be destroyed before its
    // SdlRuntime. Avoid UAF on erroneous destruction order, even though
    // final SDL_Quit cannot be performed without the owner's lifetime.
    if (!windows_exist_or_query_failed()) {
        SDL_Quit();
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
        // SDL's own process-wide initialized flags exclude a second owner.
        if (SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
            return SdlError::AlreadyInitialized;
        }

        SDL_SetMainReady();
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
            SDL_Quit();
            return SdlError::InitFailed;
        }

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
        if (windows_exist_or_query_failed()) {
            return SdlError::WindowsActive;
        }

        SDL_Quit();
        initialized_ = false;
        return SdlError::None;
    } catch (...) {
        return SdlError::InternalFailure;
    }
}

bool SdlRuntime::initialized() const noexcept {
    return initialized_;
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
