#include "stormline/core/internal/native_bridge.hpp"

#include <SDL3/SDL.h>

#include <cstring>

namespace stormline::core::internal {

NativeWindowSystem current_native_window_system() noexcept {
    const char* const driver = SDL_GetCurrentVideoDriver();
    if (driver == nullptr) {
        return NativeWindowSystem::Unknown;
    }
    if (std::strcmp(driver, "x11") == 0) {
        return NativeWindowSystem::X11;
    }
    if (std::strcmp(driver, "wayland") == 0) {
        return NativeWindowSystem::Wayland;
    }
    if (std::strcmp(driver, "windows") == 0) {
        return NativeWindowSystem::Win32;
    }
    if (std::strcmp(driver, "cocoa") == 0) {
        return NativeWindowSystem::Cocoa;
    }
    return NativeWindowSystem::Unknown;
}

}  // namespace stormline::core::internal
