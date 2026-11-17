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

} // namespace

SdlRuntime::SdlRuntime() noexcept
    : owner_thread_(std::this_thread::get_id()) {
}

SdlRuntime::~SdlRuntime() noexcept {
    if (initialized_ && on_owner_thread(owner_thread_)) {
        SDL_Quit();
        initialized_ = false;
    }
}

SdlError SdlRuntime::initialize() noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return SdlError::WrongThread;
        }
        if (initialized_) {
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
        if (!on_owner_thread(owner_thread_)) {
            return SdlError::WrongThread;
        }
        if (!initialized_) {
            return SdlError::None;
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
