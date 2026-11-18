#include "stormline/core/internal/window.hpp"
#include <SDL3/SDL.h>

#include <limits>
#include <new>

namespace stormline::core::internal {
namespace {

bool on_owner_thread(const std::thread::id& owner) noexcept {
    return std::this_thread::get_id() == owner;
}

std::uint64_t window_token(SDL_Window* window, std::uint32_t sequence) noexcept {
    const SDL_WindowID id = SDL_GetWindowID(window);
    if (id == 0 || sequence == 0) {
        return 0;
    }
    // SDL owns the window identity, and Window owns its persistent revision
    // counter. This avoids global mutable adapter state.
    return (static_cast<std::uint64_t>(id) << 32) | sequence;
}

} // namespace

struct Window::Impl final {
    SDL_Window* window{nullptr};
    std::uint64_t surface_generation{1};
    std::uint64_t native_generation{1};
    NativeWindowHandle issued_native{};
    std::uint32_t display_id{0};
    int pixel_width{0};
    int pixel_height{0};
};

Window::Window() noexcept
    : owner_thread_(std::this_thread::get_id()) {
}

Window::~Window() noexcept {
    if (impl_ && on_owner_thread(owner_thread_) && impl_->window != nullptr) {
        SDL_DestroyWindow(impl_->window);
    }
}

WindowError Window::create(const WindowConfig& config) noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return WindowError::WrongThread;
        }
        if (impl_) {
            return WindowError::AlreadyCreated;
        }
        if (config.width <= 0 || config.height <= 0) {
            return WindowError::InvalidSize;
        }
        if (SDL_WasInit(SDL_INIT_VIDEO) == 0 || !SDL_IsMainThread()) {
            return WindowError::VideoNotInitialized;
        }

        SDL_Window* window = SDL_CreateWindow(
            "Stormline",
            config.width,
            config.height,
            SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
        if (window == nullptr) {
            return WindowError::CreateFailed;
        }

        Impl* impl = new (std::nothrow) Impl{};
        if (impl == nullptr) {
            SDL_DestroyWindow(window);
            return WindowError::AllocationFailed;
        }
        if (generation_counter_ >= std::numeric_limits<std::uint32_t>::max() - 2U) {
            SDL_DestroyWindow(window);
            delete impl;
            return WindowError::InternalFailure;
        }
        const std::uint64_t native_generation = window_token(window, ++generation_counter_);
        const std::uint64_t surface_generation = window_token(window, ++generation_counter_);
        if (native_generation == 0 || surface_generation == 0) {
            SDL_DestroyWindow(window);
            delete impl;
            return WindowError::InternalFailure;
        }
        impl->window = window;
        impl->surface_generation = surface_generation;
        impl->native_generation = native_generation;
        impl->display_id = static_cast<std::uint32_t>(SDL_GetDisplayForWindow(window));
        int pixel_width = 0;
        int pixel_height = 0;
        if (SDL_GetWindowSizeInPixels(window, &pixel_width, &pixel_height)) {
            impl->pixel_width = pixel_width;
            impl->pixel_height = pixel_height;
        }
        impl_.reset(impl);
        return WindowError::None;
    } catch (...) {
        return WindowError::InternalFailure;
    }
}

WindowError Window::destroy() noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return WindowError::WrongThread;
        }
        if (!impl_) {
            return WindowError::None;
        }
        if (impl_->window != nullptr) {
            SDL_DestroyWindow(impl_->window);
        }
        impl_.reset();
        return WindowError::None;
    } catch (...) {
        return WindowError::InternalFailure;
    }
}

WindowError Window::resize(int width, int height) noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return WindowError::WrongThread;
        }
        if (!impl_) {
            return WindowError::NotCreated;
        }
        if (width <= 0 || height <= 0) {
            return WindowError::InvalidSize;
        }
        if (generation_counter_ == std::numeric_limits<std::uint32_t>::max()) {
            return WindowError::InternalFailure;
        }
        if (!SDL_SetWindowSize(impl_->window, width, height)) {
            return WindowError::ResizeFailed;
        }
        const std::uint64_t generation = window_token(impl_->window, ++generation_counter_);
        if (generation == 0) {
            return WindowError::InternalFailure;
        }
        impl_->surface_generation = generation;
        int pixel_width = 0;
        int pixel_height = 0;
        if (SDL_GetWindowSizeInPixels(impl_->window, &pixel_width, &pixel_height)) {
            impl_->pixel_width = pixel_width;
            impl_->pixel_height = pixel_height;
        }
        return WindowError::None;
    } catch (...) {
        return WindowError::InternalFailure;
    }
}

WindowError Window::show() noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return WindowError::WrongThread;
        }
        if (!impl_) {
            return WindowError::NotCreated;
        }
        return SDL_ShowWindow(impl_->window)
            ? WindowError::None
            : WindowError::ShowFailed;
    } catch (...) {
        return WindowError::InternalFailure;
    }
}

WindowError Window::focus() noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return WindowError::WrongThread;
        }
        if (!impl_) {
            return WindowError::NotCreated;
        }
        return SDL_RaiseWindow(impl_->window)
            ? WindowError::None
            : WindowError::FocusFailed;
    } catch (...) {
        return WindowError::InternalFailure;
    }
}

WindowError Window::query_surface(SurfaceMetrics& out) noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return WindowError::WrongThread;
        }
        if (!impl_) {
            return WindowError::NotCreated;
        }

        const SDL_DisplayID display = SDL_GetDisplayForWindow(impl_->window);
        const float scale = SDL_GetWindowDisplayScale(impl_->window);
        int logical_width = 0;
        int logical_height = 0;
        int pixel_width = 0;
        int pixel_height = 0;
        if (display == 0 || !(scale > 0.0F)
            || !SDL_GetWindowSize(impl_->window, &logical_width, &logical_height)
            || !SDL_GetWindowSizeInPixels(impl_->window, &pixel_width, &pixel_height)
            || logical_width <= 0 || logical_height <= 0
            || pixel_width <= 0 || pixel_height <= 0) {
            return WindowError::SurfaceQueryFailed;
        }

        const std::uint32_t display_id = static_cast<std::uint32_t>(display);
        if (impl_->display_id != 0
            && (impl_->display_id != display_id
                || impl_->pixel_width != pixel_width
                || impl_->pixel_height != pixel_height)) {
            if (generation_counter_ == std::numeric_limits<std::uint32_t>::max()) {
                return WindowError::SurfaceQueryFailed;
            }
            const std::uint64_t generation = window_token(impl_->window, ++generation_counter_);
            if (generation == 0) {
                return WindowError::SurfaceQueryFailed;
            }
            impl_->surface_generation = generation;
        }

        impl_->display_id = display_id;
        impl_->pixel_width = pixel_width;
        impl_->pixel_height = pixel_height;

        out.display_id = display_id;
        out.display_scale = scale;
        out.logical_width = logical_width;
        out.logical_height = logical_height;
        out.pixel_width = pixel_width;
        out.pixel_height = pixel_height;
        out.generation = impl_->surface_generation;
        return WindowError::None;
    } catch (...) {
        return WindowError::InternalFailure;
    }
}

bool Window::surface_valid(std::uint64_t generation) const noexcept {
    return on_owner_thread(owner_thread_) && impl_ && impl_->window != nullptr
           && generation != 0 && generation == impl_->surface_generation;
}

WindowError Window::query_native_handle(NativeWindowHandle& out) noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return WindowError::WrongThread;
        }
        if (!impl_) {
            return WindowError::NotCreated;
        }

        const SDL_PropertiesID properties = SDL_GetWindowProperties(impl_->window);
        if (properties == 0) {
            return WindowError::NativeHandleUnavailable;
        }

        NativeHandleKind kind = NativeHandleKind::None;
        std::uint64_t value = 0;

        void* pointer = SDL_GetPointerProperty(
            properties, SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);
        if (pointer != nullptr) {
            kind = NativeHandleKind::Win32Hwnd;
            value = static_cast<std::uint64_t>(reinterpret_cast<std::uintptr_t>(pointer));
        } else {
            pointer = SDL_GetPointerProperty(
                properties, SDL_PROP_WINDOW_COCOA_WINDOW_POINTER, nullptr);
        }
        if (kind == NativeHandleKind::None && pointer != nullptr) {
            kind = NativeHandleKind::CocoaWindow;
            value = static_cast<std::uint64_t>(reinterpret_cast<std::uintptr_t>(pointer));
        }
        if (kind == NativeHandleKind::None) {
            pointer = SDL_GetPointerProperty(
                properties, SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, nullptr);
        }
        if (kind == NativeHandleKind::None && pointer != nullptr) {
            kind = NativeHandleKind::WaylandSurface;
            value = static_cast<std::uint64_t>(reinterpret_cast<std::uintptr_t>(pointer));
        }
        if (kind == NativeHandleKind::None) {
            const Sint64 x11_window = SDL_GetNumberProperty(
                properties, SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0);
            if (x11_window != 0) {
                kind = NativeHandleKind::X11Window;
                value = static_cast<std::uint64_t>(x11_window);
            }
        }

        if (kind == NativeHandleKind::None || value == 0) {
            return WindowError::NativeHandleUnavailable;
        }

        out.kind = kind;
        out.value = value;
        out.generation = impl_->native_generation;
        impl_->issued_native = out;
        return WindowError::None;
    } catch (...) {
        return WindowError::InternalFailure;
    }
}

bool Window::native_handle_valid(const NativeWindowHandle& handle) const noexcept {
    return on_owner_thread(owner_thread_) && impl_ && impl_->window != nullptr
           && handle.kind != NativeHandleKind::None && handle.value != 0
           && handle.generation != 0
           && handle.kind == impl_->issued_native.kind
           && handle.value == impl_->issued_native.value
           && handle.generation == impl_->issued_native.generation
           && handle.generation == impl_->native_generation;
}

bool Window::valid() const noexcept {
    return impl_ && impl_->window != nullptr;
}

} // namespace stormline::core::internal
