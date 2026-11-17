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
