#include "stormline/core/internal/window.hpp"

#include <SDL3/SDL.h>

#include <new>

namespace stormline::core::internal {
namespace {

bool on_owner_thread(const std::thread::id& owner) noexcept {
    return std::this_thread::get_id() == owner;
}

} // namespace

struct Window::Impl final {
    SDL_Window* window{nullptr};
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
        if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
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
        impl->window = window;
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
        return SDL_SetWindowSize(impl_->window, width, height)
            ? WindowError::None
            : WindowError::ResizeFailed;
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

bool Window::valid() const noexcept {
    return impl_ && impl_->window != nullptr;
}

} // namespace stormline::core::internal
